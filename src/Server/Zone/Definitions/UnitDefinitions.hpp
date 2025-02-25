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

#ifndef HORIZON_ZONE_ENTITIES_DEFINITIONS
#define HORIZON_ZONE_ENTITIES_DEFINITIONS

#include "Server/Common/Configuration/Horizon.hpp"
#include <cstring>

enum unit_size_type
{
	ESZ_SMALL   = 0,
	ESZ_MEDIUM  = 1,
	ESZ_LARGE   = 2,
	ESZ_MAX     = 3
};

enum unit_type : int
{
	UNIT_PLAYER      =  0,
	UNIT_NPC         =  1,
	UNIT_ITEM        =  2,
	UNIT_SKILL       =  3,
	UNIT_UNKNOWN     =  4,
	UNIT_MONSTER     =  5,
	UNIT_EVENT       =  6,
	UNIT_PET         =  7,
	UNIT_HOMUNCULUS  =  8,
	UNIT_MERCENARY   =  9,
	UNIT_ELEMENTAL   = 10,
};

enum unit_type_mask
{
	UNIT_MASK_PLAYER    = 0x0000,
	UNIT_MASK_NPC       = 0x0001,
	UNIT_MASK_ITEM      = 0x0002,
	UNIT_MASK_SKILL     = 0x0004,
	UNIT_MASK_UNKNOWN   = 0x0008,
	UNIT_MASK_MONSTER   = 0x0010,
	UNIT_MASK_EVENT     = 0x0020,
	UNIT_MASK_PET       = 0x0040,
	UNIT_MASK_HOMUNCULUS= 0x0080,
	UNIT_MASK_MERCENARY = 0x0100,
	UNIT_MASK_ELEMENTAL = 0x0200,
	UNIT_MASK_ALL       = 0x0FFF
};

enum directions : short
{
	DIR_NORTH      = 0,
	DIR_NORTH_WEST = 1,
	DIR_WEST       = 2,
	DIR_SOUTH_WEST = 3,
	DIR_SOUTH      = 4,
	DIR_SOUTH_EAST = 5,
	DIR_EAST       = 6,
	DIR_NORTH_EAST = 7
};

enum status_point_type
{
	STATUS_POINT_INVALID              =  -1,
	STATUS_MOVEMENT_SPEED             =   0,
	STATUS_BASEEXP                    =   1,
	STATUS_JOBEXP                     =   2,
	STATUS_KARMA                      =   3,
	STATUS_MANNER                     =   4,
	STATUS_CURRENTHP                  =   5,
	STATUS_MAXHP                      =   6,
	STATUS_CURRENTSP                  =   7,
	STATUS_MAXSP                      =   8,
	STATUS_STATUSPOINT                =   9,
	STATUS_0a                         =  10,
	STATUS_BASELEVEL                  =  11,
	STATUS_SKILLPOINT                 =  12,
	STATUS_STRENGTH                   =  13,
	STATUS_AGILITY                    =  14,
	STATUS_VITALITY                   =  15,
	STATUS_INTELLIGENCE               =  16,
	STATUS_DEXTERITY                  =  17,
	STATUS_LUCK                       =  18,
	STATUS_CLASS                      =  19,
	STATUS_ZENY                       =  20,
	STATUS_SEX                        =  21,
	STATUS_NEXTBASEEXP                =  22,
	STATUS_NEXTJOBEXP                 =  23,
	STATUS_CURRENT_WEIGHT             =  24,
	STATUS_MAX_WEIGHT                 =  25,
	STATUS_1a                         =  26,
	STATUS_1b                         =  27,
	STATUS_1c                         =  28,
	STATUS_1d                         =  29,
	STATUS_1e                         =  30,
	STATUS_1f                         =  31,
	STATUS_STRENGTH_COST              =  32,
	STATUS_AGILITY_COST               =  33,
	STATUS_VITALITY_COST              =  34,
	STATUS_INTELLIGENCE_COST          =  35,
	STATUS_DEXTERITY_COST             =  36,
	STATUS_LUCK_COST                  =  37,
	STATUS_26                         =  38,
	STATUS_27                         =  39,
	STATUS_28                         =  40,
	STATUS_STATUS_ATK                 =  41,
	STATUS_EQUIP_ATK                  =  42,
	STATUS_EQUIP_MATK                 =  43,  // Right side in status window
	STATUS_STATUS_MATK                =  44,  // Left-side in status window
	STATUS_SOFT_DEF                   =  45,
	STATUS_HARD_DEF                   =  46,
	STATUS_SOFT_MDEF                  =  47,
	STATUS_HARD_MDEF                  =  48,
	STATUS_HIT                        =  49,
	STATUS_FLEE                       =  50,
	STATUS_PERFECT_DODGE              =  51,
	STATUS_CRITICAL                   =  52,
	STATUS_ASPD                       =  53,
	STATUS_36                         =  54,
	STATUS_JOBLEVEL                   =  55,
	STATUS_UPPER                      =  56,
	STATUS_PARTNER                    =  57,
	STATUS_CART                       =  58,
	STATUS_FAME                       =  59,
	STATUS_UNBREAKABLE                =  60,
	STATUS_CARTINFO                   =  99,

	STATUS_PSTR                       =  103,
	STATUS_PAGI                       =  104,
	STATUS_PVIT                       =  105,
	STATUS_PINT                       =  106,
	STATUS_PDEX                       =  107,
	STATUS_PLUK                       =  108,

	STATUS_BASEJOB                    =  119,
	STATUS_BASECLASS                  =  120,
	STATUS_KILLERRID                  =  121,
	STATUS_KILLEDRID                  =  122,
	STATUS_SLOTCHANGE                 =  123,
	STATUS_CHARRENAME                 =  124,
	STATUS_MOD_EXP                    =  125,
	STATUS_MOD_DROP                   =  126,
	STATUS_MOD_DEATH                  =  127,
	STATUS_BANKVAULT                  =  128,
	STATUS_MERCFLEE                   =  165,
	STATUS_MERCKILLS                  =  189,
	STATUS_MERCFAITH                  =  190,
	STATUS_POW                        =  219,
	STATUS_STA                        =  220,
	STATUS_WIS                        =  221,
	STATUS_SPL                        =  222,
	STATUS_CON                        =  223,
	STATUS_CRT                        =  224,
	STATUS_PATK                       =  225,
	STATUS_SMATK                      =  226,
	STATUS_RES                        =  227,
	STATUS_MRES                       =  228,
	STATUS_HPLUS                      =  229,
	STATUS_CRATE                      =  230,
	STATUS_T_STATUSPOINT              =  231,
	STATUS_AP                         =  232,
	STATUS_MAXAP				      =  233,
	STATUS_UPOW                       =  247,
	STATUS_USTA                       =  248,
	STATUS_UWIS                       =  249,
	STATUS_USPL                       =  250,
	STATUS_UCON                       =  251,
	STATUS_UCRT                       =  252,

