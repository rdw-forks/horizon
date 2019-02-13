/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 * Copyright (c) 2019 Horizon Dev Team.
 *
 * Base Author - Sagun Khosla. (sagunxp@gmail.com)
 *
 * Under a proprietary license this file is not for use
 * or viewing without permission.
 **************************************************/

#include "ClientSocketMgr.hpp"

#include "Server/Char/Packets/Ragexe/Packets.hpp"
#include "Server/Char/Packets/RE/Packets.hpp"
#include "Server/Char/Packets/Zero/Packets.hpp"

#include "Server/Char/Packets/PacketHandler.hpp"
#include "Server/Char/Packets/Ragexe/20170104/PacketsRagexe20170104.hpp"
#include "Server/Char/Packets/Ragexe/20170104/PacketHandlerRagexe20170104.hpp"
#include "Server/Char/Packets/RE/20170104/PacketsRE20170104.hpp"
#include "Server/Char/Packets/RE/20170104/PacketHandlerRE20170104.hpp"
#include "Server/Char/Packets/Ragexe/20170228/PacketsRagexe20170228.hpp"
#include "Server/Char/Packets/Ragexe/20170228/PacketHandlerRagexe20170228.hpp"
#include "Server/Char/Packets/RE/20170228/PacketsRE20170228.hpp"
#include "Server/Char/Packets/RE/20170228/PacketHandlerRE20170228.hpp"
#include "Server/Char/Packets/RE/20170830/PacketsRE20170830.hpp"
#include "Server/Char/Packets/RE/20170830/PacketHandlerRE20170830.hpp"
#include "Server/Char/Packets/Ragexe/20170906/PacketsRagexe20170906.hpp"
#include "Server/Char/Packets/Ragexe/20170906/PacketHandlerRagexe20170906.hpp"
#include "Server/Char/Packets/Ragexe/20171220/PacketsRagexe20171220.hpp"
#include "Server/Char/Packets/Ragexe/20171220/PacketHandlerRagexe20171220.hpp"
#include "Server/Char/Packets/RE/20171220/PacketsRE20171220.hpp"
#include "Server/Char/Packets/RE/20171220/PacketHandlerRE20171220.hpp"
#include "Server/Char/Packets/Zero/20171220/PacketsZero20171220.hpp"
#include "Server/Char/Packets/Zero/20171220/PacketHandlerZero20171220.hpp"
#include "Server/Char/Packets/Ragexe/20180103/PacketsRagexe20180103.hpp"
#include "Server/Char/Packets/Ragexe/20180103/PacketHandlerRagexe20180103.hpp"
#include "Server/Char/Packets/RE/20180103/PacketsRE20180103.hpp"
#include "Server/Char/Packets/RE/20180103/PacketHandlerRE20180103.hpp"
#include "Server/Char/Packets/Zero/20180103/PacketsZero20180103.hpp"
#include "Server/Char/Packets/Zero/20180103/PacketHandlerZero20180103.hpp"
#include "Server/Char/Packets/Ragexe/20180117/PacketsRagexe20180117.hpp"
#include "Server/Char/Packets/Ragexe/20180117/PacketHandlerRagexe20180117.hpp"
#include "Server/Char/Packets/RE/20180117/PacketsRE20180117.hpp"
#include "Server/Char/Packets/RE/20180117/PacketHandlerRE20180117.hpp"
#include "Server/Char/Packets/Zero/20180117/PacketsZero20180117.hpp"
#include "Server/Char/Packets/Zero/20180117/PacketHandlerZero20180117.hpp"

using namespace Horizon::Char;

