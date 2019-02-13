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

#ifndef HORIZON_ZONE_ZERO_20171123_PACKET_CZ_COMMAND_MER_HPP
#define HORIZON_ZONE_ZERO_20171123_PACKET_CZ_COMMAND_MER_HPP

#include "Server/Zone/Packets/Zero/20171123/PacketsZero20171123.hpp"
#include "Server/Zone/Packets/Zero/20171122/Structs/PACKET_CZ_COMMAND_MER.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Zero20171123
{
struct PACKET_CZ_COMMAND_MER : public Horizon::Zone::Zero20171122::PACKET_CZ_COMMAND_MER
{
	PACKET_CZ_COMMAND_MER(uint16_t packet_id = CZ_COMMAND_MER) : Horizon::Zone::Zero20171122::PACKET_CZ_COMMAND_MER(packet_id) { }

	virtual PacketBuffer serialize() override
	{
		return Zero20171122::PACKET_CZ_COMMAND_MER::serialize();
	}

	virtual void deserialize(PacketBuffer &buf) override
	{
		Zero20171122::PACKET_CZ_COMMAND_MER::deserialize(buf);
	}

	virtual Zero20171122::PACKET_CZ_COMMAND_MER & operator << (PacketBuffer &right) override
	{
		deserialize(right);
		return *this;
	}

	virtual PacketBuffer operator >> (PacketBuffer &right) override 
	{
		return right = serialize();
	}

	/* Size: 2 bytes */
	/* Changed from 5 in version 20171122 to 2 */
};
}
}
}

#endif /* HORIZON_ZONE_ZERO_20171123_PACKET_CZ_COMMAND_MER_HPP */