	STATUS_CLONE_SKILL_ID             =  500,
	STATUS_CLONE_SKILL_LV             =  501,
	STATUS_BS_POINT                   =  502,
	STATUS_AM_POINT                   =  503,
	STATUS_TK_POINT                   =  504,
	STATUS_PK_POINT                   =  505,
	STATUS_MISSION_TARGET             =  506,
	STATUS_HATE_SUN                   =  507,
	STATUS_HATE_MOON                  =  508,
	STATUS_HATE_STAR                  =  509,
	STATUS_HOM_INTIMATE               =  510,
	STATUS_PHARMACY_SUCCESS           =  511,
	STATUS_KILL_CHAR                  =  512,
	STATUS_KILLED_CHAR                =  513,
	STATUS_SHOP_POINT                 =  514,
	STATUS_REPRODUCE_ID               =  515,
	STATUS_REPRODUCE_LV               =  516,
	STATUS_DEPOSIT                    =  517,

	STATUS_ATTACKRANGE                = 1000,
	// bonuses
	STATUS_ATKELE                     = 1001,
	STATUS_DEFELE                     = 1002,
	STATUS_CASTRATE                   = 1003,
	STATUS_MAXHPRATE                  = 1004,
	STATUS_MAXSPRATE                  = 1005,
	STATUS_SPRATE                     = 1006,
	STATUS_ADDELE                     = 1007,
	STATUS_ADDRACE                    = 1008,
	STATUS_ADDSIZE                    = 1009,
	STATUS_SUBELE                     = 1010,
	STATUS_SUBRACE                    = 1011,
	STATUS_ADDEFF                     = 1012,
	STATUS_RESEFF                     = 1013,
	STATUS_ASPD_RATE                  = 1015,
	STATUS_HP_RECOV_RATE              = 1016,
	STATUS_SP_RECOV_RATE              = 1017,
	STATUS_SPEED_RATE                 = 1018,
	STATUS_CRITICAL_DEF               = 1019,
	STATUS_NEAR_DEF                   = 1020,
	STATUS_LONG_DEF                   = 1021,
	STATUS_DOUBLE_RATE                = 1022,
	STATUS_MAGIC_ATK_RATE             = 1023,
	STATUS_MATK                       = 1024,
	STATUS_MATK_RATE                  = 1025,
	STATUS_IGNORE_DEF_ELE             = 1026,
	STATUS_IGNORE_DEF_RACE            = 1027,
	STATUS_ATK_RATE                   = 1028,
	STATUS_SPEED_ADDRATE              = 1029,
	STATUS_ASPD_ADDRATE               = 1030,
	STATUS_MAGIC_DEF                  = 1031,
	STATUS_MISC_DEF                   = 1032,
	STATUS_IGNORE_MDEF_ELE            = 1033,
	STATUS_IGNORE_MDEF_RACE           = 1034,
	STATUS_MAGIC_ADDELE               = 1035,
	STATUS_MAGIC_ADDRACE              = 1036,
	STATUS_MAGIC_SUBRACE              = 1037,
	STATUS_PERFECT_HIT_RATE           = 1038,
	STATUS_PERFECT_HIT_ADD_RATE       = 1039,
	STATUS_CRITICAL_RATE              = 1040,
	STATUS_GET_ZENY_NUM               = 1041,
	STATUS_ADD_DAMAGE_CLASS           = 1043,
	STATUS_ADD_MAGIC_DAMAGE_CLASS     = 1044,
	STATUS_ADD_DEF_CLASS              = 1045,
	STATUS_ADD_MDEF_CLASS             = 1046,
	STATUS_ADD_MONSTER_DROP_ITEM      = 1047,
	STATUS_DEF_RATIO_ATK_ELE          = 1048,
	STATUS_DEF_RATIO_ATK_RACE         = 1049,
	STATUS_ADD_SPEED_RATE             = 1050,
	STATUS_HIT_RATE                   = 1051,
	STATUS_FLEE_RATE                  = 1052,
	STATUS_FLEE2_RATE                 = 1053,
	STATUS_DEF_RATE                   = 1054,
	STATUS_DEF2_RATE                  = 1055,
	STATUS_MDEF_RATE                  = 1056,
	STATUS_MDEF2_RATE                 = 1057,
	STATUS_SPLASH_RANGE               = 1058,
	STATUS_SPLASH_ADD_RANGE           = 1059,
	STATUS_AUTOSPELL                  = 1060,
	STATUS_HP_DRAIN_RATE              = 1061,
	STATUS_SP_DRAIN_RATE              = 1062,
	STATUS_SHORT_WEAPON_DAMAGE_RETURN = 1063,
	STATUS_LONG_WEAPON_DAMAGE_RETURN  = 1064,
	STATUS_WEAPON_COMA_ELE            = 1065,
	STATUS_WEAPON_COMA_RACE           = 1066,
	STATUS_ADDEFF2                    = 1067,
	STATUS_BREAK_WEAPON_RATE          = 1068,
	STATUS_BREAK_ARMOR_RATE           = 1069,
	STATUS_ADD_STEAL_RATE             = 1070,
	STATUS_HP_DRAIN_VALUE             = 1071,
	STATUS_SP_DRAIN_VALUE             = 1072,
	STATUS_WEAPON_ATK                 = 1073,
	STATUS_WEAPON_ATK_RATE            = 1074,
	STATUS_AUTOSPELL2                 = 1075,
	STATUS_AUTOSELFSPELL              = 1076,
	STATUS_AUTOSELFSPELL2             = 1077,
	STATUS_ADDREVEFF                  = 1078,
	STATUS_REVAUTOSPELL               = 1079,
	STATUS_REVAUTOSPELL2              = 1080,
	STATUS_REVAUTOSELFSPELL           = 1081,
	STATUS_REVAUTOSELFSPELL2          = 1082,
	STATUS_CRITICAL_DAMAGE_RATE       = 1083,
	STATUS_HP_RECOV_STOP              = 1084,
	STATUS_SP_RECOV_STOP              = 1085,
	STATUS_CRITICALRACE               = 1086,
	STATUS_CRITICALRACERATE           = 1087,
	STATUS_SUB_SIZE                   = 1088,
	STATUS_MAGIC_SUB_SIZE             = 1089,
	STATUS_EXP_RATE                   = 1090,
	STATUS_JOB_RATE                   = 1091,
	STATUS_DEF_HP_DRAIN_VALUE         = 1092,
	STATUS_DEF_SP_DRAIN_VALUE         = 1093,
	STATUS_ADD_SKILL_DAMAGE_RATE      = 1094,
	STATUS_ADD_GROUP                  = 1095,
	STATUS_SUB_GROUP                  = 1096,
	STATUS_HP_PENALTY_TIME            = 1097,
	STATUS_SP_PENALTY_TIME            = 1098,
	STATUS_HP_PENALTY_UNRIG           = 1099,
	STATUS_SP_PENALTY_UNRIG           = 1100,
	STATUS_TIGEREYE                   = 1101,
	STATUS_RACE                       = 1102,
	STATUS_ADD_SKILL_BLOW             = 1103,
	STATUS_MOB_CLASS_CHANGE           = 1104,
	STATUS_ADD_ITEMHEAL_RATE_GROUP    = 1105,
	STATUS_HPVANISH                   = 1106,
	STATUS_SPVANISH                   = 1107,
	STATUS_BONUS_DAMAGE               = 1108,
	STATUS_LOSS_EQUIP_WHEN_DIE        = 1109,
	STATUS_RAISE                      = 1110,
	STATUS_CURSE_BY_MURAMASA          = 1111,
	STATUS_LOSS_EQUIP_WHEN_ATTACK     = 1112,
	STATUS_LOSS_EQUIP_WHEN_HIT        = 1113,
	STATUS_BREAK_MYEQUIP_WHEN_ATTACK  = 1114,
	STATUS_BREAK_MYEQUIP_WHEN_HIT     = 1115,
	STATUS_HP_RATE_PENALTY_UNRIG      = 1116,
	STATUS_SP_RATE_PENALTY_UNRIG      = 1117,
	STATUS_MAGIC_DAMAGE_RETURN        = 1118,
	STATUS_ADD_SHORT_WEAPON_DAMAGE    = 1119,
	STATUS_ADD_LONG_WEAPON_DAMAGE     = 1120,
	STATUS_WEAPON_COMA_ELE2           = 1121,
	STATUS_WEAPON_COMA_RACE2          = 1122,
	STATUS_GET_ZENY_NUM2              = 1123,
	STATUS_ADD_GET_ZENY_NUM2          = 1124,
	STATUS_ADDEFFSHORT                = 1125,
	STATUS_ADDEFFLONG                 = 1126,
	STATUS_ATTACKRANGE_RATE           = 1127,
	STATUS_ATTACKRANGE2               = 1128,
	STATUS_ATTACKRANGE_RATE2          = 1129,
	STATUS_AUTO_SP_CALC_PC            = 1130,
	STATUS_ETERNAL_SP_CHANGE          = 1131,
	STATUS_SP_GAIN_VALUE              = 1132,
	STATUS_HP_GAIN_VALUE              = 1133,
	STATUS_UNBREAKABLE_WEAPON         = 1134,
	STATUS_UNBREAKABLE_ARMOR          = 1135,
	STATUS_UNBREAKABLE_HELM           = 1136,
	STATUS_UNBREAKABLE_SHIELD         = 1137,
	STATUS_IGNORE_DEF_ENEMY           = 1138,
	STATUS_IGNORE_MDEF_ENEMY          = 1139,
	STATUS_DEF_RATIO_ATK_ENEMY        = 1140,
	STATUS_ADDENEMY                   = 1141,
	STATUS_MAGIC_ADDENEMY             = 1142,
	STATUS_SUBENEMY                   = 1143,
	STATUS_SKILL_DELAY_RATE           = 1144,
	STATUS_FIX_MAXHP                  = 1145,
	STATUS_FIX_MAXSP                  = 1146,
	STATUS_FIX_BASEATK                = 1147,
	STATUS_FIX_MATK                   = 1148,
	STATUS_FIX_DEF                    = 1149,
	STATUS_FIX_MDEF                   = 1150,
	STATUS_FIX_HIT                    = 1151,
	STATUS_FIX_CRITICAL               = 1152,
	STATUS_FIX_FLEE                   = 1153,
	STATUS_FIX_ASPD                   = 1154,
	STATUS_FIX_SPEED                  = 1155,
	STATUS_ADD_FIX_CAST_RATE          = 1156,
	STATUS_ADD_SKILL_HEAL_RATE        = 1157,
	STATUS_MATK2_RATE                 = 1158,
	STATUS_AUTOACTIVE_WEAPON          = 1159,
	STATUS_AUTOACTIVE_MAGIC           = 1160,
	STATUS_REVAUTOACTIVE_WEAPON       = 1161,
	STATUS_REVAUTOACTIVE_MAGIC        = 1162,
	STATUS_AUTOACTIVE_ITEM            = 1163,
	STATUS_ADDEFFSKILL                = 1164,
	STATUS_SKILLAUTOSPELL             = 1165,
	STATUS_SKILLAUTOSPELL2            = 1166,
	STATUS_SKILLAUTOSELFSPELL         = 1167,
	STATUS_SKILLAUTOSELFSPELL2        = 1168,
	STATUS_AUTOACTIVE_SKILL           = 1169,
	STATUS_ADD_CAST_RATE              = 1170,
	STATUS_ADDEFFMAGIC                = 1171,
	STATUS_DEF_ELEENEMY               = 1172,
	STATUS_ADD_SP_COST                = 1173,
	STATUS_FIXCASTRATE                = 1174,
	STATUS_ADD_SKILL_SUBHEAL_RATE     = 1175,
	STATUS_ADD_CAST_TIME              = 1176,
	STATUS_ADD_COOL_DOWN              = 1177,
	STATUS_ADD_ELEWEAPONDAMAGE_RATE   = 1178,
	STATUS_ADD_ELEMAGICDAMAGE_RATE    = 1179,
	STATUS_HP_RATE_PENALTY_TIME       = 1180,
	STATUS_SP_RATE_PENALTY_TIME       = 1181,
	STATUS_MAGIC_ADD_GROUP            = 1182,
	STATUS_MAGIC_ADDSIZE              = 1183,
	STATUS_ALLSTATUS                  = 1184,
	STATUS_SUB_SKILL_DAMAGE_RATE      = 1185,
	STATUS_RESTART_FULL_RECORVER      = 1186,
	STATUS_NO_CASTCANCEL              = 1187,
	STATUS_NO_SIZEFIX 			      = 1188,
	STATUS_NO_MAGIC_DAMAGE 		      = 1189,
	STATUS_NO_WEAPON_DAMAGE 		  = 1190,
	STATUS_NO_GEMSTONE                = 1191,
	STATUS_NO_GEARFUEL                = 1192,
	STATUS_INFINITE_ENDURE            = 1193,
	STATUS_ITEM_NO_USE				  = 1194,
	STATUS_NO_KNOCKBACK               = 1195,
	STATUS_ADDATKELE                  = 1196,
	STATUS_ADDATKRACE                 = 1197,
	STATUS_SKILL_ATK                  = 1198,
	STATUS_SKILL_USESPRATE            = 1199,
	STATUS_SKILL_USESP                = 1200,
	STATUS_SKILL_LEARNED_HEAL         = 1201,
	STATUS_SKILL_HEALPOWER_OF_SKILL   = 1202,
	STATUS_SKILL_BLOWN                = 1203,
	STATUS_SKILL_CAST                 = 1204,
	STATUS_SKILL_COOLDOWN             = 1205,
	STATUS_SKILL_FIXCAST              = 1206,
	STATUS_SKILL_VARCAST              = 1207,
	STATUS_SKILL_RESIST               = 1208,
	STATUS_AUTOSPELLONATK 		      = 1209,
	STATUS_AUTOSPELLHIT   		      = 1210,
	STATUS_AUTOSPELLONSELF            = 1211,

