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

#ifndef HORIZON_CHAR_TRANSMITTED_PACKETS_HPP
#define HORIZON_CHAR_TRANSMITTED_PACKETS_HPP

#include "Server/Common/Base/NetworkPacket.hpp"
#include "Server/Common/Configuration/Horizon.hpp"

namespace Horizon
{
namespace Char
{
class CharSession;
enum {
#if CLIENT_TYPE == 'A' &&  \
	PACKET_VERSION >= 20040000
ID_HC_ACCEPT_DELETECHAR = 0x006f
#elif CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION >= 20030000
ID_HC_ACCEPT_DELETECHAR = 0x006f
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION >= 20080000
ID_HC_ACCEPT_DELETECHAR = 0x006f
#elif CLIENT_TYPE == 'S' &&  \
	PACKET_VERSION >= 20030000
ID_HC_ACCEPT_DELETECHAR = 0x006f
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_HC_ACCEPT_DELETECHAR = 0x006f
#endif
};
/**
 * @brief Main object for the aegis packet: HC_ACCEPT_DELETECHAR
 *
 */ 
class HC_ACCEPT_DELETECHAR : public Base::NetworkPacketTransmitter<ZoneSession>
{
public:
	HC_ACCEPT_DELETECHAR(std::shared_ptr<ZoneSession> s)
	: NetworkPacketTransmitter<ZoneSession>(ID_HC_ACCEPT_DELETECHAR, s)
	{}
	virtual ~HC_ACCEPT_DELETECHAR() {}

	void deliver();
	ByteBuffer &serialize();

/* Structure */
};

enum {
#if CLIENT_TYPE == 'A' &&  \
	PACKET_VERSION >= 20040000
ID_HC_ACCEPT_ENTER = 0x006b
#elif CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION >= 20030000
ID_HC_ACCEPT_ENTER = 0x006b
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION >= 20080000
ID_HC_ACCEPT_ENTER = 0x006b
#elif CLIENT_TYPE == 'S' &&  \
	PACKET_VERSION >= 20030000
ID_HC_ACCEPT_ENTER = 0x006b
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_HC_ACCEPT_ENTER = 0x006b
#endif
};
/**
 * @brief Main object for the aegis packet: HC_ACCEPT_ENTER
 *
 */ 
class HC_ACCEPT_ENTER : public Base::NetworkPacketTransmitter<ZoneSession>
{
public:
	HC_ACCEPT_ENTER(std::shared_ptr<ZoneSession> s)
	: NetworkPacketTransmitter<ZoneSession>(ID_HC_ACCEPT_ENTER, s)
	{}
	virtual ~HC_ACCEPT_ENTER() {}

	void deliver();
	ByteBuffer &serialize();

/* Structure */
};

enum {
#if CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION == 20101221
ID_HC_ACCEPT_ENTER2 = 0x082d
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION == 20101221
ID_HC_ACCEPT_ENTER2 = 0x082d
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_HC_ACCEPT_ENTER2 = 0x082d
#endif
};
/**
 * @brief Main object for the aegis packet: HC_ACCEPT_ENTER2
 *
 */ 
class HC_ACCEPT_ENTER2 : public Base::NetworkPacketTransmitter<ZoneSession>
{
public:
	HC_ACCEPT_ENTER2(std::shared_ptr<ZoneSession> s)
	: NetworkPacketTransmitter<ZoneSession>(ID_HC_ACCEPT_ENTER2, s)
	{}
	virtual ~HC_ACCEPT_ENTER2() {}

	void deliver();
	ByteBuffer &serialize();

/* Structure */
};

enum {
#if CLIENT_TYPE == 'A' &&  \
	PACKET_VERSION >= 20040000
ID_HC_ACCEPT_MAKECHAR = 0x006d
#elif CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION >= 20030000
ID_HC_ACCEPT_MAKECHAR = 0x006d
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION == 20081217
ID_HC_ACCEPT_MAKECHAR = 0x006d
#elif CLIENT_TYPE == 'S' &&  \
	PACKET_VERSION >= 20030000
ID_HC_ACCEPT_MAKECHAR = 0x006d
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_HC_ACCEPT_MAKECHAR = 0x006d
#endif
};
/**
 * @brief Main object for the aegis packet: HC_ACCEPT_MAKECHAR
 *
 */ 
class HC_ACCEPT_MAKECHAR : public Base::NetworkPacketTransmitter<ZoneSession>
{
public:
	HC_ACCEPT_MAKECHAR(std::shared_ptr<ZoneSession> s)
	: NetworkPacketTransmitter<ZoneSession>(ID_HC_ACCEPT_MAKECHAR, s)
	{}
	virtual ~HC_ACCEPT_MAKECHAR() {}

