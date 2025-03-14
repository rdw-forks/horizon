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
 *  (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 **************************************************/

#include "Skill.hpp"
#include "Server/Zone/Definitions/UnitDefinitions.hpp"

using namespace Horizon::Zone::Units;

Skill::Skill(uint64_t uuid, std::shared_ptr<Map> map, MapCoords mcoords)
: Unit(uuid, UNIT_SKILL, UNIT_MASK_SKILL, map, mcoords)
{
	//
}

Skill::~Skill()
{
	//
}

void Skill::stop_movement() { }
void Skill::on_pathfinding_failure() { }
void Skill::on_movement_begin(int32_t time) { }
void Skill::on_movement_step() { }
void Skill::on_movement_end() { }