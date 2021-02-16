---------------------------------------------------------------------------
--       _   _            _                                              --
--      | | | |          (_)                                             --
--      | |_| | ___  _ __ _ _______  _ __                                --
--      |  _  |/ _ \| '__| |_  / _ \| '_  \                              --
--      | | | | (_) | |  | |/ / (_) | | | |                              --
--      \_| |_/\___/|_|  |_/___\___/|_| |_|                              --
---------------------------------------------------------------------------
-- This file is part of Horizon (c).
-- Copyright (c) 2018 Horizon Dev Team.
--
-- Base Author - Sagun K. (sagunxp@gmail.com)
--
-- This library is free software; you can redistribute it and/or modify,
-- it under the terms of the GNU General Public License as published by,
-- the Free Software Foundation, either version 3 of the License, or,
-- (at your option) any later version.
--
-- This library is distributed in the hope that it will be useful,
-- but WITHOUT ANY WARRANTY; without even the implied warranty of,
-- MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the,
-- GNU General Public License for more details.
--
-- You should have received a copy of the GNU General Public License,
-- along with this library.  If not, see <http://www.gnu.org/licenses/>.
---------------------------------------------------------------------------
--- Renewal Skill Database.
---------------------------------------------------------------------------

--[[-----------------------------------------------------------------------
 --------------------Entry Structure --------------------------------------
 ---------------------------------------------------------------------------
Job_Name = { -- Job names as in src/map/pc.c (they are hard-coded at the moment so if you want to add a new job you should add it there)
	Inherit = { "Other_Job_Name" }, -- Base job from which this job will inherit its skill tree. NV_TRICKDEAD inheritance is skipped for non-novices from the source,

	Skills = { -- SKILL_NAMEs come from the Name value in db/re/skill_db.conf,
		SKILL_NAME1 = Max_Level, -- Use this for skills that don't have other skill prerequisite; Max_Level is a numeric value that should match your client side files,
		SKILL_NAME2 = { -- Use this for skills which have other skills as prerequisites,
			MaxLevel = Max_Level, -- Max_Level is a numeric value that should match your client side files,
			SKILL_NAME_PREREQUISITE = Level_Prerequisite, -- The prerequisite skill and min level for having this skill available. Should also match your client side files,
			SKILL_NAME_PREREQUISITE2 = Level_Prerequisite2, -- You can add as many prerequisite skills as you want. Minimum of 1 if you add a skill this way,
	},
},
-----------------------------------------------------------------------------]]

Novice = {
	Skills = {
		NV_BASIC = 9,
		NV_FIRSTAID = 1,
		NV_TRICKDEAD = 1,
		WE_BABY = 1,
		WE_CALLPARENT = 1,
		WE_CALLBABY = 1,
		ALL_INCCARRY = 1,
	},
},
Swordsman = {
	Inherit = { "Novice" },

	Skills = {
		SM_SWORD = 10,
		SM_TWOHAND = {
			MaxLevel = 10,
			SM_SWORD = 1,
		},
		SM_RECOVERY = 10,
		SM_BASH = 10,
		SM_PROVOKE = 10,
		SM_MAGNUM = {
			MaxLevel = 10,
			SM_BASH = 5,
		},
		SM_ENDURE = {
			MaxLevel = 10,
			SM_PROVOKE = 5,
		},
		SM_MOVINGRECOVERY = 1,
		SM_FATALBLOW = 1,
		SM_AUTOBERSERK = 1,
	},
},
Magician = {
	Inherit = { "Novice" },

	Skills = {
		MG_SRECOVERY = 10,
		MG_SIGHT = 1,
		MG_NAPALMBEAT = 10,
		MG_SAFETYWALL = {
			MaxLevel = 10,
			MG_NAPALMBEAT = 7,
			MG_SOULSTRIKE = 5,
		},
		MG_SOULSTRIKE = {
			MaxLevel = 10,
			MG_NAPALMBEAT = 4,
		},
		MG_COLDBOLT = 10,
		MG_FROSTDIVER = {
			MaxLevel = 10,
			MG_COLDBOLT = 5,
		},
		MG_STONECURSE = 10,
		MG_FIREBALL = {
			MaxLevel = 10,
			MG_FIREBOLT = 4,
		},
		MG_FIREWALL = {
			MaxLevel = 10,
			MG_FIREBALL = 5,
			MG_SIGHT = 1,
		},
		MG_FIREBOLT = 10,
		MG_LIGHTNINGBOLT = 10,
		MG_THUNDERSTORM = {
			MaxLevel = 10,
			MG_LIGHTNINGBOLT = 4,
		},
		MG_ENERGYCOAT = 1,
	},
},
Archer = {
	Inherit = { "Novice" },

	Skills = {
		AC_OWL = 10,
		AC_VULTURE = {
			MaxLevel = 10,
			AC_OWL = 3,
		},
		AC_CONCENTRATION = {
			MaxLevel = 10,
			AC_VULTURE = 1,
		},
		AC_DOUBLE = 10,
		AC_SHOWER = {
			MaxLevel = 10,
			AC_DOUBLE = 5,
		},
		AC_MAKINGARROW = 1,
		AC_CHARGEARROW = 1,
	},
},
Acolyte = {
	Inherit = { "Novice" },

	Skills = {
		AL_DP = 10,
		AL_DEMONBANE = {
			MaxLevel = 10,
			AL_DP = 3,
		},
		AL_RUWACH = 1,
		AL_PNEUMA = {
			MaxLevel = 1,
			AL_WARP = 4,
		},
		AL_TELEPORT = {
			MaxLevel = 2,
			AL_RUWACH = 1,
		},
		AL_WARP = {
			MaxLevel = 4,
			AL_TELEPORT = 2,
		},
		AL_HEAL = 10,
		AL_INCAGI = {
			MaxLevel = 10,
			AL_HEAL = 3,
		},
		AL_DECAGI = {
			MaxLevel = 10,
			AL_INCAGI = 1,
		},
		AL_HOLYWATER = 1,
		AL_CRUCIS = {
			MaxLevel = 10,
			AL_DEMONBANE = 3,
		},
		AL_ANGELUS = {
			MaxLevel = 10,
			AL_DP = 3,
		},
		AL_BLESSING = {
			MaxLevel = 10,
			AL_DP = 5,
		},
		AL_CURE = {
			MaxLevel = 1,
			AL_HEAL = 2,
		},
		AL_HOLYLIGHT = 1,
	},
},
Merchant = {
	Inherit = { "Novice" },

	Skills = {
		MC_INCCARRY = 10,
		MC_DISCOUNT = {
			MaxLevel = 10,
			MC_INCCARRY = 3,
		},
		MC_OVERCHARGE = {
			MaxLevel = 10,
			MC_DISCOUNT = 3,
		},
		MC_PUSHCART = {
			MaxLevel = 10,
			MC_INCCARRY = 5,
		},
		MC_IDENTIFY = 1,
		MC_VENDING = {
			MaxLevel = 10,
			MC_PUSHCART = 3,
		},
		MC_MAMMONITE = 10,
		MC_CARTREVOLUTION = 1,
		MC_CHANGECART = 1,
		MC_CARTDECORATE = 1,
		MC_LOUD = 1,
		ALL_BUYING_STORE = {
			MaxLevel = 1,
			MC_VENDING = 1,
		},
	},
},
Thief = {
	Inherit = { "Novice" },

	Skills = {
		TF_DOUBLE = 10,
		TF_MISS = 10,
		TF_STEAL = 10,
		TF_HIDING = {
			MaxLevel = 10,
			TF_STEAL = 5,
		},
		TF_POISON = 10,
		TF_DETOXIFY = {
			MaxLevel = 1,
			TF_POISON = 3,
		},
		TF_SPRINKLESAND = 1,
		TF_BACKSLIDING = 1,
		TF_PICKSTONE = 1,
		TF_THROWSTONE = 1,
	},
},
Knight = {
	Inherit = { "Swordsman" },

	Skills = {
		KN_SPEARMASTERY = 10,
		KN_PIERCE = {
			MaxLevel = 10,
			KN_SPEARMASTERY = 1,
		},
		KN_BRANDISHSPEAR = {
			MaxLevel = 10,
			KN_RIDING = 1,
			KN_SPEARSTAB = 3,
		},
		KN_SPEARSTAB = {
			MaxLevel = 10,
			KN_PIERCE = 5,
		},
		KN_SPEARBOOMERANG = {
			MaxLevel = 5,
			KN_PIERCE = 3,
		},
		KN_TWOHANDQUICKEN = {
			MaxLevel = 10,
			SM_TWOHAND = 1,
		},
		KN_AUTOCOUNTER = {
			MaxLevel = 5,
			SM_TWOHAND = 1,
		},
		KN_BOWLINGBASH = {
			MaxLevel = 10,
			SM_BASH = 10,
			SM_MAGNUM = 3,
			SM_TWOHAND = 5,
			KN_TWOHANDQUICKEN = 10,
			KN_AUTOCOUNTER = 5,
		},
		KN_RIDING = {
			MaxLevel = 1,
			SM_ENDURE = 1,
		},
		KN_CAVALIERMASTERY = {
			MaxLevel = 5,
			KN_RIDING = 1,
		},
		KN_CHARGEATK = 1,
		KN_ONEHAND = {
			MaxLevel = 1,
			KN_TWOHANDQUICKEN = 10,
		},
	},
},
Priest = {
	Inherit = { "Acolyte" },

	Skills = {
		MG_SRECOVERY = 10,
		MG_SAFETYWALL = {
			MaxLevel = 10,
			PR_ASPERSIO = 4,
			PR_SANCTUARY = 3,
		},
		ALL_RESURRECTION = {
			MaxLevel = 4,
			PR_STRECOVERY = 1,
			MG_SRECOVERY = 4,
		},
		PR_MACEMASTERY = 10,
		PR_IMPOSITIO = 5,
		PR_SUFFRAGIUM = {
			MaxLevel = 3,
			PR_IMPOSITIO = 2,
		},
		PR_ASPERSIO = {
			MaxLevel = 5,
			AL_HOLYWATER = 1,
			PR_IMPOSITIO = 3,
		},
		PR_BENEDICTIO = {
			MaxLevel = 5,
			PR_GLORIA = 3,
			PR_ASPERSIO = 5,
		},
		PR_SANCTUARY = {
			MaxLevel = 10,
			AL_HEAL = 1,
		},
		PR_SLOWPOISON = 4,
		PR_STRECOVERY = 1,
		PR_KYRIE = {
			MaxLevel = 10,
			AL_ANGELUS = 2,
		},
		PR_MAGNIFICAT = 5,
		PR_GLORIA = {
			MaxLevel = 5,
			PR_KYRIE = 4,
			PR_MAGNIFICAT = 3,
		},
		PR_LEXDIVINA = {
			MaxLevel = 10,
			AL_RUWACH = 1,
		},
		PR_TURNUNDEAD = {
			MaxLevel = 10,
			ALL_RESURRECTION = 1,
			PR_LEXDIVINA = 3,
		},
		PR_LEXAETERNA = {
			MaxLevel = 1,
			PR_LEXDIVINA = 5,
		},
		PR_MAGNUS = {
			MaxLevel = 10,
			MG_SAFETYWALL = 1,
			PR_LEXAETERNA = 1,
			PR_TURNUNDEAD = 3,
		},
		PR_REDEMPTIO = 1,
	},
},
Wizard = {
	Inherit = { "Magician" },

	Skills = {
		WZ_FIREPILLAR = {
			MaxLevel = 10,
			MG_FIREWALL = 1,
		},
		WZ_SIGHTRASHER = {
			MaxLevel = 10,
			MG_LIGHTNINGBOLT = 1,
			MG_SIGHT = 1,
		},
		WZ_METEOR = {
			MaxLevel = 10,
			WZ_SIGHTRASHER = 2,
			MG_THUNDERSTORM = 1,
		},
		WZ_JUPITEL = {
			MaxLevel = 10,
			MG_NAPALMBEAT = 1,
			MG_LIGHTNINGBOLT = 1,
		},
		WZ_VERMILION = {
			MaxLevel = 10,
			MG_THUNDERSTORM = 1,
			WZ_JUPITEL = 5,
		},
		WZ_WATERBALL = {
			MaxLevel = 5,
			MG_COLDBOLT = 1,
			MG_LIGHTNINGBOLT = 1,
		},
		WZ_ICEWALL = {
			MaxLevel = 10,
			MG_STONECURSE = 1,
			MG_FROSTDIVER = 1,
		},
		WZ_FROSTNOVA = {
			MaxLevel = 10,
			WZ_ICEWALL = 1,
		},
		WZ_STORMGUST = {
			MaxLevel = 10,
			MG_FROSTDIVER = 1,
			WZ_JUPITEL = 3,
		},
		WZ_EARTHSPIKE = {
			MaxLevel = 5,
			MG_STONECURSE = 1,
		},
		WZ_HEAVENDRIVE = {
			MaxLevel = 5,
			WZ_EARTHSPIKE = 3,
		},
		WZ_QUAGMIRE = {
			MaxLevel = 5,
			WZ_HEAVENDRIVE = 1,
		},
		WZ_ESTIMATION = 1,
		WZ_SIGHTBLASTER = 1,
	},
},
Blacksmith = {
	Inherit = { "Merchant" },

	Skills = {
		BS_IRON = 5,
		BS_STEEL = {
			MaxLevel = 5,
			BS_IRON = 1,
		},
		BS_ENCHANTEDSTONE = {
			MaxLevel = 5,
			BS_IRON = 1,
		},
		BS_ORIDEOCON = {
			MaxLevel = 5,
			BS_ENCHANTEDSTONE = 1,
		},
		BS_DAGGER = 3,
		BS_SWORD = {
			MaxLevel = 3,
			BS_DAGGER = 1,
		},
		BS_TWOHANDSWORD = {
			MaxLevel = 3,
			BS_SWORD = 1,
		},
		BS_AXE = {
			MaxLevel = 3,
			BS_SWORD = 2,
		},
		BS_MACE = {
			MaxLevel = 3,
			BS_KNUCKLE = 1,
		},
		BS_KNUCKLE = {
			MaxLevel = 3,
			BS_DAGGER = 1,
		},
		BS_SPEAR = {
			MaxLevel = 3,
			BS_DAGGER = 2,
		},
		BS_HILTBINDING = 1,
		BS_FINDINGORE = {
			MaxLevel = 1,
			BS_STEEL = 1,
			BS_HILTBINDING = 1,
		},
		BS_WEAPONRESEARCH = {
			MaxLevel = 10,
			BS_HILTBINDING = 1,
		},
		BS_REPAIRWEAPON = {
			MaxLevel = 1,
			BS_WEAPONRESEARCH = 1,
		},
		BS_SKINTEMPER = 5,
		BS_HAMMERFALL = 5,
		BS_ADRENALINE = {
			MaxLevel = 5,
			BS_HAMMERFALL = 2,
		},
		BS_WEAPONPERFECT = {
			MaxLevel = 5,
			BS_WEAPONRESEARCH = 2,
			BS_ADRENALINE = 2,
		},
		BS_OVERTHRUST = {
			MaxLevel = 5,
			BS_ADRENALINE = 3,
		},
		BS_MAXIMIZE = {
			MaxLevel = 5,
			BS_WEAPONPERFECT = 3,
			BS_OVERTHRUST = 2,
		},
		BS_UNFAIRLYTRICK = 1,
		BS_GREED = 1,
		BS_ADRENALINE2 = {
			MaxLevel = 1,
			BS_ADRENALINE = 5,
		},
	},
},
Hunter = {
	Inherit = { "Archer" },

	Skills = {
		HT_SKIDTRAP = 5,
		HT_LANDMINE = 5,
		HT_ANKLESNARE = {
			MaxLevel = 5,
			HT_SKIDTRAP = 1,
		},
		HT_SHOCKWAVE = {
			MaxLevel = 5,
			HT_ANKLESNARE = 1,
		},
		HT_SANDMAN = {
			MaxLevel = 5,
			HT_FLASHER = 1,
		},
		HT_FLASHER = {
			MaxLevel = 5,
			HT_SKIDTRAP = 1,
		},
		HT_FREEZINGTRAP = {
			MaxLevel = 5,
			HT_FLASHER = 1,
		},
		HT_BLASTMINE = {
			MaxLevel = 5,
			HT_LANDMINE = 1,
			HT_SANDMAN = 1,
			HT_FREEZINGTRAP = 1,
		},
		HT_CLAYMORETRAP = {
			MaxLevel = 5,
			HT_SHOCKWAVE = 1,
			HT_BLASTMINE = 1,
		},
		HT_REMOVETRAP = {
			MaxLevel = 1,
			HT_LANDMINE = 1,
		},
		HT_TALKIEBOX = {
			MaxLevel = 1,
			HT_SHOCKWAVE = 1,
			HT_REMOVETRAP = 1,
		},
		HT_BEASTBANE = 10,
		HT_FALCON = {
			MaxLevel = 1,
			HT_BEASTBANE = 1,
		},
		HT_STEELCROW = {
			MaxLevel = 10,
			HT_BLITZBEAT = 5,
		},
		HT_BLITZBEAT = {
			MaxLevel = 5,
			HT_FALCON = 1,
		},
		HT_DETECTING = {
			MaxLevel = 4,
			AC_CONCENTRATION = 1,
			HT_FALCON = 1,
		},
		HT_SPRINGTRAP = {
			MaxLevel = 5,
			HT_REMOVETRAP = 1,
			HT_FALCON = 1,
		},
		HT_PHANTASMIC = 1,
		HT_POWER = {
			MaxLevel = 1,
			AC_DOUBLE = 10,
		},
	},
},
Assassin = {
	Inherit = { "Thief" },

	Skills = {
		AS_RIGHT = 5,
		AS_LEFT = {
			MaxLevel = 5,
			AS_RIGHT = 2,
		},
		AS_KATAR = 10,
		AS_CLOAKING = {
			MaxLevel = 10,
			TF_HIDING = 2,
		},
		AS_SONICBLOW = {
			MaxLevel = 10,
			AS_KATAR = 4,
		},
		AS_GRIMTOOTH = {
			MaxLevel = 5,
			AS_CLOAKING = 2,
			AS_SONICBLOW = 5,
		},
		AS_ENCHANTPOISON = {
			MaxLevel = 10,
			TF_POISON = 1,
		},
		AS_POISONREACT = {
			MaxLevel = 10,
			AS_ENCHANTPOISON = 3,
		},
		AS_VENOMDUST = {
			MaxLevel = 10,
			AS_ENCHANTPOISON = 5,
		},
		AS_SPLASHER = {
			MaxLevel = 10,
			AS_POISONREACT = 5,
			AS_VENOMDUST = 5,
		},
		AS_SONICACCEL = 1,
		AS_VENOMKNIFE = 1,
	},
},
Crusader = {
	Inherit = { "Swordsman" },

	Skills = {
		KN_RIDING = {
			MaxLevel = 1,
			SM_ENDURE = 1,
		},
		KN_CAVALIERMASTERY = {
			MaxLevel = 5,
			KN_RIDING = 1,
		},
		KN_SPEARMASTERY = 10,
		AL_CURE = {
			MaxLevel = 1,
			CR_TRUST = 5,
		},
		AL_DP = {
			MaxLevel = 10,
			AL_CURE = 1,
		},
		AL_DEMONBANE = {
			MaxLevel = 10,
			AL_DP = 3,
		},
		AL_HEAL = {
			MaxLevel = 10,
			AL_DEMONBANE = 5,
			CR_TRUST = 10,
		},
		CR_TRUST = 10,
		CR_AUTOGUARD = 10,
		CR_SHIELDCHARGE = {
			MaxLevel = 5,
			CR_AUTOGUARD = 5,
		},
		CR_SHIELDBOOMERANG = {
			MaxLevel = 5,
			CR_SHIELDCHARGE = 3,
		},
		CR_REFLECTSHIELD = {
			MaxLevel = 10,
			CR_SHIELDBOOMERANG = 3,
		},
		CR_HOLYCROSS = {
			MaxLevel = 10,
			CR_TRUST = 7,
		},
		CR_GRANDCROSS = {
			MaxLevel = 10,
			CR_HOLYCROSS = 6,
			CR_TRUST = 10,
		},
		CR_DEVOTION = {
			MaxLevel = 5,
			CR_REFLECTSHIELD = 5,
			CR_GRANDCROSS = 4,
		},
		CR_PROVIDENCE = {
			MaxLevel = 5,
			AL_DP = 5,
			AL_HEAL = 5,
		},
		CR_DEFENDER = {
			MaxLevel = 5,
			CR_SHIELDBOOMERANG = 1,
		},
		CR_SPEARQUICKEN = {
			MaxLevel = 10,
			KN_SPEARMASTERY = 10,
		},
		CR_SHRINK = 1,
	},
},
Monk = {
	Inherit = { "Acolyte" },

	Skills = {
		MO_IRONHAND = {
			MaxLevel = 10,
			AL_DEMONBANE = 10,
			AL_DP = 10,
		},
		MO_SPIRITSRECOVERY = {
			MaxLevel = 5,
			MO_BLADESTOP = 2,
		},
		MO_CALLSPIRITS = {
			MaxLevel = 5,
			MO_IRONHAND = 2,
		},
		MO_ABSORBSPIRITS = {
			MaxLevel = 1,
			MO_CALLSPIRITS = 5,
		},
		MO_TRIPLEATTACK = {
			MaxLevel = 10,
			MO_DODGE = 5,
		},
		MO_BODYRELOCATION = {
			MaxLevel = 1,
			MO_EXTREMITYFIST = 3,
			MO_SPIRITSRECOVERY = 2,
			MO_STEELBODY = 3,
		},
		MO_DODGE = {
			MaxLevel = 10,
			MO_IRONHAND = 5,
			MO_CALLSPIRITS = 5,
		},
		MO_INVESTIGATE = {
			MaxLevel = 5,
			MO_CALLSPIRITS = 5,
		},
		MO_FINGEROFFENSIVE = {
			MaxLevel = 5,
			MO_INVESTIGATE = 3,
		},
		MO_STEELBODY = {
			MaxLevel = 5,
			MO_COMBOFINISH = 3,
		},
		MO_BLADESTOP = {
			MaxLevel = 5,
			MO_DODGE = 5,
		},
		MO_EXPLOSIONSPIRITS = {
			MaxLevel = 5,
			MO_ABSORBSPIRITS = 1,
		},
		MO_EXTREMITYFIST = {
			MaxLevel = 5,
			MO_EXPLOSIONSPIRITS = 3,
			MO_FINGEROFFENSIVE = 3,
		},
		MO_CHAINCOMBO = {
			MaxLevel = 5,
			MO_TRIPLEATTACK = 5,
		},
		MO_COMBOFINISH = {
			MaxLevel = 5,
			MO_CHAINCOMBO = 3,
		},
		MO_KITRANSLATION = 1,
		MO_BALKYOUNG = 1,
	},
},
Sage = {
	Inherit = { "Magician" },

	Skills = {
		WZ_ESTIMATION = 1,
		WZ_EARTHSPIKE = {
			MaxLevel = 5,
			SA_SEISMICWEAPON = 1,
		},
		WZ_HEAVENDRIVE = {
			MaxLevel = 5,
			WZ_EARTHSPIKE = 1,
		},
		SA_ADVANCEDBOOK = 10,
		SA_CASTCANCEL = {
			MaxLevel = 5,
			SA_ADVANCEDBOOK = 2,
		},
		SA_MAGICROD = {
			MaxLevel = 5,
			SA_ADVANCEDBOOK = 4,
		},
		SA_SPELLBREAKER = {
			MaxLevel = 5,
			SA_MAGICROD = 1,
		},
		SA_FREECAST = {
			MaxLevel = 10,
			SA_CASTCANCEL = 1,
		},
		SA_AUTOSPELL = {
			MaxLevel = 10,
			SA_FREECAST = 4,
		},
		SA_FLAMELAUNCHER = {
			MaxLevel = 5,
			MG_FIREBOLT = 1,
			SA_ADVANCEDBOOK = 5,
		},
		SA_FROSTWEAPON = {
			MaxLevel = 5,
			MG_COLDBOLT = 1,
			SA_ADVANCEDBOOK = 5,
		},
		SA_LIGHTNINGLOADER = {
			MaxLevel = 5,
			MG_LIGHTNINGBOLT = 1,
			SA_ADVANCEDBOOK = 5,
		},
		SA_SEISMICWEAPON = {
			MaxLevel = 5,
			MG_STONECURSE = 1,
			SA_ADVANCEDBOOK = 5,
		},
		SA_DRAGONOLOGY = {
			MaxLevel = 5,
			SA_ADVANCEDBOOK = 9,
		},
		SA_VOLCANO = {
			MaxLevel = 5,
			SA_FLAMELAUNCHER = 2,
		},
		SA_DELUGE = {
			MaxLevel = 5,
			SA_FROSTWEAPON = 2,
		},
		SA_VIOLENTGALE = {
			MaxLevel = 5,
			SA_LIGHTNINGLOADER = 2,
		},
		SA_LANDPROTECTOR = {
			MaxLevel = 5,
			SA_VOLCANO = 3,
			SA_DELUGE = 3,
			SA_VIOLENTGALE = 3,
		},
		SA_DISPELL = {
			MaxLevel = 5,
			SA_SPELLBREAKER = 3,
		},
		SA_ABRACADABRA = {
			MaxLevel = 10,
			SA_AUTOSPELL = 5,
			SA_DISPELL = 1,
			SA_LANDPROTECTOR = 1,
		},
		SA_CREATECON = 1,
		SA_ELEMENTWATER = 1,
		SA_ELEMENTGROUND = 1,
		SA_ELEMENTFIRE = 1,
		SA_ELEMENTWIND = 1,
	},
},
Rogue = {
	Inherit = { "Thief" },

	Skills = {
		SM_SWORD = 10,
		AC_VULTURE = 10,
		AC_DOUBLE = {
			MaxLevel = 10,
			AC_VULTURE = 10,
		},
		HT_REMOVETRAP = {
			MaxLevel = 1,
			AC_DOUBLE = 5,
		},
		RG_SNATCHER = {
			MaxLevel = 10,
			TF_STEAL = 1,
		},
		RG_STEALCOIN = {
			MaxLevel = 10,
			RG_SNATCHER = 4,
		},
		RG_BACKSTAP = {
			MaxLevel = 10,
			RG_STEALCOIN = 4,
		},
		RG_TUNNELDRIVE = {
			MaxLevel = 5,
			TF_HIDING = 1,
		},
		RG_RAID = {
			MaxLevel = 5,
			RG_BACKSTAP = 2,
			RG_TUNNELDRIVE = 2,
		},
		RG_STRIPWEAPON = {
			MaxLevel = 5,
			RG_STRIPARMOR = 5,
		},
		RG_STRIPSHIELD = {
			MaxLevel = 5,
			RG_STRIPHELM = 5,
		},
		RG_STRIPARMOR = {
			MaxLevel = 5,
			RG_STRIPSHIELD = 5,
		},
		RG_STRIPHELM = {
			MaxLevel = 5,
			RG_STEALCOIN = 2,
		},
		RG_INTIMIDATE = {
			MaxLevel = 5,
			RG_BACKSTAP = 4,
			RG_RAID = 5,
		},
		RG_GRAFFITI = {
			MaxLevel = 1,
			RG_FLAGGRAFFITI = 5,
		},
		RG_FLAGGRAFFITI = {
			MaxLevel = 5,
			RG_CLEANER = 1,
		},
		RG_CLEANER = {
			MaxLevel = 1,
			RG_GANGSTER = 1,
		},
		RG_GANGSTER = {
			MaxLevel = 1,
			RG_STRIPSHIELD = 3,
		},
		RG_COMPULSION = {
			MaxLevel = 5,
			RG_GANGSTER = 1,
		},
		RG_PLAGIARISM = {
			MaxLevel = 10,
			RG_INTIMIDATE = 5,
		},
		RG_CLOSECONFINE = 1,
	},
},
Alchemist = {
	Inherit = { "Merchant" },

	Skills = {
		AM_AXEMASTERY = 10,
		AM_LEARNINGPOTION = 10,
		AM_PHARMACY = {
			MaxLevel = 10,
			AM_LEARNINGPOTION = 5,
		},
		AM_DEMONSTRATION = {
			MaxLevel = 5,
			AM_PHARMACY = 4,
		},
		AM_ACIDTERROR = {
			MaxLevel = 5,
			AM_PHARMACY = 5,
		},
		AM_POTIONPITCHER = {
			MaxLevel = 5,
			AM_PHARMACY = 3,
		},
		AM_CANNIBALIZE = {
			MaxLevel = 5,
			AM_PHARMACY = 6,
		},
		AM_SPHEREMINE = {
			MaxLevel = 5,
			AM_PHARMACY = 2,
		},
		AM_CP_WEAPON = {
			MaxLevel = 5,
			AM_CP_ARMOR = 3,
		},
		AM_CP_SHIELD = {
			MaxLevel = 5,
			AM_CP_HELM = 3,
		},
		AM_CP_ARMOR = {
			MaxLevel = 5,
			AM_CP_SHIELD = 3,
		},
		AM_CP_HELM = {
			MaxLevel = 5,
			AM_PHARMACY = 2,
		},
		AM_BIOETHICS = 1,
		AM_CALLHOMUN = {
			MaxLevel = 1,
			AM_REST = 1,
		},
		AM_REST = {
			MaxLevel = 1,
			AM_BIOETHICS = 1,
		},
		AM_RESURRECTHOMUN = {
			MaxLevel = 5,
			AM_CALLHOMUN = 1,
		},
		AM_BERSERKPITCHER = 1,
		AM_TWILIGHT1 = {
			MaxLevel = 1,
			AM_PHARMACY = 10,
		},
		AM_TWILIGHT2 = {
			MaxLevel = 1,
			AM_PHARMACY = 10,
		},
		AM_TWILIGHT3 = {
			MaxLevel = 1,
			AM_PHARMACY = 10,
		},
	},
},
Bard = {
	Inherit = { "Archer" },

	Skills = {
		BA_MUSICALLESSON = 10,
		BA_MUSICALSTRIKE = {
			MaxLevel = 5,
			BA_MUSICALLESSON = 3,
		},
		BA_DISSONANCE = {
			MaxLevel = 5,
			BA_MUSICALLESSON = 1,
			BD_ADAPTATION = 1,
		},
		BA_FROSTJOKER = {
			MaxLevel = 5,
			BD_ENCORE = 1,
		},
		BA_WHISTLE = {
			MaxLevel = 10,
			BA_DISSONANCE = 3,
		},
		BA_ASSASSINCROSS = {
			MaxLevel = 10,
			BA_DISSONANCE = 3,
		},
		BA_POEMBRAGI = {
			MaxLevel = 10,
			BA_DISSONANCE = 3,
		},
		BA_APPLEIDUN = {
			MaxLevel = 10,
			BA_DISSONANCE = 3,
		},
		BD_ADAPTATION = 1,
		BD_ENCORE = {
			MaxLevel = 1,
			BD_ADAPTATION = 1,
		},
		BD_LULLABY = {
			MaxLevel = 1,
			BA_WHISTLE = 10,
		},
		BD_RICHMANKIM = {
			MaxLevel = 5,
			BD_SIEGFRIED = 3,
		},
		BD_ETERNALCHAOS = {
			MaxLevel = 1,
			BD_ROKISWEIL = 1,
		},
		BD_DRUMBATTLEFIELD = {
			MaxLevel = 5,
			BA_APPLEIDUN = 10,
		},
		BD_RINGNIBELUNGEN = {
			MaxLevel = 5,
			BD_DRUMBATTLEFIELD = 3,
		},
		BD_ROKISWEIL = {
			MaxLevel = 1,
			BA_ASSASSINCROSS = 10,
		},
		BD_INTOABYSS = {
			MaxLevel = 1,
			BD_LULLABY = 1,
		},
		BD_SIEGFRIED = {
			MaxLevel = 5,
			BA_POEMBRAGI = 10,
		},
		BA_PANGVOICE = 1,
	},
},
Dancer = {
	Inherit = { "Archer" },

	Skills = {
		DC_DANCINGLESSON = 10,
		DC_THROWARROW = {
			MaxLevel = 5,
			DC_DANCINGLESSON = 3,
		},
		DC_UGLYDANCE = {
			MaxLevel = 5,
			DC_DANCINGLESSON = 1,
			BD_ADAPTATION = 1,
		},
		DC_SCREAM = {
			MaxLevel = 5,
			BD_ENCORE = 1,
		},
		DC_HUMMING = {
			MaxLevel = 10,
			DC_UGLYDANCE = 3,
		},
		DC_DONTFORGETME = {
			MaxLevel = 10,
			DC_UGLYDANCE = 3,
		},
		DC_FORTUNEKISS = {
			MaxLevel = 10,
			DC_UGLYDANCE = 3,
		},
		DC_SERVICEFORYOU = {
			MaxLevel = 10,
			DC_UGLYDANCE = 3,
		},
		BD_ADAPTATION = 1,
		BD_ENCORE = {
			MaxLevel = 1,
			BD_ADAPTATION = 1,
		},
		BD_LULLABY = {
			MaxLevel = 1,
			DC_HUMMING = 10,
		},
		BD_RICHMANKIM = {
			MaxLevel = 5,
			BD_SIEGFRIED = 3,
		},
		BD_ETERNALCHAOS = {
			MaxLevel = 1,
			BD_ROKISWEIL = 1,
		},
		BD_DRUMBATTLEFIELD = {
			MaxLevel = 5,
			DC_SERVICEFORYOU = 10,
		},
		BD_RINGNIBELUNGEN = {
			MaxLevel = 5,
			BD_DRUMBATTLEFIELD = 3,
		},
		BD_ROKISWEIL = {
			MaxLevel = 1,
			DC_DONTFORGETME = 10,
		},
		BD_INTOABYSS = {
			MaxLevel = 1,
			BD_LULLABY = 1,
		},
		BD_SIEGFRIED = {
			MaxLevel = 5,
			DC_FORTUNEKISS = 10,
		},
		DC_WINKCHARM = 1,
	},
},
Super_Novice = {
	Inherit = { "Novice" },

	Skills = {
		SM_SWORD = 10,
		SM_RECOVERY = 10,
		SM_BASH = 10,
		SM_PROVOKE = 10,
		SM_MAGNUM = {
			MaxLevel = 10,
			SM_BASH = 5,
		},
		SM_ENDURE = {
			MaxLevel = 10,
			SM_PROVOKE = 5,
		},
		MG_SRECOVERY = 10,
		MG_SIGHT = 1,
		MG_NAPALMBEAT = 10,
		MG_SAFETYWALL = {
			MaxLevel = 10,
			MG_NAPALMBEAT = 7,
			MG_SOULSTRIKE = 5,
		},
		MG_SOULSTRIKE = {
			MaxLevel = 10,
			MG_NAPALMBEAT = 4,
		},
		MG_COLDBOLT = 10,
		MG_FROSTDIVER = {
			MaxLevel = 10,
			MG_COLDBOLT = 5,
		},
		MG_STONECURSE = 10,
		MG_FIREBALL = {
			MaxLevel = 10,
			MG_FIREBOLT = 4,
		},
		MG_FIREWALL = {
			MaxLevel = 10,
			MG_FIREBALL = 5,
			MG_SIGHT = 1,
		},
		MG_FIREBOLT = 10,
		MG_LIGHTNINGBOLT = 10,
		MG_THUNDERSTORM = {
			MaxLevel = 10,
			MG_LIGHTNINGBOLT = 4,
		},
		AL_DP = 10,
		AL_DEMONBANE = {
			MaxLevel = 10,
			AL_DP = 3,
		},
		AL_RUWACH = 1,
		AL_PNEUMA = {
			MaxLevel = 1,
			AL_WARP = 4,
		},
		AL_TELEPORT = {
			MaxLevel = 2,
			AL_RUWACH = 1,
		},
		AL_WARP = {
			MaxLevel = 4,
			AL_TELEPORT = 2,
		},
		AL_HEAL = 10,
		AL_INCAGI = {
			MaxLevel = 10,
			AL_HEAL = 3,
		},
		AL_DECAGI = {
			MaxLevel = 10,
			AL_INCAGI = 1,
		},
		AL_HOLYWATER = 1,
		AL_CRUCIS = {
			MaxLevel = 10,
			AL_DEMONBANE = 3,
		},
		AL_ANGELUS = {
			MaxLevel = 10,
			AL_DP = 3,
		},
		AL_BLESSING = {
			MaxLevel = 10,
			AL_DP = 5,
		},
		AL_CURE = {
			MaxLevel = 1,
			AL_HEAL = 2,
		},
		MC_INCCARRY = 10,
		MC_DISCOUNT = {
			MaxLevel = 10,
			MC_INCCARRY = 3,
		},
		MC_OVERCHARGE = {
			MaxLevel = 10,
			MC_DISCOUNT = 3,
		},
		MC_PUSHCART = {
			MaxLevel = 10,
			MC_INCCARRY = 5,
		},
		MC_IDENTIFY = 1,
		MC_VENDING = {
			MaxLevel = 10,
			MC_PUSHCART = 3,
		},
		MC_MAMMONITE = 10,
		AC_OWL = 10,
		AC_VULTURE = {
			MaxLevel = 10,
			AC_OWL = 3,
		},
		AC_CONCENTRATION = {
			MaxLevel = 10,
			AC_VULTURE = 1,
		},
		TF_DOUBLE = 10,
		TF_MISS = 10,
		TF_STEAL = 10,
		TF_HIDING = {
			MaxLevel = 10,
			TF_STEAL = 5,
		},
		TF_POISON = 10,
		TF_DETOXIFY = {
			MaxLevel = 1,
			TF_POISON = 3,
		},
		ALL_BUYING_STORE = {
			MaxLevel = 1,
			MC_VENDING = 1,
		},
	},
},
Gunslinger = {
	Inherit = { "Novice" },

	Skills = {
		GS_GLITTERING = 5,
		GS_FLING = {
			MaxLevel = 1,
			GS_GLITTERING = 1,
		},
		GS_TRIPLEACTION = {
			MaxLevel = 1,
			GS_GLITTERING = 1,
			GS_CHAINACTION = 10,
		},
		GS_BULLSEYE = {
			MaxLevel = 1,
			GS_GLITTERING = 5,
			GS_TRACKING = 10,
		},
		GS_MADNESSCANCEL = {
			MaxLevel = 1,
			GS_GLITTERING = 4,
			GS_GATLINGFEVER = 10,
		},
		GS_ADJUSTMENT = {
			MaxLevel = 1,
			GS_GLITTERING = 4,
			GS_DISARM = 5,
		},
		GS_INCREASING = {
			MaxLevel = 1,
			GS_GLITTERING = 2,
			GS_SNAKEEYE = 10,
		},
		GS_MAGICALBULLET = {
			MaxLevel = 1,
			GS_GLITTERING = 1,
		},
		GS_CRACKER = {
			MaxLevel = 1,
			GS_GLITTERING = 1,
		},
		GS_SINGLEACTION = 10,
		GS_SNAKEEYE = 10,
		GS_CHAINACTION = {
			MaxLevel = 10,
			GS_SINGLEACTION = 1,
		},
		GS_TRACKING = {
			MaxLevel = 10,
			GS_SINGLEACTION = 5,
		},
		GS_DISARM = {
			MaxLevel = 5,
			GS_TRACKING = 7,
		},
		GS_PIERCINGSHOT = {
			MaxLevel = 5,
			GS_TRACKING = 5,
		},
		GS_RAPIDSHOWER = {
			MaxLevel = 10,
			GS_CHAINACTION = 3,
		},
		GS_DESPERADO = {
			MaxLevel = 10,
			GS_RAPIDSHOWER = 5,
		},
		GS_GATLINGFEVER = {
			MaxLevel = 10,
			GS_RAPIDSHOWER = 7,
			GS_DESPERADO = 5,
		},
		GS_DUST = {
			MaxLevel = 10,
			GS_SINGLEACTION = 5,
		},
		GS_FULLBUSTER = {
			MaxLevel = 10,
			GS_DUST = 3,
		},
		GS_SPREADATTACK = {
			MaxLevel = 10,
			GS_FULLBUSTER = 5,
		},
		GS_GROUNDDRIFT = {
			MaxLevel = 10,
			GS_SPREADATTACK = 7,
		},
	},
},
Ninja = {
	Inherit = { "Novice" },

	Skills = {
		NJ_TOBIDOUGU = 10,
		NJ_SYURIKEN = {
			MaxLevel = 10,
			NJ_TOBIDOUGU = 1,
		},
		NJ_KUNAI = {
			MaxLevel = 5,
			NJ_SYURIKEN = 5,
		},
		NJ_HUUMA = {
			MaxLevel = 5,
			NJ_TOBIDOUGU = 5,
			NJ_KUNAI = 5,
		},
		NJ_ZENYNAGE = {
			MaxLevel = 10,
			NJ_TOBIDOUGU = 10,
			NJ_HUUMA = 5,
		},
		NJ_TATAMIGAESHI = 5,
		NJ_KASUMIKIRI = {
			MaxLevel = 10,
			NJ_SHADOWJUMP = 1,
		},
		NJ_SHADOWJUMP = {
			MaxLevel = 5,
			NJ_TATAMIGAESHI = 1,
		},
		NJ_KIRIKAGE = {
			MaxLevel = 5,
			NJ_KASUMIKIRI = 5,
		},
		NJ_UTSUSEMI = {
			MaxLevel = 5,
			NJ_SHADOWJUMP = 5,
		},
		NJ_BUNSINJYUTSU = {
			MaxLevel = 10,
			NJ_UTSUSEMI = 4,
			NJ_KIRIKAGE = 3,
			NJ_NEN = 1,
		},
		NJ_NINPOU = 10,
		NJ_KOUENKA = {
			MaxLevel = 10,
			NJ_NINPOU = 1,
		},
		NJ_KAENSIN = {
			MaxLevel = 10,
			NJ_KOUENKA = 5,
		},
		NJ_BAKUENRYU = {
			MaxLevel = 5,
			NJ_NINPOU = 10,
			NJ_KAENSIN = 7,
		},
		NJ_HYOUSENSOU = {
			MaxLevel = 10,
			NJ_NINPOU = 1,
		},
		NJ_SUITON = {
			MaxLevel = 10,
			NJ_HYOUSENSOU = 5,
		},
		NJ_HYOUSYOURAKU = {
			MaxLevel = 5,
			NJ_NINPOU = 10,
			NJ_SUITON = 7,
		},
		NJ_HUUJIN = {
			MaxLevel = 10,
			NJ_NINPOU = 1,
		},
		NJ_RAIGEKISAI = {
			MaxLevel = 5,
			NJ_HUUJIN = 5,
		},
		NJ_KAMAITACHI = {
			MaxLevel = 5,
			NJ_NINPOU = 10,
			NJ_RAIGEKISAI = 5,
		},
		NJ_NEN = {
			MaxLevel = 5,
			NJ_NINPOU = 5,
		},
		NJ_ISSEN = {
			MaxLevel = 10,
			NJ_TOBIDOUGU = 7,
			NJ_KIRIKAGE = 5,
			NJ_NEN = 1,
		},
	},
},
Novice_High = {
	Inherit = { "Novice" },
},
Swordsman_High = {
	Inherit = { "Swordsman" },
},
Magician_High = {
	Inherit = { "Magician" },
},
Archer_High = {
	Inherit = { "Archer" },
},
Acolyte_High = {
	Inherit = { "Acolyte" },
},
Merchant_High = {
	Inherit = { "Merchant" },
},
Thief_High = {
	Inherit = { "Thief" },
},
Lord_Knight = {
	Inherit = { "Knight" },
	Skills = {
		LK_AURABLADE = {
			MaxLevel = 5,
			SM_BASH = 5,
			SM_MAGNUM = 5,
			SM_TWOHAND = 5,
		},
		LK_PARRYING = {
			MaxLevel = 10,
			SM_TWOHAND = 10,
			SM_PROVOKE = 5,
			KN_TWOHANDQUICKEN = 3,
		},
		LK_CONCENTRATION = {
			MaxLevel = 5,
			SM_RECOVERY = 5,
			KN_SPEARMASTERY = 5,
			KN_RIDING = 1,
		},
		LK_TENSIONRELAX = {
			MaxLevel = 1,
			SM_RECOVERY = 10,
			SM_PROVOKE = 5,
			SM_ENDURE = 3,
		},
		LK_BERSERK = {
			MaxLevel = 1,
			MinJobLevel = 50,
		},
		LK_SPIRALPIERCE = {
			MaxLevel = 5,
			KN_SPEARMASTERY = 5,
			KN_PIERCE = 5,
			KN_SPEARSTAB = 5,
			KN_RIDING = 1,
		},
		LK_HEADCRUSH = {
			MaxLevel = 5,
			KN_SPEARMASTERY = 9,
			KN_RIDING = 1,
		},
		LK_JOINTBEAT = {
			MaxLevel = 10,
			KN_SPEARMASTERY = 9,
			KN_CAVALIERMASTERY = 3,
			LK_HEADCRUSH = 3,
		},
	},
},
High_Priest = {
	Inherit = { "Priest" },

	Skills = {
		HP_ASSUMPTIO = {
			MaxLevel = 5,
			AL_ANGELUS = 1,
			MG_SRECOVERY = 3,
			PR_IMPOSITIO = 3,
		},
		HP_BASILICA = {
			MaxLevel = 5,
			PR_GLORIA = 2,
			MG_SRECOVERY = 1,
			PR_KYRIE = 3,
		},
		HP_MEDITATIO = {
			MaxLevel = 10,
			PR_ASPERSIO = 3,
			MG_SRECOVERY = 5,
			PR_LEXDIVINA = 5,
		},
		HP_MANARECHARGE = {
			MaxLevel = 5,
			PR_MACEMASTERY = 10,
			AL_DEMONBANE = 10,
		},
	},
},
High_Wizard = {
	Inherit = { "Wizard" },

	Skills = {
		HW_SOULDRAIN = {
			MaxLevel = 10,
			MG_SRECOVERY = 5,
			MG_SOULSTRIKE = 7,
		},
		HW_MAGICCRASHER = {
			MaxLevel = 1,
			MG_SRECOVERY = 1,
		},
		HW_MAGICPOWER = 10,
		HW_NAPALMVULCAN = {
			MaxLevel = 5,
			MG_NAPALMBEAT = 5,
		},
		HW_GANBANTEIN = {
			MaxLevel = 1,
			WZ_ESTIMATION = 1,
			WZ_ICEWALL = 1,
		},
		HW_GRAVITATION = {
			MaxLevel = 5,
			HW_MAGICCRASHER = 1,
			HW_MAGICPOWER = 10,
			WZ_QUAGMIRE = 1,
		},
	},
},
Whitesmith = {
	Inherit = { "Blacksmith" },

	Skills = {
		WS_MELTDOWN = {
			MaxLevel = 10,
			BS_SKINTEMPER = 3,
			BS_HILTBINDING = 1,
			BS_WEAPONRESEARCH = 5,
			BS_OVERTHRUST = 3,
		},
		WS_CARTBOOST = {
			MaxLevel = 1,
			MC_PUSHCART = 5,
			MC_CARTREVOLUTION = 1,
			MC_CHANGECART = 1,
			BS_HILTBINDING = 1,
		},
		WS_WEAPONREFINE = {
			MaxLevel = 10,
			BS_WEAPONRESEARCH = 10,
		},
		WS_CARTTERMINATION = {
			MaxLevel = 10,
			MC_MAMMONITE = 10,
			BS_HAMMERFALL = 5,
			WS_CARTBOOST = 1,
		},
		WS_OVERTHRUSTMAX = {
			MaxLevel = 5,
			BS_OVERTHRUST = 5,
		},
	},
},
Sniper = {
	Inherit = { "Hunter" },

	Skills = {
		SN_SIGHT = {
			MaxLevel = 10,
			AC_OWL = 10,
			AC_VULTURE = 10,
			AC_CONCENTRATION = 10,
			HT_FALCON = 1,
		},
		SN_FALCONASSAULT = {
			MaxLevel = 5,
			HT_STEELCROW = 3,
			AC_VULTURE = 5,
			HT_BLITZBEAT = 5,
			HT_FALCON = 1,
		},
		SN_SHARPSHOOTING = {
			MaxLevel = 5,
			AC_CONCENTRATION = 10,
			AC_DOUBLE = 5,
		},
		SN_WINDWALK = {
			MaxLevel = 10,
			AC_CONCENTRATION = 9,
		},
	},
},
Assassin_Cross = {
	Inherit = { "Assassin" },

	Skills = {
		ASC_KATAR = {
			MaxLevel = 5,
			TF_DOUBLE = 5,
			AS_KATAR = 7,
		},
		ASC_EDP = {
			MaxLevel = 5,
			ASC_CDP = 1,
		},
		ASC_BREAKER = {
			MaxLevel = 10,
			TF_DOUBLE = 5,
			AS_CLOAKING = 3,
			AS_ENCHANTPOISON = 6,
			TF_POISON = 5,
		},
		ASC_METEORASSAULT = {
			MaxLevel = 10,
			AS_RIGHT = 3,
			AS_KATAR = 5,
			AS_SONICBLOW = 5,
			ASC_BREAKER = 1,
		},
		ASC_CDP = {
			MaxLevel = 1,
			TF_POISON = 10,
			TF_DETOXIFY = 1,
			AS_ENCHANTPOISON = 5,
		},
	},
},
Paladin = {
	Inherit = { "Crusader" },

	Skills = {
		PA_PRESSURE = {
			MaxLevel = 5,
			SM_ENDURE = 5,
			CR_TRUST = 5,
			CR_SHIELDCHARGE = 2,
		},
		PA_SACRIFICE = {
			MaxLevel = 5,
			SM_ENDURE = 1,
			CR_TRUST = 5,
			CR_DEVOTION = 3,
		},
		PA_GOSPEL = {
			MaxLevel = 10,
			CR_TRUST = 8,
			AL_DP = 3,
			AL_DEMONBANE = 5,
		},
		PA_SHIELDCHAIN = {
			MaxLevel = 5,
			CR_SHIELDBOOMERANG = 5,
		},
	},
},
Champion = {
	Inherit = { "Monk" },

	Skills = {
		CH_PALMSTRIKE = {
			MaxLevel = 5,
			MO_IRONHAND = 7,
			MO_CALLSPIRITS = 5,
		},
		CH_TIGERFIST = {
			MaxLevel = 5,
			MO_IRONHAND = 5,
			MO_TRIPLEATTACK = 5,
			MO_CALLSPIRITS = 5,
			MO_COMBOFINISH = 3,
		},
		CH_CHAINCRUSH = {
			MaxLevel = 10,
			MO_IRONHAND = 5,
			MO_CALLSPIRITS = 5,
			CH_TIGERFIST = 2,
		},
		CH_SOULCOLLECT = {
			MaxLevel = 1,
			MO_CALLSPIRITS = 5,
			MO_ABSORBSPIRITS = 1,
			MO_EXPLOSIONSPIRITS = 5,
		},
	},
},
Professor = {
	Inherit = { "Sage" },

	Skills = {
		PF_HPCONVERSION = {
			MaxLevel = 5,
			MG_SRECOVERY = 1,
			SA_MAGICROD = 1,
		},
		PF_SOULCHANGE = {
			MaxLevel = 1,
			SA_MAGICROD = 3,
			SA_SPELLBREAKER = 2,
		},
		PF_SOULBURN = {
			MaxLevel = 5,
			SA_CASTCANCEL = 5,
			SA_MAGICROD = 3,
			SA_DISPELL = 3,
		},
		PF_MINDBREAKER = {
			MaxLevel = 5,
			MG_SRECOVERY = 3,
			PF_SOULBURN = 1,
		},
		PF_MEMORIZE = {
			MaxLevel = 1,
			SA_ADVANCEDBOOK = 5,
			SA_FREECAST = 5,
			SA_AUTOSPELL = 1,
		},
		PF_FOGWALL = {
			MaxLevel = 1,
			SA_DELUGE = 2,
			SA_VIOLENTGALE = 2,
		},
		PF_SPIDERWEB = {
			MaxLevel = 1,
			SA_DRAGONOLOGY = 4,
		},
		PF_DOUBLECASTING = {
			MaxLevel = 5,
			SA_AUTOSPELL = 1,
		},
	},
},
Stalker = {
	Inherit = { "Rogue" },

	Skills = {
		ST_CHASEWALK = {
			MaxLevel = 5,
			TF_HIDING = 5,
			RG_TUNNELDRIVE = 3,
		},
		ST_REJECTSWORD = 5,
		ST_PRESERVE = {
			MaxLevel = 1,
			RG_PLAGIARISM = 10,
		},
		ST_FULLSTRIP = {
			MaxLevel = 5,
			RG_STRIPWEAPON = 5,
			RG_STRIPSHIELD = 5,
			RG_STRIPARMOR = 5,
			RG_STRIPHELM = 5,
		},
	},
},
Creator = {
	Inherit = { "Alchemist" },

	Skills = {
		CR_SLIMPITCHER = {
			MaxLevel = 10,
			AM_POTIONPITCHER = 5,
		},
		CR_FULLPROTECTION = {
			MaxLevel = 5,
			AM_CP_WEAPON = 5,
			AM_CP_SHIELD = 5,
			AM_CP_ARMOR = 5,
			AM_CP_HELM = 5,
		},
		CR_ACIDDEMONSTRATION = {
			MaxLevel = 10,
			AM_DEMONSTRATION = 5,
			AM_ACIDTERROR = 5,
		},
		CR_CULTIVATION = 2,
	},
},
Clown = {
	Inherit = { "Bard" },

	Skills = {
		CG_ARROWVULCAN = {
			MaxLevel = 10,
			AC_SHOWER = 5,
			BA_MUSICALSTRIKE = 1,
		},
		CG_MOONLIT = {
			MaxLevel = 5,
			AC_CONCENTRATION = 5,
			BA_MUSICALLESSON = 7,
		},
		CG_MARIONETTE = {
			MaxLevel = 1,
			AC_CONCENTRATION = 5,
			BA_MUSICALLESSON = 5,
		},
		CG_LONGINGFREEDOM = {
			MaxLevel = 5,
			BA_MUSICALLESSON = 10,
			CG_MARIONETTE = 1,
		},
		CG_HERMODE = {
			MaxLevel = 5,
			AC_CONCENTRATION = 10,
			BA_MUSICALLESSON = 10,
		},
		CG_TAROTCARD = {
			MaxLevel = 5,
			AC_CONCENTRATION = 10,
			BA_DISSONANCE = 3,
		},
	},
},
Gypsy = {
	Inherit = { "Dancer" },

	Skills = {
		CG_ARROWVULCAN = {
			MaxLevel = 10,
			AC_SHOWER = 5,
			DC_THROWARROW = 1,
		},
		CG_MOONLIT = {
			MaxLevel = 5,
			AC_CONCENTRATION = 5,
			DC_DANCINGLESSON = 7,
		},
		CG_MARIONETTE = {
			MaxLevel = 1,
			AC_CONCENTRATION = 5,
			DC_DANCINGLESSON = 5,
		},
		CG_LONGINGFREEDOM = {
			MaxLevel = 5,
			DC_DANCINGLESSON = 10,
			CG_MARIONETTE = 1,
		},
		CG_HERMODE = {
			MaxLevel = 5,
			AC_CONCENTRATION = 10,
			DC_DANCINGLESSON = 10,
		},
		CG_TAROTCARD = {
			MaxLevel = 5,
			AC_CONCENTRATION = 10,
			DC_UGLYDANCE = 3,
		},
	},
},
Baby_Novice = {
	Inherit = { "Novice" },
},
Baby_Swordsman = {
	Inherit = { "Swordsman" },
},
Baby_Magician = {
	Inherit = { "Magician" },
},
Baby_Archer = {
	Inherit = { "Archer" },
},
Baby_Acolyte = {
	Inherit = { "Acolyte" },
},
Baby_Merchant = {
	Inherit = { "Merchant" },
},
Baby_Thief = {
	Inherit = { "Thief" },
},
Baby_Knight = {
	Inherit = { "Knight" },
},
Baby_Priest = {
	Inherit = { "Priest" },
},
Baby_Wizard = {
	Inherit = { "Wizard" },
},
Baby_Blacksmith = {
	Inherit = { "Blacksmith" },
},
Baby_Hunter = {
	Inherit = { "Hunter" },
},
Baby_Assassin = {
	Inherit = { "Assassin" },
},
Baby_Crusader = {
	Inherit = { "Crusader" },
},
Baby_Monk = {
	Inherit = { "Monk" },
},
Baby_Sage = {
	Inherit = { "Sage" },
},
Baby_Rogue = {
	Inherit = { "Rogue" },
},
Baby_Alchemist = {
	Inherit = { "Alchemist" },
},
Baby_Bard = {
	Inherit = { "Bard" },
},
Baby_Dancer = {
	Inherit = { "Dancer" },
},
Super_Baby = {
	Inherit = { "Super_Novice" },
},
Taekwon = {
	Inherit = { "Novice" },

	Skills = {
		TK_RUN = 10,
		TK_READYSTORM = {
			MaxLevel = 1,
			TK_STORMKICK = 1,
		},
		TK_STORMKICK = 7,
		TK_READYDOWN = {
			MaxLevel = 1,
			TK_DOWNKICK = 1,
		},
		TK_DOWNKICK = 7,
		TK_READYTURN = {
			MaxLevel = 1,
			TK_TURNKICK = 1,
		},
		TK_TURNKICK = 7,
		TK_READYCOUNTER = {
			MaxLevel = 1,
			TK_COUNTER = 1,
		},
		TK_COUNTER = 7,
		TK_DODGE = {
			MaxLevel = 1,
			TK_JUMPKICK = 7,
		},
		TK_JUMPKICK = 7,
		TK_HPTIME = 10,
		TK_SPTIME = 10,
		TK_POWER = 5,
		TK_SEVENWIND = {
			MaxLevel = 7,
			TK_HPTIME = 5,
			TK_SPTIME = 5,
			TK_POWER = 5,
		},
		TK_HIGHJUMP = 5,
		TK_MISSION = {
			MaxLevel = 1,
			TK_POWER = 5,
		},
	},
},
Star_Gladiator = {
	Inherit = { "Taekwon" },

	Skills = {
		SG_FEEL = 3,
		SG_SUN_WARM = {
			MaxLevel = 3,
			SG_FEEL = 1,
		},
		SG_MOON_WARM = {
			MaxLevel = 3,
			SG_FEEL = 2,
		},
		SG_STAR_WARM = {
			MaxLevel = 3,
			SG_FEEL = 3,
		},
		SG_SUN_COMFORT = {
			MaxLevel = 4,
			SG_FEEL = 1,
		},
		SG_MOON_COMFORT = {
			MaxLevel = 4,
			SG_FEEL = 2,
		},
		SG_STAR_COMFORT = {
			MaxLevel = 4,
			SG_FEEL = 3,
		},
		SG_HATE = 3,
		SG_SUN_ANGER = {
			MaxLevel = 3,
			SG_HATE = 1,
		},
		SG_MOON_ANGER = {
			MaxLevel = 3,
			SG_HATE = 2,
		},
		SG_STAR_ANGER = {
			MaxLevel = 3,
			SG_HATE = 3,
		},
		SG_SUN_BLESS = {
			MaxLevel = 5,
			SG_FEEL = 1,
			SG_HATE = 1,
		},
		SG_MOON_BLESS = {
			MaxLevel = 5,
			SG_FEEL = 2,
			SG_HATE = 2,
		},
		SG_STAR_BLESS = {
			MaxLevel = 5,
			SG_FEEL = 3,
			SG_HATE = 3,
		},
		SG_DEVIL = 10,
		SG_FRIEND = 3,
		SG_KNOWLEDGE = 10,
		SG_FUSION = {
			MaxLevel = 1,
			SG_KNOWLEDGE = 9,
		},
	},
},
Soul_Linker = {
	Inherit = { "Taekwon" },

	Skills = {
		SL_ALCHEMIST = 5,
		SL_MONK = 5,
		SL_STAR = 5,
		SL_SAGE = 5,
		SL_CRUSADER = 5,
		SL_SUPERNOVICE = 5,
		SL_KNIGHT = {
			MaxLevel = 5,
			SL_CRUSADER = 1,
		},
		SL_WIZARD = {
			MaxLevel = 5,
			SL_SAGE = 1,
		},
		SL_PRIEST = {
			MaxLevel = 5,
			SL_MONK = 1,
		},
		SL_BARDDANCER = 5,
		SL_ROGUE = {
			MaxLevel = 5,
			SL_ASSASIN = 1,
		},
		SL_ASSASIN = 5,
		SL_BLACKSMITH = {
			MaxLevel = 5,
			SL_ALCHEMIST = 1,
		},
		SL_HUNTER = {
			MaxLevel = 5,
			SL_BARDDANCER = 1,
		},
		SL_SOULLINKER = {
			MaxLevel = 5,
			SL_STAR = 1,
		},
		SL_KAIZEL = {
			MaxLevel = 7,
			SL_PRIEST = 1,
		},
		SL_KAAHI = {
			MaxLevel = 7,
			SL_PRIEST = 1,
			SL_CRUSADER = 1,
		},
		SL_KAUPE = {
			MaxLevel = 3,
			SL_ROGUE = 1,
		},
		SL_KAITE = {
			MaxLevel = 7,
			SL_WIZARD = 1,
		},
		SL_KAINA = {
			MaxLevel = 7,
			TK_SPTIME = 1,
		},
		SL_STIN = {
			MaxLevel = 7,
			SL_WIZARD = 1,
		},
		SL_STUN = {
			MaxLevel = 7,
			SL_WIZARD = 1,
		},
		SL_SMA = {
			MaxLevel = 10,
			SL_STIN = 7,
			SL_STUN = 7,
		},
		SL_SWOO = {
			MaxLevel = 7,
			SL_PRIEST = 1,
		},
		SL_SKE = {
			MaxLevel = 3,
			SL_KNIGHT = 1,
		},
		SL_SKA = {
			MaxLevel = 3,
			SL_MONK = 1,
		},
		SL_HIGH = {
			MaxLevel = 5,
			SL_SUPERNOVICE = 5,
		},
	},
},
Gangsi = {
	Inherit = { "Novice" },
},
Death_Knight = {
	Inherit = { "Novice" },
},
Dark_Collector = {
	Inherit = { "Novice" },
},
Rune_Knight = {
	Inherit = { "Knight" },

	Skills = {
		RK_ENCHANTBLADE = {
			MaxLevel = 5,
			RK_RUNEMASTERY = 2,
		},
		RK_SONICWAVE = {
			MaxLevel = 5,
			RK_ENCHANTBLADE = 3,
		},
		RK_DEATHBOUND = {
			MaxLevel = 10,
			KN_AUTOCOUNTER = 1,
			RK_ENCHANTBLADE = 2,
		},
		RK_HUNDREDSPEAR = {
			MaxLevel = 10,
			RK_PHANTOMTHRUST = 3,
		},
		RK_WINDCUTTER = {
			MaxLevel = 5,
			RK_ENCHANTBLADE = 5,
		},
		RK_IGNITIONBREAK = {
			MaxLevel = 5,
			RK_SONICWAVE = 2,
			RK_DEATHBOUND = 5,
			RK_WINDCUTTER = 3,
		},
		RK_DRAGONTRAINING = {
			MaxLevel = 5,
			KN_CAVALIERMASTERY = 1,
		},
		RK_DRAGONBREATH = {
			MaxLevel = 10,
			RK_DRAGONTRAINING = 2,
		},
		RK_DRAGONHOWLING = {
			MaxLevel = 5,
			RK_DRAGONTRAINING = 2,
		},
		RK_RUNEMASTERY = 10,
		RK_PHANTOMTHRUST = {
			MaxLevel = 5,
			KN_BRANDISHSPEAR = 2,
		},
		RK_DRAGONBREATH_WATER = {
			MaxLevel = 10,
			RK_DRAGONTRAINING = 2,
		},
		ALL_FULL_THROTTLE = 5,
	},
},
Warlock = {
	Inherit = { "Wizard" },

	Skills = {
		WL_WHITEIMPRISON = {
			MaxLevel = 5,
			WL_SOULEXPANSION = 3,
		},
		WL_SOULEXPANSION = {
			MaxLevel = 5,
			WL_DRAINLIFE = 1,
		},
		WL_FROSTMISTY = {
			MaxLevel = 5,
			WL_SUMMONWB = 1,
		},
		WL_JACKFROST = {
			MaxLevel = 5,
			WL_FROSTMISTY = 2,
		},
		WL_MARSHOFABYSS = {
			MaxLevel = 5,
			WZ_QUAGMIRE = 1,
		},
		WL_RECOGNIZEDSPELL = {
			MaxLevel = 5,
			WL_WHITEIMPRISON = 1,
			WL_STASIS = 1,
			WL_RELEASE = 2,
		},
		WL_SIENNAEXECRATE = {
			MaxLevel = 5,
			WL_SUMMONSTONE = 1,
		},
		WL_RADIUS = 3,
		WL_STASIS = {
			MaxLevel = 5,
			WL_DRAINLIFE = 1,
		},
		WL_DRAINLIFE = {
			MaxLevel = 5,
			WL_RADIUS = 1,
		},
		WL_CRIMSONROCK = {
			MaxLevel = 5,
			WL_SUMMONFB = 1,
		},
		WL_HELLINFERNO = {
			MaxLevel = 5,
			WL_CRIMSONROCK = 2,
		},
		WL_COMET = {
			MaxLevel = 5,
			WL_HELLINFERNO = 3,
		},
		WL_CHAINLIGHTNING = {
			MaxLevel = 5,
			WL_SUMMONBL = 1,
		},
		WL_EARTHSTRAIN = {
			MaxLevel = 5,
			WL_SIENNAEXECRATE = 2,
		},
		WL_TETRAVORTEX = {
			MaxLevel = 5,
			WL_JACKFROST = 5,
			WL_HELLINFERNO = 5,
			WL_CHAINLIGHTNING = 5,
			WL_EARTHSTRAIN = 5,
		},
		WL_SUMMONFB = {
			MaxLevel = 5,
			WZ_METEOR = 1,
		},
		WL_SUMMONBL = {
			MaxLevel = 5,
			WZ_VERMILION = 1,
		},
		WL_SUMMONWB = {
			MaxLevel = 5,
			WZ_STORMGUST = 1,
		},
		WL_SUMMONSTONE = {
			MaxLevel = 5,
			WZ_HEAVENDRIVE = 1,
		},
		WL_RELEASE = 2,
		WL_READING_SB = 1,
		WL_FREEZE_SP = 5,
		WL_TELEKINESIS_INTENSE = {
			MaxLevel = 5,
			WL_SOULEXPANSION = 5,
		},
		ALL_FULL_THROTTLE = 5,
	},
},
Ranger = {
	Inherit = { "Hunter" },

	Skills = {
		RA_ARROWSTORM = {
			MaxLevel = 10,
			RA_AIMEDBOLT = 5,
		},
		RA_FEARBREEZE = {
			MaxLevel = 5,
			RA_ARROWSTORM = 5,
			RA_CAMOUFLAGE = 1,
		},
		RA_RANGERMAIN = 10,
		RA_AIMEDBOLT = {
			MaxLevel = 10,
			HT_ANKLESNARE = 5,
		},
		RA_DETONATOR = {
			MaxLevel = 1,
			RA_CLUSTERBOMB = 3,
		},
		RA_ELECTRICSHOCKER = {
			MaxLevel = 5,
			HT_SHOCKWAVE = 5,
		},
		RA_CLUSTERBOMB = {
			MaxLevel = 5,
			RA_RESEARCHTRAP = 3,
		},
		RA_WUGMASTERY = 1,
		RA_WUGRIDER = {
			MaxLevel = 3,
			RA_WUGMASTERY = 1,
		},
		RA_WUGDASH = {
			MaxLevel = 1,
			RA_WUGRIDER = 1,
		},
		RA_WUGSTRIKE = {
			MaxLevel = 5,
			RA_TOOTHOFWUG = 1,
		},
		RA_WUGBITE = {
			MaxLevel = 5,
			RA_WUGMASTERY = 1,
		},
		RA_TOOTHOFWUG = {
			MaxLevel = 10,
			RA_WUGMASTERY = 1,
		},
		RA_SENSITIVEKEEN = {
			MaxLevel = 5,
			RA_TOOTHOFWUG = 3,
		},
		RA_CAMOUFLAGE = {
			MaxLevel = 5,
			RA_RANGERMAIN = 1,
		},
		RA_RESEARCHTRAP = {
			MaxLevel = 5,
			HT_CLAYMORETRAP = 1,
			HT_REMOVETRAP = 1,
		},
		RA_MAGENTATRAP = {
			MaxLevel = 1,
			RA_RESEARCHTRAP = 1,
		},
		RA_COBALTTRAP = {
			MaxLevel = 1,
			RA_RESEARCHTRAP = 1,
		},
		RA_MAIZETRAP = {
			MaxLevel = 1,
			RA_RESEARCHTRAP = 1,
		},
		RA_VERDURETRAP = {
			MaxLevel = 1,
			RA_RESEARCHTRAP = 1,
		},
		RA_FIRINGTRAP = {
			MaxLevel = 5,
			RA_DETONATOR = 1,
		},
		RA_ICEBOUNDTRAP = {
			MaxLevel = 5,
			RA_DETONATOR = 1,
		},
		RA_UNLIMIT = {
			MaxLevel = 5,
			RA_FEARBREEZE = 5,
		},
		ALL_FULL_THROTTLE = 5,
	},
},
Arch_Bishop = {
	Inherit = { "Priest" },

	Skills = {
		AB_JUDEX = {
			MaxLevel = 5,
			PR_TURNUNDEAD = 1,
		},
		AB_ANCILLA = {
			MaxLevel = 1,
			AB_CLEMENTIA = 3,
		},
		AB_ADORAMUS = {
			MaxLevel = 10,
			PR_MAGNUS = 1,
			AB_JUDEX = 1,
			AB_ANCILLA = 1,
		},
		AB_CLEMENTIA = {
			MaxLevel = 3,
			AL_BLESSING = 1,
		},
		AB_CANTO = {
			MaxLevel = 3,
			AL_INCAGI = 1,
		},
		AB_CHEAL = {
			MaxLevel = 3,
			AL_HEAL = 1,
		},
		AB_EPICLESIS = {
			MaxLevel = 5,
			AB_ANCILLA = 1,
			AB_HIGHNESSHEAL = 1,
		},
		AB_PRAEFATIO = {
			MaxLevel = 10,
			PR_KYRIE = 1,
		},
		AB_ORATIO = {
			MaxLevel = 10,
			AB_PRAEFATIO = 5,
		},
		AB_LAUDAAGNUS = {
			MaxLevel = 4,
			PR_STRECOVERY = 1,
		},
		AB_LAUDARAMUS = {
			MaxLevel = 4,
			AB_LAUDAAGNUS = 2,
		},
		AB_EUCHARISTICA = {
			MaxLevel = 10,
			AB_EPICLESIS = 1,
			AB_EXPIATIO = 1,
		},
		AB_RENOVATIO = {
			MaxLevel = 1,
			AB_CHEAL = 3,
		},
		AB_HIGHNESSHEAL = {
			MaxLevel = 5,
			AB_RENOVATIO = 1,
		},
		AB_CLEARANCE = {
			MaxLevel = 5,
			AB_LAUDARAMUS = 2,
		},
		AB_EXPIATIO = {
			MaxLevel = 5,
			AB_ORATIO = 5,
			AB_DUPLELIGHT = 5,
		},
		AB_DUPLELIGHT = {
			MaxLevel = 10,
			PR_ASPERSIO = 1,
		},
		AB_SILENTIUM = {
			MaxLevel = 5,
			AB_CLEARANCE = 1,
		},
		AB_SECRAMENT = {
			MaxLevel = 5,
			AB_EPICLESIS = 1,
			AB_EXPIATIO = 1,
		},
		AB_OFFERTORIUM = {
			MaxLevel = 5,
			AB_HIGHNESSHEAL = 2,
		},
		ALL_FULL_THROTTLE = 5,
	},
},
Mechanic = {
	Inherit = { "Blacksmith" },

	Skills = {
		NC_MADOLICENCE = 5,
		NC_BOOSTKNUCKLE = {
			MaxLevel = 5,
			NC_MADOLICENCE = 1,
		},
		NC_PILEBUNKER = {
			MaxLevel = 3,
			NC_BOOSTKNUCKLE = 2,
		},
		NC_VULCANARM = {
			MaxLevel = 3,
			NC_BOOSTKNUCKLE = 2,
		},
		NC_FLAMELAUNCHER = {
			MaxLevel = 3,
			NC_VULCANARM = 3,
		},
		NC_COLDSLOWER = {
			MaxLevel = 3,
			NC_VULCANARM = 3,
		},
		NC_ARMSCANNON = {
			MaxLevel = 3,
			NC_FLAMELAUNCHER = 2,
			NC_COLDSLOWER = 2,
		},
		NC_ACCELERATION = {
			MaxLevel = 3,
			NC_MADOLICENCE = 1,
		},
		NC_HOVERING = {
			MaxLevel = 1,
			NC_ACCELERATION = 1,
		},
		NC_F_SIDESLIDE = {
			MaxLevel = 1,
			NC_HOVERING = 1,
		},
		NC_B_SIDESLIDE = {
			MaxLevel = 1,
			NC_HOVERING = 1,
		},
		NC_MAINFRAME = {
			MaxLevel = 4,
			NC_MADOLICENCE = 4,
		},
		NC_SELFDESTRUCTION = {
			MaxLevel = 3,
			NC_MAINFRAME = 2,
		},
		NC_SHAPESHIFT = {
			MaxLevel = 4,
			NC_MAINFRAME = 2,
		},
		NC_EMERGENCYCOOL = {
			MaxLevel = 1,
			NC_SELFDESTRUCTION = 2,
		},
		NC_INFRAREDSCAN = {
			MaxLevel = 1,
			NC_SHAPESHIFT = 2,
		},
		NC_ANALYZE = {
			MaxLevel = 3,
			NC_INFRAREDSCAN = 1,
		},
		NC_MAGNETICFIELD = {
			MaxLevel = 3,
			NC_EMERGENCYCOOL = 1,
		},
		NC_NEUTRALBARRIER = {
			MaxLevel = 3,
			NC_MAGNETICFIELD = 2,
		},
		NC_STEALTHFIELD = {
			MaxLevel = 3,
			NC_ANALYZE = 3,
			NC_NEUTRALBARRIER = 2,
		},
		NC_REPAIR = {
			MaxLevel = 5,
			NC_MADOLICENCE = 1,
		},
		NC_TRAININGAXE = 10,
		NC_RESEARCHFE = 5,
		NC_AXEBOOMERANG = {
			MaxLevel = 5,
			NC_TRAININGAXE = 1,
		},
		NC_POWERSWING = {
			MaxLevel = 5,
			NC_AXEBOOMERANG = 3,
		},
		NC_AXETORNADO = {
			MaxLevel = 5,
			NC_TRAININGAXE = 1,
		},
		NC_SILVERSNIPER = {
			MaxLevel = 5,
			NC_RESEARCHFE = 2,
		},
		NC_MAGICDECOY = {
			MaxLevel = 5,
			NC_RESEARCHFE = 2,
		},
		NC_DISJOINT = {
			MaxLevel = 1,
			NC_SILVERSNIPER = 1,
		},
		NC_MAGMA_ERUPTION = 5,
		ALL_FULL_THROTTLE = 5,
	},
},
Guillotine_Cross = {
	Inherit = { "Assassin" },

	Skills = {
		GC_VENOMIMPRESS = {
			MaxLevel = 5,
			AS_ENCHANTPOISON = 3,
		},
		GC_CROSSIMPACT = {
			MaxLevel = 5,
			AS_SONICBLOW = 10,
		},
		GC_DARKILLUSION = {
			MaxLevel = 5,
			GC_CROSSIMPACT = 3,
		},
		GC_RESEARCHNEWPOISON = 10,
		GC_CREATENEWPOISON = {
			MaxLevel = 1,
			GC_RESEARCHNEWPOISON = 1,
		},
		GC_ANTIDOTE = {
			MaxLevel = 1,
			GC_RESEARCHNEWPOISON = 5,
		},
		GC_POISONINGWEAPON = {
			MaxLevel = 5,
			GC_CREATENEWPOISON = 1,
		},
		GC_WEAPONBLOCKING = {
			MaxLevel = 5,
			AS_LEFT = 5,
		},
		GC_COUNTERSLASH = {
			MaxLevel = 5,
			GC_WEAPONBLOCKING = 1,
		},
		GC_WEAPONCRUSH = {
			MaxLevel = 5,
			GC_WEAPONBLOCKING = 1,
		},
		GC_VENOMPRESSURE = {
			MaxLevel = 5,
			GC_POISONINGWEAPON = 3,
			GC_WEAPONBLOCKING = 1,
		},
		GC_POISONSMOKE = {
			MaxLevel = 5,
			GC_POISONINGWEAPON = 5,
			GC_VENOMPRESSURE = 5,
		},
		GC_CLOAKINGEXCEED = {
			MaxLevel = 5,
			AS_CLOAKING = 3,
		},
		GC_PHANTOMMENACE = {
			MaxLevel = 1,
			GC_DARKILLUSION = 5,
			GC_CLOAKINGEXCEED = 5,
		},
		GC_HALLUCINATIONWALK = {
			MaxLevel = 5,
			GC_PHANTOMMENACE = 1,
		},
		GC_ROLLINGCUTTER = {
			MaxLevel = 5,
			AS_SONICBLOW = 10,
		},
		GC_CROSSRIPPERSLASHER = {
			MaxLevel = 5,
			GC_ROLLINGCUTTER = 1,
		},
		GC_DARKCROW = {
			MaxLevel = 5,
			GC_DARKILLUSION = 5,
		},
		ALL_FULL_THROTTLE = 5,
	},
},
Rune_Knight_Trans = {
	Inherit = { "Lord_Knight", "Rune_Knight" },
},
Warlock_Trans = {
	Inherit = { "High_Wizard", "Warlock" },
},
Ranger_Trans = {
	Inherit = { "Sniper", "Ranger" },
},
Arch_Bishop_Trans = {
	Inherit = { "High_Priest", "Arch_Bishop" },
},
Mechanic_Trans = {
	Inherit = { "Whitesmith", "Mechanic" },
},
Guillotine_Cross_Trans = {
	Inherit = { "Assassin_Cross", "Guillotine_Cross" },
},
Royal_Guard = {
	Inherit = { "Crusader" },

	Skills = {
		LG_CANNONSPEAR = {
			MaxLevel = 5,
			LG_PINPOINTATTACK = 1,
		},
		LG_BANISHINGPOINT = {
			MaxLevel = 10,
			KN_SPEARMASTERY = 1,
		},
		LG_TRAMPLE = 3,
		LG_SHIELDPRESS = {
			MaxLevel = 5,
			CR_SHIELDCHARGE = 3,
		},
		LG_REFLECTDAMAGE = {
			MaxLevel = 5,
			CR_REFLECTSHIELD = 5,
		},
		LG_PINPOINTATTACK = {
			MaxLevel = 5,
			LG_BANISHINGPOINT = 5,
		},
		LG_FORCEOFVANGUARD = 5,
		LG_RAGEBURST = {
			MaxLevel = 1,
			LG_FORCEOFVANGUARD = 1,
		},
		LG_SHIELDSPELL = {
			MaxLevel = 3,
			LG_SHIELDPRESS = 3,
			LG_EARTHDRIVE = 2,
		},
		LG_EXEEDBREAK = {
			MaxLevel = 5,
			LG_BANISHINGPOINT = 3,
		},
		LG_OVERBRAND = {
			MaxLevel = 5,
			LG_PINPOINTATTACK = 1,
			LG_MOONSLASHER = 3,
		},
		LG_PRESTIGE = {
			MaxLevel = 5,
			LG_TRAMPLE = 3,
		},
		LG_BANDING = {
			MaxLevel = 5,
			LG_PINPOINTATTACK = 3,
			LG_RAGEBURST = 1,
		},
		LG_MOONSLASHER = {
			MaxLevel = 5,
			KN_SPEARMASTERY = 1,
		},
		LG_RAYOFGENESIS = {
			MaxLevel = 5,
			CR_GRANDCROSS = 5,
		},
		LG_PIETY = {
			MaxLevel = 5,
			CR_TRUST = 3,
		},
		LG_EARTHDRIVE = {
			MaxLevel = 5,
			LG_REFLECTDAMAGE = 3,
		},
		LG_HESPERUSLIT = {
			MaxLevel = 5,
			LG_PRESTIGE = 3,
			LG_BANDING = 3,
		},
		LG_INSPIRATION = {
			MaxLevel = 5,
			LG_SHIELDSPELL = 3,
			LG_RAYOFGENESIS = 4,
			LG_PIETY = 5,
		},
		LG_KINGS_GRACE = {
			MaxLevel = 5,
			LG_REFLECTDAMAGE = 5,
		},
		ALL_FULL_THROTTLE = 5,
	},
},
Sorcerer = {
	Inherit = { "Sage" },

	Skills = {
		SO_FIREWALK = {
			MaxLevel = 5,
			SA_VOLCANO = 1,
		},
		SO_ELECTRICWALK = {
			MaxLevel = 5,
			SA_VIOLENTGALE = 1,
		},
		SO_SPELLFIST = {
			MaxLevel = 5,
			SA_AUTOSPELL = 4,
		},
		SO_EARTHGRAVE = {
			MaxLevel = 5,
			WZ_EARTHSPIKE = 5,
		},
		SO_DIAMONDDUST = {
			MaxLevel = 5,
			SA_DELUGE = 3,
		},
		SO_POISON_BUSTER = {
			MaxLevel = 5,
			SO_CLOUD_KILL = 2,
		},
		SO_PSYCHIC_WAVE = {
			MaxLevel = 5,
			SA_DISPELL = 2,
		},
		SO_CLOUD_KILL = {
			MaxLevel = 5,
			WZ_HEAVENDRIVE = 5,
		},
		SO_STRIKING = {
			MaxLevel = 5,
			SA_FLAMELAUNCHER = 1,
			SA_FROSTWEAPON = 1,
			SA_LIGHTNINGLOADER = 1,
			SA_SEISMICWEAPON = 1,
		},
		SO_WARMER = {
			MaxLevel = 5,
			SA_VOLCANO = 1,
			SA_VIOLENTGALE = 1,
		},
		SO_VACUUM_EXTREME = {
			MaxLevel = 5,
			SA_LANDPROTECTOR = 2,
		},
		SO_VARETYR_SPEAR = {
			MaxLevel = 5,
			SA_SEISMICWEAPON = 1,
			SA_VIOLENTGALE = 4,
		},
		SO_ARRULLO = {
			MaxLevel = 5,
			SO_WARMER = 2,
		},
		SO_EL_CONTROL = {
			MaxLevel = 4,
			SO_EL_ANALYSIS = 1,
		},
		SO_SUMMON_AGNI = {
			MaxLevel = 3,
			SO_WARMER = 3,
			SO_EL_CONTROL = 1,
		},
		SO_SUMMON_AQUA = {
			MaxLevel = 3,
			SO_DIAMONDDUST = 3,
			SO_EL_CONTROL = 1,
		},
		SO_SUMMON_VENTUS = {
			MaxLevel = 3,
			SO_VARETYR_SPEAR = 3,
			SO_EL_CONTROL = 1,
		},
		SO_SUMMON_TERA = {
			MaxLevel = 3,
			SO_EARTHGRAVE = 3,
			SO_EL_CONTROL = 1,
		},
		SO_EL_ACTION = {
			MaxLevel = 1,
			SO_EL_CONTROL = 3,
		},
		SO_EL_ANALYSIS = {
			MaxLevel = 2,
			SA_FLAMELAUNCHER = 1,
			SA_FROSTWEAPON = 1,
			SA_LIGHTNINGLOADER = 1,
			SA_SEISMICWEAPON = 1,
		},
		SO_EL_SYMPATHY = {
			MaxLevel = 5,
			SO_EL_CONTROL = 3,
		},
		SO_EL_CURE = {
			MaxLevel = 1,
			SO_EL_SYMPATHY = 1,
		},
		SO_FIRE_INSIGNIA = {
			MaxLevel = 3,
			SO_SUMMON_AGNI = 3,
		},
		SO_WATER_INSIGNIA = {
			MaxLevel = 3,
			SO_SUMMON_AQUA = 3,
		},
		SO_WIND_INSIGNIA = {
			MaxLevel = 3,
			SO_SUMMON_VENTUS = 3,
		},
		SO_EARTH_INSIGNIA = {
			MaxLevel = 3,
			SO_SUMMON_TERA = 3,
		},
		SO_ELEMENTAL_SHIELD = {
			MaxLevel = 5,
			SO_EL_CONTROL = 3,
		},
		ALL_FULL_THROTTLE = 5,
	},
},
Minstrel = {
	Inherit = { "Bard" },

	Skills = {
		MI_RUSH_WINDMILL = {
			MaxLevel = 5,
			WM_LULLABY_DEEPSLEEP = 1,
		},
		MI_ECHOSONG = {
			MaxLevel = 5,
			WM_LULLABY_DEEPSLEEP = 1,
		},
		MI_HARMONIZE = {
			MaxLevel = 5,
			WM_LULLABY_DEEPSLEEP = 1,
		},
		WM_LESSON = 10,
		WM_METALICSOUND = {
			MaxLevel = 5,
			WM_DOMINION_IMPULSE = 1,
		},
		WM_REVERBERATION = {
			MaxLevel = 5,
			BA_DISSONANCE = 5,
		},
		WM_DOMINION_IMPULSE = {
			MaxLevel = 1,
			WM_REVERBERATION = 1,
		},
		WM_SEVERE_RAINSTORM = {
			MaxLevel = 5,
			BA_MUSICALSTRIKE = 5,
		},
		WM_POEMOFNETHERWORLD = {
			MaxLevel = 5,
			WM_LESSON = 1,
		},
		WM_VOICEOFSIREN = {
			MaxLevel = 5,
			WM_POEMOFNETHERWORLD = 3,
		},
		WM_DEADHILLHERE = {
			MaxLevel = 5,
			WM_SIRCLEOFNATURE = 3,
		},
		WM_LULLABY_DEEPSLEEP = {
			MaxLevel = 5,
			WM_LESSON = 1,
		},
		WM_SIRCLEOFNATURE = {
			MaxLevel = 5,
			WM_LESSON = 1,
		},
		WM_RANDOMIZESPELL = {
			MaxLevel = 5,
			WM_POEMOFNETHERWORLD = 1,
		},
		WM_GLOOMYDAY = {
			MaxLevel = 5,
			WM_RANDOMIZESPELL = 1,
		},
		WM_GREAT_ECHO = {
			MaxLevel = 5,
			WM_METALICSOUND = 1,
		},
		WM_SONG_OF_MANA = {
			MaxLevel = 5,
			MI_RUSH_WINDMILL = 1,
			MI_ECHOSONG = 1,
			MI_HARMONIZE = 1,
		},
		WM_DANCE_WITH_WUG = {
			MaxLevel = 5,
			MI_RUSH_WINDMILL = 1,
			MI_ECHOSONG = 1,
			MI_HARMONIZE = 1,
		},
		WM_SOUND_OF_DESTRUCTION = {
			MaxLevel = 5,
			WM_SATURDAY_NIGHT_FEVER = 3,
			WM_MELODYOFSINK = 3,
		},
		WM_SATURDAY_NIGHT_FEVER = {
			MaxLevel = 5,
			WM_DANCE_WITH_WUG = 1,
		},
		WM_LERADS_DEW = {
			MaxLevel = 5,
			MI_RUSH_WINDMILL = 1,
			MI_ECHOSONG = 1,
			MI_HARMONIZE = 1,
		},
		WM_MELODYOFSINK = {
			MaxLevel = 5,
			WM_SONG_OF_MANA = 1,
		},
		WM_BEYOND_OF_WARCRY = {
			MaxLevel = 5,
			WM_LERADS_DEW = 1,
		},
		WM_UNLIMITED_HUMMING_VOICE = {
			MaxLevel = 5,
			WM_SOUND_OF_DESTRUCTION = 1,
			WM_BEYOND_OF_WARCRY = 1,
		},
		WM_FRIGG_SONG = {
			MaxLevel = 5,
			WM_LESSON = 1,
		},
		ALL_FULL_THROTTLE = 5,
	},
},
Wanderer = {
	Inherit = { "Dancer" },

	Skills = {
		WA_SWING_DANCE = {
			MaxLevel = 5,
			WM_LULLABY_DEEPSLEEP = 1,
		},
		WA_SYMPHONY_OF_LOVER = {
			MaxLevel = 5,
			WM_LULLABY_DEEPSLEEP = 1,
		},
		WA_MOONLIT_SERENADE = {
			MaxLevel = 5,
			WM_LULLABY_DEEPSLEEP = 1,
		},
		WM_LESSON = 10,
		WM_METALICSOUND = {
			MaxLevel = 5,
			WM_DOMINION_IMPULSE = 1,
		},
		WM_REVERBERATION = {
			MaxLevel = 5,
			DC_UGLYDANCE = 5,
		},
		WM_DOMINION_IMPULSE = {
			MaxLevel = 1,
			WM_REVERBERATION = 1,
		},
		WM_SEVERE_RAINSTORM = {
			MaxLevel = 5,
			DC_THROWARROW = 5,
		},
		WM_POEMOFNETHERWORLD = {
			MaxLevel = 5,
			WM_LESSON = 1,
		},
		WM_VOICEOFSIREN = {
			MaxLevel = 5,
			WM_POEMOFNETHERWORLD = 3,
		},
		WM_DEADHILLHERE = {
			MaxLevel = 5,
			WM_SIRCLEOFNATURE = 3,
		},
		WM_LULLABY_DEEPSLEEP = {
			MaxLevel = 5,
			WM_LESSON = 1,
		},
		WM_SIRCLEOFNATURE = {
			MaxLevel = 5,
			WM_LESSON = 1,
		},
		WM_RANDOMIZESPELL = {
			MaxLevel = 5,
			WM_POEMOFNETHERWORLD = 1,
		},
		WM_GLOOMYDAY = {
			MaxLevel = 5,
			WM_RANDOMIZESPELL = 1,
		},
		WM_GREAT_ECHO = {
			MaxLevel = 5,
			WM_METALICSOUND = 1,
		},
		WM_SONG_OF_MANA = {
			MaxLevel = 5,
			WA_SWING_DANCE = 1,
			WA_SYMPHONY_OF_LOVER = 1,
			WA_MOONLIT_SERENADE = 1,
		},
		WM_DANCE_WITH_WUG = {
			MaxLevel = 5,
			WA_SWING_DANCE = 1,
			WA_SYMPHONY_OF_LOVER = 1,
			WA_MOONLIT_SERENADE = 1,
		},
		WM_SOUND_OF_DESTRUCTION = {
			MaxLevel = 5,
			WM_SATURDAY_NIGHT_FEVER = 3,
			WM_MELODYOFSINK = 3,
		},
		WM_SATURDAY_NIGHT_FEVER = {
			MaxLevel = 5,
			WM_DANCE_WITH_WUG = 1,
		},
		WM_LERADS_DEW = {
			MaxLevel = 5,
			WA_SWING_DANCE = 1,
			WA_SYMPHONY_OF_LOVER = 1,
			WA_MOONLIT_SERENADE = 1,
		},
		WM_MELODYOFSINK = {
			MaxLevel = 5,
			WM_SONG_OF_MANA = 1,
		},
		WM_BEYOND_OF_WARCRY = {
			MaxLevel = 5,
			WM_LERADS_DEW = 1,
		},
		WM_UNLIMITED_HUMMING_VOICE = {
			MaxLevel = 5,
			WM_SOUND_OF_DESTRUCTION = 1,
			WM_BEYOND_OF_WARCRY = 1,
		},
		WM_FRIGG_SONG = {
			MaxLevel = 5,
			WM_LESSON = 1,
		},
		ALL_FULL_THROTTLE = 5,
	},
},
Sura = {
	Inherit = { "Monk" },

	Skills = {
		SR_DRAGONCOMBO = {
			MaxLevel = 10,
			MO_TRIPLEATTACK = 5,
		},
		SR_SKYNETBLOW = {
			MaxLevel = 5,
			SR_DRAGONCOMBO = 3,
		},
		SR_EARTHSHAKER = {
			MaxLevel = 5,
			SR_DRAGONCOMBO = 1,
			SR_CURSEDCIRCLE = 1,
		},
		SR_FALLENEMPIRE = {
			MaxLevel = 5,
			SR_DRAGONCOMBO = 1,
		},
		SR_TIGERCANNON = {
			MaxLevel = 10,
			SR_FALLENEMPIRE = 3,
		},
		SR_RAMPAGEBLASTER = {
			MaxLevel = 5,
			SR_EARTHSHAKER = 2,
		},
		SR_CRESCENTELBOW = {
			MaxLevel = 5,
			SR_SKYNETBLOW = 1,
		},
		SR_CURSEDCIRCLE = {
			MaxLevel = 5,
			MO_BLADESTOP = 2,
			SR_GENTLETOUCH_QUIET = 2,
		},
		SR_LIGHTNINGWALK = {
			MaxLevel = 5,
			SR_WINDMILL = 1,
		},
		SR_KNUCKLEARROW = {
			MaxLevel = 5,
			SR_RAMPAGEBLASTER = 3,
			SR_LIGHTNINGWALK = 3,
		},
		SR_WINDMILL = {
			MaxLevel = 1,
			SR_CURSEDCIRCLE = 1,
		},
		SR_RAISINGDRAGON = {
			MaxLevel = 10,
			SR_RAMPAGEBLASTER = 3,
			SR_GENTLETOUCH_ENERGYGAIN = 3,
		},
		SR_ASSIMILATEPOWER = {
			MaxLevel = 1,
			MO_ABSORBSPIRITS = 1,
			SR_POWERVELOCITY = 1,
		},
		SR_POWERVELOCITY = {
			MaxLevel = 1,
			MO_CALLSPIRITS = 5,
		},
		SR_GATEOFHELL = {
			MaxLevel = 10,
			SR_TIGERCANNON = 5,
			SR_RAISINGDRAGON = 5,
		},
		SR_GENTLETOUCH_QUIET = {
			MaxLevel = 5,
			SR_POWERVELOCITY = 1,
		},
		SR_GENTLETOUCH_CURE = {
			MaxLevel = 5,
			SR_POWERVELOCITY = 1,
		},
		SR_GENTLETOUCH_ENERGYGAIN = {
			MaxLevel = 5,
			SR_GENTLETOUCH_QUIET = 3,
		},
		SR_GENTLETOUCH_CHANGE = {
			MaxLevel = 5,
			SR_GENTLETOUCH_CURE = 4,
		},
		SR_GENTLETOUCH_REVITALIZE = {
			MaxLevel = 5,
			SR_GENTLETOUCH_CHANGE = 5,
		},
		SR_HOWLINGOFLION = {
			MaxLevel = 5,
			SR_ASSIMILATEPOWER = 1,
			SR_RIDEINLIGHTNING = 3,
		},
		SR_RIDEINLIGHTNING = {
			MaxLevel = 5,
			MO_FINGEROFFENSIVE = 3,
		},
		SR_FLASHCOMBO = {
			MaxLevel = 5,
			SR_DRAGONCOMBO = 3,
			SR_FALLENEMPIRE = 3,
			SR_TIGERCANNON = 1,
			SR_SKYNETBLOW = 1,
		},
		ALL_FULL_THROTTLE = 5,
	},
},
Genetic = {
	Inherit = { "Alchemist" },

	Skills = {
		GN_TRAINING_SWORD = 5,
		GN_REMODELING_CART = 5,
		GN_CART_TORNADO = {
			MaxLevel = 5,
			GN_REMODELING_CART = 1,
		},
		GN_CARTCANNON = {
			MaxLevel = 5,
			GN_REMODELING_CART = 2,
		},
		GN_CARTBOOST = {
			MaxLevel = 5,
			GN_REMODELING_CART = 3,
		},
		GN_THORNS_TRAP = {
			MaxLevel = 5,
			GN_S_PHARMACY = 2,
		},
		GN_BLOOD_SUCKER = {
			MaxLevel = 5,
			GN_S_PHARMACY = 3,
		},
		GN_SPORE_EXPLOSION = {
			MaxLevel = 5,
			GN_S_PHARMACY = 4,
		},
		GN_WALLOFTHORN = {
			MaxLevel = 5,
			GN_THORNS_TRAP = 3,
		},
		GN_CRAZYWEED = {
			MaxLevel = 10,
			GN_WALLOFTHORN = 3,
		},
		GN_DEMONIC_FIRE = {
			MaxLevel = 5,
			GN_SPORE_EXPLOSION = 3,
		},
		GN_FIRE_EXPANSION = {
			MaxLevel = 5,
			GN_DEMONIC_FIRE = 3,
		},
		GN_HELLS_PLANT = {
			MaxLevel = 5,
			GN_BLOOD_SUCKER = 3,
		},
		GN_MANDRAGORA = {
			MaxLevel = 5,
			GN_HELLS_PLANT = 3,
		},
		GN_SLINGITEM = {
			MaxLevel = 1,
			GN_CHANGEMATERIAL = 1,
		},
		GN_CHANGEMATERIAL = 1,
		GN_MIX_COOKING = {
			MaxLevel = 2,
			GN_S_PHARMACY = 1,
		},
		GN_MAKEBOMB = {
			MaxLevel = 2,
			GN_MIX_COOKING = 1,
		},
		GN_S_PHARMACY = 10,
		GN_ILLUSIONDOPING = {
			MaxLevel = 5,
			GN_S_PHARMACY = 1,
		},
		ALL_FULL_THROTTLE = 5,
	},
},
Shadow_Chaser = {
	Inherit = { "Rogue" },

	Skills = {
		SC_FATALMENACE = {
			MaxLevel = 5,
			RG_INTIMIDATE = 5,
		},
		SC_REPRODUCE = {
			MaxLevel = 10,
			RG_PLAGIARISM = 5,
		},
		SC_AUTOSHADOWSPELL = {
			MaxLevel = 10,
			SC_REPRODUCE = 5,
		},
		SC_SHADOWFORM = {
			MaxLevel = 5,
			RG_TUNNELDRIVE = 3,
		},
		SC_TRIANGLESHOT = {
			MaxLevel = 10,
			AC_DOUBLE = 7,
		},
		SC_BODYPAINT = 5,
		SC_INVISIBILITY = {
			MaxLevel = 5,
			SC_AUTOSHADOWSPELL = 7,
			SC_DEADLYINFECT = 5,
			SC_UNLUCKY = 3,
		},
		SC_DEADLYINFECT = {
			MaxLevel = 5,
			SC_AUTOSHADOWSPELL = 5,
			SC_SHADOWFORM = 3,
		},
		SC_ENERVATION = {
			MaxLevel = 3,
			SC_BODYPAINT = 1,
		},
		SC_GROOMY = {
			MaxLevel = 3,
			SC_BODYPAINT = 1,
		},
		SC_IGNORANCE = {
			MaxLevel = 3,
			SC_BODYPAINT = 1,
		},
		SC_LAZINESS = {
			MaxLevel = 3,
			SC_ENERVATION = 1,
			SC_GROOMY = 1,
			SC_IGNORANCE = 1,
		},
		SC_UNLUCKY = {
			MaxLevel = 3,
			SC_LAZINESS = 1,
			SC_WEAKNESS = 1,
		},
		SC_WEAKNESS = {
			MaxLevel = 3,
			SC_ENERVATION = 1,
			SC_GROOMY = 1,
			SC_IGNORANCE = 1,
		},
		SC_STRIPACCESSARY = {
			MaxLevel = 5,
			RG_STRIPWEAPON = 1,
		},
		SC_MANHOLE = {
			MaxLevel = 3,
			RG_FLAGGRAFFITI = 1,
		},
		SC_DIMENSIONDOOR = {
			MaxLevel = 3,
			SC_MANHOLE = 1,
		},
		SC_CHAOSPANIC = {
			MaxLevel = 3,
			SC_MANHOLE = 1,
		},
		SC_MAELSTROM = {
			MaxLevel = 3,
			SC_UNLUCKY = 3,
			SC_CHAOSPANIC = 3,
		},
		SC_BLOODYLUST = {
			MaxLevel = 3,
			SC_DIMENSIONDOOR = 3,
		},
		SC_FEINTBOMB = {
			MaxLevel = 3,
			SC_DIMENSIONDOOR = 3,
		},
		SC_ESCAPE = {
			MaxLevel = 5,
			SC_TRIANGLESHOT = 2,
		},
		ALL_FULL_THROTTLE = 5,
	},
},
Royal_Guard_Trans = {
	Inherit = { "Paladin", "Royal_Guard" },
},
Sorcerer_Trans = {
	Inherit = { "Professor", "Sorcerer" },
},
Minstrel_Trans = {
	Inherit = { "Clown", "Minstrel" },
},
Wanderer_Trans = {
	Inherit = { "Gypsy", "Wanderer" },
},
Sura_Trans = {
	Inherit = { "Champion", "Sura" },
},
Genetic_Trans = {
	Inherit = { "Creator", "Genetic" },
},
Shadow_Chaser_Trans = {
	Inherit = { "Stalker", "Shadow_Chaser" },
},
Baby_Rune_Knight = {
	Inherit = { "Rune_Knight" },
},
Baby_Warlock = {
	Inherit = { "Warlock" },
},
Baby_Ranger = {
	Inherit = { "Ranger" },
},
Baby_Arch_Bishop = {
	Inherit = { "Arch_Bishop" },
},
Baby_Mechanic = {
	Inherit = { "Mechanic" },
},
Baby_Guillotine_Cross = {
	Inherit = { "Guillotine_Cross" },
},
Baby_Royal_Guard = {
	Inherit = { "Royal_Guard" },
},
Baby_Sorcerer = {
	Inherit = { "Sorcerer" },
},
Baby_Minstrel = {
	Inherit = { "Minstrel" },
},
Baby_Wanderer = {
	Inherit = { "Wanderer" },
},
Baby_Sura = {
	Inherit = { "Sura" },
},
Baby_Genetic = {
	Inherit = { "Genetic" },
},
Baby_Shadow_Chaser = {
	Inherit = { "Shadow_Chaser" },
},
Expanded_Super_Novice = {
	Inherit = { "Super_Novice" },

	Skills = {
		PR_IMPOSITIO = 5,
		PR_SANCTUARY = {
			MaxLevel = 10,
			AL_HEAL = 1,
		},
		PR_STRECOVERY = 1,
		PR_GLORIA = {
			MaxLevel = 5,
			PR_SANCTUARY = 7,
		},
		WZ_FIREPILLAR = {
			MaxLevel = 10,
			MG_FIREWALL = 1,
		},
		WZ_SIGHTRASHER = {
			MaxLevel = 10,
			MG_LIGHTNINGBOLT = 1,
			MG_SIGHT = 1,
		},
		WZ_JUPITEL = {
			MaxLevel = 10,
			MG_NAPALMBEAT = 1,
			MG_LIGHTNINGBOLT = 1,
		},
		WZ_WATERBALL = {
			MaxLevel = 5,
			MG_COLDBOLT = 1,
			MG_LIGHTNINGBOLT = 1,
		},
		WZ_ICEWALL = {
			MaxLevel = 10,
			MG_STONECURSE = 1,
			MG_FROSTDIVER = 1,
		},
		WZ_FROSTNOVA = {
			MaxLevel = 10,
			WZ_ICEWALL = 1,
		},
		WZ_EARTHSPIKE = {
			MaxLevel = 5,
			MG_STONECURSE = 1,
		},
		WZ_HEAVENDRIVE = {
			MaxLevel = 5,
			WZ_EARTHSPIKE = 3,
		},
		WZ_QUAGMIRE = {
			MaxLevel = 5,
			WZ_HEAVENDRIVE = 1,
		},
		WZ_ESTIMATION = 1,
		BS_HILTBINDING = 1,
		BS_WEAPONRESEARCH = {
			MaxLevel = 10,
			BS_HILTBINDING = 1,
		},
		HT_SKIDTRAP = 5,
		HT_SANDMAN = {
			MaxLevel = 5,
			HT_FLASHER = 1,
		},
		HT_FLASHER = {
			MaxLevel = 5,
			HT_SKIDTRAP = 1,
		},
		HT_FREEZINGTRAP = {
			MaxLevel = 5,
			HT_FLASHER = 1,
		},
		AS_ENCHANTPOISON = {
			MaxLevel = 10,
			TF_POISON = 1,
		},
		RG_TUNNELDRIVE = {
			MaxLevel = 5,
			TF_HIDING = 1,
		},
		AM_AXEMASTERY = 10,
		CR_TRUST = 10,
		CR_HOLYCROSS = {
			MaxLevel = 10,
			CR_TRUST = 7,
		},
		MO_IRONHAND = {
			MaxLevel = 10,
			AL_DEMONBANE = 10,
			AL_DP = 10,
		},
		MO_CALLSPIRITS = {
			MaxLevel = 5,
			MO_IRONHAND = 2,
		},
		MO_ABSORBSPIRITS = {
			MaxLevel = 1,
			MO_CALLSPIRITS = 5,
		},
		HW_MAGICCRASHER = {
			MaxLevel = 1,
			MG_SRECOVERY = 1,
		},
		ALL_BUYING_STORE = {
			MaxLevel = 1,
			MC_VENDING = 1,
		},
	},
},
Expanded_Super_Baby = {
	Inherit = { "Expanded_Super_Novice" },
},
Kagerou = {
	Inherit = { "Ninja" },

	Skills = {
		KO_YAMIKUMO = {
			MaxLevel = 1,
			NJ_KIRIKAGE = 5,
		},
		KO_RIGHT = 5,
		KO_LEFT = 5,
		KO_JYUMONJIKIRI = {
			MaxLevel = 5,
			KO_YAMIKUMO = 1,
		},
		KO_SETSUDAN = {
			MaxLevel = 5,
			KO_JYUMONJIKIRI = 2,
		},
		KO_BAKURETSU = {
			MaxLevel = 5,
			NJ_KUNAI = 5,
		},
		KO_HAPPOKUNAI = {
			MaxLevel = 5,
			KO_BAKURETSU = 1,
		},
		KO_MUCHANAGE = {
			MaxLevel = 10,
			KO_MAKIBISHI = 3,
		},
		KO_HUUMARANKA = {
			MaxLevel = 5,
			NJ_HUUMA = 5,
		},
		KO_MAKIBISHI = {
			MaxLevel = 5,
			NJ_ZENYNAGE = 1,
		},
		KO_MEIKYOUSISUI = {
			MaxLevel = 5,
			NJ_NINPOU = 10,
		},
		KO_ZANZOU = {
			MaxLevel = 5,
			NJ_UTSUSEMI = 1,
		},
		KO_KYOUGAKU = {
			MaxLevel = 5,
			KO_GENWAKU = 2,
		},
		KO_JYUSATSU = {
			MaxLevel = 5,
			KO_KYOUGAKU = 3,
		},
		KO_KAHU_ENTEN = 1,
		KO_HYOUHU_HUBUKI = 1,
		KO_KAZEHU_SEIRAN = 1,
		KO_DOHU_KOUKAI = 1,
		KO_KAIHOU = {
			MaxLevel = 1,
			KO_KAHU_ENTEN = 1,
			KO_HYOUHU_HUBUKI = 1,
			KO_KAZEHU_SEIRAN = 1,
			KO_DOHU_KOUKAI = 1,
		},
		KO_ZENKAI = {
			MaxLevel = 1,
			KO_KAIHOU = 1,
			KO_IZAYOI = 1,
		},
		KO_GENWAKU = {
			MaxLevel = 5,
			NJ_UTSUSEMI = 1,
		},
		KO_IZAYOI = {
			MaxLevel = 5,
			NJ_NINPOU = 5,
		},
		KG_KAGEHUMI = {
			MaxLevel = 5,
			KO_ZANZOU = 1,
		},
		KG_KYOMU = {
			MaxLevel = 5,
			KG_KAGEHUMI = 2,
		},
		KG_KAGEMUSYA = {
			MaxLevel = 5,
			KG_KYOMU = 3,
		},
	},
},
Oboro = {
	Inherit = { "Ninja" },

	Skills = {
		KO_YAMIKUMO = {
			MaxLevel = 1,
			NJ_KIRIKAGE = 5,
		},
		KO_RIGHT = 5,
		KO_LEFT = 5,
		KO_JYUMONJIKIRI = {
			MaxLevel = 5,
			KO_YAMIKUMO = 1,
		},
		KO_SETSUDAN = {
			MaxLevel = 5,
			KO_JYUMONJIKIRI = 2,
		},
		KO_BAKURETSU = {
			MaxLevel = 5,
			NJ_KUNAI = 5,
		},
		KO_HAPPOKUNAI = {
			MaxLevel = 5,
			KO_BAKURETSU = 1,
		},
		KO_MUCHANAGE = {
			MaxLevel = 10,
			KO_MAKIBISHI = 3,
		},
		KO_HUUMARANKA = {
			MaxLevel = 5,
			NJ_HUUMA = 5,
		},
		KO_MAKIBISHI = {
			MaxLevel = 5,
			NJ_ZENYNAGE = 1,
		},
		KO_MEIKYOUSISUI = {
			MaxLevel = 5,
			NJ_NINPOU = 10,
		},
		KO_ZANZOU = {
			MaxLevel = 5,
			NJ_UTSUSEMI = 1,
		},
		KO_KYOUGAKU = {
			MaxLevel = 5,
			KO_GENWAKU = 2,
		},
		KO_JYUSATSU = {
			MaxLevel = 5,
			KO_KYOUGAKU = 3,
		},
		KO_KAHU_ENTEN = 1,
		KO_HYOUHU_HUBUKI = 1,
		KO_KAZEHU_SEIRAN = 1,
		KO_DOHU_KOUKAI = 1,
		KO_KAIHOU = {
			MaxLevel = 1,
			KO_KAHU_ENTEN = 1,
			KO_HYOUHU_HUBUKI = 1,
			KO_KAZEHU_SEIRAN = 1,
			KO_DOHU_KOUKAI = 1,
		},
		KO_ZENKAI = {
			MaxLevel = 1,
			KO_KAIHOU = 1,
			KO_IZAYOI = 1,
		},
		KO_GENWAKU = {
			MaxLevel = 5,
			NJ_UTSUSEMI = 1,
		},
		KO_IZAYOI = {
			MaxLevel = 5,
			NJ_NINPOU = 5,
		},
		OB_ZANGETSU = {
			MaxLevel = 5,
			KO_GENWAKU = 1,
		},
		OB_OBOROGENSOU = {
			MaxLevel = 5,
			OB_AKAITSUKI = 3,
		},
		OB_AKAITSUKI = {
			MaxLevel = 5,
			OB_ZANGETSU = 2,
		},
	},
},
Rebellion = {
	Inherit = { "Gunslinger" },

	Skills = {
		RL_RICHS_COIN = {
			MaxLevel = 1,
			GS_GLITTERING = 5,
		},
		RL_MASS_SPIRAL = {
			MaxLevel = 5,
			GS_PIERCINGSHOT = 1,
		},
		RL_BANISHING_BUSTER = {
			MaxLevel = 5,
			RL_S_STORM = 1,
		},
		RL_B_TRAP = 5,
		RL_FLICKER = {
			MaxLevel = 1,
			GS_FLING = 1,
		},
		RL_S_STORM = {
			MaxLevel = 5,
			GS_DISARM = 1,
			GS_DUST = 1,
		},
		RL_E_CHAIN = {
			MaxLevel = 10,
			GS_CHAINACTION = 10,
		},
		RL_QD_SHOT = {
			MaxLevel = 1,
			RL_E_CHAIN = 1,
		},
		RL_C_MARKER = {
			MaxLevel = 1,
			GS_INCREASING = 1,
		},
		RL_FIREDANCE = {
			MaxLevel = 5,
			RL_FALLEN_ANGEL = 1,
		},
		RL_H_MINE = {
			MaxLevel = 5,
			GS_SPREADATTACK = 1,
		},
		RL_P_ALTER = 5,
		RL_FALLEN_ANGEL = {
			MaxLevel = 5,
			GS_DESPERADO = 10,
		},
		RL_R_TRIP = {
			MaxLevel = 5,
			RL_FIRE_RAIN = 1,
		},
		RL_D_TAIL = {
			MaxLevel = 5,
			RL_H_MINE = 3,
			RL_C_MARKER = 1,
		},
		RL_FIRE_RAIN = {
			MaxLevel = 5,
			GS_GATLINGFEVER = 1,
		},
		RL_HEAT_BARREL = {
			MaxLevel = 5,
			RL_FIREDANCE = 2,
		},
		RL_AM_BLAST = {
			MaxLevel = 5,
			RL_MASS_SPIRAL = 1,
		},
		RL_SLUGSHOT = {
			MaxLevel = 5,
			RL_BANISHING_BUSTER = 3,
		},
		RL_HAMMER_OF_GOD = {
			MaxLevel = 5,
			RL_AM_BLAST = 3,
		},
	},
},

Summoner = {
	Skills = {
		SU_BASIC_SKILL = 1,
		SU_BITE = {
			MaxLevel = 1,
			SU_BASIC_SKILL = 1,
		},
		SU_HIDE = {
			MaxLevel = 1,
			SU_BITE = 1,
		},
		SU_SCRATCH = {
			MaxLevel = 3,
			SU_HIDE = 1,
		},
		SU_STOOP = {
			MaxLevel = 1,
			SU_SCRATCH = 3,
		},
		SU_LOPE = {
			MaxLevel = 3,
			SU_STOOP = 1,
		},
		SU_SPRITEMABLE = {
			MaxLevel = 1,
			SU_LOPE = 3,
		},
		SU_POWEROFLAND = {
			MaxLevel = 1,
			SU_CN_POWDERING = 3,
		},
		SU_SV_STEMSPEAR = {
			MaxLevel = 5,
			SU_SPRITEMABLE = 1,
		},
		SU_CN_POWDERING = {
			MaxLevel = 5,
			SU_CN_METEOR = 3,
		},
		SU_CN_METEOR = {
			MaxLevel = 5,
			SU_SV_ROOTTWIST = 3,
		},
		SU_SV_ROOTTWIST = {
			MaxLevel = 5,
			SU_SV_STEMSPEAR = 3,
		},
		SU_POWEROFLIFE = {
			MaxLevel = 1,
			SU_LUNATICCARROTBEAT = 3,
		},
		SU_SCAROFTAROU = {
			MaxLevel = 5,
			SU_SV_ROOTTWIST = 3,
		},
		SU_PICKYPECK = {
			MaxLevel = 5,
			SU_SPRITEMABLE = 1,
		},
		SU_ARCLOUSEDASH = {
			MaxLevel = 5,
			SU_PICKYPECK = 3,
		},
		SU_LUNATICCARROTBEAT = {
			MaxLevel = 5,
			SU_SCAROFTAROU = 3,
		},
		SU_POWEROFSEA = {
			MaxLevel = 1,
			SU_TUNAPARTY = 3,
		},
		SU_TUNABELLY = {
			MaxLevel = 5,
			SU_BUNCHOFSHRIMP = 3,
		},
		SU_TUNAPARTY = {
			MaxLevel = 5,
			SU_TUNABELLY = 3,
		},
		SU_BUNCHOFSHRIMP = {
			MaxLevel = 5,
			SU_FRESHSHRIMP = 3,
		},
		SU_FRESHSHRIMP = {
			MaxLevel = 5,
			SU_SPRITEMABLE = 1,
		},
	},
},
