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

 #include "LuaDefinitionSync.hpp"

#include "Server/Common/Configuration/Horizon.hpp"
#include "BattleDefinitions.hpp"
#include "EntityDefinitions.hpp"
#include "ItemDefinitions.hpp"
#include "MonsterDefinitions.hpp"
#include "NPCDefinitions.hpp"
#include "SkillDefinitions.hpp"

void sync_battle_definitions(sol::state &state)
{
	state.create_named_table("TargetCheckType",
		"Noone",  BTC_NONE,
		"Self",  BTC_SELF,
		"Enemy",  BTC_ENEMY,
		"Party",  BTC_PARTY,
		"AllianceOnly",  BTC_GUILD_ALLY,
		"Neutral",  BTC_NEUTRAL,
		"Guild",  BTC_GUILD,
		"GuildAndAlliance",  BTC_GUILD_AND_ALLY,
		"AllExceptGuild",  BTC_ALL_EXCEPT_GUILD,
		"AllExceptParty",  BTC_ALL_EXCEPT_PARTY,
		"AllExceptEnemy",  BTC_ALL_EXCEPT_ENEMY,
		"All",  BTC_ALL
	);

	state.create_named_table("AttackType",
		"None",  BAT_NONE,
		"Weapon",  BAT_WEAPON,
		"Magic",  BAT_MAGIC,
		"Misc",  BAT_MISC
	);

	state.create_named_table("DamageBehavior",
		"NoDamage",  DMG_BHVR_NONE,
		"NonOffensive",  DMG_BHVR_NON_OFFENSIVE,
		"SplashArea",  DMG_BHVR_SPLASH,
		"SplitBetweenTargets",  DMG_BHVR_SPLIT_BW_TARGETS,
		"IgnoreEquipATK",  DMG_BHVR_IGNORE_EQUIP_ATK,
		"IgnoreDefElement",  DMG_BHVR_IGNORE_DEF_ELE,
		"IgnoreSoftDef",  DMG_BHVR_IGNORE_SOFT_DEF,
		"IgnoreFLEE",  DMG_BHVR_IGNORE_FLEE,
		"IgnoreEquipDef",  DMG_BHVR_IGNORE_EQUIP_DEF
	);
}

