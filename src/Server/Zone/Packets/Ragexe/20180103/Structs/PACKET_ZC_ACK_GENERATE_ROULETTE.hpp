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

#ifndef HORIZON_ZONE_RAGEXE_20180103_PACKET_ZC_ACK_GENERATE_ROULETTE_HPP
#define HORIZON_ZONE_RAGEXE_20180103_PACKET_ZC_ACK_GENERATE_ROULETTE_HPP

#include "Server/Zone/Packets/Ragexe/20180103/PacketsRagexe20180103.hpp"
#include "Server/Zone/Packets/Ragexe/Structs/PACKET_ZC_ACK_GENERATE_ROULETTE.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Ragexe20180103
{
struct PACKET_ZC_ACK_GENERATE_ROULETTE : public Horizon::Zone::Ragexe::PACKET_ZC_ACK_GENERATE_ROULETTE
{
	PACKET_ZC_ACK_GENERATE_ROULETTE(uint16_t packet_id = ZC_ACK_GENERATE_ROULETTE) : Horizon::Zone::Ragexe::PACKET_ZC_ACK_GENERATE_ROULETTE(packet_id) { }

	/* Size: 21 bytes */
};
}
}
}

#endif /* HORIZON_ZONE_RAGEXE_20180103_PACKET_ZC_ACK_GENERATE_ROULETTE_HPP */