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

#include "Combat.hpp"
#include "Server/Zone/Definitions/ItemDefinitions.hpp"
#include "Server/Zone/Definitions/ClientDefinitions.hpp"
#include "Server/Zone/Game/Entities/Traits/Status.hpp"
#include "Server/Zone/Game/Entities/Player/Assets/Inventory.hpp"
#include "Server/Zone/Game/Entities/Player/Player.hpp"
#include "Server/Zone/Game/Entities/Creature/Hostile/Monster.hpp"
#include "Server/Zone/Game/StaticDB/ItemDB.hpp"
#include "Server/Zone/Session/ZoneSession.hpp"
#include "Server/Zone/Interface/ZoneClientInterface.hpp"

using namespace Horizon::Zone;

Combat::Combat(std::shared_ptr<Entity> entity, std::shared_ptr<Entity> target)
: _entity(entity), _target(target), _start_time(std::time(nullptr))
{
}

Combat::~Combat()
{
}

combat_retaliate_type Combat::weapon_attack()
{
    if (entity()->type() == ENTITY_PLAYER) {
        EquipmentListType const& equipments = entity()->downcast<Horizon::Zone::Entities::Player>()->inventory()->equipments();
        std::shared_ptr<const item_entry_data> weapon = nullptr;

        combat_damage dmg;

        // Calculate element damage ratio and damage.
        int64_t batk = entity()->status()->base_attack()->total();

        if (equipments[IT_EQPI_HAND_R].second.expired() == false) {
            batk = deduce_weapon_element_attack(batk, ELE_NEUTRAL, IT_EQPI_HAND_R);
            batk = deduce_damage_size_modifier(batk, IT_EQPI_HAND_R);
            dmg.right_damage = (batk << 1);
        }

        if (equipments[IT_EQPI_HAND_L].second.expired() == false) {
            batk = deduce_weapon_element_attack(batk, ELE_NEUTRAL, IT_EQPI_HAND_L);
            batk = deduce_damage_size_modifier(batk, IT_EQPI_HAND_L);
            dmg.left_damage = batk;
        }

        entity()->downcast<Horizon::Zone::Entities::Player>()->get_session()->clif()->notify_damage(entity()->guid(), target()->guid(), get_sys_time(), entity()->status()->attack_motion()->total(), entity()->status()->attack_delay()->total(), dmg.right_damage, 0, 1, ZCNA3_DAMAGE, dmg.left_damage);

        target()->status()->current_hp()->sub_base(dmg.right_damage + dmg.left_damage);

        switch (target()->type()) {
        case ENTITY_PLAYER:
            break;
        case ENTITY_NPC:
            break;
        case ENTITY_SKILL:
            break;
        case ENTITY_MONSTER:
            target()->notify_nearby_players_of_movement(true);
            target()->downcast<Horizon::Zone::Entities::Monster>()->on_damage_received(entity(), dmg.right_damage + dmg.left_damage);
            break;
        case ENTITY_PET:
            break;
        case ENTITY_HOMUNCULUS:
            break;
        case ENTITY_MERCENARY:
            break;
        case ENTITY_ELEMENTAL:
            break;
        }
    }

    return CBT_RET_NONE;
}

int64_t Combat::calculate_weapon_attack(int64_t damage)
{
    return damage;
}

int64_t Combat::calculate_magic_attack(int64_t damage)
{
    return damage;
}

int64_t Combat::calculate_misc_attack(int64_t damage)
{
    return damage;
}

int64_t Combat::deduce_weapon_element_attack(int64_t damage, element_type def_ele, item_equip_location_index loc)
{
    if (entity()->type() == ENTITY_PLAYER) {
        EquipmentListType const &equipments = entity()->downcast<Horizon::Zone::Entities::Player>()->inventory()->equipments();
        std::shared_ptr<const item_entry_data> weapon = nullptr;

        if (equipments[loc].second.expired())
            return damage;

        weapon = equipments[loc].second.lock();

        if (loc != IT_EQPI_HAND_R || loc != IT_EQPI_HAND_L)
            return damage; // not a weapon.

        std::shared_ptr<const item_config_data> weapond = ItemDB->get_item_by_id(weapon->item_id);

        if (weapond == nullptr) {
            HLog(warning) << "Combat::deduce_weapon_element_attack: could not find item config of right hand weapon ID: " << weapon->item_id << ". ignoring..." ;
            return damage;
        }

        int32_t attribute_damage_ratio = ItemDB->get_weapon_attribute_modifier(weapond->level.weapon, ELE_NEUTRAL, def_ele);

        damage += (attribute_damage_ratio < 100 ? -(damage * (attribute_damage_ratio - 100) / 100) : (damage * (attribute_damage_ratio - 100) / 100));
    }

    return damage;
}

int64_t Combat::deduce_damage_size_modifier(int64_t damage, item_equip_location_index loc)
{
    if (entity()->type() == ENTITY_PLAYER) {
        EquipmentListType const &equipments = entity()->downcast<Horizon::Zone::Entities::Player>()->inventory()->equipments();
        std::shared_ptr<const item_entry_data> weapon = nullptr;

        if (equipments[loc].second.expired())
            return damage;

        weapon = equipments[loc].second.lock();

        if (loc == IT_EQPI_HAND_R || loc == IT_EQPI_HAND_L) 
            return damage; // not a weapon.

        std::shared_ptr<const item_config_data> weapond = ItemDB->get_item_by_id(weapon->item_id);

        if (weapond == nullptr) {
            HLog(warning) << "Combat::deduce_weapon_element_attack: could not find item config of right hand weapon ID: " << weapon->item_id << ". ignoring..." ;
            return damage;
        }

        int32_t size_damage_ratio = ItemDB->get_weapon_target_size_modifier(weapond->sub_type.weapon_t, (entity_size_type) entity()->status()->size()->get_base());

        damage += (size_damage_ratio < 100 ? -(damage * (size_damage_ratio - 100) / 100) : (damage * (size_damage_ratio - 100) / 100));
    }

    return damage;
}