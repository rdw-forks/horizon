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

#ifndef HORIZON_ZONE_ZONESYSTEM_HPP
#define HORIZON_ZONE_ZONESYSTEM_HPP

#include "Server/Zone/Definitions/ItemDefinitions.hpp"
#include "Server/Common/System.hpp"

#include <boost/mysql/error_with_diagnostics.hpp>
#include <boost/mysql/handshake_params.hpp>
#include <boost/mysql/results.hpp>
#include <boost/mysql/static_results.hpp>
#include <boost/mysql/tcp_ssl.hpp>
#include <boost/describe/class.hpp>

class DatabaseProcess;

struct s_character_info 
{
	int32_t character_id{0};
	int16_t slot{0};
	int8_t online{0};
	std::string gender{""};
	int32_t max_inventory_size{MAX_INVENTORY_SIZE};
	int64_t last_unique_id{0};
	int8_t font{0};
	int32_t unban_time{0};
	int32_t rename_count{0};
	int16_t hotkey_row_index{0};
	int32_t change_slot_count{0};
	int8_t show_equip{0}; 
	int8_t allow_party{0};
	int32_t partner_aid{0};
	int32_t father_aid{0}, mother_aid{0}, child_aid{0};
	int32_t party_id{0}, guild_id{0};
	int32_t homun_id{0}, pet_id{0}, elemental_id{0};
	std::string saved_map{""};
	int32_t saved_x{0}, saved_y{0};
	std::string current_map{""};
	int32_t current_x{0}, current_y{0};
};

BOOST_DESCRIBE_STRUCT(s_character_info, (), (character_id, slot, online,
	gender, max_inventory_size, last_unique_id, font, unban_time, rename_count,
	hotkey_row_index, change_slot_count, show_equip, allow_party, partner_aid,
	father_aid, mother_aid, child_aid, party_id, guild_id,
	homun_id, pet_id, elemental_id, saved_map, saved_x, saved_y,
	current_map, current_x, current_y))

struct s_user_info_query_result
{
	int64_t id;
	int64_t account_id;
	std::string current_map;
	int32_t current_x;
	int32_t current_y;
};

BOOST_DESCRIBE_STRUCT(s_user_info_query_result, (), (id, account_id, current_map, current_x, current_y))

namespace Horizon
{
namespace Zone
{

class ZoneSession;

struct s_scenario_login_request
{
	uint32_t account_id;
	uint32_t char_id;
	uint32_t auth_code;
	uint32_t client_time;
	uint8_t gender;
};

class SCENARIO_LOGIN : public Horizon::System::RuntimeRoutineContext<std::shared_ptr<s_scenario_login_request>>
{
public:
	SCENARIO_LOGIN(std::shared_ptr<ZoneSession> session, std::shared_ptr<MainframeComponent> component) 
	: _session(session), Horizon::System::RuntimeRoutineContext<std::shared_ptr<s_scenario_login_request>>(component) { }

	class Login : public Horizon::System::RuntimeRoutineContext<std::shared_ptr<s_scenario_login_request>>::Work<SCENARIO_LOGIN, s_scenario_login_request>
	{
	public:
		Login(std::shared_ptr<SCENARIO_LOGIN> parent_context, s_scenario_login_request request) 
		: Horizon::System::RuntimeRoutineContext<std::shared_ptr<s_scenario_login_request>>::Work<SCENARIO_LOGIN, s_scenario_login_request>(parent_context, request) { }

		bool execute();
	};

	std::shared_ptr<ZoneSession> _session;
};

class SCENARIO_CREATE_USER : public Horizon::System::RuntimeRoutineContext<std::shared_ptr<s_user_info_query_result>>
{
public:
	SCENARIO_CREATE_USER(std::shared_ptr<MainframeComponent> component) : Horizon::System::RuntimeRoutineContext<std::shared_ptr<s_user_info_query_result>>(component) { }

	struct s_scenario_create_user_request
	{
		uint32_t char_id;
	};

	class CreateUser : public Horizon::System::RuntimeRoutineContext<std::shared_ptr<s_user_info_query_result>>::Work<SCENARIO_CREATE_USER, s_scenario_create_user_request>
	{
	public:
		CreateUser(std::shared_ptr<SCENARIO_CREATE_USER> parent_context, s_scenario_create_user_request request) 
		: Horizon::System::RuntimeRoutineContext<std::shared_ptr<s_user_info_query_result>>::Work<SCENARIO_CREATE_USER, s_scenario_create_user_request>(parent_context, request) { }

		bool execute();
	private:
		s_user_info_query_result _user;
	};
};

struct s_player_loaded_data
{
	int32_t account_id;
	int32_t char_id;
	std::string map;
	int32_t current_x, current_y;
};

class SCENARIO_CREATE_PLAYER : public Horizon::System::RuntimeRoutineContext<s_player_loaded_data, std::shared_ptr<s_user_info_query_result>>
{
public:
	SCENARIO_CREATE_PLAYER(std::shared_ptr<SCENARIO_CREATE_USER> create_user_context, std::shared_ptr<MainframeComponent> component) 
	: _create_user_context(create_user_context), Horizon::System::RuntimeRoutineContext<s_player_loaded_data, std::shared_ptr<s_user_info_query_result>>(component) { }

	class CreatePlayer : public Horizon::System::RuntimeRoutineContext<s_player_loaded_data, std::shared_ptr<s_user_info_query_result>>::Work<SCENARIO_CREATE_PLAYER, s_player_loaded_data, int, s_user_info_query_result>
	{
	public:
		CreatePlayer(std::shared_ptr<SCENARIO_CREATE_PLAYER> parent_context, s_player_loaded_data request, std::shared_ptr<Result<s_user_info_query_result>> user) 
		: Horizon::System::RuntimeRoutineContext<s_player_loaded_data, std::shared_ptr<s_user_info_query_result>>::Work<SCENARIO_CREATE_PLAYER, s_player_loaded_data, int, s_user_info_query_result>(parent_context, request, user) 
		{ }

		bool execute();
	};

	bool run()
	{
		prepare<SCENARIO_CREATE_USER>(_create_user_context);

		// use result in work.
		if (RuntimeRoutineContext::run()) {
			return true;
		}

		return false;
	}

	std::shared_ptr<SCENARIO_CREATE_USER> _create_user_context;
};

class SCENARIO_LOGIN_RESPONSE : public Horizon::System::RuntimeRoutineContext<int>
{
public:
	SCENARIO_LOGIN_RESPONSE(std::shared_ptr<ZoneSession> session, std::shared_ptr<MainframeComponent> component) 
	: _session(session), Horizon::System::RuntimeRoutineContext<int>(component) { }

	struct s_scenario_login_response_request
	{
		uint32_t account_id;
		uint32_t current_x, current_y;
		int8_t font;
	};

	class LoginResponse : public Horizon::System::RuntimeRoutineContext<int>::Work<SCENARIO_LOGIN_RESPONSE, s_scenario_login_response_request>
	{
	public:
		LoginResponse(std::shared_ptr<SCENARIO_LOGIN_RESPONSE> parent_context, s_scenario_login_response_request request) 
		: Horizon::System::RuntimeRoutineContext<int>::Work<SCENARIO_LOGIN_RESPONSE, s_scenario_login_response_request>(parent_context, request) { }

		bool execute();
	};

	std::shared_ptr<ZoneSession> _session;
};
}
}
#endif // HORIZON_ZONE_ZONESYSTEM_HPP
