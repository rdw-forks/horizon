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

#include "PlayerComponent.hpp"

#include "Server/Common/Configuration/Horizon.hpp"
#include "Server/Zone/Game/Entities/Player/Player.hpp"
#include "Server/Zone/Game/Entities/Player/Definitions/PlayerDefinitions.hpp"
#include "Server/Zone/Game/Entities/Player/Assets/Inventory.hpp"
#include "Server/Zone/Game/Entities/Traits/Status.hpp"
#include "Server/Zone/Session/ZoneSession.hpp"

using namespace Horizon::Zone;
using namespace Horizon::Zone::Entities;

void PlayerComponent::sync_definitions(std::shared_ptr<sol::state> state)
{
    state->create_named_table("PlayerActionType",
        "Attack", PLAYER_ACT_ATTACK,
        "ItemPickup", PLAYER_ACT_ITEM_PICKUP,
        "Sit", PLAYER_ACT_SIT,
        "Stand", PLAYER_ACT_STAND,
        "AttackNoMotion", PLAYER_ACT_ATTACK_NOMOTION,
        "Splash", PLAYER_ACT_SPLASH,
        "Skill", PLAYER_ACT_SKILL,
        "AttackRepeat", PLAYER_ACT_ATTACK_REPEAT,
        "AttackMultiple", PLAYER_ACT_ATTACK_MULTIPLE,
        "AttackMultipleNoMotion", PLAYER_ACT_ATTACK_MULTIPLE_NOMOTION,
        "AttackCritical", PLAYER_ACT_ATTACK_CRITICAL,
        "AttackLucky", PLAYER_ACT_ATTACK_LUCKY,
        "TouchSkill", PLAYER_ACT_TOUCHSKILL
    );
}

void PlayerComponent::sync_data_types(std::shared_ptr<sol::state> state)
{   
    state->new_usertype<Assets::Inventory>("Inventory",
        "add_item", &Assets::Inventory::add_item
    );

    state->new_usertype<Player>("Player",
        "guid", &Player::guid,
        "map", &Player::map,
        "map_coords", &Player::map_coords,
        "get_nearby_entity", &Player::get_nearby_entity,
        "send_npc_dialog", &Player::send_npc_dialog,
        "send_npc_next_dialog", &Player::send_npc_next_dialog,
        "send_npc_close_dialog", &Player::send_npc_close_dialog,
        "send_npc_menu_list", &Player::send_npc_menu_list,
        "move_to_map", &Player::move_to_map,
        "inventory", &Player::inventory,
        "message", [] (std::shared_ptr<Player> player, std::string const &message)
        {
            player->get_session()->clif()->notify_chat(message);
        },
        "status", &Player::status,
        "job_change", &Player::job_change,
        "perform_action", &Player::perform_action,
        "get_learnt_skill", &Player::get_learnt_skill
    );

}

void PlayerComponent::sync_functions(std::shared_ptr<sol::state> state)
{
    state->set_function("cast_entity_to_player",
                    [] (std::shared_ptr<Entity> e)
                    {
                        return e->template downcast<Player>();
                    });
}

void PlayerComponent::perform_command_from_player(std::shared_ptr<Player> player, std::string const &cmd)
{
    try {
        sol::load_result fx = player->lua_state()->load_file("scripts/internal/at_command_main.lua");
        sol::protected_function_result result = fx(player, cmd);
        if (!result.valid()) {
            sol::error err = result;
            HLog(error) << "PlayerComponent::perform_command_from_player: " << err.what();
        }
    } catch (sol::error &e) {
        HLog(error) << "PlayerComponent::perform_command_from_player: " << e.what();
    }
}
