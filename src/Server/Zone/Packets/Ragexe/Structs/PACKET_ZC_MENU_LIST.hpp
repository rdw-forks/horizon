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

#ifndef HORIZON_ZONE_RAGEXE_PACKET_ZC_MENU_LIST_HPP
#define HORIZON_ZONE_RAGEXE_PACKET_ZC_MENU_LIST_HPP


#include "Server/Zone/Packets/Ragexe/Packets.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Ragexe
{
struct PACKET_ZC_MENU_LIST : public Packet
{
	PACKET_ZC_MENU_LIST(uint16_t packet_id = ZC_MENU_LIST) : Packet(packet_id) { }

	virtual PacketBuffer serialize(std::string menu_items)
	{
		PacketBuffer buf(packet_id);

		packet_length = menu_items.size() + 8;
		buf << packet_length;
		buf << guid;
		buf.append(menu_items.c_str(), menu_items.size());

		return buf;
	}

	virtual void deserialize(PacketBuffer &/*buf*/) { }

	virtual PACKET_ZC_MENU_LIST & operator << (PacketBuffer &right)
	{
		deserialize(right);
		return *this;
	}

	/* Size: -1 bytes */
	uint16_t packet_length{0};
	uint32_t guid{0};
};
}
}
}

#endif /* HORIZON_ZONE_RAGEXE_PACKET_ZC_MENU_LIST_HPP */