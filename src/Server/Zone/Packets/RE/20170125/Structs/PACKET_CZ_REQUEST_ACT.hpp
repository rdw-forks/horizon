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

#ifndef HORIZON_ZONE_RE_20170125_PACKET_CZ_REQUEST_ACT_HPP
#define HORIZON_ZONE_RE_20170125_PACKET_CZ_REQUEST_ACT_HPP

#include "Server/Zone/Packets/RE/20170125/PacketsRE20170125.hpp"
#include "Server/Zone/Packets/RE/20170118/Structs/PACKET_CZ_REQUEST_ACT.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace RE20170125
{
struct PACKET_CZ_REQUEST_ACT : public Horizon::Zone::RE20170118::PACKET_CZ_REQUEST_ACT
{
	PACKET_CZ_REQUEST_ACT(uint16_t packet_id = CZ_REQUEST_ACT) : Horizon::Zone::RE20170118::PACKET_CZ_REQUEST_ACT(packet_id) { }

	/* Size: 7 bytes */
};
}
}
}

#endif /* HORIZON_ZONE_RE_20170125_PACKET_CZ_REQUEST_ACT_HPP */