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

#include "UnitComponent.hpp"

#include "Server/Common/Configuration/Horizon.hpp"
#include "Server/Zone/Game/Units/Player/Player.hpp"
#include "Server/Zone/Game/Units/Unit.hpp"
#include "Server/Zone/Game/Units/Battle/Combat.hpp"
#include "Server/Zone/Game/Units/Traits/Status.hpp"
#include "Server/Zone/Definitions/ClientDefinitions.hpp"
#include "Server/Zone/Game/Map/Grid/Notifiers/GridNotifiers.hpp"

#include "UnitDefinitions.hpp"

using namespace Horizon::Zone;

void UnitComponent::sync_definitions(std::shared_ptr<sol::state> state)
{
	state->create_named_table("UnitSize",
		"Small", (int) ESZ_SMALL,
		"Medium", (int) ESZ_MEDIUM,
		"Large", (int) ESZ_LARGE,
		"Max", (int) ESZ_MAX
	);

	state->new_enum("Element",
		"Neutral", (int) ELE_NEUTRAL,
		"Water", (int) ELE_WATER,
		"Earth", (int) ELE_EARTH,
		"Fire", (int) ELE_FIRE,
		"Wind", (int) ELE_WIND,
		"Poison", (int) ELE_POISON,
		"Holy", (int) ELE_HOLY,
		"Dark", (int) ELE_DARK,
		"Ghost", (int) ELE_GHOST,
		"Undead", (int) ELE_UNDEAD,
		"Max", (int) ELE_MAX,
		"Weapon", (int) ELE_WEAPON,
		"Endowed", (int) ELE_ENDOWED,
		"Random", (int) ELE_RANDOM
	);

	state->create_named_table("UnitType",
		"Player", (int) UNIT_MASK_PLAYER,
		"NPC", (int) UNIT_MASK_NPC,
		"Item", (int) UNIT_MASK_ITEM,
		"Skill", (int) UNIT_MASK_SKILL,
		"Monster", (int) UNIT_MASK_MONSTER,
		"Event", (int) UNIT_MASK_EVENT,
		"Pet", (int) UNIT_MASK_PET,
		"Homunculus", (int) UNIT_MASK_HOMUNCULUS,
		"Mercenary", (int) UNIT_MASK_MERCENARY,
		"Elemental", (int) UNIT_MASK_ELEMENTAL
	);

	state->create_named_table("Directions",
		"North", (int) DIR_NORTH,
		"NorthWest", (int) DIR_NORTH_WEST,
		"West", (int) DIR_WEST,
		"SouthWest", (int) DIR_SOUTH_WEST,
		"South", (int) DIR_SOUTH,
		"SouthEast", (int) DIR_SOUTH_EAST,
		"East", (int) DIR_EAST,
		"NorthEast", (int) DIR_NORTH_EAST
	);

	state->create_named_table("Posture",
		"Standing", (int) POSTURE_STANDING,
		"Dead", (int) POSTURE_DEAD,
		"Sitting", (int) POSTURE_SITTING
	);
	state->create_named_table("zc_notify_act_3_action_types",
    	"Damage", (int) ZCNA3_DAMAGE,
    	"PickupItem", (int) ZCNA3_PICKUP_ITEM,
    	"Sit", (int) ZCNA3_SIT,
    	"Stand", (int) ZCNA3_STAND,
    	"EndureDamage", (int) ZCNA3_ENDURE_DAMAGE,
    	"Splash", (int) ZCNA3_SPLASH,
    	"Skill", (int) ZCNA3_SKILL ,
    	"RepeatDamage", (int) ZCNA3_REPEAT_DAMAGE,
    	"MultiHitDamage", (int) ZCNA3_MULTI_HIT_DAMAGE,
    	"MultiHitEndureDamage", (int) ZCNA3_MULTI_HIT_ENDURE_DAMAGE,
    	"CriticalHit ", (int) ZCNA3_CRITICAL_HIT,
    	"LuckyDodge ", (int) ZCNA3_LUCKY_DODGE,
    	"TouchSkill", (int) ZCNA3_TOUCH_SKILL,
    	"MultiHitCritical", (int) ZCNA3_MULTI_HIT_CRITICAL
	);

	state->create_named_table("grid_unit_skill_use_notification_type",
		"GRID_UNIT_SKILL_USE_NOTIFY_CASTTIME", GRID_UNIT_SKILL_USE_NOTIFY_CASTTIME,
		"GRID_UNIT_SKILL_USE_NOTIFY_SUCCESS_DAMAGE", GRID_UNIT_SKILL_USE_NOTIFY_SUCCESS_DAMAGE,
    	"GRID_UNIT_SKILL_USE_NOTIFY_SUCCESS_NO_DAMAGE", GRID_UNIT_SKILL_USE_NOTIFY_SUCCESS_NO_DAMAGE
	);

	sol::table tbl = state->create_named_table("Job");

	tbl["Novice"] = (int) JOB_NOVICE;
	tbl["Swordman"] = (int) JOB_SWORDMAN;
	tbl["Magician"] = (int) JOB_MAGE;
	tbl["Archer"] = (int) JOB_ARCHER;
	tbl["Acolyte"] = (int) JOB_ACOLYTE;
	tbl["Merchant"] = (int) JOB_MERCHANT;
	tbl["Thief"] = (int) JOB_THIEF;
	tbl["Knight"] = (int) JOB_KNIGHT;
	tbl["Priest"] = (int) JOB_PRIEST;
	tbl["Wizard"] = (int) JOB_WIZARD;
	tbl["Blacksmith"] = (int) JOB_BLACKSMITH;
	tbl["Hunter"] = (int) JOB_HUNTER;
	tbl["Assassin"] = (int) JOB_ASSASSIN;
	//JOB_KNIGHT2
	tbl["Crusader"] = (int) JOB_CRUSADER;
	tbl["Monk"] = (int) JOB_MONK;
	tbl["Sage"] = (int) JOB_SAGE;
	tbl["Rogue"] = (int) JOB_ROGUE;
	tbl["Alchemist"] = (int) JOB_ALCHEMIST;
	tbl["Bard"] = (int) JOB_BARD;
	tbl["Dancer"] = (int) JOB_DANCER;
	tbl["Wedding"] = (int) JOB_WEDDING;
	tbl["SuperNovice"] = (int) JOB_SUPER_NOVICE;
	tbl["Gunslinger"] = (int) JOB_GUNSLINGER;
	tbl["Ninja"] = (int) JOB_NINJA;
	tbl["Xmas"] = (int) JOB_XMAS;
	tbl["Summer"] = (int) JOB_SUMMER;
	//4000-
	tbl["HighNovice"] = (int) JOB_NOVICE_HIGH;
	tbl["HighSwordman"] = (int) JOB_SWORDMAN_HIGH;
	tbl["HighMagician"] = (int) JOB_MAGE_HIGH;
	tbl["HighArcher"] = (int) JOB_ARCHER_HIGH;
	tbl["HighAcolyte"] = (int) JOB_ACOLYTE_HIGH;
	tbl["HighMerchant"] = (int) JOB_MERCHANT_HIGH;
	tbl["HighThief"] = (int) JOB_THIEF_HIGH;
	tbl["LordKnight"] = (int) JOB_LORD_KNIGHT;
	tbl["HighPriest"] = (int) JOB_HIGH_PRIEST;
	tbl["HighWizard"] = (int) JOB_HIGH_WIZARD;
	tbl["Whitesmith"] = (int) JOB_WHITESMITH;
	tbl["Sniper"] = (int) JOB_SNIPER;
	tbl["AssassinCross"] = (int) JOB_ASSASSIN_CROSS;
	tbl["Paladin"] = (int) JOB_PALADIN;
	tbl["Champion"] = (int) JOB_CHAMPION;
	tbl["Professor"] = (int) JOB_PROFESSOR;
	tbl["Stalker"] = (int) JOB_STALKER;
	tbl["Creator"] = (int) JOB_CREATOR;
	tbl["Clown"] = (int) JOB_CLOWN;
	tbl["Gypsy"] = (int) JOB_GYPSY;
	tbl["BabyNovice"] = (int) JOB_BABY_NOVICE;
	tbl["BabySwordman"] = (int) JOB_BABY_SWORDMAN;
	tbl["BabyMagician"] = (int) JOB_BABY_MAGE;
	tbl["BabyArcher"] = (int) JOB_BABY_ARCHER;
	tbl["BabyAcolyte"] = (int) JOB_BABY_ACOLYTE;
	tbl["BabyMerchant"] = (int) JOB_BABY_MERCHANT;
	tbl["BabyThief"] = (int) JOB_BABY_THIEF;
	tbl["BabyKnight"] = (int) JOB_BABY_KNIGHT;
	tbl["BabyPriest"] = (int) JOB_BABY_PRIEST;
	tbl["BabyWizard"] = (int) JOB_BABY_WIZARD;
	tbl["BabyBlacksmith"] = (int) JOB_BABY_BLACKSMITH;
	tbl["BabyHunter"] = (int) JOB_BABY_HUNTER;
	tbl["BabyAssassin"] = (int) JOB_BABY_ASSASSIN;
	tbl["BabyCrusader"] = (int) JOB_BABY_CRUSADER;
	tbl["BabyMonk"] = (int) JOB_BABY_MONK;
	tbl["BabySage"] = (int) JOB_BABY_SAGE;
	tbl["BabyRogue"] = (int) JOB_BABY_ROGUE;
	tbl["BabyAlchemist"] = (int) JOB_BABY_ALCHEMIST;
	tbl["BabyBard"] = (int) JOB_BABY_BARD;
	tbl["BabyDancer"] = (int) JOB_BABY_DANCER;
	tbl["SuperBaby"] = (int) JOB_SUPER_BABY;
	tbl["Taekwon"] = (int) JOB_TAEKWON;
	tbl["StarGladiator"] = (int) JOB_STAR_GLADIATOR;
	tbl["SoulLinker"] = (int) JOB_SOUL_LINKER;
	tbl["Gangsi"] = (int) JOB_GANGSI;
	tbl["DeathKnight"] = (int) JOB_DEATH_KNIGHT;
	tbl["DarkCollector"] = (int) JOB_DARK_COLLECTOR;
	// 4053-
	tbl["RuneKnight"] = (int) JOB_RUNE_KNIGHT;
	tbl["Warlock"] = (int) JOB_WARLOCK;
	tbl["Ranger"] = (int) JOB_RANGER;
	tbl["Archbishop"] = (int) JOB_ARCH_BISHOP;
	tbl["Mechanic"] = (int) JOB_MECHANIC;
	tbl["GuillotineCross"] = (int) JOB_GUILLOTINE_CROSS;
	tbl["RuneKnightTrans"] = (int) JOB_RUNE_KNIGHT_T;
	tbl["WarlockTrans"] = (int) JOB_WARLOCK_T;
	tbl["RangerTrans"] = (int) JOB_RANGER_T;
	tbl["ArchbishopTrans"] = (int) JOB_ARCH_BISHOP_T;
	tbl["MechanicTrans"] = (int) JOB_MECHANIC_T;
	tbl["GuillotineCrossTrans"] = (int) JOB_GUILLOTINE_CROSS_T;
	tbl["RoyalGuard"] = (int) JOB_ROYAL_GUARD;
	tbl["Sorcerer"] = (int) JOB_SORCERER;
	tbl["Minstrel"] = (int) JOB_MINSTREL;
	tbl["Wanderer"] = (int) JOB_WANDERER;
	tbl["Sura"] = (int) JOB_SURA;
	tbl["Genetic"] = (int) JOB_GENETIC;
	tbl["ShadowChaser"] = (int) JOB_SHADOW_CHASER;
	tbl["RoyalGuardTrans"] = (int) JOB_ROYAL_GUARD_T;
	tbl["SorcererTrans"] = (int) JOB_SORCERER_T;
	tbl["MinstrelTrans"] = (int) JOB_MINSTREL_T;
	tbl["WandererTrans"] = (int) JOB_WANDERER_T;
	tbl["SuraTrans"] = (int) JOB_SURA_T;
	tbl["GeneticTrans"] = (int) JOB_GENETIC_T;
	tbl["ShadowChaserTrans"] = (int) JOB_SHADOW_CHASER_T;
	//4088-4097
	tbl["BabyRuneKnight"] = (int) JOB_BABY_RUNE_KNIGHT;
	tbl["BabyWarlock"] = (int) JOB_BABY_WARLOCK;
	tbl["BabyRanger"] = (int) JOB_BABY_RANGER;
	tbl["BabyArchbishop"] = (int) JOB_BABY_ARCH_BISHOP;
	tbl["BabyMechanic"] = (int) JOB_BABY_MECHANIC;
	tbl["BabyGuillotineCross"] = (int) JOB_BABY_GUILLOTINE_CROSS;
	tbl["BabyRoyalGuard"] = (int) JOB_BABY_ROYAL_GUARD;
	tbl["BabySorcerer"] = (int) JOB_BABY_SORCERER;
	tbl["BabyMinstrel"] = (int) JOB_BABY_MINSTREL;
	tbl["BabyWanderer"] = (int) JOB_BABY_WANDERER;
	tbl["BabySura"] = (int) JOB_BABY_SURA;
	tbl["BabyGenetic"] = (int) JOB_BABY_GENETIC;
	tbl["BabyShadowChaser"] = (int) JOB_BABY_SHADOW_CHASER;
	tbl["SuperNoviceExpanded"] = (int) JOB_SUPER_NOVICE_E;
	tbl["SuperBabyExpanded"] = (int) JOB_SUPER_BABY_E;
	tbl["Kagerou"] = (int) JOB_KAGEROU;
	tbl["Oboro"] = (int) JOB_OBORO;
	tbl["Rebellion"] = (int) JOB_REBELLION;
	tbl["Summoner"] = (int) JOB_SUMMONER;
	tbl["StartBase"] = (int) JOB_BASE_START;
	tbl["EndBase"] = (int) JOB_BASE_END;
	tbl["Start_2_1"] = (int) JOB_2_1_START;
	tbl["End_2_1"] = (int) JOB_2_1_END;
	tbl["Start_2_2"] = (int) JOB_2_2_START;
	tbl["End_2_2"] = (int) JOB_2_2_END;
	tbl["StartTransBase"] = (int) JOB_TRANS_BASE_START;
	tbl["EndTransBase"] = (int) JOB_TRANS_BASE_END;
	tbl["Start_Trans_2_1"] = (int) JOB_TRANS_2_1_START;
	tbl["End_Trans_2_1"] = (int) JOB_TRANS_2_1_END;
	tbl["Start_Trans_2_2"] = (int) JOB_TRANS_2_2_START;
	tbl["End_Trans_2_2"] = (int) JOB_TRANS_2_2_END;
	tbl["Start_Baby_Base"] = (int) JOB_BABY_BASE_START;
	tbl["End_Baby_Base"] = (int) JOB_BABY_BASE_END;
	tbl["Start_Baby_2_1"] = (int) JOB_BABY_2_1_START;
	tbl["End_Baby_2_1"] = (int) JOB_BABY_2_1_END;
	tbl["Start_Baby_2_2"] = (int) JOB_BABY_2_2_START;
	tbl["End_Baby_2_2"] = (int) JOB_BABY_2_2_END;
	tbl["Start_3_1"] = (int) JOB_3_1_START;
	tbl["End_3_1"] = (int) JOB_3_1_END;
	tbl["Start_3_2"] = (int) JOB_3_2_START;
	tbl["End_3_2"] = (int) JOB_3_2_END;
	tbl["Start_Trans_3_1"] = (int) JOB_TRANS_3_1_START;
	tbl["End_Trans_3_1"] = (int) JOB_TRANS_3_1_END;
	tbl["Start_Trans_3_2"] = (int) JOB_TRANS_3_2_START;
	tbl["End_Trans_3_2"] = (int) JOB_TRANS_3_2_END;
	tbl["Start_Baby_3_1"] = (int) JOB_BABY_3_1_START;
	tbl["End_Baby_3_1"] = (int) JOB_BABY_3_1_END;
	tbl["Start_Baby_3_2"] = (int) JOB_BABY_3_2_START;
	tbl["End_Baby_3_2"] = (int) JOB_BABY_3_2_END;

	sol::table job_mask_table = state->create_named_table("JobMask");
	job_mask_table["Invalid"] = (int) JMASK_INVALID;
	job_mask_table["Novice"] = (int) JMASK_NOVICE;
	job_mask_table["Swordman"] = (int) JMASK_SWORDMAN;
	job_mask_table["Magician"] = (int) JMASK_MAGE;
	job_mask_table["Archer"] = (int) JMASK_ARCHER;
	job_mask_table["Acolyte"] = (int) JMASK_ACOLYTE;
	job_mask_table["Merchant"] = (int) JMASK_MERCHANT;
	job_mask_table["Thief"] = (int) JMASK_THIEF;
	job_mask_table["Gangsi"] = (int) JMASK_GANGSI;
	job_mask_table["Summoner"] = (int) JMASK_SUMMONER;
	job_mask_table["Taekwon"] = (int) JMASK_TAEKWON_BASE;
	job_mask_table["Gunslinger"] = (int) JMASK_GUNSLINGER_BASE;
	job_mask_table["Ninja"] = (int) JMASK_NINJA_BASE;
	job_mask_table["BaseClass"] = (int) JMASK_BASE;
	job_mask_table["Wedding"] = (int) JMASK_WEDDING;
	job_mask_table["2_1_Class"] = (int) JMASK_2_1;
	job_mask_table["2_2_Class"] = (int) JMASK_2_2;
	job_mask_table["BabyBaseClass"] = (int) JMASK_BABY_BASE;
	job_mask_table["Baby_1_1_Class"] = (int) JMASK_BABY_1_1;
	job_mask_table["Baby_1_2_Class"] = (int) JMASK_BABY_1_2;
	job_mask_table["Baby_2_1_Class"] = (int) JMASK_BABY_2_1;
	job_mask_table["Baby_2_2_Class"] = (int) JMASK_BABY_2_2;
	job_mask_table["TransBaseClass"] = (int) JMASK_TRANS_BASE;
	job_mask_table["Trans_1_1_Class"] = (int) JMASK_TRANS_1_1;
	job_mask_table["Trans_1_2_Class"] = (int) JMASK_TRANS_1_2;
	job_mask_table["Trans_2_1_Class"] = (int) JMASK_TRANS_2_1;
	job_mask_table["Trans_2_2_Class"] = (int) JMASK_TRANS_2_2;
	job_mask_table["3_1_Class"] = (int) JMASK_3_1;
	job_mask_table["3_2_Class"] = (int) JMASK_3_2;
	job_mask_table["Trans_3_1_Class"] = (int) JMASK_TRANS_3_1;
	job_mask_table["Trans_3_2_Class"] = (int) JMASK_TRANS_3_2;
	job_mask_table["Baby_3_1_Class"] = (int) JMASK_BABY_3_1;
	job_mask_table["Baby_3_3_Class"] = (int) JMASK_BABY_3_2;
	job_mask_table["ExpandedClass"] = (int) JMASK_EXPANDED;
	job_mask_table["ExpandedBabyClass"] = (int) JMASK_EXPANDED_BABY;
	job_mask_table["Expanded_2_1_Class"] = (int) JMASK_EXPANDED_2_1;
	job_mask_table["Expanded_2_2_Class"] = (int) JMASK_EXPANDED_2_2;

	job_mask_table["NormalClass"] = (int) JMASK_NORMAL;
	job_mask_table["BabyClass"] = (int) JMASK_BABY;
	job_mask_table["TransClass"] = (int) JMASK_TRANS;
	job_mask_table["ThirdClass"] = (int) JMASK_3;
	job_mask_table["TransThirdClass"] = (int) JMASK_TRANS_3;
	job_mask_table["BabyThirdClass"] = (int) JMASK_BABY_3;

	// 2-1 Jobs
	job_mask_table["Knight"] = (int) JMASK_KNIGHT;
	job_mask_table["Wizard"] = (int) JMASK_WIZARD;
	job_mask_table["Hunter"] = (int) JMASK_HUNTER;
	job_mask_table["Priest"] = (int) JMASK_PRIEST;
	job_mask_table["Blacksmith"] = (int) JMASK_BLACKSMITH;
	job_mask_table["Assassin"] = (int) JMASK_ASSASSIN;
	job_mask_table["DeathKnight"] = (int) JMASK_DEATH_KNIGHT;

	// 2-2 Jobs
	job_mask_table["Crusader"] = (int) JMASK_CRUSADER;
	job_mask_table["Sage"] = (int) JMASK_SAGE;
	job_mask_table["BardOrDancer"] = (int) JMASK_BARDDANCER;
	job_mask_table["Monk"] = (int) JMASK_MONK;
	job_mask_table["Alchemist"] = (int) JMASK_ALCHEMIST;
	job_mask_table["Rogue"] = (int) JMASK_ROGUE;
	job_mask_table["DarkCollector"] = (int) JMASK_DARK_COLLECTOR;

	//Trans Novice And Trans 1-1 J
	job_mask_table["HighNovice"] = (int) JMASK_NOVICE_HIGH;
	job_mask_table["HighSwordman"] = (int) JMASK_SWORDMAN_HIGH;
	job_mask_table["HighMagician"] = (int) JMASK_MAGE_HIGH;
	job_mask_table["HighArcher"] = (int) JMASK_ARCHER_HIGH;
	job_mask_table["HighAcolyte"] = (int) JMASK_ACOLYTE_HIGH;
	job_mask_table["HighMerchant"] = (int) JMASK_MERCHANT_HIGH;
	job_mask_table["HighThief"] = (int) JMASK_THIEF_HIGH;

	//Trans 2-1 Jobs
	job_mask_table["LordKnight"] = (int) JMASK_LORD_KNIGHT;
	job_mask_table["HighWizard"] = (int) JMASK_HIGH_WIZARD;
	job_mask_table["Sniper"] = (int) JMASK_SNIPER;
	job_mask_table["HighPriest"] = (int) JMASK_HIGH_PRIEST;
	job_mask_table["Whitesmith"] = (int) JMASK_WHITESMITH;
	job_mask_table["AssassinCross"] = (int) JMASK_ASSASSIN_CROSS;

	//Trans 2-2 Jobs
	job_mask_table["Paladin"] = (int) JMASK_PALADIN;
	job_mask_table["Professor"] = (int) JMASK_PROFESSOR;
	job_mask_table["ClownOrGypsy"] = (int) JMASK_CLOWNGYPSY;
	job_mask_table["Champion"] = (int) JMASK_CHAMPION;
	job_mask_table["Creator"] = (int) JMASK_CREATOR;
	job_mask_table["Stalker"] = (int) JMASK_STALKER;

	//Baby Novice And Baby 1-1 Job
	job_mask_table["BabyNovice"] = (int) JMASK_BABY_NOVICE;
	job_mask_table["BabySwordman"] = (int) JMASK_BABY_SWORDMAN;
	job_mask_table["BabyMage"] = (int) JMASK_BABY_MAGE;
	job_mask_table["BabyArcher"] = (int) JMASK_BABY_ARCHER;
	job_mask_table["BabyAcolyte"] = (int) JMASK_BABY_ACOLYTE;
	job_mask_table["BabyMerchant"] = (int) JMASK_BABY_MERCHANT;
	job_mask_table["BabyThief"] = (int) JMASK_BABY_THIEF;

	//Baby 2-1 Jobs
	job_mask_table["BabyKnight"] = (int) JMASK_BABY_KNIGHT;
	job_mask_table["BabyWizard"] = (int) JMASK_BABY_WIZARD;
	job_mask_table["BabyHunter"] = (int) JMASK_BABY_HUNTER;
	job_mask_table["BabyPriest"] = (int) JMASK_BABY_PRIEST;
	job_mask_table["BabyBlacksmith"] = (int) JMASK_BABY_BLACKSMITH;
	job_mask_table["BabyAssassin"] = (int) JMASK_BABY_ASSASSIN;

	//Baby 2-2 Jobs
	job_mask_table["BabyCrusader"] = (int) JMASK_BABY_CRUSADER;
	job_mask_table["BabySage"] = (int) JMASK_BABY_SAGE;
	job_mask_table["BabyBardOrDancer"] = (int) JMASK_BABY_BARDDANCER;
	job_mask_table["BabyMonk"] = (int) JMASK_BABY_MONK;
	job_mask_table["BabyAlchemist"] = (int) JMASK_BABY_ALCHEMIST;
	job_mask_table["BabyRogue"] = (int) JMASK_BABY_ROGUE;

	//3-1 Jobs
	job_mask_table["RuneKnight"] = (int) JMASK_RUNE_KNIGHT;
	job_mask_table["Warlock"] = (int) JMASK_WARLOCK;
	job_mask_table["Ranger"] = (int) JMASK_RANGER;
	job_mask_table["Archbishop"] = (int) JMASK_ARCH_BISHOP;
	job_mask_table["Mechanic"] = (int) JMASK_MECHANIC;
	job_mask_table["GuillotineCross"] = (int) JMASK_GUILLOTINE_CROSS;

	//3-2 Jobs
	job_mask_table["RoyalGuard"] = (int) JMASK_ROYAL_GUARD;
	job_mask_table["Sorcerer"] = (int) JMASK_SORCERER;
	job_mask_table["MinstrelOrWanderer"] = (int) JMASK_MINSTRELWANDERER;
	job_mask_table["Sura"] = (int) JMASK_SURA;
	job_mask_table["Genetic"] = (int) JMASK_GENETIC;
	job_mask_table["ShadowChaser"] = (int) JMASK_SHADOW_CHASER;

	//Trans 3-1 Jobs
	job_mask_table["RuneKnightTrans"] = (int) JMASK_RUNE_KNIGHT_T;
	job_mask_table["WarlockTrans"] = (int) JMASK_WARLOCK_T;
	job_mask_table["RangerTrans"] = (int) JMASK_RANGER_T;
	job_mask_table["ArchbishopTrans"] = (int) JMASK_ARCH_BISHOP_T;
	job_mask_table["MechanicTrans"] = (int) JMASK_MECHANIC_T;
	job_mask_table["GuillotineCrossTrans"] = (int) JMASK_GUILLOTINE_CROSS_T;

	//Trans 3-2 Jobs
	job_mask_table["RoyalGuardTrans"] = (int) JMASK_ROYAL_GUARD_T;
	job_mask_table["SorcererTrans"] = (int) JMASK_SORCERER_T;
	job_mask_table["MinstrelOrWandererTrans"] = (int) JMASK_MINSTRELWANDERER_T;
	job_mask_table["SuraTrans"] = (int) JMASK_SURA_T;
	job_mask_table["GeneticTrans"] = (int) JMASK_GENETIC_T;
	job_mask_table["ShadowChaserTrans"] = (int) JMASK_SHADOW_CHASER_T;

	//Baby 3-1 Jobs
	job_mask_table["BabyRuneKnight"] = (int) JMASK_BABY_RUNE_KNIGHT;
	job_mask_table["BabyWarlock"] = (int) JMASK_BABY_WARLOCK;
	job_mask_table["BabyRanger"] = (int) JMASK_BABY_RANGER;
	job_mask_table["BabyArchbishop"] = (int) JMASK_BABY_ARCH_BISHOP;
	job_mask_table["BabyMechanic"] = (int) JMASK_BABY_MECHANIC;
	job_mask_table["BabyGuillotineCross"] = (int) JMASK_BABY_GUILLOTINE_CROSS;

	//Baby 3-2 Jobs
	job_mask_table["BabyRoyalGuard"] = (int) JMASK_BABY_ROYAL_GUARD;
	job_mask_table["BabySorcerer"] = (int) JMASK_BABY_SORCERER;
	job_mask_table["BabyMinstrelOrWanderer"] = (int) JMASK_BABY_MINSTRELWANDERER;
	job_mask_table["BabySura"] = (int) JMASK_BABY_SURA;
	job_mask_table["BabyGenetic"] = (int) JMASK_BABY_GENETIC;
	job_mask_table["BabyShadowChaser"] = (int) JMASK_BABY_SHADOW_CHASER;

	// Expanded Jobs
	job_mask_table["Taekwon"] = (int) JMASK_TAEKWON;
	job_mask_table["StarGladiator"] = (int) JMASK_STAR_GLADIATOR;
	job_mask_table["SoulLinker"] = (int) JMASK_SOUL_LINKER;
	job_mask_table["SuperNovice"] = (int) JMASK_SUPER_NOVICE;
	job_mask_table["SuperNoviceExpanded"] = (int) JMASK_SUPER_NOVICE_E;
	job_mask_table["SuperBaby"] = (int) JMASK_SUPER_BABY;
	job_mask_table["SuperBabyExpanded"] = (int) JMASK_SUPER_BABY_E;
	job_mask_table["Gunslinger"] = (int) JMASK_GUNSLINGER;
	job_mask_table["Rebellion"] = (int) JMASK_REBELLION;
	job_mask_table["Ninja"] = (int) JMASK_NINJA;
	job_mask_table["KagerouOrOboro"] = (int) JMASK_KAGEROUOBORO;
	job_mask_table["All"] = (int) JMASK_ALL;
}

