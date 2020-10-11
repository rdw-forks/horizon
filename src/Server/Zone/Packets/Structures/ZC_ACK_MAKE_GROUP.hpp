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

#ifndef HORIZON_ZONE_ZC_ACK_MAKE_GROUP_HPP
#define HORIZON_ZONE_ZC_ACK_MAKE_GROUP_HPP

#include "Server/Common/Configuration/Horizon.hpp"
#include "Server/Common/Base/NetworkPacket.hpp"

namespace Horizon
{
namespace Zone
{
class AuthSocket;
namespace Packet
{

enum {
#if PACKET_VERSION >= 20090406
	ID_ZC_ACK_MAKE_GROUP = 0x00fa
#elif PACKET_VERSION >= 20090325
	ID_ZC_ACK_MAKE_GROUP = 0x00fa
#elif PACKET_VERSION >= 20090318
	ID_ZC_ACK_MAKE_GROUP = 0x00fa
#elif PACKET_VERSION >= 20090311
	ID_ZC_ACK_MAKE_GROUP = 0x00fa
#elif PACKET_VERSION >= 20090225
	ID_ZC_ACK_MAKE_GROUP = 0x00fa
#elif PACKET_VERSION >= 20090218
	ID_ZC_ACK_MAKE_GROUP = 0x00fa
#elif PACKET_VERSION >= 20090211
	ID_ZC_ACK_MAKE_GROUP = 0x00fa
#elif PACKET_VERSION >= 20090107
	ID_ZC_ACK_MAKE_GROUP = 0x00fa
#elif PACKET_VERSION >= 20081112
	ID_ZC_ACK_MAKE_GROUP = 0x00fa
#elif PACKET_VERSION >= 20081105
	ID_ZC_ACK_MAKE_GROUP = 0x00fa
#elif PACKET_VERSION >= 20081029
	ID_ZC_ACK_MAKE_GROUP = 0x00fa
#elif PACKET_VERSION >= 20081015
	ID_ZC_ACK_MAKE_GROUP = 0x00fa
#elif PACKET_VERSION >= 20081008
	ID_ZC_ACK_MAKE_GROUP = 0x00fa
#elif PACKET_VERSION >= 20080924
	ID_ZC_ACK_MAKE_GROUP = 0x00fa
#elif PACKET_VERSION >= 20080917
	ID_ZC_ACK_MAKE_GROUP = 0x00fa
#elif PACKET_VERSION >= 20080820
	ID_ZC_ACK_MAKE_GROUP = 0x00fa
#elif PACKET_VERSION >= 20080813
	ID_ZC_ACK_MAKE_GROUP = 0x00fa
#elif PACKET_VERSION >= 20080715
	ID_ZC_ACK_MAKE_GROUP = 0x00fa
#elif PACKET_VERSION >= 20080708
	ID_ZC_ACK_MAKE_GROUP = 0x00fa
#elif PACKET_VERSION >= 20080618
	ID_ZC_ACK_MAKE_GROUP = 0x00fa
#elif PACKET_VERSION >= 20080610
	ID_ZC_ACK_MAKE_GROUP = 0x00fa
#elif PACKET_VERSION >= 20080603
	ID_ZC_ACK_MAKE_GROUP = 0x00fa
#elif PACKET_VERSION >= 20080528
	ID_ZC_ACK_MAKE_GROUP = 0x00fa
#elif PACKET_VERSION >= 20080520
	ID_ZC_ACK_MAKE_GROUP = 0x00fa
#elif PACKET_VERSION >= 20080513
	ID_ZC_ACK_MAKE_GROUP = 0x00fa
#elif PACKET_VERSION >= 20080507
	ID_ZC_ACK_MAKE_GROUP = 0x00fa
#elif PACKET_VERSION >= 20080429
	ID_ZC_ACK_MAKE_GROUP = 0x00fa
#elif PACKET_VERSION >= 20080422
	ID_ZC_ACK_MAKE_GROUP = 0x00fa
#elif PACKET_VERSION >= 20080415
	ID_ZC_ACK_MAKE_GROUP = 0x00fa
#elif PACKET_VERSION >= 20080408
	ID_ZC_ACK_MAKE_GROUP = 0x00fa
#elif PACKET_VERSION >= 20080401
	ID_ZC_ACK_MAKE_GROUP = 0x00fa
#elif PACKET_VERSION >= 20080325
	ID_ZC_ACK_MAKE_GROUP = 0x00fa
#elif PACKET_VERSION >= 20080318
	ID_ZC_ACK_MAKE_GROUP = 0x00fa
#elif PACKET_VERSION >= 20080311
	ID_ZC_ACK_MAKE_GROUP = 0x00fa
#elif PACKET_VERSION >= 20080304
	ID_ZC_ACK_MAKE_GROUP = 0x00fa
#elif PACKET_VERSION >= 20080226
	ID_ZC_ACK_MAKE_GROUP = 0x00fa
#elif PACKET_VERSION >= 20080219
	ID_ZC_ACK_MAKE_GROUP = 0x00fa
#elif PACKET_VERSION >= 20080124
	ID_ZC_ACK_MAKE_GROUP = 0x00fa
#elif PACKET_VERSION >= 20080102
	ID_ZC_ACK_MAKE_GROUP = 0x00fa
#elif PACKET_VERSION >= 0
	ID_ZC_ACK_MAKE_GROUP = 0x00fa
#endif
};
/**
 * @brief Main object for the aegis packet: ZC_ACK_MAKE_GROUP
 * Size : 3 @ 0
 *
 */ 
class ZC_ACK_MAKE_GROUP : public Base::NetworkPacket<ZoneSocket>
{
public:
	ZC_ACK_MAKE_GROUP(std::shared_ptr<ZoneSocket> sock);
	~ZC_ACK_MAKE_GROUP();


	void prepare();

private:
	ByteBuffer serialize() override;

protected:
	/* Structure Goes Here */
};
}
}
}
#endif /* HORIZON_ZONE_ZC_ACK_MAKE_GROUP_HPP */