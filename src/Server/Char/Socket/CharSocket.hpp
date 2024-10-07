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

#ifndef HORIZON_CHAR_CHARSOCKET_HPP
#define HORIZON_CHAR_CHARSOCKET_HPP

#include "Libraries/Networking/Socket.hpp"

#include <memory>
#include <cstdio>
#include <boost/asio/ip/tcp.hpp>

using boost::asio::ip::tcp;

namespace Horizon
{
namespace Char
{
class CharSession;
class CharSocket : public Horizon::Networking::Socket<CharSocket>
{
	typedef Socket<CharSocket> BaseSocket;
public:
	explicit CharSocket(uint64_t uid, std::shared_ptr<tcp::socket> socket);
	~CharSocket();

	/* */
	void start() override;
	bool update() override;

	/* Auth Session */
	std::shared_ptr<CharSession> get_session();
	void set_session(std::shared_ptr<CharSession> session);

	void update_session(uint32_t diff);

protected:
	void read_handler() override;
	void on_close() override;
	void on_error() override;
	/* */
private:
	std::shared_ptr<CharSession> _session;
};
}
}

#endif //HORIZON_CHAR_CHARSOCKET_HPP
