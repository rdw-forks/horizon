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

#ifndef HORIZON_ZONE_ZONERUNTIME_HPP
#define HORIZON_ZONE_ZONERUNTIME_HPP

#include <boost/lockfree/queue.hpp>
#include <optional> 

class DatabaseProcess;

namespace Horizon
{
namespace Zone
{
struct s_zone_server_configuration;
class ClientSocketMgr;
// @brief Routines that go into the main Horizon runtime.
class ZoneRuntime
{
public:
    ZoneRuntime(boost::asio::io_service &io_service, general_server_configuration &config);

    general_server_configuration &general_conf() { return _config; }

    void initialize();
    void finalize();

	void run(uint64_t diff);

    std::shared_ptr<ClientSocketMgr> network();
    std::shared_ptr<DatabaseProcess> database();

protected:
    general_server_configuration &_config;
	boost::asio::deadline_timer _update_timer;
    boost::asio::io_service &_io_service;
};
}
}

#endif // HORIZON_ZONE_ZONERUNTIME_HPP
