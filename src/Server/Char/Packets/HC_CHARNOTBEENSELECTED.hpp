/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 * Copyright (c) 2020- Horizon Dev Team.
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

#ifndef HORIZON_HC_CHARNOTBEENSELECTED_HPP
#define HORIZON_HC_CHARNOTBEENSELECTED_HPP

#include "Server/Common/Configuration/Horizon.hpp"
#include "Server/Common/Base/NetworkPacket.hpp"

namespace Horizon
{
namespace Char
{
class CharSession;
enum {
#if PACKET_VERSION >= 20061030
	ID_HC_CHARNOTBEENSELECTED = 0x028b
#elif PACKET_VERSION >= 20061023
	ID_HC_CHARNOTBEENSELECTED = 0x028b
#elif PACKET_VERSION >= 0
	ID_HC_CHARNOTBEENSELECTED = 0x028b
#endif
};
/**
 * @brief Main object for the aegis packet: HC_CHARNOTBEENSELECTED
 * Size : -1 @ 0
 *
 */ 
class HC_CHARNOTBEENSELECTED : public Base::NetworkPacket<CharSession>
{
public:
	HC_CHARNOTBEENSELECTED(std::shared_ptr<CharSession> s);
	virtual ~HC_CHARNOTBEENSELECTED();


	void deliver();
	ByteBuffer &serialize();
	virtual void handle(ByteBuffer &&buf) override;
	void deserialize(ByteBuffer &buf);

protected:
	/* Structure Goes Here */
};
}
}

#endif /* HORIZON_HC_CHARNOTBEENSELECTED_HPP */