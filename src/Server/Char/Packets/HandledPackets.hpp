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

#ifndef HORIZON_CHAR_HANDLED_PACKETS_HPP
#define HORIZON_CHAR_HANDLED_PACKETS_HPP

#include "Server/Common/Base/NetworkPacket.hpp"
#include "Server/Common/Configuration/Horizon.hpp"

namespace Horizon
{
namespace Char
{
class CharSession;
enum {
#if CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION == 20111101
ID_CH_ACK_CHANGE_CHARACTERNAME = 0x08fd
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION == 20111101
ID_CH_ACK_CHANGE_CHARACTERNAME = 0x08fd
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_CH_ACK_CHANGE_CHARACTERNAME = 0x08fd
#endif
};
/**
 * @brief Main object for the aegis packet: CH_ACK_CHANGE_CHARACTERNAME
 *
 */ 
class CH_ACK_CHANGE_CHARACTERNAME : public Base::NetworkPacketHandler<ZoneSession>
{
public:
	CH_ACK_CHANGE_CHARACTERNAME(std::shared_ptr<ZoneSession> s)
	: NetworkPacketHandler<ZoneSession>(ID_CH_ACK_CHANGE_CHARACTERNAME, s)
	{}
	virtual ~CH_ACK_CHANGE_CHARACTERNAME() {}

	void handle(ByteBuffer &&buf);
	void deserialize(ByteBuffer &buf);

/* Structure */
};

enum {
#if CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION == 20110308
ID_CH_AVAILABLE_SECOND_PASSWD = 0x08c5
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION == 20110308
ID_CH_AVAILABLE_SECOND_PASSWD = 0x08c5
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_CH_AVAILABLE_SECOND_PASSWD = 0x08c5
#endif
};
/**
 * @brief Main object for the aegis packet: CH_AVAILABLE_SECOND_PASSWD
 *
 */ 
class CH_AVAILABLE_SECOND_PASSWD : public Base::NetworkPacketHandler<ZoneSession>
{
public:
	CH_AVAILABLE_SECOND_PASSWD(std::shared_ptr<ZoneSession> s)
	: NetworkPacketHandler<ZoneSession>(ID_CH_AVAILABLE_SECOND_PASSWD, s)
	{}
	virtual ~CH_AVAILABLE_SECOND_PASSWD() {}

	void handle(ByteBuffer &&buf);
	void deserialize(ByteBuffer &buf);

/* Structure */
};

enum {
#if CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION == 20121212
ID_CH_CHARLIST_REQ = 0x09a1
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION == 20121212
ID_CH_CHARLIST_REQ = 0x09a1
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_CH_CHARLIST_REQ = 0x09a1
#endif
};
/**
 * @brief Main object for the aegis packet: CH_CHARLIST_REQ
 *
 */ 
class CH_CHARLIST_REQ : public Base::NetworkPacketHandler<ZoneSession>
{
public:
	CH_CHARLIST_REQ(std::shared_ptr<ZoneSession> s)
	: NetworkPacketHandler<ZoneSession>(ID_CH_CHARLIST_REQ, s)
	{}
	virtual ~CH_CHARLIST_REQ() {}

	void handle(ByteBuffer &&buf);
	void deserialize(ByteBuffer &buf);

/* Structure */
};

enum {
#if CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION == 20090922
ID_CH_CHECKBOT = 0x07e7
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION == 20090922
ID_CH_CHECKBOT = 0x07e7
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_CH_CHECKBOT = 0x07e7
#endif
};
/**
 * @brief Main object for the aegis packet: CH_CHECKBOT
 *
 */ 
class CH_CHECKBOT : public Base::NetworkPacketHandler<ZoneSession>
{
public:
	CH_CHECKBOT(std::shared_ptr<ZoneSession> s)
	: NetworkPacketHandler<ZoneSession>(ID_CH_CHECKBOT, s)
	{}
	virtual ~CH_CHECKBOT() {}

