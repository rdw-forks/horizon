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

#include "PacketHandlerRE20170222.hpp"

using namespace Horizon::Zone;
PacketHandlerRE20170222::PacketHandlerRE20170222(std::shared_ptr<ZoneSocket> socket)
: PacketHandlerRE20170215(socket)
{
	initialize_handlers();
}

PacketHandlerRE20170222::~PacketHandlerRE20170222()
{
	//
}

void PacketHandlerRE20170222::initialize_handlers()
{
	PacketHandler::initialize_handlers();

#define HANDLER_FUNC(packet) add_packet_handler(RE20170222::packets::packet, boost::bind(&PacketHandlerRE20170222::Handle_ ## packet, this, boost::placeholders::_1));
#undef HANDLER_FUNC
}