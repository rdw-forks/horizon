/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 * Copyright (c) 2019 Sagun K. (sagunxp@gmail.com).
 * Copyright (c) 2019 Horizon Dev Team.
 *
 * Base Author - Sagun K. (sagunxp@gmail.com)
 *
 * This library is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 **************************************************/

#ifndef HORIZON_ZONE_RAGEXE_PACKET_ZC_ACCEPT_ENTER2_HPP
#define HORIZON_ZONE_RAGEXE_PACKET_ZC_ACCEPT_ENTER2_HPP


#include "Server/Zone/Packets/Ragexe/Packets.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Ragexe
{
struct PACKET_ZC_ACCEPT_ENTER2 : public Packet
{
	PACKET_ZC_ACCEPT_ENTER2(uint16_t packet_id = ZC_ACCEPT_ENTER2) : Packet(packet_id) { }

	virtual PacketBuffer serialize(uint16_t x, uint16_t y, uint16_t dir)
	{
		PacketBuffer buf(packet_id);

		buf << start_time;
		PackPosition((int8_t *) packed_pos, x, y, dir);
		buf.append(packed_pos, sizeof(packed_pos));
		buf << x_size << y_size << font;

		return buf;
	}

	virtual void deserialize(PacketBuffer &/*buf*/) { }

	virtual PACKET_ZC_ACCEPT_ENTER2 & operator << (PacketBuffer &right)
	{
		deserialize(right);
		return *this;
	}

	/* Size: 13 bytes */
	uint32_t start_time{0};
	char packed_pos[3]{0};
	uint8_t x_size{0};
	uint8_t y_size{0};
	uint16_t font{0};
};
}
}
}

#endif /* HORIZON_ZONE_RAGEXE_PACKET_ZC_ACCEPT_ENTER2_HPP */
