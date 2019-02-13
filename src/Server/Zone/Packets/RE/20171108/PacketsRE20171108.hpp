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

#ifndef HORIZON_ZONE_RE_20171108_PACKETS_HPP
#define HORIZON_ZONE_RE_20171108_PACKETS_HPP

namespace Horizon
{
namespace Zone
{
namespace RE20171108
{
enum packets
{
	CZ_ACK_STORE_PASSWORD = 0x0815,
	CZ_ADD_FRIENDS = 0x0878,
	CZ_CHANGE_DIRECTION = 0x091f,
	CZ_COMMAND_MER = 0x08a9,
	CZ_ENTER = 0x0949,
	CZ_GANGSI_RANK = 0x0896,
	CZ_ITEMLISTWIN_RES = 0x0884,
	CZ_ITEM_PICKUP = 0x0945,
	CZ_ITEM_THROW = 0x0965,
	CZ_JOIN_BATTLE_FIELD = 0x0947,
	CZ_MOVE_ITEM_FROM_BODY_TO_STORE = 0x0941,
	CZ_MOVE_ITEM_FROM_STORE_TO_BODY = 0x095a,
	CZ_PARTY_BOOKING_REQ_REGISTER = 0x0958,
	CZ_PARTY_JOIN_REQ = 0x094e,
	CZ_REQNAME = 0x08ad,
	CZ_REQNAME_BYGID = 0x07e4,
	CZ_REQUEST_ACT = 0x0963,
	CZ_REQUEST_MOVE = 0x0863,
	CZ_REQUEST_TIME = 0x0202,
	CZ_REQ_CLICK_TO_BUYING_STORE = 0x0940,
	CZ_REQ_CLOSE_BUYING_STORE = 0x091d,
	CZ_REQ_OPEN_BUYING_STORE = 0x0838,
	CZ_REQ_TRADE_BUYING_STORE = 0x087e,
	CZ_SEARCH_STORE_INFO = 0x0897,
	CZ_SEARCH_STORE_INFO_NEXT_PAGE = 0x0361,
	CZ_SSILIST_ITEM_CLICK = 0x085d,
	CZ_USE_SKILL = 0x08a2,
	CZ_USE_SKILL_TOGROUND = 0x0967,
	CZ_USE_SKILL_TOGROUND_WITHTALKBOX = 0x0819,
};
}
}
}
#endif /* HORIZON_ZONE_RE_20171108_PACKETS_HPP */