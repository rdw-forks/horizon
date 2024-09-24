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

#ifndef HORIZON_AUTH_CLIENT_PACKET_LENGTH_TABLE
#define HORIZON_AUTH_CLIENT_PACKET_LENGTH_TABLE

#include "PacketLengthTable.hpp"

namespace Horizon
{
namespace Auth
{
/**
 * @brief Auto-generated with a python generator tool authored by Sephus (sagunxp@gmail.com).
 */
class ClientPacketLengthTable : public PacketLengthTable
{
public:
	ClientPacketLengthTable(std::shared_ptr<AuthSession> s)
	: PacketLengthTable(s)
	{
#define ADD_HPKT(i, j, k) _hpacket_length_table.insert(i, std::make_pair(j, std::make_shared<k>(s)))
#define ADD_TPKT(i, j, k) _tpacket_length_table.insert(i, std::make_pair(j, std::make_shared<k>(s)))
// Packet Version 20171113: 1 Packets
#if PACKET_VERSION >= 20171113
		ADD_HPKT(0x0acf, 68, CA_LOGIN_OTP);
#endif
// Packet Version 20171123: 1 Packets
#if PACKET_VERSION >= 20171123
		ADD_TPKT(0x0ae3, -1, AC_LOGIN_OTP);
#endif
// Packet Version 20180627: 1 Packets
#if PACKET_VERSION >= 20180627
		ADD_TPKT(0x0b02, 26, AC_REFUSE_LOGIN4);
#endif
#undef ADD_TPKT
#undef ADD_HPKT
	}

	~ClientPacketLengthTable() { }

};
}
}
#endif /* HORIZON_AUTH_CLIENT_PACKET_LENGTH_TABLE */