void sync_entity_definitions(sol::state &state)
{
	state.create_named_table("EntitySize",
		"Small",  ESZ_SMALL,
		"Medium",  ESZ_MEDIUM,
		"Large",  ESZ_LARGE
		"Max",  ESZ_MAX
	);

	state.create_named_table("Element",
		"Neutral",  ELE_NEUTRAL,
		"Water",  ELE_WATER,
		"Earth",  ELE_EARTH,
		"Fire",  ELE_FIRE,
		"Wind",  ELE_WIND,
		"Poison",  ELE_POISON,
		"Holy",  ELE_HOLY,
		"Dark",  ELE_DARK,
		"Ghost",  ELE_GHOST,
		"Undead",  ELE_UNDEAD,
		"Max",  ELE_MAX,
		"Weapon",  ELE_WEAPON,
		"Endowed",  ELE_ENDOWED,
		"Random",  ELE_RANDOM
	);

	state.create_named_table("EntityType",
		"Player",  ENTITY_MASK_PLAYER,
		"NPC",  ENTITY_MASK_NPC,
		"Item",  ENTITY_MASK_ITEM,
		"Skill",  ENTITY_MASK_SKILL,
		"Monster",  ENTITY_MASK_MONSTER,
		"Event",  ENTITY_MASK_EVENT,
		"Pet",  ENTITY_MASK_PET,
		"Homunculus",  ENTITY_MASK_HOMNUCLUS,
		"Mercenary",  ENTITY_MASK_MERCNARY,
		"Elemental",  ENTITY_MASK_ELEMENTAL
	);

	state.create_named_table("Directions",
		"North",  DIR_NORTH,
		"NorthWest",  DIR_NORTH_WEST,
		"West",  DIR_WEST,
		"SouthWest",  DIR_SOUTH_WEST,
		"South",  DIR_SOUTH,
		"SouthEast",  DIR_SOUTH_EAST,
		"East",  DIR_EAST,
		"NorthEast",  DIR_NORTH_EAST
	);


	state.create_named_table("Posture",
		"Standing",  POSTURE_STANDING,
		"Dead",  POSTURE_DEAD,
		"Sitting",  POSTURE_SITTING
	);

	state.create_named_table("Job",
		"Novice",  JOB_NOVICE,
		"Swordman",  JOB_SWORDMAN,
		"Magician",  JOB_MAGE,
		"Archer",  JOB_ARCHER,
		"Acolyte",  JOB_ACOLYTE,
		"Merchant",  JOB_MERCHANT,
		"Thief",  JOB_THIEF,
		"Knight",  JOB_KNIGHT,
		"Priest",  JOB_PRIEST,
		"Wizard",  JOB_WIZARD,
		"Blacksmith",  JOB_BLACKSMITH,
		"Hunter",  JOB_HUNTER,
		"Assassin",  JOB_ASSASSIN,
		//JOB_KNIGHT2
		"Crusader",  JOB_CRUSADER,
		"Monk",  JOB_MONK,
		"Sage",  JOB_SAGE,
		"Rogue",  JOB_ROGUE,
		"Alchemist",  JOB_ALCHEMIST,
		"Bard",  JOB_BARD,
		"Dancer",  JOB_DANCER,
		"Wedding",  JOB_WEDDING,
		"SuperNovice",  JOB_SUPER_NOVICE,
		"Gunslinger",  JOB_GUNSLINGER,
		"Ninja",  JOB_NINJA,
		"Xmas",  JOB_XMAS,
		"Summer",  JOB_SUMMER,
		//4000-
		"HighNovice",  JOB_NOVICE_HIGH,
		"HighSwordman",  JOB_SWORDMAN_HIGH,
		"HighMagician",  JOB_MAGE_HIGH,
		"HighArcher",  JOB_ARCHER_HIGH,
		"HighAcolyte",  JOB_ACOLYTE_HIGH,
		"HighMerchant",  JOB_MERCHANT_HIGH,
		"HighThief",  JOB_THIEF_HIGH,
		"LordKnight",  JOB_LORD_KNIGHT,
		"HighPriest",  JOB_HIGH_PRIEST,
		"HighWizard",  JOB_HIGH_WIZARD,
		"Whitesmith",  JOB_WHITESMITH,
		"Sniper",  JOB_SNIPER,
		"AssassinCross",  JOB_ASSASSIN_CROSS,
		"Paladin",  JOB_PALADIN,
		"Champion",  JOB_CHAMPION,
		"Professor",  JOB_PROFESSOR,
		"Stalker",  JOB_STALKER,
		"Creator",  JOB_CREATOR,
		"Clown",  JOB_CLOWN,
		"Gypsy",  JOB_GYPSY,
		"BabyNovice",  JOB_BABY_NOVICE,
		"BabySwordman",  JOB_BABY_SWORDMAN,
		"BabyMagician",  JOB_BABY_MAGE,
		"BabyArcher",  JOB_BABY_ARCHER,
		"BabyAcolyte",  JOB_BABY_ACOLYTE,
		"BabyMerchant",  JOB_BABY_MERCHANT,
		"BabyThief",  JOB_BABY_THIEF,
		"BabyKnight",  JOB_BABY_KNIGHT,
		"BabyPriest",  JOB_BABY_PRIEST,
		"BabyWizard",  JOB_BABY_WIZARD,
		"BabyBlacksmith",  JOB_BABY_BLACKSMITH,
		"BabyHunter",  JOB_BABY_HUNTER,
		"BabyAssassin",  JOB_BABY_ASSASSIN,
		"BabyCrusader",  JOB_BABY_CRUSADER,
		"BabyMonk",  JOB_BABY_MONK,
		"BabySage",  JOB_BABY_SAGE,
		"BabyRogue",  JOB_BABY_ROGUE,
		"BabyAlchemist",  JOB_BABY_ALCHEMIST,
		"BabyBard",  JOB_BABY_BARD,
		"BabyDancer",  JOB_BABY_DANCER,
		"SuperBaby",  JOB_SUPER_BABY,
		"Taekwon",  JOB_TAEKWON,
		"StarGladiator",  JOB_STAR_GLADIATOR,
		"SoulLinker",  JOB_SOUL_LINKER,
		"Gangsi",  JOB_GANGSI,
		"DeathKnight",  JOB_DEATH_KNIGHT,
		"DarkCollector",  JOB_DARK_COLLECTOR,
		// 4053-
		"RuneKnight",  JOB_RUNE_KNIGHT,
		"Warlock",  JOB_WARLOCK,
		"Ranger",  JOB_RANGER,
		"Archbishop",  JOB_ARCH_BISHOP,
		"Mechanic",  JOB_MECHANIC,
		"GuillotineCross",  JOB_GUILLOTINE_CROSS,
		"RuneKnightTrans",  JOB_RUNE_KNIGHT_T,
		"WarlockTrans",  JOB_WARLOCK_T,
		"RangerTrans",  JOB_RANGER_T,
		"ArchbishopTrans",  JOB_ARCH_BISHOP_T,
		"MechanicTrans",  JOB_MECHANIC_T,
		"GuillotineCrossTrans",  JOB_GUILLOTINE_CROSS_T,
		"RoyalGuard",  JOB_ROYAL_GUARD,
		"Sorcerer",  JOB_SORCERER,
		"Minstrel",  JOB_MINSTREL,
		"Wanderer",  JOB_WANDERER,
		"Sura",  JOB_SURA,
		"Genetic",  JOB_GENETIC,
		"ShadowChaser",  JOB_SHADOW_CHASER,
		"RoyalGuardTrans",  JOB_ROYAL_GUARD_T,
		"SorcererTrans",  JOB_SORCERER_T,
		"MinstrelTrans",  JOB_MINSTREL_T,
		"WandererTrans",  JOB_WANDERER_T,
		"SuraTrans",  JOB_SURA_T,
		"GeneticTrans",  JOB_GENETIC_T,
		"ShadowChaserTrans",  JOB_SHADOW_CHASER_T,
		//4088-4097
		"BabyRuneKnight",  JOB_BABY_RUNE_KNIGHT,
		"BabyWarlock",  JOB_BABY_WARLOCK,
		"BabyRanger",  JOB_BABY_RANGER,
		"BabyArchbishop",  JOB_BABY_ARCH_BISHOP,
		"BabyMechanic",  JOB_BABY_MECHANIC,
		"BabyGuillotineCross",  JOB_BABY_GUILLOTINE_CROSS,
		"BabyRoyalGuard",  JOB_BABY_ROYAL_GUARD,
		"BabySorcerer",  JOB_BABY_SORCERER,
		"BabyMinstrel",  JOB_BABY_MINSTREL,
		"BabyWanderer",  JOB_BABY_WANDERER,
		"BabySura",  JOB_BABY_SURA,
		"BabyGenetic",  JOB_BABY_GENETIC,
		"BabyShadowChaser",  JOB_BABY_SHADOW_CHASER,
		"SuperNoviceExpanded",  JOB_SUPER_NOVICE_E,
		"SuperBabyExpanded",  JOB_SUPER_BABY_E,
		"Kagerou",  JOB_KAGEROU,
		"Oboro",  JOB_OBORO,
		"Rebellion",  JOB_REBELLION,
		"Summoner",  JOB_SUMMONER,
		"StartBase",  JOB_BASE_START,
		"EndBase",  JOB_BASE_END,
		"Start_2_1",  JOB_2_1_START,
		"End_2_1",  JOB_2_1_END,
		"Start_2_2",  JOB_2_2_START,
		"End_2_2",  JOB_2_2_END,
		"StartTransBase",  JOB_TRANS_BASE_START,
		"EndTransBase",  JOB_TRANS_BASE_END,
		"Start_Trans_2_1",  JOB_TRANS_2_1_START,
		"End_Trans_2_1",  JOB_TRANS_2_1_END,
		"Start_Trans_2_2",  JOB_TRANS_2_2_START,
		"End_Trans_2_2",  JOB_TRANS_2_2_END,
		"Start_Baby_Base",  JOB_BABY_BASE_START,
		"End_Baby_Base",  JOB_BABY_BASE_END,
		"Start_Baby_2_1",  JOB_BABY_2_1_START,
		"End_Baby_2_1",  JOB_BABY_2_1_END,
		"Start_Baby_2_2",  JOB_BABY_2_2_START,
		"End_Baby_2_2",  JOB_BABY_2_2_END,
		"Start_3_1",  JOB_3_1_START,
		"End_3_1",  JOB_3_1_END,
		"Start_3_2",  JOB_3_2_START,
		"End_3_2",  JOB_3_2_END,
		"Start_Trans_3_1",  JOB_TRANS_3_1_START,
		"End_Trans_3_1",  JOB_TRANS_3_1_END,
		"Start_Trans_3_2",  JOB_TRANS_3_2_START,
		"End_Trans_3_2",  JOB_TRANS_3_2_END,
		"Start_Baby_3_1",  JOB_BABY_3_1_START,
		"End_Baby_3_1",  JOB_BABY_3_1_END,
		"Start_Baby_3_2",  JOB_BABY_3_2_START,
		"End_Baby_3_2",  JOB_BABY_3_2_END
	);

	state.create_named_table("JobMask",
		"Invalid",  JMASK_INVALID,
		"Novice",  JMASK_NOVICE,
		"Swordman",  JMASK_SWORDMAN,
		"Magician",  JMASK_MAGE,
		"Archer",  JMASK_ARCHER,
		"Acolyte",  JMASK_ACOLYTE,
		"Merchant",  JMASK_MERCHANT,
		"Thief",  JMASK_THIEF,
		"Gangsi",  JMASK_GANGSI,
		"Summoner",  JMASK_SUMMONER,
		"Taekwon",  JMASK_TAEKWON_BASE,
		"Gunslinger",  JMASK_GUNSLINGER_BASE,
		"Ninja",  JMASK_NINJA_BASE,
		"BaseClass",  JMASK_BASE,
		"Wedding",  JMASK_WEDDING,
		"2_1_Class",  JMASK_2_1,
		"2_2_Class",  JMASK_2_2,
		"BabyBaseClass",  JMASK_BABY_BASE,
		"Baby_1_1_Class",  JMASK_BABY_1_1,
		"Baby_1_2_Class",  JMASK_BABY_1_2,
		"Baby_2_1_Class",  JMASK_BABY_2_1,
		"Baby_2_2_Class",  JMASK_BABY_2_2,
		"TransBaseClass",  JMASK_TRANS_BASE,
		"Trans_1_1_Class",  JMASK_TRANS_1_1,
		"Trans_1_2_Class",  JMASK_TRANS_1_2,
		"Trans_2_1_Class",  JMASK_TRANS_2_1,
		"Trans_2_2_Class",  JMASK_TRANS_2_2,
		"3_1_Class",  JMASK_3_1,
		"3_2_Class",  JMASK_3_2,
		"Trans_3_1_Class",  JMASK_TRANS_3_1,
		"Trans_3_2_Class",  JMASK_TRANS_3_2,
		"Baby_3_1_Class",  JMASK_BABY_3_1,
		"Baby_3_3_Class",  JMASK_BABY_3_2,
		"ExpandedClass",  JMASK_EXPANDED,
		"ExpandedBabyClass",  JMASK_EXPANDED_BABY,
		"Expanded_2_1_Class",  JMASK_EXPANDED_2_1,
		"Expanded_2_2_Class",  JMASK_EXPANDED_2_2,

		"NormalClass",  JMASK_NORMAL,
		"BabyClass",  JMASK_BABY,
		"TransClass",  JMASK_TRANS,
		"ThirdClass",  JMASK_3,
		"TransThirdClass",  JMASK_TRANS_3,
		"BabyThirdClass",  JMASK_BABY_3,

		// 2-1 Jobs
		"Knight",  JMASK_KNIGHT,
		"Wizard",  JMASK_WIZARD,
		"Hunter",  JMASK_HUNTER,
		"Priest",  JMASK_PRIEST,
		"Blacksmith",  JMASK_BLACKSMITH,
		"Assassin",  JMASK_ASSASSIN,
		"DeathKnight",  JMASK_DEATH_KNIGHT,

		// 2-2 Jobs
		"Crusader",  JMASK_CRUSADER,
		"Sage",  JMASK_SAGE,
		"BardOrDancer",  JMASK_BARDDANCER,
		"Monk",  JMASK_MONK,
		"Alchemist",  JMASK_ALCHEMIST,
		"Rogue",  JMASK_ROGUE,
		"DarkCollector",  JMASK_DARK_COLLECTOR,

		//Trans Novice And Trans 1-1 J
		"HighNovice",  JMASK_NOVICE_HIGH,
		"HighSwordman",  JMASK_SWORDMAN_HIGH,
		"HighMagician",  JMASK_MAGE_HIGH,
		"HighArcher",  JMASK_ARCHER_HIGH,
		"HighAcolyte",  JMASK_ACOLYTE_HIGH,
		"HighMerchant",  JMASK_MERCHANT_HIGH,
		"HighThief",  JMASK_THIEF_HIGH,

		//Trans 2-1 Jobs
		"LordKnight",  JMASK_LORD_KNIGHT,
		"HighWizard",  JMASK_HIGH_WIZARD,
		"Sniper",  JMASK_SNIPER,
		"HighPriest",  JMASK_HIGH_PRIEST,
		"Whitesmith",  JMASK_WHITESMITH,
		"AssassinCross",  JMASK_ASSASSIN_CROSS,

		//Trans 2-2 Jobs
		"Paladin",  JMASK_PALADIN,
		"Professor",  JMASK_PROFESSOR,
		"ClownOrGypsy",  JMASK_CLOWNGYPSY,
		"Champion",  JMASK_CHAMPION,
		"Creator",  JMASK_CREATOR,
		"Stalker",  JMASK_STALKER,

		//Baby Novice And Baby 1-1 Job
		"BabyNovice",  JMASK_BABY_NOVICE,
		"BabySwordman",  JMASK_BABY_SWORDMAN,
		"BabyMage",  JMASK_BABY_MAGE,
		"BabyArcher",  JMASK_BABY_ARCHER,
		"BabyAcolyte",  JMASK_BABY_ACOLYTE,
		"BabyMerchant",  JMASK_BABY_MERCHANT,
		"BabyThief",  JMASK_BABY_THIEF,

		//Baby 2-1 Jobs
		"BabyKnight",  JMASK_BABY_KNIGHT,
		"BabyWizard",  JMASK_BABY_WIZARD,
		"BabyHunter",  JMASK_BABY_HUNTER,
		"BabyPriest",  JMASK_BABY_PRIEST,
		"BabyBlacksmith",  JMASK_BABY_BLACKSMITH,
		"BabyAssassin",  JMASK_BABY_ASSASSIN,

		//Baby 2-2 Jobs
		"BabyCrusader",  JMASK_BABY_CRUSADER,
		"BabySage",  JMASK_BABY_SAGE,
		"BabyBardOrDancer",  JMASK_BABY_BARDDANCER,
		"BabyMonk",  JMASK_BABY_MONK,
		"BabyAlchemist",  JMASK_BABY_ALCHEMIST,
		"BabyRogue",  JMASK_BABY_ROGUE,

		//3-1 Jobs
		"RuneKnight",  JMASK_RUNE_KNIGHT,
		"Warlock",  JMASK_WARLOCK,
		"Ranger",  JMASK_RANGER,
		"Archbishop",  JMASK_ARCH_BISHOP,
		"Mechanic",  JMASK_MECHANIC,
		"GuillotineCross",  JMASK_GUILLOTINE_CROSS,

		//3-2 Jobs
		"RoyalGuard",  JMASK_ROYAL_GUARD,
		"Sorcerer",  JMASK_SORCERER,
		"MinstrelOrWanderer",  JMASK_MINSTRELWANDERER,
		"Sura",  JMASK_SURA,
		"Genetic",  JMASK_GENETIC,
		"ShadowChaser",  JMASK_SHADOW_CHASER,

		//Trans 3-1 Jobs
		"RuneKnightTrans",  JMASK_RUNE_KNIGHT_T,
		"WarlockTrans",  JMASK_WARLOCK_T,
		"RangerTrans",  JMASK_RANGER_T,
		"ArchbishopTrans",  JMASK_ARCH_BISHOP_T,
		"MechanicTrans",  JMASK_MECHANIC_T,
		"GuillotineCrossTrans",  JMASK_GUILLOTINE_CROSS_T,

		//Trans 3-2 Jobs
		"RoyalGuardTrans",  JMASK_ROYAL_GUARD_T,
		"SorcererTrans",  JMASK_SORCERER_T,
		"MinstrelOrWandererTrans",  JMASK_MINSTRELWANDERER_T,
		"SuraTrans",  JMASK_SURA_T,
		"GeneticTrans",  JMASK_GENETIC_T,
		"ShadowChaserTrans",  JMASK_SHADOW_CHASER_T,

		//Baby 3-1 Jobs
		"BabyRuneKnight",  JMASK_BABY_RUNE_KNIGHT,
		"BabyWarlock",  JMASK_BABY_WARLOCK,
		"BabyRanger",  JMASK_BABY_RANGER,
		"BabyArchbishop",  JMASK_BABY_ARCH_BISHOP,
		"BabyMechanic",  JMASK_BABY_MECHANIC,
		"BabyGuillotineCross",  JMASK_BABY_GUILLOTINE_CROSS,

		//Baby 3-2 Jobs
		"BabyRoyalGuard",  JMASK_BABY_ROYAL_GUARD,
		"BabySorcerer",  JMASK_BABY_SORCERER,
		"BabyMinstrelOrWanderer",  JMASK_BABY_MINSTRELWANDERER,
		"BabySura",  JMASK_BABY_SURA,
		"BabyGenetic",  JMASK_BABY_GENETIC,
		"BabyShadowChaser",  JMASK_BABY_SHADOW_CHASER,

		// Expanded Jobs
		"Taekwon",  JMASK_TAEKWON,
		"StarGladiator",  JMASK_STAR_GLADIATOR,
		"SoulLinker",  JMASK_SOUL_LINKER,

		"SuperNovice",  JMASK_SUPER_NOVICE,
		"SuperNoviceExpanded",  JMASK_SUPER_NOVICE_E,

		"SuperBaby",  JMASK_SUPER_BABY,
		"SuperBabyExpanded",  JMASK_SUPER_BABY_E,

		"Gunslinger",  JMASK_GUNSLINGER,
		"Rebellion",  JMASK_REBELLION,

		"Ninja",  JMASK_NINJA,
		"KagerouOrOboro",  JMASK_KAGEROUOBORO,

		"All",  JMASK_ALL
	);
}

