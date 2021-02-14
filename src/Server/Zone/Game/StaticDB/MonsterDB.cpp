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

#include "MonsterDB.hpp"

#include "Server/Common/Definitions/LuaDefinitionSync.hpp"
#include "Server/Zone/Zone.hpp"

using namespace Horizon::Zone;

MonsterDatabase::MonsterDatabase()
{
	//
}

MonsterDatabase::~MonsterDatabase()
{
	//
}

bool MonsterDatabase::load()
{
	sol::state lua;
	int total_entries = 0;

	lua.open_libraries(sol::lib::base);
	lua.open_libraries(sol::lib::package);

	sync_monster_definitions(lua);
	sync_item_definitions(lua);
	sync_entity_definitions(lua);

	std::string tmp_string;
	std::string file_path = sZone->config().get_static_db_path().string() + "mob_db.lua";


	// Read the file. If there is an error, report it and exit.
	try {
		lua.script_file(file_path);
		sol::table mob_tbl = lua.get<sol::table>("mob_db");
		mob_tbl.for_each([this, &total_entries] (sol::object const &key, sol::object const &value) {
			total_entries += load_internal(key, value);
		});
		HLog(info) << "Loaded " << total_entries << " entries from '" << file_path << "'.";
	} catch(const std::exception &e) {
		HLog(error) << "Monster::load: " << e.what();
		return false;
	}

	return true;
}

bool MonsterDatabase::load_internal(const sol::object &key, const sol::object &value)
{
	monster_config_data data;
	
	return true;
}
