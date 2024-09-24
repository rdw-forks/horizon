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

#ifndef HORIZON_ZONE_SKILL_DEFINITIONS_HPP
#define HORIZON_ZONE_SKILL_DEFINITIONS_HPP

#include "BattleDefinitions.hpp" // battle_damage_type in skill_config_data
#include "ItemDefinitions.hpp" // weapon_type, ammunition_type

namespace Horizon
{
namespace Zone
{
	class Unit;
}
}

#define MAX_SKILL_NAME_LENGTH     24

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

enum skill_secondary_type {
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

enum skill_learn_type
{
	SKILL_LEARN_PERMANENT         = 0,
	SKILL_LEARN_TEMPORARY         = 1,
	SKILL_LEARN_PLAGIARIZED       = 2,
	SKILL_LEARN_UNUSED            = 3, ///< needed to maintain the order since the values are saved, can be renamed and used if a new flag is necessary
	SKILL_LEARN_PERM_GRANTED      = 4, ///< Permanent, granted through someway (e.g. script).
	/* */
	/* MUST be the last, because with it the flag value stores a dynamic value (flag+lv) */
	SKILL_LEARN_REPLACED_LV_0     = 5,   // Temporary skill overshadowing permanent skill of level 'N - SKILL_FLAG_REPLACED_LV_0',
};

enum skill_use_fail_cause_type { // clif_skill_fail
	SKILL_USE_FAIL_LEVEL = 0,
	SKILL_USE_FAIL_SP_INSUFFICIENT = 1,
	SKILL_USE_FAIL_HP_INSUFFICIENT = 2,
	SKILL_USE_FAIL_STUFF_INSUFFICIENT = 3,
	SKILL_USE_FAIL_SKILLINTERVAL = 4,
	SKILL_USE_FAIL_MONEY = 5,
	SKILL_USE_FAIL_THIS_WEAPON = 6,
	SKILL_USE_FAIL_REDJAMSTONE = 7,
	SKILL_USE_FAIL_BLUEJAMSTONE = 8,
	SKILL_USE_FAIL_WEIGHTOVER = 9,
	SKILL_USE_FAIL = 10,
	SKILL_USE_FAIL_TOTARGET = 11,
	SKILL_USE_FAIL_ANCILLA_NUMOVER = 12,
	SKILL_USE_FAIL_HOLYWATER = 13,
	SKILL_USE_FAIL_ANCILLA = 14,
	SKILL_USE_FAIL_DUPLICATE_RANGEIN = 15,
	SKILL_USE_FAIL_NEED_OTHER_SKILL = 16,
	SKILL_USE_FAIL_NEED_HELPER = 17,
	SKILL_USE_FAIL_INVALID_DIR = 18,
	SKILL_USE_FAIL_SUMMON = 19,
	SKILL_USE_FAIL_SUMMON_NONE = 20,
	SKILL_USE_FAIL_IMITATION_SKILL_NONE = 21,
	SKILL_USE_FAIL_DUPLICATE = 22,
	SKILL_USE_FAIL_CONDITION = 23,
	SKILL_USE_FAIL_PAINTBRUSH = 24,
	SKILL_USE_FAIL_DRAGON = 25,
	SKILL_USE_FAIL_POS = 26,
	SKILL_USE_FAIL_HELPER_SP_INSUFFICIENT = 27,
	SKILL_USE_FAIL_NEER_WALL = 28,
	SKILL_USE_FAIL_NEED_EXP_1PERCENT = 29,
	SKILL_USE_FAIL_CHORUS_SP_INSUFFICIENT = 30,
	SKILL_USE_FAIL_GC_WEAPONBLOCKING = 31,
	SKILL_USE_FAIL_GC_POISONINGWEAPON = 32,
	SKILL_USE_FAIL_MADOGEAR = 33,
	SKILL_USE_FAIL_NEED_EQUIPMENT_KUNAI = 34,
	SKILL_USE_FAIL_TOTARGET_PLAYER = 35,
	SKILL_USE_FAIL_SIZE = 36,
	SKILL_USE_FAIL_CANONBALL = 37,
	//XXX_SKILL_USE_FAIL_II_MADOGEAR_ACCELERATION = 38,
	//XXX_SKILL_USE_FAIL_II_MADOGEAR_HOVERING_BOOSTER = 39,
	//XXX_SKILL_USE_FAIL_MADOGEAR_HOVERING = 40,
	//XXX_SKILL_USE_FAIL_II_MADOGEAR_SELFDESTRUCTION_DEVICE = 41,
	//XXX_SKILL_USE_FAIL_II_MADOGEAR_SHAPESHIFTER = 42,
	SKILL_USE_FAIL_GUILLONTINE_POISON = 43,
	//XXX_SKILL_USE_FAIL_II_MADOGEAR_COOLING_DEVICE = 44,
	//XXX_SKILL_USE_FAIL_II_MADOGEAR_MAGNETICFIELD_GENERATOR = 45,
	//XXX_SKILL_USE_FAIL_II_MADOGEAR_BARRIER_GENERATOR = 46,
	//XXX_SKILL_USE_FAIL_II_MADOGEAR_OPTICALCAMOUFLAGE_GENERATOR = 47,
	//XXX_SKILL_USE_FAIL_II_MADOGEAR_REPAIRKIT = 48,
	//XXX_SKILL_USE_FAIL_II_MONKEY_SPANNER = 49,
	SKILL_USE_FAIL_MADOGEAR_RIDE = 50,
	SKILL_USE_FAIL_SPELLBOOK = 51,
	SKILL_USE_FAIL_SPELLBOOK_DIFFICULT_SLEEP = 52,
	SKILL_USE_FAIL_SPELLBOOK_PRESERVATION_POINT = 53,
	SKILL_USE_FAIL_SPELLBOOK_READING = 54,
	//XXX_SKILL_USE_FAIL_II_FACE_PAINTS = 55,
	//XXX_SKILL_USE_FAIL_II_MAKEUP_BRUSH = 56,
	SKILL_USE_FAIL_CART = 57,
	//XXX_SKILL_USE_FAIL_II_THORNS_SEED = 58,
	//XXX_SKILL_USE_FAIL_II_BLOOD_SUCKER_SEED = 59,
	SKILL_USE_FAIL_NO_MORE_SPELL = 60,
	//XXX_SKILL_USE_FAIL_II_BOMB_MUSHROOM_SPORE = 61,
	//XXX_SKILL_USE_FAIL_II_GASOLINE_BOOMB = 62,
	//XXX_SKILL_USE_FAIL_II_OIL_BOTTLE = 63,
	//XXX_SKILL_USE_FAIL_II_EXPLOSION_POWDER = 64,
	//XXX_SKILL_USE_FAIL_II_SMOKE_POWDER = 65,
	//XXX_SKILL_USE_FAIL_II_TEAR_GAS = 66,
	//XXX_SKILL_USE_FAIL_II_HYDROCHLORIC_ACID_BOTTLE = 67,
	//XXX_SKILL_USE_FAIL_II_HELLS_PLANT_BOTTLE = 68,
	//XXX_SKILL_USE_FAIL_II_MANDRAGORA_FLOWERPOT = 69,
	SKILL_USE_FAIL_MANUAL_NOTIFY = 70,
	SKILL_USE_FAIL_NEED_ITEM = 71,
	SKILL_USE_FAIL_NEED_EQUIPMENT = 72,
	SKILL_USE_FAIL_COMBOSKILL = 73,
	SKILL_USE_FAIL_SPIRITS = 74,
	SKILL_USE_FAIL_EXPLOSIONSPIRITS = 75,
	SKILL_USE_FAIL_HP_TOOMANY = 76,
	SKILL_USE_FAIL_NEED_ROYAL_GUARD_BANDING = 77,
	SKILL_USE_FAIL_NEED_EQUIPPED_WEAPON_CLASS = 78,
	SKILL_USE_FAIL_EL_SUMMON = 79,
	SKILL_USE_FAIL_RELATIONGRADE = 80,
	SKILL_USE_FAIL_STYLE_CHANGE_FIGHTER = 81,
	SKILL_USE_FAIL_STYLE_CHANGE_GRAPPLER = 82,
	SKILL_USE_FAIL_THERE_ARE_NPC_AROUND = 83,
	SKILL_USE_FAIL_NEED_MORE_BULLET = 84,
	// max known value 96
};

struct skill_learnt_info {
	int16_t skill_id{0};
	int16_t level{0};
	skill_learn_type learn_type{SKILL_LEARN_PERMANENT};
};

struct zc_skill_info_data 
{
	int16_t skill_id{0};
	int32_t skill_type{0};
	int16_t level{0};
	int16_t sp_cost{0};
	int16_t range{0};
	char name[MAX_SKILL_NAME_LENGTH]{0};
	int8_t upgradeable;
	int16_t level2{0};
};

struct skill_required_item_data {
	struct {
		int id;
		int amount[MAX_SKILL_LEVEL];
	} item[MAX_SKILL_ITEM_REQUIRE];
	bool any[MAX_SKILL_LEVEL];
};

struct skill_config_data
{
	uint16_t skill_id{0};
	std::string name, desc;
	int max_level{1};
	int use_range[MAX_SKILL_LEVEL]{0};
	battle_damage_type damage_type[MAX_SKILL_LEVEL]{BDT_NORMAL}; // hittype
	int primary_type{SK_TYPE_PASSIVE}; // skill_primary_type / inf
	int secondary_type{SK_SUBTYPE_NONE};   // skill_secondary_type / inf2
	battle_attack_type attack_type[MAX_SKILL_LEVEL]{BAT_NONE}; // skill_type
	element_type element[MAX_SKILL_LEVEL]{ELE_NEUTRAL};
	int dmg_property{SK_DMG_PROP_NONE};  // skill_damage_property_type /< nk
	int splash_range[MAX_SKILL_LEVEL]{0};
	int number_of_hits[MAX_SKILL_LEVEL]{0};           ///< num
	bool interrupt_cast[MAX_SKILL_LEVEL]{0};
	int cast_defense_rate[MAX_SKILL_LEVEL]{0};
	int max_skill_instances[MAX_SKILL_LEVEL]{0};
	int knock_back_tiles[MAX_SKILL_LEVEL]{0};                 // blewcount
	int cast_time[MAX_SKILL_LEVEL]{0};                ///< cast
	int after_cast_actor_delay[MAX_SKILL_LEVEL]{0};   ///< delay
	int after_cast_walk_delay[MAX_SKILL_LEVEL]{0};
	int upkeep_time[MAX_SKILL_LEVEL]{0};
	int upkeep_time2[MAX_SKILL_LEVEL]{0};
	int cooldown[MAX_SKILL_LEVEL]{0};
	int fixed_cast_time[MAX_SKILL_LEVEL]{0};
	int cast_time_options{0};
	int skill_delay_options{0};
	int hp_cost[MAX_SKILL_LEVEL]{0};                   // hp
	int sp_cost[MAX_SKILL_LEVEL]{0};                   // sp
	int hp_percent_cost[MAX_SKILL_LEVEL]{0};           // hp_rate_cost
	int sp_percent_cost[MAX_SKILL_LEVEL]{0};           // sp_rate_cost
	int max_hp_trigger[MAX_SKILL_LEVEL]{0};            // mhp
	int max_sp_trigger[MAX_SKILL_LEVEL]{0};            // msp
	int zeny_cost[MAX_SKILL_LEVEL]{0};
	int weapon_type{IT_WT_FIST};                       // item_weapon_type  / weapon
	int ammunition_type{IT_AT_NONE};                   // item_ammunition_type / ammo
	int ammunition_cost[MAX_SKILL_LEVEL]{0};
	int required_state[MAX_SKILL_LEVEL]{0};            // skill_required_state_types
	int spirit_sphere_cost[MAX_SKILL_LEVEL]{0};

	struct skill_required_item_data req_items;
	struct skill_required_item_data req_equip;

	int placement_id[MAX_SKILL_LEVEL][2]{{0}};
	int placement_layout_type[MAX_SKILL_LEVEL]{0};
	int placement_range[MAX_SKILL_LEVEL]{0};
	int placement_interval[MAX_SKILL_LEVEL]{0};
	int placement_target[MAX_SKILL_LEVEL]{0};
	int placement_flag{0};
};

struct skill_tree_config 
{
	struct requirement {
		int skill_id{0};
		unsigned char level{0};
	};

	int skill_id{0};
	unsigned char max_level{0};
	unsigned char job_level{0};
	job_class_type inherited_from{JOB_INVALID};
	std::vector<struct requirement> requirements;
};

enum skill_target_type {
  SKTT_SINGLE_TARGETED = 1,
  SKTT_GROUND_TARGETED = 2
};

#endif /* HORIZON_ZONE_SKILL_DEFINITIONS_HPP */
