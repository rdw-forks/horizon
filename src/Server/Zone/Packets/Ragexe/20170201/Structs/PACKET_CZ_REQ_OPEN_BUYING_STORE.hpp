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

#ifndef HORIZON_ZONE_RAGEXE_20170201_PACKET_CZ_REQ_OPEN_BUYING_STORE_HPP
#define HORIZON_ZONE_RAGEXE_20170201_PACKET_CZ_REQ_OPEN_BUYING_STORE_HPP

#include "Server/Zone/Packets/Ragexe/20170201/PacketsRagexe20170201.hpp"
#include "Server/Zone/Packets/Ragexe/20170125/Structs/PACKET_CZ_REQ_OPEN_BUYING_STORE.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Ragexe20170201
{
struct PACKET_CZ_REQ_OPEN_BUYING_STORE : public Horizon::Zone::Ragexe20170125::PACKET_CZ_REQ_OPEN_BUYING_STORE
{
	PACKET_CZ_REQ_OPEN_BUYING_STORE(uint16_t packet_id = CZ_REQ_OPEN_BUYING_STORE) : Horizon::Zone::Ragexe20170125::PACKET_CZ_REQ_OPEN_BUYING_STORE(packet_id) { }

	virtual PacketBuffer serialize() override
	{
		return Ragexe20170125::PACKET_CZ_REQ_OPEN_BUYING_STORE::serialize();
	}

	virtual void deserialize(PacketBuffer &buf) override
	{
		Ragexe20170125::PACKET_CZ_REQ_OPEN_BUYING_STORE::deserialize(buf);
	}

	virtual Ragexe20170125::PACKET_CZ_REQ_OPEN_BUYING_STORE & operator << (PacketBuffer &right) override
	{
		deserialize(right);
		return *this;
	}

	virtual PacketBuffer operator >> (PacketBuffer &right) override 
	{
		return right = serialize();
	}

	/* Size: 2 bytes */
	/* Changed from -1 in version 20170125 to 2 */
};
}
}
}

#endif /* HORIZON_ZONE_RAGEXE_20170201_PACKET_CZ_REQ_OPEN_BUYING_STORE_HPP */