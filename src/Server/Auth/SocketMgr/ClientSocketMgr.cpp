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

#include "ClientSocketMgr.hpp"
#include "Server/Auth/Auth.hpp"

using namespace Horizon;

bool Auth::ClientSocketMgr::start(boost::asio::io_context &io_context, std::string const &listen_ip, uint16_t port, uint32_t threads, bool minimal)
{
	if (!BaseSocketMgr::start(io_context, listen_ip, port, threads, minimal))
		return false;
	for (auto i : get_thread_map()) {
		sAuth->register_component(Horizon::System::RUNTIME_NETWORKING, (std::dynamic_pointer_cast<AuthNetworkThread>(i.second)));
	}
	return true;
}