	void handle(ByteBuffer &&buf);
	void deserialize(ByteBuffer &buf);

/* Structure */
};

enum {
#if CLIENT_TYPE == 'A' &&  \
	PACKET_VERSION >= 20040000
ID_CH_DELETE_CHAR = 0x0068
#elif CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION >= 20030000
ID_CH_DELETE_CHAR = 0x0068
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION >= 20080000
ID_CH_DELETE_CHAR = 0x0068
#elif CLIENT_TYPE == 'S' &&  \
	PACKET_VERSION >= 20030000
ID_CH_DELETE_CHAR = 0x0068
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_CH_DELETE_CHAR = 0x0068
#endif
};
/**
 * @brief Main object for the aegis packet: CH_DELETE_CHAR
 *
 */ 
class CH_DELETE_CHAR : public Base::NetworkPacketHandler<ZoneSession>
{
public:
	CH_DELETE_CHAR(std::shared_ptr<ZoneSession> s)
	: NetworkPacketHandler<ZoneSession>(ID_CH_DELETE_CHAR, s)
	{}
	virtual ~CH_DELETE_CHAR() {}

	void handle(ByteBuffer &&buf);
	void deserialize(ByteBuffer &buf);

/* Structure */
};

enum {
#if CLIENT_TYPE == 'A' &&  \
	PACKET_VERSION >= 20040000
ID_CH_DELETE_CHAR2 = 0x01fb
#elif CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION == 20040419
ID_CH_DELETE_CHAR2 = 0x01fb
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION >= 20080000
ID_CH_DELETE_CHAR2 = 0x01fb
#elif CLIENT_TYPE == 'S' &&  \
	PACKET_VERSION == 20040419
ID_CH_DELETE_CHAR2 = 0x01fb
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_CH_DELETE_CHAR2 = 0x01fb
#endif
};
/**
 * @brief Main object for the aegis packet: CH_DELETE_CHAR2
 *
 */ 
class CH_DELETE_CHAR2 : public Base::NetworkPacketHandler<ZoneSession>
{
public:
	CH_DELETE_CHAR2(std::shared_ptr<ZoneSession> s)
	: NetworkPacketHandler<ZoneSession>(ID_CH_DELETE_CHAR2, s)
	{}
	virtual ~CH_DELETE_CHAR2() {}

	void handle(ByteBuffer &&buf);
	void deserialize(ByteBuffer &buf);

/* Structure */
};

enum {
#if CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION == 20100728
ID_CH_DELETE_CHAR3 = 0x0829
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION == 20100728
ID_CH_DELETE_CHAR3 = 0x0829
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_CH_DELETE_CHAR3 = 0x0829
#endif
};
/**
 * @brief Main object for the aegis packet: CH_DELETE_CHAR3
 *
 */ 
class CH_DELETE_CHAR3 : public Base::NetworkPacketHandler<ZoneSession>
{
public:
	CH_DELETE_CHAR3(std::shared_ptr<ZoneSession> s)
	: NetworkPacketHandler<ZoneSession>(ID_CH_DELETE_CHAR3, s)
	{}
	virtual ~CH_DELETE_CHAR3() {}

	void handle(ByteBuffer &&buf);
	void deserialize(ByteBuffer &buf);

/* Structure */
};

enum {
#if CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION == 20100713
ID_CH_DELETE_CHAR3_CANCEL = 0x082b
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION == 20100713
ID_CH_DELETE_CHAR3_CANCEL = 0x082b
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_CH_DELETE_CHAR3_CANCEL = 0x082b
#endif
};
/**
 * @brief Main object for the aegis packet: CH_DELETE_CHAR3_CANCEL
 *
 */ 
class CH_DELETE_CHAR3_CANCEL : public Base::NetworkPacketHandler<ZoneSession>
{
public:
	CH_DELETE_CHAR3_CANCEL(std::shared_ptr<ZoneSession> s)
	: NetworkPacketHandler<ZoneSession>(ID_CH_DELETE_CHAR3_CANCEL, s)
	{}
	virtual ~CH_DELETE_CHAR3_CANCEL() {}

