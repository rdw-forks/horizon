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

#ifndef HORIZON_ZONE_ZERO_20180822_PACKET_ZC_STORE_ITEMLIST_EQUIP_V6_HPP
#define HORIZON_ZONE_ZERO_20180822_PACKET_ZC_STORE_ITEMLIST_EQUIP_V6_HPP

#include "Server/Zone/Packets/Zero/20180822/PacketsZero20180822.hpp"
#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Zero20180822
{
struct PACKET_ZC_STORE_ITEMLIST_EQUIP_V6 : public Packet
{
	PACKET_ZC_STORE_ITEMLIST_EQUIP_V6(uint16_t packet_id = ZC_STORE_ITEMLIST_EQUIP_V6) : Packet(packet_id) { }

	virtual PacketBuffer serialize()
	{
		return PacketBuffer(packet_id);
	}

	virtual void deserialize(PacketBuffer &/*buf*/) { }

	virtual PACKET_ZC_STORE_ITEMLIST_EQUIP_V6 & operator << (PacketBuffer &right)
	{
		deserialize(right);
		return *this;
	}

	virtual PacketBuffer operator >> (PacketBuffer &right)
	{
		return right = serialize();
	}

	/* Size: -1 bytes */
};
}
}
}

#endif /* HORIZON_ZONE_ZERO_20180822_PACKET_ZC_STORE_ITEMLIST_EQUIP_V6_HPP */