/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 * Copyright (c) 2023 Horizon Dev Team.
 *
 * Base Author - Sephus. (sagunxp@gmail.com)
 *
 * This library is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 **************************************************/

#ifndef HORIZON_ZONE_AD_PACKET_LENGTH_TABLE
#define HORIZON_ZONE_AD_PACKET_LENGTH_TABLE

#include "Core/Multithreading/LockedLookupTable.hpp"
#include "Server/Zone/Packets/HandledPackets.hpp"
#include "Server/Zone/Packets/TransmittedPackets.hpp"

namespace Horizon
{
namespace Zone
{
	typedef std::shared_ptr<Base::NetworkPacket<ZoneSession>> HPacketStructPtrType;
	typedef std::shared_ptr<Base::NetworkPacket<ZoneSession>> TPacketStructPtrType;
	typedef std::pair<int16_t, HPacketStructPtrType> HPacketTablePairType;
	typedef std::pair<int16_t, TPacketStructPtrType> TPacketTablePairType;
/**
 * @brief Auto-generated with a python generator tool authored by Sephus (sagunxp@gmail.com).
 */
class PacketLengthTable
{
public:
	PacketLengthTable(std::shared_ptr<ZoneSession> s)
	: _session(s)
	{
#define ADD_HPKT(i, j, k) _hpacket_length_table.insert(i, std::make_pair(j, std::make_shared<k>(s)))
#define ADD_TPKT(i, j, k) _tpacket_length_table.insert(i, std::make_pair(j, std::make_shared<k>(s)))
		ADD_HPKT(0x00e6, 3, CZ_ACK_EXCHANGE_ITEM);
		ADD_HPKT(0x0208, 14, CZ_ACK_REQ_ADD_FRIENDS);
		ADD_HPKT(0x00c5, 7, CZ_ACK_SELECT_DEALTYPE);
		ADD_HPKT(0x00e8, 8, CZ_ADD_EXCHANGE_ITEM);
		ADD_HPKT(0x0202, 26, CZ_ADD_FRIENDS);
		ADD_HPKT(0x0172, 10, CZ_ALLY_GUILD);
		ADD_HPKT(0x0099, -1, CZ_BROADCAST);
		ADD_HPKT(0x00ed, 2, CZ_CANCEL_EXCHANGE_ITEM);
		ADD_HPKT(0x0118, 2, CZ_CANCEL_LOCKON);
		ADD_HPKT(0x00de, -1, CZ_CHANGE_CHATROOM);
		ADD_HPKT(0x019d, 6, CZ_CHANGE_EFFECTSTATE);
		ADD_HPKT(0x0102, 6, CZ_CHANGE_GROUPEXPOPTION);
		ADD_HPKT(0x0198, 8, CZ_CHANGE_MAPTYPE);
		ADD_HPKT(0x00b8, 7, CZ_CHOOSE_MENU);
		ADD_HPKT(0x01ed, 2, CZ_CHOPOKGI);
		ADD_HPKT(0x0146, 6, CZ_CLOSE_DIALOG);
		ADD_HPKT(0x01a1, 3, CZ_COMMAND_PET);
		ADD_HPKT(0x00eb, 2, CZ_CONCLUDE_EXCHANGE_ITEM);
		ADD_HPKT(0x0090, 7, CZ_CONTACTNPC);
		ADD_HPKT(0x00d5, -1, CZ_CREATE_CHATROOM);
		ADD_HPKT(0x0203, 10, CZ_DELETE_FRIENDS);
		ADD_HPKT(0x00ce, 2, CZ_DISCONNECT_ALL_CHARACTER);
		ADD_HPKT(0x00cc, 6, CZ_DISCONNECT_CHARACTER);
		ADD_HPKT(0x01e7, 2, CZ_DORIDORI);
		ADD_HPKT(0x00ef, 2, CZ_EXEC_EXCHANGE_ITEM);
		ADD_HPKT(0x00e3, 2, CZ_EXIT_ROOM);
		ADD_HPKT(0x017e, -1, CZ_GUILD_CHAT);
		ADD_HPKT(0x016e, 186, CZ_GUILD_NOTICE);
		ADD_HPKT(0x01b7, 6, CZ_GUILD_ZENY);
		ADD_HPKT(0x0143, 10, CZ_INPUT_EDITDLG);
		ADD_HPKT(0x013f, 26, CZ_ITEM_CREATE);
		ADD_HPKT(0x01f7, 14, CZ_JOIN_BABY);
		ADD_HPKT(0x01e3, 14, CZ_JOIN_COUPLE);
		ADD_HPKT(0x00ff, 10, CZ_JOIN_GROUP);
		ADD_HPKT(0x016b, 10, CZ_JOIN_GUILD);
		ADD_HPKT(0x00f9, 26, CZ_MAKE_GROUP);
		ADD_HPKT(0x01e8, 28, CZ_MAKE_GROUP2);
		ADD_HPKT(0x01cb, 9, CZ_MONSTER_TALK);
		ADD_HPKT(0x0140, 22, CZ_MOVETO_MAP);
		ADD_HPKT(0x0126, 8, CZ_MOVE_ITEM_FROM_BODY_TO_CART);
		ADD_HPKT(0x0127, 8, CZ_MOVE_ITEM_FROM_CART_TO_BODY);
		ADD_HPKT(0x0129, 8, CZ_MOVE_ITEM_FROM_CART_TO_STORE);
		ADD_HPKT(0x0128, 8, CZ_MOVE_ITEM_FROM_STORE_TO_CART);
		ADD_HPKT(0x007d, 2, CZ_NOTIFY_ACTORINIT);
		ADD_HPKT(0x00c8, -1, CZ_PC_PURCHASE_ITEMLIST);
		ADD_HPKT(0x0134, -1, CZ_PC_PURCHASE_ITEMLIST_FROMMC);
		ADD_HPKT(0x00c9, -1, CZ_PC_SELL_ITEMLIST);
		ADD_HPKT(0x01a8, 4, CZ_PETEGG_INFO);
		ADD_HPKT(0x01a9, 6, CZ_PET_ACT);
		ADD_HPKT(0x0138, 3, CZ_PKMODE_CHANGE);
		ADD_HPKT(0x01bc, 26, CZ_RECALL);
		ADD_HPKT(0x01bd, 26, CZ_RECALL_GID);
		ADD_HPKT(0x0153, -1, CZ_REGISTER_GUILD_EMBLEM_IMG);
		ADD_HPKT(0x0161, -1, CZ_REG_CHANGE_GUILD_POSITIONINFO);
		ADD_HPKT(0x011d, 2, CZ_REMEMBER_WARPPOINT);
		ADD_HPKT(0x01ba, 26, CZ_REMOVE_AID);
		ADD_HPKT(0x01a5, 26, CZ_RENAME_PET);
		ADD_HPKT(0x018e, 10, CZ_REQMAKINGITEM);
		ADD_HPKT(0x0108, -1, CZ_REQUEST_CHAT_PARTY);
		ADD_HPKT(0x0082, 2, CZ_REQUEST_QUIT);
		ADD_HPKT(0x01df, 6, CZ_REQ_ACCOUNTNAME);
		ADD_HPKT(0x0170, 14, CZ_REQ_ALLY_GUILD);
		ADD_HPKT(0x015b, 54, CZ_REQ_BAN_GUILD);
		ADD_HPKT(0x0130, 6, CZ_REQ_BUY_FROMMC);
		ADD_HPKT(0x012a, 2, CZ_REQ_CARTOFF);
		ADD_HPKT(0x01af, 4, CZ_REQ_CHANGECART);
		ADD_HPKT(0x0155, -1, CZ_REQ_CHANGE_MEMBERPOS);
		ADD_HPKT(0x012e, 2, CZ_REQ_CLOSESTORE);
		ADD_HPKT(0x0183, 10, CZ_REQ_DELETE_RELATED_GUILD);
		ADD_HPKT(0x018a, 4, CZ_REQ_DISCONNECT);
		ADD_HPKT(0x015d, 42, CZ_REQ_DISORGANIZE_GUILD);
		ADD_HPKT(0x00bf, 3, CZ_REQ_EMOTION);
		ADD_HPKT(0x00d9, 14, CZ_REQ_ENTER_ROOM);
		ADD_HPKT(0x00e4, 6, CZ_REQ_EXCHANGE_ITEM);
		ADD_HPKT(0x0103, 30, CZ_REQ_EXPEL_GROUP_MEMBER);
		ADD_HPKT(0x00e2, 26, CZ_REQ_EXPEL_MEMBER);
		ADD_HPKT(0x0149, 9, CZ_REQ_GIVE_MANNER_POINT);
		ADD_HPKT(0x0151, 6, CZ_REQ_GUILD_EMBLEM_IMG);
		ADD_HPKT(0x0175, 6, CZ_REQ_GUILD_MEMBER_INFO);
		ADD_HPKT(0x014f, 6, CZ_REQ_GUILD_MENU);
		ADD_HPKT(0x014d, 2, CZ_REQ_GUILD_MENUINTERFACE);
		ADD_HPKT(0x0180, 6, CZ_REQ_HOSTILE_GUILD);
		ADD_HPKT(0x017c, 6, CZ_REQ_ITEMCOMPOSITION);
		ADD_HPKT(0x017a, 4, CZ_REQ_ITEMCOMPOSITION_LIST);
		ADD_HPKT(0x0178, 4, CZ_REQ_ITEMIDENTIFY);
		ADD_HPKT(0x01fd, 4, CZ_REQ_ITEMREPAIR);
		ADD_HPKT(0x01f9, 6, CZ_REQ_JOIN_BABY);
		ADD_HPKT(0x01e5, 6, CZ_REQ_JOIN_COUPLE);
		ADD_HPKT(0x00fc, 6, CZ_REQ_JOIN_GROUP);
		ADD_HPKT(0x0168, 14, CZ_REQ_JOIN_GUILD);
		ADD_HPKT(0x0100, 2, CZ_REQ_LEAVE_GROUP);
		ADD_HPKT(0x0159, 54, CZ_REQ_LEAVE_GUILD);
		ADD_HPKT(0x0165, 30, CZ_REQ_MAKE_GUILD);
		ADD_HPKT(0x01ae, 4, CZ_REQ_MAKINGARROW);
		ADD_HPKT(0x00b9, 6, CZ_REQ_NEXT_SCRIPT);
		ADD_HPKT(0x012f, -1, CZ_REQ_OPENSTORE);
		ADD_HPKT(0x01b2, -1, CZ_REQ_OPENSTORE2);
		ADD_HPKT(0x0157, 6, CZ_REQ_OPEN_MEMBER_INFO);
		ADD_HPKT(0x01c0, 2, CZ_REQ_REMAINTIME);
		ADD_HPKT(0x00e0, 30, CZ_REQ_ROLE_CHANGE);
		ADD_HPKT(0x00ba, 2, CZ_REQ_STATUS);
		ADD_HPKT(0x00ab, 4, CZ_REQ_TAKEOFF_EQUIP);
		ADD_HPKT(0x00c1, 2, CZ_REQ_USER_COUNT);
		ADD_HPKT(0x00a9, 6, CZ_REQ_WEAR_EQUIP);
		ADD_HPKT(0x00d3, 2, CZ_REQ_WHISPER_LIST);
		ADD_HPKT(0x0197, 4, CZ_RESET);
		ADD_HPKT(0x00b2, 3, CZ_RESTART);
		ADD_HPKT(0x01ce, 6, CZ_SELECTAUTOSPELL);
		ADD_HPKT(0x01a7, 4, CZ_SELECT_PETEGG);
		ADD_HPKT(0x011b, 20, CZ_SELECT_WARPPOINT);
		ADD_HPKT(0x00cf, 27, CZ_SETTING_WHISPER_PC);
		ADD_HPKT(0x00d0, 3, CZ_SETTING_WHISPER_STATE);
		ADD_HPKT(0x01bb, 26, CZ_SHIFT);
		ADD_HPKT(0x00bb, 5, CZ_STATUS_CHANGE);
		ADD_HPKT(0x019f, 6, CZ_TRYCAPTURE_MONSTER);
		ADD_HPKT(0x0112, 4, CZ_UPGRADE_SKILLLEVEL);
		ADD_HPKT(0x0096, -1, CZ_WHISPER);
		ADD_TPKT(0x0073, 11, ZC_ACCEPT_ENTER);
		ADD_TPKT(0x0083, 2, ZC_ACCEPT_QUIT);
		ADD_TPKT(0x01e0, 30, ZC_ACK_ACCOUNTNAME);
		ADD_TPKT(0x012c, 3, ZC_ACK_ADDITEM_TO_CART);
		ADD_TPKT(0x00ea, 5, ZC_ACK_ADD_EXCHANGE_ITEM);
		ADD_TPKT(0x015c, 90, ZC_ACK_BAN_GUILD);
		ADD_TPKT(0x0174, -1, ZC_ACK_CHANGE_GUILD_POSITIONINFO);
		ADD_TPKT(0x00d6, 3, ZC_ACK_CREATE_CHATROOM);
		ADD_TPKT(0x00cd, 3, ZC_ACK_DISCONNECT_CHARACTER);
		ADD_TPKT(0x015f, 42, ZC_ACK_DISORGANIZE_GUILD);
		ADD_TPKT(0x015e, 6, ZC_ACK_DISORGANIZE_GUILD_RESULT);
		ADD_TPKT(0x00e7, 3, ZC_ACK_EXCHANGE_ITEM);
		ADD_TPKT(0x01f5, 9, ZC_ACK_EXCHANGE_ITEM2);
		ADD_TPKT(0x014a, 6, ZC_ACK_GIVE_MANNER_POINT);
		ADD_TPKT(0x0176, 106, ZC_ACK_GUILD_MEMBER_INFO);
		ADD_TPKT(0x014e, 6, ZC_ACK_GUILD_MENUINTERFACE);
		ADD_TPKT(0x017d, 7, ZC_ACK_ITEMCOMPOSITION);
		ADD_TPKT(0x0179, 5, ZC_ACK_ITEMIDENTIFY);
		ADD_TPKT(0x0188, 8, ZC_ACK_ITEMREFINING);
		ADD_TPKT(0x01fe, 5, ZC_ACK_ITEMREPAIR);
		ADD_TPKT(0x015a, 66, ZC_ACK_LEAVE_GUILD);
		ADD_TPKT(0x00fa, 3, ZC_ACK_MAKE_GROUP);
		ADD_TPKT(0x0158, -1, ZC_ACK_OPEN_MEMBER_INFO);
		ADD_TPKT(0x011e, 3, ZC_ACK_REMEMBER_WARPPOINT);
		ADD_TPKT(0x018f, 6, ZC_ACK_REQMAKINGITEM);
		ADD_TPKT(0x0095, 30, ZC_ACK_REQNAME);
		ADD_TPKT(0x0195, 102, ZC_ACK_REQNAMEALL);
		ADD_TPKT(0x0194, 30, ZC_ACK_REQNAME_BYGID);
		ADD_TPKT(0x0173, 3, ZC_ACK_REQ_ALLY_GUILD);
		ADD_TPKT(0x0156, -1, ZC_ACK_REQ_CHANGE_MEMBERS);
		ADD_TPKT(0x018b, 4, ZC_ACK_REQ_DISCONNECT);
		ADD_TPKT(0x0181, 3, ZC_ACK_REQ_HOSTILE_GUILD);
		ADD_TPKT(0x00fd, 27, ZC_ACK_REQ_JOIN_GROUP);
		ADD_TPKT(0x0169, 3, ZC_ACK_REQ_JOIN_GUILD);
		ADD_TPKT(0x0110, 10, ZC_ACK_TOUSESKILL);
		ADD_TPKT(0x0098, 3, ZC_ACK_WHISPER);
		ADD_TPKT(0x013b, 4, ZC_ACTION_FAILURE);
		ADD_TPKT(0x00e9, 19, ZC_ADD_EXCHANGE_ITEM);
		ADD_TPKT(0x0209, 36, ZC_ADD_FRIENDS_LIST);
		ADD_TPKT(0x0124, 21, ZC_ADD_ITEM_TO_CART);
		ADD_TPKT(0x01c5, 22, ZC_ADD_ITEM_TO_CART2);
		ADD_TPKT(0x00f4, 21, ZC_ADD_ITEM_TO_STORE);
		ADD_TPKT(0x01c4, 22, ZC_ADD_ITEM_TO_STORE2);
		ADD_TPKT(0x0104, 79, ZC_ADD_MEMBER_TO_GROUP);
		ADD_TPKT(0x01e9, 81, ZC_ADD_MEMBER_TO_GROUP2);
		ADD_TPKT(0x0185, 34, ZC_ADD_RELATED_GUILD);
		ADD_TPKT(0x0111, 39, ZC_ADD_SKILL);
		ADD_TPKT(0x0139, 16, ZC_ATTACK_FAILURE_FOR_DISTANCE);
		ADD_TPKT(0x013a, 4, ZC_ATTACK_RANGE);
		ADD_TPKT(0x0147, 39, ZC_AUTORUN_SKILL);
		ADD_TPKT(0x01cd, 30, ZC_AUTOSPELLLIST);
		ADD_TPKT(0x0163, -1, ZC_BAN_LIST);
		ADD_TPKT(0x01d1, 14, ZC_BLADESTOP);
		ADD_TPKT(0x009a, -1, ZC_BROADCAST);
		ADD_TPKT(0x01c3, -1, ZC_BROADCAST2);
		ADD_TPKT(0x00ee, 2, ZC_CANCEL_EXCHANGE_ITEM);
		ADD_TPKT(0x012b, 2, ZC_CARTOFF);
		ADD_TPKT(0x0122, -1, ZC_CART_EQUIPMENT_ITEMLIST);
		ADD_TPKT(0x0123, -1, ZC_CART_NORMAL_ITEMLIST);
		ADD_TPKT(0x01ef, -1, ZC_CART_NORMAL_ITEMLIST2);
		ADD_TPKT(0x01a4, 11, ZC_CHANGESTATE_PET);
		ADD_TPKT(0x00df, -1, ZC_CHANGE_CHATROOM);
		ADD_TPKT(0x009c, 9, ZC_CHANGE_DIRECTION);
		ADD_TPKT(0x01b4, 12, ZC_CHANGE_GUILD);
		ADD_TPKT(0x00b6, 6, ZC_CLOSE_DIALOG);
		ADD_TPKT(0x00f8, 2, ZC_CLOSE_STORE);
		ADD_TPKT(0x01d2, 10, ZC_COMBODELAY);
		ADD_TPKT(0x0144, 23, ZC_COMPASS);
		ADD_TPKT(0x00ec, 3, ZC_CONCLUDE_EXCHANGE_ITEM);
		ADD_TPKT(0x01ea, 6, ZC_CONGRATULATION);
		ADD_TPKT(0x01e6, 26, ZC_COUPLENAME);
		ADD_TPKT(0x0141, 14, ZC_COUPLESTATUS);
		ADD_TPKT(0x0137, 6, ZC_DELETEITEM_FROM_MCSTORE);
		ADD_TPKT(0x020a, 10, ZC_DELETE_FRIENDS);
		ADD_TPKT(0x0125, 8, ZC_DELETE_ITEM_FROM_CART);
		ADD_TPKT(0x00f6, 8, ZC_DELETE_ITEM_FROM_STORE);
		ADD_TPKT(0x0105, 31, ZC_DELETE_MEMBER_FROM_GROUP);
		ADD_TPKT(0x0184, 10, ZC_DELETE_RELATED_GUILD);
		ADD_TPKT(0x00d8, 6, ZC_DESTROY_ROOM);
		ADD_TPKT(0x01cf, 28, ZC_DEVOTIONLIST);
		ADD_TPKT(0x0132, 6, ZC_DISAPPEAR_ENTRY);
		ADD_TPKT(0x01b9, 6, ZC_DISPEL);
		ADD_TPKT(0x0205, 26, ZC_DIVORCE);
		ADD_TPKT(0x00c0, 7, ZC_EMOTION);
		ADD_TPKT(0x00db, -1, ZC_ENTER_ROOM);
		ADD_TPKT(0x00a4, -1, ZC_EQUIPMENT_ITEMLIST);
		ADD_TPKT(0x013c, 4, ZC_EQUIP_ARROW);
		ADD_TPKT(0x00f1, 2, ZC_EXCHANGEITEM_UNDO);
		ADD_TPKT(0x00f0, 3, ZC_EXEC_EXCHANGE_ITEM);
		ADD_TPKT(0x01a3, 5, ZC_FEED_PET);
		ADD_TPKT(0x0201, -1, ZC_FRIENDS_LIST);
		ADD_TPKT(0x0206, 11, ZC_FRIENDS_STATE);
		ADD_TPKT(0x0101, 6, ZC_GROUPINFO_CHANGE);
		ADD_TPKT(0x00fb, -1, ZC_GROUP_LIST);
		ADD_TPKT(0x017f, -1, ZC_GUILD_CHAT);
		ADD_TPKT(0x0152, -1, ZC_GUILD_EMBLEM_IMG);
		ADD_TPKT(0x0150, 110, ZC_GUILD_INFO);
		ADD_TPKT(0x01b6, 114, ZC_GUILD_INFO2);
		ADD_TPKT(0x01ec, 26, ZC_GUILD_MEMBER_MAP_CHANGE);
		ADD_TPKT(0x016f, 182, ZC_GUILD_NOTICE);
		ADD_TPKT(0x0162, -1, ZC_GUILD_SKILLINFO);
		ADD_TPKT(0x01b8, 3, ZC_GUILD_ZENY_ACK);
		ADD_TPKT(0x01ff, 10, ZC_HIGHJUMP);
		ADD_TPKT(0x01c2, 10, ZC_INFO_REMAINTIME);
		ADD_TPKT(0x017b, -1, ZC_ITEMCOMPOSITION_LIST);
		ADD_TPKT(0x0177, -1, ZC_ITEMIDENTIFY_LIST);
		ADD_TPKT(0x00a1, 6, ZC_ITEM_DISAPPEAR);
		ADD_TPKT(0x009d, 17, ZC_ITEM_ENTRY);
		ADD_TPKT(0x009e, 17, ZC_ITEM_FALL_ENTRY);
		ADD_TPKT(0x00a0, 23, ZC_ITEM_PICKUP_ACK);
		ADD_TPKT(0x00af, 6, ZC_ITEM_THROW_ACK);
		ADD_TPKT(0x00b1, 8, ZC_LONGPAR_CHANGE);
		ADD_TPKT(0x018d, -1, ZC_MAKABLEITEMLIST);
		ADD_TPKT(0x01ad, -1, ZC_MAKINGARROW_LIST);
		ADD_TPKT(0x0154, -1, ZC_MEMBERMGR_INFO);
		ADD_TPKT(0x0182, 106, ZC_MEMBER_ADD);
		ADD_TPKT(0x00dd, 29, ZC_MEMBER_EXIT);
		ADD_TPKT(0x00dc, 28, ZC_MEMBER_NEWENTRY);
		ADD_TPKT(0x00b7, -1, ZC_MENU_LIST);
		ADD_TPKT(0x018c, 29, ZC_MONSTER_INFO);
		ADD_TPKT(0x01cc, 9, ZC_MONSTER_TALK);
		ADD_TPKT(0x0196, 9, ZC_MSG_STATE_CHANGE);
		ADD_TPKT(0x010c, 6, ZC_MVP);
		ADD_TPKT(0x010a, 4, ZC_MVP_GETTING_ITEM);
		ADD_TPKT(0x010b, 6, ZC_MVP_GETTING_SPECIAL_EXP);
		ADD_TPKT(0x014c, -1, ZC_MYGUILD_BASIC_INFO);
		ADD_TPKT(0x00a3, -1, ZC_NORMAL_ITEMLIST);
		ADD_TPKT(0x01ee, -1, ZC_NORMAL_ITEMLIST2);
		ADD_TPKT(0x008a, 29, ZC_NOTIFY_ACT);
		ADD_TPKT(0x007a, 58, ZC_NOTIFY_ACTENTRY);
		ADD_TPKT(0x008b, 23, ZC_NOTIFY_ACT_POSITION);
		ADD_TPKT(0x0121, 14, ZC_NOTIFY_CARTITEM_COUNTINFO);
		ADD_TPKT(0x008d, -1, ZC_NOTIFY_CHAT);
		ADD_TPKT(0x0109, -1, ZC_NOTIFY_CHAT_PARTY);
		ADD_TPKT(0x019b, 10, ZC_NOTIFY_EFFECT);
		ADD_TPKT(0x01f3, 10, ZC_NOTIFY_EFFECT2);
		ADD_TPKT(0x0117, 18, ZC_NOTIFY_GROUNDSKILL);
		ADD_TPKT(0x0106, 10, ZC_NOTIFY_HP_TO_GROUPM);
		ADD_TPKT(0x0075, -1, ZC_NOTIFY_INITCHAR);
		ADD_TPKT(0x014b, 27, ZC_NOTIFY_MANNER_POINT_GIVEN);
		ADD_TPKT(0x0189, 4, ZC_NOTIFY_MAPINFO);
		ADD_TPKT(0x0199, 4, ZC_NOTIFY_MAPPROPERTY);
		ADD_TPKT(0x01d6, 4, ZC_NOTIFY_MAPPROPERTY2);
		ADD_TPKT(0x0086, 16, ZC_NOTIFY_MOVE);
		ADD_TPKT(0x007b, 60, ZC_NOTIFY_MOVEENTRY);
		ADD_TPKT(0x01da, 60, ZC_NOTIFY_MOVEENTRY2);
		ADD_TPKT(0x0079, 53, ZC_NOTIFY_NEWENTRY);
		ADD_TPKT(0x01d9, 53, ZC_NOTIFY_NEWENTRY2);
		ADD_TPKT(0x008e, -1, ZC_NOTIFY_PLAYERCHAT);
		ADD_TPKT(0x0087, 12, ZC_NOTIFY_PLAYERMOVE);
		ADD_TPKT(0x0107, 10, ZC_NOTIFY_POSITION_TO_GROUPM);
		ADD_TPKT(0x01eb, 10, ZC_NOTIFY_POSITION_TO_GUILDM);
		ADD_TPKT(0x019a, 14, ZC_NOTIFY_RANKING);
		ADD_TPKT(0x0114, 31, ZC_NOTIFY_SKILL);
		ADD_TPKT(0x01de, 33, ZC_NOTIFY_SKILL2);
		ADD_TPKT(0x0115, 35, ZC_NOTIFY_SKILL_POSITION);
		ADD_TPKT(0x0078, 54, ZC_NOTIFY_STANDENTRY);
		ADD_TPKT(0x01d8, 54, ZC_NOTIFY_STANDENTRY2);
		ADD_TPKT(0x007c, 41, ZC_NOTIFY_STANDENTRY_NPC);
		ADD_TPKT(0x00f2, 6, ZC_NOTIFY_STOREITEM_COUNTINFO);
		ADD_TPKT(0x007f, 6, ZC_NOTIFY_TIME);
		ADD_TPKT(0x0076, 9, ZC_NOTIFY_UPDATECHAR);
		ADD_TPKT(0x0077, 5, ZC_NOTIFY_UPDATEPLAYER);
		ADD_TPKT(0x0080, 7, ZC_NOTIFY_VANISH);
		ADD_TPKT(0x0093, 2, ZC_NPCACK_ENABLE);
		ADD_TPKT(0x0091, 22, ZC_NPCACK_MAPMOVE);
		ADD_TPKT(0x0092, 28, ZC_NPCACK_SERVERMOVE);
		ADD_TPKT(0x01b0, 11, ZC_NPCSPRITE_CHANGE);
		ADD_TPKT(0x012d, 4, ZC_OPENSTORE);
		ADD_TPKT(0x0142, 6, ZC_OPEN_EDITDLG);
		ADD_TPKT(0x01d4, 6, ZC_OPEN_EDITDLGSTR);
		ADD_TPKT(0x0164, -1, ZC_OTHER_GUILD_LIST);
		ADD_TPKT(0x00b0, 8, ZC_PAR_CHANGE);
		ADD_TPKT(0x01ab, 12, ZC_PAR_CHANGE_USER);
		ADD_TPKT(0x00c6, -1, ZC_PC_PURCHASE_ITEMLIST);
		ADD_TPKT(0x0133, -1, ZC_PC_PURCHASE_ITEMLIST_FROMMC);
		ADD_TPKT(0x0136, -1, ZC_PC_PURCHASE_MYITEMLIST);
		ADD_TPKT(0x00ca, 3, ZC_PC_PURCHASE_RESULT);
		ADD_TPKT(0x0135, 7, ZC_PC_PURCHASE_RESULT_FROMMC);
		ADD_TPKT(0x00c7, -1, ZC_PC_SELL_ITEMLIST);
		ADD_TPKT(0x00cb, 3, ZC_PC_SELL_RESULT);
		ADD_TPKT(0x01a6, -1, ZC_PETEGG_LIST);
		ADD_TPKT(0x01aa, 10, ZC_PET_ACT);
		ADD_TPKT(0x0166, -1, ZC_POSITION_ID_NAME_INFO);
		ADD_TPKT(0x0160, -1, ZC_POSITION_INFO);
		ADD_TPKT(0x01a2, 35, ZC_PROPERTY_PET);
		ADD_TPKT(0x013d, 6, ZC_RECOVERY);
		ADD_TPKT(0x0074, 3, ZC_REFUSE_ENTER);
		ADD_TPKT(0x00da, 3, ZC_REFUSE_ENTER_ROOM);
		ADD_TPKT(0x0084, 2, ZC_REFUSE_QUIT);
		ADD_TPKT(0x01fc, -1, ZC_REPAIRITEMLIST);
		ADD_TPKT(0x01c1, 14, ZC_REPLY_REMAINTIME);
		ADD_TPKT(0x0207, 34, ZC_REQ_ADD_FRIENDS);
		ADD_TPKT(0x0171, 30, ZC_REQ_ALLY_GUILD);
		ADD_TPKT(0x01f6, 34, ZC_REQ_BABY);
		ADD_TPKT(0x01e2, 34, ZC_REQ_COUPLE);
		ADD_TPKT(0x00e5, 26, ZC_REQ_EXCHANGE_ITEM);
		ADD_TPKT(0x01f4, 32, ZC_REQ_EXCHANGE_ITEM2);
		ADD_TPKT(0x00ae, -1, ZC_REQ_ITEM_EXPLANATION_ACK);
		ADD_TPKT(0x00fe, 30, ZC_REQ_JOIN_GROUP);
		ADD_TPKT(0x016a, 30, ZC_REQ_JOIN_GUILD);
		ADD_TPKT(0x00ac, 7, ZC_REQ_TAKEOFF_EQUIP_ACK);
		ADD_TPKT(0x00aa, 7, ZC_REQ_WEAR_EQUIP_ACK);
		ADD_TPKT(0x00b3, 3, ZC_RESTART_ACK);
		ADD_TPKT(0x0167, 3, ZC_RESULT_MAKE_GUILD);
		ADD_TPKT(0x0148, 8, ZC_RESURRECTION);
		ADD_TPKT(0x00e1, 30, ZC_ROLE_CHANGE);
		ADD_TPKT(0x00d7, -1, ZC_ROOM_NEWENTRY);
		ADD_TPKT(0x00b4, -1, ZC_SAY_DIALOG);
		ADD_TPKT(0x00c4, 6, ZC_SELECT_DEALTYPE);
		ADD_TPKT(0x00d1, 4, ZC_SETTING_WHISPER_PC);
		ADD_TPKT(0x00d2, 4, ZC_SETTING_WHISPER_STATE);
		ADD_TPKT(0x01b1, 7, ZC_SHOWDIGIT);
		ADD_TPKT(0x0145, 19, ZC_SHOW_IMAGE);
		ADD_TPKT(0x01b3, 67, ZC_SHOW_IMAGE2);
		ADD_TPKT(0x010f, -1, ZC_SKILLINFO_LIST);
		ADD_TPKT(0x010e, 11, ZC_SKILLINFO_UPDATE);
		ADD_TPKT(0x0120, 6, ZC_SKILL_DISAPPEAR);
		ADD_TPKT(0x011f, 16, ZC_SKILL_ENTRY);
		ADD_TPKT(0x01c9, 97, ZC_SKILL_ENTRY2);
		ADD_TPKT(0x01ac, 6, ZC_SKILL_UPDATE);
		ADD_TPKT(0x01d3, 35, ZC_SOUND);
		ADD_TPKT(0x01d0, 8, ZC_SPIRITS);
		ADD_TPKT(0x01e1, 8, ZC_SPIRITS2);
		ADD_TPKT(0x00c3, 8, ZC_SPRITE_CHANGE);
		ADD_TPKT(0x01d7, 11, ZC_SPRITE_CHANGE2);
		ADD_TPKT(0x020e, 24, ZC_STARSKILL);
		ADD_TPKT(0x01f8, 2, ZC_START_BABY);
		ADD_TPKT(0x019e, 2, ZC_START_CAPTURE);
		ADD_TPKT(0x01e4, 2, ZC_START_COUPLE);
		ADD_TPKT(0x0119, 13, ZC_STATE_CHANGE);
		ADD_TPKT(0x00bd, 44, ZC_STATUS);
		ADD_TPKT(0x00be, 5, ZC_STATUS_CHANGE);
		ADD_TPKT(0x00bc, 6, ZC_STATUS_CHANGE_ACK);
		ADD_TPKT(0x0088, 10, ZC_STOPMOVE);
		ADD_TPKT(0x0131, 86, ZC_STORE_ENTRY);
		ADD_TPKT(0x00a6, -1, ZC_STORE_EQUIPMENT_ITEMLIST);
		ADD_TPKT(0x00a5, -1, ZC_STORE_NORMAL_ITEMLIST);
		ADD_TPKT(0x01f0, -1, ZC_STORE_NORMAL_ITEMLIST2);
		ADD_TPKT(0x0191, 86, ZC_TALKBOX_CHATCONTENTS);
		ADD_TPKT(0x010d, 2, ZC_THROW_MVPITEM);
		ADD_TPKT(0x01a0, 3, ZC_TRYCAPTURE_MONSTER);
		ADD_TPKT(0x016d, 14, ZC_UPDATE_CHARSTAT);
		ADD_TPKT(0x01f2, 20, ZC_UPDATE_CHARSTAT2);
		ADD_TPKT(0x016c, 43, ZC_UPDATE_GDID);
		ADD_TPKT(0x0192, 24, ZC_UPDATE_MAPINFO);
		ADD_TPKT(0x00c2, 6, ZC_USER_COUNT);
		ADD_TPKT(0x013e, 24, ZC_USESKILL_ACK);
		ADD_TPKT(0x00a8, 7, ZC_USE_ITEM_ACK);
		ADD_TPKT(0x01c8, 13, ZC_USE_ITEM_ACK2);
		ADD_TPKT(0x011a, 15, ZC_USE_SKILL);
		ADD_TPKT(0x00b5, 6, ZC_WAIT_DIALOG);
		ADD_TPKT(0x011c, 68, ZC_WARPLIST);
		ADD_TPKT(0x0097, -1, ZC_WHISPER);
		ADD_TPKT(0x00d4, -1, ZC_WHISPER_LIST);
#undef ADD_HPKT
#undef ADD_TPKT
	}

	~PacketLengthTable() { }

	std::shared_ptr<ZoneSession> get_session() { return _session.lock(); }

	HPacketTablePairType get_hpacket_info(uint16_t packet_id) { return _hpacket_length_table.at(packet_id); }
	TPacketTablePairType get_tpacket_info(uint16_t packet_id) { return _tpacket_length_table.at(packet_id); }

protected:
	LockedLookupTable<uint16_t, HPacketTablePairType> _hpacket_length_table;
	LockedLookupTable<uint16_t, TPacketTablePairType> _tpacket_length_table;
	std::weak_ptr<ZoneSession> _session;

};
}
}
#endif /* HORIZON_ZONE_AD_PACKET_LENGTH_TABLE */
