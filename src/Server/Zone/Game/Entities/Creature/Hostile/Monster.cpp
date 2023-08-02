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

#include "Monster.hpp"

#include "Core/Logging/Logger.hpp"
#include "Server/Zone/Definitions/EntityDefinitions.hpp"
#include "Server/Zone/Game/Entities/Traits/Status.hpp"
#include "Server/Zone/Game/Entities/Player/Player.hpp"
#include "Server/Zone/Game/Map/Grid/Notifiers/GridNotifiers.hpp"
#include "Server/Zone/Game/Map/Grid/Container/GridReferenceContainer.hpp"
#include "Server/Zone/Game/Map/Grid/Container/GridReferenceContainerVisitor.hpp"
#include "Server/Zone/Game/Map/Map.hpp"
#include "Server/Zone/Zone.hpp"

using namespace Horizon::Zone::Entities;

Monster::Monster(std::shared_ptr<Map> map, MapCoords mcoords,
		std::shared_ptr<const monster_config_data> md,
		std::shared_ptr<std::vector<std::shared_ptr<const monster_skill_config_data>>> mskd)
: Creature(_last_np_entity_guid++, ENTITY_MONSTER, map, mcoords), _wmd_data(md), _wms_data(mskd)
{
	set_name(md->name);
	set_job_id(md->monster_id);
	set_direction(DIR_SOUTH);
}

Monster::~Monster()
{
	if (has_valid_grid_reference())
		remove_grid_reference();
}

bool Monster::initialize()
{
	std::shared_ptr<const monster_config_data> md = _wmd_data.lock();

	if (Creature::initialize(md) == false)
		return false;

	map()->ensure_grid_for_entity(this, map_coords());

    map()->container()->getScheduler().Schedule(
    	Milliseconds(MOB_MIN_THINK_TIME_LAZY),
    	get_scheduler_task_id(ENTITY_SCHEDULE_AI_THINK),
    	[this] (TaskContext context)
    {
    	behavior_passive();
    	context.Repeat(Milliseconds(MOB_MIN_THINK_TIME_LAZY));
    });

	return true;
}

void Monster::finalize()
{
	if (map()->container()->getScheduler().Count(get_scheduler_task_id(ENTITY_SCHEDULE_AI_THINK)))
		map()->container()->getScheduler().CancelGroup(get_scheduler_task_id(ENTITY_SCHEDULE_AI_THINK));

	if (has_valid_grid_reference())
		remove_grid_reference();
}

void Monster::behavior_passive()
{
	if (monster_config()->mode & MONSTER_MODE_MASK_CANMOVE 
		&& (next_walk_time() - std::time(nullptr) < 0)
		&& !is_walking()
		&& was_spotted_once()) {
	    try {
			std::string script_root_path = sZone->config().get_script_root_path().string();
	        sol::load_result fx = map()->container()->get_lua_manager()->lua_state()->load_file(script_root_path + "/monsters/functionalities/walking_passive.lua");
	        sol::protected_function_result result = fx(shared_from_this());
	        if (!result.valid()) {
	            sol::error err = result;
	            HLog(error) << "Monster::behavior_passive: " << err.what();
	        }
	    } catch (sol::error &e) {
	        HLog(error) << "Monster::behavior_passive: " << e.what();
	    }
	}
}

void Monster::behavior_active(std::shared_ptr<Player> pl)
{
	set_spotted(true);

	int can_move = monster_config()->mode & MONSTER_MODE_MASK_CANMOVE;

	if (monster_config()->mode & MONSTER_MODE_MASK_AGGRESSIVE) {
		GridMonsterAIActiveSearchTarget target_search(shared_from_this()->downcast<Monster>());
		GridReferenceContainerVisitor<GridMonsterAIActiveSearchTarget, GridReferenceContainer<AllEntityTypes>> ai_executor_caller(target_search);

		map()->visit_in_range(map_coords(), ai_executor_caller);
	} else if (monster_config()->mode & MONSTER_MODE_MASK_CHANGECHASE) {
		GridMonsterAIChangeChaseTarget target_search(shared_from_this()->downcast<Monster>());
		GridReferenceContainerVisitor<GridMonsterAIChangeChaseTarget, GridReferenceContainer<AllEntityTypes>> ai_executor_caller(target_search);

		map()->visit_in_range(map_coords(), ai_executor_caller);
	}

	// BL_ITEM

	// Attempt to attack
	if (_target != nullptr) {
		HLog(debug) << "Monster " << name() << " is attempting to attack target " << _target->name() << " (guid: ." << _target->guid() << ", distance: " << distance_from(_target) << ", attack_range: " << monster_config()->attack_range << ")";
		attack(_target);
	}
}

void Monster::stop_movement()
{
}

void Monster::on_pathfinding_failure()
{
	HLog(debug) << "Monster " << name() << " has failed to find path from (" << map_coords().x() << "," << map_coords().y() << ") to (" << dest_coords().x() << ", " << dest_coords().y() << ").";
}

void Monster::on_movement_begin()
{

}

void Monster::on_movement_step()
{
	map()->ensure_grid_for_entity(this, map_coords());
}

void Monster::on_movement_end()
{
}

void Monster::on_status_effect_start(std::shared_ptr<status_change_entry> sce)
{

}

void Monster::on_status_effect_end(std::shared_ptr<status_change_entry> sce)
{

}

void Monster::on_status_effect_change(std::shared_ptr<status_change_entry> sce)
{

}

void Monster::on_damage_received(std::shared_ptr<Entity> damage_dealer, int damage)
{
	if (status()->current_hp()->total() < damage) {
		status()->current_hp()->set_base(0);
		on_killed(damage_dealer);
		return;
	}
}

bool Monster::on_killed(std::shared_ptr<Entity> killer, bool with_drops, bool with_exp)
{
	std::shared_ptr<const monster_config_data> md = _wmd_data.lock();

	if (md == nullptr)
		return false;

	notify_nearby_players_of_existence(EVP_NOTIFY_DEAD);

	map()->container()->get_lua_manager()->monster()->deregister_single_spawned_monster(guid());

	switch (killer->type())
	{
	case ENTITY_PLAYER:
	{
		std::shared_ptr<Player> player = killer->downcast<Player>();

		try {
			std::string script_root_path = sZone->config().get_script_root_path().string();
			sol::load_result fx = player->lua_state()->load_file(script_root_path + "internal/on_monster_killed.lua");
			sol::protected_function_result result = fx(player, shared_from_this()->downcast<Monster>(), with_drops, with_exp);
			if (!result.valid()) {
				sol::error err = result;
				HLog(error) << "Monster::on_killed: " << err.what();
				return false;
			}
		}
		catch (sol::error& e) {
			HLog(error) << "Monster::on_killed: " << e.what();
			return false;
		}
	}
		break;
	default:
		HLog(warning) << "Monster::on_killed: Unknown entity type killed monster " << guid() << " at " << map()->get_name() << " (" << map_coords().x() << ", " << map_coords().y() << ").";
		break;
	}

	return true;
}