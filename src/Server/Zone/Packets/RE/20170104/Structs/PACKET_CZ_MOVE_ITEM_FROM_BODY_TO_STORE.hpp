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

#ifndef HORIZON_ZONE_RE_20170104_PACKET_CZ_MOVE_ITEM_FROM_BODY_TO_STORE_HPP
#define HORIZON_ZONE_RE_20170104_PACKET_CZ_MOVE_ITEM_FROM_BODY_TO_STORE_HPP

#include "Server/Zone/Packets/RE/20170104/PacketsRE20170104.hpp"
#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace RE20170104
{
struct PACKET_CZ_MOVE_ITEM_FROM_BODY_TO_STORE : public Packet
{
	PACKET_CZ_MOVE_ITEM_FROM_BODY_TO_STORE(uint16_t packet_id = CZ_MOVE_ITEM_FROM_BODY_TO_STORE) : Packet(packet_id) { }

	virtual PacketBuffer serialize()
	{
		return PacketBuffer(packet_id);
	}

	virtual void deserialize(PacketBuffer &/*buf*/) { }

	virtual PACKET_CZ_MOVE_ITEM_FROM_BODY_TO_STORE & operator << (PacketBuffer &right)
	{
		deserialize(right);
		return *this;
	}

	virtual PacketBuffer operator >> (PacketBuffer &right)
	{
		return right = serialize();
	}

	/* Size: 8 bytes */
};
}
}
}

#endif /* HORIZON_ZONE_RE_20170104_PACKET_CZ_MOVE_ITEM_FROM_BODY_TO_STORE_HPP */