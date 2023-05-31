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
// Packet Version 20031223: 1 Packets
#if PACKET_VERSION >= 20031223
		ADD_TPKT(0x01f1, -1, AC_NOTIFY_ERROR);
#endif
// Packet Version 20040322: 1 Packets
#if PACKET_VERSION >= 20040322
		ADD_HPKT(0x01fa, 48, CA_LOGIN3);
#endif
// Packet Version 20040517: 1 Packets
#if PACKET_VERSION >= 20040517
		ADD_HPKT(0x0200, 26, CA_CONNECT_INFO_CHANGED);
#endif
// Packet Version 20040531: 1 Packets
#if PACKET_VERSION >= 20040531
		ADD_HPKT(0x0204, 18, CA_EXE_HASHCHECK);
#endif
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
// Packet Version 20090701: 1 Packets
#if PACKET_VERSION >= 20090701
		ADD_TPKT(0x0276, -1, AC_ACCEPT_LOGIN2);
#endif
// Packet Version 20100413: 3 Packets
#if PACKET_VERSION >= 20100413
		ADD_TPKT(0x0823, -1, AC_OTP_AUTH_ACK);
		ADD_TPKT(0x0821, 2, AC_OTP_USER);
		ADD_HPKT(0x0822, 9, CA_OTP_AUTH_REQ);
#endif
// Packet Version 20100601: 2 Packets
#if PACKET_VERSION >= 20100601
		ADD_TPKT(0x0826, 4, AC_SSO_LOGIN_ACK);
		ADD_HPKT(0x0825, -1, CA_SSO_LOGIN_REQ);
#endif
// Packet Version 20100615: 1 Packets
#if PACKET_VERSION >= 20100615
		ADD_TPKT(0x083e, 26, AC_REFUSE_LOGIN2);
#endif
// Packet Version 20101228: 1 Packets
#if PACKET_VERSION >= 20101228
		ADD_TPKT(0x08b2, -1, AC_REALNAME_AUTH);
#endif
// Packet Version 20110726: 1 Packets
#if PACKET_VERSION >= 20110726
		ADD_HPKT(0x08cc, 109, CA_LOGIN5);
#endif
// Packet Version 20111025: 1 Packets
#if PACKET_VERSION >= 20111025
		ADD_TPKT(0x08e4, 6, AC_SHUTDOWN_INFO);
#endif
// Packet Version 20120626: 1 Packets
#if PACKET_VERSION >= 20120626
		ADD_TPKT(0x0986, 10, AC_SHUTDOWN_NOTIFY);
#endif
// Packet Version 20120702: 1 Packets
#if PACKET_VERSION >= 20120702
		ADD_HPKT(0x0987, 63, CA_LOGIN6);
#endif
// Packet Version 20120716: 2 Packets
#if PACKET_VERSION >= 20120716
		ADD_TPKT(0x098b, 2, AC_REQ_NEW_USER);
		ADD_HPKT(0x098c, 4, CA_ACK_NEW_USER);
#endif
// Packet Version 20130130: 2 Packets
#if PACKET_VERSION >= 20130130
		ADD_TPKT(0x09a2, 6, AC_REQ_MOBILE_OTP);
		ADD_HPKT(0x09a3, -1, CA_ACK_MOBILE_OTP);
#endif
// Packet Version 20130220: 1 Packets
#if PACKET_VERSION >= 20130220
		ADD_TPKT(0x09a5, 7, AC_REFUSE_LOGIN3);
#endif
// Packet Version 20130605: 1 Packets
#if PACKET_VERSION >= 20130605
		ADD_HPKT(0x09c8, -1, CA_LOGIN_OTP);
#endif
// Packet Version 20170228: 1 Packets
#if PACKET_VERSION >= 20170228
		ADD_TPKT(0x0ac4, -1, AC_ACCEPT_LOGIN);
#endif
// Packet Version 20170614: 1 Packets
#if PACKET_VERSION >= 20170614
		ADD_HPKT(0x0ad0, 11, CA_OTP_CODE);
#endif
// Packet Version 20171115: 1 Packets
#if PACKET_VERSION >= 20171115
		ADD_HPKT(0x0acf, 68, CA_LOGIN_OTP);
#endif
// Packet Version 20171213: 1 Packets
#if PACKET_VERSION >= 20190000
	ADD_TPKT(0x0ad1, -1, AC_LOGIN_OTP);
#elif PACKET_VERSION >= 20171213
	ADD_TPKT(0x0ae3, -1, AC_LOGIN_OTP);
#endif
// Packet Version 20180704: 1 Packets
#if PACKET_VERSION >= 20180704
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
