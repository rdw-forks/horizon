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

#ifndef HORIZON_ZONE_RE_20170607_PACKET_CZ_ENTER_HPP
#define HORIZON_ZONE_RE_20170607_PACKET_CZ_ENTER_HPP

#include "Server/Zone/Packets/RE/20170607/PacketsRE20170607.hpp"
#include "Server/Zone/Packets/RE/20170531/Structs/PACKET_CZ_ENTER.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace RE20170607
{
struct PACKET_CZ_ENTER : public Horizon::Zone::RE20170531::PACKET_CZ_ENTER
{
	PACKET_CZ_ENTER(uint16_t packet_id = CZ_ENTER) : Horizon::Zone::RE20170531::PACKET_CZ_ENTER(packet_id) { }

	/* Size: 19 bytes */
};
}
}
}

#endif /* HORIZON_ZONE_RE_20170607_PACKET_CZ_ENTER_HPP */