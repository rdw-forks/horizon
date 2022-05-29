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

#ifndef HORIZON_ZONE_BATTLE_DEFINITIONS_HPP
#define HORIZON_ZONE_BATTLE_DEFINITIONS_HPP

enum battle_target_check_type
{
	BTC_NONE               =   0x000000,
	BTC_SELF               =   0x010000,
	BTC_ENEMY              =   0x020000,
	BTC_PARTY              =   0x040000,
	BTC_GUILD_ALLY         =   0x080000, ///< Only allies, NOT guildmates
	BTC_NEUTRAL            =   0x100000,
	BTC_GUILD              =   0x200000, ///< No Guild Allies
	BTC_GUILD_AND_ALLY     =   0x280000, ///< Guild AND allies (BCT_SAMEGUILD|BCT_GUILDALLY)
	BTC_ALL_EXCEPT_GUILD   =   0x170000, ///< This must be (~BCT_GUILD&BCT_ALL)
	BTC_ALL_EXCEPT_PARTY   =   0x3b0000, ///< This must be (~BCT_PARTY&BCT_ALL)
	BTC_ALL_EXCEPT_ENEMY   =   0x3d0000, ///< This must be (~BCT_ENEMY&BCT_ALL)

	BTC_ALL                =   0x3F0000, ///< Sum of BCT_NOONE to BCT_SAMEGUILD
};

enum battle_attack_type
{
	BAT_NONE       = 0x0000,
	BAT_WEAPON     = 0x0001,
	BAT_MAGIC      = 0x0002,
	BAT_MISC       = 0x0004,
	BAT_SHORT      = 0x0010,
	BAT_LONG       = 0x0040,
	BAT_SKILL      = 0x0100,
	BAT_NORMAL     = 0x0200,
	BAT_WEAPONMASK = 0x000f,
	BAT_RANGEMASK  = 0x00f0,
	BAT_SKILLMASK  = 0x0f00,
};

enum damage_behavior_type
{
	DMG_BHVR_NONE                  = 0x00,
	DMG_BHVR_NON_OFFENSIVE         = 0x01, //< This skill will not cause any damage.
	DMG_BHVR_SPLASH                = 0x02, //< Has splash area (requires source modification)
	DMG_BHVR_SPLIT_BW_TARGETS      = 0x04, //< Damage should be split among targets (requires 'SplashArea' in order to work)
	DMG_BHVR_IGNORE_EQUIP_ATK      = 0x08, //< Skill ignores caster's % damage cards (misc type always ignores)
	DMG_BHVR_IGNORE_DEF_ELE        = 0x10, //< Skill ignores elemental adjustments
	DMG_BHVR_IGNORE_SOFT_DEF       = 0x20, //< Skill ignores target's defense (misc type always ignores)
	DMG_BHVR_IGNORE_FLEE           = 0x40, //< Skill ignores target's flee (magic type always ignores)
	DMG_BHVR_IGNORE_EQUIP_DEF      = 0x80, //< Skill ignores target's def cards
};

enum battle_damage_type {
	BDT_NORMAL      = 0,  // Normal attack
	//BDT_PICKUP      = 1,  // Pick up item
	BDT_SITDOWN     = 2,  // Sit down
	BDT_STANDUP     = 3,  // Stand up
	BDT_ENDURE      = 4,  // Damage (endure)
	BDT_SPLASH      = 5,  // Splash
	BDT_SKILL       = 6,  // Skill
	//BDT_REPEAT      = 7,  // (repeat damage?)
	BDT_MULTIHIT    = 8,  // Multi-hit damage
	BDT_MULTIENDURE = 9,  // Multi-hit damage (endure)
	BDT_CRIT        = 10, // Critical hit
	BDT_PDODGE      = 11, // Lucky dodge
	//BDT_TOUCH       = 12, // (touch skill?)
};

#endif /* HORIZON_ZONE_BATTLE_DEFINITIONS_HPP */
