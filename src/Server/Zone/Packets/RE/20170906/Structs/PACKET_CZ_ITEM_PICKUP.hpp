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

#ifndef HORIZON_ZONE_RE_20170906_PACKET_CZ_ITEM_PICKUP_HPP
#define HORIZON_ZONE_RE_20170906_PACKET_CZ_ITEM_PICKUP_HPP

#include "Server/Zone/Packets/RE/20170906/PacketsRE20170906.hpp"
#include "Server/Zone/Packets/RE/20170830/Structs/PACKET_CZ_ITEM_PICKUP.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace RE20170906
{
struct PACKET_CZ_ITEM_PICKUP : public Horizon::Zone::RE20170830::PACKET_CZ_ITEM_PICKUP
{
	PACKET_CZ_ITEM_PICKUP(uint16_t packet_id = CZ_ITEM_PICKUP) : Horizon::Zone::RE20170830::PACKET_CZ_ITEM_PICKUP(packet_id) { }

	/* Size: 6 bytes */
};
}
}
}

#endif /* HORIZON_ZONE_RE_20170906_PACKET_CZ_ITEM_PICKUP_HPP */