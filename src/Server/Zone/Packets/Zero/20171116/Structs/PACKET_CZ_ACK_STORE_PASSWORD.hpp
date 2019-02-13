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

#ifndef HORIZON_ZONE_ZERO_20171116_PACKET_CZ_ACK_STORE_PASSWORD_HPP
#define HORIZON_ZONE_ZERO_20171116_PACKET_CZ_ACK_STORE_PASSWORD_HPP

#include "Server/Zone/Packets/Zero/20171116/PacketsZero20171116.hpp"
#include "Server/Zone/Packets/Zero/20171115/Structs/PACKET_CZ_ACK_STORE_PASSWORD.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Zero20171116
{
struct PACKET_CZ_ACK_STORE_PASSWORD : public Horizon::Zone::Zero20171115::PACKET_CZ_ACK_STORE_PASSWORD
{
	PACKET_CZ_ACK_STORE_PASSWORD(uint16_t packet_id = CZ_ACK_STORE_PASSWORD) : Horizon::Zone::Zero20171115::PACKET_CZ_ACK_STORE_PASSWORD(packet_id) { }

	virtual PacketBuffer serialize() override
	{
		return Zero20171115::PACKET_CZ_ACK_STORE_PASSWORD::serialize();
	}

	virtual void deserialize(PacketBuffer &buf) override
	{
		Zero20171115::PACKET_CZ_ACK_STORE_PASSWORD::deserialize(buf);
	}

	virtual Zero20171115::PACKET_CZ_ACK_STORE_PASSWORD & operator << (PacketBuffer &right) override
	{
		deserialize(right);
		return *this;
	}

	virtual PacketBuffer operator >> (PacketBuffer &right) override 
	{
		return right = serialize();
	}

	/* Size: 36 bytes */
	/* Changed from 2 in version 20171115 to 36 */
};
}
}
}

#endif /* HORIZON_ZONE_ZERO_20171116_PACKET_CZ_ACK_STORE_PASSWORD_HPP */