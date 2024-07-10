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

#include "MapManager.hpp"

#include "Server/Common/Configuration/Horizon.hpp"
#include "Server/Zone/Game/Map/Map.hpp"
#include "Server/Zone/Game/Units/Player/Player.hpp"
#include "Server/Zone/Session/ZoneSession.hpp"
#include "Server/Zone/Zone.hpp"

using namespace Horizon::Zone;

bool MapManager::initialize(int segment_number)
{
	LoadMapCache();
	start_containers(segment_number);
	return true;
}

bool MapManager::finalize(int segment_number)
{
	std::map<int32_t, std::shared_ptr<MapContainerThread>> container_map = _map_containers.get_map();
	for (auto &cont : container_map) {
		cont.second->finalize();
	}

	return true;
}

bool MapManager::LoadMapCache()
{
	Horizon::Libraries::MapCache m;
	std::string db_path = sZone->config().get_static_db_path().string();

	m.setMapListPath(db_path + "map_list.lua");
	m.setMapCachePath(sZone->config().get_mapcache_path().string());

	if (m.ReadMapListConfig() != MCACHE_CONFIG_OK) {
		HLog(error) <<"Could not read map config file '" << m.getMapListPath().string() << "'.";
		return false;
	}

	switch (m.ImportFromCacheFile())
	{
		default:
			break;
		case MCACHE_IMPORT_NONEXISTENT_FILE:
			HLog(error) << "Could not open file '" << m.getMapCachePath().string() << "'.";
			return false;
		case MCACHE_IMPORT_READ_ERROR:
			HLog(error) << "Could not read file '" << m.getMapCachePath().string() << "', rebuilding...";
			return false;
		case MCACHE_IMPORT_INVALID_CHECKSUM:
			HLog(error) << "File cache file '" << m.getMapCachePath().string() << "' is corrupted (invalid checksum), rebuilding...";
			return false;
		case MCACHE_IMPORT_DECOMPRESS_ERROR:
			HLog(error) << "File cache file '" << m.getMapCachePath().string() << "' could not be decompressed, rebuilding...";
			return false;
		case MCACHE_IMPORT_MAPINFO_ERROR:
			HLog(error) << "Could not read map information for a map while importing file '" << m.getMapCachePath().string() << "', rebuilding...";
			return false;
		case MCACHE_IMPORT_CELLINFO_ERROR:
			HLog(error) << "Could not read cell information for a map while importing file '" << m.getMapCachePath().string() << "', rebuilding...";
			return false;
	}

	_maps = m.getMCache()->maps;
	
	return true;
}

void MapManager::start_containers(int segment_number)
{
	int container_idx = 0, map_counter = 0, total_maps = 0;
	int mcache_size = _maps.size();
	int max_maps_per_thread = std::ceil((double) mcache_size / MAX_GAME_LOGIC_THREADS);
	int container_max = segment_number * max_maps_per_thread;
	int container_min = (segment_number - 1) * max_maps_per_thread;

	_map_containers.insert(0, std::make_shared<MapContainerThread>());

	auto map_i = _maps.begin();
	for (int i = container_min; i < container_max; i++)
	{
		std::shared_ptr<Map> map = std::make_shared<Map>(_map_containers.at(container_idx), map_i->second.name(), map_i->second.width(), map_i->second.height(), map_i->second.getCells());
		(_map_containers.at(container_idx))->add_map(std::move(map));

		if (max_maps_per_thread - 1 == map_counter) {
			(_map_containers.at(container_idx))->initialize();
			(_map_containers.at(container_idx))->start();
			map_counter = 0;
			container_idx++;
		}

		map_counter++;
		total_maps++;
		map_i++;
	}
	
	HLog(info) << "Started map container " << segment_number << " (" << container_min + 1 << " to " << container_max << " maps) for a total of " << container_max - container_min << " out of "  << mcache_size << " maps.";

	_maps.clear();
}

std::shared_ptr<Map> MapManager::manage_session_in_map(map_container_session_action action, std::string map_name, std::shared_ptr<ZoneSession> s)
{
	std::map<int32_t, std::shared_ptr<MapContainerThread>> container_map = _map_containers.get_map();
	for (auto i = container_map.begin(); i != container_map.end(); i++) {
		std::shared_ptr<Map> map = i->second->get_map(map_name);

		if (map == nullptr)
			continue;

		i->second->manage_session(action, s);
		return map;
	}

	return nullptr;
}

std::shared_ptr<Map> MapManager::get_map(std::string map_name)
{
	std::map<int32_t, std::shared_ptr<MapContainerThread>> container_map = _map_containers.get_map();
	
	for (auto it = container_map.begin(); it != container_map.end(); ++it) {
		std::shared_ptr<MapContainerThread> mapc = it->second;
		std::shared_ptr<Map> map = mapc->get_map(map_name);
		if (map) 
			return map;
	}

	return nullptr;
}

std::shared_ptr<Units::Player> MapManager::find_player(std::string name)
{
	std::map<int32_t, std::shared_ptr<MapContainerThread>> map_containers = _map_containers.get_map();
	for (auto it = map_containers.begin(); it != map_containers.end(); it++) {
		std::shared_ptr<Units::Player> player = it->second->get_player(name);
		if (player != nullptr)
			return player;
	}

	return nullptr;
}