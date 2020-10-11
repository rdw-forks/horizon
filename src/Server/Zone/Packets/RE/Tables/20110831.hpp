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

#ifndef HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20110831
#define HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20110831

#include "Server/Common/Base/NetworkPacket.hpp"
#include "Core/Multithreading/LockedLookupTable.hpp"

#include "Default.hpp"

#include <utility>

namespace Horizon
{
namespace Zone
{
namespace ShufflePackets
{
/**
 * @brief Shuffle Packet Length Table object that stores
 * the packet length of each packet of this client version.
 * Packets with IDs already existent in the database are over-written.
 * The data is stored in a thread-safe lookup table.
 * RAII techinque ensures that the table is populated on instantiation.
 */
class ShufflePacketLengthTable : public PacketLengthTable
{
public:
	ShufflePacketLengthTable()
	{
		std::shared_ptr<ZoneSocket> sock = get_socket();

#define ADD_PKT(i, j, k) _packet_length_table.insert(i, std::make_pair<uint16_t, NetworkPacket>(j, k))
		ADD_PKT(0x023b, 10, CZ_ACK_STORE_PASSWORD(sock));
		ADD_PKT(0x0361, 2, CZ_CHANGE_DIRECTION2(sock));
		ADD_PKT(0x0436, 2, CZ_ENTER2(sock));
		ADD_PKT(0x07e4, 2, CZ_ITEMLISTWIN_RES(sock));
		ADD_PKT(0x0362, 2, CZ_ITEM_PICKUP2(sock));
		ADD_PKT(0x07ec, 2, CZ_JOIN_BATTLE_FIELD(sock));
		ADD_PKT(0x0365, 8, CZ_MOVE_ITEM_FROM_STORE_TO_BODY2(sock));
		ADD_PKT(0x0802, 19, CZ_PARTY_BOOKING_REQ_REGISTER(sock));
		ADD_PKT(0x02c4, 2, CZ_PARTY_JOIN_REQ(sock));
		ADD_PKT(0x0368, 2, CZ_REQNAME2(sock));
		ADD_PKT(0x0369, 2, CZ_REQNAME_BYGID2(sock));
		ADD_PKT(0x0360, 2, CZ_REQUEST_TIME2(sock));
		ADD_PKT(0x0817, 6, CZ_REQ_CLICK_TO_BUYING_STORE(sock));
		ADD_PKT(0x0815, -1, CZ_REQ_CLOSE_BUYING_STORE(sock));
		ADD_PKT(0x0819, 12, CZ_REQ_TRADE_BUYING_STORE(sock));
		ADD_PKT(0x0835, 4, CZ_SEARCH_STORE_INFO(sock));
		ADD_PKT(0x083c, 26, CZ_SSILIST_ITEM_CLICK(sock));
		ADD_PKT(0x0438, 6, CZ_USE_SKILL2(sock));
		ADD_PKT(0x0366, 5, CZ_USE_SKILL_TOGROUND2(sock));
		ADD_PKT(0x0367, -1, CZ_USE_SKILL_TOGROUND_WITHTALKBOX2(sock));
#undef ADD_PKT
	}

	~ShufflePacketLengthTable() { }

};
}
}
}
#endif /* HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20110831 */