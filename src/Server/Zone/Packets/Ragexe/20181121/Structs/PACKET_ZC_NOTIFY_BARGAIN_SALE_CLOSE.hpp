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

#ifndef HORIZON_ZONE_RAGEXE_20181121_PACKET_ZC_NOTIFY_BARGAIN_SALE_CLOSE_HPP
#define HORIZON_ZONE_RAGEXE_20181121_PACKET_ZC_NOTIFY_BARGAIN_SALE_CLOSE_HPP

#include "Server/Zone/Packets/Ragexe/20181121/PacketsRagexe20181121.hpp"
#include "Server/Zone/Packets/Ragexe/20180103/Structs/PACKET_ZC_NOTIFY_BARGAIN_SALE_CLOSE.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Ragexe20181121
{
struct PACKET_ZC_NOTIFY_BARGAIN_SALE_CLOSE : public Horizon::Zone::Ragexe20180103::PACKET_ZC_NOTIFY_BARGAIN_SALE_CLOSE
{
	PACKET_ZC_NOTIFY_BARGAIN_SALE_CLOSE(uint16_t packet_id = ZC_NOTIFY_BARGAIN_SALE_CLOSE) : Horizon::Zone::Ragexe20180103::PACKET_ZC_NOTIFY_BARGAIN_SALE_CLOSE(packet_id) { }

	virtual PacketBuffer serialize() override
	{
		return Ragexe20180103::PACKET_ZC_NOTIFY_BARGAIN_SALE_CLOSE::serialize();
	}

	virtual void deserialize(PacketBuffer &buf) override
	{
		Ragexe20180103::PACKET_ZC_NOTIFY_BARGAIN_SALE_CLOSE::deserialize(buf);
	}

	virtual Ragexe20180103::PACKET_ZC_NOTIFY_BARGAIN_SALE_CLOSE & operator << (PacketBuffer &right) override
	{
		deserialize(right);
		return *this;
	}

	virtual PacketBuffer operator >> (PacketBuffer &right) override 
	{
		return right = serialize();
	}

	/* Size: 6 bytes */
	/* Changed from 4 in version 20180103 to 6 */
};
}
}
}

#endif /* HORIZON_ZONE_RAGEXE_20181121_PACKET_ZC_NOTIFY_BARGAIN_SALE_CLOSE_HPP */