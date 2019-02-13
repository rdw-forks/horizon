#ifndef HORIZON_ZONE_GAME_ENTITIES_MERCENARY_HPP
#define HORIZON_ZONE_GAME_ENTITIES_MERCENARY_HPP

#include "Server/Zone/Game/Entities/Unit/Creature/Creature.hpp"

namespace Horizon
{
namespace Zone
{
namespace Game
{
template<class T>
class GridObject;
namespace Entities
{
class Mercenary : public Creature, public GridObject<Mercenary>
{
public:
	Mercenary(uint32_t guid);
	Mercenary(uint32_t guid, MapCoords mcoords);
	Mercenary(uint32_t guid, MapCoords mcoords, GridCoords gcoords);
	~Mercenary();

private:
};
}
}
}
}

#endif /* HORIZON_ZONE_GAME_ENTITIES_MERCENARY_HPP */