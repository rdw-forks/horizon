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

#ifndef HORIZON_ZONE_ZERO_20180117_PACKET_CZ_ITEMLISTWIN_RES_HPP
#define HORIZON_ZONE_ZERO_20180117_PACKET_CZ_ITEMLISTWIN_RES_HPP

#include "Server/Zone/Packets/Zero/20180117/PacketsZero20180117.hpp"
#include "Server/Zone/Packets/Zero/20180103/Structs/PACKET_CZ_ITEMLISTWIN_RES.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Zero20180117
{
struct PACKET_CZ_ITEMLISTWIN_RES : public Horizon::Zone::Zero20180103::PACKET_CZ_ITEMLISTWIN_RES
{
	PACKET_CZ_ITEMLISTWIN_RES(uint16_t packet_id = CZ_ITEMLISTWIN_RES) : Horizon::Zone::Zero20180103::PACKET_CZ_ITEMLISTWIN_RES(packet_id) { }

	/* Size: -1 bytes */
};
}
}
}

#endif /* HORIZON_ZONE_ZERO_20180117_PACKET_CZ_ITEMLISTWIN_RES_HPP */