	void deliver();
	ByteBuffer &serialize();

/* Structure */
};

enum {
#if CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION == 20110906
ID_HC_ACK_CHANGE_CHARACTER_SLOT = 0x08d5
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION == 20110906
ID_HC_ACK_CHANGE_CHARACTER_SLOT = 0x08d5
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_HC_ACK_CHANGE_CHARACTER_SLOT = 0x08d5
#endif
};
/**
 * @brief Main object for the aegis packet: HC_ACK_CHANGE_CHARACTER_SLOT
 *
 */ 
class HC_ACK_CHANGE_CHARACTER_SLOT : public Base::NetworkPacketTransmitter<ZoneSession>
{
public:
	HC_ACK_CHANGE_CHARACTER_SLOT(std::shared_ptr<ZoneSession> s)
	: NetworkPacketTransmitter<ZoneSession>(ID_HC_ACK_CHANGE_CHARACTER_SLOT, s)
	{}
	virtual ~HC_ACK_CHANGE_CHARACTER_SLOT() {}

	void deliver();
	ByteBuffer &serialize();

/* Structure */
};

enum {
#if CLIENT_TYPE == 'A' &&  \
	PACKET_VERSION == 20061030
ID_HC_ACK_CHANGE_CHARNAME = 0x0290
#elif CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION == 20061030
ID_HC_ACK_CHANGE_CHARNAME = 0x0290
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION >= 20080000
ID_HC_ACK_CHANGE_CHARNAME = 0x0290
#elif CLIENT_TYPE == 'S' &&  \
	PACKET_VERSION == 20061023
ID_HC_ACK_CHANGE_CHARNAME = 0x0290
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_HC_ACK_CHANGE_CHARNAME = 0x0290
#endif
};
/**
 * @brief Main object for the aegis packet: HC_ACK_CHANGE_CHARNAME
 *
 */ 
class HC_ACK_CHANGE_CHARNAME : public Base::NetworkPacketTransmitter<ZoneSession>
{
public:
	HC_ACK_CHANGE_CHARNAME(std::shared_ptr<ZoneSession> s)
	: NetworkPacketTransmitter<ZoneSession>(ID_HC_ACK_CHANGE_CHARNAME, s)
	{}
	virtual ~HC_ACK_CHANGE_CHARNAME() {}

	void deliver();
	ByteBuffer &serialize();

/* Structure */
};

enum {
#if CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION == 20121024
ID_HC_ACK_CHARINFO_PER_PAGE = 0x099d
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION == 20121024
ID_HC_ACK_CHARINFO_PER_PAGE = 0x099d
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_HC_ACK_CHARINFO_PER_PAGE = 0x099d
#endif
};
/**
 * @brief Main object for the aegis packet: HC_ACK_CHARINFO_PER_PAGE
 *
 */ 
class HC_ACK_CHARINFO_PER_PAGE : public Base::NetworkPacketTransmitter<ZoneSession>
{
public:
	HC_ACK_CHARINFO_PER_PAGE(std::shared_ptr<ZoneSession> s)
	: NetworkPacketTransmitter<ZoneSession>(ID_HC_ACK_CHARINFO_PER_PAGE, s)
	{}
	virtual ~HC_ACK_CHARINFO_PER_PAGE() {}

	void deliver();
	ByteBuffer &serialize();

/* Structure */
};

enum {
#if CLIENT_TYPE == 'A' &&  \
	PACKET_VERSION == 20061030
ID_HC_ACK_IS_VALID_CHARNAME = 0x028e
#elif CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION == 20061030
ID_HC_ACK_IS_VALID_CHARNAME = 0x028e
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION >= 20080000
ID_HC_ACK_IS_VALID_CHARNAME = 0x028e
#elif CLIENT_TYPE == 'S' &&  \
	PACKET_VERSION == 20061023
ID_HC_ACK_IS_VALID_CHARNAME = 0x028e
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_HC_ACK_IS_VALID_CHARNAME = 0x028e
#endif
};
/**
 * @brief Main object for the aegis packet: HC_ACK_IS_VALID_CHARNAME
 *
 */ 
class HC_ACK_IS_VALID_CHARNAME : public Base::NetworkPacketTransmitter<ZoneSession>
{
public:
	HC_ACK_IS_VALID_CHARNAME(std::shared_ptr<ZoneSession> s)
	: NetworkPacketTransmitter<ZoneSession>(ID_HC_ACK_IS_VALID_CHARNAME, s)
	{}
	virtual ~HC_ACK_IS_VALID_CHARNAME() {}

