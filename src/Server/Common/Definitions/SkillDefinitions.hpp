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

#ifndef HORIZON_ZONE_GAME_SKILL_DEFINITIONS_HPP
#define HORIZON_ZONE_GAME_SKILL_DEFINITIONS_HPP

#define MAX_SKILL_NAME_LENGTH     32

#define MAX_SKILL_LEVEL           10
#define MAX_SKILL_UNIT_LAYOUT     45
#define MAX_SQUARE_LAYOUT         5 // 11*11 Placement of a maximum unit
#define MAX_SKILL_UNIT_COUNT      ((MAX_SQUARE_LAYOUT*2+1)*(MAX_SQUARE_LAYOUT*2+1))
#define MAX_SKILL_ITEM_REQUIRE    10

#ifndef MAX_SKILL_ID
#define MAX_SKILL_ID 10015 ///< Max used Skill ID
#endif
#ifndef MAX_SKILL_TREE
#define MAX_SKILL_TREE 86 ///< Update this max as necessary. 86 is the value needed for Expanded Super Novice.
#endif


enum skill_placement_behavior_types {
	SPB_NONE             = 0x0000,
	SPB_DEFNOTENEMY      = 0x0001, // If 'defunit_not_enemy' is set, the target is changed to 'friend'
	SPB_NOREITERATION    = 0x0002, // Spell cannot be stacked
	SPB_NOFOOTSET        = 0x0004, // Spell cannot be cast near/on targets
	SPB_NOOVERLAP        = 0x0008, // Spell effects do not overlap
	SPB_PATHCHECK        = 0x0010, // Only cells with a shootable path will be placed
	SPB_NOPC             = 0x0020, // May not target players
	SPB_NOMOB            = 0x0040, // May not target mobs
	SPB_SKILL            = 0x0080, // May target skills
	SPB_DANCE            = 0x0100, // Dance
	SPB_ENSEMBLE         = 0x0200, // Duet
	SPB_SONG             = 0x0400, // Song
	SPB_DUALMODE         = 0x0800, // Spells should trigger both ontimer and onplace/onout/onleft effects.
	SPB_RANGEDSINGLEUNIT = 0x2000, // Hack for ranged layout, only display center
};

enum skill_required_state_types {
	SRS_NONE               = 0x00,
	SRS_HIDING             = 0x01,
	SRS_CLOAKING           = 0x02,
	SRS_HIDDEN             = 0x03,
	SRS_RIDING             = 0x04,
	SRS_FALCON             = 0x05,
	SRS_CART               = 0x06,
	SRS_SHIELD             = 0x07,
	SRS_SIGHT              = 0x08,
	SRS_EXPLOSIONSPIRITS   = 0x09,
	SRS_CARTBOOST          = 0x0A,
	SRS_RECOV_WEIGHT_RATE  = 0x0B,
	SRS_MOVE_ENABLE        = 0x0C,
	SRS_WATER              = 0x0D,
	SRS_RIDINGDRAGON       = 0x0E,
	SRS_WUG                = 0x0F,
	SRS_RIDINGWUG          = 0x10,
	SRS_MADO               = 0x11,
	SRS_ELEMENTALSPIRIT    = 0x12,
	SRS_POISONINGWEAPON    = 0x13,
	SRS_ROLLINGCUTTER      = 0x14,
	SRS_MH_FIGHTING        = 0x15,
	SRS_MH_GRAPPLING       = 0x16,
	SRS_PECO               = 0x17,
	SRS_MAX
};

enum skill_primary_type {
	SK_TYPE_PASSIVE        = 0x00,
	SK_TYPE_ATTACK         = 0x01,
	SK_TYPE_PLACEMENT      = 0x02,
	SK_TYPE_SELF           = 0x04, // Skills casted on self where target is automatically chosen
	// 0x08 not assigned
	SK_TYPE_FRIENDLY       = 0x10,
	SK_TYPE_TRAP           = 0x20,
};

enum skill_damage_property_type {
	SK_DMG_PROP_NONE           = 0x00,
	SK_DMG_PROP_NO_DAMAGE      = 0x01,
	SK_DMG_PROP_SPLASH         = 0x02 | 0x04, // 0x4 = splash & split
	SK_DMG_PROP_SPLASH_ONLY    = 0x02,
	SK_DMG_PROP_SPLASHSPLIT    = 0x04,
	SK_DMG_PROP_NO_CARDFIX_ATK = 0x08,
	SK_DMG_PROP_NO_ELEFIX      = 0x10,
	SK_DMG_PROP_IGNORE_DEF     = 0x20,
	SK_DMG_PROP_IGNORE_FLEE    = 0x40,
	SK_DMG_PROP_NO_CARDFIX_DEF = 0x80,
};

enum skill_sub_type {
	SK_SUBTYPE_NONE              = 0x00000,
	SK_SUBTYPE_QUEST_SKILL       = 0x00001,
	SK_SUBTYPE_NPC_SKILL         = 0x00002, // NPC skills are those that players can't have in their skill tree.
	SK_SUBTYPE_WEDDING_SKILL     = 0x00004,
	SK_SUBTYPE_SPIRIT_SKILL      = 0x00008,
	SK_SUBTYPE_GUILD_SKILL       = 0x00010,
	SK_SUBTYPE_SONG_DANCE        = 0x00020,
	SK_SUBTYPE_ENSEMBLE_SKILL    = 0x00040,
	SK_SUBTYPE_TRAP_SKILL        = 0x00080,
	SK_SUBTYPE_TARGET_SELF       = 0x00100, // Refers to ground placed skills that will target the caster as well (like Grandcross)
	SK_SUBTYPE_NO_TARGET_SELF    = 0x00200,
	SK_SUBTYPE_PARTY_ONLY        = 0x00400,
	SK_SUBTYPE_GUILD_ONLY        = 0x00800,
	SK_SUBTYPE_NO_ENEMY          = 0x01000,
	SK_SUBTYPE_NO_LAND_PROTECTOR = 0x02000, // Spells that can ignore Land Protector
	SK_SUBTYPE_CHORUS_SKILL      = 0x04000, // Chorus skill
	SK_SUBTYPE_FREE_CAST_NORMAL  = 0x08000,
	SK_SUBTYPE_FREE_CAST_REDUCED = 0x10000,
	SK_SUBTYPE_SHOW_SKILL_SCALE  = 0x20000,
	SK_SUBTYPE_ALLOW_REPRODUCE   = 0x40000,
	SK_SUBTYPE_HIDDEN_TRAP       = 0x80000, // Traps that are hidden (based on trap_visiblity battle conf)
	SK_SUBTYPE_IS_COMBO_SKILL    = 0x100000, // Sets whether a skill can be used in combos or not
};

#endif /* HORIZON_ZONE_GAME_SKILL_DEFINITIONS_HPP */
