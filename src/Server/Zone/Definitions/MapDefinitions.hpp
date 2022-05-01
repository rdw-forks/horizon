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