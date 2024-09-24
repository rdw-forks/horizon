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
 * This is proprietary software. Unauthorized copying,
 * distribution, or modification of this file, via any
 * medium, is strictly prohibited. All rights reserved.
 **************************************************/

#include "HandledPackets.hpp"
#include "Server/Char/Session/CharSession.hpp"

using namespace Horizon::Char;

/**
 * CH_DELETE_CHAR
 */
void CH_DELETE_CHAR::handle(ByteBuffer&& buf)
{
	deserialize(buf);
	get_session()->clif()->character_delete_email(_character_id, _email);
}

void CH_DELETE_CHAR::deserialize(ByteBuffer& buf)
{
	buf >> _packet_id;
	buf >> _character_id;
	buf.read(_email, CLIENT_MAX_EMAIL_LENGTH);
}
/**
 * CH_DELETE_CHAR2
 */
void CH_DELETE_CHAR2::handle(ByteBuffer &&buf) 
{
	deserialize(buf);
	get_session()->clif()->character_delete_email(_character_id, _email);
}
void CH_DELETE_CHAR2::deserialize(ByteBuffer &buf) 
{
	buf >> _packet_id;
	buf >> _character_id;
	buf.read(_email, CLIENT_MAX_EMAIL_LENGTH);
}
/**
 * CH_ENTER
 */
void CH_ENTER::handle(ByteBuffer&& buf)
{
	deserialize(buf);
	get_session()->clif()->authorize_new_connection(_account_id, _auth_code, _account_level, _gender);
}

void CH_ENTER::deserialize(ByteBuffer& buf)
{
	buf >> _packet_id;
	buf >> _account_id;
	buf >> _auth_code;
	buf >> _account_level;
	buf >> _unknown;
	buf >> _gender;
}
/**
 * CH_MAKE_CHAR
 */
void CH_MAKE_CHAR::handle(ByteBuffer&& buf)
{
	deserialize(buf);

#if PACKET_VERSION >= 20151001
	get_session()->clif()->make_new_character(_name, _slot, _hair_color, _hair_style, _job_id, _gender);
#elif PACKET_VERSION >= 20120307
	get_session()->clif()->make_new_character(_name, _slot, _hair_color, _hair_style);
#endif
}

void CH_MAKE_CHAR::deserialize(ByteBuffer& buf)
{
	buf >> _packet_id;
	buf.read(_name, MAX_UNIT_NAME_LENGTH);
	buf >> _slot;
	buf >> _hair_color;
	buf >> _hair_style;
#if PACKET_VERSION >= 20151001
	buf >> _job_id;
	buf.read(_unknown_bytes, sizeof(short));
	buf >> _gender;
#endif
}
/**
 * CH_SELECT_CHAR
 */
void CH_SELECT_CHAR::handle(ByteBuffer&& buf)
{
	deserialize(buf);
	get_session()->clif()->select_character(_slot);
}

void CH_SELECT_CHAR::deserialize(ByteBuffer& buf)
{
	buf >> _packet_id;
	buf >> _slot;
}
/**
 * CH_UNKNOWN_PING
 */
void CH_UNKNOWN_PING::handle(ByteBuffer&& buf)
{
	deserialize(buf);
	get_session()->clif()->update_session(_account_id);
}

void CH_UNKNOWN_PING::deserialize(ByteBuffer& buf)
{
	buf >> _packet_id;
	buf >> _account_id;
}
/**
 * CH_REQ_CHANGE_CHARNAME
 */
void CH_REQ_CHANGE_CHARNAME::handle(ByteBuffer &&buf) {}
void CH_REQ_CHANGE_CHARNAME::deserialize(ByteBuffer &buf) {}
/**
 * CH_REQ_IS_VALID_CHARNAME
 */
void CH_REQ_IS_VALID_CHARNAME::handle(ByteBuffer &&buf) {}
void CH_REQ_IS_VALID_CHARNAME::deserialize(ByteBuffer &buf) {}
/**
 * CH_SELECT_CHAR_GOINGTOBEUSED
 */
void CH_SELECT_CHAR_GOINGTOBEUSED::handle(ByteBuffer &&buf) {}
void CH_SELECT_CHAR_GOINGTOBEUSED::deserialize(ByteBuffer &buf) {}
/**
 * CH_ENTER2
 */
void CH_ENTER2::handle(ByteBuffer &&buf) {}
void CH_ENTER2::deserialize(ByteBuffer &buf) {}
/**
 * CH_CHECKBOT
 */
void CH_CHECKBOT::handle(ByteBuffer &&buf) {}
void CH_CHECKBOT::deserialize(ByteBuffer &buf) {}
/**
 * CH_ENTER_CHECKBOT
 */
void CH_ENTER_CHECKBOT::handle(ByteBuffer &&buf) {}
void CH_ENTER_CHECKBOT::deserialize(ByteBuffer &buf) {}
/**
 * CH_DELETE_CHAR3
 */
void CH_DELETE_CHAR3::handle(ByteBuffer&& buf)
{
	deserialize(buf);
	get_session()->clif()->character_delete_birthdate(_character_id, _birthdate);
}

void CH_DELETE_CHAR3::deserialize(ByteBuffer& buf)
{
	buf >> _packet_id;
	buf >> _character_id;
	buf.read(_birthdate, CLIENT_BIRTHDATE_STRING_LENGTH);
}
/**
 * CH_DELETE_CHAR3_CANCEL
 */
void CH_DELETE_CHAR3_CANCEL::handle(ByteBuffer&& buf)
{
	deserialize(buf);
	get_session()->clif()->character_delete_cancel(_character_id);
}

