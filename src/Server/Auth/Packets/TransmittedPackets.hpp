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

#ifndef HORIZON_AUTH_TRANSMITTED_PACKETS_HPP
#define HORIZON_AUTH_TRANSMITTED_PACKETS_HPP

#include "Server/Common/Base/NetworkPacket.hpp"
#include "Server/Common/Configuration/Horizon.hpp"

namespace Horizon
{
namespace Auth
{
class AuthSession;
enum {
#if CLIENT_TYPE == 'A' &&  \
	PACKET_VERSION >= 20040000
ID_AC_ACCEPT_LOGIN = 0x0069
#elif CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION >= 20030000
ID_AC_ACCEPT_LOGIN = 0x0069
#elif CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION == 20170228
ID_AC_ACCEPT_LOGIN = 0x0ac4
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION >= 20080000
ID_AC_ACCEPT_LOGIN = 0x0069
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION == 20170228
ID_AC_ACCEPT_LOGIN = 0x0ac4
#elif CLIENT_TYPE == 'S' &&  \
	PACKET_VERSION >= 20030000
ID_AC_ACCEPT_LOGIN = 0x0069
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_AC_ACCEPT_LOGIN = 0x0ac4
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20180000
ID_AC_ACCEPT_LOGIN = 0x0069
#endif
};
/**
 * @brief Main object for the aegis packet: AC_ACCEPT_LOGIN
 *
 */ 
class AC_ACCEPT_LOGIN : public Base::NetworkPacketTransmitter<ZoneSession>
{
public:
	AC_ACCEPT_LOGIN(std::shared_ptr<ZoneSession> s)
	: NetworkPacketTransmitter<ZoneSession>(ID_AC_ACCEPT_LOGIN, s)
	{}
	virtual ~AC_ACCEPT_LOGIN() {}

	void deliver();
	ByteBuffer &serialize();

/* Structure */
};

enum {
#if CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION == 20090701
ID_AC_ACCEPT_LOGIN2 = 0x0276
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION == 20090701
ID_AC_ACCEPT_LOGIN2 = 0x0276
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_AC_ACCEPT_LOGIN2 = 0x0276
#endif
};
/**
 * @brief Main object for the aegis packet: AC_ACCEPT_LOGIN2
 *
 */ 
class AC_ACCEPT_LOGIN2 : public Base::NetworkPacketTransmitter<ZoneSession>
{
public:
	AC_ACCEPT_LOGIN2(std::shared_ptr<ZoneSession> s)
	: NetworkPacketTransmitter<ZoneSession>(ID_AC_ACCEPT_LOGIN2, s)
	{}
	virtual ~AC_ACCEPT_LOGIN2() {}

	void deliver();
	ByteBuffer &serialize();

/* Structure */
};

enum {
#if CLIENT_TYPE == 'A' &&  \
	PACKET_VERSION == 20060109
ID_AC_ACK_EKEY_FAIL_AUTHREFUSE = 0x026a
#elif CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION == 20060109
ID_AC_ACK_EKEY_FAIL_AUTHREFUSE = 0x026a
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION >= 20080000
ID_AC_ACK_EKEY_FAIL_AUTHREFUSE = 0x026a
#elif CLIENT_TYPE == 'S' &&  \
	PACKET_VERSION == 20060109
ID_AC_ACK_EKEY_FAIL_AUTHREFUSE = 0x026a
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_AC_ACK_EKEY_FAIL_AUTHREFUSE = 0x026a
#endif
};
/**
 * @brief Main object for the aegis packet: AC_ACK_EKEY_FAIL_AUTHREFUSE
 *
 */ 
class AC_ACK_EKEY_FAIL_AUTHREFUSE : public Base::NetworkPacketTransmitter<ZoneSession>
{
public:
	AC_ACK_EKEY_FAIL_AUTHREFUSE(std::shared_ptr<ZoneSession> s)
	: NetworkPacketTransmitter<ZoneSession>(ID_AC_ACK_EKEY_FAIL_AUTHREFUSE, s)
	{}
	virtual ~AC_ACK_EKEY_FAIL_AUTHREFUSE() {}

	void deliver();
	ByteBuffer &serialize();

/* Structure */
};

enum {
#if CLIENT_TYPE == 'A' &&  \
	PACKET_VERSION == 20060109
ID_AC_ACK_EKEY_FAIL_INPUTEKEY = 0x026b
#elif CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION == 20060109
ID_AC_ACK_EKEY_FAIL_INPUTEKEY = 0x026b
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION >= 20080000
ID_AC_ACK_EKEY_FAIL_INPUTEKEY = 0x026b
#elif CLIENT_TYPE == 'S' &&  \
	PACKET_VERSION == 20060109
ID_AC_ACK_EKEY_FAIL_INPUTEKEY = 0x026b
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_AC_ACK_EKEY_FAIL_INPUTEKEY = 0x026b
#endif
};
/**
 * @brief Main object for the aegis packet: AC_ACK_EKEY_FAIL_INPUTEKEY
 *
 */ 
class AC_ACK_EKEY_FAIL_INPUTEKEY : public Base::NetworkPacketTransmitter<ZoneSession>
{
public:
	AC_ACK_EKEY_FAIL_INPUTEKEY(std::shared_ptr<ZoneSession> s)
	: NetworkPacketTransmitter<ZoneSession>(ID_AC_ACK_EKEY_FAIL_INPUTEKEY, s)
	{}
	virtual ~AC_ACK_EKEY_FAIL_INPUTEKEY() {}