	STATUS_VIRTUE                     = 50000,
	STATUS_ADELAY                     = 50001,
	STATUS_DMOTION				      = 50002,
	STATUS_BASE_ATK                   = 50003,
	STATUS_SIZE                       = 50004,
	STATUS_MOB_WEAPON_ATK             = 50005,
	STATUS_CREATE_ATTACK_DAMAGE       = 50006,
	STATUS_MOB_MAGIC_ATTACK_DAMAGE    = 50007,
	STATUS_MOB_VIEW_RANGE             = 50008,
	STATUS_MOB_CHASE_RANGE            = 50009,
	STATUS_MOB_PRIMARY_RACE           = 50010,
	STATUS_MOB_SECONDARY_RACE         = 50011,
	STATUS_MOB_ELEMENT                = 50012,
	STATUS_MOB_ELEMENT_LEVEL          = 50013,
	STATUS_MOB_MODE                   = 50014,
	STATUS_WATK_LEFT                  = 50015,
	STATUS_WATK_RIGHT	              = 50016,
	STATUS_WATK_COMBINED              = 50017,
	STATUS_HP_REGEN                   = 50018,
	STATUS_SP_REGEN                   = 50019
};

enum unit_appearance_type
{
	UAT_BASE                      =  0,
	UAT_HAIR_STYLE                =  1,
	UAT_WEAPON_SPRITE             =  2,
	UAT_HEAD_BOTTOM_SPRITE        =  3,
	UAT_HEAD_TOP_SPRITE           =  4,
	UAT_HEAD_MID_SPRITE           =  5,
	UAT_HAIR_COLOR                =  6,
	UAT_CLOTH_COLOR               =  7,
	UAT_SHIELD_SPRITE             =  8,
	UAT_SHOES                     =  9,
	UAT_BODY                      = 10,
	UAT_FLOOR                     = 11,
	UAT_ROBE_SPRITE               = 12,
	UAT_BODY_STYLE                = 13,
	UAT_MAX
};

