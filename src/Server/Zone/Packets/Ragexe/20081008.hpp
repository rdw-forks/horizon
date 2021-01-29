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

#ifndef HORIZON_ZONE_CLIENT_PACKET_LENGTH_TABLE_20081008
#define HORIZON_ZONE_CLIENT_PACKET_LENGTH_TABLE_20081008

#include "Core/Multithreading/LockedLookupTable.hpp"

#include "Default.hpp"

#include <utility>

namespace Horizon
{
namespace Zone
{
/**
 * @brief Client Packet Length Table object that stores
 * the packet length of each packet of this client version.
 * Packets with IDs already existent in the database are over-written.
 * The data is stored in a thread-safe lookup table.
 * RAII techinque ensures that the table is populated on instantiation.
 */
class ClientPacketLengthTable : public PacketLengthTable
{
public:
	ClientPacketLengthTable(std::shared_ptr<ZoneSession> s)
	: PacketLengthTable(s)
	{
#define ADD_HPKT(i, j, k) _hpacket_length_table.insert(i, std::make_pair(j, std::make_shared<k>(s)))
#define ADD_TPKT(i, j, k) _tpacket_length_table.insert(i, std::make_pair(j, std::make_shared<k>(s)))
		ADD_HPKT(0x00e6, 10, CZ_ACK_EXCHANGE_ITEM);
		ADD_HPKT(0x0208, 3, CZ_ACK_REQ_ADD_FRIENDS);
		ADD_HPKT(0x00c5, 28, CZ_ACK_SELECT_DEALTYPE);
		ADD_HPKT(0x00e8, -1, CZ_ADD_EXCHANGE_ITEM);
		ADD_HPKT(0x0202, 26, CZ_ADD_FRIENDS);
		ADD_HPKT(0x0218, 3, CZ_ALCHEMIST_RANK);
		ADD_HPKT(0x0217, -1, CZ_BLACKSMITH_RANK);
		ADD_HPKT(0x0099, -1, CZ_BROADCAST);
		ADD_HPKT(0x0118, 182, CZ_CANCEL_LOCKON);
		ADD_HPKT(0x00de, -1, CZ_CHANGE_CHATROOM);
		ADD_HPKT(0x0361, 6, CZ_CHANGE_DIRECTION2);
		ADD_HPKT(0x0102, 9, CZ_CHANGE_GROUPEXPOPTION);
		ADD_HPKT(0x00b8, 10, CZ_CHOOSE_MENU);
		ADD_HPKT(0x01ed, 8, CZ_CHOPOKGI);
		ADD_HPKT(0x022d, 26, CZ_COMMAND_MER);
		ADD_HPKT(0x01a1, -1, CZ_COMMAND_PET);
		ADD_HPKT(0x00eb, 19, CZ_CONCLUDE_EXCHANGE_ITEM);
		ADD_HPKT(0x0090, 2, CZ_CONTACTNPC);
		ADD_HPKT(0x00d5, -1, CZ_CREATE_CHATROOM);
		ADD_HPKT(0x0203, 6, CZ_DELETE_FRIENDS);
		ADD_HPKT(0x00ce, 8, CZ_DISCONNECT_ALL_CHARACTER);
		ADD_HPKT(0x00ef, 2, CZ_EXEC_EXCHANGE_ITEM);
		ADD_HPKT(0x00e3, 6, CZ_EXIT_ROOM);
		ADD_HPKT(0x017e, -1, CZ_GUILD_CHAT);
		ADD_HPKT(0x016e, 39, CZ_GUILD_NOTICE);
		ADD_HPKT(0x0143, 7, CZ_INPUT_EDITDLG);
		ADD_HPKT(0x01d5, 6, CZ_INPUT_EDITDLGSTR);
		ADD_HPKT(0x02f6, 30, CZ_IRMAIL_LIST);
		ADD_HPKT(0x02f3, -1, CZ_IRMAIL_SEND);
		ADD_HPKT(0x013f, 10, CZ_ITEM_CREATE);
		ADD_HPKT(0x0362, -1, CZ_ITEM_PICKUP2);
		ADD_HPKT(0x0363, -1, CZ_ITEM_THROW2);
		ADD_HPKT(0x00ff, -1, CZ_JOIN_GROUP);
		ADD_HPKT(0x0237, 23, CZ_KILLER_RANK);
		ADD_HPKT(0x019c, -1, CZ_LOCALBROADCAST);
		ADD_HPKT(0x00f9, -1, CZ_MAKE_GROUP);
		ADD_HPKT(0x01e8, -1, CZ_MAKE_GROUP2);
		ADD_HPKT(0x0140, -1, CZ_MOVETO_MAP);
		ADD_HPKT(0x0126, -1, CZ_MOVE_ITEM_FROM_BODY_TO_CART);
		ADD_HPKT(0x0364, 22, CZ_MOVE_ITEM_FROM_BODY_TO_STORE2);
		ADD_HPKT(0x0128, -1, CZ_MOVE_ITEM_FROM_STORE_TO_CART);
		ADD_HPKT(0x007d, -1, CZ_NOTIFY_ACTORINIT);
		ADD_HPKT(0x0134, 29, CZ_PC_PURCHASE_ITEMLIST_FROMMC);
		ADD_HPKT(0x00c9, -1, CZ_PC_SELL_ITEMLIST);
		ADD_HPKT(0x01bc, -1, CZ_RECALL);
		ADD_HPKT(0x01bd, 26, CZ_RECALL_GID);
		ADD_HPKT(0x0161, 10, CZ_REG_CHANGE_GUILD_POSITIONINFO);
		ADD_HPKT(0x011d, 14, CZ_REMEMBER_WARPPOINT);
		ADD_HPKT(0x01ba, -1, CZ_REMOVE_AID);
		ADD_HPKT(0x018e, -1, CZ_REQMAKINGITEM);
		ADD_HPKT(0x0368, -1, CZ_REQNAME2);
		ADD_HPKT(0x0437, -1, CZ_REQUEST_ACT2);
		ADD_HPKT(0x0108, 11, CZ_REQUEST_CHAT_PARTY);
		ADD_HPKT(0x035f, -1, CZ_REQUEST_MOVE2);
		ADD_HPKT(0x0232, -1, CZ_REQUEST_MOVENPC);
		ADD_HPKT(0x0234, 60, CZ_REQUEST_MOVETOOWNER);
		ADD_HPKT(0x0170, 10, CZ_REQ_ALLY_GUILD);
		ADD_HPKT(0x015b, -1, CZ_REQ_BAN_GUILD);
		ADD_HPKT(0x0130, 6, CZ_REQ_BUY_FROMMC);
		ADD_HPKT(0x012a, -1, CZ_REQ_CARTOFF);
		ADD_HPKT(0x0155, 81, CZ_REQ_CHANGE_MEMBERPOS);
		ADD_HPKT(0x012e, 5, CZ_REQ_CLOSESTORE);
		ADD_HPKT(0x018a, -1, CZ_REQ_DISCONNECT);
		ADD_HPKT(0x00bf, 7, CZ_REQ_EMOTION);
		ADD_HPKT(0x00d9, 4, CZ_REQ_ENTER_ROOM);
		ADD_HPKT(0x00e4, -1, CZ_REQ_EXCHANGE_ITEM);
		ADD_HPKT(0x0103, 27, CZ_REQ_EXPEL_GROUP_MEMBER);
		ADD_HPKT(0x00e2, -1, CZ_REQ_EXPEL_MEMBER);
		ADD_HPKT(0x0149, 58, CZ_REQ_GIVE_MANNER_POINT);
		ADD_HPKT(0x014f, -1, CZ_REQ_GUILD_MENU);
		ADD_HPKT(0x014d, 10, CZ_REQ_GUILD_MENUINTERFACE);
		ADD_HPKT(0x017c, -1, CZ_REQ_ITEMCOMPOSITION);
		ADD_HPKT(0x0178, -1, CZ_REQ_ITEMIDENTIFY);
		ADD_HPKT(0x00fc, -1, CZ_REQ_JOIN_GROUP);
		ADD_HPKT(0x0168, -1, CZ_REQ_JOIN_GUILD);
		ADD_HPKT(0x0100, 26, CZ_REQ_LEAVE_GROUP);
		ADD_HPKT(0x0159, -1, CZ_REQ_LEAVE_GUILD);
		ADD_HPKT(0x00b9, 97, CZ_REQ_NEXT_SCRIPT);
		ADD_HPKT(0x01b2, -1, CZ_REQ_OPENSTORE2);
		ADD_HPKT(0x00e0, 9, CZ_REQ_ROLE_CHANGE);
		ADD_HPKT(0x00c1, 26, CZ_REQ_USER_COUNT);
		ADD_HPKT(0x00a9, 6, CZ_REQ_WEAR_EQUIP);
		ADD_HPKT(0x00d3, 8, CZ_REQ_WHISPER_LIST);
		ADD_HPKT(0x00b2, 282, CZ_RESTART);
		ADD_HPKT(0x01ce, 53, CZ_SELECTAUTOSPELL);
		ADD_HPKT(0x01a7, 14, CZ_SELECT_PETEGG);
		ADD_HPKT(0x00cf, 6, CZ_SETTING_WHISPER_PC);
		ADD_HPKT(0x01bb, 7, CZ_SHIFT);
		ADD_HPKT(0x019f, 8, CZ_TRYCAPTURE_MONSTER);
		ADD_HPKT(0x0439, 114, CZ_USE_ITEM2);
		ADD_HPKT(0x0366, 14, CZ_USE_SKILL_TOGROUND2);
		ADD_HPKT(0x0096, 57, CZ_WHISPER);
		ADD_TPKT(0x0073, 33, ZC_ACCEPT_ENTER);
		ADD_TPKT(0x0083, 21, ZC_ACCEPT_QUIT);
		ADD_TPKT(0x012c, 14, ZC_ACK_ADDITEM_TO_CART);
		ADD_TPKT(0x00ea, 28, ZC_ACK_ADD_EXCHANGE_ITEM);
		ADD_TPKT(0x015c, 2, ZC_ACK_BAN_GUILD);
		ADD_TPKT(0x00d6, 8, ZC_ACK_CREATE_CHATROOM);
		ADD_TPKT(0x015e, 6, ZC_ACK_DISORGANIZE_GUILD_RESULT);
		ADD_TPKT(0x00e7, 2, ZC_ACK_EXCHANGE_ITEM);
		ADD_TPKT(0x017d, 53, ZC_ACK_ITEMCOMPOSITION);
		ADD_TPKT(0x0179, 6, ZC_ACK_ITEMIDENTIFY);
		ADD_TPKT(0x0274, 6, ZC_ACK_MAIL_RETURN);
		ADD_TPKT(0x00fa, 2, ZC_ACK_MAKE_GROUP);
		ADD_TPKT(0x018f, -1, ZC_ACK_REQMAKINGITEM);
		ADD_TPKT(0x0195, 39, ZC_ACK_REQNAMEALL);
		ADD_TPKT(0x0194, -1, ZC_ACK_REQNAME_BYGID);
		ADD_TPKT(0x018b, -1, ZC_ACK_REQ_DISCONNECT);
		ADD_TPKT(0x00fd, 10, ZC_ACK_REQ_JOIN_GROUP);
		ADD_TPKT(0x0169, -1, ZC_ACK_REQ_JOIN_GUILD);
		ADD_TPKT(0x0098, 2, ZC_ACK_WHISPER);
		ADD_TPKT(0x013b, 2, ZC_ACTION_FAILURE);
		ADD_TPKT(0x00e9, 6, ZC_ADD_EXCHANGE_ITEM);
		ADD_TPKT(0x0124, -1, ZC_ADD_ITEM_TO_CART);
		ADD_TPKT(0x01c5, -1, ZC_ADD_ITEM_TO_CART2);
		ADD_TPKT(0x01c4, -1, ZC_ADD_ITEM_TO_STORE2);
		ADD_TPKT(0x0104, 8, ZC_ADD_MEMBER_TO_GROUP);
		ADD_TPKT(0x0111, 6, ZC_ADD_SKILL);
		ADD_TPKT(0x021c, -1, ZC_ALCHEMIST_POINT);
		ADD_TPKT(0x0139, -1, ZC_ATTACK_FAILURE_FOR_DISTANCE);
		ADD_TPKT(0x013a, -1, ZC_ATTACK_RANGE);
		ADD_TPKT(0x0147, -1, ZC_AUTORUN_SKILL);
		ADD_TPKT(0x0163, -1, ZC_BAN_LIST);
		ADD_TPKT(0x021b, -1, ZC_BLACKSMITH_POINT);
		ADD_TPKT(0x0219, 6, ZC_BLACKSMITH_RANK);
		ADD_TPKT(0x009a, 6, ZC_BROADCAST);
		ADD_TPKT(0x01c3, 186, ZC_BROADCAST2);
		ADD_TPKT(0x0297, 6, ZC_CART_EQUIPMENT_ITEMLIST2);
		ADD_TPKT(0x0230, 10, ZC_CHANGESTATE_MER);
		ADD_TPKT(0x009c, -1, ZC_CHANGE_DIRECTION);
		ADD_TPKT(0x01d2, 4, ZC_COMBODELAY);
		ADD_TPKT(0x00ec, 20, ZC_CONCLUDE_EXCHANGE_ITEM);
		ADD_TPKT(0x01ea, 11, ZC_CONGRATULATION);
		ADD_TPKT(0x0141, 8, ZC_COUPLESTATUS);
		ADD_TPKT(0x0137, 10, ZC_DELETEITEM_FROM_MCSTORE);
		ADD_TPKT(0x020a, 5, ZC_DELETE_FRIENDS);
		ADD_TPKT(0x0105, -1, ZC_DELETE_MEMBER_FROM_GROUP);
		ADD_TPKT(0x00d8, -1, ZC_DESTROY_ROOM);
		ADD_TPKT(0x01cf, -1, ZC_DEVOTIONLIST);
		ADD_TPKT(0x01b9, 18, ZC_DISPEL);
		ADD_TPKT(0x00db, -1, ZC_ENTER_ROOM);
		ADD_TPKT(0x0295, 6, ZC_EQUIPMENT_ITEMLIST2);
		ADD_TPKT(0x013c, -1, ZC_EQUIP_ARROW);
		ADD_TPKT(0x00f0, 7, ZC_EXEC_EXCHANGE_ITEM);
		ADD_TPKT(0x022f, 30, ZC_FEED_MER);
		ADD_TPKT(0x01a3, 3, ZC_FEED_PET);
		ADD_TPKT(0x0227, 4, ZC_GAME_GUARD);
		ADD_TPKT(0x00fb, 28, ZC_GROUP_LIST);
		ADD_TPKT(0x017f, -1, ZC_GUILD_CHAT);
		ADD_TPKT(0x01b6, 31, ZC_GUILD_INFO2);
		ADD_TPKT(0x0162, -1, ZC_GUILD_SKILLINFO);
		ADD_TPKT(0x0235, 6, ZC_HOSKILLINFO_LIST);
		ADD_TPKT(0x0239, 19, ZC_HOSKILLINFO_UPDATE);
		ADD_TPKT(0x02f4, 7, ZC_IRMAIL_SEND_RES);
		ADD_TPKT(0x017b, 6, ZC_ITEMCOMPOSITION_LIST);
		ADD_TPKT(0x0177, 6, ZC_ITEMIDENTIFY_LIST);
		ADD_TPKT(0x00a1, 2, ZC_ITEM_DISAPPEAR);
		ADD_TPKT(0x009d, 6, ZC_ITEM_ENTRY);
		ADD_TPKT(0x00a0, -1, ZC_ITEM_PICKUP_ACK);
		ADD_TPKT(0x00af, -1, ZC_ITEM_THROW_ACK);
		ADD_TPKT(0x0238, -1, ZC_KILLER_RANK);
		ADD_TPKT(0x00b1, -1, ZC_LONGPAR_CHANGE);
		ADD_TPKT(0x00dd, -1, ZC_MEMBER_EXIT);
		ADD_TPKT(0x00dc, 33, ZC_MEMBER_NEWENTRY);
		ADD_TPKT(0x018c, 58, ZC_MONSTER_INFO);
		ADD_TPKT(0x010c, -1, ZC_MVP);
		ADD_TPKT(0x010a, 10, ZC_MVP_GETTING_ITEM);
		ADD_TPKT(0x00a3, 8, ZC_NORMAL_ITEMLIST);
		ADD_TPKT(0x02e1, -1, ZC_NOTIFY_ACT2);
		ADD_TPKT(0x007a, 2, ZC_NOTIFY_ACTENTRY);
		ADD_TPKT(0x019b, 8, ZC_NOTIFY_EFFECT);
		ADD_TPKT(0x0117, 6, ZC_NOTIFY_GROUNDSKILL);
		ADD_TPKT(0x0106, 60, ZC_NOTIFY_HP_TO_GROUPM);
		ADD_TPKT(0x0075, 32, ZC_NOTIFY_INITCHAR);
		ADD_TPKT(0x0199, 67, ZC_NOTIFY_MAPPROPERTY);
		ADD_TPKT(0x0086, -1, ZC_NOTIFY_MOVE);
		ADD_TPKT(0x007b, 3, ZC_NOTIFY_MOVEENTRY);
		ADD_TPKT(0x01da, 55, ZC_NOTIFY_MOVEENTRY2);
		ADD_TPKT(0x022c, 13, ZC_NOTIFY_MOVEENTRY3);
		ADD_TPKT(0x02ec, 4, ZC_NOTIFY_MOVEENTRY4);
		ADD_TPKT(0x0079, -1, ZC_NOTIFY_NEWENTRY);
		ADD_TPKT(0x01d9, -1, ZC_NOTIFY_NEWENTRY2);
		ADD_TPKT(0x022b, 3, ZC_NOTIFY_NEWENTRY3);
		ADD_TPKT(0x02ed, 4, ZC_NOTIFY_NEWENTRY4);
		ADD_TPKT(0x008e, 4, ZC_NOTIFY_PLAYERCHAT);
		ADD_TPKT(0x0107, 3, ZC_NOTIFY_POSITION_TO_GROUPM);
		ADD_TPKT(0x01eb, -1, ZC_NOTIFY_POSITION_TO_GUILDM);
		ADD_TPKT(0x019a, 4, ZC_NOTIFY_RANKING);
		ADD_TPKT(0x0114, -1, ZC_NOTIFY_SKILL);
		ADD_TPKT(0x01de, 7, ZC_NOTIFY_SKILL2);
		ADD_TPKT(0x01d8, -1, ZC_NOTIFY_STANDENTRY2);
		ADD_TPKT(0x022a, 6, ZC_NOTIFY_STANDENTRY3);
		ADD_TPKT(0x02ee, -1, ZC_NOTIFY_STANDENTRY4);
		ADD_TPKT(0x007f, 2, ZC_NOTIFY_TIME);
		ADD_TPKT(0x0091, 14, ZC_NPCACK_MAPMOVE);
		ADD_TPKT(0x0092, 2, ZC_NPCACK_SERVERMOVE);
		ADD_TPKT(0x01b0, 4, ZC_NPCSPRITE_CHANGE);
		ADD_TPKT(0x0142, 43, ZC_OPEN_EDITDLG);
		ADD_TPKT(0x01d4, -1, ZC_OPEN_EDITDLGSTR);
		ADD_TPKT(0x00b0, 5, ZC_PAR_CHANGE);
		ADD_TPKT(0x00c6, 5, ZC_PC_PURCHASE_ITEMLIST);
		ADD_TPKT(0x0136, 6, ZC_PC_PURCHASE_MYITEMLIST);
		ADD_TPKT(0x00ca, 4, ZC_PC_PURCHASE_RESULT);
		ADD_TPKT(0x00c7, -1, ZC_PC_SELL_ITEMLIST);
		ADD_TPKT(0x01a6, 30, ZC_PETEGG_LIST);
		ADD_TPKT(0x01aa, 12, ZC_PET_ACT);
		ADD_TPKT(0x0166, 3, ZC_POSITION_ID_NAME_INFO);
		ADD_TPKT(0x0160, -1, ZC_POSITION_INFO);
		ADD_TPKT(0x022e, 17, ZC_PROPERTY_HOMUN);
		ADD_TPKT(0x01a2, 2, ZC_PROPERTY_PET);
		ADD_TPKT(0x00da, -1, ZC_REFUSE_ENTER_ROOM);
		ADD_TPKT(0x0207, 2, ZC_REQ_ADD_FRIENDS);
		ADD_TPKT(0x0171, 17, ZC_REQ_ALLY_GUILD);
		ADD_TPKT(0x00e5, 3, ZC_REQ_EXCHANGE_ITEM);
		ADD_TPKT(0x01f4, 3, ZC_REQ_EXCHANGE_ITEM2);
		ADD_TPKT(0x00fe, -1, ZC_REQ_JOIN_GROUP);
		ADD_TPKT(0x00ac, 30, ZC_REQ_TAKEOFF_EQUIP_ACK);
		ADD_TPKT(0x00b3, 3, ZC_RESTART_ACK);
		ADD_TPKT(0x0167, 14, ZC_RESULT_MAKE_GUILD);
		ADD_TPKT(0x023c, 3, ZC_RESULT_STORE_PASSWORD);
		ADD_TPKT(0x0148, -1, ZC_RESURRECTION);
		ADD_TPKT(0x00e1, -1, ZC_ROLE_CHANGE);
		ADD_TPKT(0x00d7, -1, ZC_ROOM_NEWENTRY);
		ADD_TPKT(0x00c4, -1, ZC_SELECT_DEALTYPE);
		ADD_TPKT(0x00d1, -1, ZC_SETTING_WHISPER_PC);
		ADD_TPKT(0x00d2, -1, ZC_SETTING_WHISPER_STATE);
		ADD_TPKT(0x01b3, -1, ZC_SHOW_IMAGE2);
		ADD_TPKT(0x010f, 2, ZC_SKILLINFO_LIST);
		ADD_TPKT(0x01ac, 5, ZC_SKILL_UPDATE);
		ADD_TPKT(0x01d0, 10, ZC_SPIRITS);
		ADD_TPKT(0x01e1, -1, ZC_SPIRITS2);
		ADD_TPKT(0x00c3, 24, ZC_SPRITE_CHANGE);
		ADD_TPKT(0x01d7, -1, ZC_SPRITE_CHANGE2);
		ADD_TPKT(0x0119, 7, ZC_STATE_CHANGE);
		ADD_TPKT(0x0229, -1, ZC_STATE_CHANGE3);
		ADD_TPKT(0x00bd, -1, ZC_STATUS);
		ADD_TPKT(0x0131, 4, ZC_STORE_ENTRY);
		ADD_TPKT(0x00a6, -1, ZC_STORE_EQUIPMENT_ITEMLIST);
		ADD_TPKT(0x0296, -1, ZC_STORE_EQUIPMENT_ITEMLIST2);
		ADD_TPKT(0x01f0, 9, ZC_STORE_NORMAL_ITEMLIST2);
		ADD_TPKT(0x0224, 282, ZC_TAEKWON_POINT);
		ADD_TPKT(0x0226, -1, ZC_TAEKWON_RANK);
		ADD_TPKT(0x01a0, -1, ZC_TRYCAPTURE_MONSTER);
		ADD_TPKT(0x016d, 15, ZC_UPDATE_CHARSTAT);
		ADD_TPKT(0x016c, -1, ZC_UPDATE_GDID);
		ADD_TPKT(0x00a8, 42, ZC_USE_ITEM_ACK);
		ADD_TPKT(0x01c8, 35, ZC_USE_ITEM_ACK2);
		ADD_TPKT(0x011a, -1, ZC_USE_SKILL);
		ADD_TPKT(0x00b5, -1, ZC_WAIT_DIALOG);
		ADD_TPKT(0x0097, 6, ZC_WHISPER);
#undef ADD_TPKT
#undef ADD_HPKT
	}

	~ClientPacketLengthTable() { }

};
}
}
#endif /* HORIZON_ZONE_CLIENT_PACKET_LENGTH_TABLE_20081008 */