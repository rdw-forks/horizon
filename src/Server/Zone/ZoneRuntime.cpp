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

#include "ZoneRuntime.hpp"
#include "ZoneSystem.hpp"
#include "Server/Common/Server.hpp"
#include "Server/Zone/Zone.hpp"
#include "Server/Zone/SocketMgr/ClientSocketMgr.hpp"

using namespace Horizon::Zone;

ZoneRuntime::ZoneRuntime(general_server_configuration &config)
: _config(config), _update_timer(_io_context_global)
{
}

ZoneRuntime::~ZoneRuntime()
{
	_zone_users.clear();
	_update_timer.cancel();
	_update_timer.~basic_deadline_timer();
}

void ZoneRuntime::initialize()
{
    HLog(info) << "Horizon main-frame runtime initiated.";

	_update_timer.expires_from_now(boost::posix_time::seconds(1));
	_update_timer.async_wait(std::bind(&ZoneRuntime::run, this, MAX_CORE_UPDATE_INTERVAL));
	
	// We declare this here since the responsibility of starting the network is of 
	// the Runtime level. It must remain lower than the mainframe, because
	// we're using the mainframe's io_context and it will be destroyed after the destruction of
	// the ClientSocketMgr class. This fixes the issue of dangling pointers and memory access violations.
	sZone->get_client_socket_mgr().start(_io_context_global,
						  sZone->general_conf().get_listen_ip(),
						  general_conf().get_listen_port(),
						  MAX_NETWORK_THREADS,
						  general_conf().is_test_run());

}

/**
 * Runs the ZoneRuntime for a given time.
 *
 * This function is responsible for executing the runtime logic of the Zone. It performs the following tasks:
 * 1. Processes the command line.
 * 2. Manages client sockets.
 * 3. Updates client sessions.
 * 4. Processes the Horizon System Routine Queue.
 * 5. Handles shutdown and finalization.
 *
 * @param time The current time in microseconds.
 */
void ZoneRuntime::run(uint64_t time)
{
	// Disable command line on test runs.
	if (!general_conf().is_test_run())
		sZone->get_component_of_type<CommandLineProcess>(Horizon::System::RUNTIME_COMMANDLINE)->process();

	/**
	 * Process Packets.
	 */
	sZone->get_client_socket_mgr().manage_sockets(time);
    sZone->get_client_socket_mgr().update_sessions(time);

	// Process Horizon System Routine Queue.
	sZone->system_routine_process_queue();

	if (get_shutdown_stage() == SHUTDOWN_NOT_STARTED && !general_conf().is_test_run()) {
		_update_timer.expires_from_now(boost::posix_time::microseconds(MAX_CORE_UPDATE_INTERVAL));
		_update_timer.async_wait(std::bind(&ZoneRuntime::run, this, std::time(nullptr)));
		std::this_thread::sleep_for(std::chrono::microseconds(MAX_CORE_UPDATE_INTERVAL));
	} else {
		finalize();
	}
}

void ZoneRuntime::finalize()
{
	set_shutdown_stage(SHUTDOWN_INITIATED);

	// Stop the client socket manager here because the io_context will be stopped later.
	// If this is stopped before the io_context, it will cause a dangling pointer.
	sZone->get_client_socket_mgr().stop();

	// Stop the mainframe components and other processes before stopping io_context.
	sZone->finalize();

    HLog(info) << "Horizon main-frame runtime finalized.";
}

std::shared_ptr<ScriptManager> User::get_script_process() { return sZone->get_component<ScriptManager>(_module_allocation[Horizon::System::RUNTIME_SCRIPTVM]); }
void User::set_script_process(std::string uuid) { _module_allocation[Horizon::System::RUNTIME_SCRIPTVM] = uuid; }

std::shared_ptr<DatabaseProcess> User::get_database_process() { return sZone->get_component<DatabaseProcess>(_module_allocation[Horizon::System::RUNTIME_DATABASE]); }
void User::set_database_process(std::string uuid) { _module_allocation[Horizon::System::RUNTIME_DATABASE] = uuid; }

std::shared_ptr<CommandLineProcess> User::get_commandline_process() { return sZone->get_component<CommandLineProcess>(_module_allocation[Horizon::System::RUNTIME_COMMANDLINE]); }
void User::set_commandline_process(std::string uuid) { _module_allocation[Horizon::System::RUNTIME_COMMANDLINE] = uuid; }

std::shared_ptr<ZoneNetworkThread> User::get_networking_process() { return sZone->get_component<ZoneNetworkThread>(_module_allocation[Horizon::System::RUNTIME_NETWORKING]); }
void User::set_networking_process(std::string uuid) { _module_allocation[Horizon::System::RUNTIME_NETWORKING] = uuid; }

std::shared_ptr<PersistenceManager> User::get_persistence_process() { return sZone->get_component<PersistenceManager>(_module_allocation[Horizon::System::RUNTIME_PERSISTENCE]); }
void User::set_persistence_process(std::string uuid) { _module_allocation[Horizon::System::RUNTIME_PERSISTENCE] = uuid; }

std::shared_ptr<GameLogicProcess> User::get_game_logic_process() { return sZone->get_component<GameLogicProcess>(_module_allocation[Horizon::System::RUNTIME_GAMELOGIC]); }
void User::set_game_logic_process(std::string uuid) { _module_allocation[Horizon::System::RUNTIME_GAMELOGIC] = uuid; }