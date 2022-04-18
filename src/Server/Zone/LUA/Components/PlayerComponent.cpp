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
#include "Server/Zone/Game/Entities/Player/Assets/Inventory.hpp"
#include "Server/Zone/Game/Entities/Traits/Status.hpp"
#include "Server/Zone/Game/Entities/Traits/AttributesImpl.hpp"
#include "Server/Zone/Session/ZoneSession.hpp"

using namespace Horizon::Zone;
using namespace Horizon::Zone::Entities;

void PlayerComponent::sync_definitions(std::shared_ptr<sol::state> state)
{
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
		"perform_action", &Player::perform_action
	);

	state->new_usertype<Entities::Traits::Status>("Status",
		"strength", &Entities::Traits::Status::strength,
		"agility", &Entities::Traits::Status::agility,
		"vitality", &Entities::Traits::Status::vitality,
		"dexterity", &Entities::Traits::Status::dexterity,
		"intelligence", &Entities::Traits::Status::intelligence,
		"luck", &Entities::Traits::Status::luck,
		"max_hp", &Entities::Traits::Status::max_hp,
		"max_sp", &Entities::Traits::Status::max_sp,
		"current_hp", &Entities::Traits::Status::current_hp,
		"current_sp", &Entities::Traits::Status::current_sp,
		"base_level", &Entities::Traits::Status::base_level,
		"job_level", &Entities::Traits::Status::job_level,
		"base_experience", &Entities::Traits::Status::base_experience,
		"job_experience", &Entities::Traits::Status::job_experience,
		"next_base_experience", &Entities::Traits::Status::next_base_experience,
		"next_job_experience", &Entities::Traits::Status::next_job_experience,
		"movement_speed", &Entities::Traits::Status::movement_speed,
		"max_weight", &Entities::Traits::Status::max_weight,
		"current_weight", &Entities::Traits::Status::current_weight,
		"hair_color", &Entities::Traits::Status::hair_color,
		"cloth_color", &Entities::Traits::Status::cloth_color,
		"weapon_sprite", &Entities::Traits::Status::weapon_sprite,
		"shield_sprite", &Entities::Traits::Status::shield_sprite,
		"robe_sprite", &Entities::Traits::Status::robe_sprite,
		"head_top_sprite", &Entities::Traits::Status::head_top_sprite,
		"head_mid_sprite", &Entities::Traits::Status::head_mid_sprite,
		"head_bottom_sprite", &Entities::Traits::Status::head_bottom_sprite,
		"hair_style", &Entities::Traits::Status::hair_style,
		"body_style", &Entities::Traits::Status::body_style,
		"status_point", &Entities::Traits::Status::status_point,
		"skill_point", &Entities::Traits::Status::skill_point
	);

	state->new_usertype<Entities::Traits::BaseLevel>("BaseLevel",
		"add", &Entities::Traits::BaseLevel::add_base,
		"sub", &Entities::Traits::BaseLevel::sub_base,
		"get", &Entities::Traits::BaseLevel::get_base,
		"set", &Entities::Traits::BaseLevel::set_base
	);
	state->new_usertype<Entities::Traits::JobLevel>("JobLevel",
		"add", &Entities::Traits::JobLevel::add_base,
		"sub", &Entities::Traits::JobLevel::sub_base,
		"get", &Entities::Traits::JobLevel::get_base,
		"set", &Entities::Traits::JobLevel::set_base
	);
	state->new_usertype<Entities::Traits::MaxHP>("MaxHP",
		"add", &Entities::Traits::MaxHP::add_base,
		"sub", &Entities::Traits::MaxHP::sub_base,
		"get", &Entities::Traits::MaxHP::get_base,
		"set", &Entities::Traits::MaxHP::set_base
	);
	state->new_usertype<Entities::Traits::MaxSP>("MaxSP",
		"add", &Entities::Traits::MaxSP::add_base,
		"sub", &Entities::Traits::MaxSP::sub_base,
		"get", &Entities::Traits::MaxSP::get_base,
		"set", &Entities::Traits::MaxSP::set_base
	);
	state->new_usertype<Entities::Traits::CurrentHP>("CurrentHP",
		"add", &Entities::Traits::CurrentHP::add_base,
		"sub", &Entities::Traits::CurrentHP::sub_base,
		"get", &Entities::Traits::CurrentHP::get_base,
		"set", &Entities::Traits::CurrentHP::set_base
	);
	state->new_usertype<Entities::Traits::CurrentSP>("CurrentSP",
		"add", &Entities::Traits::CurrentSP::add_base,
		"sub", &Entities::Traits::CurrentSP::sub_base,
		"get", &Entities::Traits::CurrentSP::get_base,
		"set", &Entities::Traits::CurrentSP::set_base
	);
	state->new_usertype<Entities::Traits::MovementSpeed>("MovementSpeed",
		"add", &Entities::Traits::MovementSpeed::add_base,
		"sub", &Entities::Traits::MovementSpeed::sub_base,
		"get", &Entities::Traits::MovementSpeed::get_base,
		"set", &Entities::Traits::MovementSpeed::set_base
	);
	state->new_usertype<Entities::Traits::MaxWeight>("MaxWeight",
		"add", &Entities::Traits::MaxWeight::add_base,
		"sub", &Entities::Traits::MaxWeight::sub_base,
		"get", &Entities::Traits::MaxWeight::get_base,
		"set", &Entities::Traits::MaxWeight::set_base
	);
	state->new_usertype<Entities::Traits::CurrentWeight>("CurrentWeight",
		"add", &Entities::Traits::CurrentWeight::add_base,
		"sub", &Entities::Traits::CurrentWeight::sub_base,
		"get", &Entities::Traits::CurrentWeight::get_base,
		"set", &Entities::Traits::CurrentWeight::set_base
	);
	state->new_usertype<Entities::Traits::Strength>("Strength",
		"add", &Entities::Traits::Strength::add_base,
		"sub", &Entities::Traits::Strength::sub_base,
		"get", &Entities::Traits::Strength::get_base,
		"set", &Entities::Traits::Strength::set_base
	);
	state->new_usertype<Entities::Traits::Agility>("Agility",
		"add", &Entities::Traits::Agility::add_base,
		"sub", &Entities::Traits::Agility::sub_base,
		"get", &Entities::Traits::Agility::get_base,
		"set", &Entities::Traits::Agility::set_base
	);
	state->new_usertype<Entities::Traits::Vitality>("Vitality",
		"add", &Entities::Traits::Vitality::add_base,
		"sub", &Entities::Traits::Vitality::sub_base,
		"get", &Entities::Traits::Vitality::get_base,
		"set", &Entities::Traits::Vitality::set_base
	);
	state->new_usertype<Entities::Traits::Intelligence>("Intelligence",
		"add", &Entities::Traits::Intelligence::add_base,
		"sub", &Entities::Traits::Intelligence::sub_base,
		"get", &Entities::Traits::Intelligence::get_base,
		"set", &Entities::Traits::Intelligence::set_base
	);
	state->new_usertype<Entities::Traits::Dexterity>("Dexterity",
		"add", &Entities::Traits::Dexterity::add_base,
		"sub", &Entities::Traits::Dexterity::sub_base,
		"get", &Entities::Traits::Dexterity::get_base,
		"set", &Entities::Traits::Dexterity::set_base
	);
	state->new_usertype<Entities::Traits::Luck>("Luck",
		"add", &Entities::Traits::Luck::add_base,
		"sub", &Entities::Traits::Luck::sub_base,
		"get", &Entities::Traits::Luck::get_base,
		"set", &Entities::Traits::Luck::set_base
	);
	state->new_usertype<Entities::Traits::BaseExperience>("BaseExperience",
		"add", &Entities::Traits::BaseExperience::add_base,
		"sub", &Entities::Traits::BaseExperience::sub_base,
		"get", &Entities::Traits::BaseExperience::get_base,
		"set", &Entities::Traits::BaseExperience::set_base
	);
	state->new_usertype<Entities::Traits::JobExperience>("JobExperience",
		"add", &Entities::Traits::JobExperience::add_base,
		"sub", &Entities::Traits::JobExperience::sub_base,
		"get", &Entities::Traits::JobExperience::get_base,
		"set", &Entities::Traits::JobExperience::set_base
	);
	state->new_usertype<Entities::Traits::NextBaseExperience>("NextBaseExperience",
		"add", &Entities::Traits::NextBaseExperience::add_base,
		"sub", &Entities::Traits::NextBaseExperience::sub_base,
		"get", &Entities::Traits::NextBaseExperience::get_base,
		"set", &Entities::Traits::NextBaseExperience::set_base
	);
	state->new_usertype<Entities::Traits::NextJobExperience>("NextJobExperience",
		"add", &Entities::Traits::NextJobExperience::add_base,
		"sub", &Entities::Traits::NextJobExperience::sub_base,
		"get", &Entities::Traits::NextJobExperience::get_base,
		"set", &Entities::Traits::NextJobExperience::set_base
	);
	state->new_usertype<Entities::Traits::StatusPoint>("StatusPoint",
		"add", &Entities::Traits::StatusPoint::add_base,
		"sub", &Entities::Traits::StatusPoint::sub_base,
		"get", &Entities::Traits::StatusPoint::get_base,
		"set", &Entities::Traits::StatusPoint::set_base
	);
	state->new_usertype<Entities::Traits::SkillPoint>("SkillPoint",
		"add", &Entities::Traits::SkillPoint::add_base,
		"sub", &Entities::Traits::SkillPoint::sub_base,
		"get", &Entities::Traits::SkillPoint::get_base,
		"set", &Entities::Traits::SkillPoint::set_base
	);

}

void PlayerComponent::sync_functions(std::shared_ptr<sol::state> state)
{
}