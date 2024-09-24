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
 * This is proprietary software. Unauthorized copying,
 * distribution, or modification of this file, via any
 * medium, is strictly prohibited. All rights reserved.
 **************************************************/

#ifndef HORIZON_CHAR_CLIENT_PACKET_LENGTH_TABLE
#define HORIZON_CHAR_CLIENT_PACKET_LENGTH_TABLE

#include "PacketLengthTable.hpp"

namespace Horizon
{
namespace Char
{
/**
 * @brief Auto-generated with a python generator tool authored by Sephus (sagunxp@gmail.com).
 */
class ClientPacketLengthTable : public PacketLengthTable
{
public:
	ClientPacketLengthTable(std::shared_ptr<CharSession> s)
	: PacketLengthTable(s)
	{
#define ADD_HPKT(i, j, k) _hpacket_length_table.insert(i, std::make_pair(j, std::make_shared<k>(s)))
#define ADD_TPKT(i, j, k) _tpacket_length_table.insert(i, std::make_pair(j, std::make_shared<k>(s)))
// Packet Version 20081217: 1 Packets
#if PACKET_VERSION >= 20170000
		ADD_TPKT(0x006d, 157, HC_ACCEPT_MAKECHAR);
#elif PACKET_VERSION >= 20081217
		ADD_TPKT(0x006d, 114, HC_ACCEPT_MAKECHAR);
#endif
// Packet Version 20090226: 1 Packets
#if PACKET_VERSION >= 20090226
		ADD_TPKT(0x0448, -1, HC_CHARACTER_LIST);
#endif
// Packet Version 20090701: 1 Packets
#if PACKET_VERSION >= 20090701
		ADD_HPKT(0x0275, 37, CH_ENTER2);
#endif
// Packet Version 20090922: 4 Packets
#if PACKET_VERSION >= 20090922
		ADD_HPKT(0x07e7, 32, CH_CHECKBOT);
		ADD_HPKT(0x07e5, 8, CH_ENTER_CHECKBOT);
		ADD_TPKT(0x07e8, -1, HC_CHECKBOT);
		ADD_TPKT(0x07e9, 5, HC_CHECKBOT_RESULT);
#endif
// Packet Version 20100713: 5 Packets
#if PACKET_VERSION >= 20100713
		ADD_HPKT(0x082b, 6, CH_DELETE_CHAR3_CANCEL);
		ADD_HPKT(0x0827, 6, CH_DELETE_CHAR3_RESERVED);
		ADD_TPKT(0x082a, 10, HC_DELETE_CHAR3);
		ADD_TPKT(0x0828, 14, HC_DELETE_CHAR3_RESERVED);
		ADD_TPKT(0x0840, -1, HC_NOTIFY_ACCESSIBLE_MAPNAME);
#endif
// Packet Version 20100714: 1 Packets
#if PACKET_VERSION >= 20100714
		ADD_HPKT(0x0841, 4, CH_SELECT_ACCESSIBLE_MAPNAME);
#endif
// Packet Version 20100720: 1 Packets
#if PACKET_VERSION >= 20100720
		ADD_TPKT(0x082c, 10, HC_DELETE_CHAR3_CANCEL);
#endif
// Packet Version 20100728: 1 Packets
#if PACKET_VERSION >= 20100728
		ADD_HPKT(0x0829, 12, CH_DELETE_CHAR3);
#endif
// Packet Version 20101221: 1 Packets
#if PACKET_VERSION >= 20101221
		ADD_TPKT(0x082d, -1, HC_ACCEPT_ENTER2);
#endif
// Packet Version 20101228: 1 Packets
#if PACKET_VERSION >= 20101228
		ADD_TPKT(0x08af, 10, HC_WAITING_LOGIN);
#endif
// Packet Version 20110111: 1 Packets
#if PACKET_VERSION >= 20110111
		ADD_HPKT(0x08b0, 17, CH_WAITING_LOGIN);
#endif
// Packet Version 20110215: 1 Packets
#if PACKET_VERSION >= 20110215
		ADD_TPKT(0x08b7, 10, HC_SECOND_PASSWD_REQ);
#endif
// Packet Version 20110222: 1 Packets
#if PACKET_VERSION >= 20110222
		ADD_TPKT(0x08b9, 12, HC_SECOND_PASSWD_LOGIN);
#endif
// Packet Version 20110228: 1 Packets
#if PACKET_VERSION >= 20110228
		ADD_TPKT(0x08c6, 4, HC_AVAILABLE_SECOND_PASSWD);
#endif
// Packet Version 20110308: 9 Packets
#if PACKET_VERSION >= 20110308
		ADD_HPKT(0x08c5, 6, CH_AVAILABLE_SECOND_PASSWD);
		ADD_HPKT(0x08bc, 10, CH_DELETE_SECOND_PASSWD);
		ADD_HPKT(0x08be, 14, CH_EDIT_SECOND_PASSWD);
		ADD_HPKT(0x08ba, 10, CH_MAKE_SECOND_PASSWD);
		ADD_HPKT(0x08c3, 10, CH_NOT_AVAILABLE_SECOND_PASSWD);
		ADD_HPKT(0x08b8, 10, CH_SECOND_PASSWD_ACK);
		ADD_TPKT(0x08bf, 8, HC_EDIT_SECOND_PASSWD);
		ADD_TPKT(0x08bb, 8, HC_MAKE_SECOND_PASSWD);
		ADD_TPKT(0x08c4, 8, HC_NOT_AVAILABLE_SECOND_PASSWD);
#endif
// Packet Version 20110906: 1 Packets
#if PACKET_VERSION >= 20110906
		ADD_TPKT(0x08d5, -1, HC_ACK_CHANGE_CHARACTER_SLOT);
#endif
// Packet Version 20111025: 1 Packets
#if PACKET_VERSION >= 20111025
		ADD_TPKT(0x08e3, 146, HC_UPDATE_CHARINFO);
#endif
// Packet Version 20111101: 3 Packets
#if PACKET_VERSION >= 20111101
		ADD_HPKT(0x08fd, 6, CH_ACK_CHANGE_CHARACTERNAME);
		ADD_HPKT(0x08fc, 30, CH_REQ_CHANGE_CHARACTERNAME);
		ADD_HPKT(0x08d4, 8, CH_REQ_CHANGE_CHARACTER_SLOT);
#endif
// Packet Version 20111207: 1 Packets
#if PACKET_VERSION >= 20111207
		ADD_TPKT(0x08bd, 8, HC_DELETE_SECOND_PASSWD);
#endif
// Packet Version 20120214: 1 Packets
#if PACKET_VERSION >= 20120214
		ADD_HPKT(0x0970, 31, CH_MAKE_CHAR_NOT_STATS);
#endif
// Packet Version 20120724: 1 Packets
#if PACKET_VERSION >= 20120724
		ADD_HPKT(0x098f, -1, CH_DELETE_CHAR3_EXT);
#endif
// Packet Version 20121024: 2 Packets
#if PACKET_VERSION >= 20121024
		ADD_HPKT(0x099c, 6, CH_REQ_CHARINFO_PER_PAGE);
		ADD_TPKT(0x099d, -1, HC_ACK_CHARINFO_PER_PAGE);
#endif
// Packet Version 20121128: 1 Packets
#if PACKET_VERSION >= 20121128
		ADD_TPKT(0x099e, 12, HC_QUEUE_ORDER);
#endif
// Packet Version 20121212: 2 Packets
#if PACKET_VERSION >= 20121212
		ADD_HPKT(0x09a1, 2, CH_CHARLIST_REQ);
		ADD_TPKT(0x09a0, 6, HC_CHARLIST_NOTIFY);
#endif
// Packet Version 20130522: 1 Packets
#if PACKET_VERSION >= 20130522
		ADD_TPKT(0x09c2, -1, HC_SECRETSCAN_DATA);
#endif
// Packet Version 20150415: 1 Packets
#if PACKET_VERSION >= 20150415
		ADD_HPKT(0x0a39, 36, CH_MAKE_CHAR);
#endif
// Packet Version 20170228: 1 Packets
#if PACKET_VERSION >= 20170228
		ADD_TPKT(0x0ac5, 156, HC_NOTIFY_ZONESVR);
#endif
// Packet Version 20171220: 1 Packets
#if PACKET_VERSION >= 20171220
#if CLIENT_TYPE == 'M' && PACKET_VERSION >= 20180124 \
|| CLIENT_TYPE == 'R' && PACKET_VERSION >= 20180124 \
|| CLIENT_TYPE == 'Z' && PACKET_VERSION >= 20180131
		ADD_TPKT(0x0ae9, 13, HC_SECOND_PASSWD_LOGIN);
#else
		ADD_TPKT(0x0ae9, 64, HC_SECOND_PASSWD_LOGIN);
#endif
#endif
#undef ADD_TPKT
#undef ADD_HPKT
	}

	~ClientPacketLengthTable() { }

};
}
}
#endif /* HORIZON_CHAR_CLIENT_PACKET_LENGTH_TABLE */
