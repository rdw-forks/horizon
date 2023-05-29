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

#ifndef HORIZON_COMMON_TRANSMITTED_PACKETS_HPP
#define HORIZON_COMMON_TRANSMITTED_PACKETS_HPP

#include "Server/Common/Base/NetworkPacket.hpp"
#include "Server/Common/Configuration/Horizon.hpp"

namespace Horizon
{
namespace Common
{
class CommonSession;
enum {
#if CLIENT_TYPE == 'A' &&  \
	PACKET_VERSION == 20080624
ID_AHC_GAME_GUARD = 0x03dd
#elif CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION == 20080624
ID_AHC_GAME_GUARD = 0x03dd
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION >= 20080000
ID_AHC_GAME_GUARD = 0x03dd
#elif CLIENT_TYPE == 'S' &&  \
	PACKET_VERSION == 20080624
ID_AHC_GAME_GUARD = 0x03dd
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_AHC_GAME_GUARD = 0x03dd
#endif
};
/**
 * @brief Main object for the aegis packet: AHC_GAME_GUARD
 *
 */ 
class AHC_GAME_GUARD : public Base::NetworkPacketTransmitter<ZoneSession>
{
public:
	AHC_GAME_GUARD(std::shared_ptr<ZoneSession> s)
	: NetworkPacketTransmitter<ZoneSession>(ID_AHC_GAME_GUARD, s)
	{}
	virtual ~AHC_GAME_GUARD() {}

	void deliver();
	ByteBuffer &serialize();

/* Structure */
};

enum {
#if CLIENT_TYPE == 'A' &&  \
	PACKET_VERSION == 20080624
ID_CAH_ACK_GAME_GUARD = 0x03de
#elif CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION == 20080624
ID_CAH_ACK_GAME_GUARD = 0x03de
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION >= 20080000
ID_CAH_ACK_GAME_GUARD = 0x03de
#elif CLIENT_TYPE == 'S' &&  \
	PACKET_VERSION == 20080624
ID_CAH_ACK_GAME_GUARD = 0x03de
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_CAH_ACK_GAME_GUARD = 0x03de
#endif
};
/**
 * @brief Main object for the aegis packet: CAH_ACK_GAME_GUARD
 *
 */ 
class CAH_ACK_GAME_GUARD : public Base::NetworkPacketTransmitter<ZoneSession>
{
public:
	CAH_ACK_GAME_GUARD(std::shared_ptr<ZoneSession> s)
	: NetworkPacketTransmitter<ZoneSession>(ID_CAH_ACK_GAME_GUARD, s)
	{}
	virtual ~CAH_ACK_GAME_GUARD() {}

	void deliver();
	ByteBuffer &serialize();

/* Structure */
};

enum {
#if CLIENT_TYPE == 'A' &&  \
	PACKET_VERSION >= 20040000
ID_SC_ACK_ENCRYPTION = 0x01c7
#elif CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION >= 20030000
ID_SC_ACK_ENCRYPTION = 0x01c7
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION >= 20080000
ID_SC_ACK_ENCRYPTION = 0x01c7
#elif CLIENT_TYPE == 'S' &&  \
	PACKET_VERSION >= 20030000
ID_SC_ACK_ENCRYPTION = 0x01c7
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_SC_ACK_ENCRYPTION = 0x01c7
#endif
};
/**
 * @brief Main object for the aegis packet: SC_ACK_ENCRYPTION
 *
 */ 
class SC_ACK_ENCRYPTION : public Base::NetworkPacketTransmitter<ZoneSession>
{
public:
	SC_ACK_ENCRYPTION(std::shared_ptr<ZoneSession> s)
	: NetworkPacketTransmitter<ZoneSession>(ID_SC_ACK_ENCRYPTION, s)
	{}
	virtual ~SC_ACK_ENCRYPTION() {}

	void deliver();
	ByteBuffer &serialize();

/* Structure */
};

enum {
#if CLIENT_TYPE == 'A' &&  \
	PACKET_VERSION >= 20040000
ID_SC_BILLING_INFO = 0x01b5
#elif CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION >= 20030000
ID_SC_BILLING_INFO = 0x01b5
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION >= 20080000
ID_SC_BILLING_INFO = 0x01b5
#elif CLIENT_TYPE == 'S' &&  \
	PACKET_VERSION >= 20030000
ID_SC_BILLING_INFO = 0x01b5
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_SC_BILLING_INFO = 0x01b5
#endif
};
/**
 * @brief Main object for the aegis packet: SC_BILLING_INFO
 *
 */ 
class SC_BILLING_INFO : public Base::NetworkPacketTransmitter<ZoneSession>
{
public:
	SC_BILLING_INFO(std::shared_ptr<ZoneSession> s)
	: NetworkPacketTransmitter<ZoneSession>(ID_SC_BILLING_INFO, s)
	{}
	virtual ~SC_BILLING_INFO() {}

