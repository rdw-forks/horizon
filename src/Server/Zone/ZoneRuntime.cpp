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
#include "Server/Common/Server.hpp"
#include "Server/Zone/ZoneSystem.hpp"
#include "Server/Zone/Zone.hpp"
#include "Server/Zone/SocketMgr/ClientSocketMgr.hpp"

using namespace Horizon::Zone;

ZoneRuntime::ZoneRuntime(boost::asio::io_service &io_service, general_server_configuration &config)
: _io_service(io_service), _update_timer(io_service), _config(config)
{

}

void ZoneRuntime::initialize()
{
    HLog(info) << "Horizon main-frame runtime initiated.";
	
	_update_timer.expires_from_now(boost::posix_time::microseconds(MAX_CORE_UPDATE_INTERVAL));
	_update_timer.async_wait(std::bind(&ZoneRuntime::run, this, MAX_CORE_UPDATE_INTERVAL));
}

void ZoneRuntime::run(uint64_t time)
{
	sZone->get_component_of_type<CommandLineProcess>(Horizon::System::RUNTIME_COMMANDLINE)->process();

	/**
	 * Process Packets.
	 */
	sZone->get_component_of_type<ClientSocketMgr>(Horizon::System::RUNTIME_NETWORKING)->manage_sockets(time);

    sZone->get_component_of_type<ClientSocketMgr>(Horizon::System::RUNTIME_NETWORKING)->update_sessions(time);

	// Process Horizon System Routine Queue.
	sZone->system_routine_process_queue();

	if (get_shutdown_stage() == SHUTDOWN_NOT_STARTED && !general_conf().is_test_run()) {
		_update_timer.expires_from_now(boost::posix_time::microseconds(MAX_CORE_UPDATE_INTERVAL));
		_update_timer.async_wait(std::bind(&ZoneRuntime::run, this, std::time(nullptr)));
	} else {
        finalize();
	}
}

void ZoneRuntime::finalize()
{
    HLog(info) << "Horizon main-frame runtime finalized.";
	sZone->finalize();
}

std::shared_ptr<ClientSocketMgr> ZoneRuntime::network() { return sZone->get_component_of_type<ClientSocketMgr>(Horizon::System::RUNTIME_NETWORKING); }
std::shared_ptr<DatabaseProcess> ZoneRuntime::database() { return sZone->get_component_of_type<DatabaseProcess>(Horizon::System::RUNTIME_DATABASE); }