#ifndef HORIZON_ZONE_GAME_GRIDDEFINITIONS_HPP
#define HORIZON_ZONE_GAME_GRIDDEFINITIONS_HPP

#include "Core/Structures/TypeList.hpp"
#include "Server/Zone/Game/Map/Coordinates.hpp"

namespace Horizon
{
	namespace Zone
	{
		namespace Game
		{
			namespace Entities
			{
				class Player;
				class NPC;
				class Elemental;
				class Homunculus;
				class Mercenary;
				class Pet;
				class Monster;
				class MVP;
				class Skill;
			}
		}
	}
}

using namespace Horizon::Zone::Game::Entities;

template <class ACTIVE_OBJECT, class ZONE_OBJECT_TYPES>
class GridHolder;

#define MAX_CELLS_PER_GRID 8
// Max Cells in a map are 416 and so 52 * 8.
#define MAX_GRIDS_PER_MAP 52
#define MAX_CELLS_PER_MAP MAX_CELLS_PER_GRID * MAX_GRIDS_PER_MAP
#define GRID_UPDATE_DELAY 60000 ///< In milliseconds. (@TODO change to config)

typedef TYPELIST_9(Player, NPC, Elemental, Homunculus, Mercenary, Pet, Monster, MVP, Skill) AllEntityTypes;

typedef GridHolder<Player, AllEntityTypes> GridHolderType;

typedef Coordinates<MAX_GRIDS_PER_MAP> GridCoords;
typedef Coordinates<MAX_CELLS_PER_MAP> MapCoords;

#endif /* HORIZON_ZONE_GAME_GRIDDEFINITIONS_HPP */