void sync_item_definitions(sol::state &state)
{
	state.create_named_table("RefineType",
		"Armor",  REFINE_TYPE_ARMOR,
		"Weapon1",  REFINE_TYPE_WEAPON1,
		"Weapon2",  REFINE_TYPE_WEAPON2,
		"Weapon3",  REFINE_TYPE_WEAPON3,
		"Weapon4",  REFINE_TYPE_WEAPON4,
		"Max",  REFINE_TYPE_MAX
	);

	state.create_named_table("RefineChanceType",
		"Normal",  REFINE_CHANCE_TYPE_NORMAL,
		"Enriched",  REFINE_CHANCE_TYPE_ENRICHED,
		"EventNormal",  REFINE_CHANCE_TYPE_E_NORMAL,
		"EventEnriched",  REFINE_CHANCE_TYPE_E_ENRICHED,
		"Max",  REFINE_CHANCE_TYPE_MAX
	);

	state.create_named_table("WeaponType",
		"Fist",  IT_WT_FIST,
		"Dagger",  IT_WT_DAGGER,
		"OneHandedSword",  IT_WT_1HSWORD,
		"TwoHandedSword",  IT_WT_2HSWORD,
		"OneHandedSpear",  IT_WT_1HSPEAR,
		"TwoHandedSpear",  IT_WT_2HSPEAR,
		"OneHandedAxe",  IT_WT_1HAXE,
		"TwoHandedAxe",  IT_WT_2HAXE,
		"OneHandedMace",  IT_WT_1HMACE,
		"TwoHandedMace",  IT_WT_2HMACE,
		"OneHandedStaff",  IT_WT_STAFF,
		"Bow",  IT_WT_BOW,
		"Knuckle",  IT_WT_KNUCKLE,
		"MusicalInstrument",  IT_WT_MUSICAL,
		"Whip",  IT_WT_WHIP,
		"Book",  IT_WT_BOOK,
		"Katar",  IT_WT_KATAR,
		"Revolver",  IT_WT_REVOLVER,
		"Rifle",  IT_WT_RIFLE,
		"GatlingGun",  IT_WT_GATLING,
		"Shotgun",  IT_WT_SHOTGUN,
		"GrenadeLauncher",  IT_WT_GRENADE,
		"FuumaShuriken",  IT_WT_HUUMA,
		"TwoHandedStaff",  IT_WT_2HSTAFF,
		"DWDaggers",  IT_WT_DOUBLE_DAGGERS, ///< 2 daggers
		"DWSwords",  IT_WT_DOUBLE_SWORDS, ///< 2 swords
		"DWAxes",  IT_WT_DOUBLE_AXES, ///< 2 axes
		"DWDaggerSword",  IT_WT_DOUBLE_DAGGER_SWORD, ///< dagger + sword
		"DWDaggerAxe",  IT_WT_DOUBLE_DAGGER_AXE, ///< dagger + axe
		"DWSwordAxe",  IT_WT_DOUBLE_SWORD_AXE ///< sword + axe
	);

	state.create_named_table("WeaponTypeMask",
		"Ranged",  IT_WTM_RANGED,
		"Melee",  IT_WTM_MELEE
	);

	state.create_named_table("ItemLevelType",
		"Armor",  IT_LVL_ARMOR,
		"Weapon1",  IT_LVL_WEAPON1,
		"Weapon2",  IT_LVL_WEAPON2,
		"Weapon3",  IT_LVL_WEAPON3,
		"Weapon4",  IT_LVL_WEAPON4,
		"Max",  IT_LVL_MAX
	);

	state.create_named_table("ItemGenderType",
		"Female",  IT_GENDER_FEMALE,
		"Male",  IT_GENDER_MALE,
		"Any",  IT_GENDER_ANY
	);

	state.create_named_table("EquipLocationMask",
		"None",  IT_EQPM_NONE,
		"LowerHead",  IT_EQPM_HEAD_LOW,
		"RightHand",  IT_EQPM_HAND_R,
		"Garment",  IT_EQPM_GARMENT,
		"LeftAccessory",  IT_EQPM_ACC_L,
		"Armor",  IT_EQPM_ARMOR,
		"LeftHand",  IT_EQPM_HAND_L,
		"Shoes",  IT_EQPM_SHOES,
		"RightAccessory",  IT_EQPM_ACC_R,
		"TopHead",  IT_EQPM_HEAD_TOP,
		"MidHead",  IT_EQPM_HEAD_MID,
		"CostumeTopHead",  IT_EQPM_COSTUME_HEAD_TOP,
		"CostumeMidHead",  IT_EQPM_COSTUME_HEAD_MID,
		"CostumeLowerHead",  IT_EQPM_COSTUME_HEAD_LOW,
		"CostumeGarment",  IT_EQPM_COSTUME_GARMENT,
		"Ammunition",  IT_EQPM_AMMO,
		"ShadowArmor",  IT_EQPM_SHADOW_ARMOR,
		"ShadowWeapon",  IT_EQPM_SHADOW_WEAPON,
		"ShadowShield",  IT_EQPM_SHADOW_SHIELD,
		"ShadowShoes",  IT_EQPM_SHADOW_SHOES,
		"ShadowRightAccessory",  IT_EQPM_SHADOW_ACC_R,
		"ShadowLeftAccessory",  IT_EQPM_SHADOW_ACC_L,
		"Weapon",  IT_EQPM_WEAPON,
		"Shield",  IT_EQPM_SHIELD,
		"BothArms",  IT_EQPM_ARMS,
		"AllHeadgear",  IT_EQPM_HELM,
		"AllAccessory",  IT_EQPM_ACC,
		"AllCostume",  IT_EQPM_COSTUME,
		"ShadowAccessory",  IT_EQPM_SHADOW_ACC,
		"ShadowArms",  IT_EQPM_SHADOW_ARMS
	);

	state.create_named_table("EquipLocationIndex",
		"LeftAccessory",  IT_EQPI_ACC_L,
		"RightAccessory",  IT_EQPI_ACC_R,
		"Shoes",  IT_EQPI_SHOES,
		"Garment",  IT_EQPI_GARMENT,
		"LowerHead",  IT_EQPI_HEAD_LOW,
		"MidHead",  IT_EQPI_HEAD_MID,
		"TopHead",  IT_EQPI_HEAD_TOP,
		"Armor",  IT_EQPI_ARMOR,
		"LeftHand",  IT_EQPI_HAND_L,
		"RightHand",  IT_EQPI_HAND_R,
		"CostumeTopHead",  IT_EQPI_COSTUME_TOP,
		"CostumeMidHead",  IT_EQPI_COSTUME_MID,
		"CostumeLowHead",  IT_EQPI_COSTUME_LOW,
		"CostumeGarment",  IT_EQPI_COSTUME_GARMENT,
		"Ammunition",  IT_EQPI_AMMO,
		"ShadowArmor",  IT_EQPI_SHADOW_ARMOR,
		"ShadowWeapon",  IT_EQPI_SHADOW_WEAPON,
		"ShadowShield",  IT_EQPI_SHADOW_SHIELD,
		"ShadowShoes",  IT_EQPI_SHADOW_SHOES,
		"ShadowRightAccessory",  IT_EQPI_SHADOW_ACC_R,
		"ShadowLeftAccessory",  IT_EQPI_SHADOW_ACC_L,
		"Max",  IT_EQPI_MAX
	);

	state.create_named_table("ItemTradeMask",
		"None",  ITRMASK_NONE,
		"Drop",  ITRMASK_DROP,
		"Trade",  ITRMASK_TRADE,
		"TradeWithPartner",  ITRMASK_TRADEWPARTNER,
		"SellToNPC",  ITRMASK_SELL_TO_NPC,
		"StoreInCart",  ITRMASK_CART,
		"StoreInStorage",  ITRMASK_STORAGE,
		"StoreInGuildStorage",  ITRMASK_GSTORAGE,
		"Mail",  ITRMASK_MAIL,
		"Auction",  ITRMASK_AUCTION,
		"SellInBuyingStore",  ITRMASK_BUYING_STORE,
		"AllowAll",  ITRMASK_ALL
	);

	state.create_named_table("ItemUsageMask",
		"Sitting",  IURMASK_SITTING,
		"All",  IURMASK_ALL
	);

	state.create_named_table("ItemType",
		"Healing",  IT_TYPE_HEALING,
		"Unknown",  IT_TYPE_UNKNOWN,
		"Usable",  IT_TYPE_USABLE,
		"Etc",  IT_TYPE_ETC,
		"Weapon",  IT_TYPE_WEAPON,
		"Armor",  IT_TYPE_ARMOR,
		"Card",  IT_TYPE_CARD,
		"PetEgg",  IT_TYPE_PET_EGG,
		"PetArmor",  IT_TYPE_PET_ARMOR,
		"Unknown2",  IT_TYPE_UNKNOWN2,
		"Ammunition",  IT_TYPE_AMMO,
		"ConsumptionDelay",  IT_TYPE_CONSUMPTION_DELAY,
		"Cash",  IT_TYPE_CASH,
		"Max",  IT_TYPE_MAX
	);

	state.create_named_table("AmmoType",
		"None",  IT_AT_NONE,
		"Arrow",  IT_AT_ARROW,
		"ThrowableDagger",  IT_AT_DAGGER,
		"Bullet",  IT_AT_BULLET,
		"Shell",  IT_AT_SHELL,
		"Grenade",  IT_AT_GRENADE,
		"Shuriken",  IT_AT_SHURIKEN,
		"Kunai",  IT_AT_KUNAI,
		"CannonBall",  IT_AT_CANNONBALL,
		"ThrowableItem",  IT_AT_THROWABLE_ITEM,
		"Max",  IT_AT_MAX
	);

	state.create_named_table("ItemBindType",
		"None",  IT_BIND_NONE,
		"Account",  IT_BIND_ACCOUNT,
		"Guild",  IT_BIND_GUILD,
		"Party",  IT_BIND_PARTY,
		"Character",  IT_BIND_CHARACTER,
		"Max",  IT_BIND_MAX
	);
}

