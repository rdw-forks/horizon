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

#ifndef HORIZON_ZONE_GAME_ENTITIES_MERCENARY_HPP
#define HORIZON_ZONE_GAME_ENTITIES_MERCENARY_HPP

#include "Server/Zone/Game/Units/Mob/Mob.hpp"
#include "Server/Zone/Game/GridObject.hpp"


namespace Horizon
{
namespace Zone
{
class Map;
namespace Units
{
class Mercenary : public Mob, public GridObject<Mercenary>
{
public:
	Mercenary(uint64_t uuid, std::shared_ptr<Map> map, MapCoords mcoords);
	~Mercenary();

    void stop_movement() override;
    void on_pathfinding_failure() override;
    void on_movement_begin(int32_t time) override;
    void on_movement_step() override;
    void on_movement_end() override;

    void on_status_effect_start(std::shared_ptr<status_change_entry> sce) override;
    void on_status_effect_end(std::shared_ptr<status_change_entry> sce) override;
    void on_status_effect_change(std::shared_ptr<status_change_entry> sce) override;
private:
};
}
}
}

#endif /* HORIZON_ZONE_GAME_ENTITIES_MERCENARY_HPP */
