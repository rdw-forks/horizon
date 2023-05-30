/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 *
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
#ifndef HORIZON_ZONE_SESSION_ZONESESSION_HPP
#define HORIZON_ZONE_SESSION_ZONESESSION_HPP

#include "Libraries/Networking/Session.hpp"
#include "Server/Common/Configuration/Horizon.hpp"
#include "Server/Common/Configuration/ServerConfiguration.hpp"
#include "Server/Zone/Interface/ZoneClientInterface.hpp"
#include "Server/Zone/Game/Entities/Player/Player.hpp"

#if CLIENT_TYPE == 'R'
#include "Server/Zone/Packets/RE/ClientPacketLengthTable.hpp"
#elif CLIENT_TYPE == 'M'
#include "Server/Zone/Packets/Main/ClientPacketLengthTable.hpp"
#elif CLIENT_TYPE == 'S'
#include "Server/Zone/Packets/Sakray/ClientPacketLengthTable.hpp"
#elif CLIENT_TYPE == 'Z'
#include "Server/Zone/Packets/Zero/ClientPacketLengthTable.hpp"
#elif CLIENT_TYPE == 'A'
#include "Server/Zone/Packets/Ad/ClientPacketLengthTable.hpp"
#endif

namespace Horizon
{
namespace Zone
{
class ZoneSocket;
class ZoneSession : public Horizon::Networking::Session<ZoneSocket, ZoneSession>
{
public:
	ZoneSession(std::shared_ptr<ZoneSocket> socket);
	~ZoneSession();

	void transmit_buffer(ByteBuffer _buffer, std::size_t size);

	void update(uint32_t diff);

	void perform_cleanup();

	void initialize();
	
	std::unique_ptr<ZoneClientInterface> &clif() { return _clif; }
	std::unique_ptr<ClientPacketLengthTable> &pkt_tbl() { return _pkt_tbl; }
	std::shared_ptr<Entities::Player> player() { return _player.expired() ? nullptr : _player.lock(); }
	void set_player(std::shared_ptr<Entities::Player> pl) { _player = pl; }

protected:
	std::unique_ptr<ZoneClientInterface> _clif;
	std::unique_ptr<ClientPacketLengthTable> _pkt_tbl;
	std::weak_ptr<Entities::Player> _player;
};
}
}

#endif
