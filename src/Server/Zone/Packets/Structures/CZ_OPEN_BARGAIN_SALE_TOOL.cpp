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

#include "CZ_OPEN_BARGAIN_SALE_TOOL.hpp"
#include "Server/Zone/Socket/ZoneSocket.hpp"

using namespace Horizon::Zone::Packet;

CZ_OPEN_BARGAIN_SALE_TOOL::CZ_OPEN_BARGAIN_SALE_TOOL(std::shared_ptr<ZoneSocket> sock)
: NetworkPacket(ID_CZ_OPEN_BARGAIN_SALE_TOOL, sock) { }

CZ_OPEN_BARGAIN_SALE_TOOL::~CZ_OPEN_BARGAIN_SALE_TOOL() { }

void CZ_OPEN_BARGAIN_SALE_TOOL::handle(ByteBuffer &buf)
{
}

void CZ_OPEN_BARGAIN_SALE_TOOL::deserialize(ByteBuffer &buf)
{
}