void ClientSocketMgr::initialize_packet_length_db_Ragexe()
{
#define ADD_PVL_DEF(name, len) add_packet_length(Horizon::Char::Ragexe::packets::name, len);
	ADD_PVL_DEF(CH_ACK_CHANGE_CHARACTERNAME, 6)
	ADD_PVL_DEF(CH_AVAILABLE_SECOND_PASSWD, 6)
	ADD_PVL_DEF(CH_CHARLIST_REQ, 2)
	ADD_PVL_DEF(CH_CHECKBOT, 32)
	ADD_PVL_DEF(CH_DELETE_CHAR, 46)
	ADD_PVL_DEF(CH_DELETE_CHAR2, 56)
	ADD_PVL_DEF(CH_DELETE_CHAR3, 12)
	ADD_PVL_DEF(CH_DELETE_CHAR3_CANCEL, 6)
	ADD_PVL_DEF(CH_DELETE_CHAR3_EXT, -1)
	ADD_PVL_DEF(CH_DELETE_CHAR3_RESERVED, 6)
	ADD_PVL_DEF(CH_DELETE_SECOND_PASSWD, 10)
	ADD_PVL_DEF(CH_EDIT_SECOND_PASSWD, 14)
	ADD_PVL_DEF(CH_ENTER, 17)
	ADD_PVL_DEF(CH_ENTER2, 37)
	ADD_PVL_DEF(CH_ENTER_CHECKBOT, 4)
	ADD_PVL_DEF(CH_MAKE_CHAR, 36)
	ADD_PVL_DEF(CH_MAKE_CHAR_NOT_STATS, 31)
	ADD_PVL_DEF(CH_MAKE_SECOND_PASSWD, 10)
	ADD_PVL_DEF(CH_NOT_AVAILABLE_SECOND_PASSWD, 10)
	ADD_PVL_DEF(CH_REQ_CHANGE_CHARACTERNAME, 30)
	ADD_PVL_DEF(CH_REQ_CHANGE_CHARACTER_SLOT, 8)
	ADD_PVL_DEF(CH_REQ_CHANGE_CHARNAME, 6)
	ADD_PVL_DEF(CH_REQ_CHARINFO_PER_PAGE, 6)
	ADD_PVL_DEF(CH_REQ_IS_VALID_CHARNAME, 34)
	ADD_PVL_DEF(CH_SECOND_PASSWD_ACK, 10)
	ADD_PVL_DEF(CH_SELECT_ACCESSIBLE_MAPNAME, 4)
	ADD_PVL_DEF(CH_SELECT_CHAR, 3)
	ADD_PVL_DEF(CH_SELECT_CHAR_GOINGTOBEUSED, 46)
	ADD_PVL_DEF(CH_UNKNOWN_PING, 6)
	ADD_PVL_DEF(CH_WAITING_LOGIN, 17)
	ADD_PVL_DEF(HC_ACCEPT_DELETECHAR, 2)
	ADD_PVL_DEF(HC_ACCEPT_ENTER, -1)
	ADD_PVL_DEF(HC_ACCEPT_ENTER2, -1)
	ADD_PVL_DEF(HC_ACCEPT_MAKECHAR, 108)
	ADD_PVL_DEF(HC_ACK_CHANGE_CHARACTER_SLOT, -1)
	ADD_PVL_DEF(HC_ACK_CHANGE_CHARNAME, 4)
	ADD_PVL_DEF(HC_ACK_CHARINFO_PER_PAGE, -1)
	ADD_PVL_DEF(HC_ACK_IS_VALID_CHARNAME, 4)
	ADD_PVL_DEF(HC_AVAILABLE_SECOND_PASSWD, 4)
	ADD_PVL_DEF(HC_BLOCK_CHARACTER, -1)
	ADD_PVL_DEF(HC_CHARACTER_LIST, -1)
	ADD_PVL_DEF(HC_CHARLIST_NOTIFY, 6)
	ADD_PVL_DEF(HC_CHARNOTBEENSELECTED, -1)
	ADD_PVL_DEF(HC_CHECKBOT, -1)
	ADD_PVL_DEF(HC_CHECKBOT_RESULT, 5)
	ADD_PVL_DEF(HC_DELETE_CHAR3, 10)
	ADD_PVL_DEF(HC_DELETE_CHAR3_CANCEL, 10)
	ADD_PVL_DEF(HC_DELETE_CHAR3_RESERVED, 14)
	ADD_PVL_DEF(HC_DELETE_SECOND_PASSWD, 8)
	ADD_PVL_DEF(HC_EDIT_SECOND_PASSWD, 8)
	ADD_PVL_DEF(HC_MAKE_SECOND_PASSWD, 8)
	ADD_PVL_DEF(HC_NOTIFY_ACCESSIBLE_MAPNAME, -1)
	ADD_PVL_DEF(HC_NOTIFY_ZONESVR, 28)
	ADD_PVL_DEF(HC_NOT_AVAILABLE_SECOND_PASSWD, 8)
	ADD_PVL_DEF(HC_QUEUE_ORDER, 12)
	ADD_PVL_DEF(HC_REFUSE_DELETECHAR, 3)
	ADD_PVL_DEF(HC_REFUSE_ENTER, 3)
	ADD_PVL_DEF(HC_REFUSE_MAKECHAR, 3)
	ADD_PVL_DEF(HC_REFUSE_SELECTCHAR, 3)
	ADD_PVL_DEF(HC_REQUEST_CHARACTER_PASSWORD, 8)
	ADD_PVL_DEF(HC_SECOND_PASSWD_LOGIN, 13)
	ADD_PVL_DEF(HC_SECRETSCAN_DATA, -1)
	ADD_PVL_DEF(HC_WAITING_LOGIN, 10)
#undef ADD_PVL_DEF
}

void ClientSocketMgr::initialize_packet_length_db_RE()
{
#define ADD_PVL_DEF(name, len) add_packet_length(Horizon::Char::RE::packets::name, len);
	ADD_PVL_DEF(CH_MAKE_CHAR, 37)
	ADD_PVL_DEF(HC_SECOND_PASSWD_LOGIN, 12)
#undef ADD_PVL_DEF
}