	void handle(ByteBuffer &&buf);
	void deserialize(ByteBuffer &buf);

/* Structure */
};

enum {
#if CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION == 20120724
ID_CH_DELETE_CHAR3_EXT = 0x098f
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION == 20120724
ID_CH_DELETE_CHAR3_EXT = 0x098f
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_CH_DELETE_CHAR3_EXT = 0x098f
#endif
};
/**
 * @brief Main object for the aegis packet: CH_DELETE_CHAR3_EXT
 *
 */ 
class CH_DELETE_CHAR3_EXT : public Base::NetworkPacketHandler<ZoneSession>
{
public:
	CH_DELETE_CHAR3_EXT(std::shared_ptr<ZoneSession> s)
	: NetworkPacketHandler<ZoneSession>(ID_CH_DELETE_CHAR3_EXT, s)
	{}
	virtual ~CH_DELETE_CHAR3_EXT() {}

	void handle(ByteBuffer &&buf);
	void deserialize(ByteBuffer &buf);

/* Structure */
};

enum {
#if CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION == 20100713
ID_CH_DELETE_CHAR3_RESERVED = 0x0827
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION == 20100713
ID_CH_DELETE_CHAR3_RESERVED = 0x0827
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_CH_DELETE_CHAR3_RESERVED = 0x0827
#endif
};
/**
 * @brief Main object for the aegis packet: CH_DELETE_CHAR3_RESERVED
 *
 */ 
class CH_DELETE_CHAR3_RESERVED : public Base::NetworkPacketHandler<ZoneSession>
{
public:
	CH_DELETE_CHAR3_RESERVED(std::shared_ptr<ZoneSession> s)
	: NetworkPacketHandler<ZoneSession>(ID_CH_DELETE_CHAR3_RESERVED, s)
	{}
	virtual ~CH_DELETE_CHAR3_RESERVED() {}

	void handle(ByteBuffer &&buf);
	void deserialize(ByteBuffer &buf);

/* Structure */
};

enum {
#if CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION == 20110308
ID_CH_DELETE_SECOND_PASSWD = 0x08bc
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION == 20110308
ID_CH_DELETE_SECOND_PASSWD = 0x08bc
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_CH_DELETE_SECOND_PASSWD = 0x08bc
#endif
};
/**
 * @brief Main object for the aegis packet: CH_DELETE_SECOND_PASSWD
 *
 */ 
class CH_DELETE_SECOND_PASSWD : public Base::NetworkPacketHandler<ZoneSession>
{
public:
	CH_DELETE_SECOND_PASSWD(std::shared_ptr<ZoneSession> s)
	: NetworkPacketHandler<ZoneSession>(ID_CH_DELETE_SECOND_PASSWD, s)
	{}
	virtual ~CH_DELETE_SECOND_PASSWD() {}

	void handle(ByteBuffer &&buf);
	void deserialize(ByteBuffer &buf);

/* Structure */
};

enum {
#if CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION == 20110308
ID_CH_EDIT_SECOND_PASSWD = 0x08be
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION == 20110308
ID_CH_EDIT_SECOND_PASSWD = 0x08be
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_CH_EDIT_SECOND_PASSWD = 0x08be
#endif
};
/**
 * @brief Main object for the aegis packet: CH_EDIT_SECOND_PASSWD
 *
 */ 
class CH_EDIT_SECOND_PASSWD : public Base::NetworkPacketHandler<ZoneSession>
{
public:
	CH_EDIT_SECOND_PASSWD(std::shared_ptr<ZoneSession> s)
	: NetworkPacketHandler<ZoneSession>(ID_CH_EDIT_SECOND_PASSWD, s)
	{}
	virtual ~CH_EDIT_SECOND_PASSWD() {}