	void deliver();
	ByteBuffer &serialize();

/* Structure */
};

enum {
#if CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION == 20110228
ID_HC_AVAILABLE_SECOND_PASSWD = 0x08c6
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION == 20110228
ID_HC_AVAILABLE_SECOND_PASSWD = 0x08c6
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_HC_AVAILABLE_SECOND_PASSWD = 0x08c6
#endif
};
/**
 * @brief Main object for the aegis packet: HC_AVAILABLE_SECOND_PASSWD
 *
 */ 
class HC_AVAILABLE_SECOND_PASSWD : public Base::NetworkPacketTransmitter<ZoneSession>
{
public:
	HC_AVAILABLE_SECOND_PASSWD(std::shared_ptr<ZoneSession> s)
	: NetworkPacketTransmitter<ZoneSession>(ID_HC_AVAILABLE_SECOND_PASSWD, s)
	{}
	virtual ~HC_AVAILABLE_SECOND_PASSWD() {}

	void deliver();
	ByteBuffer &serialize();

/* Structure */
};

enum {
#if CLIENT_TYPE == 'A' &&  \
	PACKET_VERSION >= 20040000
ID_HC_BLOCK_CHARACTER = 0x020d
#elif CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION == 20040621
ID_HC_BLOCK_CHARACTER = 0x020d
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION >= 20080000
ID_HC_BLOCK_CHARACTER = 0x020d
#elif CLIENT_TYPE == 'S' &&  \
	PACKET_VERSION == 20040621
ID_HC_BLOCK_CHARACTER = 0x020d
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_HC_BLOCK_CHARACTER = 0x020d
#endif
};
/**
 * @brief Main object for the aegis packet: HC_BLOCK_CHARACTER
 *
 */ 
class HC_BLOCK_CHARACTER : public Base::NetworkPacketTransmitter<ZoneSession>
{
public:
	HC_BLOCK_CHARACTER(std::shared_ptr<ZoneSession> s)
	: NetworkPacketTransmitter<ZoneSession>(ID_HC_BLOCK_CHARACTER, s)
	{}
	virtual ~HC_BLOCK_CHARACTER() {}

	void deliver();
	ByteBuffer &serialize();

/* Structure */
};

enum {
#if CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION == 20090225
ID_HC_CHARACTER_LIST = 0x0448
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION == 20090226
ID_HC_CHARACTER_LIST = 0x0448
#elif CLIENT_TYPE == 'S' &&  \
	PACKET_VERSION == 20090225
ID_HC_CHARACTER_LIST = 0x0448
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_HC_CHARACTER_LIST = 0x0448
#endif
};
/**
 * @brief Main object for the aegis packet: HC_CHARACTER_LIST
 *
 */ 
class HC_CHARACTER_LIST : public Base::NetworkPacketTransmitter<ZoneSession>
{
public:
	HC_CHARACTER_LIST(std::shared_ptr<ZoneSession> s)
	: NetworkPacketTransmitter<ZoneSession>(ID_HC_CHARACTER_LIST, s)
	{}
	virtual ~HC_CHARACTER_LIST() {}

	void deliver();
	ByteBuffer &serialize();

/* Structure */
};

enum {
#if CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION == 20121212
ID_HC_CHARLIST_NOTIFY = 0x09a0
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION == 20121212
ID_HC_CHARLIST_NOTIFY = 0x09a0
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_HC_CHARLIST_NOTIFY = 0x09a0
#endif
};
/**
 * @brief Main object for the aegis packet: HC_CHARLIST_NOTIFY
 *
 */ 
class HC_CHARLIST_NOTIFY : public Base::NetworkPacketTransmitter<ZoneSession>
{
public:
	HC_CHARLIST_NOTIFY(std::shared_ptr<ZoneSession> s)
	: NetworkPacketTransmitter<ZoneSession>(ID_HC_CHARLIST_NOTIFY, s)
	{}
	virtual ~HC_CHARLIST_NOTIFY() {}

