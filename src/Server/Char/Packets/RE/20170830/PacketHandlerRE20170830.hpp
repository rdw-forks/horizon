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

#ifndef HORIZON_CHAR_RE_20170830_PACKETHANDLER_HPP
#define HORIZON_CHAR_RE_20170830_PACKETHANDLER_HPP

#include "Server/Common/PacketBuffer.hpp"
#include "Server/Char/Packets/RE/20170830/Structs/PACKET_HC_ACCEPT_MAKECHAR.hpp"
#include "Server/Char/Packets/RE/20170830/Structs/PACKET_HC_UPDATE_CHARINFO.hpp"
#include "Server/Char/Packets/RE/20170228/PacketHandlerRE20170228.hpp"

namespace Horizon
{
namespace Char
{

class CharSocket;

class PacketHandlerRE20170830 : public PacketHandlerRE20170228
{
public:
	PacketHandlerRE20170830(std::shared_ptr<CharSocket> socket);
	~PacketHandlerRE20170830();

	virtual void initialize_handlers() override;

};
}
}

#endif /* HORIZON_CHAR_RE_20170830_PACKETHANDLER_HPP */