	void handle(ByteBuffer &&buf);
	void deserialize(ByteBuffer &buf);

/* Structure */
};

enum {
#if CLIENT_TYPE == 'A' &&  \
	PACKET_VERSION >= 20040000
ID_CH_ENTER = 0x0065
#elif CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION >= 20030000
ID_CH_ENTER = 0x0065
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION >= 20080000
ID_CH_ENTER = 0x0065
#elif CLIENT_TYPE == 'S' &&  \
	PACKET_VERSION >= 20030000
ID_CH_ENTER = 0x0065
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_CH_ENTER = 0x0065
#endif
};
/**
 * @brief Main object for the aegis packet: CH_ENTER
 *
 */ 
class CH_ENTER : public Base::NetworkPacketHandler<ZoneSession>
{
public:
	CH_ENTER(std::shared_ptr<ZoneSession> s)
	: NetworkPacketHandler<ZoneSession>(ID_CH_ENTER, s)
	{}
	virtual ~CH_ENTER() {}

	void handle(ByteBuffer &&buf);
	void deserialize(ByteBuffer &buf);

/* Structure */
};

enum {
#if CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION == 20090701
ID_CH_ENTER2 = 0x0275
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION == 20090701
ID_CH_ENTER2 = 0x0275
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_CH_ENTER2 = 0x0275
#endif
};
/**
 * @brief Main object for the aegis packet: CH_ENTER2
 *
 */ 
class CH_ENTER2 : public Base::NetworkPacketHandler<ZoneSession>
{
public:
	CH_ENTER2(std::shared_ptr<ZoneSession> s)
	: NetworkPacketHandler<ZoneSession>(ID_CH_ENTER2, s)
	{}
	virtual ~CH_ENTER2() {}

	void handle(ByteBuffer &&buf);
	void deserialize(ByteBuffer &buf);

/* Structure */
};

enum {
#if CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION == 20090922
ID_CH_ENTER_CHECKBOT = 0x07e5
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION == 20090922
ID_CH_ENTER_CHECKBOT = 0x07e5
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_CH_ENTER_CHECKBOT = 0x07e5
#endif
};
/**
 * @brief Main object for the aegis packet: CH_ENTER_CHECKBOT
 *
 */ 
class CH_ENTER_CHECKBOT : public Base::NetworkPacketHandler<ZoneSession>
{
public:
	CH_ENTER_CHECKBOT(std::shared_ptr<ZoneSession> s)
	: NetworkPacketHandler<ZoneSession>(ID_CH_ENTER_CHECKBOT, s)
	{}
	virtual ~CH_ENTER_CHECKBOT() {}

	void handle(ByteBuffer &&buf);
	void deserialize(ByteBuffer &buf);

/* Structure */
};

enum {
#if CLIENT_TYPE == 'A' &&  \
	PACKET_VERSION >= 20040000
ID_CH_MAKE_CHAR = 0x0067
#elif CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION >= 20030000
ID_CH_MAKE_CHAR = 0x0067
#elif CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION == 20150415
ID_CH_MAKE_CHAR = 0x0a39
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION >= 20080000
ID_CH_MAKE_CHAR = 0x0067
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION == 20150415
ID_CH_MAKE_CHAR = 0x0a39
#elif CLIENT_TYPE == 'S' &&  \
	PACKET_VERSION >= 20030000
ID_CH_MAKE_CHAR = 0x0067
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_CH_MAKE_CHAR = 0x0a39
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20180000
ID_CH_MAKE_CHAR = 0x0067
#endif
};
/**
 * @brief Main object for the aegis packet: CH_MAKE_CHAR
 *
 */ 
class CH_MAKE_CHAR : public Base::NetworkPacketHandler<ZoneSession>
{
public:
	CH_MAKE_CHAR(std::shared_ptr<ZoneSession> s)
	: NetworkPacketHandler<ZoneSession>(ID_CH_MAKE_CHAR, s)
	{}
	virtual ~CH_MAKE_CHAR() {}