	void deliver();
	ByteBuffer &serialize();

/* Structure */
};

enum {
#if CLIENT_TYPE == 'A' &&  \
	PACKET_VERSION == 20060109
ID_AC_ACK_EKEY_FAIL_NEEDCARDPASS = 0x026d
#elif CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION == 20060109
ID_AC_ACK_EKEY_FAIL_NEEDCARDPASS = 0x026d
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION >= 20080000
ID_AC_ACK_EKEY_FAIL_NEEDCARDPASS = 0x026d
#elif CLIENT_TYPE == 'S' &&  \
	PACKET_VERSION == 20060109
ID_AC_ACK_EKEY_FAIL_NEEDCARDPASS = 0x026d
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_AC_ACK_EKEY_FAIL_NEEDCARDPASS = 0x026d
#endif
};
/**
 * @brief Main object for the aegis packet: AC_ACK_EKEY_FAIL_NEEDCARDPASS
 *
 */ 
class AC_ACK_EKEY_FAIL_NEEDCARDPASS : public Base::NetworkPacketTransmitter<ZoneSession>
{
public:
	AC_ACK_EKEY_FAIL_NEEDCARDPASS(std::shared_ptr<ZoneSession> s)
	: NetworkPacketTransmitter<ZoneSession>(ID_AC_ACK_EKEY_FAIL_NEEDCARDPASS, s)
	{}
	virtual ~AC_ACK_EKEY_FAIL_NEEDCARDPASS() {}

	void deliver();
	ByteBuffer &serialize();

/* Structure */
};

enum {
#if CLIENT_TYPE == 'A' &&  \
	PACKET_VERSION == 20060109
ID_AC_ACK_EKEY_FAIL_NOTEXIST = 0x0267
#elif CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION == 20060109
ID_AC_ACK_EKEY_FAIL_NOTEXIST = 0x0267
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION >= 20080000
ID_AC_ACK_EKEY_FAIL_NOTEXIST = 0x0267
#elif CLIENT_TYPE == 'S' &&  \
	PACKET_VERSION == 20060109
ID_AC_ACK_EKEY_FAIL_NOTEXIST = 0x0267
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_AC_ACK_EKEY_FAIL_NOTEXIST = 0x0267
#endif
};
/**
 * @brief Main object for the aegis packet: AC_ACK_EKEY_FAIL_NOTEXIST
 *
 */ 
class AC_ACK_EKEY_FAIL_NOTEXIST : public Base::NetworkPacketTransmitter<ZoneSession>
{
public:
	AC_ACK_EKEY_FAIL_NOTEXIST(std::shared_ptr<ZoneSession> s)
	: NetworkPacketTransmitter<ZoneSession>(ID_AC_ACK_EKEY_FAIL_NOTEXIST, s)
	{}
	virtual ~AC_ACK_EKEY_FAIL_NOTEXIST() {}

	void deliver();
	ByteBuffer &serialize();

/* Structure */
};

enum {
#if CLIENT_TYPE == 'A' &&  \
	PACKET_VERSION == 20060109
ID_AC_ACK_EKEY_FAIL_NOTICE = 0x026c
#elif CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION == 20060109
ID_AC_ACK_EKEY_FAIL_NOTICE = 0x026c
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION >= 20080000
ID_AC_ACK_EKEY_FAIL_NOTICE = 0x026c
#elif CLIENT_TYPE == 'S' &&  \
	PACKET_VERSION == 20060109
ID_AC_ACK_EKEY_FAIL_NOTICE = 0x026c
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_AC_ACK_EKEY_FAIL_NOTICE = 0x026c
#endif
};
/**
 * @brief Main object for the aegis packet: AC_ACK_EKEY_FAIL_NOTICE
 *
 */ 
class AC_ACK_EKEY_FAIL_NOTICE : public Base::NetworkPacketTransmitter<ZoneSession>
{
public:
	AC_ACK_EKEY_FAIL_NOTICE(std::shared_ptr<ZoneSession> s)
	: NetworkPacketTransmitter<ZoneSession>(ID_AC_ACK_EKEY_FAIL_NOTICE, s)
	{}
	virtual ~AC_ACK_EKEY_FAIL_NOTICE() {}

