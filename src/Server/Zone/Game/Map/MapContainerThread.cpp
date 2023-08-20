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
#include "Server/Zone/Game/Entities/Player/Player.hpp"
#include "Server/Zone/Zone.hpp"
#include "Server/Zone/Game/Map/Map.hpp"
#include "Server/Zone/Game/Map/MapManager.hpp"
#include "Core/Logging/Logger.hpp"
#include "Server/Zone/Session/ZoneSession.hpp"

using namespace Horizon::Zone;

MapContainerThread::MapContainerThread()
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

//! @brief Adds a session to the session buffer, marking him for management
//! in the list of the managed session by this container on the next update.
//! @param[in] action enum value of the action to be performed on the session.
//! @param[in] p shared_ptr to a session object which should be managed by this map.
//! @note A session added for management by this container must be the only owner of the session object.
void MapContainerThread::manage_session(map_container_session_action action, std::shared_ptr<ZoneSession> s)
{
	_session_buffer.push(std::make_pair(action, s));
}

std::shared_ptr<Entities::Player> MapContainerThread::get_player(std::string const &name)
{
	std::map<int64_t, std::shared_ptr<ZoneSession>> session_map = _managed_sessions.get_map();
	for (auto it = session_map.begin(); it != session_map.end(); it++)
		if (it->second->player()->name() == name)
			return it->second->player();

	return nullptr;
}

std::shared_ptr<Entities::Player> MapContainerThread::get_player(int guid)
{
	std::map<int64_t, std::shared_ptr<ZoneSession>> session_map = _managed_sessions.get_map();
	for (auto it = session_map.begin(); it != session_map.end(); it++)
		if (it->second->player()->guid() == guid)
			return it->second->player();

	return nullptr;
}

//! @brief Returns a session if found, nullptr otherwise.
std::shared_ptr<ZoneSession> MapContainerThread::get_session(int64_t session_id)
{
	std::map<int64_t, std::shared_ptr<ZoneSession>> session_map = _managed_sessions.get_map();
	auto it = session_map.find(session_id);
	
	if (it != session_map.end())
		return it->second;
	
	return nullptr;
}

//! @brief Responsible for initialization of the container and is called externally.
//! This is mainly for members that can't be initialized from the constructor method.
void MapContainerThread::initialize()
{
	_lua_mgr = std::make_shared<LUAManager>(shared_from_this());
}

//! @brief Add entity to vector of entities to be updated.
void MapContainerThread::add_entity(std::shared_ptr<Entity> entity)
{
	_entities.push_back(entity);
}

//! @brief Remove entity from vector of entities to be updated.
void MapContainerThread::remove_entity(std::shared_ptr<Entity> entity)
{
	_entities.erase(std::remove(_entities.begin(), _entities.end(), entity), _entities.end());
}

//! @brief Process container finalization by cleanly disconnecting players after saving their data.
//! Clears all managed map instances from itself.
//! This method must not be called from within the thread itself! @see MapManager::finalize()
void MapContainerThread::finalize()
{
	std::map<int64_t, std::shared_ptr<ZoneSession>> smap = _managed_sessions.get_map();
	for (auto si = smap.begin(); si != smap.end();) {
		std::shared_ptr<ZoneSession> session = si->second;

		if (session && session->player())
			session->player()->save();

		// Disconnect player.
		_managed_sessions.erase(session->get_socket()->get_socket_id());
		si++;
	}

	// Clear anyone in the session buffer (You never know...)
	std::shared_ptr<std::pair<map_container_session_action, std::shared_ptr<ZoneSession>>> sbuf = nullptr;

	while ((sbuf = _session_buffer.try_pop())) {
		std::shared_ptr<ZoneSession> session = sbuf->second;

		if (session == nullptr)
			continue;
		if (session->player() == nullptr) {
			HLog(warning) << "Tried to save player when player was nullptr in session " << session->get_session_id();
			continue;
		}

		session->player()->notify_nearby_players_of_existence(EVP_NOTIFY_LOGGED_OUT);
		session->player()->set_logged_in(false);
		session->player()->save();
		session->player()->remove_grid_reference();

//		player->get_packet_handler()->Send_ZC_ACK_REQ_DISCONNECT(true);
	}

	if (_thread.joinable())
		_thread.join();

	_managed_maps.clear();

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
	get_lua_manager()->initialize_for_container();

	HLog(info) << "Map container " << (void *) this << " has initialized.";
	HLog(info) << "Total maps: " << _managed_maps.size() << " Total sessions: " << _managed_sessions.size();
	int monster_count = 0, npc_count = 0;
	for (auto i = _lua_mgr->monster()->_monster_spawn_db.begin(); i != _lua_mgr->monster()->_monster_spawn_db.end(); i++)
		monster_count += i->second->amount;
	npc_count = _lua_mgr->npc()->_npc_db.size();
	HLog(info) << "Total monsters spawned: " << monster_count << " Total NPCs spawned: " << npc_count;

	int updates_per_second_timer = 0;
	int update_count = 0;
	double average_update_per_second = 0;
	while (!sZone->general_conf().is_test_run() && sZone->get_shutdown_stage() == SHUTDOWN_NOT_STARTED) {
		std::chrono::high_resolution_clock::time_point start_time = std::chrono::high_resolution_clock::now();
		update(std::time(nullptr));
		update_count++;
		std::chrono::high_resolution_clock::time_point end_time = std::chrono::high_resolution_clock::now();
    
		std::chrono::duration<long, std::micro> elapsed_time = std::chrono::duration_cast<std::chrono::duration<long, std::micro>>(end_time - start_time);

		// Check updates per second.
    	updates_per_second_timer += elapsed_time.count();

		if (updates_per_second_timer / 1000 >= 1000) {
			average_update_per_second = update_count + (update_count <= 1 ? 0 : average_update_per_second) / update_count;
        	HLog(info) << "Map Container " << (void*) this << " update rate: " << average_update_per_second << " update(s) per second.";
			updates_per_second_timer = 0;
        	update_count = 0;
   		}
		
		std::this_thread::sleep_for(std::chrono::microseconds(MAX_CORE_UPDATE_INTERVAL));
	};

	get_lua_manager()->finalize();
}

