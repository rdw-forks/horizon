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

#ifndef HORIZON_COMMON_RE_PACKET_LENGTH_TABLE
#define HORIZON_COMMON_RE_PACKET_LENGTH_TABLE

#include "Server\/Zone\/Packets\/HandlerPackets.hpp"
#include "Server\/Zone\/Packets\/TransmitterPackets.hpp"

namespace Horizon
{
namespace Zone
{
	typedef std::shared_ptr<Base::NetworkPacketHandler<ZoneSession>> HPacketStructPtrType;
	typedef std::shared_ptr<Base::NetworkPacketTransmitter<ZoneSession>> TPacketStructPtrType;
	typedef std::pair<int16_t, HPacketStructPtrType> HPacketTablePairType;
	typedef std::pair<int16_t, TPacketStructPtrType> TPacketTablePairType;
/**
 * @brief Auto-generated with a python generator tool authored by Sephus (sagunxp@gmail.com).
 */
class PacketLengthTable
{{
public:
	PacketLengthTable(std::shared_ptr<ZoneSession> s)
	: _session(s)
	{{
#define ADD_HPKT(i, j, k) _hpacket_length_table.insert(i, std::make_pair(j, std::make_shared<k>(s)))
#define ADD_TPKT(i, j, k) _tpacket_length_table.insert(i, std::make_pair(j, std::make_shared<k>(s)))
		ADD_TPKT(0x03dd, 18, AHC_GAME_GUARD);
		ADD_TPKT(0x03de, 18, CAH_ACK_GAME_GUARD);
		ADD_HPKT(0x01c6, 4, CS_REQ_ENCRYPTION);
		ADD_TPKT(0x01c7, 2, SC_ACK_ENCRYPTION);
		ADD_TPKT(0x01b5, 18, SC_BILLING_INFO);
		ADD_TPKT(0x0081, 3, SC_NOTIFY_BAN);
#undef ADD_HPKT
#undef ADD_TPKT
	}

	~PacketLengthTable() { }

	std::shared_ptr<ZoneSession> get_session() { return _session.lock(); }

	HPacketTablePairType get_hpacket_info(uint16_t packet_id) { return _hpacket_length_table.at(packet_id); }
	TPacketTablePairType get_tpacket_info(uint16_t packet_id) { return _tpacket_length_table.at(packet_id); }

protected:
	LockedLookupTable<uint16_t, HPacketTablePairType> _hpacket_length_table;
	LockedLookupTable<uint16_t, TPacketTablePairType> _tpacket_length_table;
	std::weak_ptr<ZoneSession> _session;

};
}
}
#endif /* HORIZON_COMMON_RE_PACKET_LENGTH_TABLE */
