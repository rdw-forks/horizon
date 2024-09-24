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
 * This is proprietary software. Unauthorized copying,
 * distribution, or modification of this file, via any
 * medium, is strictly prohibited. All rights reserved.
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