void CH_DELETE_CHAR3_CANCEL::deserialize(ByteBuffer& buf)
{
	buf >> _packet_id;
	buf >> _character_id;
}
/**
 * CH_DELETE_CHAR3_RESERVED
 */
void CH_DELETE_CHAR3_RESERVED::handle(ByteBuffer&& buf)
{
	deserialize(buf);
	get_session()->clif()->character_delete_reserve(_character_id);
}

void CH_DELETE_CHAR3_RESERVED::deserialize(ByteBuffer& buf)
{
	buf >> _packet_id;
	buf >> _character_id;
}
/**
 * CH_SELECT_ACCESSIBLE_MAPNAME
 */
void CH_SELECT_ACCESSIBLE_MAPNAME::handle(ByteBuffer &&buf) {}
void CH_SELECT_ACCESSIBLE_MAPNAME::deserialize(ByteBuffer &buf) {}
/**
 * CH_ACK_CHANGE_CHARACTERNAME
 */
void CH_ACK_CHANGE_CHARACTERNAME::handle(ByteBuffer &&buf) {}
void CH_ACK_CHANGE_CHARACTERNAME::deserialize(ByteBuffer &buf) {}
/**
 * CH_REQ_CHANGE_CHARACTERNAME
 */
void CH_REQ_CHANGE_CHARACTERNAME::handle(ByteBuffer &&buf) {}
void CH_REQ_CHANGE_CHARACTERNAME::deserialize(ByteBuffer &buf) {}
/**
 * CH_REQ_CHANGE_CHARACTER_SLOT
 */
void CH_REQ_CHANGE_CHARACTER_SLOT::handle(ByteBuffer &&buf) {}
void CH_REQ_CHANGE_CHARACTER_SLOT::deserialize(ByteBuffer &buf) {}
/**
 * CH_WAITING_LOGIN
 */
void CH_WAITING_LOGIN::handle(ByteBuffer &&buf) {}
void CH_WAITING_LOGIN::deserialize(ByteBuffer &buf) {}
/**
 * CH_AVAILABLE_SECOND_PASSWD
 */
void CH_AVAILABLE_SECOND_PASSWD::handle(ByteBuffer &&buf) {}
void CH_AVAILABLE_SECOND_PASSWD::deserialize(ByteBuffer &buf) {}
/**
 * CH_DELETE_SECOND_PASSWD
 */
void CH_DELETE_SECOND_PASSWD::handle(ByteBuffer &&buf) {}
void CH_DELETE_SECOND_PASSWD::deserialize(ByteBuffer &buf) {}
/**
 * CH_EDIT_SECOND_PASSWD
 */
void CH_EDIT_SECOND_PASSWD::handle(ByteBuffer&& buf)
{
	deserialize(buf);
	get_session()->clif()->pincode_change(_account_id, _old_pin, _new_pin);
}

void CH_EDIT_SECOND_PASSWD::deserialize(ByteBuffer& buf)
{
	buf >> _packet_id;
	buf >> _account_id;
	buf.read(_old_pin, MAX_PINCODE_STRING_LENGTH - 1);
	buf.read(_new_pin, MAX_PINCODE_STRING_LENGTH - 1);
}
/**
 * CH_MAKE_SECOND_PASSWD
 */
void CH_MAKE_SECOND_PASSWD::handle(ByteBuffer&& buf)
{
	deserialize(buf);
	get_session()->clif()->pincode_create(_account_id, _new_pin);
}

void CH_MAKE_SECOND_PASSWD::deserialize(ByteBuffer& buf)
{
	memset(_new_pin, '\0', MAX_PINCODE_STRING_LENGTH);

	buf >> _packet_id;
	buf >> _account_id;
	buf.read(_new_pin, MAX_PINCODE_STRING_LENGTH - 1);
}
/**
 * CH_NOT_AVAILABLE_SECOND_PASSWD
 */
void CH_NOT_AVAILABLE_SECOND_PASSWD::handle(ByteBuffer &&buf) {}
void CH_NOT_AVAILABLE_SECOND_PASSWD::deserialize(ByteBuffer &buf) {}
/**
 * CH_SECOND_PASSWD_ACK
 */
void CH_SECOND_PASSWD_ACK::handle(ByteBuffer&& buf)
{
	deserialize(buf);
	get_session()->clif()->pincode_verify(_account_id, _pincode);
}

void CH_SECOND_PASSWD_ACK::deserialize(ByteBuffer& buf)
{
	buf >> _packet_id;
	buf >> _account_id;
	buf.read(_pincode, MAX_PINCODE_STRING_LENGTH - 1);
}
/**
 * CH_MAKE_CHAR_NOT_STATS
 */
void CH_MAKE_CHAR_NOT_STATS::handle(ByteBuffer &&buf) {}
void CH_MAKE_CHAR_NOT_STATS::deserialize(ByteBuffer &buf) {}
/**
 * CH_DELETE_CHAR3_EXT
 */
void CH_DELETE_CHAR3_EXT::handle(ByteBuffer &&buf) {}
void CH_DELETE_CHAR3_EXT::deserialize(ByteBuffer &buf) {}
/**
 * CH_REQ_CHARINFO_PER_PAGE
 */
void CH_REQ_CHARINFO_PER_PAGE::handle(ByteBuffer &&buf) {}
void CH_REQ_CHARINFO_PER_PAGE::deserialize(ByteBuffer &buf) {}
/**
 * CH_CHARLIST_REQ
 */
void CH_CHARLIST_REQ::handle(ByteBuffer &&buf) {}
void CH_CHARLIST_REQ::deserialize(ByteBuffer &buf) {}
