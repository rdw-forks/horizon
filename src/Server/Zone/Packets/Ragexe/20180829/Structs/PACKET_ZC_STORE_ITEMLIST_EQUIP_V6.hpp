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

#ifndef HORIZON_ZONE_RAGEXE_20180829_PACKET_ZC_STORE_ITEMLIST_EQUIP_V6_HPP
#define HORIZON_ZONE_RAGEXE_20180829_PACKET_ZC_STORE_ITEMLIST_EQUIP_V6_HPP

#include "Server/Zone/Packets/Ragexe/20180829/PacketsRagexe20180829.hpp"
#include "Server/Zone/Packets/Ragexe/Structs/PACKET_ZC_STORE_ITEMLIST_EQUIP_V6.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Ragexe20180829
{
struct PACKET_ZC_STORE_ITEMLIST_EQUIP_V6 : public Horizon::Zone::Ragexe::PACKET_ZC_STORE_ITEMLIST_EQUIP_V6
{
	PACKET_ZC_STORE_ITEMLIST_EQUIP_V6(uint16_t packet_id = ZC_STORE_ITEMLIST_EQUIP_V6) : Horizon::Zone::Ragexe::PACKET_ZC_STORE_ITEMLIST_EQUIP_V6(packet_id) { }

	/* Size: -1 bytes */
};
}
}
}

#endif /* HORIZON_ZONE_RAGEXE_20180829_PACKET_ZC_STORE_ITEMLIST_EQUIP_V6_HPP */