void sync_monster_definitions(sol::state &state)
{
	state.create_named_table("MonsterRace",
		"Formless",  MONSTER_RACE_FORMLESS,
		"Undead",  MONSTER_RACE_UNDEAD,
		"Brute",  MONSTER_RACE_BRUTE,
		"Plant",  MONSTER_RACE_PLANT,
		"Insect",  MONSTER_RACE_INSECT,
		"Fish",  MONSTER_RACE_FISH,
		"Demon",  MONSTER_RACE_DEMON,
		"DemiHuman",  MONSTER_RACE_DEMIHUMAN,
		"Angel",  MONSTER_RACE_ANGEL,
		"Dragon",  MONSTER_RACE_DRAGON,
		"Player",  MONSTER_RACE_PLAYER,
		"Boss",  MONSTER_RACE_BOSS,
		"NonBoss",  MONSTER_RACE_NONBOSS
	);

	state.create_named_table("MonsterMode",
		"None",  MONSTER_MODE_MASK_NONE,
		"CanMove",  MONSTER_MODE_MASK_CANMOVE,
		"Looter",  MONSTER_MODE_MASK_LOOTER,
		"Aggressive",  MONSTER_MODE_MASK_AGGRESSIVE,
		"Assist",  MONSTER_MODE_MASK_ASSIST,
		"CastSensorIdle",  MONSTER_MODE_MASK_CASTSENSOR_IDLE,
		"Boss",  MONSTER_MODE_MASK_BOSS,
		"Plant",  MONSTER_MODE_MASK_PLANT,
		"CanAttack",  MONSTER_MODE_MASK_CANATTACK,
		"Detector",  MONSTER_MODE_MASK_DETECTOR,
		"CastSensorChase",  MONSTER_MODE_MASK_CASTSENSOR_CHASE,
		"ChangeChase",  MONSTER_MODE_MASK_CHANGECHASE,
		"Angry",  MONSTER_MODE_MASK_ANGRY,
		"ChangeTargetMelee",  MONSTER_MODE_MASK_CHANGETARGET_MELEE,
		"ChangeTargetChase",  MONSTER_MODE_MASK_CHANGETARGET_CHASE,
		"TargetWeak",  MONSTER_MODE_MASK_TARGETWEAK,
		"NoKnockBack",  MONSTER_MODE_MASK_NOKNOCKBACK
	);

	state.create_named_table("MonsterSkillState",
		"Any", MONSTER_SKILL_STATE_ANY = -1,
		"Idle", MONSTER_SKILL_STATE_IDLE,
		"Walk", MONSTER_SKILL_STATE_WALK,
		"Loot", MONSTER_SKILL_STATE_LOOT,
		"Dead", MONSTER_SKILL_STATE_DEAD,
		"Berserk", MONSTER_SKILL_STATE_BERSERK, //Aggressive mob attacking
		"Angry", MONSTER_SKILL_STATE_ANGRY,   //Mob retaliating from being attacked.
		"Rush", MONSTER_SKILL_STATE_RUSH,    //Mob following a player after being attacked.
		"Follow", MONSTER_SKILL_STATE_FOLLOW,  //Mob following a player without being attacked.
		"AnyTarget", MONSTER_SKILL_STATE_ANYTARGET,
	);

	state.create_named_table("MonsterSkillTarget",
		"Target", MONSTER_SKILL_TARGET_TARGET,
		"Random", MONSTER_SKILL_TARGET_RANDOM,
		"Self", MONSTER_SKILL_TARGET_SELF,
		"Friend", MONSTER_SKILL_TARGET_FRIEND,
		"Master", MONSTER_SKILL_TARGET_MASTER,
		"Around5", MONSTER_SKILL_TARGET_AROUND5,
		"Around6", MONSTER_SKILL_TARGET_AROUND6,
		"Around7", MONSTER_SKILL_TARGET_AROUND7,
		"Around8", MONSTER_SKILL_TARGET_AROUND8,
		"Around1", MONSTER_SKILL_TARGET_AROUND1,
		"Around2", MONSTER_SKILL_TARGET_AROUND2,
		"Around3", MONSTER_SKILL_TARGET_AROUND3,
		"Around4", MONSTER_SKILL_TARGET_AROUND4,
		"Around", MONSTER_SKILL_TARGET_AROUND
	);


	state.create_named_table("MonsterSkillCastCondition",
		"Always", MONSTER_SKILL_CC_ALWAYS,
		"MyHpLtMaxRate", MONSTER_SKILL_CC_MYHPLTMAXRATE,
		"MyHpInRate", MONSTER_SKILL_CC_MYHPINRATE,
		"FriendHpLtMaxRate", MONSTER_SKILL_CC_FRIENDHPLTMAXRATE,
		"FriendHpInRate", MONSTER_SKILL_CC_FRIENDHPINRATE,
		"MyStatusOn", MONSTER_SKILL_CC_MYSTATUSON,
		"MyStatusOff", MONSTER_SKILL_CC_MYSTATUSOFF,
		"FriendStatusOn", MONSTER_SKILL_CC_FRIENDSTATUSON,
		"FriendStatusOff", MONSTER_SKILL_CC_FRIENDSTATUSOFF,
		"AttackPCGT", MONSTER_SKILL_CC_ATTACKPCGT,
		"AttackPCGE", MONSTER_SKILL_CC_ATTACKPCGE,
		"SlaveLT", MONSTER_SKILL_CC_SLAVELT,
		"SlaveLE", MONSTER_SKILL_CC_SLAVELE,
		"CloseRangeAttacked", MONSTER_SKILL_CC_CLOSERANGEATTACKED,
		"LongRangeAttacked", MONSTER_SKILL_CC_LONGRANGEATTACKED,
		"AfterSkill", MONSTER_SKILL_CC_AFTERSKILL,
		"SkillUsed", MONSTER_SKILL_CC_SKILLUSED,
		"CastTargeted", MONSTER_SKILL_CC_CASTTARGETED,
		"RudeAttacked", MONSTER_SKILL_CC_RUDEATTACKED,
		"MasterHPLTMaxRate", MONSTER_SKILL_CC_MASTERHPLTMAXRATE,
		"MasterAttacked", MONSTER_SKILL_CC_MASTERATTACKED,
		"Alchemist", MONSTER_SKILL_CC_ALCHEMIST,
		"Spawn", MONSTER_SKILL_CC_SPAWN,
		"MagicAttacked", MONSTER_SKILL_CC_MAGICATTACKED
	);
}

