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

#include "TransmittedPackets.hpp"
#include "Server/Char/Session/CharSession.hpp"
#include "Utility/Utility.hpp"

using namespace Horizon::Char;

/**
 * HC_ACCEPT_DELETECHAR
 */
void HC_ACCEPT_DELETECHAR::deliver() {}
ByteBuffer &HC_ACCEPT_DELETECHAR::serialize()
{
	return buf();
}
/**
 * HC_ACCEPT_ENTER
 */
void HC_ACCEPT_ENTER::deliver() {}
ByteBuffer &HC_ACCEPT_ENTER::serialize()
{
	return buf();
}
/**
 * HC_ACCEPT_MAKECHAR
 */
void HC_ACCEPT_MAKECHAR::deliver() {}
ByteBuffer &HC_ACCEPT_MAKECHAR::serialize()
{
	return buf();
}
/**
 * HC_BLOCK_CHARACTER
 */
void HC_BLOCK_CHARACTER::deliver() {}
ByteBuffer &HC_BLOCK_CHARACTER::serialize()
{
	return buf();
}
/**
 * HC_NOTIFY_ZONESVR
 */
void HC_NOTIFY_ZONESVR::deliver() {}
ByteBuffer &HC_NOTIFY_ZONESVR::serialize()
{
	return buf();
}
/**
 * HC_REFUSE_DELETECHAR
 */
void HC_REFUSE_DELETECHAR::deliver() {}
ByteBuffer &HC_REFUSE_DELETECHAR::serialize()
{
	return buf();
}
/**
 * HC_REFUSE_ENTER
 */
void HC_REFUSE_ENTER::deliver() {}
ByteBuffer &HC_REFUSE_ENTER::serialize()
{
	return buf();
}
/**
 * HC_REFUSE_MAKECHAR
 */
void HC_REFUSE_MAKECHAR::deliver() {}
ByteBuffer &HC_REFUSE_MAKECHAR::serialize()
{
	return buf();
}
/**
 * HC_REQUEST_CHARACTER_PASSWORD
 */
void HC_REQUEST_CHARACTER_PASSWORD::deliver() {}
ByteBuffer &HC_REQUEST_CHARACTER_PASSWORD::serialize()
{
	return buf();
}
/**
 * HC_ACK_CHANGE_CHARNAME
 */
void HC_ACK_CHANGE_CHARNAME::deliver() {}
ByteBuffer &HC_ACK_CHANGE_CHARNAME::serialize()
{
	return buf();
}
/**
 * HC_ACK_IS_VALID_CHARNAME
 */
void HC_ACK_IS_VALID_CHARNAME::deliver() {}
ByteBuffer &HC_ACK_IS_VALID_CHARNAME::serialize()
{
	return buf();
}
/**
 * HC_CHARNOTBEENSELECTED
 */
void HC_CHARNOTBEENSELECTED::deliver() {}
ByteBuffer &HC_CHARNOTBEENSELECTED::serialize()
{
	return buf();
}
/**
 * HC_REFUSE_SELECTCHAR
 */
void HC_REFUSE_SELECTCHAR::deliver() {}
ByteBuffer &HC_REFUSE_SELECTCHAR::serialize()
{
	return buf();
}
/**
 * HC_CHARACTER_LIST
 */
void HC_CHARACTER_LIST::deliver() {}
ByteBuffer &HC_CHARACTER_LIST::serialize()
{
	return buf();
}
/**
 * HC_CHECKBOT
 */
void HC_CHECKBOT::deliver() {}
ByteBuffer &HC_CHECKBOT::serialize()
{
	return buf();
}
/**
 * HC_CHECKBOT_RESULT
 */
void HC_CHECKBOT_RESULT::deliver() {}
ByteBuffer &HC_CHECKBOT_RESULT::serialize()
{
	return buf();
}
/**
 * HC_DELETE_CHAR3
 */
void HC_DELETE_CHAR3::deliver() {}
ByteBuffer &HC_DELETE_CHAR3::serialize()
{
	return buf();
}
/**
 * HC_DELETE_CHAR3_RESERVED
 */
