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

#ifndef HORIZON_ZONE_RE_20171122_PACKET_CZ_ITEMLISTWIN_RES_HPP
#define HORIZON_ZONE_RE_20171122_PACKET_CZ_ITEMLISTWIN_RES_HPP

#include "Server/Zone/Packets/RE/20171122/PacketsRE20171122.hpp"
#include "Server/Zone/Packets/RE/20171115/Structs/PACKET_CZ_ITEMLISTWIN_RES.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace RE20171122
{
struct PACKET_CZ_ITEMLISTWIN_RES : public Horizon::Zone::RE20171115::PACKET_CZ_ITEMLISTWIN_RES
{
	PACKET_CZ_ITEMLISTWIN_RES(uint16_t packet_id = CZ_ITEMLISTWIN_RES) : Horizon::Zone::RE20171115::PACKET_CZ_ITEMLISTWIN_RES(packet_id) { }

	/* Size: -1 bytes */
};
}
}
}

#endif /* HORIZON_ZONE_RE_20171122_PACKET_CZ_ITEMLISTWIN_RES_HPP */