	void deliver();
	ByteBuffer &serialize();

/* Structure */
};

enum {
#if CLIENT_TYPE == 'A' &&  \
	PACKET_VERSION == 20061030
ID_HC_CHARNOTBEENSELECTED = 0x028b
#elif CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION == 20061030
ID_HC_CHARNOTBEENSELECTED = 0x028b
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION >= 20080000
ID_HC_CHARNOTBEENSELECTED = 0x028b
#elif CLIENT_TYPE == 'S' &&  \
	PACKET_VERSION == 20061023
ID_HC_CHARNOTBEENSELECTED = 0x028b
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_HC_CHARNOTBEENSELECTED = 0x028b
#endif
};
/**
 * @brief Main object for the aegis packet: HC_CHARNOTBEENSELECTED
 *
 */ 
class HC_CHARNOTBEENSELECTED : public Base::NetworkPacketTransmitter<ZoneSession>
{
public:
	HC_CHARNOTBEENSELECTED(std::shared_ptr<ZoneSession> s)
	: NetworkPacketTransmitter<ZoneSession>(ID_HC_CHARNOTBEENSELECTED, s)
	{}
	virtual ~HC_CHARNOTBEENSELECTED() {}

	void deliver();
	ByteBuffer &serialize();

/* Structure */
};

enum {
#if CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION == 20090922
ID_HC_CHECKBOT = 0x07e8
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION == 20090922
ID_HC_CHECKBOT = 0x07e8
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_HC_CHECKBOT = 0x07e8
#endif
};
/**
 * @brief Main object for the aegis packet: HC_CHECKBOT
 *
 */ 
class HC_CHECKBOT : public Base::NetworkPacketTransmitter<ZoneSession>
{
public:
	HC_CHECKBOT(std::shared_ptr<ZoneSession> s)
	: NetworkPacketTransmitter<ZoneSession>(ID_HC_CHECKBOT, s)
	{}
	virtual ~HC_CHECKBOT() {}

	void deliver();
	ByteBuffer &serialize();

/* Structure */
};

enum {
#if CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION == 20090922
ID_HC_CHECKBOT_RESULT = 0x07e9
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION == 20090922
ID_HC_CHECKBOT_RESULT = 0x07e9
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_HC_CHECKBOT_RESULT = 0x07e9
#endif
};
/**
 * @brief Main object for the aegis packet: HC_CHECKBOT_RESULT
 *
 */ 
class HC_CHECKBOT_RESULT : public Base::NetworkPacketTransmitter<ZoneSession>
{
public:
	HC_CHECKBOT_RESULT(std::shared_ptr<ZoneSession> s)
	: NetworkPacketTransmitter<ZoneSession>(ID_HC_CHECKBOT_RESULT, s)
	{}
	virtual ~HC_CHECKBOT_RESULT() {}

	void deliver();
	ByteBuffer &serialize();

/* Structure */
};

enum {
#if CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION == 20100713
ID_HC_DELETE_CHAR3 = 0x082a
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION == 20100713
ID_HC_DELETE_CHAR3 = 0x082a
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_HC_DELETE_CHAR3 = 0x082a
#endif
};
/**
 * @brief Main object for the aegis packet: HC_DELETE_CHAR3
 *
 */ 
class HC_DELETE_CHAR3 : public Base::NetworkPacketTransmitter<ZoneSession>
{
public:
	HC_DELETE_CHAR3(std::shared_ptr<ZoneSession> s)
	: NetworkPacketTransmitter<ZoneSession>(ID_HC_DELETE_CHAR3, s)
	{}
	virtual ~HC_DELETE_CHAR3() {}

	void deliver();
	ByteBuffer &serialize();

/* Structure */
};

enum {
#if CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION == 20100720
ID_HC_DELETE_CHAR3_CANCEL = 0x082c
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION == 20100720
ID_HC_DELETE_CHAR3_CANCEL = 0x082c
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_HC_DELETE_CHAR3_CANCEL = 0x082c
#endif
};
/**
 * @brief Main object for the aegis packet: HC_DELETE_CHAR3_CANCEL
 *
 */ 
class HC_DELETE_CHAR3_CANCEL : public Base::NetworkPacketTransmitter<ZoneSession>
{
public:
	HC_DELETE_CHAR3_CANCEL(std::shared_ptr<ZoneSession> s)
	: NetworkPacketTransmitter<ZoneSession>(ID_HC_DELETE_CHAR3_CANCEL, s)
	{}
	virtual ~HC_DELETE_CHAR3_CANCEL() {}

	void deliver();
	ByteBuffer &serialize();

/* Structure */
};

enum {
#if CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION == 20100713
ID_HC_DELETE_CHAR3_RESERVED = 0x0828
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION == 20100713
ID_HC_DELETE_CHAR3_RESERVED = 0x0828
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_HC_DELETE_CHAR3_RESERVED = 0x0828
#endif
};
/**
 * @brief Main object for the aegis packet: HC_DELETE_CHAR3_RESERVED
 *
 */ 
class HC_DELETE_CHAR3_RESERVED : public Base::NetworkPacketTransmitter<ZoneSession>
{
public:
	HC_DELETE_CHAR3_RESERVED(std::shared_ptr<ZoneSession> s)
	: NetworkPacketTransmitter<ZoneSession>(ID_HC_DELETE_CHAR3_RESERVED, s)
	{}
	virtual ~HC_DELETE_CHAR3_RESERVED() {}

