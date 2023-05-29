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
#include "Server/Auth/Session/AuthSession.hpp"
#include "Utility/Utility.hpp"

using namespace Horizon::Auth;

/**
 * AC_ACCEPT_LOGIN
 */
void AC_ACCEPT_LOGIN::deliver() {}
ByteBuffer &AC_ACCEPT_LOGIN::serialize()
{
	return buf();
}
/**
 * AC_ACK_HASH
 */
void AC_ACK_HASH::deliver() {}
ByteBuffer &AC_ACK_HASH::serialize()
{
	return buf();
}
/**
 * AC_ASK_PNGAMEROOM
 */
void AC_ASK_PNGAMEROOM::deliver() {}
ByteBuffer &AC_ASK_PNGAMEROOM::serialize()
{
	return buf();
}
/**
 * AC_NOTIFY_ERROR
 */
void AC_NOTIFY_ERROR::deliver() {}
ByteBuffer &AC_NOTIFY_ERROR::serialize()
{
	return buf();
}
/**
 * AC_REFUSE_LOGIN
 */
void AC_REFUSE_LOGIN::deliver() {}
ByteBuffer &AC_REFUSE_LOGIN::serialize()
{
	return buf();
}
/**
 * AC_EVENT_RESULT
 */
void AC_EVENT_RESULT::deliver() {}
ByteBuffer &AC_EVENT_RESULT::serialize()
{
	return buf();
}
/**
 * AC_ACK_GAME_GUARD
 */
void AC_ACK_GAME_GUARD::deliver() {}
ByteBuffer &AC_ACK_GAME_GUARD::serialize()
{
	return buf();
}
/**
 * AC_ACK_EKEY_FAIL_AUTHREFUSE
 */
void AC_ACK_EKEY_FAIL_AUTHREFUSE::deliver() {}
ByteBuffer &AC_ACK_EKEY_FAIL_AUTHREFUSE::serialize()
{
	return buf();
}
/**
 * AC_ACK_EKEY_FAIL_INPUTEKEY
 */
void AC_ACK_EKEY_FAIL_INPUTEKEY::deliver() {}
ByteBuffer &AC_ACK_EKEY_FAIL_INPUTEKEY::serialize()
{
	return buf();
}
/**
 * AC_ACK_EKEY_FAIL_NEEDCARDPASS
 */
void AC_ACK_EKEY_FAIL_NEEDCARDPASS::deliver() {}
ByteBuffer &AC_ACK_EKEY_FAIL_NEEDCARDPASS::serialize()
{
	return buf();
}
/**
 * AC_ACK_EKEY_FAIL_NOTEXIST
 */
void AC_ACK_EKEY_FAIL_NOTEXIST::deliver() {}
ByteBuffer &AC_ACK_EKEY_FAIL_NOTEXIST::serialize()
{
	return buf();
}
/**
 * AC_ACK_EKEY_FAIL_NOTICE
 */
void AC_ACK_EKEY_FAIL_NOTICE::deliver() {}
ByteBuffer &AC_ACK_EKEY_FAIL_NOTICE::serialize()
{
	return buf();
}
/**
 * AC_ACK_EKEY_FAIL_NOTUSEDEKEY
 */
void AC_ACK_EKEY_FAIL_NOTUSEDEKEY::deliver() {}
ByteBuffer &AC_ACK_EKEY_FAIL_NOTUSEDEKEY::serialize()
{
	return buf();
}
/**
 * AC_ACK_EKEY_FAIL_NOTUSESEKEY
 */
void AC_ACK_EKEY_FAIL_NOTUSESEKEY::deliver() {}
ByteBuffer &AC_ACK_EKEY_FAIL_NOTUSESEKEY::serialize()
{
	return buf();
}
/**
 * AC_ACK_FIRST_LOGIN
 */
void AC_ACK_FIRST_LOGIN::deliver() {}
ByteBuffer &AC_ACK_FIRST_LOGIN::serialize()
{
	return buf();
}
/**
 * AC_ACK_PT_ID_INFO
 */
