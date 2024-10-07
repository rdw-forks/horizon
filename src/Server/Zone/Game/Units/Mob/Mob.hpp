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

#ifndef HORIZON_ZONE_GAME_ENTITIES_MOB_HPP
#define HORIZON_ZONE_GAME_ENTITIES_MOB_HPP

#include "Server/Zone/Game/Units/Unit.hpp"

struct monster_config_data;

namespace Horizon
{
namespace Zone
{
class Map;
namespace Units
{
class Mob : public Unit
{
public:
	Mob(uint64_t uuid, unit_type type, unit_type_mask type_mask, std::shared_ptr<Map> map, MapCoords mcoords);
	~Mob() override;

	bool initialize(std::shared_ptr<const monster_config_data> md);
	virtual bool finalize() override;

	virtual void on_damage_received(std::shared_ptr<Unit> damage_dealer, int damage) override;
	virtual void on_killed(std::shared_ptr<Unit> killer, bool with_drops = false, bool with_exp = false) override;
};
}
}
}

#endif /* HORIZON_ZONE_GAME_ENTITIES_MOB_HPP */