	void deliver();
	ByteBuffer &serialize();

/* Structure */
};

enum {
#if CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION == 20111207
ID_HC_DELETE_SECOND_PASSWD = 0x08bd
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION == 20111207
ID_HC_DELETE_SECOND_PASSWD = 0x08bd
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_HC_DELETE_SECOND_PASSWD = 0x08bd
#endif
};
/**
 * @brief Main object for the aegis packet: HC_DELETE_SECOND_PASSWD
 *
 */ 
class HC_DELETE_SECOND_PASSWD : public Base::NetworkPacketTransmitter<ZoneSession>
{
public:
	HC_DELETE_SECOND_PASSWD(std::shared_ptr<ZoneSession> s)
	: NetworkPacketTransmitter<ZoneSession>(ID_HC_DELETE_SECOND_PASSWD, s)
	{}
	virtual ~HC_DELETE_SECOND_PASSWD() {}

	void deliver();
	ByteBuffer &serialize();

/* Structure */
};

enum {
#if CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION == 20110308
ID_HC_EDIT_SECOND_PASSWD = 0x08bf
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION == 20110308
ID_HC_EDIT_SECOND_PASSWD = 0x08bf
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_HC_EDIT_SECOND_PASSWD = 0x08bf
#endif
};
/**
 * @brief Main object for the aegis packet: HC_EDIT_SECOND_PASSWD
 *
 */ 
class HC_EDIT_SECOND_PASSWD : public Base::NetworkPacketTransmitter<ZoneSession>
{
public:
	HC_EDIT_SECOND_PASSWD(std::shared_ptr<ZoneSession> s)
	: NetworkPacketTransmitter<ZoneSession>(ID_HC_EDIT_SECOND_PASSWD, s)
	{}
	virtual ~HC_EDIT_SECOND_PASSWD() {}

	void deliver();
	ByteBuffer &serialize();

/* Structure */
};

enum {
#if CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION == 20110308
ID_HC_MAKE_SECOND_PASSWD = 0x08bb
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION == 20110308
ID_HC_MAKE_SECOND_PASSWD = 0x08bb
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_HC_MAKE_SECOND_PASSWD = 0x08bb
#endif
};
/**
 * @brief Main object for the aegis packet: HC_MAKE_SECOND_PASSWD
 *
 */ 
class HC_MAKE_SECOND_PASSWD : public Base::NetworkPacketTransmitter<ZoneSession>
{
public:
	HC_MAKE_SECOND_PASSWD(std::shared_ptr<ZoneSession> s)
	: NetworkPacketTransmitter<ZoneSession>(ID_HC_MAKE_SECOND_PASSWD, s)
	{}
	virtual ~HC_MAKE_SECOND_PASSWD() {}

	void deliver();
	ByteBuffer &serialize();

/* Structure */
};

enum {
#if CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION == 20100713
ID_HC_NOTIFY_ACCESSIBLE_MAPNAME = 0x0840
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION == 20100713
ID_HC_NOTIFY_ACCESSIBLE_MAPNAME = 0x0840
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_HC_NOTIFY_ACCESSIBLE_MAPNAME = 0x0840
#endif
};
/**
 * @brief Main object for the aegis packet: HC_NOTIFY_ACCESSIBLE_MAPNAME
 *
 */ 
class HC_NOTIFY_ACCESSIBLE_MAPNAME : public Base::NetworkPacketTransmitter<ZoneSession>
{
public:
	HC_NOTIFY_ACCESSIBLE_MAPNAME(std::shared_ptr<ZoneSession> s)
	: NetworkPacketTransmitter<ZoneSession>(ID_HC_NOTIFY_ACCESSIBLE_MAPNAME, s)
	{}
	virtual ~HC_NOTIFY_ACCESSIBLE_MAPNAME() {}

