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
 * This is proprietary software. Unauthorized copying,
 * distribution, or modification of this file, via any
 * medium, is strictly prohibited. All rights reserved.
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