void HC_DELETE_CHAR3_RESERVED::deliver() {}
ByteBuffer &HC_DELETE_CHAR3_RESERVED::serialize()
{
	return buf();
}
/**
 * HC_NOTIFY_ACCESSIBLE_MAPNAME
 */
void HC_NOTIFY_ACCESSIBLE_MAPNAME::deliver() {}
ByteBuffer &HC_NOTIFY_ACCESSIBLE_MAPNAME::serialize()
{
	return buf();
}
/**
 * HC_DELETE_CHAR3_CANCEL
 */
void HC_DELETE_CHAR3_CANCEL::deliver() {}
ByteBuffer &HC_DELETE_CHAR3_CANCEL::serialize()
{
	return buf();
}
/**
 * HC_ACCEPT_ENTER2
 */
void HC_ACCEPT_ENTER2::deliver() {}
ByteBuffer &HC_ACCEPT_ENTER2::serialize()
{
	return buf();
}
/**
 * HC_WAITING_LOGIN
 */
void HC_WAITING_LOGIN::deliver() {}
ByteBuffer &HC_WAITING_LOGIN::serialize()
{
	return buf();
}
/**
 * HC_UPDATE_CHARINFO
 */
void HC_UPDATE_CHARINFO::deliver() {}
ByteBuffer &HC_UPDATE_CHARINFO::serialize()
{
	return buf();
}
/**
 * HC_SECOND_PASSWD_REQ
 */
void HC_SECOND_PASSWD_REQ::deliver() {}
ByteBuffer &HC_SECOND_PASSWD_REQ::serialize()
{
	return buf();
}
/**
 * HC_EDIT_SECOND_PASSWD
 */
void HC_EDIT_SECOND_PASSWD::deliver() {}
ByteBuffer &HC_EDIT_SECOND_PASSWD::serialize()
{
	return buf();
}
/**
 * HC_MAKE_SECOND_PASSWD
 */
void HC_MAKE_SECOND_PASSWD::deliver() {}
ByteBuffer &HC_MAKE_SECOND_PASSWD::serialize()
{
	return buf();
}
/**
 * HC_NOT_AVAILABLE_SECOND_PASSWD
 */
void HC_NOT_AVAILABLE_SECOND_PASSWD::deliver() {}
ByteBuffer &HC_NOT_AVAILABLE_SECOND_PASSWD::serialize()
{
	return buf();
}
/**
 * HC_SECOND_PASSWD_LOGIN
 */
void HC_SECOND_PASSWD_LOGIN::deliver() {}
ByteBuffer &HC_SECOND_PASSWD_LOGIN::serialize()
{
	return buf();
}
/**
 * HC_DELETE_SECOND_PASSWD
 */
void HC_DELETE_SECOND_PASSWD::deliver() {}
ByteBuffer &HC_DELETE_SECOND_PASSWD::serialize()
{
	return buf();
}
/**
 * HC_AVAILABLE_SECOND_PASSWD
 */
void HC_AVAILABLE_SECOND_PASSWD::deliver() {}
ByteBuffer &HC_AVAILABLE_SECOND_PASSWD::serialize()
{
	return buf();
}
/**
 * HC_ACK_CHANGE_CHARACTER_SLOT
 */
void HC_ACK_CHANGE_CHARACTER_SLOT::deliver() {}
ByteBuffer &HC_ACK_CHANGE_CHARACTER_SLOT::serialize()
{
	return buf();
}
/**
 * HC_ACK_CHARINFO_PER_PAGE
 */
void HC_ACK_CHARINFO_PER_PAGE::deliver() {}
ByteBuffer &HC_ACK_CHARINFO_PER_PAGE::serialize()
{
	return buf();
}
/**
 * HC_QUEUE_ORDER
 */
void HC_QUEUE_ORDER::deliver() {}
ByteBuffer &HC_QUEUE_ORDER::serialize()
{
	return buf();
}
/**
 * HC_CHARLIST_NOTIFY
 */
void HC_CHARLIST_NOTIFY::deliver() {}
ByteBuffer &HC_CHARLIST_NOTIFY::serialize()
{
	return buf();
}
/**
 * HC_SECRETSCAN_DATA
 */
void HC_SECRETSCAN_DATA::deliver() {}
ByteBuffer &HC_SECRETSCAN_DATA::serialize()
{
	return buf();
}
