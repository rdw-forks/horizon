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

#ifndef HORIZON_ZONE_RE_20180502_PACKET_CZ_SSILIST_ITEM_CLICK_HPP
#define HORIZON_ZONE_RE_20180502_PACKET_CZ_SSILIST_ITEM_CLICK_HPP

#include "Server/Zone/Packets/RE/20180502/PacketsRE20180502.hpp"
#include "Server/Zone/Packets/RE/20180425/Structs/PACKET_CZ_SSILIST_ITEM_CLICK.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace RE20180502
{
struct PACKET_CZ_SSILIST_ITEM_CLICK : public Horizon::Zone::RE20180425::PACKET_CZ_SSILIST_ITEM_CLICK
{
	PACKET_CZ_SSILIST_ITEM_CLICK(uint16_t packet_id = CZ_SSILIST_ITEM_CLICK) : Horizon::Zone::RE20180425::PACKET_CZ_SSILIST_ITEM_CLICK(packet_id) { }

	/* Size: 12 bytes */
};
}
}
}

#endif /* HORIZON_ZONE_RE_20180502_PACKET_CZ_SSILIST_ITEM_CLICK_HPP */