enum unit_posture_type : char
{
	POSTURE_STANDING  = 0,
	POSTURE_DEAD      = 1,
	POSTURE_SITTING   = 2,
};

enum job_class_type
{
	JOB_NOVICE                    = 0,
	JOB_SWORDMAN                  = 1,
	JOB_MAGE                      = 2,
	JOB_ARCHER                    = 3,
	JOB_ACOLYTE                   = 4,
	JOB_MERCHANT                  = 5,
	JOB_THIEF                     = 6,
	JOB_KNIGHT                    = 7,
	JOB_PRIEST                    = 8,
	JOB_WIZARD                    = 9,
	JOB_BLACKSMITH                = 10,
	JOB_HUNTER                    = 11,
	JOB_ASSASSIN                  = 12,
	//JOB_KNIGHT2                   = 13,
	JOB_CRUSADER                  = 14,
	JOB_MONK                      = 15,
	JOB_SAGE                      = 16,
	JOB_ROGUE                     = 17,
	JOB_ALCHEMIST                 = 18,
	JOB_BARD                      = 19,
	JOB_DANCER                    = 20,
	JOB_CRUSADER2                 = 21,
	JOB_WEDDING                   = 22,
	JOB_SUPER_NOVICE              = 23,
	JOB_GUNSLINGER                = 24,
	JOB_NINJA                     = 25,
	JOB_XMAS                      = 26,
	JOB_SUMMER                    = 27,
	// 4000-
	JOB_NOVICE_HIGH               = 4001,
	JOB_SWORDMAN_HIGH             = 4002,
	JOB_MAGE_HIGH                 = 4003,
	JOB_ARCHER_HIGH               = 4004,
	JOB_ACOLYTE_HIGH              = 4005,
	JOB_MERCHANT_HIGH             = 4006,
	JOB_THIEF_HIGH                = 4007,
	JOB_LORD_KNIGHT               = 4008,
	JOB_HIGH_PRIEST               = 4009,
	JOB_HIGH_WIZARD               = 4010,
	JOB_WHITESMITH                = 4011,
	JOB_SNIPER                    = 4012,
	JOB_ASSASSIN_CROSS            = 4013,
	JOB_LORD_KNIGHT2              = 4014,
	JOB_PALADIN                   = 4015,
	JOB_CHAMPION                  = 4016,
	JOB_PROFESSOR                 = 4017,
	JOB_STALKER                   = 4018,
	JOB_CREATOR                   = 4019,
	JOB_CLOWN                     = 4020,
	JOB_GYPSY                     = 4021,
	JOB_PALADIN2                  = 4022,
	JOB_BABY_NOVICE               = 4023,
	JOB_BABY_SWORDMAN             = 4024,
	JOB_BABY_MAGE                 = 4025,
	JOB_BABY_ARCHER               = 4026,
	JOB_BABY_ACOLYTE              = 4027,
	JOB_BABY_MERCHANT             = 4028,
	JOB_BABY_THIEF                = 4029,
	JOB_BABY_KNIGHT               = 4030,
	JOB_BABY_PRIEST               = 4031,
	JOB_BABY_WIZARD               = 4032,
	JOB_BABY_BLACKSMITH           = 4033,
	JOB_BABY_HUNTER               = 4034,
	JOB_BABY_ASSASSIN             = 4035,
	JOB_BABY_KNIGHT2              = 4036,
	JOB_BABY_CRUSADER             = 4037,
	JOB_BABY_MONK                 = 4038,
	JOB_BABY_SAGE                 = 4039,
	JOB_BABY_ROGUE                = 4040,
	JOB_BABY_ALCHEMIST            = 4041,
	JOB_BABY_BARD                 = 4042,
	JOB_BABY_DANCER               = 4043,
	JOB_BABY_CRUSADER2            = 4044,
	JOB_SUPER_BABY                = 4045,
	JOB_TAEKWON                   = 4046,
	JOB_STAR_GLADIATOR            = 4047,
	JOB_STAR_GLADIATOR2           = 4048,
	JOB_SOUL_LINKER               = 4049,
	JOB_GANGSI                    = 4050,
	JOB_DEATH_KNIGHT              = 4051,
	JOB_DARK_COLLECTOR            = 4052,
	// 4053-
	JOB_RUNE_KNIGHT               = 4054,
	JOB_WARLOCK                   = 4055,
	JOB_RANGER                    = 4056,
	JOB_ARCH_BISHOP               = 4057,
	JOB_MECHANIC                  = 4058,
	JOB_GUILLOTINE_CROSS          = 4059,
	JOB_RUNE_KNIGHT_T             = 4060,
	JOB_WARLOCK_T                 = 4061,
	JOB_RANGER_T                  = 4062,
	JOB_ARCH_BISHOP_T             = 4063,
	JOB_MECHANIC_T                = 4064,
	JOB_GUILLOTINE_CROSS_T        = 4065,
	JOB_ROYAL_GUARD               = 4066,
	JOB_SORCERER                  = 4067,
	JOB_MINSTREL                  = 4068,
	JOB_WANDERER                  = 4069,
	JOB_SURA                      = 4070,
	JOB_GENETIC                   = 4071,
	JOB_SHADOW_CHASER             = 4072,
	JOB_ROYAL_GUARD_T             = 4073,
	JOB_SORCERER_T                = 4074,
	JOB_MINSTREL_T                = 4075,
	JOB_WANDERER_T                = 4076,
	JOB_SURA_T                    = 4077,
	JOB_GENETIC_T                 = 4078,
	JOB_SHADOW_CHASER_T           = 4079,
	JOB_RUNE_KNIGHT2              = 4080,
	JOB_RUNE_KNIGHT_T2            = 4081,
	JOB_ROYAL_GUARD2              = 4082,
	JOB_ROYAL_GUARD_T2            = 4083,
	JOB_RANGER2                   = 4084,
	JOB_RANGER_T2                 = 4085,
	JOB_MECHANIC2                 = 4086,
	JOB_MECHANIC_T2               = 4087,
	//4088-4097
	JOB_BABY_RUNE_KNIGHT          = 4096,
	JOB_BABY_WARLOCK              = 4097,
	JOB_BABY_RANGER               = 4098,
	JOB_BABY_ARCH_BISHOP               = 4099,
	JOB_BABY_MECHANIC             = 4100,
	JOB_BABY_GUILLOTINE_CROSS     = 4101,
	JOB_BABY_ROYAL_GUARD          = 4102,
	JOB_BABY_SORCERER             = 4103,
	JOB_BABY_MINSTREL             = 4104,
	JOB_BABY_WANDERER             = 4105,
	JOB_BABY_SURA                 = 4106,
	JOB_BABY_GENETIC              = 4107,
	JOB_BABY_SHADOW_CHASER        = 4108,
	JOB_BABY_RUNE_KNIGHT2         = 4109,
	JOB_BABY_ROYAL_GUARD2         = 4110,
	JOB_BABY_RANGER2              = 4111,
	JOB_BABY_MECHANIC2            = 4112,
	JOB_SUPER_NOVICE_E            = 4190,
	JOB_SUPER_BABY_E              = 4191,
	JOB_KAGEROU                   = 4211,
	JOB_OBORO                     = 4212,
	JOB_REBELLION                 = 4215,
	JOB_SUMMONER                  = 4218,
	JOB_MAX,
	JOB_INVALID                   = -1,
	JOB_BASE_START                = JOB_SWORDMAN,
	JOB_BASE_END                  = JOB_THIEF,
	JOB_2_1_START                 = JOB_KNIGHT,
	JOB_2_1_END                   = JOB_ASSASSIN,
	JOB_2_2_START                 = JOB_CRUSADER,
	JOB_2_2_END                   = JOB_DANCER,
	JOB_TRANS_BASE_START          = JOB_SWORDMAN_HIGH,
	JOB_TRANS_BASE_END            = JOB_THIEF_HIGH,
	JOB_TRANS_2_1_START           = JOB_LORD_KNIGHT,
	JOB_TRANS_2_1_END             = JOB_ASSASSIN_CROSS,
	JOB_TRANS_2_2_START           = JOB_PALADIN,
	JOB_TRANS_2_2_END             = JOB_GYPSY,
	JOB_BABY_BASE_START           = JOB_BABY_SWORDMAN,
	JOB_BABY_BASE_END             = JOB_BABY_THIEF,
	JOB_BABY_2_1_START            = JOB_BABY_KNIGHT,
	JOB_BABY_2_1_END              = JOB_BABY_ASSASSIN,
	JOB_BABY_2_2_START            = JOB_BABY_CRUSADER,
	JOB_BABY_2_2_END              = JOB_BABY_DANCER,
	JOB_3_1_START                 = JOB_RUNE_KNIGHT,
	JOB_3_1_END                   = JOB_GUILLOTINE_CROSS,
	JOB_3_2_START                 = JOB_ROYAL_GUARD,
	JOB_3_2_END                   = JOB_SHADOW_CHASER,
	JOB_TRANS_3_1_START           = JOB_RUNE_KNIGHT_T,
	JOB_TRANS_3_1_END             = JOB_GUILLOTINE_CROSS_T,
	JOB_TRANS_3_2_START           = JOB_ROYAL_GUARD_T,
	JOB_TRANS_3_2_END             = JOB_SHADOW_CHASER_T,
	JOB_BABY_3_1_START            = JOB_BABY_RUNE_KNIGHT,
	JOB_BABY_3_1_END              = JOB_BABY_GUILLOTINE_CROSS,
	JOB_BABY_3_2_START            = JOB_BABY_ROYAL_GUARD,
	JOB_BABY_3_2_END              = JOB_BABY_SHADOW_CHASER
};

