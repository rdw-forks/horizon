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

#ifndef HORIZON_AUTH_RAGEXE_20170621_PACKETHANDLER_HPP
#define HORIZON_AUTH_RAGEXE_20170621_PACKETHANDLER_HPP

#include "Server/Common/PacketBuffer.hpp"
#include "Server/Auth/Packets/Ragexe/20170621/Structs/PACKET_CA_LOGIN_OTP.hpp"
#include "Server/Auth/Packets/Ragexe/20170614/PacketHandlerRagexe20170614.hpp"

namespace Horizon
{
namespace Auth
{

class AuthSocket;

class PacketHandlerRagexe20170621 : public PacketHandlerRagexe20170614
{
public:
	PacketHandlerRagexe20170621(std::shared_ptr<AuthSocket> socket);
	~PacketHandlerRagexe20170621();

	virtual void initialize_handlers() override;

};
}
}

#endif /* HORIZON_AUTH_Ragexe_20170621_PACKETHANDLER_HPP */