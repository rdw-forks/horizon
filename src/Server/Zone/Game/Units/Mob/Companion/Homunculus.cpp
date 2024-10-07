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

#include "Homunculus.hpp"
#include "Server/Zone/Definitions/UnitDefinitions.hpp"

using namespace Horizon::Zone::Units;

Homunculus::Homunculus(uint64_t uuid, std::shared_ptr<Map> map, MapCoords mcoords)
: Mob(uuid, UNIT_HOMUNCULUS, UNIT_MASK_HOMUNCULUS, map, mcoords)
{
	//
}

Homunculus::~Homunculus()
{
	//
}

void Homunculus::stop_movement() { }
void Homunculus::on_pathfinding_failure() { }
void Homunculus::on_movement_begin(int32_t time) { }
void Homunculus::on_movement_step() { }
void Homunculus::on_movement_end() { }

void Homunculus::on_status_effect_start(std::shared_ptr<status_change_entry> sce) { }
void Homunculus::on_status_effect_end(std::shared_ptr<status_change_entry> sce) { }
void Homunculus::on_status_effect_change(std::shared_ptr<status_change_entry> sce) { }