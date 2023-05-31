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
#if PACKET_VERSION >= 20171213
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
