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

#ifndef HORIZON_CHAR_CLIENTSOCKETMGR_HPP
#define HORIZON_CHAR_CLIENTSOCKETMGR_HPP
#include "Libraries/Networking/AcceptSocketMgr.hpp"

#include "Server/Char/Char.hpp"
#include "Server/Char/Session/CharSession.hpp"
#include "Server/Char/Socket/CharSocket.hpp"
#include "Server/Common/Configuration/ServerConfiguration.hpp"

namespace Horizon
{
namespace Char
{
	
class CharNetworkThread : public MainframeComponent, public Networking::NetworkThread<CharSocket>
{
protected:
	using resource_priority_type = MainframeSegmentResourceMediator::mainframe_segment_priority_type;
	using resource_category_type = MainframeSegmentResourceMediator::mainframe_segment_resource_category;

	void on_socket_removed(std::shared_ptr<CharSocket> socket) override
	{
		get_resource_mediator().add_resource_value(resource_priority_type::SEGMENT_PRIORITY_PRIMARY, socket->get_socket_id());
	}

	void on_socket_added(std::shared_ptr<CharSocket> socket) override
	{
		get_resource_mediator().remove_resource_value(resource_priority_type::SEGMENT_PRIORITY_PRIMARY, socket->get_socket_id());
	}
public:
	CharNetworkThread() : MainframeComponent(Horizon::System::RUNTIME_NETWORKING) { }

	bool start(int segment_number = 1)
	{
		if (!Networking::NetworkThread<CharSocket>::start(segment_number))
			return false;

		initialize(segment_number);
		return true;
	}

	void run() override
	{
		Networking::NetworkThread<CharSocket>::run();
	}

	void update() override
	{
		Networking::NetworkThread<CharSocket>::update();

		get_system_routine_manager().process_queue();
	}

	virtual void initialize(int segment_number = 1) override 
	{
		get_resource_mediator().register_resource(resource_priority_type::SEGMENT_PRIORITY_PRIMARY, resource_category_type::SEGMENT_RESOURCE_SOCKET_ID);

		bool value = _is_initialized;
		_is_initialized.compare_exchange_strong(value, true);
		set_segment_number(segment_number);
	}

	virtual void finalize() override 
	{
		Networking::NetworkThread<CharSocket>::finalize();
		bool value = _is_initialized;
		_is_initialized.compare_exchange_strong(value, false); 
	}

	virtual bool is_initialized() override { return _is_initialized.load(); }
protected:
	std::atomic<bool> _is_initialized;
};

/**
 * Manager of client sockets and initialization of the packet db * @brief Singleton class
 */
class ClientSocketMgr : public Horizon::Networking::AcceptSocketMgr<CharSocket, CharNetworkThread>
{
	typedef Horizon::Networking::AcceptSocketMgr<CharSocket, CharNetworkThread> BaseSocketMgr;
public:
	static ClientSocketMgr *Instance()
	{
		static ClientSocketMgr instance;
		return &instance;
	}

	bool start(boost::asio::io_context &io_context, std::string const &listen_ip, uint16_t port, uint32_t threads = 1, bool minimal = false)
	{
		if (!BaseSocketMgr::start(io_context, listen_ip, port, threads, minimal))
			return false;

		for (auto i : get_thread_map()) {
			sChar->register_component(Horizon::System::RUNTIME_NETWORKING, (std::dynamic_pointer_cast<CharNetworkThread>(i.second->shared_from_this())));
		}
		return true;
	}

	bool stop()
	{
		if (!BaseSocketMgr::stop_network())
			return false;
		return true;
	}

	void update_sessions(uint64_t time)
	{
		auto socket_map = get_sockets();

		for (auto s : socket_map) {
			if (s.second->get_session() != nullptr)
				s.second->get_session()->update(time);
		}
	}
};
}
}
#define sClientSocketMgr Horizon::Char::ClientSocketMgr::Instance()
#endif /* HORIZON_CHAR_CLIENTSOCKETMGR_HPP */
