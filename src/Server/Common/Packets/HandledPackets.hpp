/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 * Copyright (c) 2023 Horizon Dev Team.
 *
 * Base Author - Sephus. (sagunxp@gmail.com)
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

#ifndef HORIZON_COMMON_HANDLED_PACKETS_HPP
#define HORIZON_COMMON_HANDLED_PACKETS_HPP

#include "Server/Common/Base/NetworkPacket.hpp"
#include "Server/Common/Configuration/Horizon.hpp"

namespace Horizon
{
namespace Common
{
class CommonSession;
enum {
#if CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION >= 20130605
ID_CS_LOGIN_QUERY = 0x09c5
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION >= 20130605
ID_CS_LOGIN_QUERY = 0x09c5
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_CS_LOGIN_QUERY = 0x09c5
#else
ID_CS_LOGIN_QUERY = 0x0000 // Disabled
#endif
};
/**
 * @brief Main object for the aegis packet: CS_LOGIN_QUERY
 *
 */ 
class CS_LOGIN_QUERY : public Base::NetworkPacketHandler<CommonSession>
{
public:
	CS_LOGIN_QUERY(std::shared_ptr<CommonSession> s)
	: NetworkPacketHandler<CommonSession>(ID_CS_LOGIN_QUERY, s)
	{}
	virtual ~CS_LOGIN_QUERY() {}

	void handle(ByteBuffer &&buf);
	void deserialize(ByteBuffer &buf);

/* Structure */
};

enum {
#if CLIENT_TYPE == 'A' &&  \
	PACKET_VERSION >= 20040000
ID_CS_REQ_ENCRYPTION = 0x01c6
#elif CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION >= 20030000
ID_CS_REQ_ENCRYPTION = 0x01c6
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION >= 20080000
ID_CS_REQ_ENCRYPTION = 0x01c6
#elif CLIENT_TYPE == 'S' &&  \
	PACKET_VERSION >= 20030000
ID_CS_REQ_ENCRYPTION = 0x01c6
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_CS_REQ_ENCRYPTION = 0x01c6
#else
ID_CS_REQ_ENCRYPTION = 0x0000 // Disabled
#endif
};
/**
 * @brief Main object for the aegis packet: CS_REQ_ENCRYPTION
 *
 */ 
class CS_REQ_ENCRYPTION : public Base::NetworkPacketHandler<CommonSession>
{
public:
	CS_REQ_ENCRYPTION(std::shared_ptr<CommonSession> s)
	: NetworkPacketHandler<CommonSession>(ID_CS_REQ_ENCRYPTION, s)
	{}
	virtual ~CS_REQ_ENCRYPTION() {}

	void handle(ByteBuffer &&buf);
	void deserialize(ByteBuffer &buf);

/* Structure */
};

} /* namespace Common */
} /* namespace Horizon */
#endif /* HORIZON_COMMON_TRANSMITTED_PACKETS_HPP */
