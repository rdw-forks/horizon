/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 * Copyright (c) 2020- Horizon Dev Team.
 *
 * Base Author - Sagun Khosla. (sagunxp@gmail.com)
 *
 * This is proprietary software. Unauthorized copying,
 * distribution, or modification of this file, via any
 * medium, is strictly prohibited. All rights reserved.
 **************************************************/

#ifndef HORIZON_CLIENTINTERFACE_HPP
#define HORIZON_CLIENTINTERFACE_HPP

#include <memory>

namespace Horizon
{

template <typename SessionType>
class ClientInterface
{
public:
	ClientInterface(std::shared_ptr<SessionType> s) : _session(s) { }
	~ClientInterface() { }

	std::shared_ptr<SessionType> get_session() { return _session.lock(); }
	void set_session(std::shared_ptr<SessionType> s) { _session = s; }

private:
	std::weak_ptr<SessionType> _session;
};

}

#endif /* HORIZON_CLIENTINTERFACE_HPP */
