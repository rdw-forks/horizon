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

#ifndef HORIZON_ZONE_RE_20171002_PACKET_CZ_MOVE_ITEM_FROM_BODY_TO_STORE_HPP
#define HORIZON_ZONE_RE_20171002_PACKET_CZ_MOVE_ITEM_FROM_BODY_TO_STORE_HPP

#include "Server/Zone/Packets/RE/20171002/PacketsRE20171002.hpp"
#include "Server/Zone/Packets/RE/20170927/Structs/PACKET_CZ_MOVE_ITEM_FROM_BODY_TO_STORE.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace RE20171002
{
struct PACKET_CZ_MOVE_ITEM_FROM_BODY_TO_STORE : public Horizon::Zone::RE20170927::PACKET_CZ_MOVE_ITEM_FROM_BODY_TO_STORE
{
	PACKET_CZ_MOVE_ITEM_FROM_BODY_TO_STORE(uint16_t packet_id = CZ_MOVE_ITEM_FROM_BODY_TO_STORE) : Horizon::Zone::RE20170927::PACKET_CZ_MOVE_ITEM_FROM_BODY_TO_STORE(packet_id) { }

	/* Size: 8 bytes */
};
}
}
}

#endif /* HORIZON_ZONE_RE_20171002_PACKET_CZ_MOVE_ITEM_FROM_BODY_TO_STORE_HPP */