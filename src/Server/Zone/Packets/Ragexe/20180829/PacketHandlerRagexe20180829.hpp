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

#ifndef HORIZON_ZONE_RAGEXE_20180829_PACKETHANDLER_HPP
#define HORIZON_ZONE_RAGEXE_20180829_PACKETHANDLER_HPP

#include "Server/Common/PacketBuffer.hpp"
#include "Server/Zone/Packets/Ragexe/20180829/Structs/PACKET_CZ_ACK_STORE_PASSWORD.hpp"
#include "Server/Zone/Packets/Ragexe/20180829/Structs/PACKET_CZ_ADD_FRIENDS.hpp"
#include "Server/Zone/Packets/Ragexe/20180829/Structs/PACKET_CZ_CHANGE_DIRECTION.hpp"
#include "Server/Zone/Packets/Ragexe/20180829/Structs/PACKET_CZ_COMMAND_MER.hpp"
#include "Server/Zone/Packets/Ragexe/20180829/Structs/PACKET_CZ_ENTER.hpp"
#include "Server/Zone/Packets/Ragexe/20180829/Structs/PACKET_CZ_GANGSI_RANK.hpp"
#include "Server/Zone/Packets/Ragexe/20180829/Structs/PACKET_CZ_ITEMLISTWIN_RES.hpp"
#include "Server/Zone/Packets/Ragexe/20180829/Structs/PACKET_CZ_ITEM_PICKUP.hpp"
#include "Server/Zone/Packets/Ragexe/20180829/Structs/PACKET_CZ_ITEM_THROW.hpp"
#include "Server/Zone/Packets/Ragexe/20180829/Structs/PACKET_CZ_JOIN_BATTLE_FIELD.hpp"
#include "Server/Zone/Packets/Ragexe/20180829/Structs/PACKET_CZ_MOVE_ITEM_FROM_BODY_TO_STORE.hpp"
#include "Server/Zone/Packets/Ragexe/20180829/Structs/PACKET_CZ_MOVE_ITEM_FROM_STORE_TO_BODY.hpp"
#include "Server/Zone/Packets/Ragexe/20180829/Structs/PACKET_CZ_PARTY_BOOKING_REQ_REGISTER.hpp"
#include "Server/Zone/Packets/Ragexe/20180829/Structs/PACKET_CZ_PARTY_JOIN_REQ.hpp"
#include "Server/Zone/Packets/Ragexe/20180829/Structs/PACKET_CZ_REQNAME.hpp"
#include "Server/Zone/Packets/Ragexe/20180829/Structs/PACKET_CZ_REQNAME_BYGID.hpp"
#include "Server/Zone/Packets/Ragexe/20180829/Structs/PACKET_CZ_REQUEST_ACT.hpp"
#include "Server/Zone/Packets/Ragexe/20180829/Structs/PACKET_CZ_REQUEST_MOVE.hpp"
#include "Server/Zone/Packets/Ragexe/20180829/Structs/PACKET_CZ_REQUEST_TIME.hpp"
#include "Server/Zone/Packets/Ragexe/20180829/Structs/PACKET_CZ_REQ_CLICK_TO_BUYING_STORE.hpp"
#include "Server/Zone/Packets/Ragexe/20180829/Structs/PACKET_CZ_REQ_CLOSE_BUYING_STORE.hpp"
#include "Server/Zone/Packets/Ragexe/20180829/Structs/PACKET_CZ_REQ_OPEN_BUYING_STORE.hpp"
#include "Server/Zone/Packets/Ragexe/20180829/Structs/PACKET_CZ_REQ_TRADE_BUYING_STORE.hpp"
#include "Server/Zone/Packets/Ragexe/20180829/Structs/PACKET_CZ_SEARCH_STORE_INFO.hpp"
#include "Server/Zone/Packets/Ragexe/20180829/Structs/PACKET_CZ_SEARCH_STORE_INFO_NEXT_PAGE.hpp"
#include "Server/Zone/Packets/Ragexe/20180829/Structs/PACKET_CZ_SSILIST_ITEM_CLICK.hpp"
#include "Server/Zone/Packets/Ragexe/20180829/Structs/PACKET_CZ_USE_SKILL.hpp"
#include "Server/Zone/Packets/Ragexe/20180829/Structs/PACKET_CZ_USE_SKILL_TOGROUND.hpp"
#include "Server/Zone/Packets/Ragexe/20180829/Structs/PACKET_CZ_USE_SKILL_TOGROUND_WITHTALKBOX.hpp"
#include "Server/Zone/Packets/Ragexe/20180829/Structs/PACKET_ZC_ADD_QUEST_EX.hpp"
#include "Server/Zone/Packets/Ragexe/20180829/Structs/PACKET_ZC_INVENTORY_END.hpp"
#include "Server/Zone/Packets/Ragexe/20180829/Structs/PACKET_ZC_INVENTORY_START.hpp"
#include "Server/Zone/Packets/Ragexe/20180829/Structs/PACKET_ZC_OFFLINE_STORE_VISIBLE.hpp"
#include "Server/Zone/Packets/Ragexe/20180829/Structs/PACKET_ZC_STORE_ITEMLIST_EQUIP_V6.hpp"
#include "Server/Zone/Packets/Ragexe/20180829/Structs/PACKET_ZC_STORE_ITEMLIST_NORMAL_V6.hpp"
#include "Server/Zone/Packets/Ragexe/20180822/PacketHandlerRagexe20180822.hpp"

namespace Horizon
{
namespace Zone
{

class ZoneSocket;

class PacketHandlerRagexe20180829 : public PacketHandlerRagexe20180822
{
public:
	PacketHandlerRagexe20180829(std::shared_ptr<ZoneSocket> socket);
	~PacketHandlerRagexe20180829();

	virtual void initialize_handlers() override;

};
}
}

#endif /* HORIZON_ZONE_Ragexe_20180829_PACKETHANDLER_HPP */