	void deliver();
	ByteBuffer &serialize();

/* Structure */
};

enum {
#if CLIENT_TYPE == 'A' &&  \
	PACKET_VERSION == 20060109
ID_AC_ACK_EKEY_FAIL_NOTUSEDEKEY = 0x0269
#elif CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION == 20060109
ID_AC_ACK_EKEY_FAIL_NOTUSEDEKEY = 0x0269
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION >= 20080000
ID_AC_ACK_EKEY_FAIL_NOTUSEDEKEY = 0x0269
#elif CLIENT_TYPE == 'S' &&  \
	PACKET_VERSION == 20060109
ID_AC_ACK_EKEY_FAIL_NOTUSEDEKEY = 0x0269
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_AC_ACK_EKEY_FAIL_NOTUSEDEKEY = 0x0269
#endif
};
/**
 * @brief Main object for the aegis packet: AC_ACK_EKEY_FAIL_NOTUSEDEKEY
 *
 */ 
class AC_ACK_EKEY_FAIL_NOTUSEDEKEY : public Base::NetworkPacketTransmitter<ZoneSession>
{
public:
	AC_ACK_EKEY_FAIL_NOTUSEDEKEY(std::shared_ptr<ZoneSession> s)
	: NetworkPacketTransmitter<ZoneSession>(ID_AC_ACK_EKEY_FAIL_NOTUSEDEKEY, s)
	{}
	virtual ~AC_ACK_EKEY_FAIL_NOTUSEDEKEY() {}

	void deliver();
	ByteBuffer &serialize();

/* Structure */
};

enum {
#if CLIENT_TYPE == 'A' &&  \
	PACKET_VERSION == 20060109
ID_AC_ACK_EKEY_FAIL_NOTUSESEKEY = 0x0268
#elif CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION == 20060109
ID_AC_ACK_EKEY_FAIL_NOTUSESEKEY = 0x0268
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION >= 20080000
ID_AC_ACK_EKEY_FAIL_NOTUSESEKEY = 0x0268
#elif CLIENT_TYPE == 'S' &&  \
	PACKET_VERSION == 20060109
ID_AC_ACK_EKEY_FAIL_NOTUSESEKEY = 0x0268
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_AC_ACK_EKEY_FAIL_NOTUSESEKEY = 0x0268
#endif
};
/**
 * @brief Main object for the aegis packet: AC_ACK_EKEY_FAIL_NOTUSESEKEY
 *
 */ 
class AC_ACK_EKEY_FAIL_NOTUSESEKEY : public Base::NetworkPacketTransmitter<ZoneSession>
{
public:
	AC_ACK_EKEY_FAIL_NOTUSESEKEY(std::shared_ptr<ZoneSession> s)
	: NetworkPacketTransmitter<ZoneSession>(ID_AC_ACK_EKEY_FAIL_NOTUSESEKEY, s)
	{}
	virtual ~AC_ACK_EKEY_FAIL_NOTUSESEKEY() {}

	void deliver();
	ByteBuffer &serialize();

/* Structure */
};

enum {
#if CLIENT_TYPE == 'A' &&  \
	PACKET_VERSION == 20060109
ID_AC_ACK_FIRST_LOGIN = 0x026f
#elif CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION == 20060109
ID_AC_ACK_FIRST_LOGIN = 0x026f
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION >= 20080000
ID_AC_ACK_FIRST_LOGIN = 0x026f
#elif CLIENT_TYPE == 'S' &&  \
	PACKET_VERSION == 20060109
ID_AC_ACK_FIRST_LOGIN = 0x026f
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_AC_ACK_FIRST_LOGIN = 0x026f
#endif
};
/**
 * @brief Main object for the aegis packet: AC_ACK_FIRST_LOGIN
 *
 */ 
class AC_ACK_FIRST_LOGIN : public Base::NetworkPacketTransmitter<ZoneSession>
{
public:
	AC_ACK_FIRST_LOGIN(std::shared_ptr<ZoneSession> s)
	: NetworkPacketTransmitter<ZoneSession>(ID_AC_ACK_FIRST_LOGIN, s)
	{}
	virtual ~AC_ACK_FIRST_LOGIN() {}

	void deliver();
	ByteBuffer &serialize();

/* Structure */
};

enum {
#if CLIENT_TYPE == 'A' &&  \
	PACKET_VERSION == 20050912
ID_AC_ACK_GAME_GUARD = 0x0259
#elif CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION == 20050912
ID_AC_ACK_GAME_GUARD = 0x0259
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION >= 20080000
ID_AC_ACK_GAME_GUARD = 0x0259
#elif CLIENT_TYPE == 'S' &&  \
	PACKET_VERSION == 20050912
ID_AC_ACK_GAME_GUARD = 0x0259
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_AC_ACK_GAME_GUARD = 0x0259
#endif
};
/**
 * @brief Main object for the aegis packet: AC_ACK_GAME_GUARD
 *
 */ 
class AC_ACK_GAME_GUARD : public Base::NetworkPacketTransmitter<ZoneSession>
{
public:
	AC_ACK_GAME_GUARD(std::shared_ptr<ZoneSession> s)
	: NetworkPacketTransmitter<ZoneSession>(ID_AC_ACK_GAME_GUARD, s)
	{}
	virtual ~AC_ACK_GAME_GUARD() {}