void UnitComponent::sync_data_types(std::shared_ptr<sol::state> state)
{
	sol::usertype<Horizon::Zone::Traits::Attribute> config_3 = state->new_usertype<Horizon::Zone::Traits::Attribute>("Attribute");
	config_3["add_base"] = &Horizon::Zone::Traits::Attribute::add_base;
	config_3["sub_base"] = &Horizon::Zone::Traits::Attribute::sub_base;
	config_3["add_equip"] = &Horizon::Zone::Traits::Attribute::add_equip;
	config_3["sub_equip"] = &Horizon::Zone::Traits::Attribute::sub_equip;
	config_3["add_status"] = &Horizon::Zone::Traits::Attribute::add_status;
	config_3["sub_status"] = &Horizon::Zone::Traits::Attribute::sub_status;
	config_3["total"] = &Horizon::Zone::Traits::Attribute::total;

    sol::usertype<Horizon::Zone::Traits::Status> config_4 = state->new_usertype<Horizon::Zone::Traits::Status>("Status");
    config_4["strength"] = &Horizon::Zone::Traits::Status::strength;
    config_4["agility"] = &Horizon::Zone::Traits::Status::agility;
    config_4["vitality"] = &Horizon::Zone::Traits::Status::vitality;
    config_4["dexterity"] = &Horizon::Zone::Traits::Status::dexterity;
    config_4["intelligence"] = &Horizon::Zone::Traits::Status::intelligence;
    config_4["luck"] = &Horizon::Zone::Traits::Status::luck;
    config_4["max_hp"] = &Horizon::Zone::Traits::Status::max_hp;
    config_4["max_sp"] = &Horizon::Zone::Traits::Status::max_sp;
    config_4["current_hp"] = &Horizon::Zone::Traits::Status::current_hp;
    config_4["current_sp"] = &Horizon::Zone::Traits::Status::current_sp;
    config_4["base_level"] = &Horizon::Zone::Traits::Status::base_level;
    config_4["job_level"] = &Horizon::Zone::Traits::Status::job_level;
    config_4["base_experience"] = &Horizon::Zone::Traits::Status::base_experience;
    config_4["job_experience"] = &Horizon::Zone::Traits::Status::job_experience;
    config_4["next_base_experience"] = &Horizon::Zone::Traits::Status::next_base_experience;
    config_4["next_job_experience"] = &Horizon::Zone::Traits::Status::next_job_experience;
    config_4["movement_speed"] = &Horizon::Zone::Traits::Status::movement_speed;
    config_4["max_weight"] = &Horizon::Zone::Traits::Status::max_weight;
    config_4["current_weight"] = &Horizon::Zone::Traits::Status::current_weight;
    config_4["hair_color"] = &Horizon::Zone::Traits::Status::hair_color;
    config_4["cloth_color"] = &Horizon::Zone::Traits::Status::cloth_color;
    config_4["weapon_sprite"] = &Horizon::Zone::Traits::Status::weapon_sprite;
    config_4["shield_sprite"] = &Horizon::Zone::Traits::Status::shield_sprite;
    config_4["robe_sprite"] = &Horizon::Zone::Traits::Status::robe_sprite;
    config_4["head_top_sprite"] = &Horizon::Zone::Traits::Status::head_top_sprite;
    config_4["head_mid_sprite"] = &Horizon::Zone::Traits::Status::head_mid_sprite;
    config_4["head_bottom_sprite"] = &Horizon::Zone::Traits::Status::head_bottom_sprite;
    config_4["hair_style"] = &Horizon::Zone::Traits::Status::hair_style;
    config_4["body_style"] = &Horizon::Zone::Traits::Status::body_style;
    config_4["status_point"] = &Horizon::Zone::Traits::Status::status_point;
    config_4["skill_point"] = &Horizon::Zone::Traits::Status::skill_point;
	config_4["zeny"] = &Horizon::Zone::Traits::Status::zeny;

	sol::usertype<Combat> config_30 = state->new_usertype<Combat>("Combat",
		sol::constructors<Combat(std::shared_ptr<Unit>, std::shared_ptr<Unit>)>());
	config_30["source"] = &Combat::unit;
	config_30["target"] = &Combat::target;

    sol::usertype<Horizon::Zone::Traits::BaseLevel> config_5 = state->new_usertype<Horizon::Zone::Traits::BaseLevel>("BaseLevel");
    config_5["attribute"] = [](std::shared_ptr<Horizon::Zone::Traits::BaseLevel> t) { return std::static_pointer_cast<Horizon::Zone::Traits::Attribute>(t); };
    config_5["add"] = &Horizon::Zone::Traits::BaseLevel::add_base;
    config_5["sub"] = &Horizon::Zone::Traits::BaseLevel::sub_base;
    config_5["get"] = &Horizon::Zone::Traits::BaseLevel::get_base;
    config_5["set"] = &Horizon::Zone::Traits::BaseLevel::set_base;
    sol::usertype<Horizon::Zone::Traits::JobLevel> config_6 = state->new_usertype<Horizon::Zone::Traits::JobLevel>("JobLevel");
    config_6["attribute"] = [](std::shared_ptr<Horizon::Zone::Traits::JobLevel> t) { return std::static_pointer_cast<Horizon::Zone::Traits::Attribute>(t); };
    config_6["add"] = &Horizon::Zone::Traits::JobLevel::add_base;
    config_6["sub"] = &Horizon::Zone::Traits::JobLevel::sub_base;
    config_6["get"] = &Horizon::Zone::Traits::JobLevel::get_base;
    config_6["set"] = &Horizon::Zone::Traits::JobLevel::set_base;
    sol::usertype<Horizon::Zone::Traits::MaxHP> config_7 = state->new_usertype<Horizon::Zone::Traits::MaxHP>("MaxHP");
    config_7["attribute"] = [](std::shared_ptr<Horizon::Zone::Traits::MaxHP> t) { return std::static_pointer_cast<Horizon::Zone::Traits::Attribute>(t); };
    config_7["add"] = &Horizon::Zone::Traits::MaxHP::add_base;
    config_7["sub"] = &Horizon::Zone::Traits::MaxHP::sub_base;
    config_7["get"] = &Horizon::Zone::Traits::MaxHP::get_base;
    config_7["set"] = &Horizon::Zone::Traits::MaxHP::set_base;
    sol::usertype<Horizon::Zone::Traits::MaxSP> config_8 = state->new_usertype<Horizon::Zone::Traits::MaxSP>("MaxSP");
    config_8["attribute"] = [](std::shared_ptr<Horizon::Zone::Traits::MaxSP> t) { return std::static_pointer_cast<Horizon::Zone::Traits::Attribute>(t); };
    config_8["add"] = &Horizon::Zone::Traits::MaxSP::add_base;
    config_8["sub"] = &Horizon::Zone::Traits::MaxSP::sub_base;
    config_8["get"] = &Horizon::Zone::Traits::MaxSP::get_base;
    config_8["set"] = &Horizon::Zone::Traits::MaxSP::set_base;
    sol::usertype<Horizon::Zone::Traits::CurrentHP> config_9 = state->new_usertype<Horizon::Zone::Traits::CurrentHP>("CurrentHP");
    config_9["attribute"] = [](std::shared_ptr<Horizon::Zone::Traits::CurrentHP> t) { return std::static_pointer_cast<Horizon::Zone::Traits::Attribute>(t); };
    config_9["add"] = &Horizon::Zone::Traits::CurrentHP::add_base;
    config_9["sub"] = &Horizon::Zone::Traits::CurrentHP::sub_base;
    config_9["get"] = &Horizon::Zone::Traits::CurrentHP::get_base;
    config_9["set"] = &Horizon::Zone::Traits::CurrentHP::set_base;
    sol::usertype<Horizon::Zone::Traits::CurrentSP> config_10 = state->new_usertype<Horizon::Zone::Traits::CurrentSP>("CurrentSP");
    config_10["attribute"] = [](std::shared_ptr<Horizon::Zone::Traits::CurrentHP> t) { return std::static_pointer_cast<Horizon::Zone::Traits::Attribute>(t); };
    config_10["add"] = &Horizon::Zone::Traits::CurrentSP::add_base;
    config_10["sub"] = &Horizon::Zone::Traits::CurrentSP::sub_base;
    config_10["get"] = &Horizon::Zone::Traits::CurrentSP::get_base;
    config_10["set"] = &Horizon::Zone::Traits::CurrentSP::set_base;
    sol::usertype<Horizon::Zone::Traits::MovementSpeed> config_11 = state->new_usertype<Horizon::Zone::Traits::MovementSpeed>("MovementSpeed");
    config_11["attribute"] = [](std::shared_ptr<Horizon::Zone::Traits::MovementSpeed> t) { return std::static_pointer_cast<Horizon::Zone::Traits::Attribute>(t); };
    config_11["add"] = &Horizon::Zone::Traits::MovementSpeed::add_base;
    config_11["sub"] = &Horizon::Zone::Traits::MovementSpeed::sub_base;
    config_11["get"] = &Horizon::Zone::Traits::MovementSpeed::get_base;
    config_11["set"] = &Horizon::Zone::Traits::MovementSpeed::set_base;
    sol::usertype<Horizon::Zone::Traits::MaxWeight> config_12 = state->new_usertype<Horizon::Zone::Traits::MaxWeight>("MaxWeight");
    config_12["attribute"] = [](std::shared_ptr<Horizon::Zone::Traits::MaxWeight> t) { return std::static_pointer_cast<Horizon::Zone::Traits::Attribute>(t); };
    config_12["add"] = &Horizon::Zone::Traits::MaxWeight::add_base;
    config_12["sub"] = &Horizon::Zone::Traits::MaxWeight::sub_base;
    config_12["get"] = &Horizon::Zone::Traits::MaxWeight::get_base;
    config_12["set"] = &Horizon::Zone::Traits::MaxWeight::set_base;
    sol::usertype<Horizon::Zone::Traits::CurrentWeight> config_13 = state->new_usertype<Horizon::Zone::Traits::CurrentWeight>("CurrentWeight");
    config_13["attribute"] = [](std::shared_ptr<Horizon::Zone::Traits::CurrentWeight> t) { return std::static_pointer_cast<Horizon::Zone::Traits::Attribute>(t); };
    config_13["add"] = &Horizon::Zone::Traits::CurrentWeight::add_base;
    config_13["sub"] = &Horizon::Zone::Traits::CurrentWeight::sub_base;
    config_13["get"] = &Horizon::Zone::Traits::CurrentWeight::get_base;
    config_13["set"] = &Horizon::Zone::Traits::CurrentWeight::set_base;
    sol::usertype<Horizon::Zone::Traits::Strength> config_14 = state->new_usertype<Horizon::Zone::Traits::Strength>("Strength");
    config_14["attribute"] = [](std::shared_ptr<Horizon::Zone::Traits::Strength> t) { return std::static_pointer_cast<Horizon::Zone::Traits::Attribute>(t); };
    config_14["add"] = &Horizon::Zone::Traits::Strength::add_base;
    config_14["sub"] = &Horizon::Zone::Traits::Strength::sub_base;
    config_14["get"] = &Horizon::Zone::Traits::Strength::get_base;
    config_14["set"] = &Horizon::Zone::Traits::Strength::set_base;
    sol::usertype<Horizon::Zone::Traits::Agility> config_15 = state->new_usertype<Horizon::Zone::Traits::Agility>("Agility");
    config_15["attribute"] = [](std::shared_ptr<Horizon::Zone::Traits::Agility> t) { return std::static_pointer_cast<Horizon::Zone::Traits::Attribute>(t); };
    config_15["add"] = &Horizon::Zone::Traits::Agility::add_base;
    config_15["sub"] = &Horizon::Zone::Traits::Agility::sub_base;
    config_15["get"] = &Horizon::Zone::Traits::Agility::get_base;
    config_15["set"] = &Horizon::Zone::Traits::Agility::set_base;
    sol::usertype<Horizon::Zone::Traits::Vitality> config_16 = state->new_usertype<Horizon::Zone::Traits::Vitality>("Vitality");
    config_16["attribute"] = [](std::shared_ptr<Horizon::Zone::Traits::Vitality> t) { return std::static_pointer_cast<Horizon::Zone::Traits::Attribute>(t); };
    config_16["add"] = &Horizon::Zone::Traits::Vitality::add_base;
    config_16["sub"] = &Horizon::Zone::Traits::Vitality::sub_base;
    config_16["get"] = &Horizon::Zone::Traits::Vitality::get_base;
    config_16["set"] = &Horizon::Zone::Traits::Vitality::set_base;
    sol::usertype<Horizon::Zone::Traits::Intelligence> config_17 = state->new_usertype<Horizon::Zone::Traits::Intelligence>("Intelligence");
    config_17["attribute"] = [](std::shared_ptr<Horizon::Zone::Traits::Intelligence> t) { return std::static_pointer_cast<Horizon::Zone::Traits::Attribute>(t); };
    config_17["add"] = &Horizon::Zone::Traits::Intelligence::add_base;
    config_17["sub"] = &Horizon::Zone::Traits::Intelligence::sub_base;
    config_17["get"] = &Horizon::Zone::Traits::Intelligence::get_base;
    config_17["set"] = &Horizon::Zone::Traits::Intelligence::set_base;
    sol::usertype<Horizon::Zone::Traits::Dexterity> config_18 = state->new_usertype<Horizon::Zone::Traits::Dexterity>("Dexterity");
    config_18["attribute"] = [](std::shared_ptr<Horizon::Zone::Traits::Dexterity> t) { return std::static_pointer_cast<Horizon::Zone::Traits::Attribute>(t); };
    config_18["add"] = &Horizon::Zone::Traits::Dexterity::add_base;
    config_18["sub"] = &Horizon::Zone::Traits::Dexterity::sub_base;
    config_18["get"] = &Horizon::Zone::Traits::Dexterity::get_base;
    config_18["set"] = &Horizon::Zone::Traits::Dexterity::set_base;
    sol::usertype<Horizon::Zone::Traits::Luck> config_19 = state->new_usertype<Horizon::Zone::Traits::Luck>("Luck");
    config_19["attribute"] = [](std::shared_ptr<Horizon::Zone::Traits::Luck> t) { return std::static_pointer_cast<Horizon::Zone::Traits::Attribute>(t); };
    config_19["add"] = &Horizon::Zone::Traits::Luck::add_base;
    config_19["sub"] = &Horizon::Zone::Traits::Luck::sub_base;
    config_19["get"] = &Horizon::Zone::Traits::Luck::get_base;
    config_19["set"] = &Horizon::Zone::Traits::Luck::set_base;
    sol::usertype<Horizon::Zone::Traits::BaseExperience> config_20 = state->new_usertype<Horizon::Zone::Traits::BaseExperience>("BaseExperience");
    config_20["attribute"] = [](std::shared_ptr<Horizon::Zone::Traits::BaseExperience> t) { return std::static_pointer_cast<Horizon::Zone::Traits::Attribute>(t); };
    config_20["add"] = &Horizon::Zone::Traits::BaseExperience::add_base;
    config_20["sub"] = &Horizon::Zone::Traits::BaseExperience::sub_base;
    config_20["get"] = &Horizon::Zone::Traits::BaseExperience::get_base;
    config_20["set"] = &Horizon::Zone::Traits::BaseExperience::set_base;
    sol::usertype<Horizon::Zone::Traits::JobExperience> config_21 = state->new_usertype<Horizon::Zone::Traits::JobExperience>("JobExperience");
    config_21["attribute"] = [](std::shared_ptr<Horizon::Zone::Traits::JobExperience> t) { return std::static_pointer_cast<Horizon::Zone::Traits::Attribute>(t); };
    config_21["add"] = &Horizon::Zone::Traits::JobExperience::add_base;
    config_21["sub"] = &Horizon::Zone::Traits::JobExperience::sub_base;
    config_21["get"] = &Horizon::Zone::Traits::JobExperience::get_base;
    config_21["set"] = &Horizon::Zone::Traits::JobExperience::set_base;
    sol::usertype<Horizon::Zone::Traits::NextBaseExperience> config_22 = state->new_usertype<Horizon::Zone::Traits::NextBaseExperience>("NextBaseExperience");
    config_22["attribute"] = [](std::shared_ptr<Horizon::Zone::Traits::NextBaseExperience> t) { return std::static_pointer_cast<Horizon::Zone::Traits::Attribute>(t); };
    config_22["add"] = &Horizon::Zone::Traits::NextBaseExperience::add_base;
    config_22["sub"] = &Horizon::Zone::Traits::NextBaseExperience::sub_base;
    config_22["get"] = &Horizon::Zone::Traits::NextBaseExperience::get_base;
    config_22["set"] = &Horizon::Zone::Traits::NextBaseExperience::set_base;
    sol::usertype<Horizon::Zone::Traits::NextJobExperience> config_23 = state->new_usertype<Horizon::Zone::Traits::NextJobExperience>("NextJobExperience");
    config_23["attribute"] = [](std::shared_ptr<Horizon::Zone::Traits::NextJobExperience> t) { return std::static_pointer_cast<Horizon::Zone::Traits::Attribute>(t); };
    config_23["add"] = &Horizon::Zone::Traits::NextJobExperience::add_base;
    config_23["sub"] = &Horizon::Zone::Traits::NextJobExperience::sub_base;
    config_23["get"] = &Horizon::Zone::Traits::NextJobExperience::get_base;
    config_23["set"] = &Horizon::Zone::Traits::NextJobExperience::set_base;
    sol::usertype<Horizon::Zone::Traits::StatusPoint> config_24 = state->new_usertype<Horizon::Zone::Traits::StatusPoint>("StatusPoint");
    config_24["attribute"] = [](std::shared_ptr<Horizon::Zone::Traits::StatusPoint> t) { return std::static_pointer_cast<Horizon::Zone::Traits::Attribute>(t); };
    config_24["add"] = &Horizon::Zone::Traits::StatusPoint::add_base;
    config_24["sub"] = &Horizon::Zone::Traits::StatusPoint::sub_base;
    config_24["get"] = &Horizon::Zone::Traits::StatusPoint::get_base;
    config_24["set"] = &Horizon::Zone::Traits::StatusPoint::set_base;
    sol::usertype<Horizon::Zone::Traits::SkillPoint> config_25 = state->new_usertype<Horizon::Zone::Traits::SkillPoint>("SkillPoint");
    config_25["attribute"] = [](std::shared_ptr<Horizon::Zone::Traits::SkillPoint> t) { return std::static_pointer_cast<Horizon::Zone::Traits::Attribute>(t); };
    config_25["add"] = &Horizon::Zone::Traits::SkillPoint::add_base;
    config_25["sub"] = &Horizon::Zone::Traits::SkillPoint::sub_base;
    config_25["get"] = &Horizon::Zone::Traits::SkillPoint::get_base;
    config_25["set"] = &Horizon::Zone::Traits::SkillPoint::set_base;
    sol::usertype<Horizon::Zone::Traits::Zeny> config_26 = state->new_usertype<Horizon::Zone::Traits::Zeny>("Zeny");
    config_26["attribute"] = [](std::shared_ptr<Horizon::Zone::Traits::Zeny> t) { return std::static_pointer_cast<Horizon::Zone::Traits::Attribute>(t); };
    config_26["add"] = &Horizon::Zone::Traits::Zeny::add_base;
    config_26["sub"] = &Horizon::Zone::Traits::Zeny::sub_base;
    config_26["get"] = &Horizon::Zone::Traits::Zeny::get_base;
    config_26["set"] = &Horizon::Zone::Traits::Zeny::set_base;
    sol::usertype<Horizon::Zone::Traits::Honor> config_27 = state->new_usertype<Horizon::Zone::Traits::Honor>("Honor");
    config_27["attribute"] = [](std::shared_ptr<Horizon::Zone::Traits::Honor> t) { return std::static_pointer_cast<Horizon::Zone::Traits::Attribute>(t); };
    config_27["add"] = &Horizon::Zone::Traits::Honor::add_base;
    config_27["sub"] = &Horizon::Zone::Traits::Honor::sub_base;
    config_27["get"] = &Horizon::Zone::Traits::Honor::get_base;
    config_27["set"] = &Horizon::Zone::Traits::Honor::set_base;
    sol::usertype<Horizon::Zone::Traits::Manner> config_28 = state->new_usertype<Horizon::Zone::Traits::Manner>("Manner");
    config_28["attribute"] = [](std::shared_ptr<Horizon::Zone::Traits::Manner> t) { return std::static_pointer_cast<Horizon::Zone::Traits::Attribute>(t); };
    config_28["add"] = &Horizon::Zone::Traits::Manner::add_base;
    config_28["sub"] = &Horizon::Zone::Traits::Manner::sub_base;
    config_28["get"] = &Horizon::Zone::Traits::Manner::get_base;
    config_28["set"] = &Horizon::Zone::Traits::Manner::set_base;
    sol::usertype<Horizon::Zone::Traits::Virtue> config_29 = state->new_usertype<Horizon::Zone::Traits::Virtue>("Virtue");
    config_29["attribute"] = [](std::shared_ptr<Horizon::Zone::Traits::Virtue> t) { return std::static_pointer_cast<Horizon::Zone::Traits::Attribute>(t); };
    config_29["add"] = &Horizon::Zone::Traits::Virtue::add_base;
    config_29["sub"] = &Horizon::Zone::Traits::Virtue::sub_base;
    config_29["get"] = &Horizon::Zone::Traits::Virtue::get_base;
    config_29["set"] = &Horizon::Zone::Traits::Virtue::set_base;
	sol::usertype<unit_uuid> uuid = state->new_usertype<unit_uuid>("UnitUUID");
	uuid["type"] = &unit_uuid::type;
	uuid["guid"] = &unit_uuid::guid;
	uuid["uid2"] = &unit_uuid::uid2;
	uuid["uid3"] = &unit_uuid::uid3;

	sol::usertype<Unit> config_1 = state->new_usertype<Unit>("Unit");
	config_1["guid"] = &Unit::guid;
	config_1["uuid"] = &Unit::uuid;
	config_1["s_uuid"] = &Unit::s_uuid;
	config_1["set_uuid"] = &Unit::set_uuid;
	config_1["dest_coords"] = &Unit::dest_coords;
	config_1["walk_to_coordinates"] = &Unit::walk_to_coordinates;
	config_1["is_walking"] = &Unit::is_walking;
	config_1["stop_movement"] = &Unit::stop_movement;
	config_1["job_id"] = &Unit::job_id;
	config_1["posture"] = &Unit::posture;
	config_1["set_posture"] = &Unit::set_posture;
	config_1["name"] = &Unit::name;
	config_1["direction"] = &Unit::direction;
	config_1["status"] = &Unit::status;
	config_1["force_movement_stop_internal"] = &Unit::force_movement_stop_internal;
	config_1["map"] = &Unit::map;
	config_1["type"] = &Unit::type;
	config_1["map_coords"] = &Unit::map_coords;
	config_1["grid_coords"] = &Unit::grid_coords;
	config_1["is_in_range_of"] = &Unit::is_in_range_of;
	config_1["notify_nearby_players_of_existence"] = &Unit::notify_nearby_players_of_existence;
	config_1["notify_nearby_players_of_movement"] = &Unit::notify_nearby_players_of_movement;
	config_1["notify_nearby_players_of_spawn"] = &Unit::notify_nearby_players_of_spawn;
	config_1["notify_nearby_players_of_skill_use"] = &Unit::notify_nearby_players_of_skill_use;
	config_1["notify_nearby_players_of_item_drop"] = &Unit::notify_nearby_players_of_item_drop;
	config_1["get_nearby_unit"] = &Unit::get_nearby_unit;
	config_1["status_effect_start"] = &Unit::status_effect_start;
	config_1["status_effect_end"] = &Unit::status_effect_end;
	config_1["get_walk_path"] = &Unit::get_walk_path;
	config_1["is_dead"] = &Unit::is_dead;
	config_1["combat"] = &Unit::combat;
	config_1["combat_registry"] = &Unit::combat_registry;
	config_1["apply_status_change_in_area"] = &Unit::apply_status_change_in_area;
	config_1["remove_status_change_in_area"] = &Unit::remove_status_change_in_area;
	config_1["execute_skill_in_area"] = &Unit::execute_skill_in_area;
	config_1["execute_skill_in_cell"] = &Unit::execute_skill_in_cell;

	sol::usertype<s_unit_skill_use_notifier_config> config_2 = state->new_usertype<s_unit_skill_use_notifier_config>("s_unit_skill_use_notifier_config");
	config_2["source_guid"] = &s_unit_skill_use_notifier_config::source_guid;
	config_2["target_guid"] = &s_unit_skill_use_notifier_config::target_guid;
	config_2["skill_id"] = &s_unit_skill_use_notifier_config::skill_id;
	config_2["skill_lv"] = &s_unit_skill_use_notifier_config::skill_lv;
	config_2["damage_value"] = &s_unit_skill_use_notifier_config::damage_value;
	config_2["display_value"] = &s_unit_skill_use_notifier_config::display_value;
	config_2["start_time"] = &s_unit_skill_use_notifier_config::start_time;
	config_2["attack_motion"] = &s_unit_skill_use_notifier_config::attack_motion;
	config_2["delay_motion"] = &s_unit_skill_use_notifier_config::delay_motion;
	config_2["number_of_hits"] = &s_unit_skill_use_notifier_config::number_of_hits;
	config_2["action_type"] = &s_unit_skill_use_notifier_config::action_type;
	config_2["item_id"] = &s_unit_skill_use_notifier_config::item_id;
	config_2["target_x"] = &s_unit_skill_use_notifier_config::target_x;
	config_2["target_y"] = &s_unit_skill_use_notifier_config::target_y;
	config_2["element"] = &s_unit_skill_use_notifier_config::element;
	config_2["cast_time"] = &s_unit_skill_use_notifier_config::cast_time;

	
    sol::usertype<Horizon::Zone::Bonuses::Bonus> config_31 = state->new_usertype<Horizon::Zone::Bonuses::Bonus>("Bonus",
		sol::constructors<Horizon::Zone::Bonuses::Bonus(std::shared_ptr<Unit>, status_point_type, int)>());
    config_31["attribute"] = [](std::shared_ptr<Horizon::Zone::Bonuses::Bonus> t) { return std::static_pointer_cast<Horizon::Zone::Traits::Attribute>(t); };
    config_31["get"] = &Horizon::Zone::Bonuses::Bonus::get;
    config_31["set"] = &Horizon::Zone::Bonuses::Bonus::set;
	config_31["get_parameter_1"] = &Horizon::Zone::Bonuses::Bonus::get_parameter_1;
	config_31["get_parameter_2"] = &Horizon::Zone::Bonuses::Bonus::get_parameter_2;
	config_31["get_parameter_3"] = &Horizon::Zone::Bonuses::Bonus::get_parameter_3;
	config_31["set_parameter_1"] = &Horizon::Zone::Bonuses::Bonus::set_parameter_1;
	config_31["set_parameter_2"] = &Horizon::Zone::Bonuses::Bonus::set_parameter_2;
	config_31["set_parameter_3"] = &Horizon::Zone::Bonuses::Bonus::set_parameter_3;
	config_31["is_applied"] = &Horizon::Zone::Bonuses::Bonus::is_applied;
	config_31["set_applied"] = &Horizon::Zone::Bonuses::Bonus::set_applied;

	sol::usertype<Horizon::Zone::Bonuses::BonusAllStatus> config_35 = state->new_usertype<Horizon::Zone::Bonuses::BonusAllStatus>("BonusAllStatus",
		sol::constructors<Horizon::Zone::Bonuses::BonusAllStatus(std::shared_ptr<Unit>, int value)>());
	config_35["attribute"] = [](std::shared_ptr<Horizon::Zone::Bonuses::BonusAllStatus> t) { return std::static_pointer_cast<Horizon::Zone::Traits::Attribute>(t); };
	config_35["get"] = &Horizon::Zone::Bonuses::BonusAllStatus::get;
	config_35["set"] = &Horizon::Zone::Bonuses::BonusAllStatus::set;

	sol::usertype<Horizon::Zone::Bonuses::BonusAttackElement> config_36 = state->new_usertype<Horizon::Zone::Bonuses::BonusAttackElement>("BonusAttackElement",
		sol::constructors<Horizon::Zone::Bonuses::BonusAllStatus(std::shared_ptr<Unit>, int)>());
	config_36["attribute"] = [](std::shared_ptr<Horizon::Zone::Bonuses::BonusAttackElement> t) { return std::static_pointer_cast<Horizon::Zone::Traits::Attribute>(t); };
	config_36["get"] = &Horizon::Zone::Bonuses::BonusAttackElement::get;
	config_36["set"] = &Horizon::Zone::Bonuses::BonusAttackElement::set;

	sol::usertype<Horizon::Zone::Bonuses::BonusDefenseElement> config_37 = state->new_usertype<Horizon::Zone::Bonuses::BonusDefenseElement>("BonusDefenseElement",
		sol::constructors<Horizon::Zone::Bonuses::BonusDefenseElement(std::shared_ptr<Unit>, int)>());
	config_37["attribute"] = [](std::shared_ptr<Horizon::Zone::Bonuses::BonusDefenseElement> t) { return std::static_pointer_cast<Horizon::Zone::Traits::Attribute>(t); };
	config_37["get"] = &Horizon::Zone::Bonuses::BonusDefenseElement::get;
	config_37["set"] = &Horizon::Zone::Bonuses::BonusDefenseElement::set;

	sol::usertype<Horizon::Zone::Bonuses::BonusCastPercent> config_38 = state->new_usertype<Horizon::Zone::Bonuses::BonusCastPercent>("BonusCastPercent",
		sol::constructors<Horizon::Zone::Bonuses::BonusCastPercent(std::shared_ptr<Unit>, int)>());
	config_38["attribute"] = [](std::shared_ptr<Horizon::Zone::Bonuses::BonusCastPercent> t) { return std::static_pointer_cast<Horizon::Zone::Traits::Attribute>(t); };
	config_38["get"] = &Horizon::Zone::Bonuses::BonusCastPercent::get;
	config_38["set"] = &Horizon::Zone::Bonuses::BonusCastPercent::set;

	sol::usertype<Horizon::Zone::Bonuses::BonusMaxHPPercent> config_39 = state->new_usertype<Horizon::Zone::Bonuses::BonusMaxHPPercent>("BonusMaxHPPercent",
		sol::constructors<Horizon::Zone::Bonuses::BonusMaxHPPercent(std::shared_ptr<Unit>, int)>());
	config_39["attribute"] = [](std::shared_ptr<Horizon::Zone::Bonuses::BonusMaxHPPercent> t) { return std::static_pointer_cast<Horizon::Zone::Traits::Attribute>(t); };
	config_39["get"] = &Horizon::Zone::Bonuses::BonusMaxHPPercent::get;
	config_39["set"] = &Horizon::Zone::Bonuses::BonusMaxHPPercent::set;

	sol::usertype<Horizon::Zone::Bonuses::BonusMaxSPPercent> config_40 = state->new_usertype<Horizon::Zone::Bonuses::BonusMaxSPPercent>("BonusMaxSPPercent",
		sol::constructors<Horizon::Zone::Bonuses::BonusMaxSPPercent(std::shared_ptr<Unit>, int)>());
	config_40["attribute"] = [](std::shared_ptr<Horizon::Zone::Bonuses::BonusMaxSPPercent> t) { return std::static_pointer_cast<Horizon::Zone::Traits::Attribute>(t); };
	config_40["get"] = &Horizon::Zone::Bonuses::BonusMaxSPPercent::get;
	config_40["set"] = &Horizon::Zone::Bonuses::BonusMaxSPPercent::set;

	sol::usertype<Horizon::Zone::Bonuses::BonusAttackRange> config_41 = state->new_usertype<Horizon::Zone::Bonuses::BonusAttackRange>("BonusAttackRange",
		sol::constructors<Horizon::Zone::Bonuses::BonusAttackRange(std::shared_ptr<Unit>, int)>());
	config_41["attribute"] = [](std::shared_ptr<Horizon::Zone::Bonuses::BonusAttackRange> t) { return std::static_pointer_cast<Horizon::Zone::Traits::Attribute>(t); };
	config_41["get"] = &Horizon::Zone::Bonuses::BonusAttackRange::get;
	config_41["set"] = &Horizon::Zone::Bonuses::BonusAttackRange::set;

	sol::usertype<Horizon::Zone::Bonuses::BonusAttackRangePercent> config_42 = state->new_usertype<Horizon::Zone::Bonuses::BonusAttackRangePercent>("BonusAttackRangePercent",
		sol::constructors<Horizon::Zone::Bonuses::BonusAttackRangePercent(std::shared_ptr<Unit>, int)>());
	config_42["attribute"] = [](std::shared_ptr<Horizon::Zone::Bonuses::BonusAttackRangePercent> t) { return std::static_pointer_cast<Horizon::Zone::Traits::Attribute>(t); };
	config_42["get"] = &Horizon::Zone::Bonuses::BonusAttackRangePercent::get;
	config_42["set"] = &Horizon::Zone::Bonuses::BonusAttackRangePercent::set;

	sol::usertype<Horizon::Zone::Bonuses::BonusAddMovementSpeedPercent> config_43 = state->new_usertype<Horizon::Zone::Bonuses::BonusAddMovementSpeedPercent>("BonusAddMovementSpeedPercent",
		sol::constructors<Horizon::Zone::Bonuses::BonusAddMovementSpeedPercent(std::shared_ptr<Unit>, int)>());
	config_43["attribute"] = [](std::shared_ptr<Horizon::Zone::Bonuses::BonusAddMovementSpeedPercent> t) { return std::static_pointer_cast<Horizon::Zone::Traits::Attribute>(t); };
	config_43["get"] = &Horizon::Zone::Bonuses::BonusAddMovementSpeedPercent::get;
	config_43["set"] = &Horizon::Zone::Bonuses::BonusAddMovementSpeedPercent::set;

	sol::usertype<Horizon::Zone::Bonuses::BonusAttackSpeedPercent> config_44 = state->new_usertype<Horizon::Zone::Bonuses::BonusAttackSpeedPercent>("BonusAttackSpeedPercent",
		sol::constructors<Horizon::Zone::Bonuses::BonusAttackSpeedPercent(std::shared_ptr<Unit>, int)>());
	config_44["attribute"] = [](std::shared_ptr<Horizon::Zone::Bonuses::BonusAttackSpeedPercent> t) { return std::static_pointer_cast<Horizon::Zone::Traits::Attribute>(t); };
	config_44["get"] = &Horizon::Zone::Bonuses::BonusAttackSpeedPercent::get;
	config_44["set"] = &Horizon::Zone::Bonuses::BonusAttackSpeedPercent::set;

	sol::usertype<Horizon::Zone::Bonuses::BonusHPRecoveryPercent> config_45 = state->new_usertype<Horizon::Zone::Bonuses::BonusHPRecoveryPercent>("BonusHPRecoveryPercent",
		sol::constructors<Horizon::Zone::Bonuses::BonusHPRecoveryPercent(std::shared_ptr<Unit>, int)>());
	config_45["attribute"] = [](std::shared_ptr<Horizon::Zone::Bonuses::BonusHPRecoveryPercent> t) { return std::static_pointer_cast<Horizon::Zone::Traits::Attribute>(t); };
	config_45["get"] = &Horizon::Zone::Bonuses::BonusHPRecoveryPercent::get;
	config_45["set"] = &Horizon::Zone::Bonuses::BonusHPRecoveryPercent::set;

	sol::usertype<Horizon::Zone::Bonuses::BonusSPRecoveryPercent> config_46 = state->new_usertype<Horizon::Zone::Bonuses::BonusSPRecoveryPercent>("BonusSPRecoveryPercent",
		sol::constructors<Horizon::Zone::Bonuses::BonusSPRecoveryPercent(std::shared_ptr<Unit>, int)>());
	config_46["attribute"] = [](std::shared_ptr<Horizon::Zone::Bonuses::BonusSPRecoveryPercent> t) { return std::static_pointer_cast<Horizon::Zone::Traits::Attribute>(t); };
	config_46["get"] = &Horizon::Zone::Bonuses::BonusSPRecoveryPercent::get;
	config_46["set"] = &Horizon::Zone::Bonuses::BonusSPRecoveryPercent::set;

	sol::usertype<Horizon::Zone::Bonuses::BonusCriticalDefense> config_47 = state->new_usertype<Horizon::Zone::Bonuses::BonusCriticalDefense>("BonusCriticalDefense",
		sol::constructors<Horizon::Zone::Bonuses::BonusCriticalDefense(std::shared_ptr<Unit>, int)>());
	config_47["attribute"] = [](std::shared_ptr<Horizon::Zone::Bonuses::BonusCriticalDefense> t) { return std::static_pointer_cast<Horizon::Zone::Traits::Attribute>(t); };
	config_47["get"] = &Horizon::Zone::Bonuses::BonusCriticalDefense::get;
	config_47["set"] = &Horizon::Zone::Bonuses::BonusCriticalDefense::set;

	sol::usertype<Horizon::Zone::Bonuses::BonusMeleeDefense> config_48 = state->new_usertype<Horizon::Zone::Bonuses::BonusMeleeDefense>("BonusMeleeDefense",
		sol::constructors<Horizon::Zone::Bonuses::BonusMeleeDefense(std::shared_ptr<Unit>, int)>());
	config_48["attribute"] = [](std::shared_ptr<Horizon::Zone::Bonuses::BonusMeleeDefense> t) { return std::static_pointer_cast<Horizon::Zone::Traits::Attribute>(t); };
	config_48["get"] = &Horizon::Zone::Bonuses::BonusMeleeDefense::get;
	config_48["set"] = &Horizon::Zone::Bonuses::BonusMeleeDefense::set;

	sol::usertype<Horizon::Zone::Bonuses::BonusRangedDefense> config_49 = state->new_usertype<Horizon::Zone::Bonuses::BonusRangedDefense>("BonusRangedDefense",
		sol::constructors<Horizon::Zone::Bonuses::BonusRangedDefense(std::shared_ptr<Unit>, int)>());
	config_49["attribute"] = [](std::shared_ptr<Horizon::Zone::Bonuses::BonusRangedDefense> t) { return std::static_pointer_cast<Horizon::Zone::Traits::Attribute>(t); };
	config_49["get"] = &Horizon::Zone::Bonuses::BonusRangedDefense::get;
	config_49["set"] = &Horizon::Zone::Bonuses::BonusRangedDefense::set;

	sol::usertype<Horizon::Zone::Bonuses::BonusDoubleAttackPercent> config_50 = state->new_usertype<Horizon::Zone::Bonuses::BonusDoubleAttackPercent>("BonusDoubleAttackPercent",
		sol::constructors<Horizon::Zone::Bonuses::BonusDoubleAttackPercent(std::shared_ptr<Unit>, int)>());
	config_50["attribute"] = [](std::shared_ptr<Horizon::Zone::Bonuses::BonusDoubleAttackPercent> t) { return std::static_pointer_cast<Horizon::Zone::Traits::Attribute>(t); };
	config_50["get"] = &Horizon::Zone::Bonuses::BonusDoubleAttackPercent::get;
	config_50["set"] = &Horizon::Zone::Bonuses::BonusDoubleAttackPercent::set;

	sol::usertype<Horizon::Zone::Bonuses::BonusMagicAttackPercent> config_51 = state->new_usertype<Horizon::Zone::Bonuses::BonusMagicAttackPercent>("BonusMagicAttackPercent",
		sol::constructors<Horizon::Zone::Bonuses::BonusMagicAttackPercent(std::shared_ptr<Unit>, int)>());
	config_51["attribute"] = [](std::shared_ptr<Horizon::Zone::Bonuses::BonusMagicAttackPercent> t) { return std::static_pointer_cast<Horizon::Zone::Traits::Attribute>(t); };
	config_51["get"] = &Horizon::Zone::Bonuses::BonusMagicAttackPercent::get;
	config_51["set"] = &Horizon::Zone::Bonuses::BonusMagicAttackPercent::set;

	sol::usertype<Horizon::Zone::Bonuses::BonusAttackPercent> config_52 = state->new_usertype<Horizon::Zone::Bonuses::BonusAttackPercent>("BonusAttackPercent",
		sol::constructors<Horizon::Zone::Bonuses::BonusAttackPercent(std::shared_ptr<Unit>, int)>());
	config_52["attribute"] = [](std::shared_ptr<Horizon::Zone::Bonuses::BonusAttackPercent> t) { return std::static_pointer_cast<Horizon::Zone::Traits::Attribute>(t); };
	config_52["get"] = &Horizon::Zone::Bonuses::BonusAttackPercent::get;
	config_52["set"] = &Horizon::Zone::Bonuses::BonusAttackPercent::set;

	sol::usertype<Horizon::Zone::Bonuses::BonusMagicDefensePercent> config_53 = state->new_usertype<Horizon::Zone::Bonuses::BonusMagicDefensePercent>("BonusMagicDefensePercent",
		sol::constructors<Horizon::Zone::Bonuses::BonusMagicDefensePercent(std::shared_ptr<Unit>, int)>());
	config_53["attribute"] = [](std::shared_ptr<Horizon::Zone::Bonuses::BonusMagicDefensePercent> t) { return std::static_pointer_cast<Horizon::Zone::Traits::Attribute>(t); };
	config_53["get"] = &Horizon::Zone::Bonuses::BonusMagicDefensePercent::get;
	config_53["set"] = &Horizon::Zone::Bonuses::BonusMagicDefensePercent::set;

	sol::usertype<Horizon::Zone::Bonuses::BonusMiscDefensePercent> config_55 = state->new_usertype<Horizon::Zone::Bonuses::BonusMiscDefensePercent>("BonusMiscDefensePercent",
		sol::constructors<Horizon::Zone::Bonuses::BonusMiscDefensePercent(std::shared_ptr<Unit>, int)>());
	config_55["attribute"] = [](std::shared_ptr<Horizon::Zone::Bonuses::BonusMiscDefensePercent> t) { return std::static_pointer_cast<Horizon::Zone::Traits::Attribute>(t); };
	config_55["get"] = &Horizon::Zone::Bonuses::BonusMiscDefensePercent::get;
	config_55["set"] = &Horizon::Zone::Bonuses::BonusMiscDefensePercent::set;
	
	sol::usertype<Horizon::Zone::Bonuses::BonusPerfectHitPercent> config_56 = state->new_usertype<Horizon::Zone::Bonuses::BonusPerfectHitPercent>("BonusPerfectHitPercent",
		sol::constructors<Horizon::Zone::Bonuses::BonusPerfectHitPercent(std::shared_ptr<Unit>, int)>());
	config_56["attribute"] = [](std::shared_ptr<Horizon::Zone::Bonuses::BonusPerfectHitPercent> t) { return std::static_pointer_cast<Horizon::Zone::Traits::Attribute>(t); };
	config_56["get"] = &Horizon::Zone::Bonuses::BonusPerfectHitPercent::get;
	config_56["set"] = &Horizon::Zone::Bonuses::BonusPerfectHitPercent::set;

	sol::usertype<Horizon::Zone::Bonuses::BonusCriticalPercent> config_57 = state->new_usertype<Horizon::Zone::Bonuses::BonusCriticalPercent>("BonusCriticalPercent",
		sol::constructors<Horizon::Zone::Bonuses::BonusCriticalPercent(std::shared_ptr<Unit>, int)>());
	config_57["attribute"] = [](std::shared_ptr<Horizon::Zone::Bonuses::BonusCriticalPercent> t) { return std::static_pointer_cast<Horizon::Zone::Traits::Attribute>(t); };
	config_57["get"] = &Horizon::Zone::Bonuses::BonusCriticalPercent::get;
	config_57["set"] = &Horizon::Zone::Bonuses::BonusCriticalPercent::set;

	sol::usertype<Horizon::Zone::Bonuses::BonusGetZenyNum> config_58 = state->new_usertype<Horizon::Zone::Bonuses::BonusGetZenyNum>("BonusGetZenyNum",
		sol::constructors<Horizon::Zone::Bonuses::BonusGetZenyNum(std::shared_ptr<Unit>, int)>());
	config_58["attribute"] = [](std::shared_ptr<Horizon::Zone::Bonuses::BonusGetZenyNum> t) { return std::static_pointer_cast<Horizon::Zone::Traits::Attribute>(t); };
	config_58["get"] = &Horizon::Zone::Bonuses::BonusGetZenyNum::get;
	config_58["set"] = &Horizon::Zone::Bonuses::BonusGetZenyNum::set;

	sol::usertype<Horizon::Zone::Bonuses::BonusAttackOnDefenseRatioForElement> config_59 = state->new_usertype<Horizon::Zone::Bonuses::BonusAttackOnDefenseRatioForElement>("BonusAttackOnDefenseRatioForElement",
		sol::constructors<Horizon::Zone::Bonuses::BonusAttackOnDefenseRatioForElement(std::shared_ptr<Unit>, int)>());
	config_59["attribute"] = [](std::shared_ptr<Horizon::Zone::Bonuses::BonusAttackOnDefenseRatioForElement> t) { return std::static_pointer_cast<Horizon::Zone::Traits::Attribute>(t); };
	config_59["get"] = &Horizon::Zone::Bonuses::BonusAttackOnDefenseRatioForElement::get;
	config_59["set"] = &Horizon::Zone::Bonuses::BonusAttackOnDefenseRatioForElement::set;

	sol::usertype<Horizon::Zone::Bonuses::BonusAttackOnDefenseRatioForRace> config_60 = state->new_usertype<Horizon::Zone::Bonuses::BonusAttackOnDefenseRatioForRace>("BonusAttackOnDefenseRatioForRace",
		sol::constructors<Horizon::Zone::Bonuses::BonusAttackOnDefenseRatioForRace(std::shared_ptr<Unit>, int)>());
	config_60["attribute"] = [](std::shared_ptr<Horizon::Zone::Bonuses::BonusAttackOnDefenseRatioForRace> t) { return std::static_pointer_cast<Horizon::Zone::Traits::Attribute>(t); };
	config_60["get"] = &Horizon::Zone::Bonuses::BonusAttackOnDefenseRatioForRace::get;
	config_60["set"] = &Horizon::Zone::Bonuses::BonusAttackOnDefenseRatioForRace::set;

	sol::usertype<Horizon::Zone::Bonuses::BonusHitPercent> config_61 = state->new_usertype<Horizon::Zone::Bonuses::BonusHitPercent>("BonusHitPercent",
		sol::constructors<Horizon::Zone::Bonuses::BonusHitPercent(std::shared_ptr<Unit>, int)>());
	config_61["attribute"] = [](std::shared_ptr<Horizon::Zone::Bonuses::BonusHitPercent> t) { return std::static_pointer_cast<Horizon::Zone::Traits::Attribute>(t); };
	config_61["get"] = &Horizon::Zone::Bonuses::BonusHitPercent::get;
	config_61["set"] = &Horizon::Zone::Bonuses::BonusHitPercent::set;

	sol::usertype<Horizon::Zone::Bonuses::BonusFleePercent> config_62 = state->new_usertype<Horizon::Zone::Bonuses::BonusFleePercent>("BonusFleePercent",
		sol::constructors<Horizon::Zone::Bonuses::BonusFleePercent(std::shared_ptr<Unit>, int)>());
	config_62["attribute"] = [](std::shared_ptr<Horizon::Zone::Bonuses::BonusFleePercent> t) { return std::static_pointer_cast<Horizon::Zone::Traits::Attribute>(t); };
	config_62["get"] = &Horizon::Zone::Bonuses::BonusFleePercent::get;
	config_62["set"] = &Horizon::Zone::Bonuses::BonusFleePercent::set;

	sol::usertype<Horizon::Zone::Bonuses::BonusPerfectDodgePercent> config_63 = state->new_usertype<Horizon::Zone::Bonuses::BonusPerfectDodgePercent>("BonusPerfectDodgePercent",
		sol::constructors<Horizon::Zone::Bonuses::BonusPerfectDodgePercent(std::shared_ptr<Unit>, int)>());
	config_63["attribute"] = [](std::shared_ptr<Horizon::Zone::Bonuses::BonusPerfectDodgePercent> t) { return std::static_pointer_cast<Horizon::Zone::Traits::Attribute>(t); };
	config_63["get"] = &Horizon::Zone::Bonuses::BonusPerfectDodgePercent::get;
	config_63["set"] = &Horizon::Zone::Bonuses::BonusPerfectDodgePercent::set;

	sol::usertype<Horizon::Zone::Bonuses::BonusSoftDefensePercent> config_64 = state->new_usertype<Horizon::Zone::Bonuses::BonusSoftDefensePercent>("BonusSoftDefensePercent",
		sol::constructors<Horizon::Zone::Bonuses::BonusSoftDefensePercent(std::shared_ptr<Unit>, int)>());
	config_64["attribute"] = [](std::shared_ptr<Horizon::Zone::Bonuses::BonusSoftDefensePercent> t) { return std::static_pointer_cast<Horizon::Zone::Traits::Attribute>(t); };
	config_64["get"] = &Horizon::Zone::Bonuses::BonusSoftDefensePercent::get;
	config_64["set"] = &Horizon::Zone::Bonuses::BonusSoftDefensePercent::set;

	sol::usertype<Horizon::Zone::Bonuses::BonusHardDefensePercent> config_65 = state->new_usertype<Horizon::Zone::Bonuses::BonusHardDefensePercent>("BonusHardDefensePercent",
		sol::constructors<Horizon::Zone::Bonuses::BonusHardDefensePercent(std::shared_ptr<Unit>, int)>());
	config_65["attribute"] = [](std::shared_ptr<Horizon::Zone::Bonuses::BonusHardDefensePercent> t) { return std::static_pointer_cast<Horizon::Zone::Traits::Attribute>(t); };
	config_65["get"] = &Horizon::Zone::Bonuses::BonusHardDefensePercent::get;
	config_65["set"] = &Horizon::Zone::Bonuses::BonusHardDefensePercent::set;

	sol::usertype<Horizon::Zone::Bonuses::BonusSoftMagicalDefensePercent> config_66 = state->new_usertype<Horizon::Zone::Bonuses::BonusSoftMagicalDefensePercent>("BonusSoftMagicalDefensePercent",
		sol::constructors<Horizon::Zone::Bonuses::BonusSoftMagicalDefensePercent(std::shared_ptr<Unit>, int)>());
	config_66["attribute"] = [](std::shared_ptr<Horizon::Zone::Bonuses::BonusSoftMagicalDefensePercent> t) { return std::static_pointer_cast<Horizon::Zone::Traits::Attribute>(t); };
	config_66["get"] = &Horizon::Zone::Bonuses::BonusSoftMagicalDefensePercent::get;
	config_66["set"] = &Horizon::Zone::Bonuses::BonusSoftMagicalDefensePercent::set;

	sol::usertype<Horizon::Zone::Bonuses::BonusHardMagicalDefensePercent> config_67 = state->new_usertype<Horizon::Zone::Bonuses::BonusHardMagicalDefensePercent>("BonusHardMagicalDefensePercent",
		sol::constructors<Horizon::Zone::Bonuses::BonusHardMagicalDefensePercent(std::shared_ptr<Unit>, int)>());
	config_67["attribute"] = [](std::shared_ptr<Horizon::Zone::Bonuses::BonusHardMagicalDefensePercent> t) { return std::static_pointer_cast<Horizon::Zone::Traits::Attribute>(t); };
	config_67["get"] = &Horizon::Zone::Bonuses::BonusHardMagicalDefensePercent::get;
	config_67["set"] = &Horizon::Zone::Bonuses::BonusHardMagicalDefensePercent::set;

	sol::usertype<Horizon::Zone::Bonuses::BonusRestartWithFullRecovery> config_68 = state->new_usertype<Horizon::Zone::Bonuses::BonusRestartWithFullRecovery>("BonusRestartWithFullRecovery",
		sol::constructors<Horizon::Zone::Bonuses::BonusRestartWithFullRecovery(std::shared_ptr<Unit>, int)>());
	config_68["attribute"] = [](std::shared_ptr<Horizon::Zone::Bonuses::BonusRestartWithFullRecovery> t) { return std::static_pointer_cast<Horizon::Zone::Traits::Attribute>(t); };
	config_68["get"] = &Horizon::Zone::Bonuses::BonusRestartWithFullRecovery::get;
	config_68["set"] = &Horizon::Zone::Bonuses::BonusRestartWithFullRecovery::set;

	sol::usertype<Horizon::Zone::Bonuses::BonusCastCancelImmunity> config_69 = state->new_usertype<Horizon::Zone::Bonuses::BonusCastCancelImmunity>("BonusCastCancelImmunity",
		sol::constructors<Horizon::Zone::Bonuses::BonusCastCancelImmunity(std::shared_ptr<Unit>, int)>());
	config_69["attribute"] = [](std::shared_ptr<Horizon::Zone::Bonuses::BonusCastCancelImmunity> t) { return std::static_pointer_cast<Horizon::Zone::Traits::Attribute>(t); };
	config_69["get"] = &Horizon::Zone::Bonuses::BonusCastCancelImmunity::get;
	config_69["set"] = &Horizon::Zone::Bonuses::BonusCastCancelImmunity::set;

	sol::usertype<Horizon::Zone::Bonuses::BonusSizeModifierImmunity> config_70 = state->new_usertype<Horizon::Zone::Bonuses::BonusSizeModifierImmunity>("BonusSizeModifierImmunity",
		sol::constructors<Horizon::Zone::Bonuses::BonusSizeModifierImmunity(std::shared_ptr<Unit>, int)>());
	config_70["attribute"] = [](std::shared_ptr<Horizon::Zone::Bonuses::BonusSizeModifierImmunity> t) { return std::static_pointer_cast<Horizon::Zone::Traits::Attribute>(t); };
	config_70["get"] = &Horizon::Zone::Bonuses::BonusSizeModifierImmunity::get;
	config_70["set"] = &Horizon::Zone::Bonuses::BonusSizeModifierImmunity::set;

	sol::usertype<Horizon::Zone::Bonuses::BonusMagicDamageImmunity> config_71 = state->new_usertype<Horizon::Zone::Bonuses::BonusMagicDamageImmunity>("BonusMagicDamageImmunity",
		sol::constructors<Horizon::Zone::Bonuses::BonusMagicDamageImmunity(std::shared_ptr<Unit>, int)>());
	config_71["attribute"] = [](std::shared_ptr<Horizon::Zone::Bonuses::BonusMagicDamageImmunity> t) { return std::static_pointer_cast<Horizon::Zone::Traits::Attribute>(t); };
	config_71["get"] = &Horizon::Zone::Bonuses::BonusMagicDamageImmunity::get;
	config_71["set"] = &Horizon::Zone::Bonuses::BonusMagicDamageImmunity::set;

	sol::usertype<Horizon::Zone::Bonuses::BonusWeaponDamageImmunity> config_72 = state->new_usertype<Horizon::Zone::Bonuses::BonusWeaponDamageImmunity>("BonusWeaponDamageImmunity",
		sol::constructors<Horizon::Zone::Bonuses::BonusWeaponDamageImmunity(std::shared_ptr<Unit>, int)>());
	config_72["attribute"] = [](std::shared_ptr<Horizon::Zone::Bonuses::BonusWeaponDamageImmunity> t) { return std::static_pointer_cast<Horizon::Zone::Traits::Attribute>(t); };
	config_72["get"] = &Horizon::Zone::Bonuses::BonusWeaponDamageImmunity::get;
	config_72["set"] = &Horizon::Zone::Bonuses::BonusWeaponDamageImmunity::set;

	sol::usertype<Horizon::Zone::Bonuses::BonusGemstoneImmunity> config_73 = state->new_usertype<Horizon::Zone::Bonuses::BonusGemstoneImmunity>("BonusGemstoneImmunity",
		sol::constructors<Horizon::Zone::Bonuses::BonusGemstoneImmunity(std::shared_ptr<Unit>, int)>());
	config_73["attribute"] = [](std::shared_ptr<Horizon::Zone::Bonuses::BonusGemstoneImmunity> t) { return std::static_pointer_cast<Horizon::Zone::Traits::Attribute>(t); };
	config_73["get"] = &Horizon::Zone::Bonuses::BonusGemstoneImmunity::get;
	config_73["set"] = &Horizon::Zone::Bonuses::BonusGemstoneImmunity::set;

	sol::usertype<Horizon::Zone::Bonuses::BonusGearFuelImmunity> config_74 = state->new_usertype<Horizon::Zone::Bonuses::BonusGearFuelImmunity>("BonusGearFuelImmunity",
		sol::constructors<Horizon::Zone::Bonuses::BonusGearFuelImmunity(std::shared_ptr<Unit>, int)>());
	config_74["attribute"] = [](std::shared_ptr<Horizon::Zone::Bonuses::BonusGearFuelImmunity> t) { return std::static_pointer_cast<Horizon::Zone::Traits::Attribute>(t); };
	config_74["get"] = &Horizon::Zone::Bonuses::BonusGearFuelImmunity::get;
	config_74["set"] = &Horizon::Zone::Bonuses::BonusGearFuelImmunity::set;

	sol::usertype<Horizon::Zone::Bonuses::BonusInfiniteEndure> config_75 = state->new_usertype<Horizon::Zone::Bonuses::BonusInfiniteEndure>("BonusInfiniteEndure",
		sol::constructors<Horizon::Zone::Bonuses::BonusInfiniteEndure(std::shared_ptr<Unit>, int)>());
	config_75["attribute"] = [](std::shared_ptr<Horizon::Zone::Bonuses::BonusInfiniteEndure> t) { return std::static_pointer_cast<Horizon::Zone::Traits::Attribute>(t); };
	config_75["get"] = &Horizon::Zone::Bonuses::BonusInfiniteEndure::get;
	config_75["set"] = &Horizon::Zone::Bonuses::BonusInfiniteEndure::set;

	sol::usertype<Horizon::Zone::Bonuses::BonusUnbreakableWeapon> config_76 = state->new_usertype<Horizon::Zone::Bonuses::BonusUnbreakableWeapon>("BonusUnbreakableWeapon",
		sol::constructors<Horizon::Zone::Bonuses::BonusUnbreakableWeapon(std::shared_ptr<Unit>, int)>());
	config_76["attribute"] = [](std::shared_ptr<Horizon::Zone::Bonuses::BonusUnbreakableWeapon> t) { return std::static_pointer_cast<Horizon::Zone::Traits::Attribute>(t); };
	config_76["get"] = &Horizon::Zone::Bonuses::BonusUnbreakableWeapon::get;
	config_76["set"] = &Horizon::Zone::Bonuses::BonusUnbreakableWeapon::set;

	sol::usertype<Horizon::Zone::Bonuses::BonusUnbreakableArmor> config_77 = state->new_usertype<Horizon::Zone::Bonuses::BonusUnbreakableArmor>("BonusUnbreakableArmor",
		sol::constructors<Horizon::Zone::Bonuses::BonusUnbreakableArmor(std::shared_ptr<Unit>, int)>());
	config_77["attribute"] = [](std::shared_ptr<Horizon::Zone::Bonuses::BonusUnbreakableArmor> t) { return std::static_pointer_cast<Horizon::Zone::Traits::Attribute>(t); };
	config_77["get"] = &Horizon::Zone::Bonuses::BonusUnbreakableArmor::get;
	config_77["set"] = &Horizon::Zone::Bonuses::BonusUnbreakableArmor::set;

	sol::usertype<Horizon::Zone::Bonuses::BonusUnbreakableHelm> config_78 = state->new_usertype<Horizon::Zone::Bonuses::BonusUnbreakableHelm>("BonusUnbreakableHelm",
		sol::constructors<Horizon::Zone::Bonuses::BonusUnbreakableHelm(std::shared_ptr<Unit>, int)>());
	config_78["attribute"] = [](std::shared_ptr<Horizon::Zone::Bonuses::BonusUnbreakableHelm> t) { return std::static_pointer_cast<Horizon::Zone::Traits::Attribute>(t); };
	config_78["get"] = &Horizon::Zone::Bonuses::BonusUnbreakableHelm::get;
	config_78["set"] = &Horizon::Zone::Bonuses::BonusUnbreakableHelm::set;

	sol::usertype<Horizon::Zone::Bonuses::BonusUnbreakableShield> config_79 = state->new_usertype<Horizon::Zone::Bonuses::BonusUnbreakableShield>("BonusUnbreakableShield",
		sol::constructors<Horizon::Zone::Bonuses::BonusUnbreakableShield(std::shared_ptr<Unit>, int)>());
	config_79["attribute"] = [](std::shared_ptr<Horizon::Zone::Bonuses::BonusUnbreakableShield> t) { return std::static_pointer_cast<Horizon::Zone::Traits::Attribute>(t); };
	config_79["get"] = &Horizon::Zone::Bonuses::BonusUnbreakableShield::get;
	config_79["set"] = &Horizon::Zone::Bonuses::BonusUnbreakableShield::set;

	sol::usertype<Horizon::Zone::Bonuses::BonusSPGainOnMobKill> config_80 = state->new_usertype<Horizon::Zone::Bonuses::BonusSPGainOnMobKill>("BonusSPGainOnMobKill",
		sol::constructors<Horizon::Zone::Bonuses::BonusSPGainOnMobKill(std::shared_ptr<Unit>, int)>());
	config_80["attribute"] = [](std::shared_ptr<Horizon::Zone::Bonuses::BonusSPGainOnMobKill> t) { return std::static_pointer_cast<Horizon::Zone::Traits::Attribute>(t); };
	config_80["get"] = &Horizon::Zone::Bonuses::BonusSPGainOnMobKill::get;
	config_80["set"] = &Horizon::Zone::Bonuses::BonusSPGainOnMobKill::set;

	sol::usertype<Horizon::Zone::Bonuses::BonusHPGainOnMobKill> config_81 = state->new_usertype<Horizon::Zone::Bonuses::BonusHPGainOnMobKill>("BonusHPGainOnMobKill",
		sol::constructors<Horizon::Zone::Bonuses::BonusHPGainOnMobKill(std::shared_ptr<Unit>, int)>());
	config_81["attribute"] = [](std::shared_ptr<Horizon::Zone::Bonuses::BonusHPGainOnMobKill> t) { return std::static_pointer_cast<Horizon::Zone::Traits::Attribute>(t); };
	config_81["get"] = &Horizon::Zone::Bonuses::BonusHPGainOnMobKill::get;
	config_81["set"] = &Horizon::Zone::Bonuses::BonusHPGainOnMobKill::set;

	sol::usertype<Horizon::Zone::Bonuses::BonusDamageSplashRange> config_82 = state->new_usertype<Horizon::Zone::Bonuses::BonusDamageSplashRange>("BonusDamageSplashRange",
		sol::constructors<Horizon::Zone::Bonuses::BonusDamageSplashRange(std::shared_ptr<Unit>, int)>());
	config_82["attribute"] = [](std::shared_ptr<Horizon::Zone::Bonuses::BonusDamageSplashRange> t) { return std::static_pointer_cast<Horizon::Zone::Traits::Attribute>(t); };
	config_82["get"] = &Horizon::Zone::Bonuses::BonusDamageSplashRange::get;
	config_82["set"] = &Horizon::Zone::Bonuses::BonusDamageSplashRange::set;

	sol::usertype<Horizon::Zone::Bonuses::BonusMeleeWeaponDamageReflectPercentOnSelf> config_83 = state->new_usertype<Horizon::Zone::Bonuses::BonusMeleeWeaponDamageReflectPercentOnSelf>("BonusMeleeWeaponDamageReflectPercentOnSelf",
		sol::constructors<Horizon::Zone::Bonuses::BonusMeleeWeaponDamageReflectPercentOnSelf(std::shared_ptr<Unit>, int)>());
	config_83["attribute"] = [](std::shared_ptr<Horizon::Zone::Bonuses::BonusMeleeWeaponDamageReflectPercentOnSelf> t) { return std::static_pointer_cast<Horizon::Zone::Traits::Attribute>(t); };
	config_83["get"] = &Horizon::Zone::Bonuses::BonusMeleeWeaponDamageReflectPercentOnSelf::get;
	config_83["set"] = &Horizon::Zone::Bonuses::BonusMeleeWeaponDamageReflectPercentOnSelf::set;

	sol::usertype<Horizon::Zone::Bonuses::BonusRangedWeaponDamageReflectPercentOnSelf> config_84 = state->new_usertype<Horizon::Zone::Bonuses::BonusRangedWeaponDamageReflectPercentOnSelf>("BonusRangedWeaponDamageReflectPercentOnSelf",
		sol::constructors<Horizon::Zone::Bonuses::BonusRangedWeaponDamageReflectPercentOnSelf(std::shared_ptr<Unit>, int)>());
	config_84["attribute"] = [](std::shared_ptr<Horizon::Zone::Bonuses::BonusRangedWeaponDamageReflectPercentOnSelf> t) { return std::static_pointer_cast<Horizon::Zone::Traits::Attribute>(t); };
	config_84["get"] = &Horizon::Zone::Bonuses::BonusRangedWeaponDamageReflectPercentOnSelf::get;
	config_84["set"] = &Horizon::Zone::Bonuses::BonusRangedWeaponDamageReflectPercentOnSelf::set;

	sol::usertype<Horizon::Zone::Bonuses::BonusWeaponBreakPercent> config_85 = state->new_usertype<Horizon::Zone::Bonuses::BonusWeaponBreakPercent>("BonusWeaponBreakPercent",
		sol::constructors<Horizon::Zone::Bonuses::BonusWeaponBreakPercent(std::shared_ptr<Unit>, int)>());
	config_85["attribute"] = [](std::shared_ptr<Horizon::Zone::Bonuses::BonusWeaponBreakPercent> t) { return std::static_pointer_cast<Horizon::Zone::Traits::Attribute>(t); };
	config_85["get"] = &Horizon::Zone::Bonuses::BonusWeaponBreakPercent::get;
	config_85["set"] = &Horizon::Zone::Bonuses::BonusWeaponBreakPercent::set;

	sol::usertype<Horizon::Zone::Bonuses::BonusArmorBreakPercent> config_86 = state->new_usertype<Horizon::Zone::Bonuses::BonusArmorBreakPercent>("BonusArmorBreakPercent",
		sol::constructors<Horizon::Zone::Bonuses::BonusArmorBreakPercent(std::shared_ptr<Unit>, int)>());
	config_86["attribute"] = [](std::shared_ptr<Horizon::Zone::Bonuses::BonusArmorBreakPercent> t) { return std::static_pointer_cast<Horizon::Zone::Traits::Attribute>(t); };
	config_86["get"] = &Horizon::Zone::Bonuses::BonusArmorBreakPercent::get;
	config_86["set"] = &Horizon::Zone::Bonuses::BonusArmorBreakPercent::set;

	sol::usertype<Horizon::Zone::Bonuses::BonusAddStealPercent> config_87 = state->new_usertype<Horizon::Zone::Bonuses::BonusAddStealPercent>("BonusAddStealPercent",
		sol::constructors<Horizon::Zone::Bonuses::BonusAddStealPercent(std::shared_ptr<Unit>, int)>());
	config_87["attribute"] = [](std::shared_ptr<Horizon::Zone::Bonuses::BonusAddStealPercent> t) { return std::static_pointer_cast<Horizon::Zone::Traits::Attribute>(t); };
	config_87["get"] = &Horizon::Zone::Bonuses::BonusAddStealPercent::get;
	config_87["set"] = &Horizon::Zone::Bonuses::BonusAddStealPercent::set;

	sol::usertype<Horizon::Zone::Bonuses::BonusCriticalDamagePercent> config_88 = state->new_usertype<Horizon::Zone::Bonuses::BonusCriticalDamagePercent>("BonusCriticalDamagePercent",
		sol::constructors<Horizon::Zone::Bonuses::BonusCriticalDamagePercent(std::shared_ptr<Unit>, int)>());
	config_88["attribute"] = [](std::shared_ptr<Horizon::Zone::Bonuses::BonusCriticalDamagePercent> t) { return std::static_pointer_cast<Horizon::Zone::Traits::Attribute>(t); };
	config_88["get"] = &Horizon::Zone::Bonuses::BonusCriticalDamagePercent::get;
	config_88["set"] = &Horizon::Zone::Bonuses::BonusCriticalDamagePercent::set;

	sol::usertype<Horizon::Zone::Bonuses::BonusDisableHPRecovery> config_89 = state->new_usertype<Horizon::Zone::Bonuses::BonusDisableHPRecovery>("BonusDisableHPRecovery",
		sol::constructors<Horizon::Zone::Bonuses::BonusDisableHPRecovery(std::shared_ptr<Unit>, int)>());
	config_89["attribute"] = [](std::shared_ptr<Horizon::Zone::Bonuses::BonusDisableHPRecovery> t) { return std::static_pointer_cast<Horizon::Zone::Traits::Attribute>(t); };
	config_89["get"] = &Horizon::Zone::Bonuses::BonusDisableHPRecovery::get;
	config_89["set"] = &Horizon::Zone::Bonuses::BonusDisableHPRecovery::set;

	sol::usertype<Horizon::Zone::Bonuses::BonusDisableSPRecovery> config_90 = state->new_usertype<Horizon::Zone::Bonuses::BonusDisableSPRecovery>("BonusDisableSPRecovery",
		sol::constructors<Horizon::Zone::Bonuses::BonusDisableSPRecovery(std::shared_ptr<Unit>, int)>());
	config_90["attribute"] = [](std::shared_ptr<Horizon::Zone::Bonuses::BonusDisableSPRecovery> t) { return std::static_pointer_cast<Horizon::Zone::Traits::Attribute>(t); };
	config_90["get"] = &Horizon::Zone::Bonuses::BonusDisableSPRecovery::get;
	config_90["set"] = &Horizon::Zone::Bonuses::BonusDisableSPRecovery::set;

	sol::usertype<Horizon::Zone::Bonuses::BonusMagicDamageReflectPercentOnSelf> config_91 = state->new_usertype<Horizon::Zone::Bonuses::BonusMagicDamageReflectPercentOnSelf>("BonusMagicDamageReflectPercentOnSelf",
		sol::constructors<Horizon::Zone::Bonuses::BonusMagicDamageReflectPercentOnSelf(std::shared_ptr<Unit>, int)>());
	config_91["attribute"] = [](std::shared_ptr<Horizon::Zone::Bonuses::BonusMagicDamageReflectPercentOnSelf> t) { return std::static_pointer_cast<Horizon::Zone::Traits::Attribute>(t); };
	config_91["get"] = &Horizon::Zone::Bonuses::BonusMagicDamageReflectPercentOnSelf::get;
	config_91["set"] = &Horizon::Zone::Bonuses::BonusMagicDamageReflectPercentOnSelf::set;

	sol::usertype<Horizon::Zone::Bonuses::BonusShortWeaponDamagePercent> config_92 = state->new_usertype<Horizon::Zone::Bonuses::BonusShortWeaponDamagePercent>("BonusShortWeaponDamagePercent",
		sol::constructors<Horizon::Zone::Bonuses::BonusShortWeaponDamagePercent(std::shared_ptr<Unit>, int)>());
	config_92["attribute"] = [](std::shared_ptr<Horizon::Zone::Bonuses::BonusShortWeaponDamagePercent> t) { return std::static_pointer_cast<Horizon::Zone::Traits::Attribute>(t); };
	config_92["get"] = &Horizon::Zone::Bonuses::BonusShortWeaponDamagePercent::get;
	config_92["set"] = &Horizon::Zone::Bonuses::BonusShortWeaponDamagePercent::set;

	sol::usertype<Horizon::Zone::Bonuses::BonusLongWeaponDamagePercent> config_93 = state->new_usertype<Horizon::Zone::Bonuses::BonusLongWeaponDamagePercent>("BonusLongWeaponDamagePercent",
		sol::constructors<Horizon::Zone::Bonuses::BonusLongWeaponDamagePercent(std::shared_ptr<Unit>, int)>());
	config_93["attribute"] = [](std::shared_ptr<Horizon::Zone::Bonuses::BonusLongWeaponDamagePercent> t) { return std::static_pointer_cast<Horizon::Zone::Traits::Attribute>(t); };
	config_93["get"] = &Horizon::Zone::Bonuses::BonusLongWeaponDamagePercent::get;
	config_93["set"] = &Horizon::Zone::Bonuses::BonusLongWeaponDamagePercent::set;

	sol::usertype<Horizon::Zone::Bonuses::BonusItemUsageImmunity> config_94 = state->new_usertype<Horizon::Zone::Bonuses::BonusItemUsageImmunity>("BonusItemUsageImmunity",
		sol::constructors<Horizon::Zone::Bonuses::BonusItemUsageImmunity(std::shared_ptr<Unit>, int)>());
	config_94["attribute"] = [](std::shared_ptr<Horizon::Zone::Bonuses::BonusItemUsageImmunity> t) { return std::static_pointer_cast<Horizon::Zone::Traits::Attribute>(t); };
	config_94["get"] = &Horizon::Zone::Bonuses::BonusItemUsageImmunity::get;
	config_94["set"] = &Horizon::Zone::Bonuses::BonusItemUsageImmunity::set;

	sol::usertype<Horizon::Zone::Bonuses::BonusKnockBackImmunity> config_95 = state->new_usertype<Horizon::Zone::Bonuses::BonusKnockBackImmunity>("BonusKnockbackImmunity",
		sol::constructors<Horizon::Zone::Bonuses::BonusKnockBackImmunity(std::shared_ptr<Unit>, int)>());
	config_95["attribute"] = [](std::shared_ptr<Horizon::Zone::Bonuses::BonusKnockBackImmunity> t) { return std::static_pointer_cast<Horizon::Zone::Traits::Attribute>(t); };
	config_95["get"] = &Horizon::Zone::Bonuses::BonusKnockBackImmunity::get;
	config_95["set"] = &Horizon::Zone::Bonuses::BonusKnockBackImmunity::set;

	sol::usertype<Horizon::Zone::Bonuses::BonusAddAttackPercentageToElement> config_96 = state->new_usertype<Horizon::Zone::Bonuses::BonusAddAttackPercentageToElement>("BonusAddAttackPercentageToElement",
		sol::constructors<Horizon::Zone::Bonuses::BonusAddAttackPercentageToElement(std::shared_ptr<Unit>)>());
	config_96["get"] = &Horizon::Zone::Bonuses::BonusAddAttackPercentageToElement::get;
	config_96["set"] = &Horizon::Zone::Bonuses::BonusAddAttackPercentageToElement::set;
	config_96["clear"] = sol::resolve<void()>(&Horizon::Zone::Bonuses::BonusAddAttackPercentageToElement::clear);
	config_96["clear_single"] = sol::resolve<void(int)>(&Horizon::Zone::Bonuses::BonusAddAttackPercentageToElement::clear);
	
	sol::usertype<Horizon::Zone::Bonuses::BonusAddAttackPercentageToRace> config_97 = state->new_usertype<Horizon::Zone::Bonuses::BonusAddAttackPercentageToRace>("BonusAddAttackPercentageToRace",
		sol::constructors<Horizon::Zone::Bonuses::BonusAddAttackPercentageToRace(std::shared_ptr<Unit>)>());
	config_97["get"] = &Horizon::Zone::Bonuses::BonusAddAttackPercentageToRace::get;
	config_97["set"] = &Horizon::Zone::Bonuses::BonusAddAttackPercentageToRace::set;
	config_97["clear"] = sol::resolve<void()>(&Horizon::Zone::Bonuses::BonusAddAttackPercentageToRace::clear);
	config_97["clear_single"] = sol::resolve<void(int)>(&Horizon::Zone::Bonuses::BonusAddAttackPercentageToRace::clear);

	sol::usertype<Horizon::Zone::Bonuses::BonusAddAttackPercentageToSize> config_98 = state->new_usertype<Horizon::Zone::Bonuses::BonusAddAttackPercentageToSize>("BonusAddAttackPercentageToSize",
		sol::constructors<Horizon::Zone::Bonuses::BonusAddAttackPercentageToSize(std::shared_ptr<Unit>)>());
	config_98["get"] = &Horizon::Zone::Bonuses::BonusAddAttackPercentageToSize::get;
	config_98["set"] = &Horizon::Zone::Bonuses::BonusAddAttackPercentageToSize::set;
	config_98["clear"] = sol::resolve<void()>(&Horizon::Zone::Bonuses::BonusAddAttackPercentageToSize::clear);
	config_98["clear_single"] = sol::resolve<void(int)>(&Horizon::Zone::Bonuses::BonusAddAttackPercentageToSize::clear);

	sol::usertype<Horizon::Zone::Bonuses::BonusSubAttackPercentageFromElement> config_99 = state->new_usertype<Horizon::Zone::Bonuses::BonusSubAttackPercentageFromElement>("BonusSubAttackPercentageFromElement",
		sol::constructors<Horizon::Zone::Bonuses::BonusSubAttackPercentageFromElement(std::shared_ptr<Unit>)>());
	config_99["get"] = &Horizon::Zone::Bonuses::BonusSubAttackPercentageFromElement::get;
	config_99["set"] = &Horizon::Zone::Bonuses::BonusSubAttackPercentageFromElement::set;
	config_99["clear"] = sol::resolve<void()>(&Horizon::Zone::Bonuses::BonusSubAttackPercentageFromElement::clear);
	config_99["clear_single"] = sol::resolve<void(int)>(&Horizon::Zone::Bonuses::BonusSubAttackPercentageFromElement::clear);

	sol::usertype<Horizon::Zone::Bonuses::BonusSubAttackPercentageFromRace> config_100 = state->new_usertype<Horizon::Zone::Bonuses::BonusSubAttackPercentageFromRace>("BonusSubAttackPercentageFromRace",
		sol::constructors<Horizon::Zone::Bonuses::BonusSubAttackPercentageFromRace(std::shared_ptr<Unit>)>());
	config_100["get"] = &Horizon::Zone::Bonuses::BonusSubAttackPercentageFromRace::get;
	config_100["set"] = &Horizon::Zone::Bonuses::BonusSubAttackPercentageFromRace::set;
	config_100["clear"] = sol::resolve<void()>(&Horizon::Zone::Bonuses::BonusSubAttackPercentageFromRace::clear);
	config_100["clear_single"] = sol::resolve<void(int)>(&Horizon::Zone::Bonuses::BonusSubAttackPercentageFromRace::clear);

	sol::usertype<Horizon::Zone::Bonuses::s_add_effect> config_104 = state->new_usertype<Horizon::Zone::Bonuses::s_add_effect>("s_add_effect");
	config_104["eff_id"] = &Horizon::Zone::Bonuses::s_add_effect::eff_id;
	config_104["rate"] = &Horizon::Zone::Bonuses::s_add_effect::rate;
	config_104["arrow_rate"] = &Horizon::Zone::Bonuses::s_add_effect::arrow_rate;
	config_104["tigger_type"] = &Horizon::Zone::Bonuses::s_add_effect::tigger_type;
	config_104["duration"] = &Horizon::Zone::Bonuses::s_add_effect::duration;
	
	sol::usertype<Horizon::Zone::Bonuses::BonusAddEffectOnDamage> config_101 = state->new_usertype<Horizon::Zone::Bonuses::BonusAddEffectOnDamage>("BonusAddEffectOnDamage",
		sol::constructors<Horizon::Zone::Bonuses::BonusAddEffectOnDamage(std::shared_ptr<Unit>)>());
	config_101["get"] = &Horizon::Zone::Bonuses::BonusAddEffectOnDamage::get;
	config_101["set"] = &Horizon::Zone::Bonuses::BonusAddEffectOnDamage::set;
	config_101["clear"] = sol::resolve<void()>(&Horizon::Zone::Bonuses::BonusAddEffectOnDamage::clear);
	config_101["clear_single"] = sol::resolve<void(int)>(&Horizon::Zone::Bonuses::BonusAddEffectOnDamage::clear);

	sol::usertype<Horizon::Zone::Bonuses::BonusAddEffectWhenDamaged> config_102 = state->new_usertype<Horizon::Zone::Bonuses::BonusAddEffectWhenDamaged>("BonusAddEffectWhenDamaged",
		sol::constructors<Horizon::Zone::Bonuses::BonusAddEffectWhenDamaged(std::shared_ptr<Unit>)>());
	config_102["get"] = &Horizon::Zone::Bonuses::BonusAddEffectWhenDamaged::get;
	config_102["set"] = &Horizon::Zone::Bonuses::BonusAddEffectWhenDamaged::set;
	config_102["clear"] = sol::resolve<void()>(&Horizon::Zone::Bonuses::BonusAddEffectWhenDamaged::clear);
	config_102["clear_single"] = sol::resolve<void(int)>(&Horizon::Zone::Bonuses::BonusAddEffectWhenDamaged::clear);

	sol::usertype<Horizon::Zone::Bonuses::BonusRessistEffect> config_103 = state->new_usertype<Horizon::Zone::Bonuses::BonusRessistEffect>("BonusRessistEffect",
		sol::constructors<Horizon::Zone::Bonuses::BonusRessistEffect(std::shared_ptr<Unit>)>());
	config_103["get"] = &Horizon::Zone::Bonuses::BonusRessistEffect::get;
	config_103["set"] = &Horizon::Zone::Bonuses::BonusRessistEffect::set;
	config_103["clear"] = sol::resolve<void()>(&Horizon::Zone::Bonuses::BonusRessistEffect::clear);
	config_103["clear_single"] = sol::resolve<void(int)>(&Horizon::Zone::Bonuses::BonusRessistEffect::clear);

	sol::usertype<Horizon::Zone::Bonuses::BonusAddMagicAttackPercentageToElement> config_105 = state->new_usertype<Horizon::Zone::Bonuses::BonusAddMagicAttackPercentageToElement>("BonusAddMagicAttackPercentageToElement",
		sol::constructors<Horizon::Zone::Bonuses::BonusAddMagicAttackPercentageToElement(std::shared_ptr<Unit>)>());
	config_105["get"] = &Horizon::Zone::Bonuses::BonusAddMagicAttackPercentageToElement::get;
	config_105["set"] = &Horizon::Zone::Bonuses::BonusAddMagicAttackPercentageToElement::set;
	config_105["clear"] = sol::resolve<void()>(&Horizon::Zone::Bonuses::BonusAddMagicAttackPercentageToElement::clear);
	config_105["clear_single"] = sol::resolve<void(int)>(&Horizon::Zone::Bonuses::BonusAddMagicAttackPercentageToElement::clear);

	sol::usertype<Horizon::Zone::Bonuses::BonusAddMagicAttackPercentageToRace> config_106 = state->new_usertype<Horizon::Zone::Bonuses::BonusAddMagicAttackPercentageToRace>("BonusAddMagicAttackPercentageToRace",
		sol::constructors<Horizon::Zone::Bonuses::BonusAddMagicAttackPercentageToRace(std::shared_ptr<Unit>)>());
	config_106["get"] = &Horizon::Zone::Bonuses::BonusAddMagicAttackPercentageToRace::get;
	config_106["set"] = &Horizon::Zone::Bonuses::BonusAddMagicAttackPercentageToRace::set;
	config_106["clear"] = sol::resolve<void()>(&Horizon::Zone::Bonuses::BonusAddMagicAttackPercentageToRace::clear);
	config_106["clear_single"] = sol::resolve<void(int)>(&Horizon::Zone::Bonuses::BonusAddMagicAttackPercentageToRace::clear);

	sol::usertype<Horizon::Zone::Bonuses::BonusAddMagicAttackPercentageToSize> config_107 = state->new_usertype<Horizon::Zone::Bonuses::BonusAddMagicAttackPercentageToSize>("BonusAddMagicAttackPercentageToSize",
		sol::constructors<Horizon::Zone::Bonuses::BonusAddMagicAttackPercentageToSize(std::shared_ptr<Unit>)>());
	config_107["get"] = &Horizon::Zone::Bonuses::BonusAddMagicAttackPercentageToSize::get;
	config_107["set"] = &Horizon::Zone::Bonuses::BonusAddMagicAttackPercentageToSize::set;
	config_107["clear"] = sol::resolve<void()>(&Horizon::Zone::Bonuses::BonusAddMagicAttackPercentageToSize::clear);
	config_107["clear_single"] = sol::resolve<void(int)>(&Horizon::Zone::Bonuses::BonusAddMagicAttackPercentageToSize::clear);

	sol::usertype<Horizon::Zone::Bonuses::BonusAddEffectOnMagicAttack> config_108 = state->new_usertype<Horizon::Zone::Bonuses::BonusAddEffectOnMagicAttack>("BonusAddEffectOnMagicAttack",
		sol::constructors<Horizon::Zone::Bonuses::BonusAddEffectOnMagicAttack(std::shared_ptr<Unit>)>());
	config_108["get"] = &Horizon::Zone::Bonuses::BonusAddEffectOnMagicAttack::get;
	config_108["set"] = &Horizon::Zone::Bonuses::BonusAddEffectOnMagicAttack::set;
	config_108["clear"] = sol::resolve<void()>(&Horizon::Zone::Bonuses::BonusAddEffectOnMagicAttack::clear);
	config_108["clear_single"] = sol::resolve<void(int)>(&Horizon::Zone::Bonuses::BonusAddEffectOnMagicAttack::clear);

	sol::usertype<Horizon::Zone::Bonuses::BonusResistMagicAttackFromRace> config_109 = state->new_usertype<Horizon::Zone::Bonuses::BonusResistMagicAttackFromRace>("BonusResistMagicAttackFromRace",
		sol::constructors<Horizon::Zone::Bonuses::BonusResistMagicAttackFromRace(std::shared_ptr<Unit>)>());
	config_109["get"] = &Horizon::Zone::Bonuses::BonusResistMagicAttackFromRace::get;
	config_109["set"] = &Horizon::Zone::Bonuses::BonusResistMagicAttackFromRace::set;
	config_109["clear"] = sol::resolve<void()>(&Horizon::Zone::Bonuses::BonusResistMagicAttackFromRace::clear);
	config_109["clear_single"] = sol::resolve<void(int)>(&Horizon::Zone::Bonuses::BonusResistMagicAttackFromRace::clear);

	sol::usertype<Horizon::Zone::Bonuses::BonusAddDamageToClass> config_110 = state->new_usertype<Horizon::Zone::Bonuses::BonusAddDamageToClass>("BonusAddDamageToClass",
		sol::constructors<Horizon::Zone::Bonuses::BonusAddDamageToClass(std::shared_ptr<Unit>)>());
	config_110["get"] = &Horizon::Zone::Bonuses::BonusAddDamageToClass::get;
	config_110["set"] = &Horizon::Zone::Bonuses::BonusAddDamageToClass::set;
	config_110["clear"] = sol::resolve<void()>(&Horizon::Zone::Bonuses::BonusAddDamageToClass::clear);
	config_110["clear_single"] = sol::resolve<void(int)>(&Horizon::Zone::Bonuses::BonusAddDamageToClass::clear);

	sol::usertype<Horizon::Zone::Bonuses::BonusAddMagicDamageToClass> config_111 = state->new_usertype<Horizon::Zone::Bonuses::BonusAddMagicDamageToClass>("BonusAddMagicDamageToClass",
		sol::constructors<Horizon::Zone::Bonuses::BonusAddMagicDamageToClass(std::shared_ptr<Unit>)>());
	config_111["get"] = &Horizon::Zone::Bonuses::BonusAddMagicDamageToClass::get;
	config_111["set"] = &Horizon::Zone::Bonuses::BonusAddMagicDamageToClass::set;
	config_111["clear"] = sol::resolve<void()>(&Horizon::Zone::Bonuses::BonusAddMagicDamageToClass::clear);
	config_111["clear_single"] = sol::resolve<void(int)>(&Horizon::Zone::Bonuses::BonusAddMagicDamageToClass::clear);

	sol::usertype<Horizon::Zone::Bonuses::BonusAddDefenseToClass> config_112 = state->new_usertype<Horizon::Zone::Bonuses::BonusAddDefenseToClass>("BonusAddDefenseToClass",
		sol::constructors<Horizon::Zone::Bonuses::BonusAddDefenseToClass(std::shared_ptr<Unit>)>());
	config_112["get"] = &Horizon::Zone::Bonuses::BonusAddDefenseToClass::get;
	config_112["set"] = &Horizon::Zone::Bonuses::BonusAddDefenseToClass::set;
	config_112["clear"] = sol::resolve<void()>(&Horizon::Zone::Bonuses::BonusAddDefenseToClass::clear);
	config_112["clear_single"] = sol::resolve<void(int)>(&Horizon::Zone::Bonuses::BonusAddDefenseToClass::clear);

	sol::usertype<Horizon::Zone::Bonuses::BonusAddMagicalDefenseToClass> config_113 = state->new_usertype<Horizon::Zone::Bonuses::BonusAddMagicalDefenseToClass>("BonusAddMagicalDefenseToClass",
		sol::constructors<Horizon::Zone::Bonuses::BonusAddMagicalDefenseToClass(std::shared_ptr<Unit>)>());
	config_113["get"] = &Horizon::Zone::Bonuses::BonusAddMagicalDefenseToClass::get;
	config_113["set"] = &Horizon::Zone::Bonuses::BonusAddMagicalDefenseToClass::set;
	config_113["clear"] = sol::resolve<void()>(&Horizon::Zone::Bonuses::BonusAddMagicalDefenseToClass::clear);
	config_113["clear_single"] = sol::resolve<void(int)>(&Horizon::Zone::Bonuses::BonusAddMagicalDefenseToClass::clear);

	sol::usertype<Horizon::Zone::Bonuses::BonusHPDrainPercent> config_114 = state->new_usertype<Horizon::Zone::Bonuses::BonusHPDrainPercent>("BonusHPDrainPercent",
		sol::constructors<Horizon::Zone::Bonuses::BonusHPDrainPercent(std::shared_ptr<Unit>, int, int)>());
	config_114["get"] = &Horizon::Zone::Bonuses::BonusHPDrainPercent::get;
	config_114["set"] = &Horizon::Zone::Bonuses::BonusHPDrainPercent::set;
	config_114["get_parameter_1"] = &Horizon::Zone::Bonuses::BonusHPDrainPercent::get_parameter_1;
	config_114["set_parameter_1"] = &Horizon::Zone::Bonuses::BonusHPDrainPercent::set_parameter_1;

	sol::usertype<Horizon::Zone::Bonuses::BonusHPDrainValue> config_115 = state->new_usertype<Horizon::Zone::Bonuses::BonusHPDrainValue>("BonusHPDrainValue",
		sol::constructors<Horizon::Zone::Bonuses::BonusHPDrainValue(std::shared_ptr<Unit>, int, int)>());
	config_115["get"] = &Horizon::Zone::Bonuses::BonusHPDrainValue::get;
	config_115["set"] = &Horizon::Zone::Bonuses::BonusHPDrainValue::set;
	config_115["get_parameter_1"] = &Horizon::Zone::Bonuses::BonusHPDrainValue::get_parameter_1;
	config_115["set_parameter_1"] = &Horizon::Zone::Bonuses::BonusHPDrainValue::set_parameter_1;

	sol::usertype<Horizon::Zone::Bonuses::BonusSPDrainPercent> config_116 = state->new_usertype<Horizon::Zone::Bonuses::BonusSPDrainPercent>("BonusSPDrainPercent",
		sol::constructors<Horizon::Zone::Bonuses::BonusSPDrainPercent(std::shared_ptr<Unit>, int, int)>());
	config_116["get"] = &Horizon::Zone::Bonuses::BonusSPDrainPercent::get;
	config_116["set"] = &Horizon::Zone::Bonuses::BonusSPDrainPercent::set;
	config_116["get_parameter_1"] = &Horizon::Zone::Bonuses::BonusSPDrainPercent::get_parameter_1;
	config_116["set_parameter_1"] = &Horizon::Zone::Bonuses::BonusSPDrainPercent::set_parameter_1;

	sol::usertype<Horizon::Zone::Bonuses::BonusSPDrainValue> config_117 = state->new_usertype<Horizon::Zone::Bonuses::BonusSPDrainValue>("BonusSPDrainValue",
		sol::constructors<Horizon::Zone::Bonuses::BonusSPDrainValue(std::shared_ptr<Unit>, int, int)>());
	config_117["get"] = &Horizon::Zone::Bonuses::BonusSPDrainValue::get;
	config_117["set"] = &Horizon::Zone::Bonuses::BonusSPDrainValue::set;
	config_117["get_parameter_1"] = &Horizon::Zone::Bonuses::BonusSPDrainValue::get_parameter_1;
	config_117["set_parameter_1"] = &Horizon::Zone::Bonuses::BonusSPDrainValue::set_parameter_1;

	sol::usertype<Horizon::Zone::Bonuses::BonusAddWeaponComaToElement> config_118 = state->new_usertype<Horizon::Zone::Bonuses::BonusAddWeaponComaToElement>("BonusAddWeaponComaToElement",
		sol::constructors<Horizon::Zone::Bonuses::BonusAddWeaponComaToElement(std::shared_ptr<Unit>)>());
	config_118["get"] = &Horizon::Zone::Bonuses::BonusAddWeaponComaToElement::get;
	config_118["set"] = &Horizon::Zone::Bonuses::BonusAddWeaponComaToElement::set;
	config_118["clear"] = sol::resolve<void()>(&Horizon::Zone::Bonuses::BonusAddWeaponComaToElement::clear);
	config_118["clear_single"] = sol::resolve<void(int)>(&Horizon::Zone::Bonuses::BonusAddWeaponComaToElement::clear);

	sol::usertype<Horizon::Zone::Bonuses::BonusAddWeaponComaToRace> config_119 = state->new_usertype<Horizon::Zone::Bonuses::BonusAddWeaponComaToRace>("BonusAddWeaponComaToRace",
		sol::constructors<Horizon::Zone::Bonuses::BonusAddWeaponComaToRace(std::shared_ptr<Unit>)>());
	config_119["get"] = &Horizon::Zone::Bonuses::BonusAddWeaponComaToRace::get;
	config_119["set"] = &Horizon::Zone::Bonuses::BonusAddWeaponComaToRace::set;
	config_119["clear"] = sol::resolve<void()>(&Horizon::Zone::Bonuses::BonusAddWeaponComaToRace::clear);
	config_119["clear_single"] = sol::resolve<void(int)>(&Horizon::Zone::Bonuses::BonusAddWeaponComaToRace::clear);

	sol::usertype<Horizon::Zone::Bonuses::BonusAddWeaponComaToSubElement> config_121 = state->new_usertype<Horizon::Zone::Bonuses::BonusAddWeaponComaToSubElement>("BonusAddWeaponComaToSubElement",
		sol::constructors<Horizon::Zone::Bonuses::BonusAddWeaponComaToSubElement(std::shared_ptr<Unit>)>());
	config_121["get"] = &Horizon::Zone::Bonuses::BonusAddWeaponComaToSubElement::get;
	config_121["set"] = &Horizon::Zone::Bonuses::BonusAddWeaponComaToSubElement::set;
	config_121["clear"] = sol::resolve<void()>(&Horizon::Zone::Bonuses::BonusAddWeaponComaToSubElement::clear);
	config_121["clear_single"] = sol::resolve<void(int)>(&Horizon::Zone::Bonuses::BonusAddWeaponComaToSubElement::clear);

	sol::usertype<Horizon::Zone::Bonuses::BonusAddWeaponComaToSubRace> config_122 = state->new_usertype<Horizon::Zone::Bonuses::BonusAddWeaponComaToSubRace>("BonusAddWeaponComaToSubRace",
		sol::constructors<Horizon::Zone::Bonuses::BonusAddWeaponComaToSubRace(std::shared_ptr<Unit>)>());
	config_122["get"] = &Horizon::Zone::Bonuses::BonusAddWeaponComaToSubRace::get;
	config_122["set"] = &Horizon::Zone::Bonuses::BonusAddWeaponComaToSubRace::set;
	config_122["clear"] = sol::resolve<void()>(&Horizon::Zone::Bonuses::BonusAddWeaponComaToSubRace::clear);
	config_122["clear_single"] = sol::resolve<void(int)>(&Horizon::Zone::Bonuses::BonusAddWeaponComaToSubRace::clear);

	sol::usertype<Horizon::Zone::Bonuses::BonusAddAttack> config_123 = state->new_usertype<Horizon::Zone::Bonuses::BonusAddAttack>("BonusAddAttack",
		sol::constructors<Horizon::Zone::Bonuses::BonusAddAttack(std::shared_ptr<Unit>)>());
	config_123["get"] = &Horizon::Zone::Bonuses::BonusAddAttack::get;
	config_123["set"] = &Horizon::Zone::Bonuses::BonusAddAttack::set;
	config_123["clear"] = sol::resolve<void()>(&Horizon::Zone::Bonuses::BonusAddAttack::clear);
	config_123["clear_single"] = sol::resolve<void(int)>(&Horizon::Zone::Bonuses::BonusAddAttack::clear);

	sol::usertype<Horizon::Zone::Bonuses::BonusAddAttackPercent> config_124 = state->new_usertype<Horizon::Zone::Bonuses::BonusAddAttackPercent>("BonusAddAttackPercent",
		sol::constructors<Horizon::Zone::Bonuses::BonusAddAttackPercent(std::shared_ptr<Unit>)>());
	config_124["get"] = &Horizon::Zone::Bonuses::BonusAddAttackPercent::get;
	config_124["set"] = &Horizon::Zone::Bonuses::BonusAddAttackPercent::set;
	config_124["clear"] = sol::resolve<void()>(&Horizon::Zone::Bonuses::BonusAddAttackPercent::clear);
	config_124["clear_single"] = sol::resolve<void(int)>(&Horizon::Zone::Bonuses::BonusAddAttackPercent::clear);

	sol::usertype<Horizon::Zone::Bonuses::BonusCriticalRace> config_125 = state->new_usertype<Horizon::Zone::Bonuses::BonusCriticalRace>("BonusCriticalRace",
		sol::constructors<Horizon::Zone::Bonuses::BonusCriticalRace(std::shared_ptr<Unit>)>());
	config_125["get"] = &Horizon::Zone::Bonuses::BonusCriticalRace::get;
	config_125["set"] = &Horizon::Zone::Bonuses::BonusCriticalRace::set;
	config_125["clear"] = sol::resolve<void()>(&Horizon::Zone::Bonuses::BonusCriticalRace::clear);
	config_125["clear_single"] = sol::resolve<void(int)>(&Horizon::Zone::Bonuses::BonusCriticalRace::clear);

	sol::usertype<Horizon::Zone::Bonuses::BonusCriticalRacePercent> config_126 = state->new_usertype<Horizon::Zone::Bonuses::BonusCriticalRacePercent>("BonusCriticalRacePercent",
		sol::constructors<Horizon::Zone::Bonuses::BonusCriticalRacePercent(std::shared_ptr<Unit>)>());
	config_126["get"] = &Horizon::Zone::Bonuses::BonusCriticalRacePercent::get;
	config_126["set"] = &Horizon::Zone::Bonuses::BonusCriticalRacePercent::set;
	config_126["clear"] = sol::resolve<void()>(&Horizon::Zone::Bonuses::BonusCriticalRacePercent::clear);
	config_126["clear_single"] = sol::resolve<void(int)>(&Horizon::Zone::Bonuses::BonusCriticalRacePercent::clear);

	sol::usertype<Horizon::Zone::Bonuses::BonusDamageReductionAgainstSize> config_127 = state->new_usertype<Horizon::Zone::Bonuses::BonusDamageReductionAgainstSize>("BonusDamageReductionAgainstSize",
		sol::constructors<Horizon::Zone::Bonuses::BonusDamageReductionAgainstSize(std::shared_ptr<Unit>)>());
	config_127["get"] = &Horizon::Zone::Bonuses::BonusDamageReductionAgainstSize::get;
	config_127["set"] = &Horizon::Zone::Bonuses::BonusDamageReductionAgainstSize::set;
	config_127["clear"] = sol::resolve<void()>(&Horizon::Zone::Bonuses::BonusDamageReductionAgainstSize::clear);
	config_127["clear_single"] = sol::resolve<void(int)>(&Horizon::Zone::Bonuses::BonusDamageReductionAgainstSize::clear);

	sol::usertype<Horizon::Zone::Bonuses::BonusMagicDamageReductionAgainstSize> config_128 = state->new_usertype<Horizon::Zone::Bonuses::BonusMagicDamageReductionAgainstSize>("BonusMagicDamageReductionAgainstSize",
		sol::constructors<Horizon::Zone::Bonuses::BonusMagicDamageReductionAgainstSize(std::shared_ptr<Unit>)>());
	config_128["get"] = &Horizon::Zone::Bonuses::BonusMagicDamageReductionAgainstSize::get;
	config_128["set"] = &Horizon::Zone::Bonuses::BonusMagicDamageReductionAgainstSize::set;
	config_128["clear"] = sol::resolve<void()>(&Horizon::Zone::Bonuses::BonusMagicDamageReductionAgainstSize::clear);
	config_128["clear_single"] = sol::resolve<void(int)>(&Horizon::Zone::Bonuses::BonusMagicDamageReductionAgainstSize::clear);

	sol::usertype<Horizon::Zone::Bonuses::BonusExpPercentPerRace> config_129 = state->new_usertype<Horizon::Zone::Bonuses::BonusExpPercentPerRace>("BonusExpPercentPerRace",
		sol::constructors<Horizon::Zone::Bonuses::BonusExpPercentPerRace(std::shared_ptr<Unit>)>());
	config_129["get"] = &Horizon::Zone::Bonuses::BonusExpPercentPerRace::get;
	config_129["set"] = &Horizon::Zone::Bonuses::BonusExpPercentPerRace::set;
	config_129["clear"] = sol::resolve<void()>(&Horizon::Zone::Bonuses::BonusExpPercentPerRace::clear);
	config_129["clear_single"] = sol::resolve<void(int)>(&Horizon::Zone::Bonuses::BonusExpPercentPerRace::clear);

	sol::usertype<Horizon::Zone::Bonuses::BonusJobPercentPerRace> config_130 = state->new_usertype<Horizon::Zone::Bonuses::BonusJobPercentPerRace>("BonusJobPercentPerRace",
		sol::constructors<Horizon::Zone::Bonuses::BonusJobPercentPerRace(std::shared_ptr<Unit>)>());
	config_130["get"] = &Horizon::Zone::Bonuses::BonusJobPercentPerRace::get;
	config_130["set"] = &Horizon::Zone::Bonuses::BonusJobPercentPerRace::set;
	config_130["clear"] = sol::resolve<void()>(&Horizon::Zone::Bonuses::BonusJobPercentPerRace::clear);
	config_130["clear_single"] = sol::resolve<void(int)>(&Horizon::Zone::Bonuses::BonusJobPercentPerRace::clear);

	sol::usertype<Horizon::Zone::Bonuses::BonusSkillAttack> config_131 = state->new_usertype<Horizon::Zone::Bonuses::BonusSkillAttack>("BonusSkillAttack",
		sol::constructors<Horizon::Zone::Bonuses::BonusSkillAttack(std::shared_ptr<Unit>)>());
	config_131["get"] = &Horizon::Zone::Bonuses::BonusSkillAttack::get;
	config_131["set"] = &Horizon::Zone::Bonuses::BonusSkillAttack::set;
	config_131["clear"] = sol::resolve<void()>(&Horizon::Zone::Bonuses::BonusSkillAttack::clear);
	config_131["clear_single"] = sol::resolve<void(int)>(&Horizon::Zone::Bonuses::BonusSkillAttack::clear);

	sol::usertype<Horizon::Zone::Bonuses::BonusReduceSPConsumptionOfSkillByPercent> config_132 = state->new_usertype<Horizon::Zone::Bonuses::BonusReduceSPConsumptionOfSkillByPercent>("BonusReduceSPConsumptionOfSkillByPercent",
		sol::constructors<Horizon::Zone::Bonuses::BonusReduceSPConsumptionOfSkillByPercent(std::shared_ptr<Unit>)>());
	config_132["get"] = &Horizon::Zone::Bonuses::BonusReduceSPConsumptionOfSkillByPercent::get;
	config_132["set"] = &Horizon::Zone::Bonuses::BonusReduceSPConsumptionOfSkillByPercent::set;
	config_132["clear"] = sol::resolve<void()>(&Horizon::Zone::Bonuses::BonusReduceSPConsumptionOfSkillByPercent::clear);
	config_132["clear_single"] = sol::resolve<void(int)>(&Horizon::Zone::Bonuses::BonusReduceSPConsumptionOfSkillByPercent::clear);

	sol::usertype<Horizon::Zone::Bonuses::BonusReduceSPConsumptionOfSkill> config_133 = state->new_usertype<Horizon::Zone::Bonuses::BonusReduceSPConsumptionOfSkill>("BonusReduceSPConsumptionOfSkill",
		sol::constructors<Horizon::Zone::Bonuses::BonusReduceSPConsumptionOfSkill(std::shared_ptr<Unit>)>());
	config_133["get"] = &Horizon::Zone::Bonuses::BonusReduceSPConsumptionOfSkill::get;
	config_133["set"] = &Horizon::Zone::Bonuses::BonusReduceSPConsumptionOfSkill::set;
	config_133["clear"] = sol::resolve<void()>(&Horizon::Zone::Bonuses::BonusReduceSPConsumptionOfSkill::clear);
	config_133["clear_single"] = sol::resolve<void(int)>(&Horizon::Zone::Bonuses::BonusReduceSPConsumptionOfSkill::clear);

	sol::usertype<Horizon::Zone::Bonuses::BonusLearnedSkillHeal> config_134 = state->new_usertype<Horizon::Zone::Bonuses::BonusLearnedSkillHeal>("BonusLearnedSkillHeal",
		sol::constructors<Horizon::Zone::Bonuses::BonusLearnedSkillHeal(std::shared_ptr<Unit>)>());
	config_134["get"] = &Horizon::Zone::Bonuses::BonusLearnedSkillHeal::get;
	config_134["set"] = &Horizon::Zone::Bonuses::BonusLearnedSkillHeal::set;
	config_134["clear"] = sol::resolve<void()>(&Horizon::Zone::Bonuses::BonusLearnedSkillHeal::clear);
	config_134["clear_single"] = sol::resolve<void(int)>(&Horizon::Zone::Bonuses::BonusLearnedSkillHeal::clear);

	sol::usertype<Horizon::Zone::Bonuses::BonusHealOfSkillCastedOnSelf> config_135 = state->new_usertype<Horizon::Zone::Bonuses::BonusHealOfSkillCastedOnSelf>("BonusHealOfSkillCastedOnSelf",
		sol::constructors<Horizon::Zone::Bonuses::BonusHealOfSkillCastedOnSelf(std::shared_ptr<Unit>)>());
	config_135["get"] = &Horizon::Zone::Bonuses::BonusHealOfSkillCastedOnSelf::get;
	config_135["set"] = &Horizon::Zone::Bonuses::BonusHealOfSkillCastedOnSelf::set;
	config_135["clear"] = sol::resolve<void()>(&Horizon::Zone::Bonuses::BonusHealOfSkillCastedOnSelf::clear);
	config_135["clear_single"] = sol::resolve<void(int)>(&Horizon::Zone::Bonuses::BonusHealOfSkillCastedOnSelf::clear);

	sol::usertype<Horizon::Zone::Bonuses::BonusSkillKnockback> config_136 = state->new_usertype<Horizon::Zone::Bonuses::BonusSkillKnockback>("BonusSkillKnockback",
		sol::constructors<Horizon::Zone::Bonuses::BonusSkillKnockback(std::shared_ptr<Unit>)>());
	config_136["get"] = &Horizon::Zone::Bonuses::BonusSkillKnockback::get;
	config_136["set"] = &Horizon::Zone::Bonuses::BonusSkillKnockback::set;
	config_136["clear"] = sol::resolve<void()>(&Horizon::Zone::Bonuses::BonusSkillKnockback::clear);
	config_136["clear_single"] = sol::resolve<void(int)>(&Horizon::Zone::Bonuses::BonusSkillKnockback::clear);

	sol::usertype<Horizon::Zone::Bonuses::BonusSkillCastPercent> config_137 = state->new_usertype<Horizon::Zone::Bonuses::BonusSkillCastPercent>("BonusSkillCastPercent",
		sol::constructors<Horizon::Zone::Bonuses::BonusSkillCastPercent(std::shared_ptr<Unit>)>());
	config_137["get"] = &Horizon::Zone::Bonuses::BonusSkillCastPercent::get;
	config_137["set"] = &Horizon::Zone::Bonuses::BonusSkillCastPercent::set;
	config_137["clear"] = sol::resolve<void()>(&Horizon::Zone::Bonuses::BonusSkillCastPercent::clear);
	config_137["clear_single"] = sol::resolve<void(int)>(&Horizon::Zone::Bonuses::BonusSkillCastPercent::clear);

	sol::usertype<Horizon::Zone::Bonuses::BonusSkillCooldown> config_138 = state->new_usertype<Horizon::Zone::Bonuses::BonusSkillCooldown>("BonusSkillCooldown",
		sol::constructors<Horizon::Zone::Bonuses::BonusSkillCooldown(std::shared_ptr<Unit>)>());
	config_138["get"] = &Horizon::Zone::Bonuses::BonusSkillCooldown::get;
	config_138["set"] = &Horizon::Zone::Bonuses::BonusSkillCooldown::set;
	config_138["clear"] = sol::resolve<void()>(&Horizon::Zone::Bonuses::BonusSkillCooldown::clear);
	config_138["clear_single"] = sol::resolve<void(int)>(&Horizon::Zone::Bonuses::BonusSkillCooldown::clear);

	sol::usertype<Horizon::Zone::Bonuses::BonusSkillFixCastPercent> config_139 = state->new_usertype<Horizon::Zone::Bonuses::BonusSkillFixCastPercent>("BonusSkillFixCastPercent",
		sol::constructors<Horizon::Zone::Bonuses::BonusSkillFixCastPercent(std::shared_ptr<Unit>)>());
	config_139["get"] = &Horizon::Zone::Bonuses::BonusSkillFixCastPercent::get;
	config_139["set"] = &Horizon::Zone::Bonuses::BonusSkillFixCastPercent::set;
	config_139["clear"] = sol::resolve<void()>(&Horizon::Zone::Bonuses::BonusSkillFixCastPercent::clear);
	config_139["clear_single"] = sol::resolve<void(int)>(&Horizon::Zone::Bonuses::BonusSkillFixCastPercent::clear);

	sol::usertype<Horizon::Zone::Bonuses::BonusSkillVariableCastPercent> config_140 = state->new_usertype<Horizon::Zone::Bonuses::BonusSkillVariableCastPercent>("BonusSkillVariableCastPercent",
		sol::constructors<Horizon::Zone::Bonuses::BonusSkillVariableCastPercent(std::shared_ptr<Unit>)>());
	config_140["get"] = &Horizon::Zone::Bonuses::BonusSkillVariableCastPercent::get;
	config_140["set"] = &Horizon::Zone::Bonuses::BonusSkillVariableCastPercent::set;
	config_140["clear"] = sol::resolve<void()>(&Horizon::Zone::Bonuses::BonusSkillVariableCastPercent::clear);
	config_140["clear_single"] = sol::resolve<void(int)>(&Horizon::Zone::Bonuses::BonusSkillVariableCastPercent::clear);

	sol::usertype<Horizon::Zone::Bonuses::BonusResistSkillDamagePercent> config_141 = state->new_usertype<Horizon::Zone::Bonuses::BonusResistSkillDamagePercent>("BonusResistSkillDamagePercent",
		sol::constructors<Horizon::Zone::Bonuses::BonusResistSkillDamagePercent(std::shared_ptr<Unit>)>());
	config_141["get"] = &Horizon::Zone::Bonuses::BonusResistSkillDamagePercent::get;
	config_141["set"] = &Horizon::Zone::Bonuses::BonusResistSkillDamagePercent::set;
	config_141["clear"] = sol::resolve<void()>(&Horizon::Zone::Bonuses::BonusResistSkillDamagePercent::clear);
	config_141["clear_single"] = sol::resolve<void(int)>(&Horizon::Zone::Bonuses::BonusResistSkillDamagePercent::clear);

	sol::usertype<Horizon::Zone::Bonuses::BonusIgnoreDefenseFromElement> config_142 = state->new_usertype<Horizon::Zone::Bonuses::BonusIgnoreDefenseFromElement>("BonusIgnoreDefenseFromElement",
		sol::constructors<Horizon::Zone::Bonuses::BonusIgnoreDefenseFromElement(std::shared_ptr<Unit>)>());
	config_142["get"] = &Horizon::Zone::Bonuses::BonusIgnoreDefenseFromElement::get;
	config_142["set"] = &Horizon::Zone::Bonuses::BonusIgnoreDefenseFromElement::set;
	config_142["clear"] = sol::resolve<void()>(&Horizon::Zone::Bonuses::BonusIgnoreDefenseFromElement::clear);
	config_142["clear_single"] = sol::resolve<void(int)>(&Horizon::Zone::Bonuses::BonusIgnoreDefenseFromElement::clear);

	sol::usertype<Horizon::Zone::Bonuses::BonusIgnoreDefenseFromRace> config_143 = state->new_usertype<Horizon::Zone::Bonuses::BonusIgnoreDefenseFromRace>("BonusIgnoreDefenseFromRace",
		sol::constructors<Horizon::Zone::Bonuses::BonusIgnoreDefenseFromRace(std::shared_ptr<Unit>)>());
	config_143["get"] = &Horizon::Zone::Bonuses::BonusIgnoreDefenseFromRace::get;
	config_143["set"] = &Horizon::Zone::Bonuses::BonusIgnoreDefenseFromRace::set;
	config_143["clear"] = sol::resolve<void()>(&Horizon::Zone::Bonuses::BonusIgnoreDefenseFromRace::clear);
	config_143["clear_single"] = sol::resolve<void(int)>(&Horizon::Zone::Bonuses::BonusIgnoreDefenseFromRace::clear);

	sol::usertype<Horizon::Zone::Bonuses::BonusIgnoreMagicDefenseFromElement> config_144 = state->new_usertype<Horizon::Zone::Bonuses::BonusIgnoreMagicDefenseFromElement>("BonusIgnoreMagicDefenseFromElement",
		sol::constructors<Horizon::Zone::Bonuses::BonusIgnoreMagicDefenseFromElement(std::shared_ptr<Unit>)>());
	config_144["get"] = &Horizon::Zone::Bonuses::BonusIgnoreMagicDefenseFromElement::get;
	config_144["set"] = &Horizon::Zone::Bonuses::BonusIgnoreMagicDefenseFromElement::set;
	config_144["clear"] = sol::resolve<void()>(&Horizon::Zone::Bonuses::BonusIgnoreMagicDefenseFromElement::clear);
	config_144["clear_single"] = sol::resolve<void(int)>(&Horizon::Zone::Bonuses::BonusIgnoreMagicDefenseFromElement::clear);

	sol::usertype<Horizon::Zone::Bonuses::BonusIgnoreMagicDefenseFromRace> config_145 = state->new_usertype<Horizon::Zone::Bonuses::BonusIgnoreMagicDefenseFromRace>("BonusIgnoreMagicDefenseFromRace",
		sol::constructors<Horizon::Zone::Bonuses::BonusIgnoreMagicDefenseFromRace(std::shared_ptr<Unit>)>());
	config_145["get"] = &Horizon::Zone::Bonuses::BonusIgnoreMagicDefenseFromRace::get;
	config_145["set"] = &Horizon::Zone::Bonuses::BonusIgnoreMagicDefenseFromRace::set;
	config_145["clear"] = sol::resolve<void()>(&Horizon::Zone::Bonuses::BonusIgnoreMagicDefenseFromRace::clear);
	config_145["clear_single"] = sol::resolve<void(int)>(&Horizon::Zone::Bonuses::BonusIgnoreMagicDefenseFromRace::clear);
	
	sol::usertype<Horizon::Zone::Bonuses::BonusAddEleWeaponDamagePercent> config_146 = state->new_usertype<Horizon::Zone::Bonuses::BonusAddEleWeaponDamagePercent>("BonusAddEleWeaponDamagePercent",
		sol::constructors<Horizon::Zone::Bonuses::BonusAddEleWeaponDamagePercent(std::shared_ptr<Unit>)>());
	config_146["get"] = &Horizon::Zone::Bonuses::BonusAddEleWeaponDamagePercent::get;
	config_146["set"] = &Horizon::Zone::Bonuses::BonusAddEleWeaponDamagePercent::set;
	config_146["clear"] = sol::resolve<void()>(&Horizon::Zone::Bonuses::BonusAddEleWeaponDamagePercent::clear);
	config_146["clear_single"] = sol::resolve<void(int)>(&Horizon::Zone::Bonuses::BonusAddEleWeaponDamagePercent::clear);

	sol::usertype<Horizon::Zone::Bonuses::BonusAddEleMagicDamagePercent> config_147 = state->new_usertype<Horizon::Zone::Bonuses::BonusAddEleMagicDamagePercent>("BonusAddEleMagicDamagePercent",
		sol::constructors<Horizon::Zone::Bonuses::BonusAddEleMagicDamagePercent(std::shared_ptr<Unit>)>());
	config_147["get"] = &Horizon::Zone::Bonuses::BonusAddEleMagicDamagePercent::get;
	config_147["set"] = &Horizon::Zone::Bonuses::BonusAddEleMagicDamagePercent::set;
	config_147["clear"] = sol::resolve<void()>(&Horizon::Zone::Bonuses::BonusAddEleMagicDamagePercent::clear);
	config_147["clear_single"] = sol::resolve<void(int)>(&Horizon::Zone::Bonuses::BonusAddEleMagicDamagePercent::clear);

	sol::usertype<Horizon::Zone::Bonuses::s_autospell> config_148 = state->new_usertype<Horizon::Zone::Bonuses::s_autospell>("s_autospell");
	config_148["lv"] = &Horizon::Zone::Bonuses::s_autospell::lv;
	config_148["id"] = &Horizon::Zone::Bonuses::s_autospell::id;
	config_148["rate"] = &Horizon::Zone::Bonuses::s_autospell::rate;
	config_148["flag"] = &Horizon::Zone::Bonuses::s_autospell::flag;
	config_148["card_id"] = &Horizon::Zone::Bonuses::s_autospell::card_id;
	config_148["skill"] = &Horizon::Zone::Bonuses::s_autospell::skill;
	config_148["count"] = &Horizon::Zone::Bonuses::s_autospell::count;

	sol::usertype<Horizon::Zone::Bonuses::BonusAutoSpellOnSkill> config_149 = state->new_usertype<Horizon::Zone::Bonuses::BonusAutoSpellOnSkill>("BonusAutoSpellOnSkill",
		sol::constructors<Horizon::Zone::Bonuses::BonusAutoSpellOnSkill(std::shared_ptr<Unit>)>());
	config_149["get"] = &Horizon::Zone::Bonuses::BonusAutoSpellOnSkill::get;
	config_149["set"] = &Horizon::Zone::Bonuses::BonusAutoSpellOnSkill::set;
	config_149["clear"] = sol::resolve<void()>(&Horizon::Zone::Bonuses::BonusAutoSpellOnSkill::clear);
	config_149["clear_single"] = sol::resolve<void(int)>(&Horizon::Zone::Bonuses::BonusAutoSpellOnSkill::clear);

	sol::usertype<Horizon::Zone::Bonuses::BonusAutoSpellOnAttack> config_150 = state->new_usertype<Horizon::Zone::Bonuses::BonusAutoSpellOnAttack>("BonusAutoSpellOnAttack",
		sol::constructors<Horizon::Zone::Bonuses::BonusAutoSpellOnAttack(std::shared_ptr<Unit>)>());
	config_150["get"] = &Horizon::Zone::Bonuses::BonusAutoSpellOnAttack::get;
	config_150["set"] = &Horizon::Zone::Bonuses::BonusAutoSpellOnAttack::set;
	config_150["clear"] = sol::resolve<void()>(&Horizon::Zone::Bonuses::BonusAutoSpellOnAttack::clear);
	config_150["clear_single"] = sol::resolve<void(int)>(&Horizon::Zone::Bonuses::BonusAutoSpellOnAttack::clear);

	sol::usertype<Horizon::Zone::Bonuses::BonusAutoSpellOnReceiveDamage> config_151 = state->new_usertype<Horizon::Zone::Bonuses::BonusAutoSpellOnReceiveDamage>("BonusAutoSpellOnReceiveDamage",
		sol::constructors<Horizon::Zone::Bonuses::BonusAutoSpellOnReceiveDamage(std::shared_ptr<Unit>)>());
	config_151["get"] = &Horizon::Zone::Bonuses::BonusAutoSpellOnReceiveDamage::get;
	config_151["set"] = &Horizon::Zone::Bonuses::BonusAutoSpellOnReceiveDamage::set;
	config_151["clear"] = sol::resolve<void()>(&Horizon::Zone::Bonuses::BonusAutoSpellOnReceiveDamage::clear);
	config_151["clear_single"] = sol::resolve<void(int)>(&Horizon::Zone::Bonuses::BonusAutoSpellOnReceiveDamage::clear);

	sol::usertype<Horizon::Zone::Bonuses::BonusAutoSpellOnSelf> config_152 = state->new_usertype<Horizon::Zone::Bonuses::BonusAutoSpellOnSelf>("BonusAutoSpellOnSelf",
		sol::constructors<Horizon::Zone::Bonuses::BonusAutoSpellOnSelf(std::shared_ptr<Unit>)>());
	config_152["get"] = &Horizon::Zone::Bonuses::BonusAutoSpellOnSelf::get;
	config_152["set"] = &Horizon::Zone::Bonuses::BonusAutoSpellOnSelf::set;
	config_152["clear"] = sol::resolve<void()>(&Horizon::Zone::Bonuses::BonusAutoSpellOnSelf::clear);
	config_152["clear_single"] = sol::resolve<void(int)>(&Horizon::Zone::Bonuses::BonusAutoSpellOnSelf::clear);

	sol::usertype<Horizon::Zone::Bonuses::BonusHPVanishPercent> config_153 = state->new_usertype<Horizon::Zone::Bonuses::BonusHPVanishPercent>("BonusHPVanishPercent",
		sol::constructors<Horizon::Zone::Bonuses::BonusHPVanishPercent(std::shared_ptr<Unit>, int, int, int)>());
    config_31["bonus"] = [](std::shared_ptr<Horizon::Zone::Bonuses::BonusHPVanishPercent> t) { return std::static_pointer_cast<Horizon::Zone::Bonuses::Bonus>(t); };
	config_153["get"] = &Horizon::Zone::Bonuses::BonusHPVanishPercent::get;
	config_153["set"] = &Horizon::Zone::Bonuses::BonusHPVanishPercent::set;
	
	sol::usertype<Horizon::Zone::Bonuses::BonusSPVanishPercent> config_154 = state->new_usertype<Horizon::Zone::Bonuses::BonusSPVanishPercent>("BonusSPVanishPercent",
		sol::constructors<Horizon::Zone::Bonuses::BonusSPVanishPercent(std::shared_ptr<Unit>, int, int, int)>());
	config_31["bonus"] = [](std::shared_ptr<Horizon::Zone::Bonuses::BonusSPVanishPercent> t) { return std::static_pointer_cast<Horizon::Zone::Bonuses::Bonus>(t); };
	config_154["get"] = &Horizon::Zone::Bonuses::BonusSPVanishPercent::get;
	config_154["set"] = &Horizon::Zone::Bonuses::BonusSPVanishPercent::set;

	sol::usertype<Horizon::Zone::Bonuses::BonusRaise> config_155 = state->new_usertype<Horizon::Zone::Bonuses::BonusRaise>("BonusRaise",
		sol::constructors<Horizon::Zone::Bonuses::BonusRaise(std::shared_ptr<Unit>, int, int, int)>());
	config_31["bonus"] = [](std::shared_ptr<Horizon::Zone::Bonuses::BonusRaise> t) { return std::static_pointer_cast<Horizon::Zone::Bonuses::Bonus>(t); };
	config_155["get"] = &Horizon::Zone::Bonuses::BonusRaise::get;
	config_155["set"] = &Horizon::Zone::Bonuses::BonusRaise::set;

	sol::usertype<Horizon::Zone::Bonuses::BonusAddItemDropOnMonsterKill> config_156 = state->new_usertype<Horizon::Zone::Bonuses::BonusAddItemDropOnMonsterKill>("BonusAddItemDropOnMonsterKill",
		sol::constructors<Horizon::Zone::Bonuses::BonusAddItemDropOnMonsterKill(std::shared_ptr<Unit>, int, int, int)>());
	config_31["bonus"] = [](std::shared_ptr<Horizon::Zone::Bonuses::BonusAddItemDropOnMonsterKill> t) { return std::static_pointer_cast<Horizon::Zone::Bonuses::Bonus>(t); };
	config_156["get"] = &Horizon::Zone::Bonuses::BonusAddItemDropOnMonsterKill::get;
	config_156["set"] = &Horizon::Zone::Bonuses::BonusAddItemDropOnMonsterKill::set;

	sol::usertype<Horizon::Zone::Bonuses::BonusHPDrainOnMonsterKill> config_157 = state->new_usertype<Horizon::Zone::Bonuses::BonusHPDrainOnMonsterKill>("BonusHPDrainOnMonsterKill",
		sol::constructors<Horizon::Zone::Bonuses::BonusHPDrainOnMonsterKill(std::shared_ptr<Unit>, int, int, int)>());
	config_31["bonus"] = [](std::shared_ptr<Horizon::Zone::Bonuses::BonusHPDrainOnMonsterKill> t) { return std::static_pointer_cast<Horizon::Zone::Bonuses::Bonus>(t); };
	config_157["get"] = &Horizon::Zone::Bonuses::BonusHPDrainOnMonsterKill::get;
	config_157["set"] = &Horizon::Zone::Bonuses::BonusHPDrainOnMonsterKill::set;

	sol::usertype<Horizon::Zone::Bonuses::BonusSPDrainOnMonsterKill> config_158 = state->new_usertype<Horizon::Zone::Bonuses::BonusSPDrainOnMonsterKill>("BonusSPDrainOnMonsterKill",
		sol::constructors<Horizon::Zone::Bonuses::BonusSPDrainOnMonsterKill(std::shared_ptr<Unit>, int, int, int)>());
	config_31["bonus"] = [](std::shared_ptr<Horizon::Zone::Bonuses::BonusSPDrainOnMonsterKill> t) { return std::static_pointer_cast<Horizon::Zone::Bonuses::Bonus>(t); };
	config_158["get"] = &Horizon::Zone::Bonuses::BonusSPDrainOnMonsterKill::get;
	config_158["set"] = &Horizon::Zone::Bonuses::BonusSPDrainOnMonsterKill::set;

}

void UnitComponent::sync_functions(std::shared_ptr<sol::state> state)
{
}
