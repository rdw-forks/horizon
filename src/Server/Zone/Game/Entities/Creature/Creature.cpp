/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
       \_| |_/\___/|_|  |_/___\___/|_| |_|        *
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

#include "Creature.hpp"

#include "Server/Zone/Game/Map/Map.hpp"
#include "Server/Zone/Game/Entities/Traits/Status.hpp"
#include "Server/Zone/Game/Entities/Creature/Creature.hpp"

using namespace Horizon::Zone::Entities;

Creature::Creature(uint32_t guid, entity_type type, std::shared_ptr<Map> map, MapCoords mcoords)
: Entity(guid, type, map, mcoords)
{
	//
}

Creature::~Creature()
{
}

bool Creature::initialize(std::shared_ptr<const monster_config_data> md)
{
	if (Entity::initialize() == false)
		return false;

	if (status()->initialize(shared_from_this()->downcast<Creature>(), md) == false) {
		HLog(error) << "Status::initialize: failed to initialize status for creature with monster id " << md->monster_id << ".";
		return false;
	}

	return true;
}