enum job_class_mask : uint64_t
{
	JMASK_INVALID                 = 0x00000000000,
	JMASK_NOVICE                  = 0x00000000001,
	JMASK_SWORDMAN                = 0x00000000002,
	JMASK_MAGE                    = 0x00000000004,
	JMASK_ARCHER                  = 0x00000000008,
	JMASK_ACOLYTE                 = 0x00000000010,
	JMASK_MERCHANT                = 0x00000000020,
	JMASK_THIEF                   = 0x00000000040,
	JMASK_GANGSI                  = 0x00000000080,
	JMASK_SUMMONER                = 0x00000000100,
	JMASK_TAEKWON_BASE            = 0x00000000200,
	JMASK_GUNSLINGER_BASE         = 0x00000000400,
	JMASK_NINJA_BASE              = 0x00000000800,

	JMASK_BASE                    = 0x00000000FFF,

	JMASK_WEDDING                 = 0x00000001000,

	JMASK_2_1                     = 0x00000100000,
	JMASK_2_2                     = 0x00000200000,
	JMASK_BABY_BASE               = 0x00000400000,
	JMASK_BABY_1_1                = 0x00000800000,
	JMASK_BABY_1_2                = 0x00001000000,
	JMASK_BABY_2_1                = 0x00002000000,
	JMASK_BABY_2_2                = 0x00004000000,
	JMASK_TRANS_BASE              = 0x00008000000,
	JMASK_TRANS_1_1               = 0x00010000000,
	JMASK_TRANS_1_2               = 0x00020000000,
	JMASK_TRANS_2_1               = 0x00040000000,
	JMASK_TRANS_2_2               = 0x00080000000,
	JMASK_3_1                     = 0x00100000000,
	JMASK_3_2                     = 0x00200000000,
	JMASK_TRANS_3_1               = 0x00400000000,
	JMASK_TRANS_3_2               = 0x00800000000,
	JMASK_BABY_3_1                = 0x01000000000,
	JMASK_BABY_3_2                = 0x02000000000,
	JMASK_EXPANDED                = 0x04000000000,
	JMASK_EXPANDED_BABY           = 0x08000000000,
	JMASK_EXPANDED_2_1            = 0x10000000000,
	JMASK_EXPANDED_2_2            = 0x20000000000,

