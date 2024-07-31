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

#include "MapContainerThread.hpp"
#include "Server/Zone/Game/Units/Player/Player.hpp"
#include "Server/Zone/Zone.hpp"
#include "Server/Zone/Game/Map/Map.hpp"
#include "Server/Zone/Socket/ZoneSocket.hpp"
#include "Server/Zone/Session/ZoneSession.hpp"

using namespace Horizon::Zone;

MapContainerThread::MapContainerThread(std::function<void(uint64_t)> update_callback)
: _update_callback(update_callback)
{

}

MapContainerThread::~MapContainerThread()
{
}

//! @brief Retrieves a shared pointer to a map managed by the container.
//! Managed maps are saved in thread-safe tables.
//! @param[in] name const reference to the name of the map to lookup.
//! @return Managed map if found, else a null shared_ptr instance.
std::shared_ptr<Map> MapContainerThread::get_map(std::string const &name) const
{
	return _managed_maps.at(name);
}

//! @brief Adds a map to the container in real time. Managed maps are
//! saved in thread-safe tables.
//! @param[in] m r-value reference to a shared_ptr of a map object.
void MapContainerThread::add_map(std::shared_ptr<Map> &&m)
{
	_managed_maps.insert(m->get_name(), m);
}

//! @brief Removes a map from the container in real time. Managed maps are
//! saved in thread-safe tables.
//! @param[in] m r-value reference to a shared_ptr of a map object.
void MapContainerThread::remove_map(std::string const &name)
{
	_managed_maps.erase(name);
}

//! @brief Responsible for initialization of the container and is called externally.
//! This is mainly for members that can't be initialized from the constructor method.
void MapContainerThread::initialize()
{
}

//! @brief Add unit to vector of entities to be updated.
void MapContainerThread::add_unit(std::shared_ptr<Unit> unit)
{
	_entities.push_back(unit);
}

//! @brief Remove unit from vector of entities to be updated.
void MapContainerThread::remove_unit(std::shared_ptr<Unit> unit)
{
	_entities.erase(std::remove(_entities.begin(), _entities.end(), unit), _entities.end());
}

//! @brief Process container finalization by cleanly disconnecting players after saving their data.
//! Clears all managed map instances from itself.
//! This method must not be called from within the thread itself! @see GameLogicProcess::finalize()
void MapContainerThread::finalize()
{
	// Clear anyone in the session buffer (You never know...)
	_managed_maps.clear();

	//@TODO finalize lua manager
	//get_lua_manager()->finalize();

	if (_thread.joinable())
		_thread.join();

	HLog(info) << "Map container " << (void *) this << " has shut down.";
}

//! @brief Begins running the container's thread and notifies of doing so.
//! This function is a wrapper for the internal start function which the internal thread instance is
//! responsible for calling. The internal start function deals with actual data loading/initializing,
//! world update loop and finalization of the same on shutdown.
void MapContainerThread::start()
{
	_thread = std::thread(&MapContainerThread::start_internal, this);

	HLog(info) << "Map container " << (void *) this << " with " << _managed_maps.size() << " maps has begun working.";
}

//! @brief Called by the internal thread of MapContainerThread and deals with initialization of thread-accessible data.
//! Is also responsible emulating the world update loop and performing everything in maps it manages.
//! @thread MapContainerThread
void MapContainerThread::start_internal()
{
	HLog(info) << "Map container " << (void *) this << " has initialized.";
	HLog(info) << "Total maps: " << _managed_maps.size();

	while (!sZone->general_conf().is_test_run_minimal() && get_shutdown_stage() == SHUTDOWN_NOT_STARTED) {
		update(std::time(nullptr));
		std::this_thread::sleep_for(std::chrono::microseconds(MAX_CORE_UPDATE_INTERVAL));
	};
}

//! @brief World update loop for a MapContainerThread.
//! Performs world updates for maps managed in the specific thread container.
//! @param[in] diff current system time.
void MapContainerThread::update(uint64_t diff)
{
	// Update the entities.
	for (auto unit : _entities)
		if(unit != nullptr)
			unit->update(diff);

	getScheduler().Update();

	_update_callback(diff);
}
