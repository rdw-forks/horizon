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
