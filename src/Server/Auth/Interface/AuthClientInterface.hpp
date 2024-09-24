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

#ifndef HORIZON_AUTHCLIENTINTERFACE_HPP
#define HORIZON_AUTHCLIENTINTERFACE_HPP

#include "Server/Common/Interfaces/ClientInterface.hpp"
#include <string>

namespace Horizon
{
namespace Auth
{
class AuthSession;
class AuthClientInterface : public ClientInterface<AuthSession>
{
public:
	AuthClientInterface(std::shared_ptr<AuthSession> session);
	~AuthClientInterface();
	
	bool process_login(std::string username, std::string hash, uint16_t version, uint16_t client_type);
	bool client_login_otp_response();
};
}
}

#endif /* HORIZON_AUTHCLIENTINTERFACE_HPP */