void AC_ACK_PT_ID_INFO::deliver() {}
ByteBuffer &AC_ACK_PT_ID_INFO::serialize()
{
	return buf();
}
/**
 * AC_REQ_LOGIN_ACCOUNT_INFO
 */
void AC_REQ_LOGIN_ACCOUNT_INFO::deliver() {}
ByteBuffer &AC_REQ_LOGIN_ACCOUNT_INFO::serialize()
{
	return buf();
}
/**
 * AC_REQ_LOGIN_CARDPASS
 */
void AC_REQ_LOGIN_CARDPASS::deliver() {}
ByteBuffer &AC_REQ_LOGIN_CARDPASS::serialize()
{
	return buf();
}
/**
 * AC_REQ_LOGIN_NEWEKEY
 */
void AC_REQ_LOGIN_NEWEKEY::deliver() {}
ByteBuffer &AC_REQ_LOGIN_NEWEKEY::serialize()
{
	return buf();
}
/**
 * AC_REQ_LOGIN_OLDEKEY
 */
void AC_REQ_LOGIN_OLDEKEY::deliver() {}
ByteBuffer &AC_REQ_LOGIN_OLDEKEY::serialize()
{
	return buf();
}
/**
 * AC_REQUEST_SECOND_PASSWORD
 */
void AC_REQUEST_SECOND_PASSWORD::deliver() {}
ByteBuffer &AC_REQUEST_SECOND_PASSWORD::serialize()
{
	return buf();
}
/**
 * AC_ACCEPT_LOGIN2
 */
void AC_ACCEPT_LOGIN2::deliver() {}
ByteBuffer &AC_ACCEPT_LOGIN2::serialize()
{
	return buf();
}
/**
 * AC_OTP_AUTH_ACK
 */
void AC_OTP_AUTH_ACK::deliver() {}
ByteBuffer &AC_OTP_AUTH_ACK::serialize()
{
	return buf();
}
/**
 * AC_OTP_USER
 */
void AC_OTP_USER::deliver() {}
ByteBuffer &AC_OTP_USER::serialize()
{
	return buf();
}
/**
 * AC_SSO_LOGIN_ACK
 */
void AC_SSO_LOGIN_ACK::deliver() {}
ByteBuffer &AC_SSO_LOGIN_ACK::serialize()
{
	return buf();
}
/**
 * AC_REFUSE_LOGIN2
 */
void AC_REFUSE_LOGIN2::deliver() {}
ByteBuffer &AC_REFUSE_LOGIN2::serialize()
{
	return buf();
}
/**
 * AC_REALNAME_AUTH
 */
void AC_REALNAME_AUTH::deliver() {}
ByteBuffer &AC_REALNAME_AUTH::serialize()
{
	return buf();
}
/**
 * AC_SHUTDOWN_INFO
 */
void AC_SHUTDOWN_INFO::deliver() {}
ByteBuffer &AC_SHUTDOWN_INFO::serialize()
{
	return buf();
}
/**
 * AC_SHUTDOWN_NOTIFY
 */
void AC_SHUTDOWN_NOTIFY::deliver() {}
ByteBuffer &AC_SHUTDOWN_NOTIFY::serialize()
{
	return buf();
}
/**
 * AC_REQ_NEW_USER
 */
void AC_REQ_NEW_USER::deliver() {}
ByteBuffer &AC_REQ_NEW_USER::serialize()
{
	return buf();
}
/**
 * AC_REQ_MOBILE_OTP
 */
void AC_REQ_MOBILE_OTP::deliver() {}
ByteBuffer &AC_REQ_MOBILE_OTP::serialize()
{
	return buf();
}
/**
 * AC_REFUSE_LOGIN3
 */
void AC_REFUSE_LOGIN3::deliver() {}
ByteBuffer &AC_REFUSE_LOGIN3::serialize()
{
	return buf();
}
/**
 * AC_LOGIN_OTP
 */
void AC_LOGIN_OTP::deliver() {}
ByteBuffer &AC_LOGIN_OTP::serialize()
{
	return buf();
}
/**
 * AC_REFUSE_LOGIN4
 */
void AC_REFUSE_LOGIN4::deliver() {}
ByteBuffer &AC_REFUSE_LOGIN4::serialize()
{
	return buf();
}
