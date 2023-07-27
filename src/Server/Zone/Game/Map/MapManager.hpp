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
friend class MapContainerJob;
public:
	MapManager() { };
	~MapManager();

	static MapManager *getInstance()
	{
		static MapManager map_mgr;
		return &map_mgr;
	}

	bool initialize();
	bool finalize();
	bool LoadMapCache();

	std::shared_ptr<Map> add_session_to_map(std::string map_name, std::shared_ptr<ZoneSession> s);
	bool remove_session_from_map(std::string map_name, std::shared_ptr<ZoneSession> s);

	std::shared_ptr<Map> get_map(std::string map_name);

	TaskScheduler &getScheduler() { return _scheduler; }

	std::shared_ptr<Entities::Player> find_player(std::string name);

	std::map<int32_t, std::shared_ptr<MapContainerThread>> get_containers() { return _map_containers.get_map(); }

	//! @brief Container job queue, storing the jobs required to be called in the next update sequence.
	//! Jobs are only run in one instance of MapContainerThread, queued by other MapContainerThreads threads.
	void consign_job_to_all(MapContainerJob &job);
private:
	TaskScheduler _scheduler;
	LockedLookupTable<int32_t, std::shared_ptr<MapContainerThread>> _map_containers;
};

//! @brief MapContainerJob is a class invoked in the calling thread. The calling thread initiates the
//! work transaction / transfer. 
//! @note MapContainerJob class should be a one-way transfer or transaction between
//! the intiating thread and the remaining worker threads. This typically means that the transfer should not lead
//! to a recursive invocation of the job, for example, execution pathways that lead to the same job execution should be avoided.
class MapContainerJob
{
public:
	MapContainerJob() { }
	~MapContainerJob() { }

	//! @brief Run method is invoked from the invokee threads, responsible for
	//! invoking the function. Threads in which a job is queued are responsible for running the job.
	//! thread: any thread but the caller thread.
	//! thread-safety: Mutex can be applied within the run function's workings to create a thread-safe working environment.
	virtual bool run(std::shared_ptr<MapContainerThread> container) { return false; }
};

class SearchSessionAndTransmitJob : public MapContainerJob
{
    ByteBuffer _buf;
    int64_t _session_id{ 0 };
public:
    SearchSessionAndTransmitJob(int64_t session_id, ByteBuffer &buf) : _session_id(session_id), _buf(buf), MapContainerJob() { }
    ~SearchSessionAndTransmitJob() { }

    bool run(std::shared_ptr<MapContainerThread> container);
};

}
}

#define MapMgr Horizon::Zone::MapManager::getInstance()

#endif /* HORIZON_GAME_MAP_MAPMGR_HPP */
