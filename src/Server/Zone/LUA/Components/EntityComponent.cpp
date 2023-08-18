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

#include "EntityComponent.hpp"

#include "Server/Common/Configuration/Horizon.hpp"
#include "Server/Zone/Game/Entities/Player/Player.hpp"
#include "Server/Zone/Game/Entities/Traits/Status.hpp"

#include "EntityDefinitions.hpp"

using namespace Horizon::Zone;

void EntityComponent::sync_definitions(std::shared_ptr<sol::state> state)
{
	state->create_named_table("EntitySize",
		"Small", (int) ESZ_SMALL,
		"Medium", (int) ESZ_MEDIUM,
		"Large", (int) ESZ_LARGE,
		"Max", (int) ESZ_MAX
	);

	state->create_named_table("Element",
		"Neutral", (int) ELE_NEUTRAL,
		"Water", (int) ELE_WATER,
		"Earth", (int) ELE_EARTH,
		"Fire", (int) ELE_FIRE,
		"Wind", (int) ELE_WIND,
		"Poison", (int) ELE_POISON,
		"Holy", (int) ELE_HOLY,
		"Dark", (int) ELE_DARK,
		"Ghost", (int) ELE_GHOST,
		"Undead", (int) ELE_UNDEAD,
		"Max", (int) ELE_MAX,
		"Weapon", (int) ELE_WEAPON,
		"Endowed", (int) ELE_ENDOWED,
		"Random", (int) ELE_RANDOM
	);

	state->create_named_table("EntityType",
		"Player", (int) ENTITY_MASK_PLAYER,
		"NPC", (int) ENTITY_MASK_NPC,
		"Item", (int) ENTITY_MASK_ITEM,
		"Skill", (int) ENTITY_MASK_SKILL,
		"Monster", (int) ENTITY_MASK_MONSTER,
		"Event", (int) ENTITY_MASK_EVENT,
		"Pet", (int) ENTITY_MASK_PET,
		"Homunculus", (int) ENTITY_MASK_HOMNUCLUS,
		"Mercenary", (int) ENTITY_MASK_MERCNARY,
		"Elemental", (int) ENTITY_MASK_ELEMENTAL
	);

	state->create_named_table("Directions",
		"North", (int) DIR_NORTH,
		"NorthWest", (int) DIR_NORTH_WEST,
		"West", (int) DIR_WEST,
		"SouthWest", (int) DIR_SOUTH_WEST,
		"South", (int) DIR_SOUTH,
		"SouthEast", (int) DIR_SOUTH_EAST,
		"East", (int) DIR_EAST,
		"NorthEast", (int) DIR_NORTH_EAST
	);


	state->create_named_table("Posture",
		"Standing", (int) POSTURE_STANDING,
		"Dead", (int) POSTURE_DEAD,
		"Sitting", (int) POSTURE_SITTING
	);
}