	void handle(ByteBuffer &&buf);
	void deserialize(ByteBuffer &buf);

/* Structure */
};

enum {
#if CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION == 20120214
ID_CH_MAKE_CHAR_NOT_STATS = 0x0970
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION == 20120214
ID_CH_MAKE_CHAR_NOT_STATS = 0x0970
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_CH_MAKE_CHAR_NOT_STATS = 0x0970
#endif
};
/**
 * @brief Main object for the aegis packet: CH_MAKE_CHAR_NOT_STATS
 *
 */ 
class CH_MAKE_CHAR_NOT_STATS : public Base::NetworkPacketHandler<ZoneSession>
{
public:
	CH_MAKE_CHAR_NOT_STATS(std::shared_ptr<ZoneSession> s)
	: NetworkPacketHandler<ZoneSession>(ID_CH_MAKE_CHAR_NOT_STATS, s)
	{}
	virtual ~CH_MAKE_CHAR_NOT_STATS() {}

	void handle(ByteBuffer &&buf);
	void deserialize(ByteBuffer &buf);

/* Structure */
};

enum {
#if CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION == 20110308
ID_CH_MAKE_SECOND_PASSWD = 0x08ba
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION == 20110308
ID_CH_MAKE_SECOND_PASSWD = 0x08ba
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_CH_MAKE_SECOND_PASSWD = 0x08ba
#endif
};
/**
 * @brief Main object for the aegis packet: CH_MAKE_SECOND_PASSWD
 *
 */ 
class CH_MAKE_SECOND_PASSWD : public Base::NetworkPacketHandler<ZoneSession>
{
public:
	CH_MAKE_SECOND_PASSWD(std::shared_ptr<ZoneSession> s)
	: NetworkPacketHandler<ZoneSession>(ID_CH_MAKE_SECOND_PASSWD, s)
	{}
	virtual ~CH_MAKE_SECOND_PASSWD() {}

	void handle(ByteBuffer &&buf);
	void deserialize(ByteBuffer &buf);

/* Structure */
};

enum {
#if CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION == 20110308
ID_CH_NOT_AVAILABLE_SECOND_PASSWD = 0x08c3
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION == 20110308
ID_CH_NOT_AVAILABLE_SECOND_PASSWD = 0x08c3
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_CH_NOT_AVAILABLE_SECOND_PASSWD = 0x08c3
#endif
};
/**
 * @brief Main object for the aegis packet: CH_NOT_AVAILABLE_SECOND_PASSWD
 *
 */ 
class CH_NOT_AVAILABLE_SECOND_PASSWD : public Base::NetworkPacketHandler<ZoneSession>
{
public:
	CH_NOT_AVAILABLE_SECOND_PASSWD(std::shared_ptr<ZoneSession> s)
	: NetworkPacketHandler<ZoneSession>(ID_CH_NOT_AVAILABLE_SECOND_PASSWD, s)
	{}
	virtual ~CH_NOT_AVAILABLE_SECOND_PASSWD() {}

	void handle(ByteBuffer &&buf);
	void deserialize(ByteBuffer &buf);

/* Structure */
};

enum {
#if CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION == 20111101
ID_CH_REQ_CHANGE_CHARACTERNAME = 0x08fc
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION == 20111101
ID_CH_REQ_CHANGE_CHARACTERNAME = 0x08fc
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_CH_REQ_CHANGE_CHARACTERNAME = 0x08fc
#endif
};
/**
 * @brief Main object for the aegis packet: CH_REQ_CHANGE_CHARACTERNAME
 *
 */ 
class CH_REQ_CHANGE_CHARACTERNAME : public Base::NetworkPacketHandler<ZoneSession>
{
public:
	CH_REQ_CHANGE_CHARACTERNAME(std::shared_ptr<ZoneSession> s)
	: NetworkPacketHandler<ZoneSession>(ID_CH_REQ_CHANGE_CHARACTERNAME, s)
	{}
	virtual ~CH_REQ_CHANGE_CHARACTERNAME() {}

