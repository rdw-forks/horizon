/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 * Copyright (c) 2019 Sagun K. (sagunxp@gmail.com).
 * Copyright (c) 2019 Horizon Dev Team.
 *
 * Base Author - Sagun K. (sagunxp@gmail.com)
 *
 * This library is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 **************************************************/

#ifndef HORIZON_COMMON_CONFIGURATION_DATABASE_HPP
#define HORIZON_COMMON_CONFIGURATION_DATABASE_HPP

enum game_account_gender_type
{
	ACCOUNT_GENDER_MALE,
	ACCOUNT_GENDER_FEMALE,
	ACCOUNT_GENDER_NONE
};

enum game_account_state_type
{
	ACCOUNT_STATE_NONE,
	ACCOUNT_STATE_BANNED
};

enum character_gender_type
{
	CHARACTER_GENDER_FEMALE = 0,
	CHARACTER_GENDER_MALE = 1,
};

enum character_save_mask
{
	CHAR_SAVE_BASE_DATA = 0x1,
	CHAR_SAVE_STATUS_DATA = 0x2,
	CHAR_SAVE_INVENTORY_DATA = 0x4,
	CHAR_SAVE_ALL = 0xf,
};

#endif
