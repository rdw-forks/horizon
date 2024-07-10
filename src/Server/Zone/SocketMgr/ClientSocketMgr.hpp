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

/* This is an auto-generated file, please do not edit manually. */

#ifndef HORIZON_ZONE_CLIENTSOCKETMGR_HPP
#define HORIZON_ZONE_CLIENTSOCKETMGR_HPP

#include "Libraries/Networking/AcceptSocketMgr.hpp"
#include "Server/Common/System.hpp"
#include "Server/Zone/Session/ZoneSession.hpp"
#include "Server/Zone/Socket/ZoneSocket.hpp"

namespace Horizon
{
namespace Zone
{
/**
 * Manager of client sockets
 */
class ClientSocketMgr : public Horizon::Networking::AcceptSocketMgr<ZoneSocket>, public MainframeComponent
{
	typedef Horizon::Networking::AcceptSocketMgr<ZoneSocket> BaseSocketMgr;
public:
	ClientSocketMgr() : MainframeComponent(Horizon::System::RUNTIME_NETWORKING) { }

	bool start(boost::asio::io_service &io_service, std::string const &listen_ip, uint16_t port, uint32_t threads = 1)
	{
		if (!BaseSocketMgr::start(io_service, listen_ip, port, threads))
			return false;

		bool value = _is_initialized;
		_is_initialized.compare_exchange_strong(value, true);
		return true;
	}

	bool stop()
	{
		if (!BaseSocketMgr::stop_network())
			return false;

		bool value = _is_initialized;
		_is_initialized.compare_exchange_strong(value, false);
		return true;
	}

	virtual bool is_initialized() override { return _is_initialized.load(); }

	virtual void initialize(int segment_number = 1) override { this->initialize(); }
	virtual void finalize(int segment_number = 1) override { stop(); }

	void update_sessions(uint64_t time)
	{
		auto socket_map = get_sockets();

		for (auto s : socket_map) {
			s.second->get_session()->update(time);
		}
	}

protected:
	std::atomic<bool> _is_initialized;
};
}
}

#endif /* HORIZON_ZONE_CLIENTSOCKETMGR_HPP */