	void handle(ByteBuffer &&buf);
	void deserialize(ByteBuffer &buf);

/* Structure */
};

enum {
#if CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION == 20111101
ID_CH_REQ_CHANGE_CHARACTER_SLOT = 0x08d4
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION == 20111101
ID_CH_REQ_CHANGE_CHARACTER_SLOT = 0x08d4
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_CH_REQ_CHANGE_CHARACTER_SLOT = 0x08d4
#endif
};
/**
 * @brief Main object for the aegis packet: CH_REQ_CHANGE_CHARACTER_SLOT
 *
 */ 
class CH_REQ_CHANGE_CHARACTER_SLOT : public Base::NetworkPacketHandler<ZoneSession>
{
public:
	CH_REQ_CHANGE_CHARACTER_SLOT(std::shared_ptr<ZoneSession> s)
	: NetworkPacketHandler<ZoneSession>(ID_CH_REQ_CHANGE_CHARACTER_SLOT, s)
	{}
	virtual ~CH_REQ_CHANGE_CHARACTER_SLOT() {}

	void handle(ByteBuffer &&buf);
	void deserialize(ByteBuffer &buf);

/* Structure */
};

enum {
#if CLIENT_TYPE == 'A' &&  \
	PACKET_VERSION == 20061030
ID_CH_REQ_CHANGE_CHARNAME = 0x028f
#elif CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION == 20061030
ID_CH_REQ_CHANGE_CHARNAME = 0x028f
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION >= 20080000
ID_CH_REQ_CHANGE_CHARNAME = 0x028f
#elif CLIENT_TYPE == 'S' &&  \
	PACKET_VERSION == 20061023
ID_CH_REQ_CHANGE_CHARNAME = 0x028f
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_CH_REQ_CHANGE_CHARNAME = 0x028f
#endif
};
/**
 * @brief Main object for the aegis packet: CH_REQ_CHANGE_CHARNAME
 *
 */ 
class CH_REQ_CHANGE_CHARNAME : public Base::NetworkPacketHandler<ZoneSession>
{
public:
	CH_REQ_CHANGE_CHARNAME(std::shared_ptr<ZoneSession> s)
	: NetworkPacketHandler<ZoneSession>(ID_CH_REQ_CHANGE_CHARNAME, s)
	{}
	virtual ~CH_REQ_CHANGE_CHARNAME() {}

	void handle(ByteBuffer &&buf);
	void deserialize(ByteBuffer &buf);

/* Structure */
};

enum {
#if CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION == 20121024
ID_CH_REQ_CHARINFO_PER_PAGE = 0x099c
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION == 20121024
ID_CH_REQ_CHARINFO_PER_PAGE = 0x099c
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_CH_REQ_CHARINFO_PER_PAGE = 0x099c
#endif
};
/**
 * @brief Main object for the aegis packet: CH_REQ_CHARINFO_PER_PAGE
 *
 */ 
class CH_REQ_CHARINFO_PER_PAGE : public Base::NetworkPacketHandler<ZoneSession>
{
public:
	CH_REQ_CHARINFO_PER_PAGE(std::shared_ptr<ZoneSession> s)
	: NetworkPacketHandler<ZoneSession>(ID_CH_REQ_CHARINFO_PER_PAGE, s)
	{}
	virtual ~CH_REQ_CHARINFO_PER_PAGE() {}

