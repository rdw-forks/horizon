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

#ifndef HORIZON_ZONE_GAME_ENTITIES_SKILL_HPP
#define HORIZON_ZONE_GAME_ENTITIES_SKILL_HPP

#include "Server/Zone/Game/Units/Unit.hpp"
#include "Server/Zone/Game/GridObject.hpp"

namespace Horizon
{
namespace Zone
{
namespace Units
{
class Skill : public Unit, public GridObject<Skill>
{
public:
	Skill(uint64_t uuid, std::shared_ptr<Map> map, MapCoords mcoords);
	~Skill();

    void stop_movement() override;
    void on_pathfinding_failure() override;
    void on_movement_begin(int32_t time) override;
    void on_movement_step() override;
    void on_movement_end() override;
};
}
}
}

#endif /* HORIZON_ZONE_GAME_ENTITIES_SKILL_HPP */