	JMASK_NORMAL                  = JMASK_2_2 | JMASK_2_1 | JMASK_BASE,
	JMASK_BABY                    = JMASK_BABY_2_1 | JMASK_BABY_2_2 | JMASK_BABY_1_1 | JMASK_BABY_1_2 | JMASK_BABY_BASE,
	JMASK_TRANS                   = JMASK_TRANS_2_1 | JMASK_TRANS_2_2 | JMASK_TRANS_1_1 | JMASK_TRANS_1_2 | JMASK_TRANS_BASE,
	JMASK_3                       = JMASK_3_1 | JMASK_3_2,
	JMASK_TRANS_3                 = JMASK_TRANS_3_1 | JMASK_TRANS_3_2,
	JMASK_BABY_3                  = JMASK_BABY_3_1 | JMASK_BABY_3_2,

	// 2-1 Jobs
	JMASK_KNIGHT                  = JMASK_2_1 | JMASK_SWORDMAN,
	JMASK_WIZARD                  = JMASK_2_1 | JMASK_MAGE,
	JMASK_HUNTER                  = JMASK_2_1 | JMASK_ARCHER,
	JMASK_PRIEST                  = JMASK_2_1 | JMASK_ACOLYTE,
	JMASK_BLACKSMITH              = JMASK_2_1 | JMASK_MERCHANT,
	JMASK_ASSASSIN                = JMASK_2_1 | JMASK_THIEF,
	JMASK_DEATH_KNIGHT            = JMASK_2_1 | JMASK_GANGSI,

	// 2-2 Jobs
	JMASK_CRUSADER                = JMASK_2_2 | JMASK_SWORDMAN,
	JMASK_SAGE                    = JMASK_2_2 | JMASK_MAGE,
	JMASK_BARDDANCER              = JMASK_2_2 | JMASK_ARCHER,
	JMASK_MONK                    = JMASK_2_2 | JMASK_ACOLYTE,
	JMASK_ALCHEMIST               = JMASK_2_2 | JMASK_MERCHANT,
	JMASK_ROGUE                   = JMASK_2_2 | JMASK_THIEF,
	JMASK_DARK_COLLECTOR          = JMASK_2_2 | JMASK_GANGSI,

	//Trans Novice And Trans 1-1 Jobs
	JMASK_NOVICE_HIGH             = JMASK_TRANS_BASE | JMASK_NOVICE,
	JMASK_SWORDMAN_HIGH           = JMASK_TRANS_BASE | JMASK_SWORDMAN,
	JMASK_MAGE_HIGH               = JMASK_TRANS_BASE | JMASK_MAGE,
	JMASK_ARCHER_HIGH             = JMASK_TRANS_BASE | JMASK_ARCHER,
	JMASK_ACOLYTE_HIGH            = JMASK_TRANS_BASE | JMASK_ACOLYTE,
	JMASK_MERCHANT_HIGH           = JMASK_TRANS_BASE | JMASK_MERCHANT,
	JMASK_THIEF_HIGH              = JMASK_TRANS_BASE | JMASK_THIEF,

	//Trans 2-1 Jobs
	JMASK_LORD_KNIGHT             = JMASK_TRANS_1_1 | JMASK_KNIGHT,
	JMASK_HIGH_WIZARD             = JMASK_TRANS_1_1 | JMASK_WIZARD,
	JMASK_SNIPER                  = JMASK_TRANS_1_1 | JMASK_HUNTER,
	JMASK_HIGH_PRIEST             = JMASK_TRANS_1_1 | JMASK_PRIEST,
	JMASK_WHITESMITH              = JMASK_TRANS_1_1 | JMASK_BLACKSMITH,
	JMASK_ASSASSIN_CROSS          = JMASK_TRANS_1_1 | JMASK_ASSASSIN,

	//Trans 2-2 Jobs
	JMASK_PALADIN                 = JMASK_TRANS_1_2 | JMASK_CRUSADER,
	JMASK_PROFESSOR               = JMASK_TRANS_1_2 | JMASK_SAGE,
	JMASK_CLOWNGYPSY              = JMASK_TRANS_1_2 | JMASK_BARDDANCER,
	JMASK_CHAMPION                = JMASK_TRANS_1_2 | JMASK_MONK,
	JMASK_CREATOR                 = JMASK_TRANS_1_2 | JMASK_ALCHEMIST,
	JMASK_STALKER                 = JMASK_TRANS_1_2 | JMASK_ROGUE,

