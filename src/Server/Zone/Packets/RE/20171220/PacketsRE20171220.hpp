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

#ifndef HORIZON_ZONE_RE_20171220_PACKETS_HPP
#define HORIZON_ZONE_RE_20171220_PACKETS_HPP

namespace Horizon
{
namespace Zone
{
namespace RE20171220
{
enum packets
{
	CZ_ACK_STORE_PASSWORD = 0x0899,
	CZ_ADD_FRIENDS = 0x0957,
	CZ_CHANGE_DIRECTION = 0x0933,
	CZ_COMMAND_MER = 0x0951,
	CZ_ENTER = 0x0281,
	CZ_GANGSI_RANK = 0x0946,
	CZ_ITEMLISTWIN_RES = 0x0885,
	CZ_ITEM_PICKUP = 0x091b,
	CZ_ITEM_THROW = 0x0929,
	CZ_JOIN_BATTLE_FIELD = 0x094e,
	CZ_MOVE_ITEM_FROM_BODY_TO_STORE = 0x0924,
	CZ_MOVE_ITEM_FROM_STORE_TO_BODY = 0x0366,
	CZ_PARTY_BOOKING_REQ_REGISTER = 0x0437,
	CZ_PARTY_JOIN_REQ = 0x0964,
	CZ_REQNAME = 0x0873,
	CZ_REQNAME_BYGID = 0x091e,
	CZ_REQUEST_ACT = 0x093e,
	CZ_REQUEST_MOVE = 0x089e,
	CZ_REQUEST_TIME = 0x0882,
	CZ_REQ_CLICK_TO_BUYING_STORE = 0x0941,
	CZ_REQ_CLOSE_BUYING_STORE = 0x08a7,
	CZ_REQ_OPEN_BUYING_STORE = 0x085e,
	CZ_REQ_TRADE_BUYING_STORE = 0x0861,
	CZ_SEARCH_STORE_INFO = 0x0369,
	CZ_SEARCH_STORE_INFO_NEXT_PAGE = 0x0436,
	CZ_SSILIST_ITEM_CLICK = 0x0880,
	CZ_USE_SKILL = 0x0872,
	CZ_USE_SKILL_TOGROUND = 0x088c,
	CZ_USE_SKILL_TOGROUND_WITHTALKBOX = 0x0960,
};
}
}
}
#endif /* HORIZON_ZONE_RE_20171220_PACKETS_HPP */