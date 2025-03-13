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
// Packet Version 20050628: 1 Packets
#if PACKET_VERSION >= 20050628
		ADD_TPKT(0x023d, 6, AC_EVENT_RESULT);
#endif
// Packet Version 20050912: 2 Packets
#if PACKET_VERSION >= 20050912
		ADD_TPKT(0x0259, 3, AC_ACK_GAME_GUARD);
		ADD_HPKT(0x0258, 2, CA_REQ_GAME_GUARD_CHECK);
#endif
// Packet Version 20060109: 16 Packets
#if PACKET_VERSION >= 20060109
		ADD_TPKT(0x026a, 4, AC_ACK_EKEY_FAIL_AUTHREFUSE);
		ADD_TPKT(0x026b, 4, AC_ACK_EKEY_FAIL_INPUTEKEY);
		ADD_TPKT(0x026d, 4, AC_ACK_EKEY_FAIL_NEEDCARDPASS);
		ADD_TPKT(0x0267, 4, AC_ACK_EKEY_FAIL_NOTEXIST);
		ADD_TPKT(0x026c, 4, AC_ACK_EKEY_FAIL_NOTICE);
		ADD_TPKT(0x0269, 4, AC_ACK_EKEY_FAIL_NOTUSEDEKEY);
		ADD_TPKT(0x0268, 4, AC_ACK_EKEY_FAIL_NOTUSESEKEY);
		ADD_TPKT(0x026f, 2, AC_ACK_FIRST_LOGIN);
		ADD_TPKT(0x0272, 44, AC_ACK_PT_ID_INFO);
		ADD_TPKT(0x0270, 2, AC_REQ_LOGIN_ACCOUNT_INFO);
		ADD_TPKT(0x0263, 11, AC_REQ_LOGIN_CARDPASS);
		ADD_TPKT(0x0262, 11, AC_REQ_LOGIN_NEWEKEY);
		ADD_TPKT(0x0261, 11, AC_REQ_LOGIN_OLDEKEY);
		ADD_HPKT(0x0266, 30, CA_ACK_LOGIN_CARDPASS);
		ADD_HPKT(0x0265, 20, CA_ACK_LOGIN_NEWEKEY);
		ADD_HPKT(0x0264, 20, CA_ACK_LOGIN_OLDEKEY);
#endif
// Packet Version 20060126: 1 Packets
#if PACKET_VERSION >= 20060126
		ADD_HPKT(0x0271, 40, CA_ACK_LOGIN_ACCOUNT_INFO);
#endif
// Packet Version 20060424: 1 Packets
#if PACKET_VERSION >= 20060424
		ADD_HPKT(0x0277, 84, CA_LOGIN_PCBANG);
#endif
// Packet Version 20060626: 1 Packets
#if PACKET_VERSION >= 20060626
		ADD_HPKT(0x027c, 60, CA_LOGIN4);
#endif
// Packet Version 20060821: 1 Packets
#if PACKET_VERSION >= 20060821
		ADD_HPKT(0x027f, 8, CA_CLIENT_TYPE);
#endif
// Packet Version 20070227: 1 Packets
#if PACKET_VERSION >= 20070227
		ADD_TPKT(0x02ad, 8, AC_REQUEST_SECOND_PASSWORD);
#endif
// Packet Version 20070514: 1 Packets
#if PACKET_VERSION >= 20070514
		ADD_HPKT(0x02b0, 85, CA_LOGIN_HAN);
#endif
#undef ADD_TPKT
#undef ADD_HPKT
	}

	~ClientPacketLengthTable() { }

};
}
}
#endif /* HORIZON_AUTH_CLIENT_PACKET_LENGTH_TABLE */
