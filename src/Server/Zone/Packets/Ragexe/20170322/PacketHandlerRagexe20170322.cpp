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

#include "PacketHandlerRagexe20170322.hpp"

using namespace Horizon::Zone;
PacketHandlerRagexe20170322::PacketHandlerRagexe20170322(std::shared_ptr<ZoneSocket> socket)
: PacketHandlerRagexe20170315(socket)
{
	initialize_handlers();
}

PacketHandlerRagexe20170322::~PacketHandlerRagexe20170322()
{
	//
}

void PacketHandlerRagexe20170322::initialize_handlers()
{
	PacketHandler::initialize_handlers();

#define HANDLER_FUNC(packet) add_packet_handler(Ragexe20170322::packets::packet, boost::bind(&PacketHandlerRagexe20170322::Handle_ ## packet, this, boost::placeholders::_1));
#undef HANDLER_FUNC
}