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
 *  (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 **************************************************/

#ifndef HORIZON_ZONE_ZONESOCKET_HPP
#define HORIZON_ZONE_ZONESOCKET_HPP

#include "Libraries/Networking/Socket.hpp"

using boost::asio::ip::tcp;

namespace Horizon
{
namespace Zone
{
class ZoneSession;
class ZoneSocket : public Horizon::Networking::Socket<ZoneSocket>
{
	typedef Socket<ZoneSocket> BaseSocket;
public:
	ZoneSocket(uint64_t uid, std::shared_ptr<tcp::socket> socket);
	~ZoneSocket() { }
	/* */
	void start() override;
	bool update() override;

	/* */
	std::shared_ptr<ZoneSession> get_session();
	void set_session(std::shared_ptr<ZoneSession> session);
protected:
	void read_handler() override;
	void on_close() override;
	void on_error() override;

	std::shared_ptr<ZoneSession> _session;
};
}
}
#endif //HORIZON_ZONE_ZONESOCKET_HPP
