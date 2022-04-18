/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
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

#ifndef HORIZON_ZONE_MONSTER_LUA_COMPONENT_HPP
#define HORIZON_ZONE_MONSTER_LUA_COMPONENT_HPP

#include "Server/Zone/LUA/Components/LUAComponent.hpp"
#include "Server/Zone/Definitions/MonsterDefinitions.hpp"
#include <sol.hpp>

namespace Horizon
{
namespace Zone
{
class MapContainerThread;
class MonsterComponent : public LUAComponent
{
public:
    MonsterComponent() : LUAComponent() { }
    ~MonsterComponent() { }

    void sync_definitions(std::shared_ptr<sol::state> state);
    void sync_data_types(std::shared_ptr<sol::state> state);
    void sync_functions(std::shared_ptr<sol::state> state) { }
    void sync_functions(std::shared_ptr<sol::state> state, std::shared_ptr<MapContainerThread> container);

    void register_monster_spawn_info(uint32_t id, std::shared_ptr<monster_spawn_data> data) { _monster_spawn_db.insert(id, data); }
    std::shared_ptr<monster_spawn_data> get_monster_spawn_info(uint32_t id) { return _monster_spawn_db.at(id, nullptr); }

    void register_single_spawned_monster(uint32_t guid, std::shared_ptr<Entities::Monster> data) { _monster_spawned_map.insert(guid, data); }
    std::shared_ptr<Entities::Monster> get_single_spawned_monster(uint32_t guid) { return _monster_spawned_map.at(guid, nullptr); }

private: 
    LockedLookupTable<uint32_t, std::shared_ptr<monster_spawn_data>> _monster_spawn_db;
    LockedLookupTable<uint32_t, std::shared_ptr<Entities::Monster>> _monster_spawned_map;
    int32_t _last_monster_spawn_id{0};
};
}
}

#endif /* HORIZON_ZONE_MONSTER_LUA_COMPONENT_HPP */