	void deliver();
	ByteBuffer &serialize();

/* Structure */
};

enum {
#if CLIENT_TYPE == 'A' &&  \
	PACKET_VERSION >= 20040000
ID_AC_ACK_HASH = 0x01dc
#elif CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION >= 20030000
ID_AC_ACK_HASH = 0x01dc
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION >= 20080000
ID_AC_ACK_HASH = 0x01dc
#elif CLIENT_TYPE == 'S' &&  \
	PACKET_VERSION >= 20030000
ID_AC_ACK_HASH = 0x01dc
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_AC_ACK_HASH = 0x01dc
#endif
};
/**
 * @brief Main object for the aegis packet: AC_ACK_HASH
 *
 */ 
class AC_ACK_HASH : public Base::NetworkPacketTransmitter<ZoneSession>
{
public:
	AC_ACK_HASH(std::shared_ptr<ZoneSession> s)
	: NetworkPacketTransmitter<ZoneSession>(ID_AC_ACK_HASH, s)
	{}
	virtual ~AC_ACK_HASH() {}

	void deliver();
	ByteBuffer &serialize();

/* Structure */
};

enum {
#if CLIENT_TYPE == 'A' &&  \
	PACKET_VERSION == 20060109
ID_AC_ACK_PT_ID_INFO = 0x0272
#elif CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION == 20060109
ID_AC_ACK_PT_ID_INFO = 0x0272
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION >= 20080000
ID_AC_ACK_PT_ID_INFO = 0x0272
#elif CLIENT_TYPE == 'S' &&  \
	PACKET_VERSION == 20060109
ID_AC_ACK_PT_ID_INFO = 0x0272
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_AC_ACK_PT_ID_INFO = 0x0272
#endif
};
/**
 * @brief Main object for the aegis packet: AC_ACK_PT_ID_INFO
 *
 */ 
class AC_ACK_PT_ID_INFO : public Base::NetworkPacketTransmitter<ZoneSession>
{
public:
	AC_ACK_PT_ID_INFO(std::shared_ptr<ZoneSession> s)
	: NetworkPacketTransmitter<ZoneSession>(ID_AC_ACK_PT_ID_INFO, s)
	{}
	virtual ~AC_ACK_PT_ID_INFO() {}

	void deliver();
	ByteBuffer &serialize();

/* Structure */
};

enum {
#if CLIENT_TYPE == 'A' &&  \
	PACKET_VERSION >= 20040000
ID_AC_ASK_PNGAMEROOM = 0x01be
#elif CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION >= 20030000
ID_AC_ASK_PNGAMEROOM = 0x01be
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION >= 20080000
ID_AC_ASK_PNGAMEROOM = 0x01be
#elif CLIENT_TYPE == 'S' &&  \
	PACKET_VERSION >= 20030000
ID_AC_ASK_PNGAMEROOM = 0x01be
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_AC_ASK_PNGAMEROOM = 0x01be
#endif
};
/**
 * @brief Main object for the aegis packet: AC_ASK_PNGAMEROOM
 *
 */ 
class AC_ASK_PNGAMEROOM : public Base::NetworkPacketTransmitter<ZoneSession>
{
public:
	AC_ASK_PNGAMEROOM(std::shared_ptr<ZoneSession> s)
	: NetworkPacketTransmitter<ZoneSession>(ID_AC_ASK_PNGAMEROOM, s)
	{}
	virtual ~AC_ASK_PNGAMEROOM() {}

	void deliver();
	ByteBuffer &serialize();

/* Structure */
};

enum {
#if CLIENT_TYPE == 'A' &&  \
	PACKET_VERSION == 20050628
ID_AC_EVENT_RESULT = 0x023d
#elif CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION == 20050628
ID_AC_EVENT_RESULT = 0x023d
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION >= 20080000
ID_AC_EVENT_RESULT = 0x023d
#elif CLIENT_TYPE == 'S' &&  \
	PACKET_VERSION == 20050628
ID_AC_EVENT_RESULT = 0x023d
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_AC_EVENT_RESULT = 0x023d
#endif
};
/**
 * @brief Main object for the aegis packet: AC_EVENT_RESULT
 *
 */ 
class AC_EVENT_RESULT : public Base::NetworkPacketTransmitter<ZoneSession>
{
public:
	AC_EVENT_RESULT(std::shared_ptr<ZoneSession> s)
	: NetworkPacketTransmitter<ZoneSession>(ID_AC_EVENT_RESULT, s)
	{}
	virtual ~AC_EVENT_RESULT() {}

