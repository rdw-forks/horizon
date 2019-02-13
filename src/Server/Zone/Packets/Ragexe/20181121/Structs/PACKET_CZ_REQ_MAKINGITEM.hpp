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

#ifndef HORIZON_ZONE_RAGEXE_20181121_PACKET_CZ_REQ_MAKINGITEM_HPP
#define HORIZON_ZONE_RAGEXE_20181121_PACKET_CZ_REQ_MAKINGITEM_HPP

#include "Server/Zone/Packets/Ragexe/20181121/PacketsRagexe20181121.hpp"
#include "Server/Zone/Packets/Ragexe/20180103/Structs/PACKET_CZ_REQ_MAKINGITEM.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Ragexe20181121
{
struct PACKET_CZ_REQ_MAKINGITEM : public Horizon::Zone::Ragexe20180103::PACKET_CZ_REQ_MAKINGITEM
{
	PACKET_CZ_REQ_MAKINGITEM(uint16_t packet_id = CZ_REQ_MAKINGITEM) : Horizon::Zone::Ragexe20180103::PACKET_CZ_REQ_MAKINGITEM(packet_id) { }

	virtual PacketBuffer serialize() override
	{
		return Ragexe20180103::PACKET_CZ_REQ_MAKINGITEM::serialize();
	}

	virtual void deserialize(PacketBuffer &buf) override
	{
		Ragexe20180103::PACKET_CZ_REQ_MAKINGITEM::deserialize(buf);
	}

	virtual Ragexe20180103::PACKET_CZ_REQ_MAKINGITEM & operator << (PacketBuffer &right) override
	{
		deserialize(right);
		return *this;
	}

	virtual PacketBuffer operator >> (PacketBuffer &right) override 
	{
		return right = serialize();
	}

	/* Size: 8 bytes */
	/* Changed from 6 in version 20180103 to 8 */
};
}
}
}

#endif /* HORIZON_ZONE_RAGEXE_20181121_PACKET_CZ_REQ_MAKINGITEM_HPP */