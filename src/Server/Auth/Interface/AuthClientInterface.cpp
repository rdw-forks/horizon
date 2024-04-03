/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 * Copyright (c) 2020- Horizon Dev Team.
 *
 * Base Author - Sagun Khosla. (sagunxp@gmail.com)
 *
 * This library is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 **************************************************/

#include "AuthClientInterface.hpp"

#include "Common/Configuration/Database.hpp"

#include "Server/Auth/Auth.hpp"
#include "Server/Auth/Packets/TransmittedPackets.hpp"
#include "Server/Auth/Session/AuthSession.hpp"
#include "Server/Auth/Socket/AuthSocket.hpp"

using namespace Horizon::Auth;

AuthClientInterface::AuthClientInterface(std::shared_ptr<AuthSession> s)
: ClientInterface(s)
{
	
}

AuthClientInterface::~AuthClientInterface()
{
	
}


bool AuthClientInterface::process_login(std::string username, std::string password, uint16_t version, uint16_t client_type)
{
	AC_ACCEPT_LOGIN acal(get_session());
	AC_REFUSE_LOGIN acrl(get_session());
	int pos = 0;
	char block_date[20]{ 0 };

	if (((pos = username.find("_m")) || (pos = username.find("_f"))) && pos != std::string::npos) {
		enum game_account_gender_type gender = ACCOUNT_GENDER_NONE;

		if (username.find("_m")) {
			username = username.substr(0, pos);
			gender = ACCOUNT_GENDER_MALE;
		}
		else if (username.find("_f")) {
			username = username.substr(0, pos);
			gender = ACCOUNT_GENDER_FEMALE;
		}

		//std::string salt = sAuth->get_auth_config()._password_salt_mix.c_str();
		//std::string hash = argon2.gen_hash(password, salt);

		auto conn = sAuth->get_database_connection();
		auto b1 = conn->prepare_statement("SELECT * `game_accounts` WHERE `username` = ?").bind(username);
		boost::mysql::results results;
		conn->execute(b1, results);

		if (results.rows().empty()) {
			HLog(info) << "Recieved connection request for unknown account '" << username << "'.";

			enum game_account_gender_type gender;

			HLog(info) << "Creating a new account for user '" << username << "' with password '" << password << "'.";

			try {
				boost::mysql::statement stmt = conn->prepare_statement("INSERT INTO `game_accounts` (`username`, `hash`, `salt`, `gender`, `group_id`, `state`, `login_count`, `last_login`, `last_ip`, `character_slots`) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
				auto b2 = stmt.bind(username, password, "", (gender == (int)ACCOUNT_GENDER_FEMALE ? "F" : "M"), 0, (int)ACCOUNT_STATE_NONE, 1, std::time(nullptr), get_session()->get_socket()->remote_ip_address(), 3);
				conn->execute(b2, results);
				uint32_t aid = results.last_insert_id();
				acal.deliver(aid, aid, 0, gender);

				stmt = conn->prepare_statement("REPLACE INTO `session_data` (`auth_code`, `game_account_id`, `client_version`, `client_type`, `character_slots`, `group_id`, `connect_time`, `current_server`) VALUES (?, ?, ?, ?, ?, ?, ?, ?);");
				auto b3 = stmt.bind(results.last_insert_id(), aid, PACKET_VERSION, client_type, 3, 0, std::time(nullptr), "A");
				conn->execute(b3, results);

				HLog(info) << "Session (" << aid << ") has been initiated.";
				HLog(info) << "Request for authorization of account '" << username << "' (" << aid << ")" << " has been granted.";
			}
			catch (std::exception& error) {
				HLog(error) << error.what();
				acrl.deliver(login_error_codes::ERR_SESSION_CONNECTED, block_date, 0);
				return false;
			}
			return true;
		}
		
		acrl.deliver(login_error_codes::ERR_SESSION_CONNECTED, block_date, 0);
		return false;
	}
	
	try
	{
		auto conn = sAuth->get_database_connection();
		boost::mysql::statement stmt = conn->prepare_statement("SELECT * FROM `game_accounts` WHERE `username` = ?");
		auto b1 = stmt.bind(username);
		boost::mysql::results results;
		conn->execute(b1, results);

		if (results.rows().empty()) {
			HLog(info) << "Recieved connection request for unknown account '" << username << "'.";
			acrl.deliver(login_error_codes::ERR_UNREGISTERED_ID, block_date, 0);
			return false;
		}

		std::string hash = results.rows()[0][2].as_string();
		// std::string salt = res.front().salt;

		uint32_t aid = results.rows()[0][0].as_uint64();
		uint32_t group_id = results.rows()[0][6].as_int64();
		uint32_t gender = results.rows()[0][4].as_string().compare("M") == 0 ? 0 : 1;

		if (password.compare(hash) != 0) {
			HLog(info) << "Incorrect password for account '" << username << "' with password '" << password << "'.";
			acrl.deliver(login_error_codes::ERR_INCORRECT_PASSWORD, block_date, 0);
			return false;
		}

		stmt = conn->prepare_statement("SELECT * FROM `session_data` WHERE `game_account_id` = ?");
		auto b2 = stmt.bind(aid);
		boost::mysql::results r2;
		conn->execute(b2, r2);

		if (!r2.rows().empty()) {
			acrl.deliver(login_error_codes::ERR_SESSION_CONNECTED, block_date, 0);
			return false;
		}
		else {
			stmt = conn->prepare_statement("INSERT INTO `session_data` (`auth_code`, `game_account_id`, `client_version`, `client_type`, `character_slots`, `group_id`, `connect_time`, `current_server`) VALUES (?, ?, ?, ?, ?, ?, ?, ?)");
			auto b3 = stmt.bind(aid, aid, PACKET_VERSION, client_type, 3, 0, std::time(nullptr), "A");
			boost::mysql::results r3;
			conn->execute(b3, r3);

			HLog(info) << "Session (" << aid << ") has been initiated.";
		}

		acal.deliver(aid, aid, group_id, gender);

		HLog(info) << "Request for authorization of account '" << username << "' (" << aid << ")" << " has been granted.";
	}
	catch (boost::mysql::error_with_diagnostics &err) {
		HLog(error) << err.what();
		return false;
	}
	catch (std::exception& err) {
		HLog(error) << err.what();
		return false;
	}
	
	return true;
}

bool AuthClientInterface::client_login_otp_response()
{
	AC_LOGIN_OTP pkt(get_session());
	pkt.deliver();
	return true;
}