	void deliver();
	ByteBuffer &serialize();

/* Structure */
};

enum {
#if CLIENT_TYPE == 'A' &&  \
	PACKET_VERSION >= 20040000
ID_HC_NOTIFY_ZONESVR = 0x0071
#elif CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION >= 20030000
ID_HC_NOTIFY_ZONESVR = 0x0071
#elif CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION == 20170228
ID_HC_NOTIFY_ZONESVR = 0x0ac5
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION >= 20080000
ID_HC_NOTIFY_ZONESVR = 0x0071
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION == 20170228
ID_HC_NOTIFY_ZONESVR = 0x0ac5
#elif CLIENT_TYPE == 'S' &&  \
	PACKET_VERSION >= 20030000
ID_HC_NOTIFY_ZONESVR = 0x0071
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_HC_NOTIFY_ZONESVR = 0x0ac5
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20180000
ID_HC_NOTIFY_ZONESVR = 0x0071
#endif
};
/**
 * @brief Main object for the aegis packet: HC_NOTIFY_ZONESVR
 *
 */ 
class HC_NOTIFY_ZONESVR : public Base::NetworkPacketTransmitter<ZoneSession>
{
public:
	HC_NOTIFY_ZONESVR(std::shared_ptr<ZoneSession> s)
	: NetworkPacketTransmitter<ZoneSession>(ID_HC_NOTIFY_ZONESVR, s)
	{}
	virtual ~HC_NOTIFY_ZONESVR() {}

	void deliver();
	ByteBuffer &serialize();

/* Structure */
};

enum {
#if CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION == 20110308
ID_HC_NOT_AVAILABLE_SECOND_PASSWD = 0x08c4
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION == 20110308
ID_HC_NOT_AVAILABLE_SECOND_PASSWD = 0x08c4
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_HC_NOT_AVAILABLE_SECOND_PASSWD = 0x08c4
#endif
};
/**
 * @brief Main object for the aegis packet: HC_NOT_AVAILABLE_SECOND_PASSWD
 *
 */ 
class HC_NOT_AVAILABLE_SECOND_PASSWD : public Base::NetworkPacketTransmitter<ZoneSession>
{
public:
	HC_NOT_AVAILABLE_SECOND_PASSWD(std::shared_ptr<ZoneSession> s)
	: NetworkPacketTransmitter<ZoneSession>(ID_HC_NOT_AVAILABLE_SECOND_PASSWD, s)
	{}
	virtual ~HC_NOT_AVAILABLE_SECOND_PASSWD() {}

	void deliver();
	ByteBuffer &serialize();

/* Structure */
};

enum {
#if CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION == 20121128
ID_HC_QUEUE_ORDER = 0x099e
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION == 20121128
ID_HC_QUEUE_ORDER = 0x099e
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_HC_QUEUE_ORDER = 0x099e
#endif
};
/**
 * @brief Main object for the aegis packet: HC_QUEUE_ORDER
 *
 */ 
class HC_QUEUE_ORDER : public Base::NetworkPacketTransmitter<ZoneSession>
{
public:
	HC_QUEUE_ORDER(std::shared_ptr<ZoneSession> s)
	: NetworkPacketTransmitter<ZoneSession>(ID_HC_QUEUE_ORDER, s)
	{}
	virtual ~HC_QUEUE_ORDER() {}

	void deliver();
	ByteBuffer &serialize();

/* Structure */
};

enum {
#if CLIENT_TYPE == 'A' &&  \
	PACKET_VERSION >= 20040000
ID_HC_REFUSE_DELETECHAR = 0x0070
#elif CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION >= 20030000
ID_HC_REFUSE_DELETECHAR = 0x0070
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION >= 20080000
ID_HC_REFUSE_DELETECHAR = 0x0070
#elif CLIENT_TYPE == 'S' &&  \
	PACKET_VERSION >= 20030000
ID_HC_REFUSE_DELETECHAR = 0x0070
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_HC_REFUSE_DELETECHAR = 0x0070
#endif
};
/**
 * @brief Main object for the aegis packet: HC_REFUSE_DELETECHAR
 *
 */ 
class HC_REFUSE_DELETECHAR : public Base::NetworkPacketTransmitter<ZoneSession>
{
public:
	HC_REFUSE_DELETECHAR(std::shared_ptr<ZoneSession> s)
	: NetworkPacketTransmitter<ZoneSession>(ID_HC_REFUSE_DELETECHAR, s)
	{}
	virtual ~HC_REFUSE_DELETECHAR() {}

