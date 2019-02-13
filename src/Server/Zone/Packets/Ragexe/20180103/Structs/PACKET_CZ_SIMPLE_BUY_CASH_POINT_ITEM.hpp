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

#ifndef HORIZON_ZONE_RAGEXE_20180103_PACKET_CZ_SIMPLE_BUY_CASH_POINT_ITEM_HPP
#define HORIZON_ZONE_RAGEXE_20180103_PACKET_CZ_SIMPLE_BUY_CASH_POINT_ITEM_HPP

#include "Server/Zone/Packets/Ragexe/20180103/PacketsRagexe20180103.hpp"
#include "Server/Zone/Packets/Ragexe/Structs/PACKET_CZ_SIMPLE_BUY_CASH_POINT_ITEM.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Ragexe20180103
{
struct PACKET_CZ_SIMPLE_BUY_CASH_POINT_ITEM : public Horizon::Zone::Ragexe::PACKET_CZ_SIMPLE_BUY_CASH_POINT_ITEM
{
	PACKET_CZ_SIMPLE_BUY_CASH_POINT_ITEM(uint16_t packet_id = CZ_SIMPLE_BUY_CASH_POINT_ITEM) : Horizon::Zone::Ragexe::PACKET_CZ_SIMPLE_BUY_CASH_POINT_ITEM(packet_id) { }

	/* Size: 10 bytes */
};
}
}
}

#endif /* HORIZON_ZONE_RAGEXE_20180103_PACKET_CZ_SIMPLE_BUY_CASH_POINT_ITEM_HPP */