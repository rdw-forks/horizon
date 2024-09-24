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
// Packet Version 20040419: 1 Packets
#if PACKET_VERSION >= 20040419
		ADD_HPKT(0x01fb, 56, CH_DELETE_CHAR2);
#endif
// Packet Version 20040621: 1 Packets
#if PACKET_VERSION >= 20040621
		ADD_TPKT(0x020d, -1, HC_BLOCK_CHARACTER);
#endif
// Packet Version 20050628: 1 Packets
#if PACKET_VERSION >= 20050628
		ADD_TPKT(0x023e, 4, HC_REQUEST_CHARACTER_PASSWORD);
#endif
// Packet Version 20061023: 6 Packets
#if PACKET_VERSION >= 20061023
		ADD_HPKT(0x028f, 6, CH_REQ_CHANGE_CHARNAME);
		ADD_HPKT(0x028d, 34, CH_REQ_IS_VALID_CHARNAME);
		ADD_HPKT(0x028c, 46, CH_SELECT_CHAR_GOINGTOBEUSED);
		ADD_TPKT(0x0290, 4, HC_ACK_CHANGE_CHARNAME);
		ADD_TPKT(0x028e, 4, HC_ACK_IS_VALID_CHARNAME);
		ADD_TPKT(0x028b, -1, HC_CHARNOTBEENSELECTED);
#endif
// Packet Version 20070821: 1 Packets
#if PACKET_VERSION >= 20070821
		ADD_TPKT(0x02ca, 3, HC_REFUSE_SELECTCHAR);
#endif
// Packet Version 20090225: 1 Packets
#if PACKET_VERSION >= 20090225
		ADD_TPKT(0x0448, -1, HC_CHARACTER_LIST);
#endif
#undef ADD_TPKT
#undef ADD_HPKT
	}

	~ClientPacketLengthTable() { }

};
}
}
#endif /* HORIZON_CHAR_CLIENT_PACKET_LENGTH_TABLE */
