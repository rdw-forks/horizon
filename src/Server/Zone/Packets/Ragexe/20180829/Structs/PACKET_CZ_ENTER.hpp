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

#ifndef HORIZON_ZONE_RAGEXE_20180829_PACKET_CZ_ENTER_HPP
#define HORIZON_ZONE_RAGEXE_20180829_PACKET_CZ_ENTER_HPP

#include "Server/Zone/Packets/Ragexe/20180829/PacketsRagexe20180829.hpp"
#include "Server/Zone/Packets/Ragexe/20180822/Structs/PACKET_CZ_ENTER.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Ragexe20180829
{
struct PACKET_CZ_ENTER : public Horizon::Zone::Ragexe20180822::PACKET_CZ_ENTER
{
	PACKET_CZ_ENTER(uint16_t packet_id = CZ_ENTER) : Horizon::Zone::Ragexe20180822::PACKET_CZ_ENTER(packet_id) { }

	/* Size: 19 bytes */
};
}
}
}

#endif /* HORIZON_ZONE_RAGEXE_20180829_PACKET_CZ_ENTER_HPP */