	void handle(ByteBuffer &&buf);
	void deserialize(ByteBuffer &buf);

/* Structure */
};

enum {
#if CLIENT_TYPE == 'A' &&  \
	PACKET_VERSION == 20061030
ID_CH_REQ_IS_VALID_CHARNAME = 0x028d
#elif CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION == 20061030
ID_CH_REQ_IS_VALID_CHARNAME = 0x028d
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION >= 20080000
ID_CH_REQ_IS_VALID_CHARNAME = 0x028d
#elif CLIENT_TYPE == 'S' &&  \
	PACKET_VERSION == 20061023
ID_CH_REQ_IS_VALID_CHARNAME = 0x028d
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_CH_REQ_IS_VALID_CHARNAME = 0x028d
#endif
};
/**
 * @brief Main object for the aegis packet: CH_REQ_IS_VALID_CHARNAME
 *
 */ 
class CH_REQ_IS_VALID_CHARNAME : public Base::NetworkPacketHandler<ZoneSession>
{
public:
	CH_REQ_IS_VALID_CHARNAME(std::shared_ptr<ZoneSession> s)
	: NetworkPacketHandler<ZoneSession>(ID_CH_REQ_IS_VALID_CHARNAME, s)
	{}
	virtual ~CH_REQ_IS_VALID_CHARNAME() {}

	void handle(ByteBuffer &&buf);
	void deserialize(ByteBuffer &buf);

/* Structure */
};

enum {
#if CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION == 20110308
ID_CH_SECOND_PASSWD_ACK = 0x08b8
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION == 20110308
ID_CH_SECOND_PASSWD_ACK = 0x08b8
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_CH_SECOND_PASSWD_ACK = 0x08b8
#endif
};
/**
 * @brief Main object for the aegis packet: CH_SECOND_PASSWD_ACK
 *
 */ 
class CH_SECOND_PASSWD_ACK : public Base::NetworkPacketHandler<ZoneSession>
{
public:
	CH_SECOND_PASSWD_ACK(std::shared_ptr<ZoneSession> s)
	: NetworkPacketHandler<ZoneSession>(ID_CH_SECOND_PASSWD_ACK, s)
	{}
	virtual ~CH_SECOND_PASSWD_ACK() {}

	void handle(ByteBuffer &&buf);
	void deserialize(ByteBuffer &buf);

/* Structure */
};

enum {
#if CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION == 20100714
ID_CH_SELECT_ACCESSIBLE_MAPNAME = 0x0841
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION == 20100714
ID_CH_SELECT_ACCESSIBLE_MAPNAME = 0x0841
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_CH_SELECT_ACCESSIBLE_MAPNAME = 0x0841
#endif
};
/**
 * @brief Main object for the aegis packet: CH_SELECT_ACCESSIBLE_MAPNAME
 *
 */ 
class CH_SELECT_ACCESSIBLE_MAPNAME : public Base::NetworkPacketHandler<ZoneSession>
{
public:
	CH_SELECT_ACCESSIBLE_MAPNAME(std::shared_ptr<ZoneSession> s)
	: NetworkPacketHandler<ZoneSession>(ID_CH_SELECT_ACCESSIBLE_MAPNAME, s)
	{}
	virtual ~CH_SELECT_ACCESSIBLE_MAPNAME() {}

	void handle(ByteBuffer &&buf);
	void deserialize(ByteBuffer &buf);

/* Structure */
};

enum {
#if CLIENT_TYPE == 'A' &&  \
	PACKET_VERSION >= 20040000
ID_CH_SELECT_CHAR = 0x0066
#elif CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION >= 20030000
ID_CH_SELECT_CHAR = 0x0066
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION >= 20080000
ID_CH_SELECT_CHAR = 0x0066
#elif CLIENT_TYPE == 'S' &&  \
	PACKET_VERSION >= 20030000
ID_CH_SELECT_CHAR = 0x0066
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_CH_SELECT_CHAR = 0x0066
#endif
};
/**
 * @brief Main object for the aegis packet: CH_SELECT_CHAR
 *
 */ 
class CH_SELECT_CHAR : public Base::NetworkPacketHandler<ZoneSession>
{
public:
	CH_SELECT_CHAR(std::shared_ptr<ZoneSession> s)
	: NetworkPacketHandler<ZoneSession>(ID_CH_SELECT_CHAR, s)
	{}
	virtual ~CH_SELECT_CHAR() {}

