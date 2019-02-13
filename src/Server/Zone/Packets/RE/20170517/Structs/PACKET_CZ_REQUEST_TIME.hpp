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

#ifndef HORIZON_ZONE_RE_20170517_PACKET_CZ_REQUEST_TIME_HPP
#define HORIZON_ZONE_RE_20170517_PACKET_CZ_REQUEST_TIME_HPP

#include "Server/Zone/Packets/RE/20170517/PacketsRE20170517.hpp"
#include "Server/Zone/Packets/RE/20170502/Structs/PACKET_CZ_REQUEST_TIME.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace RE20170517
{
struct PACKET_CZ_REQUEST_TIME : public Horizon::Zone::RE20170502::PACKET_CZ_REQUEST_TIME
{
	PACKET_CZ_REQUEST_TIME(uint16_t packet_id = CZ_REQUEST_TIME) : Horizon::Zone::RE20170502::PACKET_CZ_REQUEST_TIME(packet_id) { }

	/* Size: 6 bytes */
};
}
}
}

#endif /* HORIZON_ZONE_RE_20170517_PACKET_CZ_REQUEST_TIME_HPP */