void ClientSocketMgr::initialize_packet_length_db_Zero()
{
#define ADD_PVL_DEF(name, len) add_packet_length(Horizon::Char::Zero::packets::name, len);
	ADD_PVL_DEF(HC_NOTIFY_ZONESVR, 156)
	ADD_PVL_DEF(HC_UPDATE_CHARINFO, 157)
#undef ADD_PVL_DEF
}

void ClientSocketMgr::initialize_packet_length_db_Ragexe_20170104()
{
#define ADD_PVL_DEF(name, len) add_packet_length(Horizon::Char::Ragexe20170104::packets::name, len);
	ADD_PVL_DEF(HC_ACCEPT_MAKECHAR, 149)
	ADD_PVL_DEF(HC_UPDATE_CHARINFO, 149)
#undef ADD_PVL_DEF
}

void ClientSocketMgr::initialize_packet_length_db_RE_20170104()
{
#define ADD_PVL_DEF(name, len) add_packet_length(Horizon::Char::RE20170104::packets::name, len);
#undef ADD_PVL_DEF
}

void ClientSocketMgr::initialize_packet_length_db_Ragexe_20170228()
{
#define ADD_PVL_DEF(name, len) add_packet_length(Horizon::Char::Ragexe20170228::packets::name, len);
	ADD_PVL_DEF(HC_NOTIFY_ZONESVR, 156)
#undef ADD_PVL_DEF
}

void ClientSocketMgr::initialize_packet_length_db_RE_20170228()
{
#define ADD_PVL_DEF(name, len) add_packet_length(Horizon::Char::RE20170228::packets::name, len);
#undef ADD_PVL_DEF
}

void ClientSocketMgr::initialize_packet_length_db_RE_20170830()
{
#define ADD_PVL_DEF(name, len) add_packet_length(Horizon::Char::RE20170830::packets::name, len);
	ADD_PVL_DEF(HC_ACCEPT_MAKECHAR, 157)
	ADD_PVL_DEF(HC_UPDATE_CHARINFO, 157)
#undef ADD_PVL_DEF
}

void ClientSocketMgr::initialize_packet_length_db_Ragexe_20170906()
{
#define ADD_PVL_DEF(name, len) add_packet_length(Horizon::Char::Ragexe20170906::packets::name, len);
	ADD_PVL_DEF(HC_ACCEPT_MAKECHAR, 157)
	ADD_PVL_DEF(HC_UPDATE_CHARINFO, 157)
#undef ADD_PVL_DEF
}

void ClientSocketMgr::initialize_packet_length_db_Ragexe_20171220()
{
#define ADD_PVL_DEF(name, len) add_packet_length(Horizon::Char::Ragexe20171220::packets::name, len);
	ADD_PVL_DEF(HC_SECOND_PASSWD_LOGIN, 64)
#undef ADD_PVL_DEF
}

void ClientSocketMgr::initialize_packet_length_db_RE_20171220()
{
#define ADD_PVL_DEF(name, len) add_packet_length(Horizon::Char::RE20171220::packets::name, len);
#undef ADD_PVL_DEF
}

void ClientSocketMgr::initialize_packet_length_db_Zero_20171220()
{
#define ADD_PVL_DEF(name, len) add_packet_length(Horizon::Char::Zero20171220::packets::name, len);
#undef ADD_PVL_DEF
}

void ClientSocketMgr::initialize_packet_length_db_Ragexe_20180103()
{
#define ADD_PVL_DEF(name, len) add_packet_length(Horizon::Char::Ragexe20180103::packets::name, len);
	ADD_PVL_DEF(HC_SECOND_PASSWD_LOGIN, 64)
#undef ADD_PVL_DEF
}

void ClientSocketMgr::initialize_packet_length_db_RE_20180103()
{
#define ADD_PVL_DEF(name, len) add_packet_length(Horizon::Char::RE20180103::packets::name, len);
#undef ADD_PVL_DEF
}

void ClientSocketMgr::initialize_packet_length_db_Zero_20180103()
{
#define ADD_PVL_DEF(name, len) add_packet_length(Horizon::Char::Zero20180103::packets::name, len);
#undef ADD_PVL_DEF
}

void ClientSocketMgr::initialize_packet_length_db_Ragexe_20180117()
{
#define ADD_PVL_DEF(name, len) add_packet_length(Horizon::Char::Ragexe20180117::packets::name, len);
	ADD_PVL_DEF(HC_SECOND_PASSWD_LOGIN, 13)
#undef ADD_PVL_DEF
}

void ClientSocketMgr::initialize_packet_length_db_RE_20180117()
{
#define ADD_PVL_DEF(name, len) add_packet_length(Horizon::Char::RE20180117::packets::name, len);
#undef ADD_PVL_DEF
}

void ClientSocketMgr::initialize_packet_length_db_Zero_20180117()
{
#define ADD_PVL_DEF(name, len) add_packet_length(Horizon::Char::Zero20180117::packets::name, len);
#undef ADD_PVL_DEF
}
