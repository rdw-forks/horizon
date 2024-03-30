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

#ifndef HORIZON_ZONE_GAME_MAPMANAGER_HPP
#define HORIZON_ZONE_GAME_MAPMANAGER_HPP

#include "Utility/TaskScheduler.hpp"
#include "MapContainerThread.hpp"
#include "Libraries/Networking/Buffer/ByteBuffer.hpp"

enum mapmgr_task_schedule_group
{
	MAPMGR_TASK_MAP_UPDATE = 0
};

namespace Horizon
{
namespace Zone
{

namespace Entities
{
	class Player;
}

class ZoneSession;
class Map;

class MapManager
{
public:
	bool initialize();
	bool finalize();
	bool LoadMapCache();

	std::shared_ptr<Map> manage_session_in_map(map_container_session_action action, std::string map_name, std::shared_ptr<ZoneSession> s);

	std::shared_ptr<Map> get_map(std::string map_name);

	TaskScheduler &getScheduler() { return _scheduler; }

	std::shared_ptr<Entities::Player> find_player(std::string name);

	std::map<int32_t, std::shared_ptr<MapContainerThread>> get_containers() { return _map_containers.get_map(); }

private:
	TaskScheduler _scheduler;
	LockedLookupTable<int32_t, std::shared_ptr<MapContainerThread>> _map_containers;
};
}
}

#endif /* HORIZON_GAME_MAP_MAPMGR_HPP */
