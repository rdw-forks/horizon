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

#ifndef HORIZON_ZONE_RAGEXE_20170906_PACKET_CZ_REQ_OPEN_BUYING_STORE_HPP
#define HORIZON_ZONE_RAGEXE_20170906_PACKET_CZ_REQ_OPEN_BUYING_STORE_HPP

#include "Server/Zone/Packets/Ragexe/20170906/PacketsRagexe20170906.hpp"
#include "Server/Zone/Packets/Ragexe/20170830/Structs/PACKET_CZ_REQ_OPEN_BUYING_STORE.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Ragexe20170906
{
struct PACKET_CZ_REQ_OPEN_BUYING_STORE : public Horizon::Zone::Ragexe20170830::PACKET_CZ_REQ_OPEN_BUYING_STORE
{
	PACKET_CZ_REQ_OPEN_BUYING_STORE(uint16_t packet_id = CZ_REQ_OPEN_BUYING_STORE) : Horizon::Zone::Ragexe20170830::PACKET_CZ_REQ_OPEN_BUYING_STORE(packet_id) { }

	virtual PacketBuffer serialize() override
	{
		return Ragexe20170830::PACKET_CZ_REQ_OPEN_BUYING_STORE::serialize();
	}

	virtual void deserialize(PacketBuffer &buf) override
	{
		Ragexe20170830::PACKET_CZ_REQ_OPEN_BUYING_STORE::deserialize(buf);
	}

	virtual Ragexe20170830::PACKET_CZ_REQ_OPEN_BUYING_STORE & operator << (PacketBuffer &right) override
	{
		deserialize(right);
		return *this;
	}

	virtual PacketBuffer operator >> (PacketBuffer &right) override 
	{
		return right = serialize();
	}

	/* Size: -1 bytes */
	/* Changed from 2 in version 20170830 to -1 */
};
}
}
}

#endif /* HORIZON_ZONE_RAGEXE_20170906_PACKET_CZ_REQ_OPEN_BUYING_STORE_HPP */