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

#ifndef HORIZON_CHAR_RE_PACKET_LENGTH_TABLE
#define HORIZON_CHAR_RE_PACKET_LENGTH_TABLE

#include "Core/Multithreading/LockedLookupTable.hpp"
#include "Server/Char/Packets/HandledPackets.hpp"
#include "Server/Char/Packets/TransmittedPackets.hpp"

namespace Horizon
{
namespace Char
{
	typedef std::shared_ptr<Base::NetworkPacketHandler<CharSession>> HPacketStructPtrType;
	typedef std::shared_ptr<Base::NetworkPacketTransmitter<CharSession>> TPacketStructPtrType;
	typedef std::pair<int16_t, HPacketStructPtrType> HPacketTablePairType;
	typedef std::pair<int16_t, TPacketStructPtrType> TPacketTablePairType;
/**
 * @brief Auto-generated with a python generator tool authored by Sephus (sagunxp@gmail.com).
 */
class PacketLengthTable
{
public:
	PacketLengthTable(std::shared_ptr<CharSession> s)
	: _session(s)
	{
#define ADD_HPKT(i, j, k) _hpacket_length_table.insert(i, std::make_pair(j, std::make_shared<k>(s)))
#define ADD_TPKT(i, j, k) _tpacket_length_table.insert(i, std::make_pair(j, std::make_shared<k>(s)))
		ADD_HPKT(0x0068, 46, CH_DELETE_CHAR);
		ADD_HPKT(0x01fb, 56, CH_DELETE_CHAR2);
		ADD_HPKT(0x0065, 17, CH_ENTER);
		ADD_HPKT(0x0067, 37, CH_MAKE_CHAR);
		ADD_HPKT(0x028f, 6, CH_REQ_CHANGE_CHARNAME);
		ADD_HPKT(0x028d, 34, CH_REQ_IS_VALID_CHARNAME);
		ADD_HPKT(0x0066, 3, CH_SELECT_CHAR);
		ADD_HPKT(0x028c, 46, CH_SELECT_CHAR_GOINGTOBEUSED);
		ADD_HPKT(0x0187, 6, CH_UNKNOWN_PING);
		ADD_TPKT(0x006f, 2, HC_ACCEPT_DELETECHAR);
		ADD_TPKT(0x006b, -1, HC_ACCEPT_ENTER);
		ADD_TPKT(0x0290, 4, HC_ACK_CHANGE_CHARNAME);
		ADD_TPKT(0x028e, 4, HC_ACK_IS_VALID_CHARNAME);
		ADD_TPKT(0x020d, -1, HC_BLOCK_CHARACTER);
		ADD_TPKT(0x028b, -1, HC_CHARNOTBEENSELECTED);
		ADD_TPKT(0x0071, 28, HC_NOTIFY_ZONESVR);
		ADD_TPKT(0x0070, 3, HC_REFUSE_DELETECHAR);
		ADD_TPKT(0x006c, 3, HC_REFUSE_ENTER);
		ADD_TPKT(0x006e, 3, HC_REFUSE_MAKECHAR);
		ADD_TPKT(0x02ca, 3, HC_REFUSE_SELECTCHAR);
		ADD_TPKT(0x023e, 8, HC_REQUEST_CHARACTER_PASSWORD);
#undef ADD_HPKT
#undef ADD_TPKT
	}

	~PacketLengthTable() { }

	std::shared_ptr<CharSession> get_session() { return _session.lock(); }

	HPacketTablePairType get_hpacket_info(uint16_t packet_id) { return _hpacket_length_table.at(packet_id); }
	TPacketTablePairType get_tpacket_info(uint16_t packet_id) { return _tpacket_length_table.at(packet_id); }

protected:
	LockedLookupTable<uint16_t, HPacketTablePairType> _hpacket_length_table;
	LockedLookupTable<uint16_t, TPacketTablePairType> _tpacket_length_table;
	std::weak_ptr<CharSession> _session;

};
}
}
#endif /* HORIZON_CHAR_RE_PACKET_LENGTH_TABLE */