	//Baby Novice And Baby 1-1 Jobs
	JMASK_BABY_NOVICE             = JMASK_BABY_BASE | JMASK_NOVICE,
	JMASK_BABY_SWORDMAN           = JMASK_BABY_BASE | JMASK_SWORDMAN,
	JMASK_BABY_MAGE               = JMASK_BABY_BASE | JMASK_MAGE,
	JMASK_BABY_ARCHER             = JMASK_BABY_BASE | JMASK_ARCHER,
	JMASK_BABY_ACOLYTE            = JMASK_BABY_BASE | JMASK_ACOLYTE,
	JMASK_BABY_MERCHANT           = JMASK_BABY_BASE | JMASK_MERCHANT,
	JMASK_BABY_THIEF              = JMASK_BABY_BASE | JMASK_THIEF,

	//Baby 2-1 Jobs
	JMASK_BABY_KNIGHT             = JMASK_BABY_1_1 | JMASK_KNIGHT,
	JMASK_BABY_WIZARD             = JMASK_BABY_1_1 | JMASK_WIZARD,
	JMASK_BABY_HUNTER             = JMASK_BABY_1_1 | JMASK_HUNTER,
	JMASK_BABY_PRIEST             = JMASK_BABY_1_1 | JMASK_PRIEST,
	JMASK_BABY_BLACKSMITH         = JMASK_BABY_1_1 | JMASK_BLACKSMITH,
	JMASK_BABY_ASSASSIN           = JMASK_BABY_1_1 | JMASK_ASSASSIN,

	//Baby 2-2 Jobs
	JMASK_BABY_CRUSADER           = JMASK_BABY_1_2 | JMASK_CRUSADER,
	JMASK_BABY_SAGE               = JMASK_BABY_1_2 | JMASK_SAGE,
	JMASK_BABY_BARDDANCER         = JMASK_BABY_1_2 | JMASK_BARDDANCER,
	JMASK_BABY_MONK               = JMASK_BABY_1_2 | JMASK_MONK,
	JMASK_BABY_ALCHEMIST          = JMASK_BABY_1_2 | JMASK_ALCHEMIST,
	JMASK_BABY_ROGUE              = JMASK_BABY_1_2 | JMASK_ROGUE,

	//3-1 Jobs
	JMASK_RUNE_KNIGHT             = JMASK_3_1 | JMASK_KNIGHT,
	JMASK_WARLOCK                 = JMASK_3_1 | JMASK_WIZARD,
	JMASK_RANGER                  = JMASK_3_1 | JMASK_HUNTER,
	JMASK_ARCH_BISHOP             = JMASK_3_1 | JMASK_PRIEST,
	JMASK_MECHANIC                = JMASK_3_1 | JMASK_BLACKSMITH,
	JMASK_GUILLOTINE_CROSS        = JMASK_3_1 | JMASK_ASSASSIN,

	//3-2 Jobs
	JMASK_ROYAL_GUARD             = JMASK_3_2 | JMASK_CRUSADER,
	JMASK_SORCERER                = JMASK_3_2 | JMASK_SAGE,
	JMASK_MINSTRELWANDERER        = JMASK_3_2 | JMASK_BARDDANCER,
	JMASK_SURA                    = JMASK_3_2 | JMASK_MONK,
	JMASK_GENETIC                 = JMASK_3_2 | JMASK_ALCHEMIST,
	JMASK_SHADOW_CHASER           = JMASK_3_2 | JMASK_ROGUE,

	//Trans 3-1 Jobs
	JMASK_RUNE_KNIGHT_T           = JMASK_TRANS_3_1 | JMASK_KNIGHT,
	JMASK_WARLOCK_T               = JMASK_TRANS_3_1 | JMASK_HIGH_WIZARD,
	JMASK_RANGER_T                = JMASK_TRANS_3_1 | JMASK_SNIPER,
	JMASK_ARCH_BISHOP_T           = JMASK_TRANS_3_1 | JMASK_HIGH_PRIEST,
	JMASK_MECHANIC_T              = JMASK_TRANS_3_1 | JMASK_WHITESMITH,
	JMASK_GUILLOTINE_CROSS_T      = JMASK_TRANS_3_1 | JMASK_ASSASSIN_CROSS,

	//Trans 3-2 Jobs
	JMASK_ROYAL_GUARD_T           = JMASK_TRANS_3_2 | JMASK_PALADIN,
	JMASK_SORCERER_T              = JMASK_TRANS_3_2 | JMASK_PROFESSOR,
	JMASK_MINSTRELWANDERER_T      = JMASK_TRANS_3_2 | JMASK_CLOWNGYPSY,
	JMASK_SURA_T                  = JMASK_TRANS_3_2 | JMASK_CHAMPION,
	JMASK_GENETIC_T               = JMASK_TRANS_3_2 | JMASK_CREATOR,
	JMASK_SHADOW_CHASER_T         = JMASK_TRANS_3_2 | JMASK_STALKER,

	//Baby 3-1 Jobs
	JMASK_BABY_RUNE_KNIGHT        = JMASK_BABY_3_1 | JMASK_KNIGHT,
	JMASK_BABY_WARLOCK            = JMASK_BABY_3_1 | JMASK_WIZARD,
	JMASK_BABY_RANGER             = JMASK_BABY_3_1 | JMASK_HUNTER,
	JMASK_BABY_ARCH_BISHOP        = JMASK_BABY_3_1 | JMASK_PRIEST,
	JMASK_BABY_MECHANIC           = JMASK_BABY_3_1 | JMASK_BLACKSMITH,
	JMASK_BABY_GUILLOTINE_CROSS   = JMASK_BABY_3_1 | JMASK_ASSASSIN,

	//Baby 3-2 Jobs
	JMASK_BABY_ROYAL_GUARD        = JMASK_BABY_3_2 | JMASK_CRUSADER,
	JMASK_BABY_SORCERER           = JMASK_BABY_3_2 | JMASK_SAGE,
	JMASK_BABY_MINSTRELWANDERER   = JMASK_BABY_3_2 | JMASK_BARDDANCER,
	JMASK_BABY_SURA               = JMASK_BABY_3_2 | JMASK_MONK,
	JMASK_BABY_GENETIC            = JMASK_BABY_3_2 | JMASK_ALCHEMIST,
	JMASK_BABY_SHADOW_CHASER      = JMASK_BABY_3_2 | JMASK_ROGUE,

	// Expanded Jobs
	JMASK_TAEKWON                 = JMASK_EXPANDED | JMASK_TAEKWON_BASE,
	JMASK_STAR_GLADIATOR          = JMASK_EXPANDED_2_1 | JMASK_TAEKWON,
	JMASK_SOUL_LINKER             = JMASK_EXPANDED_2_2 | JMASK_TAEKWON,

