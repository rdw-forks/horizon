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

#ifndef HORIZON_SOCKET_AUTHSOCKET_HPP
#define HORIZON_SOCKET_AUTHSOCKET_HPP

#include "Libraries/Networking/Socket.hpp"

#include <cstdio>
#include <boost/asio/ip/tcp.hpp>
#include <memory>

using boost::asio::ip::tcp;

namespace Horizon
{
namespace Auth
{
class AuthSession;
class AuthSocket : public Horizon::Networking::Socket<AuthSocket>
{
	typedef Socket<AuthSocket> BaseSocket;
public:
	explicit AuthSocket(uint64_t uid);
	explicit AuthSocket(uint64_t uid, std::shared_ptr<tcp::socket> socket);
	~AuthSocket();
	/* */
	virtual void start() override;
	bool update() override;

	/* Session */
	std::shared_ptr<AuthSession> get_session();
	void set_session(std::shared_ptr<AuthSession> session);

	void update_session(uint32_t diff);

protected:
	void read_handler() override;
	void on_close() override;
	void on_error() override;

private:
	std::shared_ptr<AuthSession> _session;
};
}
}

#endif /* HORIZON_SOCKET_AuthSocket_HPP */