	void deliver();
	ByteBuffer &serialize();

/* Structure */
};

enum {
#if CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION == 20171213
ID_AC_LOGIN_OTP = 0x0ae3
#elif CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION >= 20190000
ID_AC_LOGIN_OTP = 0x0ad1
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION == 20171213
ID_AC_LOGIN_OTP = 0x0ae3
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION >= 20190000
ID_AC_LOGIN_OTP = 0x0ad1
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION == 20171123
ID_AC_LOGIN_OTP = 0x0ae3
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20190000
ID_AC_LOGIN_OTP = 0x0ad1
#endif
};
/**
 * @brief Main object for the aegis packet: AC_LOGIN_OTP
 *
 */ 
class AC_LOGIN_OTP : public Base::NetworkPacketTransmitter<ZoneSession>
{
public:
	AC_LOGIN_OTP(std::shared_ptr<ZoneSession> s)
	: NetworkPacketTransmitter<ZoneSession>(ID_AC_LOGIN_OTP, s)
	{}
	virtual ~AC_LOGIN_OTP() {}

	void deliver();
	ByteBuffer &serialize();

/* Structure */
};

enum {
#if CLIENT_TYPE == 'A' &&  \
	PACKET_VERSION >= 20040000
ID_AC_NOTIFY_ERROR = 0x01f1
#elif CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION == 20031223
ID_AC_NOTIFY_ERROR = 0x01f1
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION >= 20080000
ID_AC_NOTIFY_ERROR = 0x01f1
#elif CLIENT_TYPE == 'S' &&  \
	PACKET_VERSION == 20031223
ID_AC_NOTIFY_ERROR = 0x01f1
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_AC_NOTIFY_ERROR = 0x01f1
#endif
};
/**
 * @brief Main object for the aegis packet: AC_NOTIFY_ERROR
 *
 */ 
class AC_NOTIFY_ERROR : public Base::NetworkPacketTransmitter<ZoneSession>
{
public:
	AC_NOTIFY_ERROR(std::shared_ptr<ZoneSession> s)
	: NetworkPacketTransmitter<ZoneSession>(ID_AC_NOTIFY_ERROR, s)
	{}
	virtual ~AC_NOTIFY_ERROR() {}

	void deliver();
	ByteBuffer &serialize();

/* Structure */
};

enum {
#if CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION == 20100413
ID_AC_OTP_AUTH_ACK = 0x0823
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION == 20100413
ID_AC_OTP_AUTH_ACK = 0x0823
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_AC_OTP_AUTH_ACK = 0x0823
#endif
};
/**
 * @brief Main object for the aegis packet: AC_OTP_AUTH_ACK
 *
 */ 
class AC_OTP_AUTH_ACK : public Base::NetworkPacketTransmitter<ZoneSession>
{
public:
	AC_OTP_AUTH_ACK(std::shared_ptr<ZoneSession> s)
	: NetworkPacketTransmitter<ZoneSession>(ID_AC_OTP_AUTH_ACK, s)
	{}
	virtual ~AC_OTP_AUTH_ACK() {}

	void deliver();
	ByteBuffer &serialize();

/* Structure */
};

enum {
#if CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION == 20100413
ID_AC_OTP_USER = 0x0821
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION == 20100413
ID_AC_OTP_USER = 0x0821
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_AC_OTP_USER = 0x0821
#endif
};
/**
 * @brief Main object for the aegis packet: AC_OTP_USER
 *
 */ 
class AC_OTP_USER : public Base::NetworkPacketTransmitter<ZoneSession>
{
public:
	AC_OTP_USER(std::shared_ptr<ZoneSession> s)
	: NetworkPacketTransmitter<ZoneSession>(ID_AC_OTP_USER, s)
	{}
	virtual ~AC_OTP_USER() {}

	void deliver();
	ByteBuffer &serialize();

/* Structure */
};

enum {
#if CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION == 20101228
ID_AC_REALNAME_AUTH = 0x08b2
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION == 20101228
ID_AC_REALNAME_AUTH = 0x08b2
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_AC_REALNAME_AUTH = 0x08b2
#endif
};
/**
 * @brief Main object for the aegis packet: AC_REALNAME_AUTH
 *
 */ 
class AC_REALNAME_AUTH : public Base::NetworkPacketTransmitter<ZoneSession>
{
public:
	AC_REALNAME_AUTH(std::shared_ptr<ZoneSession> s)
	: NetworkPacketTransmitter<ZoneSession>(ID_AC_REALNAME_AUTH, s)
	{}
	virtual ~AC_REALNAME_AUTH() {}

