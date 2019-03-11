/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
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

#ifndef HORIZON_ZONE_GAME_ENTITIES_NPC_HPP
#define HORIZON_ZONE_GAME_ENTITIES_NPC_HPP

#include "Server/Zone/Game/Entities/Entity.hpp"
#include "Common/Definitions/NPCDefinitions.hpp"
#include "Server/Zone/Game/Entities/GridObject.hpp"

namespace Horizon
{
namespace Zone
{
namespace Game
{
namespace Entities
{
class NPC : public Entity, public GridObject<NPC>
{
public:
	NPC(std::string const &name, std::shared_ptr<Map> map, MapCoords const &coords, uint32_t job_id, directions dir);
	~NPC();

	void initialize() override;
	virtual void stop_movement() override;

	virtual void on_movement_begin() override;
	virtual void on_movement_step() override;
	virtual void on_movement_end() override;
	virtual void sync_with_models() override;

private:
};
}
}
}
}

#endif /* HORIZON_ZONE_GAME_ENTITIES_NPC_HPP */
