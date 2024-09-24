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

#ifndef HORIZON_ZONE_GAME_PLAYER_DEFINITIONS_HPP
#define HORIZON_ZONE_GAME_PLAYER_DEFINITIONS_HPP

/** Client action types */
enum player_action_type {
	PLAYER_ACT_ATTACK,
	PLAYER_ACT_ITEM_PICKUP,
	PLAYER_ACT_SIT,
	PLAYER_ACT_STAND,
	PLAYER_ACT_ATTACK_NOMOTION,
	PLAYER_ACT_SPLASH,
	PLAYER_ACT_SKILL,
	PLAYER_ACT_ATTACK_REPEAT,
	PLAYER_ACT_ATTACK_MULTIPLE,
	PLAYER_ACT_ATTACK_MULTIPLE_NOMOTION,
	PLAYER_ACT_ATTACK_CRITICAL,
	PLAYER_ACT_ATTACK_LUCKY,
	PLAYER_ACT_TOUCHSKILL
};

#endif // HORIZON_ZONE_GAME_PLAYER_DEFINITIONS_HPP