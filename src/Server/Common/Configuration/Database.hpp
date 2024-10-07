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
 * This is proprietary software. Unauthorized copying,
 * distribution, or modification of this file, via any
 * medium, is strictly prohibited. All rights reserved.
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
