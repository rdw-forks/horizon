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

#ifndef HORIZON_ZONE_ZERO_PACKET_ZC_ITEM_FALL_ENTRY_HPP
#define HORIZON_ZONE_ZERO_PACKET_ZC_ITEM_FALL_ENTRY_HPP


#include "Server/Zone/Packets/Zero/Packets.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Zero
{
struct PACKET_ZC_ITEM_FALL_ENTRY : public Packet
{
	PACKET_ZC_ITEM_FALL_ENTRY(uint16_t packet_id = ZC_ITEM_FALL_ENTRY) : Packet(packet_id) { }

	virtual PacketBuffer serialize()
	{
		return PacketBuffer(packet_id);
	}

	virtual void deserialize(PacketBuffer &/*buf*/) { }

	virtual PACKET_ZC_ITEM_FALL_ENTRY & operator << (PacketBuffer &right)
	{
		deserialize(right);
		return *this;
	}

	virtual PacketBuffer operator >> (PacketBuffer &right)
	{
		return right = serialize();
	}

	/* Size: 22 bytes */
};
}
}
}

#endif /* HORIZON_ZONE_ZERO_PACKET_ZC_ITEM_FALL_ENTRY_HPP */