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

#ifndef HORIZON_ZONE_GAME_GRIDDEFINITIONS_HPP
#define HORIZON_ZONE_GAME_GRIDDEFINITIONS_HPP

#include "Core/Structures/TypeList.hpp"
#include "Server/Zone/Game/Map/Coordinates.hpp"

namespace Horizon
{
	namespace Zone
	{
		namespace Units
		{
			class Player;
			class NPC;
			class Elemental;
			class Homunculus;
			class Mercenary;
			class Pet;
			class Monster;
			class Item;
			class Skill;
		}
	}
}

template <class ZONE_OBJECT_TYPES>
class GridHolder;

template <int16_t MAX_COORDINATES>
class Coordinates;

template<class OBJECT_TYPES>
class GridReferenceContainer;

// Max Cells in a map are 416.
#define MAX_CELLS_PER_GRID 32
#define MAX_GRIDS_PER_MAP 14
#define MAX_CELLS_PER_MAP MAX_CELLS_PER_GRID * MAX_GRIDS_PER_MAP

#define unit_ns(e) Horizon::Zone::Units::e
typedef TYPELIST_9(unit_ns(Player),
	unit_ns(NPC),
	unit_ns(Elemental),
	unit_ns(Homunculus),
	unit_ns(Mercenary),
	unit_ns(Pet),
	unit_ns(Monster),
	unit_ns(Skill),
	unit_ns(Item)) AllUnitTypes;
typedef GridHolder<AllUnitTypes> GridHolderType;
#undef unit_ns

typedef Coordinates<MAX_GRIDS_PER_MAP> GridCoords;
typedef Coordinates<MAX_CELLS_PER_MAP> MapCoords;

typedef GridReferenceContainer<AllUnitTypes> MapUnitContainer;

enum grid_unit_skill_use_notification_type
{
	GRID_UNIT_SKILL_USE_NOTIFY_CASTTIME,
	GRID_UNIT_SKILL_USE_NOTIFY_SUCCESS_DAMAGE,
	GRID_UNIT_SKILL_USE_NOTIFY_SUCCESS_NO_DAMAGE,
};

#endif /* HORIZON_ZONE_GAME_GRIDDEFINITIONS_HPP */