	void deliver();
	ByteBuffer &serialize();

/* Structure */
};

enum {
#if CLIENT_TYPE == 'A' &&  \
	PACKET_VERSION >= 20040000
ID_AC_REFUSE_LOGIN = 0x006a
#elif CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION >= 20030000
ID_AC_REFUSE_LOGIN = 0x006a
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION >= 20080000
ID_AC_REFUSE_LOGIN = 0x006a
#elif CLIENT_TYPE == 'S' &&  \
	PACKET_VERSION >= 20030000
ID_AC_REFUSE_LOGIN = 0x006a
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_AC_REFUSE_LOGIN = 0x006a
#endif
};
/**
 * @brief Main object for the aegis packet: AC_REFUSE_LOGIN
 *
 */ 
class AC_REFUSE_LOGIN : public Base::NetworkPacketTransmitter<ZoneSession>
{
public:
	AC_REFUSE_LOGIN(std::shared_ptr<ZoneSession> s)
	: NetworkPacketTransmitter<ZoneSession>(ID_AC_REFUSE_LOGIN, s)
	{}
	virtual ~AC_REFUSE_LOGIN() {}

	void deliver();
	ByteBuffer &serialize();

/* Structure */
};

enum {
#if CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION == 20100615
ID_AC_REFUSE_LOGIN2 = 0x083e
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION == 20100615
ID_AC_REFUSE_LOGIN2 = 0x083e
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_AC_REFUSE_LOGIN2 = 0x083e
#endif
};
/**
 * @brief Main object for the aegis packet: AC_REFUSE_LOGIN2
 *
 */ 
class AC_REFUSE_LOGIN2 : public Base::NetworkPacketTransmitter<ZoneSession>
{
public:
	AC_REFUSE_LOGIN2(std::shared_ptr<ZoneSession> s)
	: NetworkPacketTransmitter<ZoneSession>(ID_AC_REFUSE_LOGIN2, s)
	{}
	virtual ~AC_REFUSE_LOGIN2() {}

	void deliver();
	ByteBuffer &serialize();

/* Structure */
};

enum {
#if CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION == 20130220
ID_AC_REFUSE_LOGIN3 = 0x09a5
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION == 20130220
ID_AC_REFUSE_LOGIN3 = 0x09a5
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_AC_REFUSE_LOGIN3 = 0x09a5
#endif
};
/**
 * @brief Main object for the aegis packet: AC_REFUSE_LOGIN3
 *
 */ 
class AC_REFUSE_LOGIN3 : public Base::NetworkPacketTransmitter<ZoneSession>
{
public:
	AC_REFUSE_LOGIN3(std::shared_ptr<ZoneSession> s)
	: NetworkPacketTransmitter<ZoneSession>(ID_AC_REFUSE_LOGIN3, s)
	{}
	virtual ~AC_REFUSE_LOGIN3() {}

	void deliver();
	ByteBuffer &serialize();

/* Structure */
};

enum {
#if CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION == 20180704
ID_AC_REFUSE_LOGIN4 = 0x0b02
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION == 20180704
ID_AC_REFUSE_LOGIN4 = 0x0b02
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION == 20180627
ID_AC_REFUSE_LOGIN4 = 0x0b02
#endif
};
/**
 * @brief Main object for the aegis packet: AC_REFUSE_LOGIN4
 *
 */ 
class AC_REFUSE_LOGIN4 : public Base::NetworkPacketTransmitter<ZoneSession>
{
public:
	AC_REFUSE_LOGIN4(std::shared_ptr<ZoneSession> s)
	: NetworkPacketTransmitter<ZoneSession>(ID_AC_REFUSE_LOGIN4, s)
	{}
	virtual ~AC_REFUSE_LOGIN4() {}

	void deliver();
	ByteBuffer &serialize();

/* Structure */
};

enum {
#if CLIENT_TYPE == 'A' &&  \
	PACKET_VERSION == 20070227
ID_AC_REQUEST_SECOND_PASSWORD = 0x02ad
#elif CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION == 20070227
ID_AC_REQUEST_SECOND_PASSWORD = 0x02ad
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION >= 20080000
ID_AC_REQUEST_SECOND_PASSWORD = 0x02ad
#elif CLIENT_TYPE == 'S' &&  \
	PACKET_VERSION == 20070227
ID_AC_REQUEST_SECOND_PASSWORD = 0x02ad
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_AC_REQUEST_SECOND_PASSWORD = 0x02ad
#endif
};
/**
 * @brief Main object for the aegis packet: AC_REQUEST_SECOND_PASSWORD
 *
 */ 
class AC_REQUEST_SECOND_PASSWORD : public Base::NetworkPacketTransmitter<ZoneSession>
{
public:
	AC_REQUEST_SECOND_PASSWORD(std::shared_ptr<ZoneSession> s)
	: NetworkPacketTransmitter<ZoneSession>(ID_AC_REQUEST_SECOND_PASSWORD, s)
	{}
	virtual ~AC_REQUEST_SECOND_PASSWORD() {}

