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
 * Base Author - Sxyz <sagunxp@gmail.com>
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

#include "Map.hpp"
#include "Utility/Utility.hpp"
#include "Core/Multithreading/WorkerThreadPool.hpp"
#include "Server/Zone/Game/Map/Grid/Notifiers/GridNotifiers.hpp"
#include "Server/Zone/Game/Map/Grid/Container/GridReferenceContainer.hpp"
#include "Server/Zone/Game/Map/Grid/Container/GridReferenceContainerVisitor.hpp"
#include "Server/Zone/Game/Map/Grid/Grid.hpp"

using namespace Horizon::Zone;

Map::Map(std::weak_ptr<MapContainerThread> container, std::string const &name, uint16_t width, uint16_t height, std::vector<uint8_t> const &cells)
: _container(container), _name(name), _width(width), _height(height),
  _max_grids((width / MAX_CELLS_PER_GRID), (height / MAX_CELLS_PER_GRID)),
  _gridholder((width / MAX_CELLS_PER_GRID) + 1, (height / MAX_CELLS_PER_GRID) + 1), // add 1 because 0,0 is included.
  _pathfinder(AStar::Generator(MapCoords(width, height), std::bind(&Map::has_obstruction_at, this, std::placeholders::_1, std::placeholders::_2), MAX_VIEW_RANGE))
{
	for (int y = height - 1; y >= 0; --y) {
		for (int x = 0; x < width; ++x) {
			_cells[x][y] = Cell(cells.at(y * width + x));
		}
	}
}

Map::~Map()
{
}

bool Map::has_obstruction_at(int16_t x, int16_t y)
{
	if (x < 0 || y < 0 || x > _width || y > _height)
		return true;

	Cell c = _cells[x][y];
	
	if (!c.isWalkable())
		return true;

	return false;
}


