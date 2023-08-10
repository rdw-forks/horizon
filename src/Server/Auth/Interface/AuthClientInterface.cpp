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

#include <mysqlx/xdevapi.h>

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

		mysqlx::Session db_session = sAuth->database_pool()->get_connection();
		mysqlx::RowResult rr = db_session.sql("SELECT * `game_accounts` WHERE `username` = ?").bind(username).execute();

		mysqlx::Row r = rr.fetchOne();

		if (r.isNull()) {
			HLog(info) << "Recieved connection request for unknown account '" << username << "'.";

			enum game_account_gender_type gender;

			HLog(info) << "Creating a new account for user '" << username << "' with password '" << password << "'.";

			try {
				db_session.sql("INSERT INTO `game_accounts` (`username`, `hash`, `salt`, `gender`, `group_id`, `state`, `login_count`, `last_login`, `last_ip`, `character_slots`) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)")
					.bind(username, password, "", (gender == (int)ACCOUNT_GENDER_FEMALE ? "F" : "M"), 0, (int)ACCOUNT_STATE_NONE, 1, std::time(nullptr), get_session()->get_socket()->remote_ip_address(), 3)
					.execute();
				mysqlx::RowResult rr = db_session.sql("SELECT LAST_INSERT_ID() AS id;").execute();
				mysqlx::Row r = rr.fetchOne();
				int last_insert_id = r[0].get<int>();
				uint32_t aid = last_insert_id;
				acal.deliver(aid, aid, 0, gender);

				db_session.sql("REPLACE INTO `session_data` (`auth_code`, `game_account_id`, `client_version`, `client_type`, `character_slots`, `group_id`, `connect_time`, `current_server`) VALUES (?, ?, ?, ?, ?, ?, ?, ?);")
					.bind(last_insert_id, aid, PACKET_VERSION, client_type, 3, 0, std::time(nullptr), "A")
					.execute();

				HLog(info) << "Session (" << aid << ") has been initiated.";
				HLog(info) << "Request for authorization of account '" << username << "' (" << aid << ")" << " has been granted.";
			}
			catch (std::exception& error) {
				HLog(error) << error.what();
				acrl.deliver(login_error_codes::ERR_SESSION_CONNECTED, block_date, 0);
				sAuth->database_pool()->release_connection(std::move(db_session));
				return false;
			}

			sAuth->database_pool()->release_connection(std::move(db_session));
			return true;
		}

		sAuth->database_pool()->release_connection(std::move(db_session));
		
		acrl.deliver(login_error_codes::ERR_SESSION_CONNECTED, block_date, 0);
		return false;
	}

	mysqlx::Session db_session = sAuth->database_pool()->get_connection();
	
	try
	{
		mysqlx::RowResult rr = db_session.sql("SELECT * FROM `game_accounts` WHERE `username` = ?")
			.bind(username)
			.execute();

		mysqlx::Row r = rr.fetchOne();

		if (r.isNull()) {
			HLog(info) << "Recieved connection request for unknown account '" << username << "'.";
			acrl.deliver(login_error_codes::ERR_UNREGISTERED_ID, block_date, 0);
			sAuth->database_pool()->release_connection(std::move(db_session));
			return false;
		}

		std::string hash = r[2].get<std::string>();
		// std::string salt = res.front().salt;

		uint32_t aid = r[0].get<int>();
		uint32_t group_id = r[6].get<int>();
		uint32_t gender = r[4].get<std::string>().compare("M") == 0 ? 0 : 1;

		if (password.compare(hash) != 0) {
			HLog(info) << "Incorrect password for account '" << username << "' with password '" << password << "'.";
			acrl.deliver(login_error_codes::ERR_INCORRECT_PASSWORD, block_date, 0);
			sAuth->database_pool()->release_connection(std::move(db_session));
			return false;
		}

		mysqlx::RowResult rr2 = db_session.sql("SELECT * FROM `session_data` WHERE `game_account_id` = ?")
			.bind(aid)
			.execute();

		mysqlx::Row r3 = rr2.fetchOne();

		if (!r3.isNull()) {
			acrl.deliver(login_error_codes::ERR_SESSION_CONNECTED, block_date, 0);
			sAuth->database_pool()->release_connection(std::move(db_session));
			return false;
		}
		else {
			db_session.sql("INSERT INTO `session_data` (`auth_code`, `game_account_id`, `client_version`, `client_type`, `character_slots`, `group_id`, `connect_time`, `current_server`) VALUES (?, ?, ?, ?, ?, ?, ?, ?)")
				.bind(aid, aid, PACKET_VERSION, client_type, 3, 0, std::time(nullptr), "A")
				.execute();

			HLog(info) << "Session (" << aid << ") has been initiated.";
		}

		acal.deliver(aid, aid, group_id, gender);

		HLog(info) << "Request for authorization of account '" << username << "' (" << aid << ")" << " has been granted.";
	}
	catch (mysqlx::Error& err) {
		HLog(error) << err.what();
		sAuth->database_pool()->release_connection(std::move(db_session));
		return false;
	}
	catch (std::exception& err) {
		HLog(error) << err.what();
		sAuth->database_pool()->release_connection(std::move(db_session));
		return false;
	}

	sAuth->database_pool()->release_connection(std::move(db_session));
	
	return true;
}

bool AuthClientInterface::client_login_otp_response()
{
	AC_LOGIN_OTP pkt(get_session());
	pkt.deliver();
	return true;
}