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

local d = require('default_packets_ragexe')

d:add(0x0208, 18, require('CZ_ACK_REQ_ADD_FRIENDS'))
d:add(0x00c5, -1, require('CZ_ACK_SELECT_DEALTYPE'))
d:add(0x00e8, 282, require('CZ_ADD_EXCHANGE_ITEM'))
d:add(0x0217, -1, require('CZ_BLACKSMITH_RANK'))
d:add(0x0099, -1, require('CZ_BROADCAST'))
d:add(0x00ed, -1, require('CZ_CANCEL_EXCHANGE_ITEM'))
d:add(0x00de, -1, require('CZ_CHANGE_CHATROOM'))
d:add(0x019d, -1, require('CZ_CHANGE_EFFECTSTATE'))
d:add(0x0102, 7, require('CZ_CHANGE_GROUPEXPOPTION'))
d:add(0x00b8, 2, require('CZ_CHOOSE_MENU'))
d:add(0x01ed, 10, require('CZ_CHOPOKGI'))
d:add(0x0146, 3, require('CZ_CLOSE_DIALOG'))
d:add(0x01a1, -1, require('CZ_COMMAND_PET'))
d:add(0x0090, 5, require('CZ_CONTACTNPC'))
d:add(0x0203, 6, require('CZ_DELETE_FRIENDS'))
d:add(0x00ce, 9, require('CZ_DISCONNECT_ALL_CHARACTER'))
d:add(0x00cc, 6, require('CZ_DISCONNECT_CHARACTER'))
d:add(0x01e7, 8, require('CZ_DORIDORI'))
d:add(0x0436, -1, require('CZ_ENTER2'))
d:add(0x00ef, 8, require('CZ_EXEC_EXCHANGE_ITEM'))
d:add(0x017e, 6, require('CZ_GUILD_CHAT'))
d:add(0x016e, 6, require('CZ_GUILD_NOTICE'))
d:add(0x0143, 6, require('CZ_INPUT_EDITDLG'))
d:add(0x01d5, -1, require('CZ_INPUT_EDITDLGSTR'))
d:add(0x02f6, 11, require('CZ_IRMAIL_LIST'))
d:add(0x02f3, 58, require('CZ_IRMAIL_SEND'))
d:add(0x013f, -1, require('CZ_ITEM_CREATE'))
d:add(0x0363, 8, require('CZ_ITEM_THROW2'))
d:add(0x00ff, -1, require('CZ_JOIN_GROUP'))
d:add(0x016b, -1, require('CZ_JOIN_GUILD'))
d:add(0x0237, 5, require('CZ_KILLER_RANK'))
d:add(0x01e8, -1, require('CZ_MAKE_GROUP2'))
d:add(0x0140, -1, require('CZ_MOVETO_MAP'))
d:add(0x0364, 10, require('CZ_MOVE_ITEM_FROM_BODY_TO_STORE2'))
d:add(0x0365, 86, require('CZ_MOVE_ITEM_FROM_STORE_TO_BODY2'))
d:add(0x0134, 6, require('CZ_PC_PURCHASE_ITEMLIST_FROMMC'))
d:add(0x00c9, 4, require('CZ_PC_SELL_ITEMLIST'))
d:add(0x01bd, 97, require('CZ_RECALL_GID'))
d:add(0x01ba, 7, require('CZ_REMOVE_AID'))
d:add(0x018e, 4, require('CZ_REQMAKINGITEM'))
d:add(0x0368, 13, require('CZ_REQNAME2'))
d:add(0x0369, -1, require('CZ_REQNAME_BYGID2'))
d:add(0x0437, -1, require('CZ_REQUEST_ACT2'))
d:add(0x0233, 5, require('CZ_REQUEST_ACTNPC'))
d:add(0x0108, -1, require('CZ_REQUEST_CHAT_PARTY'))
d:add(0x035f, -1, require('CZ_REQUEST_MOVE2'))
d:add(0x0360, 16, require('CZ_REQUEST_TIME2'))
d:add(0x015b, -1, require('CZ_REQ_BAN_GUILD'))
d:add(0x0130, -1, require('CZ_REQ_BUY_FROMMC'))
d:add(0x012a, 8, require('CZ_REQ_CARTOFF'))
d:add(0x0155, 2, require('CZ_REQ_CHANGE_MEMBERPOS'))
d:add(0x018a, 186, require('CZ_REQ_DISCONNECT'))
d:add(0x00bf, -1, require('CZ_REQ_EMOTION'))
d:add(0x014d, 282, require('CZ_REQ_GUILD_MENUINTERFACE'))
d:add(0x017c, 5, require('CZ_REQ_ITEMCOMPOSITION'))
d:add(0x01fd, 32, require('CZ_REQ_ITEMREPAIR'))
d:add(0x0100, -1, require('CZ_REQ_LEAVE_GROUP'))
d:add(0x0159, -1, require('CZ_REQ_LEAVE_GUILD'))
d:add(0x01ae, 22, require('CZ_REQ_MAKINGARROW'))
d:add(0x00b9, -1, require('CZ_REQ_NEXT_SCRIPT'))
d:add(0x01b2, -1, require('CZ_REQ_OPENSTORE2'))
d:add(0x00e0, -1, require('CZ_REQ_ROLE_CHANGE'))
d:add(0x00ab, 79, require('CZ_REQ_TAKEOFF_EQUIP'))
d:add(0x00c1, 21, require('CZ_REQ_USER_COUNT'))
d:add(0x00a9, 18, require('CZ_REQ_WEAR_EQUIP'))
d:add(0x00d3, 10, require('CZ_REQ_WHISPER_LIST'))
d:add(0x01a7, -1, require('CZ_SELECT_PETEGG'))
d:add(0x011b, -1, require('CZ_SELECT_WARPPOINT'))
d:add(0x00cf, -1, require('CZ_SETTING_WHISPER_PC'))
d:add(0x00d0, 29, require('CZ_SETTING_WHISPER_STATE'))
d:add(0x01bb, 27, require('CZ_SHIFT'))
d:add(0x0225, 5, require('CZ_TAEKWON_RANK'))
d:add(0x019f, -1, require('CZ_TRYCAPTURE_MONSTER'))
d:add(0x0112, 4, require('CZ_UPGRADE_SKILLLEVEL'))
d:add(0x0439, 30, require('CZ_USE_ITEM2'))
d:add(0x0438, 10, require('CZ_USE_SKILL2'))
d:add(0x0366, 14, require('CZ_USE_SKILL_TOGROUND2'))
d:add(0x0367, 11, require('CZ_USE_SKILL_TOGROUND_WITHTALKBOX2'))
d:add(0x0083, 2, require('ZC_ACCEPT_QUIT'))
d:add(0x012c, -1, require('ZC_ACK_ADDITEM_TO_CART'))
d:add(0x00ea, 4, require('ZC_ACK_ADD_EXCHANGE_ITEM'))
d:add(0x00d6, -1, require('ZC_ACK_CREATE_CHATROOM'))
d:add(0x015e, 32, require('ZC_ACK_DISORGANIZE_GUILD_RESULT'))
d:add(0x00e7, 33, require('ZC_ACK_EXCHANGE_ITEM'))
d:add(0x01f5, -1, require('ZC_ACK_EXCHANGE_ITEM2'))
d:add(0x0179, 4, require('ZC_ACK_ITEMIDENTIFY'))
d:add(0x0188, 3, require('ZC_ACK_ITEMREFINING'))
d:add(0x01fe, -1, require('ZC_ACK_ITEMREPAIR'))
d:add(0x0274, 8, require('ZC_ACK_MAIL_RETURN'))
d:add(0x00fa, -1, require('ZC_ACK_MAKE_GROUP'))
d:add(0x018f, -1, require('ZC_ACK_REQMAKINGITEM'))
d:add(0x0195, -1, require('ZC_ACK_REQNAMEALL'))
d:add(0x018b, -1, require('ZC_ACK_REQ_DISCONNECT'))
d:add(0x00fd, 6, require('ZC_ACK_REQ_JOIN_GROUP'))
d:add(0x0169, 53, require('ZC_ACK_REQ_JOIN_GUILD'))
d:add(0x0110, 16, require('ZC_ACK_TOUSESKILL'))
d:add(0x013b, -1, require('ZC_ACTION_FAILURE'))
d:add(0x00e9, 6, require('ZC_ADD_EXCHANGE_ITEM'))
d:add(0x0209, 3, require('ZC_ADD_FRIENDS_LIST'))
d:add(0x0124, 4, require('ZC_ADD_ITEM_TO_CART'))
d:add(0x01c5, 3, require('ZC_ADD_ITEM_TO_CART2'))
d:add(0x00f4, 4, require('ZC_ADD_ITEM_TO_STORE'))
d:add(0x01c4, 10, require('ZC_ADD_ITEM_TO_STORE2'))
d:add(0x0139, 7, require('ZC_ATTACK_FAILURE_FOR_DISTANCE'))
d:add(0x013a, 11, require('ZC_ATTACK_RANGE'))
d:add(0x0147, -1, require('ZC_AUTORUN_SKILL'))
d:add(0x0219, -1, require('ZC_BLACKSMITH_RANK'))
d:add(0x009a, 2, require('ZC_BROADCAST'))
d:add(0x01c3, -1, require('ZC_BROADCAST2'))
d:add(0x00ee, 10, require('ZC_CANCEL_EXCHANGE_ITEM'))
d:add(0x0122, 65, require('ZC_CART_EQUIPMENT_ITEMLIST'))
d:add(0x0123, -1, require('ZC_CART_NORMAL_ITEMLIST'))
d:add(0x0230, -1, require('ZC_CHANGESTATE_MER'))
d:add(0x01a4, 10, require('ZC_CHANGESTATE_PET'))
d:add(0x009c, 2, require('ZC_CHANGE_DIRECTION'))
d:add(0x00b6, 4, require('ZC_CLOSE_DIALOG'))
d:add(0x0144, 5, require('ZC_COMPASS'))
d:add(0x00ec, -1, require('ZC_CONCLUDE_EXCHANGE_ITEM'))
d:add(0x01ea, 8, require('ZC_CONGRATULATION'))
d:add(0x0141, -1, require('ZC_COUPLESTATUS'))
d:add(0x020a, 4, require('ZC_DELETE_FRIENDS'))
d:add(0x0125, 4, require('ZC_DELETE_ITEM_FROM_CART'))
d:add(0x00f6, -1, require('ZC_DELETE_ITEM_FROM_STORE'))
d:add(0x01cf, -1, require('ZC_DEVOTIONLIST'))
d:add(0x0132, -1, require('ZC_DISAPPEAR_ENTRY'))
d:add(0x00a4, 6, require('ZC_EQUIPMENT_ITEMLIST'))
d:add(0x0295, 14, require('ZC_EQUIPMENT_ITEMLIST2'))
d:add(0x00f0, -1, require('ZC_EXEC_EXCHANGE_ITEM'))
d:add(0x022f, -1, require('ZC_FEED_MER'))
d:add(0x01a3, 10, require('ZC_FEED_PET'))
d:add(0x0206, 8, require('ZC_FRIENDS_STATE'))
d:add(0x0227, 9, require('ZC_GAME_GUARD'))
d:add(0x0101, 10, require('ZC_GROUPINFO_CHANGE'))
d:add(0x00fb, 8, require('ZC_GROUP_LIST'))
d:add(0x017f, 30, require('ZC_GUILD_CHAT'))
d:add(0x01b6, -1, require('ZC_GUILD_INFO2'))
d:add(0x016f, 11, require('ZC_GUILD_NOTICE'))
d:add(0x0162, 7, require('ZC_GUILD_SKILLINFO'))
d:add(0x02f5, 10, require('ZC_IRMAIL_NOTIFY'))
d:add(0x02f4, -1, require('ZC_IRMAIL_SEND_RES'))
d:add(0x0177, 3, require('ZC_ITEMIDENTIFY_LIST'))
d:add(0x009d, 6, require('ZC_ITEM_ENTRY'))
d:add(0x009e, 3, require('ZC_ITEM_FALL_ENTRY'))
d:add(0x029a, -1, require('ZC_ITEM_PICKUP_ACK2'))
d:add(0x00b1, 8, require('ZC_LONGPAR_CHANGE'))
d:add(0x0154, 7, require('ZC_MEMBERMGR_INFO'))
d:add(0x00dd, -1, require('ZC_MEMBER_EXIT'))
d:add(0x00b7, 6, require('ZC_MENU_LIST'))
d:add(0x018c, 26, require('ZC_MONSTER_INFO'))
d:add(0x0196, 5, require('ZC_MSG_STATE_CHANGE'))
d:add(0x010b, 14, require('ZC_MVP_GETTING_SPECIAL_EXP'))
d:add(0x014c, -1, require('ZC_MYGUILD_BASIC_INFO'))
d:add(0x00a3, 6, require('ZC_NORMAL_ITEMLIST'))
d:add(0x008a, 10, require('ZC_NOTIFY_ACT'))
d:add(0x02e1, -1, require('ZC_NOTIFY_ACT2'))
d:add(0x008d, -1, require('ZC_NOTIFY_CHAT'))
d:add(0x0109, 17, require('ZC_NOTIFY_CHAT_PARTY'))
d:add(0x019b, 8, require('ZC_NOTIFY_EFFECT'))
d:add(0x0106, -1, require('ZC_NOTIFY_HP_TO_GROUPM'))
d:add(0x0075, -1, require('ZC_NOTIFY_INITCHAR'))
d:add(0x0199, 4, require('ZC_NOTIFY_MAPPROPERTY'))
d:add(0x01d6, 28, require('ZC_NOTIFY_MAPPROPERTY2'))
d:add(0x0086, 7, require('ZC_NOTIFY_MOVE'))
d:add(0x007b, 27, require('ZC_NOTIFY_MOVEENTRY'))
d:add(0x01da, 3, require('ZC_NOTIFY_MOVEENTRY2'))
d:add(0x022c, 15, require('ZC_NOTIFY_MOVEENTRY3'))
d:add(0x0079, 3, require('ZC_NOTIFY_NEWENTRY'))
d:add(0x02ed, 17, require('ZC_NOTIFY_NEWENTRY4'))
d:add(0x008e, -1, require('ZC_NOTIFY_PLAYERCHAT'))
d:add(0x0087, 60, require('ZC_NOTIFY_PLAYERMOVE'))
d:add(0x0107, -1, require('ZC_NOTIFY_POSITION_TO_GROUPM'))
d:add(0x01eb, -1, require('ZC_NOTIFY_POSITION_TO_GUILDM'))
d:add(0x019a, -1, require('ZC_NOTIFY_RANKING'))
d:add(0x01de, 2, require('ZC_NOTIFY_SKILL2'))
d:add(0x02ee, -1, require('ZC_NOTIFY_STANDENTRY4'))
d:add(0x007c, -1, require('ZC_NOTIFY_STANDENTRY_NPC'))
d:add(0x0077, 3, require('ZC_NOTIFY_UPDATEPLAYER'))
d:add(0x0080, 27, require('ZC_NOTIFY_VANISH'))
d:add(0x0093, 6, require('ZC_NPCACK_ENABLE'))
d:add(0x0092, -1, require('ZC_NPCACK_SERVERMOVE'))
d:add(0x01d4, -1, require('ZC_OPEN_EDITDLGSTR'))
d:add(0x0287, -1, require('ZC_PC_CASH_POINT_ITEMLIST'))
d:add(0x00ca, -1, require('ZC_PC_PURCHASE_RESULT'))
d:add(0x0135, 114, require('ZC_PC_PURCHASE_RESULT_FROMMC'))
d:add(0x00c7, 6, require('ZC_PC_SELL_ITEMLIST'))
d:add(0x01a6, 14, require('ZC_PETEGG_LIST'))
d:add(0x01aa, 2, require('ZC_PET_ACT'))
d:add(0x0166, -1, require('ZC_POSITION_ID_NAME_INFO'))
d:add(0x0160, 102, require('ZC_POSITION_INFO'))
d:add(0x022e, -1, require('ZC_PROPERTY_HOMUN'))
d:add(0x01a2, 26, require('ZC_PROPERTY_PET'))
d:add(0x013d, -1, require('ZC_RECOVERY'))
d:add(0x00da, 90, require('ZC_REFUSE_ENTER_ROOM'))
d:add(0x01fc, 3, require('ZC_REPAIRITEMLIST'))
d:add(0x0207, 30, require('ZC_REQ_ADD_FRIENDS'))
d:add(0x0171, -1, require('ZC_REQ_ALLY_GUILD'))
d:add(0x00e5, 23, require('ZC_REQ_EXCHANGE_ITEM'))
d:add(0x01f4, -1, require('ZC_REQ_EXCHANGE_ITEM2'))
d:add(0x00fe, 10, require('ZC_REQ_JOIN_GROUP'))
d:add(0x00ac, 59, require('ZC_REQ_TAKEOFF_EQUIP_ACK'))
d:add(0x00aa, 39, require('ZC_REQ_WEAR_EQUIP_ACK'))
d:add(0x00b3, 30, require('ZC_RESTART_ACK'))
d:add(0x0148, 4, require('ZC_RESURRECTION'))
d:add(0x00e1, -1, require('ZC_ROLE_CHANGE'))
d:add(0x00d7, -1, require('ZC_ROOM_NEWENTRY'))
d:add(0x00c4, 26, require('ZC_SELECT_DEALTYPE'))
d:add(0x00d1, 9, require('ZC_SETTING_WHISPER_PC'))
d:add(0x00d2, 15, require('ZC_SETTING_WHISPER_STATE'))
d:add(0x01b3, -1, require('ZC_SHOW_IMAGE2'))
d:add(0x010f, 4, require('ZC_SKILLINFO_LIST'))
d:add(0x0120, -1, require('ZC_SKILL_DISAPPEAR'))
d:add(0x011f, -1, require('ZC_SKILL_ENTRY'))
d:add(0x01e1, 19, require('ZC_SPIRITS2'))
d:add(0x0119, -1, require('ZC_STATE_CHANGE'))
d:add(0x00bd, 3, require('ZC_STATUS'))
d:add(0x00be, 19, require('ZC_STATUS_CHANGE'))
d:add(0x0088, 60, require('ZC_STOPMOVE'))
d:add(0x0296, 14, require('ZC_STORE_EQUIPMENT_ITEMLIST2'))
d:add(0x00a5, 2, require('ZC_STORE_NORMAL_ITEMLIST'))
d:add(0x01f0, -1, require('ZC_STORE_NORMAL_ITEMLIST2'))
d:add(0x0224, 6, require('ZC_TAEKWON_POINT'))
d:add(0x01f2, -1, require('ZC_UPDATE_CHARSTAT2'))
d:add(0x013e, 30, require('ZC_USESKILL_ACK'))
d:add(0x00a8, 10, require('ZC_USE_ITEM_ACK'))
d:add(0x011a, 58, require('ZC_USE_SKILL'))
d:add(0x00b5, 71, require('ZC_WAIT_DIALOG'))
d:add(0x011c, 3, require('ZC_WARPLIST'))

return d