	JMASK_SUPER_NOVICE            = JMASK_EXPANDED | JMASK_NOVICE,
	JMASK_SUPER_NOVICE_E          = JMASK_EXPANDED_2_1 | JMASK_SUPER_NOVICE,

	JMASK_SUPER_BABY              = JMASK_EXPANDED_BABY | JMASK_BABY_NOVICE,
	JMASK_SUPER_BABY_E            = JMASK_EXPANDED_2_1 | JMASK_SUPER_BABY,

	JMASK_GUNSLINGER              = JMASK_EXPANDED | JMASK_GUNSLINGER_BASE,
	JMASK_REBELLION               = JMASK_EXPANDED_2_1 | JMASK_GUNSLINGER,

	JMASK_NINJA                   = JMASK_EXPANDED | JMASK_NINJA_BASE,
	JMASK_KAGEROUOBORO            = JMASK_EXPANDED_2_1 | JMASK_NINJA,

	JMASK_ALL                     = 0xFFFFFFFFFFFFFFFF,
};

enum unit_viewport_notification_type
{
	EVP_NOTIFY_IN_SIGHT          = -1,
	EVP_NOTIFY_OUT_OF_SIGHT      = 0,
	EVP_NOTIFY_DEAD              = 1,
	EVP_NOTIFY_LOGGED_OUT        = 2,
	EVP_NOTIFY_TELEPORT          = 3,
	EVP_NOTIFY_TRICKDEAD         = 4
};

struct viewport_entry
{
	unit_type _unit_type{UNIT_PLAYER};
	uint32_t _guid{ 0 };
};

struct unit_viewport_entry : public viewport_entry
{
	virtual unit_viewport_entry operator = (unit_viewport_entry const &right)
	{
		_unit_type = right._unit_type;
		_guid = right._guid;
		character_id = right.character_id;
		speed = right.speed;
		body_state = right.body_state;
		health_state = right.health_state;
		effect_state = right.effect_state;
		job_id = right.job_id;
		hair_style_id = right.hair_style_id;
		weapon_id = right.weapon_id;
		headgear_bottom_id = right.headgear_bottom_id;
		headgear_top_id = right.headgear_top_id;
		headgear_mid_id = right.headgear_mid_id;
		hair_color_id = right.hair_color_id;
		cloth_color_id = right.cloth_color_id;
		head_direction = right.head_direction;
		robe_id = right.robe_id;
		guild_id = right.guild_id;
		guild_emblem_version = right.guild_emblem_version;
		honor = right.honor;
		virtue = right.virtue;
		in_pk_mode = right.in_pk_mode;
		gender = right.gender;
		current_x = right.current_x;
		current_y = right.current_y;
		to_x = right.to_x;
		to_y = right.to_y;
		current_dir = right.current_dir;
		x_size = right.x_size;
		y_size = right.y_size;
		posture = right.posture;
		base_level = right.base_level;
		font = right.font;
		max_hp = right.max_hp;
		hp = right.hp;
		is_boss = right.is_boss;
		body_style_id = right.body_style_id;
		std::strncpy(name, right.name, MAX_UNIT_NAME_LENGTH);
		move_start_time = right.move_start_time;
		return *this;
	}

	int32_t character_id{0};
	int16_t speed{150};
	int16_t body_state{0};
	int16_t health_state{0};
	int32_t effect_state{0};
	int16_t job_id{0};
	int16_t hair_style_id{0};
	int32_t weapon_id{0};
#if (CLIENT_TYPE == 'M' && PACKET_VERSION >= 20181121) \
|| (CLIENT_TYPE == 'R' && PACKET_VERSION >= 20180704) \
|| (CLIENT_TYPE == 'Z' && PACKET_VERSION >= 20181114)
	int32_t shield_id{0};
#endif
	int16_t headgear_bottom_id{0};
	int16_t headgear_top_id{0};
	int16_t headgear_mid_id{0};
	int16_t hair_color_id{0};
	int16_t cloth_color_id{0};
	directions head_direction{DIR_SOUTH}; // int16_t
	int16_t robe_id{0};
	int32_t guild_id{0};
	int16_t guild_emblem_version{0};
	int16_t honor{0};
	int32_t virtue{0};
	int8_t in_pk_mode{0};
	int8_t gender{0};
	int16_t current_x{0}, current_y{0}, current_dir{0};
	int16_t to_x{0}, to_y{0};
	int8_t x_size{0};
	int8_t y_size{0};
	unit_posture_type posture{POSTURE_STANDING};
	int16_t base_level{0};
	int16_t font{0};
	int32_t max_hp{-1};
	int32_t hp{-1};
	int8_t is_boss{0};
	int16_t body_style_id{0};
	char name[MAX_UNIT_NAME_LENGTH]{0};
	int32_t move_start_time;
};

struct item_viewport_entry : public viewport_entry
{
	item_viewport_entry operator = (item_viewport_entry const &right)
	{
		_unit_type = right._unit_type;
		_guid = right._guid;
		item_id = right.item_id;
		is_identified = right.is_identified;
		x = right.x;
		y = right.y;
		amount = right.amount;
		x_area = right.x_area;
		y_area = right.y_area;
		return *this;
	}

#if (CLIENT_TYPE == 'M' && PACKET_VERSION >= 20181121) || \
	(CLIENT_TYPE == 'R' && PACKET_VERSION >= 20180704) || \
	(CLIENT_TYPE == 'Z' && PACKET_VERSION >= 20181114)
	uint32_t item_id{ 0 };
#else
	uint16_t item_id{ 0 };
#endif
	uint8_t is_identified{ 0 };
	uint16_t x{ 0 };
	uint16_t y{ 0 };
	uint16_t amount{ 0 };
	uint8_t x_area{ 0 };
	uint8_t y_area{ 0 };
};

enum element_type : uint8_t
{
	ELE_NEUTRAL = 0,
	ELE_WATER   = 1,
	ELE_EARTH   = 2,
	ELE_FIRE    = 3,
	ELE_WIND    = 4,
	ELE_POISON  = 5,
	ELE_HOLY    = 6,
	ELE_DARK    = 7,
	ELE_GHOST   = 8,
	ELE_UNDEAD  = 9,
	ELE_MAX     = 10,
	ELE_WEAPON  = 11,
	ELE_ENDOWED = 12,
	ELE_RANDOM  = 13
};

enum unit_gender_types : int8_t
{
	UNIT_GENDER_FEMALE = 0,
	UNIT_GENDER_MALE   = 1,
};

#endif /* HORIZON_ZONE_ENTITIES_DEFINITIONS */