	void handle(ByteBuffer &&buf);
	void deserialize(ByteBuffer &buf);

/* Structure */
};

enum {
#if CLIENT_TYPE == 'A' &&  \
	PACKET_VERSION == 20061030
ID_CH_SELECT_CHAR_GOINGTOBEUSED = 0x028c
#elif CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION == 20061030
ID_CH_SELECT_CHAR_GOINGTOBEUSED = 0x028c
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION >= 20080000
ID_CH_SELECT_CHAR_GOINGTOBEUSED = 0x028c
#elif CLIENT_TYPE == 'S' &&  \
	PACKET_VERSION == 20061023
ID_CH_SELECT_CHAR_GOINGTOBEUSED = 0x028c
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_CH_SELECT_CHAR_GOINGTOBEUSED = 0x028c
#endif
};
/**
 * @brief Main object for the aegis packet: CH_SELECT_CHAR_GOINGTOBEUSED
 *
 */ 
class CH_SELECT_CHAR_GOINGTOBEUSED : public Base::NetworkPacketHandler<ZoneSession>
{
public:
	CH_SELECT_CHAR_GOINGTOBEUSED(std::shared_ptr<ZoneSession> s)
	: NetworkPacketHandler<ZoneSession>(ID_CH_SELECT_CHAR_GOINGTOBEUSED, s)
	{}
	virtual ~CH_SELECT_CHAR_GOINGTOBEUSED() {}

	void handle(ByteBuffer &&buf);
	void deserialize(ByteBuffer &buf);

/* Structure */
};

enum {
#if CLIENT_TYPE == 'A' &&  \
	PACKET_VERSION >= 20040000
ID_CH_UNKNOWN_PING = 0x0187
#elif CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION >= 20030000
ID_CH_UNKNOWN_PING = 0x0187
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION >= 20080000
ID_CH_UNKNOWN_PING = 0x0187
#elif CLIENT_TYPE == 'S' &&  \
	PACKET_VERSION >= 20030000
ID_CH_UNKNOWN_PING = 0x0187
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_CH_UNKNOWN_PING = 0x0187
#endif
};
/**
 * @brief Main object for the aegis packet: CH_UNKNOWN_PING
 *
 */ 
class CH_UNKNOWN_PING : public Base::NetworkPacketHandler<ZoneSession>
{
public:
	CH_UNKNOWN_PING(std::shared_ptr<ZoneSession> s)
	: NetworkPacketHandler<ZoneSession>(ID_CH_UNKNOWN_PING, s)
	{}
	virtual ~CH_UNKNOWN_PING() {}

	void handle(ByteBuffer &&buf);
	void deserialize(ByteBuffer &buf);

/* Structure */
};

enum {
#if CLIENT_TYPE == 'M' &&  \
	PACKET_VERSION == 20110111
ID_CH_WAITING_LOGIN = 0x08b0
#elif CLIENT_TYPE == 'R' &&  \
	PACKET_VERSION == 20110111
ID_CH_WAITING_LOGIN = 0x08b0
#elif CLIENT_TYPE == 'Z' &&  \
	PACKET_VERSION >= 20170000
ID_CH_WAITING_LOGIN = 0x08b0
#endif
};
/**
 * @brief Main object for the aegis packet: CH_WAITING_LOGIN
 *
 */ 
class CH_WAITING_LOGIN : public Base::NetworkPacketHandler<ZoneSession>
{
public:
	CH_WAITING_LOGIN(std::shared_ptr<ZoneSession> s)
	: NetworkPacketHandler<ZoneSession>(ID_CH_WAITING_LOGIN, s)
	{}
	virtual ~CH_WAITING_LOGIN() {}

	void handle(ByteBuffer &&buf);
	void deserialize(ByteBuffer &buf);

/* Structure */
};

}
 /* namespace Char */}
 /* namespace Horizon */
