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