void sync_skill_definitions(sol::state &state)
{
	state.create_named_table("SkillType",
		"Passive", SK_TYPE_PASSIVE,
		"Attack", SK_TYPE_ATTACK,
		"Placement", SK_TYPE_PLACEMENT,
		"Self", SK_TYPE_SELF,
		"Friendly", SK_TYPE_FRIENDLY,
		"Trap", SK_TYPE_TRAP
	);

	state.create_named_table("SkillPlacementBehavior", 
		"None",  SPB_NONE,
		"DefNotEnemy",  SPB_DEFNOTENEMY,
		"CannotOverlap",  SPB_NOREITERATION,
		"AllowPlacementOnTarget",  SPB_NOFOOTSET,
		"CannotOverlap",  SPB_NOOVERLAP,
		"CheckObstructionInPath",  SPB_PATHCHECK,
		"WontTargetPlayers",  SPB_NOPC,
		"WontTargetMobs",  SPB_NOMOB,
		"CanTargetSkills",  SPB_SKILL,
		"IsDance",  SPB_DANCE,
		"IsEnsemble",  SPB_ENSEMBLE,
		"IsSong",  SPB_SONG,
		"AffectOnContact",  SPB_DUALMODE,
		"OnlyDisplayCenter",  SPB_RANGEDSINGLEUNIT
	);

	state.create_named_table("SkillRequiredState",
		"None",  SRS_NONE,
		"Hiding",  SRS_HIDING,
		"Cloaking",  SRS_CLOAKING,
		"Hidden",  SRS_HIDDEN,
		"Riding",  SRS_RIDING,
		"Falcon",  SRS_FALCON,
		"Cart",  SRS_CART,
		"Shield",  SRS_SHIELD,
		"Sight",  SRS_SIGHT,
		"ExplosionSpirits",  SRS_EXPLOSIONSPIRITS,
		"CartBoost",  SRS_CARTBOOST,
		"NotOverWeight",  SRS_RECOV_WEIGHT_RATE,
		"Moveable",  SRS_MOVE_ENABLE,
		"InWater",  SRS_WATER,
		"Dragon",  SRS_RIDINGDRAGON,
		"Warg",  SRS_WUG,
		"RidingWarg",  SRS_RIDINGWUG,
		"MadoGear",  SRS_MADO,
		"ElementalSpirit",  SRS_ELEMENTALSPIRIT,
		"PoisonWeapon",  SRS_POISONINGWEAPON,
		"RollingCutter",  SRS_ROLLINGCUTTER,
		"MH_Fighting",  SRS_MH_FIGHTING,
		"MH_Grappling",  SRS_MH_GRAPPLING,
		"Peco",  SRS_PECO
	);

	state.create_named_table("SkillSubType",
		"None", SK_SUBTYPE_NONE,
		"Quest", SK_SUBTYPE_QUEST_SKILL,
		"NPC", SK_SUBTYPE_NPC_SKILL,
		"Wedding", SK_SUBTYPE_WEDDING_SKILL,
		"Spirit", SK_SUBTYPE_SPIRIT_SKILL,
		"Guild", SK_SUBTYPE_GUILD_SKILL,
		"Song", SK_SUBTYPE_SONG_DANCE,
		"Ensemble", SK_SUBTYPE_ENSEMBLE_SKILL,
		"Trap", SK_SUBTYPE_TRAP_SKILL,
		"TargetSelf", SK_SUBTYPE_TARGET_SELF,
		"NoTargetSelf", SK_SUBTYPE_NO_TARGET_SELF,
		"PartyOnly", SK_SUBTYPE_PARTY_ONLY,
		"GuildOnly", SK_SUBTYPE_GUILD_ONLY,
		"NoEnemy", SK_SUBTYPE_NO_ENEMY,
		"IgnoreLandProtector", SK_SUBTYPE_NO_LAND_PROTECTOR,
		"Chorus", SK_SUBTYPE_CHORUS_SKILL,
		"FreeCastNormal", SK_SUBTYPE_FREE_CAST_NORMAL,
		"FreeCastReduced", SK_SUBTYPE_FREE_CAST_REDUCED,
		"ShowSkillScale", SK_SUBTYPE_SHOW_SKILL_SCALE,
		"AllowReproduce", SK_SUBTYPE_ALLOW_REPRODUCE,
		"HiddenTrap", SK_SUBTYPE_HIDDEN_TRAP,
		"IsCombo", SK_SUBTYPE_IS_COMBO_SKILL   
	);
}
