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

#ifndef HORIZON_ZONE_GAME_MAP_DEFINITIONS_HPP
#define HORIZON_ZONE_GAME_MAP_DEFINITIONS_HPP

enum map_cell_types : int8_t
{
    CELL_WALKABLE_SHOOTABLE_GROUND_0 = 0,
    CELL_NONWALKABLE_GROUND = 1,
    CELL_WALKABLE_SHOOTABLE_2 = 2,
    CELL_WALKABLE_SHOOTABLE_WATER = 3,
    CELL_WALKABLE_SHOOTABLE_4 = 4,
    CELL_CLIFF_ONLY_SHOOTABLE_5 = 5,
    CELL_WALKABLE_SHOOTABLE_6 = 6,

	CELL_HAS_NPC,
	CELL_BASILICA,
	CELL_LAND_PROTECTOR,
	CELL_NO_VENDING,
	CELL_NO_CHAT,
	CELL_ICE_WALL,
	CELL_NO_ICE_WALL,
};

#endif /* HORIZON_ZONE_GAME_MAP_DEFINITIONS_HPP */