void EntityComponent::sync_data_types(std::shared_ptr<sol::state> state)
{
    state->new_usertype<Horizon::Zone::Traits::Status>("Status",
        "strength", &Horizon::Zone::Traits::Status::strength,
        "agility", &Horizon::Zone::Traits::Status::agility,
        "vitality", &Horizon::Zone::Traits::Status::vitality,
        "dexterity", &Horizon::Zone::Traits::Status::dexterity,
        "intelligence", &Horizon::Zone::Traits::Status::intelligence,
        "luck", &Horizon::Zone::Traits::Status::luck,
        "max_hp", &Horizon::Zone::Traits::Status::max_hp,
        "max_sp", &Horizon::Zone::Traits::Status::max_sp,
        "current_hp", &Horizon::Zone::Traits::Status::current_hp,
        "current_sp", &Horizon::Zone::Traits::Status::current_sp,
        "base_level", &Horizon::Zone::Traits::Status::base_level,
        "job_level", &Horizon::Zone::Traits::Status::job_level,
        "base_experience", &Horizon::Zone::Traits::Status::base_experience,
        "job_experience", &Horizon::Zone::Traits::Status::job_experience,
        "next_base_experience", &Horizon::Zone::Traits::Status::next_base_experience,
        "next_job_experience", &Horizon::Zone::Traits::Status::next_job_experience,
        "movement_speed", &Horizon::Zone::Traits::Status::movement_speed,
        "max_weight", &Horizon::Zone::Traits::Status::max_weight,
        "current_weight", &Horizon::Zone::Traits::Status::current_weight,
        "hair_color", &Horizon::Zone::Traits::Status::hair_color,
        "cloth_color", &Horizon::Zone::Traits::Status::cloth_color,
        "weapon_sprite", &Horizon::Zone::Traits::Status::weapon_sprite,
        "shield_sprite", &Horizon::Zone::Traits::Status::shield_sprite,
        "robe_sprite", &Horizon::Zone::Traits::Status::robe_sprite,
        "head_top_sprite", &Horizon::Zone::Traits::Status::head_top_sprite,
        "head_mid_sprite", &Horizon::Zone::Traits::Status::head_mid_sprite,
        "head_bottom_sprite", &Horizon::Zone::Traits::Status::head_bottom_sprite,
        "hair_style", &Horizon::Zone::Traits::Status::hair_style,
        "body_style", &Horizon::Zone::Traits::Status::body_style,
        "status_point", &Horizon::Zone::Traits::Status::status_point,
        "skill_point", &Horizon::Zone::Traits::Status::skill_point
    );

    state->new_usertype<Horizon::Zone::Traits::BaseLevel>("BaseLevel",
        "add", &Horizon::Zone::Traits::BaseLevel::add_base,
        "sub", &Horizon::Zone::Traits::BaseLevel::sub_base,
        "get", &Horizon::Zone::Traits::BaseLevel::get_base,
        "set", &Horizon::Zone::Traits::BaseLevel::set_base
    );
    state->new_usertype<Horizon::Zone::Traits::JobLevel>("JobLevel",
        "add", &Horizon::Zone::Traits::JobLevel::add_base,
        "sub", &Horizon::Zone::Traits::JobLevel::sub_base,
        "get", &Horizon::Zone::Traits::JobLevel::get_base,
        "set", &Horizon::Zone::Traits::JobLevel::set_base
    );
    state->new_usertype<Horizon::Zone::Traits::MaxHP>("MaxHP",
        "add", &Horizon::Zone::Traits::MaxHP::add_base,
        "sub", &Horizon::Zone::Traits::MaxHP::sub_base,
        "get", &Horizon::Zone::Traits::MaxHP::get_base,
        "set", &Horizon::Zone::Traits::MaxHP::set_base
    );
    state->new_usertype<Horizon::Zone::Traits::MaxSP>("MaxSP",
        "add", &Horizon::Zone::Traits::MaxSP::add_base,
        "sub", &Horizon::Zone::Traits::MaxSP::sub_base,
        "get", &Horizon::Zone::Traits::MaxSP::get_base,
        "set", &Horizon::Zone::Traits::MaxSP::set_base
    );
    state->new_usertype<Horizon::Zone::Traits::CurrentHP>("CurrentHP",
        "add", &Horizon::Zone::Traits::CurrentHP::add_base,
        "sub", &Horizon::Zone::Traits::CurrentHP::sub_base,
        "get", &Horizon::Zone::Traits::CurrentHP::get_base,
        "set", &Horizon::Zone::Traits::CurrentHP::set_base
    );
    state->new_usertype<Horizon::Zone::Traits::CurrentSP>("CurrentSP",
        "add", &Horizon::Zone::Traits::CurrentSP::add_base,
        "sub", &Horizon::Zone::Traits::CurrentSP::sub_base,
        "get", &Horizon::Zone::Traits::CurrentSP::get_base,
        "set", &Horizon::Zone::Traits::CurrentSP::set_base
    );
    state->new_usertype<Horizon::Zone::Traits::MovementSpeed>("MovementSpeed",
        "add", &Horizon::Zone::Traits::MovementSpeed::add_base,
        "sub", &Horizon::Zone::Traits::MovementSpeed::sub_base,
        "get", &Horizon::Zone::Traits::MovementSpeed::get_base,
        "set", &Horizon::Zone::Traits::MovementSpeed::set_base
    );
    state->new_usertype<Horizon::Zone::Traits::MaxWeight>("MaxWeight",
        "add", &Horizon::Zone::Traits::MaxWeight::add_base,
        "sub", &Horizon::Zone::Traits::MaxWeight::sub_base,
        "get", &Horizon::Zone::Traits::MaxWeight::get_base,
        "set", &Horizon::Zone::Traits::MaxWeight::set_base
    );
    state->new_usertype<Horizon::Zone::Traits::CurrentWeight>("CurrentWeight",
        "add", &Horizon::Zone::Traits::CurrentWeight::add_base,
        "sub", &Horizon::Zone::Traits::CurrentWeight::sub_base,
        "get", &Horizon::Zone::Traits::CurrentWeight::get_base,
        "set", &Horizon::Zone::Traits::CurrentWeight::set_base
    );
    state->new_usertype<Horizon::Zone::Traits::Strength>("Strength",
        "add", &Horizon::Zone::Traits::Strength::add_base,
        "sub", &Horizon::Zone::Traits::Strength::sub_base,
        "get", &Horizon::Zone::Traits::Strength::get_base,
        "set", &Horizon::Zone::Traits::Strength::set_base
    );
    state->new_usertype<Horizon::Zone::Traits::Agility>("Agility",
        "add", &Horizon::Zone::Traits::Agility::add_base,
        "sub", &Horizon::Zone::Traits::Agility::sub_base,
        "get", &Horizon::Zone::Traits::Agility::get_base,
        "set", &Horizon::Zone::Traits::Agility::set_base
    );
    state->new_usertype<Horizon::Zone::Traits::Vitality>("Vitality",
        "add", &Horizon::Zone::Traits::Vitality::add_base,
        "sub", &Horizon::Zone::Traits::Vitality::sub_base,
        "get", &Horizon::Zone::Traits::Vitality::get_base,
        "set", &Horizon::Zone::Traits::Vitality::set_base
    );
    state->new_usertype<Horizon::Zone::Traits::Intelligence>("Intelligence",
        "add", &Horizon::Zone::Traits::Intelligence::add_base,
        "sub", &Horizon::Zone::Traits::Intelligence::sub_base,
        "get", &Horizon::Zone::Traits::Intelligence::get_base,
        "set", &Horizon::Zone::Traits::Intelligence::set_base
    );
    state->new_usertype<Horizon::Zone::Traits::Dexterity>("Dexterity",
        "add", &Horizon::Zone::Traits::Dexterity::add_base,
        "sub", &Horizon::Zone::Traits::Dexterity::sub_base,
        "get", &Horizon::Zone::Traits::Dexterity::get_base,
        "set", &Horizon::Zone::Traits::Dexterity::set_base
    );
    state->new_usertype<Horizon::Zone::Traits::Luck>("Luck",
        "add", &Horizon::Zone::Traits::Luck::add_base,
        "sub", &Horizon::Zone::Traits::Luck::sub_base,
        "get", &Horizon::Zone::Traits::Luck::get_base,
        "set", &Horizon::Zone::Traits::Luck::set_base
    );
    state->new_usertype<Horizon::Zone::Traits::BaseExperience>("BaseExperience",
        "add", &Horizon::Zone::Traits::BaseExperience::add_base,
        "sub", &Horizon::Zone::Traits::BaseExperience::sub_base,
        "get", &Horizon::Zone::Traits::BaseExperience::get_base,
        "set", &Horizon::Zone::Traits::BaseExperience::set_base
    );
    state->new_usertype<Horizon::Zone::Traits::JobExperience>("JobExperience",
        "add", &Horizon::Zone::Traits::JobExperience::add_base,
        "sub", &Horizon::Zone::Traits::JobExperience::sub_base,
        "get", &Horizon::Zone::Traits::JobExperience::get_base,
        "set", &Horizon::Zone::Traits::JobExperience::set_base
    );
    state->new_usertype<Horizon::Zone::Traits::NextBaseExperience>("NextBaseExperience",
        "add", &Horizon::Zone::Traits::NextBaseExperience::add_base,
        "sub", &Horizon::Zone::Traits::NextBaseExperience::sub_base,
        "get", &Horizon::Zone::Traits::NextBaseExperience::get_base,
        "set", &Horizon::Zone::Traits::NextBaseExperience::set_base
    );
    state->new_usertype<Horizon::Zone::Traits::NextJobExperience>("NextJobExperience",
        "add", &Horizon::Zone::Traits::NextJobExperience::add_base,
        "sub", &Horizon::Zone::Traits::NextJobExperience::sub_base,
        "get", &Horizon::Zone::Traits::NextJobExperience::get_base,
        "set", &Horizon::Zone::Traits::NextJobExperience::set_base
    );
    state->new_usertype<Horizon::Zone::Traits::StatusPoint>("StatusPoint",
        "add", &Horizon::Zone::Traits::StatusPoint::add_base,
        "sub", &Horizon::Zone::Traits::StatusPoint::sub_base,
        "get", &Horizon::Zone::Traits::StatusPoint::get_base,
        "set", &Horizon::Zone::Traits::StatusPoint::set_base
    );
    state->new_usertype<Horizon::Zone::Traits::SkillPoint>("SkillPoint",
        "add", &Horizon::Zone::Traits::SkillPoint::add_base,
        "sub", &Horizon::Zone::Traits::SkillPoint::sub_base,
        "get", &Horizon::Zone::Traits::SkillPoint::get_base,
        "set", &Horizon::Zone::Traits::SkillPoint::set_base
    );
	state->new_usertype<Entity>("Entity",
		"dest_coords", &Entity::dest_coords,
		"walk_to_coordinates", &Entity::walk_to_coordinates,
		"is_walking", &Entity::is_walking,
		"stop_movement", &Entity::stop_movement,
		"guid", &Entity::guid,
		"job_id", &Entity::job_id,
		"posture", &Entity::posture,
		"set_posture", &Entity::set_posture,
		"name", &Entity::name,
		"direction", &Entity::direction,
		"status", &Entity::status,
		"force_movement_stop_internal", &Entity::force_movement_stop_internal,
		"map", &Entity::map,
		"type", &Entity::type,
		"map_coords", &Entity::map_coords,
		"grid_coords", &Entity::grid_coords,
		"is_in_range_of", &Entity::is_in_range_of,
		"notify_nearby_players_of_existence", &Entity::notify_nearby_players_of_existence,
		"notify_nearby_players_of_movement", &Entity::notify_nearby_players_of_movement,
		"notify_nearby_players_of_spawn", &Entity::notify_nearby_players_of_spawn,
		"get_nearby_entity", &Entity::get_nearby_entity,
		"status_effect_start", &Entity::status_effect_start,
		"status_effect_end", &Entity::status_effect_end,
		"get_walk_path", &Entity::get_walk_path
	);
}

void EntityComponent::sync_functions(std::shared_ptr<sol::state> state)
{
}