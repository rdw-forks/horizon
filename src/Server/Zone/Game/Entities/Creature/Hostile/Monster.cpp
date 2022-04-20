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
#include "Server/Zone/Game/Map/Map.hpp"

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

void Monster::initialize()
{
	std::shared_ptr<const monster_config_data> md = _wmd_data.lock();

	Entity::initialize();

	status()->initialize();

	status()->movement_speed()->set_base(md->move_speed);

	map()->ensure_grid_for_entity(this, map_coords());

    map()->container()->getScheduler().Schedule(
    	Milliseconds(MOB_MIN_THINK_TIME_LAZY),
    	get_scheduler_task_id(ENTITY_SCHEDULE_AI_THINK),
    	[this] (TaskContext context)
    {
    	behavior_passive();
    	context.Repeat(Milliseconds(MOB_MIN_THINK_TIME_LAZY));
    });
}

void Monster::behavior_passive()
{
	if (monster_config()->mode & MONSTER_MODE_MASK_CANMOVE 
		&& (next_walk_time() - std::time(nullptr) < 0)
		&& !is_walking()
		&& was_spotted_once()) {
	    try {
	        sol::load_result fx = lua_manager()->lua_state()->load_file("scripts/monsters/functionalities/walking_passive.lua");
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

void Monster::behavior_active()
{

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

