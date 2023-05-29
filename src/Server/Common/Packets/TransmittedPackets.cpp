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
#include "Server/Common/Session/CommonSession.hpp"
#include "Utility/Utility.hpp"

using namespace Horizon::Common;

/**
 * SC_ACK_ENCRYPTION
 */
void SC_ACK_ENCRYPTION::deliver() {}
ByteBuffer &SC_ACK_ENCRYPTION::serialize()
{
	return buf();
}
/**
 * SC_BILLING_INFO
 */
void SC_BILLING_INFO::deliver() {}
ByteBuffer &SC_BILLING_INFO::serialize()
{
	return buf();
}
/**
 * SC_NOTIFY_BAN
 */
void SC_NOTIFY_BAN::deliver() {}
ByteBuffer &SC_NOTIFY_BAN::serialize()
{
	return buf();
}
/**
 * AHC_GAME_GUARD
 */
void AHC_GAME_GUARD::deliver() {}
ByteBuffer &AHC_GAME_GUARD::serialize()
{
	return buf();
}
/**
 * CAH_ACK_GAME_GUARD
 */
void CAH_ACK_GAME_GUARD::deliver() {}
ByteBuffer &CAH_ACK_GAME_GUARD::serialize()
{
	return buf();
}
/**
 * SC_LOGIN_ANSWER
 */
void SC_LOGIN_ANSWER::deliver() {}
ByteBuffer &SC_LOGIN_ANSWER::serialize()
{
	return buf();
}
/**
 * SC_LOGIN_ERROR
 */
void SC_LOGIN_ERROR::deliver() {}
ByteBuffer &SC_LOGIN_ERROR::serialize()
{
	return buf();
}
/**
 * SC_SOCT
 */
void SC_SOCT::deliver() {}
ByteBuffer &SC_SOCT::serialize()
{
	return buf();
}
/**
 * SC_LOGIN_ANSWER_WITH_ID
 */
void SC_LOGIN_ANSWER_WITH_ID::deliver() {}
ByteBuffer &SC_LOGIN_ANSWER_WITH_ID::serialize()
{
	return buf();
}
