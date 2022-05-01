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