	void deliver();
	ByteBuffer &serialize();

/* Structure */
};

enum {
#if CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION == 20130605
ID_SC_LOGIN_ANSWER = 0x09c6
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION == 20130605
ID_SC_LOGIN_ANSWER = 0x09c6
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_SC_LOGIN_ANSWER = 0x09c6
#endif
};
/**
 * @brief Main object for the aegis packet: SC_LOGIN_ANSWER
 *
 */ 
class SC_LOGIN_ANSWER : public Base::NetworkPacketTransmitter<ZoneSession>
{
public:
	SC_LOGIN_ANSWER(std::shared_ptr<ZoneSession> s)
	: NetworkPacketTransmitter<ZoneSession>(ID_SC_LOGIN_ANSWER, s)
	{}
	virtual ~SC_LOGIN_ANSWER() {}

	void deliver();
	ByteBuffer &serialize();

/* Structure */
};

enum {
#if CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION == 20131030
ID_SC_LOGIN_ANSWER_WITH_ID = 0x09e0
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION == 20131030
ID_SC_LOGIN_ANSWER_WITH_ID = 0x09e0
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_SC_LOGIN_ANSWER_WITH_ID = 0x09e0
#endif
};
/**
 * @brief Main object for the aegis packet: SC_LOGIN_ANSWER_WITH_ID
 *
 */ 
class SC_LOGIN_ANSWER_WITH_ID : public Base::NetworkPacketTransmitter<ZoneSession>
{
public:
	SC_LOGIN_ANSWER_WITH_ID(std::shared_ptr<ZoneSession> s)
	: NetworkPacketTransmitter<ZoneSession>(ID_SC_LOGIN_ANSWER_WITH_ID, s)
	{}
	virtual ~SC_LOGIN_ANSWER_WITH_ID() {}

	void deliver();
	ByteBuffer &serialize();

/* Structure */
};

enum {
#if CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION == 20130612
ID_SC_LOGIN_ERROR = 0x09c7
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION == 20130612
ID_SC_LOGIN_ERROR = 0x09c7
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_SC_LOGIN_ERROR = 0x09c7
#endif
};
/**
 * @brief Main object for the aegis packet: SC_LOGIN_ERROR
 *
 */ 
class SC_LOGIN_ERROR : public Base::NetworkPacketTransmitter<ZoneSession>
{
public:
	SC_LOGIN_ERROR(std::shared_ptr<ZoneSession> s)
	: NetworkPacketTransmitter<ZoneSession>(ID_SC_LOGIN_ERROR, s)
	{}
	virtual ~SC_LOGIN_ERROR() {}

	void deliver();
	ByteBuffer &serialize();

/* Structure */
};

enum {
#if CLIENT_TYPE == 'A' &&  \
	PACKET_VERSION >= 20040000
ID_SC_NOTIFY_BAN = 0x0081
#elif CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION >= 20030000
ID_SC_NOTIFY_BAN = 0x0081
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION >= 20080000
ID_SC_NOTIFY_BAN = 0x0081
#elif CLIENT_TYPE == 'S' &&  \
	PACKET_VERSION >= 20030000
ID_SC_NOTIFY_BAN = 0x0081
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_SC_NOTIFY_BAN = 0x0081
#endif
};
/**
 * @brief Main object for the aegis packet: SC_NOTIFY_BAN
 *
 */ 
class SC_NOTIFY_BAN : public Base::NetworkPacketTransmitter<ZoneSession>
{
public:
	SC_NOTIFY_BAN(std::shared_ptr<ZoneSession> s)
	: NetworkPacketTransmitter<ZoneSession>(ID_SC_NOTIFY_BAN, s)
	{}
	virtual ~SC_NOTIFY_BAN() {}

	void deliver();
	ByteBuffer &serialize();

/* Structure */
};

enum {
#if CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION == 20130612
ID_SC_SOCT = 0x09c9
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION == 20130612
ID_SC_SOCT = 0x09c9
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_SC_SOCT = 0x09c9
#endif
};
/**
 * @brief Main object for the aegis packet: SC_SOCT
 *
 */ 
class SC_SOCT : public Base::NetworkPacketTransmitter<ZoneSession>
{
public:
	SC_SOCT(std::shared_ptr<ZoneSession> s)
	: NetworkPacketTransmitter<ZoneSession>(ID_SC_SOCT, s)
	{}
	virtual ~SC_SOCT() {}

	void deliver();
	ByteBuffer &serialize();

/* Structure */
};

}
 /* namespace Common */}
 /* namespace Horizon */
