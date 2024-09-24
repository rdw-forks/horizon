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

#ifndef HORIZON_ZONE_GAME_CELL_HPP
#define HORIZON_ZONE_GAME_CELL_HPP

#include "Utility/Utility.hpp"
#include "Server/Zone/Definitions/MapDefinitions.hpp"

namespace Horizon
{
namespace Zone
{
#pragma pack(push, 1)
struct Cell
{
public:
    Cell(uint8_t type)
    : _type((map_cell_types) type)
    {
		validate_type(_type);
    }

	Cell()
	{

	}

    ~Cell()
    {
        //
    }

	void set_type(uint8_t type) { _type = (map_cell_types) type; validate_type(_type); }
	map_cell_types get_type() { return _type; }

	void validate_type(map_cell_types type)
	{
		switch (type)
		{
			case CELL_WALKABLE_SHOOTABLE_WATER: setWater(); // walkable water
			case CELL_WALKABLE_SHOOTABLE_GROUND_0: // ground
			case CELL_WALKABLE_SHOOTABLE_2: // ???
			case CELL_WALKABLE_SHOOTABLE_4: // ???
			case CELL_WALKABLE_SHOOTABLE_6: setWalkable(); // ???
			case CELL_CLIFF_ONLY_SHOOTABLE_5: setShootable(); // gap (snipable)
			case CELL_NONWALKABLE_GROUND: break;

//			case 0: cell.walkable = 1; cell.shootable = 1; cell.water = 0; break; // walkable ground
//			case 1: cell.walkable = 0; cell.shootable = 0; cell.water = 0; break; // non-walkable ground
//			case 2: cell.walkable = 1; cell.shootable = 1; cell.water = 0; break; // ???
//			case 3: cell.walkable = 1; cell.shootable = 1; cell.water = 1; break; // walkable water
//			case 4: cell.walkable = 1; cell.shootable = 1; cell.water = 0; break; // ???
//			case 5: cell.walkable = 0; cell.shootable = 1; cell.water = 0; break; // gap (snipable)
//			case 6: cell.walkable = 1; cell.shootable = 1; cell.water = 0; break; // ???
			default:
				break;
		}
	}

	bool isWalkable() { return setting._walkable ? true : false; }
	void setWalkable() { setting._walkable = 1; }

	bool isShootable() { return setting._shootable ? true : false; }
	void setShootable() { setting._shootable = 1; }

	bool isWater() { return setting._is_water ? true : false; }
	void setWater() { setting._is_water = 1; }

private:
	struct {
		unsigned _walkable : 1;
		unsigned _shootable : 1;
		unsigned _is_water : 1;
		unsigned unused : 5;
	} setting{0};
	map_cell_types _type{0};
};
#pragma pack(pop)
}
}

#endif /* HORIZON_ZONE_GAME_CELL_HPP */