	void deliver();
	ByteBuffer &serialize();

/* Structure */
};

enum {
#if CLIENT_TYPE == 'A' &&  \
	PACKET_VERSION == 20060109
ID_AC_REQ_LOGIN_ACCOUNT_INFO = 0x0270
#elif CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION == 20060109
ID_AC_REQ_LOGIN_ACCOUNT_INFO = 0x0270
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION >= 20080000
ID_AC_REQ_LOGIN_ACCOUNT_INFO = 0x0270
#elif CLIENT_TYPE == 'S' &&  \
	PACKET_VERSION == 20060109
ID_AC_REQ_LOGIN_ACCOUNT_INFO = 0x0270
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_AC_REQ_LOGIN_ACCOUNT_INFO = 0x0270
#endif
};
/**
 * @brief Main object for the aegis packet: AC_REQ_LOGIN_ACCOUNT_INFO
 *
 */ 
class AC_REQ_LOGIN_ACCOUNT_INFO : public Base::NetworkPacketTransmitter<ZoneSession>
{
public:
	AC_REQ_LOGIN_ACCOUNT_INFO(std::shared_ptr<ZoneSession> s)
	: NetworkPacketTransmitter<ZoneSession>(ID_AC_REQ_LOGIN_ACCOUNT_INFO, s)
	{}
	virtual ~AC_REQ_LOGIN_ACCOUNT_INFO() {}

	void deliver();
	ByteBuffer &serialize();

/* Structure */
};

enum {
#if CLIENT_TYPE == 'A' &&  \
	PACKET_VERSION == 20060109
ID_AC_REQ_LOGIN_CARDPASS = 0x0263
#elif CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION == 20060109
ID_AC_REQ_LOGIN_CARDPASS = 0x0263
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION >= 20080000
ID_AC_REQ_LOGIN_CARDPASS = 0x0263
#elif CLIENT_TYPE == 'S' &&  \
	PACKET_VERSION == 20060109
ID_AC_REQ_LOGIN_CARDPASS = 0x0263
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_AC_REQ_LOGIN_CARDPASS = 0x0263
#endif
};
/**
 * @brief Main object for the aegis packet: AC_REQ_LOGIN_CARDPASS
 *
 */ 
class AC_REQ_LOGIN_CARDPASS : public Base::NetworkPacketTransmitter<ZoneSession>
{
public:
	AC_REQ_LOGIN_CARDPASS(std::shared_ptr<ZoneSession> s)
	: NetworkPacketTransmitter<ZoneSession>(ID_AC_REQ_LOGIN_CARDPASS, s)
	{}
	virtual ~AC_REQ_LOGIN_CARDPASS() {}

	void deliver();
	ByteBuffer &serialize();

/* Structure */
};

enum {
#if CLIENT_TYPE == 'A' &&  \
	PACKET_VERSION == 20060109
ID_AC_REQ_LOGIN_NEWEKEY = 0x0262
#elif CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION == 20060109
ID_AC_REQ_LOGIN_NEWEKEY = 0x0262
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION >= 20080000
ID_AC_REQ_LOGIN_NEWEKEY = 0x0262
#elif CLIENT_TYPE == 'S' &&  \
	PACKET_VERSION == 20060109
ID_AC_REQ_LOGIN_NEWEKEY = 0x0262
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_AC_REQ_LOGIN_NEWEKEY = 0x0262
#endif
};
/**
 * @brief Main object for the aegis packet: AC_REQ_LOGIN_NEWEKEY
 *
 */ 
class AC_REQ_LOGIN_NEWEKEY : public Base::NetworkPacketTransmitter<ZoneSession>
{
public:
	AC_REQ_LOGIN_NEWEKEY(std::shared_ptr<ZoneSession> s)
	: NetworkPacketTransmitter<ZoneSession>(ID_AC_REQ_LOGIN_NEWEKEY, s)
	{}
	virtual ~AC_REQ_LOGIN_NEWEKEY() {}

	void deliver();
	ByteBuffer &serialize();

/* Structure */
};

enum {
#if CLIENT_TYPE == 'A' &&  \
	PACKET_VERSION == 20060109
ID_AC_REQ_LOGIN_OLDEKEY = 0x0261
#elif CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION == 20060109
ID_AC_REQ_LOGIN_OLDEKEY = 0x0261
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION >= 20080000
ID_AC_REQ_LOGIN_OLDEKEY = 0x0261
#elif CLIENT_TYPE == 'S' &&  \
	PACKET_VERSION == 20060109
ID_AC_REQ_LOGIN_OLDEKEY = 0x0261
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_AC_REQ_LOGIN_OLDEKEY = 0x0261
#endif
};
/**
 * @brief Main object for the aegis packet: AC_REQ_LOGIN_OLDEKEY
 *
 */ 
class AC_REQ_LOGIN_OLDEKEY : public Base::NetworkPacketTransmitter<ZoneSession>
{
public:
	AC_REQ_LOGIN_OLDEKEY(std::shared_ptr<ZoneSession> s)
	: NetworkPacketTransmitter<ZoneSession>(ID_AC_REQ_LOGIN_OLDEKEY, s)
	{}
	virtual ~AC_REQ_LOGIN_OLDEKEY() {}

