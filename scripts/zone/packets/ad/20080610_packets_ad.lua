-----------------------------------------------------
--       _   _            _                        --
--      | | | |          (_)                       --
--      | |_| | ___  _ __ _ _______  _ __          --
--      |  _  |/ _ \| '__| |_  / _ \| '_  \        --
--      | | | | (_) | |  | |/ / (_) | | | |        --
--      \_| |_/\___/|_|  |_/___\___/|_| |_|        --
-----------------------------------------------------
-- This file is part of Horizon (c).
-- Copyright (c) 2019 Horizon Dev Team.
--
-- Base Author - Sagun Khosla. (sagunxp@gmail.com)
--
-- This library is free software; you can redistribute it and/or modify
-- it under the terms of the GNU General Public License as published by
-- the Free Software Foundation, either version 3 of the License, or
-- (at your option) any later version.
--
-- This library is distributed in the hope that it will be useful,
-- but WITHOUT ANY WARRANTY; without even the implied warranty of
-- MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
-- GNU General Public License for more details.
--
-- You should have received a copy of the GNU General Public License
-- along with this library.  If not, see <http://www.gnu.org/licenses/>.
-----------------------------------------------------

local d = require('default_packets_ad')

d:add(0x00e6, 6, require('CZ_ACK_EXCHANGE_ITEM'))
d:add(0x0208, 15, require('CZ_ACK_REQ_ADD_FRIENDS'))
d:add(0x00c5, 114, require('CZ_ACK_SELECT_DEALTYPE'))
d:add(0x00e8, -1, require('CZ_ADD_EXCHANGE_ITEM'))
d:add(0x0202, -1, require('CZ_ADD_FRIENDS'))
d:add(0x0218, 30, require('CZ_ALCHEMIST_RANK'))
d:add(0x0172, 3, require('CZ_ALLY_GUILD'))
d:add(0x0217, 53, require('CZ_BLACKSMITH_RANK'))
d:add(0x0099, 9, require('CZ_BROADCAST'))
d:add(0x00ed, -1, require('CZ_CANCEL_EXCHANGE_ITEM'))
d:add(0x0118, 22, require('CZ_CANCEL_LOCKON'))
d:add(0x0102, -1, require('CZ_CHANGE_GROUPEXPOPTION'))
d:add(0x00b8, -1, require('CZ_CHOOSE_MENU'))
d:add(0x01ed, -1, require('CZ_CHOPOKGI'))
d:add(0x0146, 5, require('CZ_CLOSE_DIALOG'))
d:add(0x01a1, 10, require('CZ_COMMAND_PET'))
d:add(0x00eb, -1, require('CZ_CONCLUDE_EXCHANGE_ITEM'))
d:add(0x0090, 6, require('CZ_CONTACTNPC'))
d:add(0x0203, -1, require('CZ_DELETE_FRIENDS'))
d:add(0x00ce, 22, require('CZ_DISCONNECT_ALL_CHARACTER'))
d:add(0x00cc, 28, require('CZ_DISCONNECT_CHARACTER'))
d:add(0x01e7, 4, require('CZ_DORIDORI'))
d:add(0x00ef, 9, require('CZ_EXEC_EXCHANGE_ITEM'))
d:add(0x00e3, -1, require('CZ_EXIT_ROOM'))
d:add(0x017e, 2, require('CZ_GUILD_CHAT'))
d:add(0x0143, 10, require('CZ_INPUT_EDITDLG'))
d:add(0x01d5, -1, require('CZ_INPUT_EDITDLGSTR'))
d:add(0x02f6, 5, require('CZ_IRMAIL_LIST'))
d:add(0x02f3, 30, require('CZ_IRMAIL_SEND'))
d:add(0x013f, 7, require('CZ_ITEM_CREATE'))
d:add(0x00ff, -1, require('CZ_JOIN_GROUP'))
d:add(0x0237, 4, require('CZ_KILLER_RANK'))
d:add(0x019c, 6, require('CZ_LOCALBROADCAST'))
d:add(0x00f9, -1, require('CZ_MAKE_GROUP'))
d:add(0x01e8, 27, require('CZ_MAKE_GROUP2'))
d:add(0x0140, 11, require('CZ_MOVETO_MAP'))
d:add(0x0126, 97, require('CZ_MOVE_ITEM_FROM_BODY_TO_CART'))
d:add(0x0129, 8, require('CZ_MOVE_ITEM_FROM_CART_TO_STORE'))
d:add(0x0128, 31, require('CZ_MOVE_ITEM_FROM_STORE_TO_CART'))
d:add(0x007d, 26, require('CZ_NOTIFY_ACTORINIT'))
d:add(0x0134, 67, require('CZ_PC_PURCHASE_ITEMLIST_FROMMC'))
d:add(0x00c9, 9, require('CZ_PC_SELL_ITEMLIST'))
d:add(0x01bc, 2, require('CZ_RECALL'))
d:add(0x01bd, 3, require('CZ_RECALL_GID'))
d:add(0x0161, 5, require('CZ_REG_CHANGE_GUILD_POSITIONINFO'))
d:add(0x011d, 28, require('CZ_REMEMBER_WARPPOINT'))
d:add(0x018e, 59, require('CZ_REQMAKINGITEM'))
d:add(0x0233, 66, require('CZ_REQUEST_ACTNPC'))
d:add(0x0108, 2, require('CZ_REQUEST_CHAT_PARTY'))
d:add(0x0232, 30, require('CZ_REQUEST_MOVENPC'))
d:add(0x015b, 54, require('CZ_REQ_BAN_GUILD'))
d:add(0x0130, 30, require('CZ_REQ_BUY_FROMMC'))
d:add(0x012a, -1, require('CZ_REQ_CARTOFF'))
d:add(0x0155, -1, require('CZ_REQ_CHANGE_MEMBERPOS'))
d:add(0x018a, -1, require('CZ_REQ_DISCONNECT'))
d:add(0x00bf, -1, require('CZ_REQ_EMOTION'))
d:add(0x0103, -1, require('CZ_REQ_EXPEL_GROUP_MEMBER'))
d:add(0x00e2, 282, require('CZ_REQ_EXPEL_MEMBER'))
d:add(0x0149, 8, require('CZ_REQ_GIVE_MANNER_POINT'))
d:add(0x017c, -1, require('CZ_REQ_ITEMCOMPOSITION'))
d:add(0x017a, -1, require('CZ_REQ_ITEMCOMPOSITION_LIST'))
d:add(0x01fd, 10, require('CZ_REQ_ITEMREPAIR'))
d:add(0x00fc, -1, require('CZ_REQ_JOIN_GROUP'))
d:add(0x0168, 11, require('CZ_REQ_JOIN_GUILD'))
d:add(0x0100, 2, require('CZ_REQ_LEAVE_GROUP'))
d:add(0x0159, 3, require('CZ_REQ_LEAVE_GUILD'))
d:add(0x0165, 4, require('CZ_REQ_MAKE_GUILD'))
d:add(0x01ae, 43, require('CZ_REQ_MAKINGARROW'))
d:add(0x00b9, -1, require('CZ_REQ_NEXT_SCRIPT'))
d:add(0x01b2, 2, require('CZ_REQ_OPENSTORE2'))
d:add(0x00e0, 6, require('CZ_REQ_ROLE_CHANGE'))
d:add(0x00ab, 16, require('CZ_REQ_TAKEOFF_EQUIP'))
d:add(0x00c1, -1, require('CZ_REQ_USER_COUNT'))
d:add(0x00a9, 282, require('CZ_REQ_WEAR_EQUIP'))
d:add(0x00b2, 13, require('CZ_RESTART'))
d:add(0x01ce, 3, require('CZ_SELECTAUTOSPELL'))
d:add(0x00cf, 57, require('CZ_SETTING_WHISPER_PC'))
d:add(0x00d0, -1, require('CZ_SETTING_WHISPER_STATE'))
d:add(0x00bb, 36, require('CZ_STATUS_CHANGE'))
d:add(0x0225, 32, require('CZ_TAEKWON_RANK'))
d:add(0x019f, -1, require('CZ_TRYCAPTURE_MONSTER'))
d:add(0x0112, 6, require('CZ_UPGRADE_SKILLLEVEL'))
d:add(0x0096, -1, require('CZ_WHISPER'))
d:add(0x0083, 6, require('ZC_ACCEPT_QUIT'))
d:add(0x012c, -1, require('ZC_ACK_ADDITEM_TO_CART'))
d:add(0x00d6, 26, require('ZC_ACK_CREATE_CHATROOM'))
d:add(0x015e, -1, require('ZC_ACK_DISORGANIZE_GUILD_RESULT'))
d:add(0x00e7, 14, require('ZC_ACK_EXCHANGE_ITEM'))
d:add(0x017d, -1, require('ZC_ACK_ITEMCOMPOSITION'))
d:add(0x0179, -1, require('ZC_ACK_ITEMIDENTIFY'))
d:add(0x0188, 29, require('ZC_ACK_ITEMREFINING'))
d:add(0x01fe, -1, require('ZC_ACK_ITEMREPAIR'))
d:add(0x015a, 24, require('ZC_ACK_LEAVE_GUILD'))
d:add(0x0274, 4, require('ZC_ACK_MAIL_RETURN'))
d:add(0x011e, 5, require('ZC_ACK_REMEMBER_WARPPOINT'))
d:add(0x018f, 6, require('ZC_ACK_REQMAKINGITEM'))
d:add(0x0095, -1, require('ZC_ACK_REQNAME'))
d:add(0x0195, -1, require('ZC_ACK_REQNAMEALL'))
d:add(0x0194, 2, require('ZC_ACK_REQNAME_BYGID'))
d:add(0x018b, -1, require('ZC_ACK_REQ_DISCONNECT'))
d:add(0x00fd, 6, require('ZC_ACK_REQ_JOIN_GROUP'))
d:add(0x0169, -1, require('ZC_ACK_REQ_JOIN_GUILD'))
d:add(0x0110, 3, require('ZC_ACK_TOUSESKILL'))
d:add(0x0098, 26, require('ZC_ACK_WHISPER'))
d:add(0x013b, 22, require('ZC_ACTION_FAILURE'))
d:add(0x00e9, 8, require('ZC_ADD_EXCHANGE_ITEM'))
d:add(0x0209, 6, require('ZC_ADD_FRIENDS_LIST'))
d:add(0x0124, 58, require('ZC_ADD_ITEM_TO_CART'))
d:add(0x01c5, 26, require('ZC_ADD_ITEM_TO_CART2'))
d:add(0x01c4, 33, require('ZC_ADD_ITEM_TO_STORE2'))
d:add(0x0104, -1, require('ZC_ADD_MEMBER_TO_GROUP'))
d:add(0x01e9, -1, require('ZC_ADD_MEMBER_TO_GROUP2'))
d:add(0x0111, -1, require('ZC_ADD_SKILL'))
d:add(0x021c, 8, require('ZC_ALCHEMIST_POINT'))
d:add(0x021a, 23, require('ZC_ALCHEMIST_RANK'))
d:add(0x0139, 5, require('ZC_ATTACK_FAILURE_FOR_DISTANCE'))
d:add(0x013a, 30, require('ZC_ATTACK_RANGE'))
d:add(0x0147, 8, require('ZC_AUTORUN_SKILL'))
d:add(0x01cd, 102, require('ZC_AUTOSPELLLIST'))
d:add(0x0163, -1, require('ZC_BAN_LIST'))
d:add(0x021b, -1, require('ZC_BLACKSMITH_POINT'))
d:add(0x0219, 6, require('ZC_BLACKSMITH_RANK'))
d:add(0x009a, 90, require('ZC_BROADCAST'))
d:add(0x01c3, -1, require('ZC_BROADCAST2'))
d:add(0x00ee, 2, require('ZC_CANCEL_EXCHANGE_ITEM'))
d:add(0x0122, 15, require('ZC_CART_EQUIPMENT_ITEMLIST'))
d:add(0x0297, 6, require('ZC_CART_EQUIPMENT_ITEMLIST2'))
d:add(0x0123, 23, require('ZC_CART_NORMAL_ITEMLIST'))
d:add(0x01a4, 4, require('ZC_CHANGESTATE_PET'))
d:add(0x00df, 10, require('ZC_CHANGE_CHATROOM'))
d:add(0x009c, 6, require('ZC_CHANGE_DIRECTION'))
d:add(0x00b6, 3, require('ZC_CLOSE_DIALOG'))
d:add(0x00f8, 30, require('ZC_CLOSE_STORE'))
d:add(0x0144, 81, require('ZC_COMPASS'))
d:add(0x00ec, 6, require('ZC_CONCLUDE_EXCHANGE_ITEM'))
d:add(0x01ea, 4, require('ZC_CONGRATULATION'))
d:add(0x0141, 6, require('ZC_COUPLESTATUS'))
d:add(0x0137, -1, require('ZC_DELETEITEM_FROM_MCSTORE'))
d:add(0x020a, 186, require('ZC_DELETE_FRIENDS'))
d:add(0x0125, 86, require('ZC_DELETE_ITEM_FROM_CART'))
d:add(0x00f6, 6, require('ZC_DELETE_ITEM_FROM_STORE'))
d:add(0x0105, 26, require('ZC_DELETE_MEMBER_FROM_GROUP'))
d:add(0x00d8, 30, require('ZC_DESTROY_ROOM'))
d:add(0x01cf, 2, require('ZC_DEVOTIONLIST'))
d:add(0x0132, 14, require('ZC_DISAPPEAR_ENTRY'))
d:add(0x01b9, 6, require('ZC_DISPEL'))
d:add(0x00c0, 39, require('ZC_EMOTION'))
d:add(0x00a4, 10, require('ZC_EQUIPMENT_ITEMLIST'))
d:add(0x0295, -1, require('ZC_EQUIPMENT_ITEMLIST2'))
d:add(0x013c, -1, require('ZC_EQUIP_ARROW'))
d:add(0x00f0, 60, require('ZC_EXEC_EXCHANGE_ITEM'))
d:add(0x022f, -1, require('ZC_FEED_MER'))
d:add(0x01a3, -1, require('ZC_FEED_PET'))
d:add(0x0201, -1, require('ZC_FRIENDS_LIST'))
d:add(0x0227, 10, require('ZC_GAME_GUARD'))
d:add(0x0101, 2, require('ZC_GROUPINFO_CHANGE'))
d:add(0x00fb, 4, require('ZC_GROUP_LIST'))
d:add(0x01b6, 55, require('ZC_GUILD_INFO2'))
d:add(0x0162, 18, require('ZC_GUILD_SKILLINFO'))
d:add(0x0235, 6, require('ZC_HOSKILLINFO_LIST'))
d:add(0x0239, -1, require('ZC_HOSKILLINFO_UPDATE'))
d:add(0x02f5, -1, require('ZC_IRMAIL_NOTIFY'))
d:add(0x02f4, 30, require('ZC_IRMAIL_SEND_RES'))
d:add(0x017b, 2, require('ZC_ITEMCOMPOSITION_LIST'))
d:add(0x0177, 31, require('ZC_ITEMIDENTIFY_LIST'))
d:add(0x009d, 3, require('ZC_ITEM_ENTRY'))
d:add(0x009e, 10, require('ZC_ITEM_FALL_ENTRY'))
d:add(0x00a0, 26, require('ZC_ITEM_PICKUP_ACK'))
d:add(0x029a, -1, require('ZC_ITEM_PICKUP_ACK2'))
d:add(0x00af, -1, require('ZC_ITEM_THROW_ACK'))
d:add(0x0238, -1, require('ZC_KILLER_RANK'))
d:add(0x00b1, 11, require('ZC_LONGPAR_CHANGE'))
d:add(0x018d, 65, require('ZC_MAKABLEITEMLIST'))
d:add(0x01ad, 10, require('ZC_MAKINGARROW_LIST'))
d:add(0x0154, 13, require('ZC_MEMBERMGR_INFO'))
d:add(0x00dd, -1, require('ZC_MEMBER_EXIT'))
d:add(0x00dc, 2, require('ZC_MEMBER_NEWENTRY'))
d:add(0x00b7, 2, require('ZC_MENU_LIST'))
d:add(0x018c, 282, require('ZC_MONSTER_INFO'))
d:add(0x0196, 10, require('ZC_MSG_STATE_CHANGE'))
d:add(0x010c, -1, require('ZC_MVP'))
d:add(0x010a, -1, require('ZC_MVP_GETTING_ITEM'))
d:add(0x010b, 26, require('ZC_MVP_GETTING_SPECIAL_EXP'))
d:add(0x014c, 4, require('ZC_MYGUILD_BASIC_INFO'))
d:add(0x00a3, 10, require('ZC_NORMAL_ITEMLIST'))
d:add(0x01ee, 8, require('ZC_NORMAL_ITEMLIST2'))
d:add(0x008a, 28, require('ZC_NOTIFY_ACT'))
d:add(0x02e1, 26, require('ZC_NOTIFY_ACT2'))
d:add(0x007a, 53, require('ZC_NOTIFY_ACTENTRY'))
d:add(0x0121, 5, require('ZC_NOTIFY_CARTITEM_COUNTINFO'))
d:add(0x008d, 60, require('ZC_NOTIFY_CHAT'))
d:add(0x0109, -1, require('ZC_NOTIFY_CHAT_PARTY'))
d:add(0x019b, -1, require('ZC_NOTIFY_EFFECT'))
d:add(0x0106, 9, require('ZC_NOTIFY_HP_TO_GROUPM'))
d:add(0x0075, 8, require('ZC_NOTIFY_INITCHAR'))
d:add(0x0189, -1, require('ZC_NOTIFY_MAPINFO'))
d:add(0x0199, 4, require('ZC_NOTIFY_MAPPROPERTY'))
d:add(0x01d6, 6, require('ZC_NOTIFY_MAPPROPERTY2'))
d:add(0x0086, -1, require('ZC_NOTIFY_MOVE'))
d:add(0x01da, 12, require('ZC_NOTIFY_MOVEENTRY2'))
d:add(0x02ec, 6, require('ZC_NOTIFY_MOVEENTRY4'))
d:add(0x0079, 3, require('ZC_NOTIFY_NEWENTRY'))
d:add(0x01d9, 8, require('ZC_NOTIFY_NEWENTRY2'))
d:add(0x022b, 2, require('ZC_NOTIFY_NEWENTRY3'))
d:add(0x02ed, 7, require('ZC_NOTIFY_NEWENTRY4'))
d:add(0x008e, 10, require('ZC_NOTIFY_PLAYERCHAT'))
d:add(0x0087, -1, require('ZC_NOTIFY_PLAYERMOVE'))
d:add(0x01eb, 4, require('ZC_NOTIFY_POSITION_TO_GUILDM'))
d:add(0x019a, 6, require('ZC_NOTIFY_RANKING'))
d:add(0x0114, 11, require('ZC_NOTIFY_SKILL'))
d:add(0x01d8, -1, require('ZC_NOTIFY_STANDENTRY2'))
d:add(0x02ee, -1, require('ZC_NOTIFY_STANDENTRY4'))
d:add(0x00f2, 39, require('ZC_NOTIFY_STOREITEM_COUNTINFO'))
d:add(0x0077, 14, require('ZC_NOTIFY_UPDATEPLAYER'))
d:add(0x0093, 5, require('ZC_NPCACK_ENABLE'))
d:add(0x0091, 21, require('ZC_NPCACK_MAPMOVE'))
d:add(0x0092, 20, require('ZC_NPCACK_SERVERMOVE'))
d:add(0x01b0, 4, require('ZC_NPCSPRITE_CHANGE'))
d:add(0x012d, 8, require('ZC_OPENSTORE'))
d:add(0x0142, 32, require('ZC_OPEN_EDITDLG'))
d:add(0x01d4, 20, require('ZC_OPEN_EDITDLGSTR'))
d:add(0x00b0, -1, require('ZC_PAR_CHANGE'))
d:add(0x01ab, 11, require('ZC_PAR_CHANGE_USER'))
d:add(0x0287, 2, require('ZC_PC_CASH_POINT_ITEMLIST'))
d:add(0x00c6, 8, require('ZC_PC_PURCHASE_ITEMLIST'))
d:add(0x0133, 7, require('ZC_PC_PURCHASE_ITEMLIST_FROMMC'))
d:add(0x0136, 11, require('ZC_PC_PURCHASE_MYITEMLIST'))
d:add(0x00ca, -1, require('ZC_PC_PURCHASE_RESULT'))
d:add(0x0135, -1, require('ZC_PC_PURCHASE_RESULT_FROMMC'))
d:add(0x01a6, 3, require('ZC_PETEGG_LIST'))
d:add(0x01aa, 6, require('ZC_PET_ACT'))
d:add(0x0166, 27, require('ZC_POSITION_ID_NAME_INFO'))
d:add(0x0160, 5, require('ZC_POSITION_INFO'))
d:add(0x022e, -1, require('ZC_PROPERTY_HOMUN'))
d:add(0x01a2, -1, require('ZC_PROPERTY_PET'))
d:add(0x013d, 7, require('ZC_RECOVERY'))
d:add(0x00da, -1, require('ZC_REFUSE_ENTER_ROOM'))
d:add(0x01fc, 10, require('ZC_REPAIRITEMLIST'))
d:add(0x0207, 7, require('ZC_REQ_ADD_FRIENDS'))
d:add(0x0171, 10, require('ZC_REQ_ALLY_GUILD'))
d:add(0x00e5, -1, require('ZC_REQ_EXCHANGE_ITEM'))
d:add(0x01f4, -1, require('ZC_REQ_EXCHANGE_ITEM2'))
d:add(0x00fe, 2, require('ZC_REQ_JOIN_GROUP'))
d:add(0x016a, 4, require('ZC_REQ_JOIN_GUILD'))
d:add(0x00ac, 7, require('ZC_REQ_TAKEOFF_EQUIP_ACK'))
d:add(0x00aa, 4, require('ZC_REQ_WEAR_EQUIP_ACK'))
d:add(0x00b3, 6, require('ZC_RESTART_ACK'))
d:add(0x0167, 9, require('ZC_RESULT_MAKE_GUILD'))
d:add(0x023c, 4, require('ZC_RESULT_STORE_PASSWORD'))
d:add(0x0148, 2, require('ZC_RESURRECTION'))
d:add(0x00e1, -1, require('ZC_ROLE_CHANGE'))
d:add(0x00b4, 6, require('ZC_SAY_DIALOG'))
d:add(0x00d1, 6, require('ZC_SETTING_WHISPER_PC'))
d:add(0x00d2, -1, require('ZC_SETTING_WHISPER_STATE'))
d:add(0x01b3, -1, require('ZC_SHOW_IMAGE2'))
d:add(0x010f, 30, require('ZC_SKILLINFO_LIST'))
d:add(0x010e, 8, require('ZC_SKILLINFO_UPDATE'))
d:add(0x0120, 79, require('ZC_SKILL_DISAPPEAR'))
d:add(0x011f, 10, require('ZC_SKILL_ENTRY'))
d:add(0x01c9, -1, require('ZC_SKILL_ENTRY2'))
d:add(0x01ac, -1, require('ZC_SKILL_UPDATE'))
d:add(0x01d0, 7, require('ZC_SPIRITS'))
d:add(0x00c3, 42, require('ZC_SPRITE_CHANGE'))
d:add(0x01d7, -1, require('ZC_SPRITE_CHANGE2'))
d:add(0x0229, 21, require('ZC_STATE_CHANGE3'))
d:add(0x00bd, 18, require('ZC_STATUS'))
d:add(0x00be, 44, require('ZC_STATUS_CHANGE'))
d:add(0x00bc, 2, require('ZC_STATUS_CHANGE_ACK'))
d:add(0x0088, 19, require('ZC_STOPMOVE'))
d:add(0x0131, 12, require('ZC_STORE_ENTRY'))
d:add(0x00a6, -1, require('ZC_STORE_EQUIPMENT_ITEMLIST'))
d:add(0x0296, 17, require('ZC_STORE_EQUIPMENT_ITEMLIST2'))
d:add(0x00a5, 7, require('ZC_STORE_NORMAL_ITEMLIST'))
d:add(0x0224, 4, require('ZC_TAEKWON_POINT'))
d:add(0x0226, -1, require('ZC_TAEKWON_RANK'))
d:add(0x01a0, 11, require('ZC_TRYCAPTURE_MONSTER'))
d:add(0x016d, 3, require('ZC_UPDATE_CHARSTAT'))
d:add(0x016c, 28, require('ZC_UPDATE_GDID'))
d:add(0x00c2, 2, require('ZC_USER_COUNT'))
d:add(0x00a8, -1, require('ZC_USE_ITEM_ACK'))
d:add(0x01c8, -1, require('ZC_USE_ITEM_ACK2'))
d:add(0x011a, 26, require('ZC_USE_SKILL'))
d:add(0x00b5, 3, require('ZC_WAIT_DIALOG'))
d:add(0x011c, 14, require('ZC_WARPLIST'))
d:add(0x0097, 8, require('ZC_WHISPER'))

return d