	void deliver();
	ByteBuffer &serialize();

/* Structure */
};

enum {
#if CLIENT_TYPE == 'A' &&  \
	PACKET_VERSION >= 20040000
ID_HC_REFUSE_ENTER = 0x006c
#elif CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION >= 20030000
ID_HC_REFUSE_ENTER = 0x006c
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION >= 20080000
ID_HC_REFUSE_ENTER = 0x006c
#elif CLIENT_TYPE == 'S' &&  \
	PACKET_VERSION >= 20030000
ID_HC_REFUSE_ENTER = 0x006c
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_HC_REFUSE_ENTER = 0x006c
#endif
};
/**
 * @brief Main object for the aegis packet: HC_REFUSE_ENTER
 *
 */ 
class HC_REFUSE_ENTER : public Base::NetworkPacketTransmitter<ZoneSession>
{
public:
	HC_REFUSE_ENTER(std::shared_ptr<ZoneSession> s)
	: NetworkPacketTransmitter<ZoneSession>(ID_HC_REFUSE_ENTER, s)
	{}
	virtual ~HC_REFUSE_ENTER() {}

	void deliver();
	ByteBuffer &serialize();

/* Structure */
};

enum {
#if CLIENT_TYPE == 'A' &&  \
	PACKET_VERSION >= 20040000
ID_HC_REFUSE_MAKECHAR = 0x006e
#elif CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION >= 20030000
ID_HC_REFUSE_MAKECHAR = 0x006e
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION >= 20080000
ID_HC_REFUSE_MAKECHAR = 0x006e
#elif CLIENT_TYPE == 'S' &&  \
	PACKET_VERSION >= 20030000
ID_HC_REFUSE_MAKECHAR = 0x006e
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_HC_REFUSE_MAKECHAR = 0x006e
#endif
};
/**
 * @brief Main object for the aegis packet: HC_REFUSE_MAKECHAR
 *
 */ 
class HC_REFUSE_MAKECHAR : public Base::NetworkPacketTransmitter<ZoneSession>
{
public:
	HC_REFUSE_MAKECHAR(std::shared_ptr<ZoneSession> s)
	: NetworkPacketTransmitter<ZoneSession>(ID_HC_REFUSE_MAKECHAR, s)
	{}
	virtual ~HC_REFUSE_MAKECHAR() {}

	void deliver();
	ByteBuffer &serialize();

/* Structure */
};

enum {
#if CLIENT_TYPE == 'A' &&  \
	PACKET_VERSION == 20070821
ID_HC_REFUSE_SELECTCHAR = 0x02ca
#elif CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION == 20070821
ID_HC_REFUSE_SELECTCHAR = 0x02ca
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION >= 20080000
ID_HC_REFUSE_SELECTCHAR = 0x02ca
#elif CLIENT_TYPE == 'S' &&  \
	PACKET_VERSION == 20070821
ID_HC_REFUSE_SELECTCHAR = 0x02ca
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_HC_REFUSE_SELECTCHAR = 0x02ca
#endif
};
/**
 * @brief Main object for the aegis packet: HC_REFUSE_SELECTCHAR
 *
 */ 
class HC_REFUSE_SELECTCHAR : public Base::NetworkPacketTransmitter<ZoneSession>
{
public:
	HC_REFUSE_SELECTCHAR(std::shared_ptr<ZoneSession> s)
	: NetworkPacketTransmitter<ZoneSession>(ID_HC_REFUSE_SELECTCHAR, s)
	{}
	virtual ~HC_REFUSE_SELECTCHAR() {}

	void deliver();
	ByteBuffer &serialize();

/* Structure */
};

enum {
#if CLIENT_TYPE == 'A' &&  \
	PACKET_VERSION == 20050628
ID_HC_REQUEST_CHARACTER_PASSWORD = 0x023e
#elif CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION == 20050628
ID_HC_REQUEST_CHARACTER_PASSWORD = 0x023e
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION >= 20080000
ID_HC_REQUEST_CHARACTER_PASSWORD = 0x023e
#elif CLIENT_TYPE == 'S' &&  \
	PACKET_VERSION == 20050628
ID_HC_REQUEST_CHARACTER_PASSWORD = 0x023e
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_HC_REQUEST_CHARACTER_PASSWORD = 0x023e
#endif
};
/**
 * @brief Main object for the aegis packet: HC_REQUEST_CHARACTER_PASSWORD
 *
 */ 
class HC_REQUEST_CHARACTER_PASSWORD : public Base::NetworkPacketTransmitter<ZoneSession>
{
public:
	HC_REQUEST_CHARACTER_PASSWORD(std::shared_ptr<ZoneSession> s)
	: NetworkPacketTransmitter<ZoneSession>(ID_HC_REQUEST_CHARACTER_PASSWORD, s)
	{}
	virtual ~HC_REQUEST_CHARACTER_PASSWORD() {}

