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

#include "GameLogicProcess.hpp"

#include "Server/Zone/Game/StaticDB/ExpDB.hpp"
#include "Server/Zone/Game/StaticDB/JobDB.hpp"
#include "Server/Zone/Game/StaticDB/ItemDB.hpp"
#include "Server/Zone/Game/StaticDB/MonsterDB.hpp"
#include "Server/Zone/Game/StaticDB/SkillDB.hpp"
#include "Server/Zone/Game/StaticDB/StatusEffectDB.hpp"
#include "Server/Zone/Game/StaticDB/StorageDB.hpp"

#include "Server/Common/Configuration/Horizon.hpp"
#include "Server/Zone/Game/Map/Map.hpp"
#include "Server/Zone/Game/Units/Player/Player.hpp"
#include "Server/Zone/Session/ZoneSession.hpp"
#include "Server/Zone/Zone.hpp"

using namespace Horizon::Zone;

static std::atomic<bool> static_db_loaded = false;

void GameLogicProcess::initialize(int segment_number)
{
	set_segment_number(segment_number);

	/**
	 * Static Databases
	 */
	if (static_db_loaded == false) {
		ExpDB->load();
		ExpDB->load_status_point_table();
		JobDB->load();
		ItemDB->load();
		ItemDB->load_refine_db();
		ItemDB->load_weapon_target_size_modifiers_db();
		ItemDB->load_weapon_attribute_modifiers_db();
		StatusEffectDB->load();
		SkillDB->load();
		MonsterDB->load();
		StorageDB->load();
		static_db_loaded = true;
	}
	load_map_cache();
	start_containers();

	_is_initialized.exchange(true);
}

void GameLogicProcess::finalize()
{
	std::map<int32_t, std::shared_ptr<MapContainerThread>> container_map = _map_containers.get_map();
	for (auto &cont : container_map) {
		cont.second->finalize();
	}

	_is_finalized.exchange(true);
}

bool GameLogicProcess::load_map_cache()
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

void GameLogicProcess::start_containers()
{
	int container_idx = 0, map_counter = 0, total_maps = 0;
	int mcache_size = _maps.size();
	int max_maps_per_thread = std::ceil((double) mcache_size / MAX_GAME_LOGIC_THREADS);
	int container_max = get_segment_number() * max_maps_per_thread;
	int container_min = (get_segment_number() - 1) * max_maps_per_thread;

	_map_containers.insert(0, std::make_shared<MapContainerThread>(std::bind(&GameLogicProcess::on_map_update, this, std::placeholders::_1)));

	auto map_i = _maps.begin();
	for (int i = container_min; i < container_max; i++)
	{
		std::shared_ptr<Map> map = std::make_shared<Map>(_map_containers.at(container_idx), map_i->second.name(), map_i->second.width(), map_i->second.height(), map_i->second.getCells());
		
		this->get_resource_manager().add<SEGMENT_PRIORITY_PRIMARY>(map_i->second.name(), map);
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
	
	HLog(info) << "Started map container " << get_segment_number() << " (" << container_min + 1 << " to " << container_max << " maps) for a total of " << container_max - container_min << " out of "  << mcache_size << " maps.";

	_maps.clear();
}

void GameLogicProcess::on_map_update(int64_t diff)
{
	get_system_routine_manager().process_queue();
}