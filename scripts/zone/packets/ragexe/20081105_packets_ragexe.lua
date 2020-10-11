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

d:add(0x00e6, 39, require('CZ_ACK_EXCHANGE_ITEM'))
d:add(0x00c5, -1, require('CZ_ACK_SELECT_DEALTYPE'))
d:add(0x00e8, -1, require('CZ_ADD_EXCHANGE_ITEM'))
d:add(0x0218, 30, require('CZ_ALCHEMIST_RANK'))
d:add(0x0172, 30, require('CZ_ALLY_GUILD'))
d:add(0x0217, 10, require('CZ_BLACKSMITH_RANK'))
d:add(0x00ed, -1, require('CZ_CANCEL_EXCHANGE_ITEM'))
d:add(0x0118, -1, require('CZ_CANCEL_LOCKON'))
d:add(0x00de, 16, require('CZ_CHANGE_CHATROOM'))
d:add(0x0361, 6, require('CZ_CHANGE_DIRECTION2'))
d:add(0x019d, 8, require('CZ_CHANGE_EFFECTSTATE'))
d:add(0x0102, 8, require('CZ_CHANGE_GROUPEXPOPTION'))
d:add(0x00b8, -1, require('CZ_CHOOSE_MENU'))
d:add(0x01a1, 2, require('CZ_COMMAND_PET'))
d:add(0x00eb, -1, require('CZ_CONCLUDE_EXCHANGE_ITEM'))
d:add(0x0090, -1, require('CZ_CONTACTNPC'))
d:add(0x00d5, -1, require('CZ_CREATE_CHATROOM'))
d:add(0x00cc, -1, require('CZ_DISCONNECT_CHARACTER'))
d:add(0x01e7, 8, require('CZ_DORIDORI'))
d:add(0x0436, 60, require('CZ_ENTER2'))
d:add(0x00ef, 14, require('CZ_EXEC_EXCHANGE_ITEM'))
d:add(0x00e3, 15, require('CZ_EXIT_ROOM'))
d:add(0x017e, 67, require('CZ_GUILD_CHAT'))
d:add(0x016e, 6, require('CZ_GUILD_NOTICE'))
d:add(0x01d5, 2, require('CZ_INPUT_EDITDLGSTR'))
d:add(0x02f6, 10, require('CZ_IRMAIL_LIST'))
d:add(0x013f, 29, require('CZ_ITEM_CREATE'))
d:add(0x0362, 5, require('CZ_ITEM_PICKUP2'))
d:add(0x016b, 43, require('CZ_JOIN_GUILD'))
d:add(0x00f9, -1, require('CZ_MAKE_GROUP'))
d:add(0x01e8, 8, require('CZ_MAKE_GROUP2'))
d:add(0x0140, 28, require('CZ_MOVETO_MAP'))
d:add(0x0126, 60, require('CZ_MOVE_ITEM_FROM_BODY_TO_CART'))
d:add(0x0364, -1, require('CZ_MOVE_ITEM_FROM_BODY_TO_STORE2'))
d:add(0x0129, -1, require('CZ_MOVE_ITEM_FROM_CART_TO_STORE'))
d:add(0x0365, 6, require('CZ_MOVE_ITEM_FROM_STORE_TO_BODY2'))
d:add(0x0128, 3, require('CZ_MOVE_ITEM_FROM_STORE_TO_CART'))
d:add(0x00c8, -1, require('CZ_PC_PURCHASE_ITEMLIST'))
d:add(0x0134, -1, require('CZ_PC_PURCHASE_ITEMLIST_FROMMC'))
d:add(0x00c9, 9, require('CZ_PC_SELL_ITEMLIST'))
d:add(0x01bc, -1, require('CZ_RECALL'))
d:add(0x01bd, 4, require('CZ_RECALL_GID'))
d:add(0x0161, 2, require('CZ_REG_CHANGE_GUILD_POSITIONINFO'))
d:add(0x011d, -1, require('CZ_REMEMBER_WARPPOINT'))
d:add(0x0368, -1, require('CZ_REQNAME2'))
d:add(0x0437, 282, require('CZ_REQUEST_ACT2'))
d:add(0x0233, 6, require('CZ_REQUEST_ACTNPC'))
d:add(0x035f, 30, require('CZ_REQUEST_MOVE2'))
d:add(0x0234, 20, require('CZ_REQUEST_MOVETOOWNER'))
d:add(0x0360, 14, require('CZ_REQUEST_TIME2'))
d:add(0x015b, -1, require('CZ_REQ_BAN_GUILD'))
d:add(0x0130, -1, require('CZ_REQ_BUY_FROMMC'))
d:add(0x012a, 54, require('CZ_REQ_CARTOFF'))
d:add(0x0155, 30, require('CZ_REQ_CHANGE_MEMBERPOS'))
d:add(0x012e, 6, require('CZ_REQ_CLOSESTORE'))
d:add(0x00bf, -1, require('CZ_REQ_EMOTION'))
d:add(0x00e4, 12, require('CZ_REQ_EXCHANGE_ITEM'))
d:add(0x0103, -1, require('CZ_REQ_EXPEL_GROUP_MEMBER'))
d:add(0x00e2, 6, require('CZ_REQ_EXPEL_MEMBER'))
d:add(0x0149, -1, require('CZ_REQ_GIVE_MANNER_POINT'))
d:add(0x017c, 2, require('CZ_REQ_ITEMCOMPOSITION'))
d:add(0x017a, 71, require('CZ_REQ_ITEMCOMPOSITION_LIST'))
d:add(0x01fd, 2, require('CZ_REQ_ITEMREPAIR'))
d:add(0x0100, 6, require('CZ_REQ_LEAVE_GROUP'))
d:add(0x01ae, -1, require('CZ_REQ_MAKINGARROW'))
d:add(0x00b9, 2, require('CZ_REQ_NEXT_SCRIPT'))
d:add(0x00ab, -1, require('CZ_REQ_TAKEOFF_EQUIP'))
d:add(0x00c1, 9, require('CZ_REQ_USER_COUNT'))
d:add(0x00b2, 11, require('CZ_RESTART'))
d:add(0x01ce, -1, require('CZ_SELECTAUTOSPELL'))
d:add(0x011b, 15, require('CZ_SELECT_WARPPOINT'))
d:add(0x00d0, 6, require('CZ_SETTING_WHISPER_STATE'))
d:add(0x01bb, -1, require('CZ_SHIFT'))
d:add(0x00bb, -1, require('CZ_STATUS_CHANGE'))
d:add(0x019f, 6, require('CZ_TRYCAPTURE_MONSTER'))
d:add(0x0439, 4, require('CZ_USE_ITEM2'))
d:add(0x0438, 4, require('CZ_USE_SKILL2'))
d:add(0x0366, -1, require('CZ_USE_SKILL_TOGROUND2'))
d:add(0x0367, -1, require('CZ_USE_SKILL_TOGROUND_WITHTALKBOX2'))
d:add(0x0096, -1, require('CZ_WHISPER'))
d:add(0x0073, 7, require('ZC_ACCEPT_ENTER'))
d:add(0x0083, 4, require('ZC_ACCEPT_QUIT'))
d:add(0x012c, -1, require('ZC_ACK_ADDITEM_TO_CART'))
d:add(0x00ea, 11, require('ZC_ACK_ADD_EXCHANGE_ITEM'))
d:add(0x015c, 6, require('ZC_ACK_BAN_GUILD'))
d:add(0x00d6, 6, require('ZC_ACK_CREATE_CHATROOM'))
d:add(0x017d, -1, require('ZC_ACK_ITEMCOMPOSITION'))
d:add(0x0179, 3, require('ZC_ACK_ITEMIDENTIFY'))
d:add(0x0188, -1, require('ZC_ACK_ITEMREFINING'))
d:add(0x01fe, -1, require('ZC_ACK_ITEMREPAIR'))
d:add(0x015a, -1, require('ZC_ACK_LEAVE_GUILD'))
d:add(0x0274, 3, require('ZC_ACK_MAIL_RETURN'))
d:add(0x00fa, -1, require('ZC_ACK_MAKE_GROUP'))
d:add(0x011e, -1, require('ZC_ACK_REMEMBER_WARPPOINT'))
d:add(0x018f, -1, require('ZC_ACK_REQMAKINGITEM'))
d:add(0x0195, -1, require('ZC_ACK_REQNAMEALL'))
d:add(0x0194, 20, require('ZC_ACK_REQNAME_BYGID'))
d:add(0x018b, 18, require('ZC_ACK_REQ_DISCONNECT'))
d:add(0x00fd, -1, require('ZC_ACK_REQ_JOIN_GROUP'))
d:add(0x0169, -1, require('ZC_ACK_REQ_JOIN_GUILD'))
d:add(0x0098, 16, require('ZC_ACK_WHISPER'))
d:add(0x013b, 6, require('ZC_ACTION_FAILURE'))
d:add(0x00e9, 10, require('ZC_ADD_EXCHANGE_ITEM'))
d:add(0x0209, -1, require('ZC_ADD_FRIENDS_LIST'))
d:add(0x01c5, 14, require('ZC_ADD_ITEM_TO_CART2'))
d:add(0x00f4, 2, require('ZC_ADD_ITEM_TO_STORE'))
d:add(0x01c4, 6, require('ZC_ADD_ITEM_TO_STORE2'))
d:add(0x0104, -1, require('ZC_ADD_MEMBER_TO_GROUP'))
d:add(0x01e9, -1, require('ZC_ADD_MEMBER_TO_GROUP2'))
d:add(0x0111, 10, require('ZC_ADD_SKILL'))
d:add(0x021c, -1, require('ZC_ALCHEMIST_POINT'))
d:add(0x021a, -1, require('ZC_ALCHEMIST_RANK'))
d:add(0x013a, 8, require('ZC_ATTACK_RANGE'))
d:add(0x01cd, -1, require('ZC_AUTOSPELLLIST'))
d:add(0x0163, 28, require('ZC_BAN_LIST'))
d:add(0x021b, 3, require('ZC_BLACKSMITH_POINT'))
d:add(0x0219, 5, require('ZC_BLACKSMITH_RANK'))
d:add(0x009a, -1, require('ZC_BROADCAST'))
d:add(0x01c3, -1, require('ZC_BROADCAST2'))
d:add(0x0122, 10, require('ZC_CART_EQUIPMENT_ITEMLIST'))
d:add(0x0297, -1, require('ZC_CART_EQUIPMENT_ITEMLIST2'))
d:add(0x0123, -1, require('ZC_CART_NORMAL_ITEMLIST'))
d:add(0x01ef, 24, require('ZC_CART_NORMAL_ITEMLIST2'))
d:add(0x0230, 10, require('ZC_CHANGESTATE_MER'))
d:add(0x01a4, -1, require('ZC_CHANGESTATE_PET'))
d:add(0x009c, 30, require('ZC_CHANGE_DIRECTION'))
d:add(0x00b6, 2, require('ZC_CLOSE_DIALOG'))
d:add(0x01d2, 10, require('ZC_COMBODELAY'))
d:add(0x0144, 53, require('ZC_COMPASS'))
d:add(0x00ec, 86, require('ZC_CONCLUDE_EXCHANGE_ITEM'))
d:add(0x01ea, -1, require('ZC_CONGRATULATION'))
d:add(0x0141, 57, require('ZC_COUPLESTATUS'))
d:add(0x0125, 4, require('ZC_DELETE_ITEM_FROM_CART'))
d:add(0x00f6, -1, require('ZC_DELETE_ITEM_FROM_STORE'))
d:add(0x00d8, 26, require('ZC_DESTROY_ROOM'))
d:add(0x0132, -1, require('ZC_DISAPPEAR_ENTRY'))
d:add(0x00db, 28, require('ZC_ENTER_ROOM'))
d:add(0x00a4, 10, require('ZC_EQUIPMENT_ITEMLIST'))
d:add(0x0295, 6, require('ZC_EQUIPMENT_ITEMLIST2'))
d:add(0x00f0, 8, require('ZC_EXEC_EXCHANGE_ITEM'))
d:add(0x022f, -1, require('ZC_FEED_MER'))
d:add(0x01a3, -1, require('ZC_FEED_PET'))
d:add(0x0201, -1, require('ZC_FRIENDS_LIST'))
d:add(0x0206, 44, require('ZC_FRIENDS_STATE'))
d:add(0x0101, -1, require('ZC_GROUPINFO_CHANGE'))
d:add(0x01b6, -1, require('ZC_GUILD_INFO2'))
d:add(0x016f, 26, require('ZC_GUILD_NOTICE'))
d:add(0x0162, 8, require('ZC_GUILD_SKILLINFO'))
d:add(0x0235, 59, require('ZC_HOSKILLINFO_LIST'))
d:add(0x02f5, 90, require('ZC_IRMAIL_NOTIFY'))
d:add(0x02f4, 2, require('ZC_IRMAIL_SEND_RES'))
d:add(0x0177, 8, require('ZC_ITEMIDENTIFY_LIST'))
d:add(0x00a1, 8, require('ZC_ITEM_DISAPPEAR'))
d:add(0x029a, -1, require('ZC_ITEM_PICKUP_ACK2'))
d:add(0x00af, 6, require('ZC_ITEM_THROW_ACK'))
d:add(0x0154, 4, require('ZC_MEMBERMGR_INFO'))
d:add(0x00dd, 26, require('ZC_MEMBER_EXIT'))
d:add(0x00dc, 5, require('ZC_MEMBER_NEWENTRY'))
d:add(0x018c, 4, require('ZC_MONSTER_INFO'))
d:add(0x0196, 21, require('ZC_MSG_STATE_CHANGE'))
d:add(0x010c, -1, require('ZC_MVP'))
d:add(0x010a, 36, require('ZC_MVP_GETTING_ITEM'))
d:add(0x014c, 3, require('ZC_MYGUILD_BASIC_INFO'))
d:add(0x00a3, -1, require('ZC_NORMAL_ITEMLIST'))
d:add(0x01ee, 10, require('ZC_NORMAL_ITEMLIST2'))
d:add(0x008a, -1, require('ZC_NOTIFY_ACT'))
d:add(0x02e1, -1, require('ZC_NOTIFY_ACT2'))
d:add(0x007a, -1, require('ZC_NOTIFY_ACTENTRY'))
d:add(0x0121, 3, require('ZC_NOTIFY_CARTITEM_COUNTINFO'))
d:add(0x008d, 79, require('ZC_NOTIFY_CHAT'))
d:add(0x0109, 6, require('ZC_NOTIFY_CHAT_PARTY'))
d:add(0x0117, 14, require('ZC_NOTIFY_GROUNDSKILL'))
d:add(0x0106, -1, require('ZC_NOTIFY_HP_TO_GROUPM'))
d:add(0x0075, 8, require('ZC_NOTIFY_INITCHAR'))
d:add(0x0199, -1, require('ZC_NOTIFY_MAPPROPERTY'))
d:add(0x0086, -1, require('ZC_NOTIFY_MOVE'))
d:add(0x01da, -1, require('ZC_NOTIFY_MOVEENTRY2'))
d:add(0x022c, -1, require('ZC_NOTIFY_MOVEENTRY3'))
d:add(0x02ec, -1, require('ZC_NOTIFY_MOVEENTRY4'))
d:add(0x0079, 30, require('ZC_NOTIFY_NEWENTRY'))
d:add(0x01d9, -1, require('ZC_NOTIFY_NEWENTRY2'))
d:add(0x008e, 5, require('ZC_NOTIFY_PLAYERCHAT'))
d:add(0x0107, 5, require('ZC_NOTIFY_POSITION_TO_GROUPM'))
d:add(0x0114, 10, require('ZC_NOTIFY_SKILL'))
d:add(0x01de, 22, require('ZC_NOTIFY_SKILL2'))
d:add(0x0078, 7, require('ZC_NOTIFY_STANDENTRY'))
d:add(0x01d8, 30, require('ZC_NOTIFY_STANDENTRY2'))
d:add(0x022a, -1, require('ZC_NOTIFY_STANDENTRY3'))
d:add(0x02ee, 14, require('ZC_NOTIFY_STANDENTRY4'))
d:add(0x007f, -1, require('ZC_NOTIFY_TIME'))
d:add(0x0077, -1, require('ZC_NOTIFY_UPDATEPLAYER'))
d:add(0x0080, -1, require('ZC_NOTIFY_VANISH'))
d:add(0x0091, 22, require('ZC_NPCACK_MAPMOVE'))
d:add(0x0092, -1, require('ZC_NPCACK_SERVERMOVE'))
d:add(0x0142, 3, require('ZC_OPEN_EDITDLG'))
d:add(0x01d4, 2, require('ZC_OPEN_EDITDLGSTR'))
d:add(0x01ab, 3, require('ZC_PAR_CHANGE_USER'))
d:add(0x0287, -1, require('ZC_PC_CASH_POINT_ITEMLIST'))
d:add(0x0133, -1, require('ZC_PC_PURCHASE_ITEMLIST_FROMMC'))
d:add(0x0136, 7, require('ZC_PC_PURCHASE_MYITEMLIST'))
d:add(0x00ca, -1, require('ZC_PC_PURCHASE_RESULT'))
d:add(0x0135, 3, require('ZC_PC_PURCHASE_RESULT_FROMMC'))
d:add(0x01a6, 58, require('ZC_PETEGG_LIST'))
d:add(0x01aa, 29, require('ZC_PET_ACT'))
d:add(0x0166, 6, require('ZC_POSITION_ID_NAME_INFO'))
d:add(0x0160, 2, require('ZC_POSITION_INFO'))
d:add(0x022e, -1, require('ZC_PROPERTY_HOMUN'))
d:add(0x01a2, 282, require('ZC_PROPERTY_PET'))
d:add(0x013d, -1, require('ZC_RECOVERY'))
d:add(0x00da, -1, require('ZC_REFUSE_ENTER_ROOM'))
d:add(0x0207, 5, require('ZC_REQ_ADD_FRIENDS'))
d:add(0x00fe, 5, require('ZC_REQ_JOIN_GROUP'))
d:add(0x016a, 102, require('ZC_REQ_JOIN_GUILD'))
d:add(0x023a, -1, require('ZC_REQ_STORE_PASSWORD'))
d:add(0x00aa, 4, require('ZC_REQ_WEAR_EQUIP_ACK'))
d:add(0x00b3, 11, require('ZC_RESTART_ACK'))
d:add(0x023c, 6, require('ZC_RESULT_STORE_PASSWORD'))
d:add(0x00e1, 28, require('ZC_ROLE_CHANGE'))
d:add(0x00b4, 32, require('ZC_SAY_DIALOG'))
d:add(0x00c4, -1, require('ZC_SELECT_DEALTYPE'))
d:add(0x00d1, 23, require('ZC_SETTING_WHISPER_PC'))
d:add(0x00d2, 6, require('ZC_SETTING_WHISPER_STATE'))
d:add(0x01b3, -1, require('ZC_SHOW_IMAGE2'))
d:add(0x010e, 30, require('ZC_SKILLINFO_UPDATE'))
d:add(0x011f, 2, require('ZC_SKILL_ENTRY'))
d:add(0x01c9, -1, require('ZC_SKILL_ENTRY2'))
d:add(0x01d0, -1, require('ZC_SPIRITS'))
d:add(0x01e1, 3, require('ZC_SPIRITS2'))
d:add(0x00c3, 10, require('ZC_SPRITE_CHANGE'))
d:add(0x0229, 2, require('ZC_STATE_CHANGE3'))
d:add(0x00bd, 6, require('ZC_STATUS'))
d:add(0x0088, 2, require('ZC_STOPMOVE'))
d:add(0x0131, -1, require('ZC_STORE_ENTRY'))
d:add(0x00a5, 42, require('ZC_STORE_NORMAL_ITEMLIST'))
d:add(0x01f0, 3, require('ZC_STORE_NORMAL_ITEMLIST2'))
d:add(0x0224, -1, require('ZC_TAEKWON_POINT'))
d:add(0x01a0, -1, require('ZC_TRYCAPTURE_MONSTER'))
d:add(0x016d, 10, require('ZC_UPDATE_CHARSTAT'))
d:add(0x01f2, -1, require('ZC_UPDATE_CHARSTAT2'))
d:add(0x016c, 29, require('ZC_UPDATE_GDID'))
d:add(0x013e, 6, require('ZC_USESKILL_ACK'))
d:add(0x01c8, -1, require('ZC_USE_ITEM_ACK2'))
d:add(0x011a, 7, require('ZC_USE_SKILL'))
d:add(0x00b5, 4, require('ZC_WAIT_DIALOG'))
d:add(0x011c, 26, require('ZC_WARPLIST'))
d:add(0x0097, -1, require('ZC_WHISPER'))

return d