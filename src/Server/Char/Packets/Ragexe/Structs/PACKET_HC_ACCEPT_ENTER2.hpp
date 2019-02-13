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

#ifndef HORIZON_CHAR_RAGEXE_PACKET_HC_ACCEPT_ENTER2_HPP
#define HORIZON_CHAR_RAGEXE_PACKET_HC_ACCEPT_ENTER2_HPP


#include "Server/Char/Packets/Ragexe/Packets.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Char
{
namespace Ragexe
{
struct PACKET_HC_ACCEPT_ENTER2 : public Packet
{
	PACKET_HC_ACCEPT_ENTER2(uint16_t packet_id = HC_ACCEPT_ENTER2) : Packet(packet_id) { }

	virtual PacketBuffer serialize()
	{
		PacketBuffer buf(HC_ACCEPT_ENTER2);

		buf << packet_length;
		buf << total_slots;
		buf << premium_slots;
		buf << unknown_byte;
		buf << char_slots_1;
		buf << char_slots_2;
		buf.append(unknown_bytes, sizeof(unknown_bytes));
		return buf;
	}

	virtual void deserialize(PacketBuffer &/*buf*/) { }

	virtual PACKET_HC_ACCEPT_ENTER2 & operator << (PacketBuffer &right)
	{
		deserialize(right);
		return *this;
	}

	virtual PacketBuffer operator >> (PacketBuffer &right)
	{
		return right = serialize();
	}

	virtual uint16_t get_length(uint8_t max_chars = 0) { return 29; }

	/* Size: -1 bytes */
	uint16_t packet_length{29};
	uint8_t total_slots{MAX_CHARACTER_SLOTS};
	uint8_t premium_slots{MAX_CHARACTER_SLOTS};
	uint8_t unknown_byte{0};
	uint8_t char_slots_1{MAX_CHARACTER_SLOTS};
	uint8_t char_slots_2{MAX_CHARACTER_SLOTS};
	uint8_t unknown_bytes[20]{0};
};
}
}
}

#endif /* HORIZON_CHAR_RAGEXE_PACKET_HC_ACCEPT_ENTER2_HPP */