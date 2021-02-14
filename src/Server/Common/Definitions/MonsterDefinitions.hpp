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

#ifndef HORIZON_ZONE_GAME_MONSTER_DEFINITIONS_HPP
#define HORIZON_ZONE_GAME_MONSTER_DEFINITIONS_HPP

#define MAX_MOB_DROP 10
#define MAX_MVP_DROP 10

enum monster_boss_type {
	BOSS_TYPE_NONE = 0,
	BOSS_TYPE_BOSS = 1,
	BOSS_TYPE_MVP = 2,
};

enum monster_size_type {
	MONSTER_SIZE_SMALL = 0,
	MONSTER_SIZE_MEDIUM,
	MONSTER_SIZE_LARGE,
};

enum monster_race_type {
	// Base Races
	MONSTER_RACE_FORMLESS = 0,  ///< Formless
	MONSTER_RACE_UNDEAD,        ///< Undead
	MONSTER_RACE_BRUTE,         ///< Beast/Brute
	MONSTER_RACE_PLANT,         ///< Plant
	MONSTER_RACE_INSECT,        ///< Insect
	MONSTER_RACE_FISH,          ///< Fish
	MONSTER_RACE_DEMON,         ///< Demon
	MONSTER_RACE_DEMIHUMAN,     ///< Demi-Human (not including Player)
	MONSTER_RACE_ANGEL,         ///< Angel
	MONSTER_RACE_DRAGON,        ///< Dragon
	MONSTER_RACE_PLAYER,        ///< Player
	// Boss
	MONSTER_RACE_BOSS,          ///< Boss
	MONSTER_RACE_NONBOSS,       ///< Non-boss

	MONSTER_RACE_MAX,           // Array size delimiter (keep before the combination races)

	// Combination Races
	MONSTER_RACE_NONDEMIHUMAN,   ///< Every race except Demi-Human (including Player)
	MONSTER_RACE_NONPLAYER,      ///< Every non-player race
	MONSTER_RACE_DEMIPLAYER,     ///< Demi-Human (including Player)
	MONSTER_RACE_NONDEMIPLAYER,  ///< Every race except Demi-Human (and except Player)
	MONSTER_RACE_ALL = 0xFF,     ///< Every race (implemented as equivalent to RC_BOSS and RC_NONBOSS)
};

struct monster_config_data
{
	int monster_id;
	char sprite_name[MAX_UNIT_NAME_LENGTH], name[MAX_UNIT_NAME_LENGTH], alt_name[MAX_UNIT_NAME_LENGTH];

	short view_range, chase_range;
	short group_id;
	unsigned short lv;
	//struct view_data vd;
	unsigned int option;
	//struct mob_skill skill[MAX_MOBSKILL];
	//struct spawn_info spawn[10];

	struct rewards
	{
		unsigned int base_exp, job_exp;
		unsigned int mvp_exp;
		struct { int item_id, rate; } items[MAX_MOB_DROP];
		struct { int item_id, rate; } items_mvp[MAX_MVP_DROP];
	} rewards;
};

enum monster_mode_type
{
	MONSTER_MODE_MASK_NONE               = 0x00000000,
	MONSTER_MODE_MASK_CANMOVE            = 0x00000001,
	MONSTER_MODE_MASK_LOOTER             = 0x00000002,
	MONSTER_MODE_MASK_AGGRESSIVE         = 0x00000004,
	MONSTER_MODE_MASK_ASSIST             = 0x00000008,
	MONSTER_MODE_MASK_CASTSENSOR_IDLE    = 0x00000010,
	MONSTER_MODE_MASK_BOSS               = 0x00000020,
	MONSTER_MODE_MASK_PLANT              = 0x00000040,
	MONSTER_MODE_MASK_CANATTACK          = 0x00000080,
	MONSTER_MODE_MASK_DETECTOR           = 0x00000100,
	MONSTER_MODE_MASK_CASTSENSOR_CHASE   = 0x00000200,
	MONSTER_MODE_MASK_CHANGECHASE        = 0x00000400,
	MONSTER_MODE_MASK_ANGRY              = 0x00000800,
	MONSTER_MODE_MASK_CHANGETARGET_MELEE = 0x00001000,
	MONSTER_MODE_MASK_CHANGETARGET_CHASE = 0x00002000,
	MONSTER_MODE_MASK_TARGETWEAK         = 0x00004000,
	MONSTER_MODE_MASK_NOKNOCKBACK        = 0x00008000,
	//MD_RANDOMTARGET     = 0x00010000, // Not implemented
	// Note: This should be kept within INT_MAX, since it's often cast to int.
	MONSTER_MODE_MASK_ALL               = 0x7FFFFFFF,
};

#endif /* HORIZON_ZONE_GAME_MONSTER_DEFINITIONS_HPP */