	void deliver();
	ByteBuffer &serialize();

/* Structure */
};

enum {
#if CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION == 20110222
ID_HC_SECOND_PASSWD_LOGIN = 0x08b9
#elif CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION == 20171220
ID_HC_SECOND_PASSWD_LOGIN = 0x0ae9
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION == 20110222
ID_HC_SECOND_PASSWD_LOGIN = 0x08b9
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION == 20171220
ID_HC_SECOND_PASSWD_LOGIN = 0x0ae9
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_HC_SECOND_PASSWD_LOGIN = 0x08b9
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION == 20171220
ID_HC_SECOND_PASSWD_LOGIN = 0x0ae9
#endif
};
/**
 * @brief Main object for the aegis packet: HC_SECOND_PASSWD_LOGIN
 *
 */ 
class HC_SECOND_PASSWD_LOGIN : public Base::NetworkPacketTransmitter<ZoneSession>
{
public:
	HC_SECOND_PASSWD_LOGIN(std::shared_ptr<ZoneSession> s)
	: NetworkPacketTransmitter<ZoneSession>(ID_HC_SECOND_PASSWD_LOGIN, s)
	{}
	virtual ~HC_SECOND_PASSWD_LOGIN() {}

	void deliver();
	ByteBuffer &serialize();

/* Structure */
};

enum {
#if CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION == 20110215
ID_HC_SECOND_PASSWD_REQ = 0x08b7
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION == 20110215
ID_HC_SECOND_PASSWD_REQ = 0x08b7
#endif
};
/**
 * @brief Main object for the aegis packet: HC_SECOND_PASSWD_REQ
 *
 */ 
class HC_SECOND_PASSWD_REQ : public Base::NetworkPacketTransmitter<ZoneSession>
{
public:
	HC_SECOND_PASSWD_REQ(std::shared_ptr<ZoneSession> s)
	: NetworkPacketTransmitter<ZoneSession>(ID_HC_SECOND_PASSWD_REQ, s)
	{}
	virtual ~HC_SECOND_PASSWD_REQ() {}

	void deliver();
	ByteBuffer &serialize();

/* Structure */
};

enum {
#if CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION == 20130522
ID_HC_SECRETSCAN_DATA = 0x09c2
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION == 20130522
ID_HC_SECRETSCAN_DATA = 0x09c2
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_HC_SECRETSCAN_DATA = 0x09c2
#endif
};
/**
 * @brief Main object for the aegis packet: HC_SECRETSCAN_DATA
 *
 */ 
class HC_SECRETSCAN_DATA : public Base::NetworkPacketTransmitter<ZoneSession>
{
public:
	HC_SECRETSCAN_DATA(std::shared_ptr<ZoneSession> s)
	: NetworkPacketTransmitter<ZoneSession>(ID_HC_SECRETSCAN_DATA, s)
	{}
	virtual ~HC_SECRETSCAN_DATA() {}

	void deliver();
	ByteBuffer &serialize();

/* Structure */
};

enum {
#if CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION == 20111101
ID_HC_UPDATE_CHARINFO = 0x08e3
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION == 20111025
ID_HC_UPDATE_CHARINFO = 0x08e3
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_HC_UPDATE_CHARINFO = 0x08e3
#endif
};
/**
 * @brief Main object for the aegis packet: HC_UPDATE_CHARINFO
 *
 */ 
class HC_UPDATE_CHARINFO : public Base::NetworkPacketTransmitter<ZoneSession>
{
public:
	HC_UPDATE_CHARINFO(std::shared_ptr<ZoneSession> s)
	: NetworkPacketTransmitter<ZoneSession>(ID_HC_UPDATE_CHARINFO, s)
	{}
	virtual ~HC_UPDATE_CHARINFO() {}

	void deliver();
	ByteBuffer &serialize();

/* Structure */
};

enum {
#if CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION == 20101228
ID_HC_WAITING_LOGIN = 0x08af
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION == 20101228
ID_HC_WAITING_LOGIN = 0x08af
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_HC_WAITING_LOGIN = 0x08af
#endif
};
/**
 * @brief Main object for the aegis packet: HC_WAITING_LOGIN
 *
 */ 
class HC_WAITING_LOGIN : public Base::NetworkPacketTransmitter<ZoneSession>
{
public:
	HC_WAITING_LOGIN(std::shared_ptr<ZoneSession> s)
	: NetworkPacketTransmitter<ZoneSession>(ID_HC_WAITING_LOGIN, s)
	{}
	virtual ~HC_WAITING_LOGIN() {}

	void deliver();
	ByteBuffer &serialize();

/* Structure */
};

}
 /* namespace Char */}
 /* namespace Horizon */
