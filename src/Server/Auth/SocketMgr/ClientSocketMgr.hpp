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

#ifndef HORIZON_CLIENTSOCKETMGR_HPP
#define HORIZON_CLIENTSOCKETMGR_HPP
#include "Libraries/Networking/AcceptSocketMgr.hpp"

#include "Server/Auth/Auth.hpp"
#include "Server/Auth/Session/AuthSession.hpp"
#include "Server/Auth/Socket/AuthSocket.hpp"
#include "Server/Common/System.hpp"
#include "Server/Common/Server.hpp"
#include "Server/Common/Configuration/ServerConfiguration.hpp"

namespace Horizon
{
namespace Auth
{
class AuthNetworkThread : public MainframeComponent, public Networking::NetworkThread<AuthSocket>
{
protected:
	void on_socket_removed(std::shared_ptr<AuthSocket> socket) override
	{
		get_resource_manager().add<SEGMENT_PRIORITY_PRIMARY>(socket->get_socket_id(), socket);
	}

	void on_socket_added(std::shared_ptr<AuthSocket> socket) override
	{
		get_resource_manager().remove<SEGMENT_PRIORITY_PRIMARY>(socket->get_socket_id());
	}
public:
	AuthNetworkThread() 
	: MainframeComponent(Horizon::System::RUNTIME_NETWORKING),
	_resource_manager(PrimaryResource(SEGMENT_PRIORITY_PRIMARY, std::make_shared<s_segment_storage<uint64_t, std::shared_ptr<AuthSocket>>>()))
	{
	}

	bool start(int segment_number = 1)
	{
		if (!Networking::NetworkThread<AuthSocket>::start(segment_number))
			return false;

		initialize(segment_number);
		return true;
	}

	void run() override
	{
		Networking::NetworkThread<AuthSocket>::run();
	}

	void update() override
	{
		Networking::NetworkThread<AuthSocket>::update();

		get_system_routine_manager().process_queue();
	}

	virtual void initialize(int segment_number = 1) override 
	{ 
		set_segment_number(segment_number);
		_is_initialized.exchange(true);
	}

	virtual void finalize() override 
	{
		Networking::NetworkThread<AuthSocket>::finalize();

		_is_finalized.exchange(true);
	}

	virtual bool is_initialized() override { return _is_initialized.load(); }
	virtual bool is_finalized() override { return _is_finalized.load(); }

protected:
	std::atomic<bool> _is_initialized{false};
	std::atomic<bool> _is_finalized{false};
	
	using PrimaryResource = SharedPriorityResourceMedium<s_segment_storage<uint64_t, std::shared_ptr<AuthSocket>>>;
	using ResourceManager = SharedPriorityResourceManager<PrimaryResource>;
	ResourceManager _resource_manager;
public:
	ResourceManager &get_resource_manager() { return _resource_manager; }
};
/**
 * Manager of client sockets and initialization of the packet db * @brief Singleton class
 */
class ClientSocketMgr : public Networking::AcceptSocketMgr<AuthSocket, AuthNetworkThread>
{
	typedef Networking::AcceptSocketMgr<AuthSocket, AuthNetworkThread> BaseSocketMgr;
public:
	static ClientSocketMgr *Instance()
	{
		static ClientSocketMgr instance;
		return &instance;
	}
	
	bool start(boost::asio::io_context &io_context, std::string const &listen_ip, uint16_t port, uint32_t threads = MAX_NETWORK_THREADS, bool minimal = false) override;

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

#define sClientSocketMgr Horizon::Auth::ClientSocketMgr::Instance()

#endif /* HORIZON_CLIENTSOCKETMGR_HPP */
