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

#ifndef HORIZON_ZONE_RAGEXE_20170726_PACKETS_HPP
#define HORIZON_ZONE_RAGEXE_20170726_PACKETS_HPP

namespace Horizon
{
namespace Zone
{
namespace Ragexe20170726
{
enum packets
{
	CZ_ACK_STORE_PASSWORD = 0x08a7,
	CZ_ADD_FRIENDS = 0x091d,
	CZ_CHANGE_DIRECTION = 0x0952,
	CZ_COMMAND_MER = 0x022d,
	CZ_ENTER = 0x0366,
	CZ_GANGSI_RANK = 0x0881,
	CZ_ITEMLISTWIN_RES = 0x07e4,
	CZ_ITEM_PICKUP = 0x08ab,
	CZ_ITEM_THROW = 0x0943,
	CZ_JOIN_BATTLE_FIELD = 0x08a3,
	CZ_MOVE_ITEM_FROM_BODY_TO_STORE = 0x0364,
	CZ_MOVE_ITEM_FROM_STORE_TO_BODY = 0x094f,
	CZ_PARTY_BOOKING_REQ_REGISTER = 0x0954,
	CZ_PARTY_JOIN_REQ = 0x0438,
	CZ_REQNAME = 0x08aa,
	CZ_REQNAME2 = 0x0368,
	CZ_REQNAME_BYGID = 0x0921,
	CZ_REQUEST_ACT = 0x0878,
	CZ_REQUEST_MOVE = 0x088e,
	CZ_REQUEST_TIME = 0x08ac,
	CZ_REQ_CLICK_TO_BUYING_STORE = 0x0873,
	CZ_REQ_CLOSE_BUYING_STORE = 0x0838,
	CZ_REQ_OPEN_BUYING_STORE = 0x0363,
	CZ_REQ_TRADE_BUYING_STORE = 0x0923,
	CZ_SEARCH_STORE_INFO = 0x0963,
	CZ_SEARCH_STORE_INFO_NEXT_PAGE = 0x0888,
	CZ_SSILIST_ITEM_CLICK = 0x091e,
	CZ_USE_SKILL = 0x0369,
	CZ_USE_SKILL_TOGROUND = 0x0950,
	CZ_USE_SKILL_TOGROUND_WITHTALKBOX = 0x095a,
	ZC_PRNPC_STATE = 0x091b,
	ZC_REFINE_STATUS = 0x0ada,
};
}
}
}
#endif /* HORIZON_ZONE_RAGEXE_20170726_PACKETS_HPP */