//! @brief World update loop for a MapContainerThread.
//! Performs world updates for maps managed in the specific thread container.
//! @param[in] diff current system time.
void MapContainerThread::update(uint64_t diff)
{
	std::shared_ptr<std::pair<map_container_session_action, std::shared_ptr<ZoneSession>>> sbuf = nullptr;

	// Add any new players / remove anyone else.
	while ((sbuf = _session_buffer.try_pop())) {
		map_container_session_action action = sbuf->first;
		std::shared_ptr<ZoneSession> session = sbuf->second;

		if (session == nullptr)
			continue;

		if (action == SESSION_ACTION_ADD) {
			if (session->is_initialized() && session->player() != nullptr && session->player()->is_initialized() == false) {
				// Intialized player upon loading.
				session->player()->initialize();
			}
			
			_managed_sessions.insert(session->get_session_id(), session);
			add_entity(session->player());
			HLog(debug) << "Session " << session->get_session_id() << " was added to managed sessions in map container " << (void *) this;
		} else if (action == SESSION_ACTION_REMOVE) {
			remove_entity(session->player());
			_managed_sessions.erase(session->get_session_id());
			HLog(debug) << "Session " << session->get_session_id() << " was removed from managed sessions in map container " << (void *) this;
		} else if (action == SESSION_ACTION_LOGOUT_AND_REMOVE) {
			if (session->player() != nullptr) {
				session->player()->notify_nearby_players_of_existence(EVP_NOTIFY_LOGGED_OUT);
				session->player()->set_logged_in(false);
				session->player()->save();
				if (session->player()->has_valid_grid_reference())
					session->player()->remove_grid_reference();
				session->player()->map()->sub_user_count();
			}
			remove_entity(session->player());
			_managed_sessions.erase(session->get_session_id());
			HLog(debug) << "Session " << session->get_session_id() << " was logged out and removed from managed sessions in map container " << (void *) this;
		}
	}

	// Update the entities.
	std::chrono::high_resolution_clock::time_point start_time_e = std::chrono::high_resolution_clock::now();
	for (auto i = _entities.begin(); i != _entities.end();) {
		std::shared_ptr<Entity> entity = *i;

		if (entity == nullptr || entity->is_finalized()) {
			i = _entities.erase(i);
			continue;
		} else if (entity->is_initialized() == false)
			continue;

		entity->update(diff);
		++i;
	}
	std::chrono::high_resolution_clock::time_point end_time_e = std::chrono::high_resolution_clock::now();
	std::chrono::duration<long, std::micro> elapsed_time_e = std::chrono::duration_cast<std::chrono::duration<long, std::micro>>(end_time_e - start_time_e);
	//HLog(debug) << "Entities Update time: " << elapsed_time_e.count() << "us";

	// Update sessions
	std::map<int64_t, std::shared_ptr<ZoneSession>> smap = _managed_sessions.get_map();
	for (auto si = smap.begin(); si != smap.end();) {
		std::shared_ptr<ZoneSession> session = si->second;

		if (session == nullptr) {
			_managed_sessions.erase(si->first);
			si++;
			continue;
		}
		// process packets
		session->update(diff);
		si++;
	}
	
	// Update Monsters
	std::chrono::high_resolution_clock::time_point start_time = std::chrono::high_resolution_clock::now();
	getScheduler().Update();
	std::chrono::high_resolution_clock::time_point end_time = std::chrono::high_resolution_clock::now();
	std::chrono::duration<long, std::micro> elapsed_time = std::chrono::duration_cast<std::chrono::duration<long, std::micro>>(end_time - start_time);
	//HLog(debug) << "Scheduler Update time: " << elapsed_time.count() << "us";
}
