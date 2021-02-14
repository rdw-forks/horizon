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

#ifndef HORIZON_ZONE_GAME_MONSTERDB_HPP
#define HORIZON_ZONE_GAME_MONSTERDB_HPP

#include <cstdlib>

#include <sol.hpp>

namespace Horizon
{
namespace Zone
{
struct monster_config_data
{
	int _monster_id;
};
class MonsterDatabase
{
public:
	MonsterDatabase();
	~MonsterDatabase();
	
	static MonsterDatabase *get_instance()
	{
		static MonsterDatabase instance;
		return &instance;
	}
	
	bool load();

protected:
	bool load_internal(sol::object const &key, sol::object const &value);

private:
	LockedLookupTable<uint32_t, std::shared_ptr<monster_config_data>> _monster_db;
};
}
}

#define MonsterDB Horizon::Zone::MonsterDatabase::get_instance()

#endif /* HORIZON_ZONE_GAME_MONSTERDB_HPP */
