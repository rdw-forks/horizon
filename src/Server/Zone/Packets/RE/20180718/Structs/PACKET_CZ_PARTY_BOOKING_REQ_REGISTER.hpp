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

#ifndef HORIZON_ZONE_RE_20180718_PACKET_CZ_PARTY_BOOKING_REQ_REGISTER_HPP
#define HORIZON_ZONE_RE_20180718_PACKET_CZ_PARTY_BOOKING_REQ_REGISTER_HPP

#include "Server/Zone/Packets/RE/20180718/PacketsRE20180718.hpp"
#include "Server/Zone/Packets/RE/20180711/Structs/PACKET_CZ_PARTY_BOOKING_REQ_REGISTER.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace RE20180718
{
struct PACKET_CZ_PARTY_BOOKING_REQ_REGISTER : public Horizon::Zone::RE20180711::PACKET_CZ_PARTY_BOOKING_REQ_REGISTER
{
	PACKET_CZ_PARTY_BOOKING_REQ_REGISTER(uint16_t packet_id = CZ_PARTY_BOOKING_REQ_REGISTER) : Horizon::Zone::RE20180711::PACKET_CZ_PARTY_BOOKING_REQ_REGISTER(packet_id) { }

	/* Size: 18 bytes */
};
}
}
}

#endif /* HORIZON_ZONE_RE_20180718_PACKET_CZ_PARTY_BOOKING_REQ_REGISTER_HPP */