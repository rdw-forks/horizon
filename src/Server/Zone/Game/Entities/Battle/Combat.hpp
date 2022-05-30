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

#ifndef HORIZON_ZONE_GAME_ENTITIES_BATTLE_COMBAT_HPP
#define HORIZON_ZONE_GAME_ENTITIES_BATTLE_COMBAT_HPP

#include "Server/Zone/Definitions/CombatDefinitions.hpp"
#include "Server/Zone/Game/Entities/Entity.hpp"

namespace Horizon
{
namespace Zone
{
class Combat
{
public:
    explicit Combat(std::shared_ptr<Entity> entity, std::shared_ptr<Entity> target);
    ~Combat();

    std::shared_ptr<Entity> entity() const { return _entity.lock(); }
    std::shared_ptr<Entity> target() const { return _target.lock(); }

    combat_retaliate_type weapon_attack();
    int64_t calculate_weapon_attack(int64_t damage);
    int64_t calculate_magic_attack(int64_t damage);
    int64_t calculate_misc_attack(int64_t damage);
    int64_t deduce_weapon_element_attack(int64_t damage, element_type def_ele, item_equip_location_index loc);
    int64_t deduce_damage_size_modifier(int64_t damage, item_equip_location_index loc);

private:
    time_t _start_time{0};
    std::weak_ptr<Entity> _entity, _target;
};
}
}

#endif /* HORIZON_ZONE_GAME_ENTITIES_BATTLE_COMBAT_HPP */
