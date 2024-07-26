/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 *
 * Copyright (c) 2019 Sagun K. (sagunxp@gmail.com).
 * Copyright (c) 2019 Horizon Dev Team.
 *
 * Base Author - Sagun K. (sagunxp@gmail.com)
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

#include "ZoneSystem.hpp"
#include "Server/Common/Server.hpp"
#include "Server/Zone/Packets/TransmittedPackets.hpp"
#include "Server/Zone/Zone.hpp"

bool Horizon::Zone::SCENARIO_LOGIN::Login::execute()
{
	std::shared_ptr<boost::mysql::tcp_ssl_connection> conn = sZone->get_database_connection();

	boost::mysql::statement stmt = conn->prepare_statement("SELECT `current_server` FROM `session_data` WHERE `game_account_id` = ? AND `auth_code` = ?");
	auto b1 = stmt.bind(_request.account_id, _request.auth_code);
	boost::mysql::results results;
	conn->execute(b1, results);

	if (results.rows().empty()) {
		HLog(error) << "Login error! Session data for game account " << _request.account_id << " and authentication code " << _request.auth_code << " does not exist.";
		return false;
	}

	auto r = results.rows()[0];

	std::string current_server = r[0].as_string();
	if (current_server.compare("Z") == 0) { // Already on Zone.
		ZC_REFUSE_ENTER pkt(std::dynamic_pointer_cast<SCENARIO_LOGIN>(get_runtime_context())->get_session());
		pkt.deliver(ZONE_SERV_ERROR_REJECT);
		return false;
	}

	stmt = conn->prepare_statement("SELECT `gender`, `group_id` FROM `game_accounts` WHERE `id` = ?");
	auto b2 = stmt.bind(_request.account_id);
	conn->execute(b2, results);
	
	if (results.rows().empty()) {
		HLog(error) << "Login error! Game account with id " << _request.account_id << " does not exist.";
		return false;
	}
	
	auto r2 = results.rows()[0];

	stmt = conn->prepare_statement("UPDATE `session_data` SET `current_server` = ? WHERE `game_account_id` = ? AND `auth_code` = ?");
	auto b3 = stmt.bind("Z", _request.account_id, _request.auth_code);
	conn->execute(b3, results);

	//uint64_t uuid = sZone->to_uuid((int8_t) UNIT_PLAYER, _request.account_id, _request.char_id, 0);
	//std::shared_ptr<Horizon::Zone::Units::Player> pl = std::make_shared<Horizon::Zone::Units::Player>(_session, uuid);

	//pl->create(_request.char_id, r2[0].as_string(), r2[1].as_int64());

	return true;
}

bool Horizon::Zone::SCENARIO_CREATE_USER::CreateUser::execute()
{
	std::shared_ptr<boost::mysql::tcp_ssl_connection> conn = sZone->get_database_connection();
	
	try {
		boost::mysql::statement stmt = conn->prepare_statement("SELECT `id`, `account_id`, `current_map`, `current_x`, `current_y` FROM `characters` WHERE id = ?");
		auto b1 = stmt.bind(_request.char_id);
        boost::mysql::static_results<s_user_info_query_result> results;
		conn->execute(b1, results);

		if (results.rows().empty()) {
			HLog(error) << "Error loading player, character with ID " << _request.char_id << " does not exist.";
			return false;
		}

		s_user_info_query_result user = results.rows()[0];
		
		Horizon::System::Result<s_user_info_query_result> result = Horizon::System::Result<s_user_info_query_result>(user);
		set_result(result);
		std::dynamic_pointer_cast<SCENARIO_CREATE_USER>(get_runtime_context())->set_result(result);
	}
	catch (boost::mysql::error_with_diagnostics &error) {
		HLog(error) << "SCENARIO_CREATE_USER: " << error.what();
		return false;
	}
	catch (std::exception& error) {
		HLog(error) << "SCENARIO_CREATE_USER:" << error.what();
		return false;
	}

	return true;
}

bool Horizon::Zone::SCENARIO_CREATE_PLAYER::CreatePlayer::execute()
{
	return true;
}

bool Horizon::Zone::SCENARIO_LOGIN_RESPONSE::LoginResponse::execute()
{	
	ZC_AID zc_aid(std::dynamic_pointer_cast<SCENARIO_LOGIN_RESPONSE>(get_runtime_context())->get_session());
	zc_aid.deliver(_request.account_id);
	
	ZC_ACCEPT_ENTER2 zc_ae2(std::dynamic_pointer_cast<SCENARIO_LOGIN_RESPONSE>(get_runtime_context())->get_session());
	zc_ae2.deliver(_request.current_x, _request.current_y, DIR_SOUTH, _request.font); // edit third argument to saved font.
	return true;
}