	void deliver();
	ByteBuffer &serialize();

/* Structure */
};

enum {
#if CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION == 20130130
ID_AC_REQ_MOBILE_OTP = 0x09a2
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION == 20130130
ID_AC_REQ_MOBILE_OTP = 0x09a2
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_AC_REQ_MOBILE_OTP = 0x09a2
#endif
};
/**
 * @brief Main object for the aegis packet: AC_REQ_MOBILE_OTP
 *
 */ 
class AC_REQ_MOBILE_OTP : public Base::NetworkPacketTransmitter<ZoneSession>
{
public:
	AC_REQ_MOBILE_OTP(std::shared_ptr<ZoneSession> s)
	: NetworkPacketTransmitter<ZoneSession>(ID_AC_REQ_MOBILE_OTP, s)
	{}
	virtual ~AC_REQ_MOBILE_OTP() {}

	void deliver();
	ByteBuffer &serialize();

/* Structure */
};

enum {
#if CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION == 20120716
ID_AC_REQ_NEW_USER = 0x098b
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION == 20120716
ID_AC_REQ_NEW_USER = 0x098b
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_AC_REQ_NEW_USER = 0x098b
#endif
};
/**
 * @brief Main object for the aegis packet: AC_REQ_NEW_USER
 *
 */ 
class AC_REQ_NEW_USER : public Base::NetworkPacketTransmitter<ZoneSession>
{
public:
	AC_REQ_NEW_USER(std::shared_ptr<ZoneSession> s)
	: NetworkPacketTransmitter<ZoneSession>(ID_AC_REQ_NEW_USER, s)
	{}
	virtual ~AC_REQ_NEW_USER() {}

	void deliver();
	ByteBuffer &serialize();

/* Structure */
};

enum {
#if CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION == 20111025
ID_AC_SHUTDOWN_INFO = 0x08e4
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION == 20111025
ID_AC_SHUTDOWN_INFO = 0x08e4
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_AC_SHUTDOWN_INFO = 0x08e4
#endif
};
/**
 * @brief Main object for the aegis packet: AC_SHUTDOWN_INFO
 *
 */ 
class AC_SHUTDOWN_INFO : public Base::NetworkPacketTransmitter<ZoneSession>
{
public:
	AC_SHUTDOWN_INFO(std::shared_ptr<ZoneSession> s)
	: NetworkPacketTransmitter<ZoneSession>(ID_AC_SHUTDOWN_INFO, s)
	{}
	virtual ~AC_SHUTDOWN_INFO() {}

	void deliver();
	ByteBuffer &serialize();

/* Structure */
};

enum {
#if CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION == 20120626
ID_AC_SHUTDOWN_NOTIFY = 0x0986
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION == 20120626
ID_AC_SHUTDOWN_NOTIFY = 0x0986
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_AC_SHUTDOWN_NOTIFY = 0x0986
#endif
};
/**
 * @brief Main object for the aegis packet: AC_SHUTDOWN_NOTIFY
 *
 */ 
class AC_SHUTDOWN_NOTIFY : public Base::NetworkPacketTransmitter<ZoneSession>
{
public:
	AC_SHUTDOWN_NOTIFY(std::shared_ptr<ZoneSession> s)
	: NetworkPacketTransmitter<ZoneSession>(ID_AC_SHUTDOWN_NOTIFY, s)
	{}
	virtual ~AC_SHUTDOWN_NOTIFY() {}

	void deliver();
	ByteBuffer &serialize();

/* Structure */
};

enum {
#if CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION == 20100601
ID_AC_SSO_LOGIN_ACK = 0x0826
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION == 20100601
ID_AC_SSO_LOGIN_ACK = 0x0826
#endif
};
/**
 * @brief Main object for the aegis packet: AC_SSO_LOGIN_ACK
 *
 */ 
class AC_SSO_LOGIN_ACK : public Base::NetworkPacketTransmitter<ZoneSession>
{
public:
	AC_SSO_LOGIN_ACK(std::shared_ptr<ZoneSession> s)
	: NetworkPacketTransmitter<ZoneSession>(ID_AC_SSO_LOGIN_ACK, s)
	{}
	virtual ~AC_SSO_LOGIN_ACK() {}

	void deliver();
	ByteBuffer &serialize();

/* Structure */
};

}
 /* namespace Auth */}
 /* namespace Horizon */
