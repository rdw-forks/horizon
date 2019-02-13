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

#include "PacketHandlerZero20171025.hpp"

using namespace Horizon::Zone;
PacketHandlerZero20171025::PacketHandlerZero20171025(std::shared_ptr<ZoneSocket> socket)
: PacketHandlerZero20171024(socket)
{
	initialize_handlers();
}

PacketHandlerZero20171025::~PacketHandlerZero20171025()
{
	//
}

void PacketHandlerZero20171025::initialize_handlers()
{
	PacketHandler::initialize_handlers();

#define HANDLER_FUNC(packet) add_packet_handler(Zero20171025::packets::packet, boost::bind(&PacketHandlerZero20171025::Handle_ ## packet, this, boost::placeholders::_1));
#undef HANDLER_FUNC
}