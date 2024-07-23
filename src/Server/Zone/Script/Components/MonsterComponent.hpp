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

#include "Server/Zone/Script/Components/LUAComponent.hpp"
#include "Server/Zone/Definitions/MonsterDefinitions.hpp"

#include <map>

namespace Horizon
{
namespace Zone
{
class Map;
class MapContainerThread;
class MonsterComponent : public LUAComponent
{
public:
    MonsterComponent() { }
    MonsterComponent(std::shared_ptr<MapContainerThread> container) 
    : LUAComponent(container) { }
    ~MonsterComponent() { }

    void sync_definitions(std::shared_ptr<sol::state> state);
    void sync_data_types(std::shared_ptr<sol::state> state);
    void sync_functions(std::shared_ptr<sol::state> state) { }
    void sync_functions(std::shared_ptr<sol::state> state, std::shared_ptr<MapContainerThread> container);

    void register_monster_spawn_info(uint32_t id, std::shared_ptr<monster_spawn_data> data) { _monster_spawn_db.emplace(id, data); }
    std::shared_ptr<monster_spawn_data> get_monster_spawn_info(uint32_t id) { return _monster_spawn_db.at(id); }

    void reschedule_single_monster_spawn(std::shared_ptr<Horizon::Zone::Units::Monster> monster);
    
    void register_single_spawned_monster(uint64_t guid, std::shared_ptr<Units::Monster> data) { _monster_spawned_map.emplace(guid, data); }
    std::shared_ptr<Units::Monster> get_single_spawned_monster(uint64_t guid) { return _monster_spawned_map.at(guid); }
    void deregister_single_spawned_monster(uint64_t guid);

    void spawn_monsters(std::string map_name, std::shared_ptr<MapContainerThread> container);
    void spawn_monster(std::shared_ptr<Map> map, int spawn_dataset_id, int monster_id, int16_t amount, int16_t x, int16_t y, int16_t x_area, int16_t y_area);
    void despawn_monsters(std::string map_name, std::shared_ptr<MapContainerThread> container);

    std::map<uint32_t, std::shared_ptr<monster_spawn_data>> _monster_spawn_db;
    std::map<uint64_t, std::shared_ptr<Units::Monster>> _monster_spawned_map;
    
    int32_t _last_monster_spawn_id{0};
};
}
}

#endif /* HORIZON_ZONE_MONSTER_LUA_COMPONENT_HPP */
