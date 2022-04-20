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
-- This library is free software; you can redistribute it and/or modify
-- it under the terms of the GNU General Public License as published by
-- the Free Software Foundation, either version 3 of the License, or
-- (at your option) any later version.
--
-- This library is distributed in the hope that it will be useful
-- but WITHOUT ANY WARRANTY; without even the implied warranty of
-- MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
-- GNU General Public License for more details.
--
-- You should have received a copy of the GNU General Public License,
-- along with this library.  If not, see <http =--www.gnu.org/licenses/>.
---------------------------------------------------------------------------
--- Status Change Database.
---------------------------------------------------------------------------

local status_effect_db = {
--[[*************************************************************************
 ************* Entry structure ********************************************
 **************************************************************************
SC_TYPE = {
	// ================ Optional fields ===============================
	Visible =           (bool) SC can be visible for all players
	Behavior = {
		StatusEffectBehavior.NoDeathReset      (bool) SC cannot be removed by death.
		StatusEffectBehavior.NoSave            (bool) SC cannot be saved.
		StatusEffectBehavior.CantDispell       (bool) SC cannot be reset by dispell.
		StatusEffectBehavior.CantClearance     (bool) SC cannot be reset by clearance.
		StatusEffectBehavior.IsBuff            (bool) SC considered as buff and be removed by Hermode and etc.
		StatusEffectBehavior.IsDebuff          (bool) SC considered as debuff and be removed by Gospel and etc.
		StatusEffectBehavior.NoMadoReset       (bool) SC cannot be reset when MADO Gear is taken off.
		StatusEffectBehavior.NoAllReset        (bool) SC cannot be reset by 'sc_end SC_ALL' and status change clear.
		StatusEffectBehavior.NoBoss            (bool) SC cannot be applied to boss monsters.
	},
	Icon =              (string, defaults to SI_BLANK) The status icon attached to the SC
},
*************************************************************************--]]
SC_PROVOKE = {
	Id = 0,
	Behavior = {
		StatusEffectBehavior.IsDebuff,
		StatusEffectBehavior.NoBoss,
	},
	Icon = "SI_PROVOKE"
},
SC_ENDURE = {
	Id = 1,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_ENDURE"
},
SC_HIDING = {
	Id = 4,
	Behavior = {
		StatusEffectBehavior.CantDispell,
	},
	Icon = "SI_HIDING"
},
SC_CLOAKING = {
	Id = 5,
	Behavior = {
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantDispell,
	},
	Icon = "SI_CLOAKING"
},
SC_TWOHANDQUICKEN = {
	Id = 2,
	Behavior = {
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_TWOHANDQUICKEN"
},
SC_CONCENTRATION = {
	Id = 3,
	Behavior = {
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_CONCENTRATION"
},
SC_ENCHANTPOISON = {
	Id = 6,
	Behavior = {
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_ENCHANTPOISON"
},
SC_POISONREACT = {
	Id = 7,
	Behavior = {
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_POISONREACT"
},
SC_QUAGMIRE = {
	Id = 8,
	Behavior = {
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsDebuff,
	},
	Icon = "SI_QUAGMIRE"
},
SC_ANGELUS = {
	Id = 9,
	Behavior = {
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_ANGELUS"
},
SC_BLESSING = {
	Id = 10,
	Behavior = {
		StatusEffectBehavior.IsBuff,
		StatusEffectBehavior.NoMadoReset,
		StatusEffectBehavior.NoBoss,
	},
	Icon = "SI_BLESSING"
},
SC_INC_AGI = {
	Id = 12,
	Behavior = {
		StatusEffectBehavior.IsBuff,
		StatusEffectBehavior.NoMadoReset,
	},
	Icon = "SI_INC_AGI"
},
SC_DEC_AGI = {
	Id = 13,
	Behavior = {
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.IsDebuff,
		StatusEffectBehavior.NoBoss,
	},
	Icon = "SI_DEC_AGI"
},
SC_SLOWPOISON = {
	Id = 14,
	Behavior = {
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_SLOWPOISON"
},
SC_IMPOSITIO = {
	Id = 15,
	Behavior = {
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_IMPOSITIO"
},
SC_SUFFRAGIUM = {
	Id = 16,
	Behavior = {
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_SUFFRAGIUM"
},
SC_ASPERSIO = {
	Id = 17,
	Behavior = {
		StatusEffectBehavior.IsBuff,
		StatusEffectBehavior.NoMadoReset,
	},
	Icon = "SI_ASPERSIO"
},
SC_BENEDICTIO = {
	Id = 18,
	Behavior = {
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_BENEDICTIO"
},
SC_KYRIE = {
	Id = 19,
	Behavior = {
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_KYRIE"
},
SC_MAGNIFICAT = {
	Id = 20,
	Behavior = {
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_MAGNIFICAT"
},
SC_GLORIA = {
	Id = 21,
	Behavior = {
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_GLORIA"
},
SC_LEXAETERNA = {
	Id = 22,
	Behavior = {
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_LEXAETERNA"
},
SC_ADRENALINE = {
	Id = 23,
	Behavior = {
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_ADRENALINE"
},
SC_WEAPONPERFECT = {
	Id = 24,
	Behavior = {
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_WEAPONPERFECT"
},
SC_OVERTHRUST = {
	Id = 25,
	Behavior = {
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_OVERTHRUST"
},
SC_TRICKDEAD = {
	Id = 29,
	Behavior = {
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_TRICKDEAD"
},
SC_SHOUT = {
	Id = 30,
	Behavior = {
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_SHOUT"
},
SC_ENERGYCOAT = {
	Id = 31,
	Behavior = {
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_ENERGYCOAT"
},
SC_ATTHASTE_POTION1 = {
	Id = 37,
	Behavior = {
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_ATTHASTE_POTION1"
},
SC_ATTHASTE_POTION2 = {
	Id = 38,
	Behavior = {
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_ATTHASTE_POTION2"
},
SC_ATTHASTE_POTION3 = {
	Id = 39,
	Behavior = {
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_ATTHASTE_POTION3"
},
SC_MOVHASTE_POTION = {
	Id = 41,
	Behavior = {
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_MOVHASTE_POTION"
},
SC_BARRIER = {
	Id = 49,
	Behavior = {
		StatusEffectBehavior.IsBuff,
	},
},
SC_NOEQUIPWEAPON = {
	Id = 50,
	Behavior = {
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_NOEQUIPWEAPON"
},
SC_NOEQUIPSHIELD = {
	Id = 51,
	Behavior = {
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_NOEQUIPSHIELD"
},
SC_NOEQUIPARMOR = {
	Id = 52,
	Behavior = {
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_NOEQUIPARMOR"
},
SC_NOEQUIPHELM = {
	Id = 53,
	Behavior = {
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_NOEQUIPHELM"
},
SC_PROTECTWEAPON = {
	Id = 54,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_PROTECTWEAPON"
},
SC_PROTECTSHIELD = {
	Id = 55,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_PROTECTSHIELD"
},
SC_PROTECTARMOR = {
	Id = 56,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_PROTECTARMOR"
},
SC_PROTECTHELM = {
	Id = 57,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_PROTECTHELM"
},
SC_AUTOGUARD = {
	Id = 58,
	Behavior = {
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_AUTOGUARD"
},
SC_REFLECTSHIELD = {
	Id = 59,
	Behavior = {
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_REFLECTSHIELD"
},
SC_DEVOTION = {
	Id = 60,
	Behavior = {
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.IsBuff,
	},
},
SC_PROVIDENCE = {
	Id = 61,
	Behavior = {
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_PROVIDENCE"
},
SC_DEFENDER = {
	Id = 62,
	Behavior = {
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_DEFENDER"
},
SC_MAGICROD = {
	Id = 63,
	Behavior = {
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
},
SC_AUTOSPELL = {
	Id = 65,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_AUTOSPELL"
},
SC_SPEARQUICKEN = {
	Id = 68,
	Behavior = {
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_SPEARQUICKEN"
},
SC_BLADESTOP = {
	Id = 85,
	Behavior = {
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
},
SC_EXPLOSIONSPIRITS = {
	Id = 86,
	Behavior = {
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_EXPLOSIONSPIRITS"
},
SC_STEELBODY = {
	Id = 87,
	Behavior = {
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_STEELBODY"
},
SC_PROPERTYFIRE = {
	Id = 90,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_PROPERTYFIRE"
},
SC_PROPERTYWATER = {
	Id = 91,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_PROPERTYWATER"
},
SC_PROPERTYWIND = {
	Id = 92,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_PROPERTYWIND"
},
SC_PROPERTYGROUND = {
	Id = 93,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_PROPERTYGROUND"
},
SC_STOP = {
	Id = 95,
	Behavior = {
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_STOP"
},
SC_PROPERTYUNDEAD = {
	Id = 97,
	Behavior = {
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_PROPERTYUNDEAD"
},
SC_AURABLADE = {
	Id = 103,
	Behavior = {
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_AURABLADE"
},
SC_PARRYING = {
	Id = 104,
	Behavior = {
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_PARRYING"
},
SC_LKCONCENTRATION = {
	Id = 105,
	Behavior = {
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_LKCONCENTRATION"
},
SC_TENSIONRELAX = {
	Id = 106,
	Behavior = {
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_TENSIONRELAX"
},
SC_BERSERK = {
	Id = 107,
	Behavior = {
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_BERSERK"
},
SC_SACRIFICE = {
	Id = 108,
	Behavior = {
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
},
SC_GOSPEL = {
	Id = 109,
	Behavior = {
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.IsDebuff,
	},
},
SC_ASSUMPTIO = {
	Id = 110,
	Behavior = {
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_ASSUMPTIO"
},
SC_BASILICA = {
	Id = 111,
	Behavior = {
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
},
SC_MAGICPOWER = {
	Id = 113,
	Behavior = {
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_MAGICPOWER"
},
SC_EDP = {
	Id = 114,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_EDP"
},
SC_TRUESIGHT = {
	Id = 115,
	Behavior = {
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_TRUESIGHT"
},
SC_WINDWALK = {
	Id = 116,
	Behavior = {
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_WINDWALK"
},
SC_MELTDOWN = {
	Id = 117,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_MELTDOWN"
},
SC_CARTBOOST = {
	Id = 118,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_CARTBOOST"
},
SC_BLOODING = {
	Id = 124,
	Behavior = {
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_BLOODING"
},
SC_JOINTBEAT = {
	Id = 125,
	Behavior = {
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsDebuff,
	},
	Icon = "SI_JOINTBEAT"
},
SC_MINDBREAKER = {
	Id = 126,
	Behavior = {
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.IsBuff,
	},
},
SC_MEMORIZE = {
	Id = 127,
	Behavior = {
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.IsBuff,
	},
},
SC_FOGWALL = {
	Id = 128,
	Behavior = {
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
		StatusEffectBehavior.NoBoss,
	},
},
SC_SPIDERWEB = {
	Id = 129,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsDebuff,
	},
},
SC_SUB_WEAPONPROPERTY = {
	Id = 131,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.IsBuff,
	},
},
SC_RUN = {
	Id = 133,
	Behavior = {
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_RUN"
},
SC_STRUP = {
	Id = 145,
	Behavior = {
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_STRUP"
},
SC_PROPERTYDARK = {
	Id = 146,
	Behavior = {
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_PROPERTYDARK"
},
SC_ADRENALINE2 = {
	Id = 147,
	Behavior = {
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_ADRENALINE2"
},
SC_PROPERTYTELEKINESIS = {
	Id = 148,
	Behavior = {
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_PROPERTYTELEKINESIS"
},
SC_SOULLINK = {
	Id = 149,
	Behavior = {
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_SOULLINK"
},
SC_PLUSATTACKPOWER = {
	Id = 150,
	Behavior = {
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
		StatusEffectBehavior.NoMadoReset,
	},
	Icon = "SI_PLUSATTACKPOWER"
},
SC_PLUSMAGICPOWER = {
	Id = 151,
	Behavior = {
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
		StatusEffectBehavior.NoMadoReset,
	},
	Icon = "SI_PLUSMAGICPOWER"
},
SC_KAITE = {
	Id = 153,
	Behavior = {
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_KAITE"
},
SC_KAAHI = {
	Id = 157,
	Behavior = {
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_KAAHI"
},
SC_KAUPE = {
	Id = 158,
	Behavior = {
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_KAUPE"
},
SC_ONEHANDQUICKEN = {
	Id = 161,
	Behavior = {
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_ONEHANDQUICKEN"
},
SC_PRESERVE = {
	Id = 181,
	Behavior = {
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_PRESERVE"
},
SC_CHASEWALK = {
	Id = 119,
	Behavior = {
		StatusEffectBehavior.CantDispell,
	},
},
SC_CHASEWALK2 = {
	Id = 182,
	Behavior = {
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_INCSTR"
},
SC_MOVESLOW_POTION = {
	Id = 185,
	Behavior = {
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_MOVESLOW_POTION"
},
SC_DOUBLECASTING = {
	Id = 186,
	Behavior = {
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_DOUBLECASTING"
},
SC_GRAVITATION = {
	Id = 187,
	Behavior = {
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
		StatusEffectBehavior.NoBoss,
	},
},
SC_OVERTHRUSTMAX = {
	Id = 188,
	Behavior = {
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_OVERTHRUSTMAX"
},
SC_TAROTCARD = {
	Id = 191,
	Behavior = {
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsDebuff,
	},
	Icon = "SI_TAROTCARD"
},
SC_CR_SHRINK = {
	Id = 197,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_CR_SHRINK"
},
SC_WZ_SIGHTBLASTER = {
	Id = 198,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_WZ_SIGHTBLASTER"
},
SC_RG_CCONFINE_M = {
	Id = 200,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_RG_CCONFINE_M"
},
SC_RG_CCONFINE_S = {
	Id = 201,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_RG_CCONFINE_S"
},
SC_NJ_UTSUSEMI = {
	Id = 206,
	Behavior = {
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_NJ_UTSUSEMI"
},
SC_NJ_BUNSINJYUTSU = {
	Id = 207,
	Behavior = {
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_NJ_BUNSINJYUTSU"
},
SC_NJ_SUITON = {
	Id = 211,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsDebuff,
		StatusEffectBehavior.NoBoss,
	},
	Icon = "SI_NJ_SUITON"
},
SC_FOOD_STR = {
	Id = 241,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
		StatusEffectBehavior.NoMadoReset,
	},
	Icon = "SI_FOOD_STR"
},
SC_FOOD_AGI = {
	Id = 242,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
		StatusEffectBehavior.NoMadoReset,
	},
	Icon = "SI_FOOD_AGI"
},
SC_FOOD_VIT = {
	Id = 243,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
		StatusEffectBehavior.NoMadoReset,
	},
	Icon = "SI_FOOD_VIT"
},
SC_FOOD_DEX = {
	Id = 244,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
		StatusEffectBehavior.NoMadoReset,
	},
	Icon = "SI_FOOD_DEX"
},
SC_FOOD_INT = {
	Id = 245,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
		StatusEffectBehavior.NoMadoReset,
	},
	Icon = "SI_FOOD_INT"
},
SC_FOOD_LUK = {
	Id = 246,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
		StatusEffectBehavior.NoMadoReset,
	},
	Icon = "SI_FOOD_LUK"
},
SC_FOOD_BASICAVOIDANCE = {
	Id = 247,
	Behavior = {
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
		StatusEffectBehavior.NoMadoReset,
	},
	Icon = "SI_FOOD_BASICAVOIDANCE"
},
SC_FOOD_BASICHIT = {
	Id = 248,
	Behavior = {
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
		StatusEffectBehavior.NoMadoReset,
	},
	Icon = "SI_FOOD_BASICHIT"
},
SC_FOOD_CRITICALSUCCESSVALUE = {
	Id = 249,
	Behavior = {
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_FOOD_CRITICALSUCCESSVALUE"
},
SC_CASH_PLUSEXP = {
	Id = 250,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
		StatusEffectBehavior.NoMadoReset,
	},
	Icon = "SI_CASH_PLUSEXP"
},
SC_CASH_DEATHPENALTY = {
	Id = 251,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
		StatusEffectBehavior.NoMadoReset,
	},
	Icon = "SI_CASH_DEATHPENALTY"
},
SC_CASH_RECEIVEITEM = {
	Id = 252,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
		StatusEffectBehavior.NoMadoReset,
	},
	Icon = "SI_CASH_RECEIVEITEM"
},
SC_CASH_BOSS_ALARM = {
	Id = 253,
	Behavior = {
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
		StatusEffectBehavior.NoMadoReset,
	},
	Icon = "SI_CASH_BOSS_ALARM"
},
SC_FOOD_STR_CASH = {
	Id = 271,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
		StatusEffectBehavior.NoMadoReset,
	},
	Icon = "SI_FOOD_STR_CASH"
},
SC_FOOD_AGI_CASH = {
	Id = 272,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
		StatusEffectBehavior.NoMadoReset,
	},
	Icon = "SI_FOOD_AGI_CASH"
},
SC_FOOD_VIT_CASH = {
	Id = 273,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
		StatusEffectBehavior.NoMadoReset,
	},
	Icon = "SI_FOOD_VIT_CASH"
},
SC_FOOD_DEX_CASH = {
	Id = 274,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
		StatusEffectBehavior.NoMadoReset,
	},
	Icon = "SI_FOOD_DEX_CASH"
},
SC_FOOD_INT_CASH = {
	Id = 275,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
		StatusEffectBehavior.NoMadoReset,
	},
	Icon = "SI_FOOD_INT_CASH"
},
SC_FOOD_LUK_CASH = {
	Id = 276,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
		StatusEffectBehavior.NoMadoReset,
	},
	Icon = "SI_FOOD_LUK_CASH"
},
SC_SAVAGE_STEAK = {
	Id = 491,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.NoMadoReset,
	},
	Icon = "SI_SAVAGE_STEAK"
},
SC_COCKTAIL_WARG_BLOOD = {
	Id = 492,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.NoMadoReset,
	},
	Icon = "SI_COCKTAIL_WARG_BLOOD"
},
SC_MINOR_BBQ = {
	Id = 493,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.NoMadoReset,
	},
	Icon = "SI_MINOR_BBQ"
},
SC_SIROMA_ICE_TEA = {
	Id = 494,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.NoMadoReset,
	},
	Icon = "SI_SIROMA_ICE_TEA"
},
SC_DROCERA_HERB_STEAMED = {
	Id = 495,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.NoMadoReset,
	},
	Icon = "SI_DROCERA_HERB_STEAMED"
},
SC_PUTTI_TAILS_NOODLES = {
	Id = 496,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.NoMadoReset,
	},
	Icon = "SI_PUTTI_TAILS_NOODLES"
},
SC_MELON_BOMB = {
	Id = 478,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
	},
	Icon = "SI_MELON_BOMB"
},
SC_BANANA_BOMB_SITDOWN_POSTDELAY = {
	Id = 479,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
	},
	Icon = "SI_BANANA_BOMB_SITDOWN_POSTDELAY"
},
SC_BANANA_BOMB = {
	Id = 497,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
	},
	Icon = "SI_BANANA_BOMB"
},
SC_PROMOTE_HEALTH_RESERCH = {
	Id = 480,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
	},
	Icon = "SI_PROMOTE_HEALTH_RESERCH"
},
SC_ENERGY_DRINK_RESERCH = {
	Id = 481,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
	},
	Icon = "SI_ENERGY_DRINK_RESERCH"
},
SC_EXTRACT_WHITE_POTION_Z = {
	Id = 482,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
	},
},
SC_VITATA_500 = {
	Id = 483,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
	},
},
SC_EXTRACT_SALAMINE_JUICE = {
	Id = 484,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
	},
},
SC_BOOST500 = {
	Id = 485,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
	},
},
SC_FULL_SWING_K = {
	Id = 486,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
	},
},
SC_MANA_PLUS = {
	Id = 487,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
	},
},
SC_MUSTLE_M = {
	Id = 488,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
	},
},
SC_LIFE_FORCE_F = {
	Id = 489,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
	},
},
SC_MER_FLEE = {
	Id = 277,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_MER_FLEE"
},
SC_MER_ATK = {
	Id = 278,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_MER_ATK"
},
SC_MER_HP = {
	Id = 279,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_MER_HP"
},
SC_MER_SP = {
	Id = 280,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_MER_SP"
},
SC_MER_HIT = {
	Id = 281,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_MER_HIT"
},
SC_SLOWCAST = {
	Id = 282,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_SLOWCAST"
},
SC_CRITICALWOUND = {
	Id = 286,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_CRITICALWOUND"
},
SC_MOVHASTE_HORSE = {
	Id = 289,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_MOVHASTE_HORSE"
},
SC_PROTECT_DEF = {
	Id = 290,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_PROTECT_DEF"
},
SC_PROTECT_MDEF = {
	Id = 291,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_PROTECT_MDEF"
},
SC_HEALPLUS = {
	Id = 292,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
		StatusEffectBehavior.NoMadoReset,
	},
	Icon = "SI_HEALPLUS"
},
SC_S_LIFEPOTION = {
	Id = 293,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
		StatusEffectBehavior.NoMadoReset,
	},
	Icon = "SI_S_LIFEPOTION"
},
SC_L_LIFEPOTION = {
	Id = 294,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
		StatusEffectBehavior.NoMadoReset,
	},
	Icon = "SI_L_LIFEPOTION"
},
SC_CRITICALPERCENT = {
	Id = 295,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
		StatusEffectBehavior.NoMadoReset,
	},
	Icon = "SI_CRITICALPERCENT"
},
SC_PLUSAVOIDVALUE = {
	Id = 296,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
		StatusEffectBehavior.NoMadoReset,
	},
	Icon = "SI_PLUSAVOIDVALUE"
},
SC_ATKER_ASPD = {
	Id = 297,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_ATKER_ASPD"
},
SC_TARGET_ASPD = {
	Id = 298,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
		StatusEffectBehavior.NoMadoReset,
	},
	Icon = "SI_TARGET_ASPD"
},
SC_ATKER_MOVESPEED = {
	Id = 299,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_ATKER_MOVESPEED"
},
SC_ATKER_BLOOD = {
	Id = 300,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_ATKER_BLOOD"
},
SC_TARGET_BLOOD = {
	Id = 301,
	Behavior = {
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_TARGET_BLOOD"
},
SC_ARMOR_PROPERTY = {
	Id = 302,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_ARMOR_PROPERTY"
},
SC_HELLPOWER = {
	Id = 304,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_HELLPOWER"
},
SC_STEAMPACK = {
	Id = 305,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsDebuff,
		StatusEffectBehavior.NoMadoReset,
	},
	Icon = "SI_STEAMPACK"
},
SC_CASH_PLUSONLYJOBEXP = {
	Id = 312,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
		StatusEffectBehavior.NoMadoReset,
	},
	Icon = "SI_CASH_PLUSONLYJOBEXP"
},
SC_PARTYFLEE = {
	Id = 313,
	Behavior = {
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_PARTYFLEE"
},
SC_ANGEL_PROTECT = {
	Id = 314,
	Behavior = {
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_ANGEL_PROTECT"
},
SC_ENCHANTBLADE = {
	Id = 316,
	Behavior = {
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_ENCHANTBLADE"
},
SC_DEATHBOUND = {
	Id = 317,
	Behavior = {
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_DEATHBOUND"
},
SC_REFRESH = {
	Id = 318,
	Behavior = {
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_REFRESH"
},
SC_GIANTGROWTH = {
	Id = 319,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_GIANTGROWTH"
},
SC_STONEHARDSKIN = {
	Id = 320,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_STONEHARDSKIN"
},
SC_VITALITYACTIVATION = {
	Id = 321,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_VITALITYACTIVATION"
},
SC_FIGHTINGSPIRIT = {
	Id = 322,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_FIGHTINGSPIRIT"
},
SC_ABUNDANCE = {
	Id = 323,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_ABUNDANCE"
},
SC_EPICLESIS = {
	Id = 329,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_EPICLESIS"
},
SC_ORATIO = {
	Id = 330,
	Visible = true,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_ORATIO"
},
SC_LAUDAAGNUS = {
	Id = 331,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_LAUDAAGNUS"
},
SC_LAUDARAMUS = {
	Id = 332,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_LAUDARAMUS"
},
SC_CLOAKINGEXCEED = {
	Id = 333,
	Behavior = {
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_CLOAKINGEXCEED"
},
SC_HALLUCINATIONWALK = {
	Id = 334,
	Visible = true,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_HALLUCINATIONWALK"
},
SC_HALLUCINATIONWALK_POSTDELAY = {
	Id = 335,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_HALLUCINATIONWALK_POSTDELAY"
},
SC_RENOVATIO = {
	Id = 336,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_RENOVATIO"
},
SC_WEAPONBLOCKING = {
	Id = 337,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_WEAPONBLOCKING"
},
SC_ROLLINGCUTTER = {
	Id = 339,
	Visible = true,
	Behavior = {
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_ROLLINGCUTTER"
},
SC_EXPIATIO = {
	Id = 340,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_EXPIATIO"
},
SC_POISONINGWEAPON = {
	Id = 341,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_POISONINGWEAPON"
},
SC_TOXIN = {
	Id = 342,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.IsBuff,
		StatusEffectBehavior.NoBoss,
	},
	Icon = "SI_TOXIN"
},
SC_PARALYSE = {
	Id = 343,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.IsBuff,
		StatusEffectBehavior.NoBoss,
	},
	Icon = "SI_PARALYSE"
},
SC_VENOMBLEED = {
	Id = 344,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.IsBuff,
		StatusEffectBehavior.NoBoss,
	},
	Icon = "SI_VENOMBLEED"
},
SC_MAGICMUSHROOM = {
	Id = 345,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.IsBuff,
		StatusEffectBehavior.NoBoss,
	},
	Icon = "SI_MAGICMUSHROOM"
},
SC_DEATHHURT = {
	Id = 346,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.IsBuff,
		StatusEffectBehavior.NoBoss,
	},
	Icon = "SI_DEATHHURT"
},
SC_PYREXIA = {
	Id = 347,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.IsBuff,
		StatusEffectBehavior.NoBoss,
	},
	Icon = "SI_PYREXIA"
},
SC_OBLIVIONCURSE = {
	Id = 348,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.IsBuff,
		StatusEffectBehavior.NoBoss,
	},
	Icon = "SI_OBLIVIONCURSE"
},
SC_LEECHESEND = {
	Id = 349,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.IsBuff,
		StatusEffectBehavior.NoBoss,
	},
	Icon = "SI_LEECHESEND"
},
SC_DUPLELIGHT = {
	Id = 350,
	Visible = true,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_DUPLELIGHT"
},
SC_FEARBREEZE = {
	Id = 352,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_FEARBREEZE"
},
SC_ELECTRICSHOCKER = {
	Id = 353,
	Behavior = {
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
		StatusEffectBehavior.NoBoss,
	},
	Icon = "SI_ELECTRICSHOCKER"
},
SC_MARSHOFABYSS = {
	Id = 354,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.IsBuff,
		StatusEffectBehavior.NoBoss,
	},
	Icon = "SI_MARSHOFABYSS"
},
SC_RECOGNIZEDSPELL = {
	Id = 355,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_RECOGNIZEDSPELL"
},
SC_WUGDASH = {
	Id = 358,
	Behavior = {
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_WUGDASH"
},
SC_WUGBITE = {
	Id = 359,
	Behavior = {
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
		StatusEffectBehavior.NoBoss,
	},
},
SC_CAMOUFLAGE = {
	Id = 360,
	Visible = true,
	Behavior = {
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_CAMOUFLAGE"
},
SC_ACCELERATION = {
	Id = 361,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_ACCELERATION"
},
SC_HOVERING = {
	Id = 362,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_HOVERING"
},
SC_SUMMON1 = {
	Id = 363,
	Visible = true,
	Behavior = {
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_SPHERE_1"
},
SC_SUMMON2 = {
	Id = 364,
	Visible = true,
	Behavior = {
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_SPHERE_2"
},
SC_SUMMON3 = {
	Id = 365,
	Visible = true,
	Behavior = {
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_SPHERE_3"
},
SC_SUMMON4 = {
	Id = 366,
	Visible = true,
	Behavior = {
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_SPHERE_4"
},
SC_SUMMON5 = {
	Id = 367,
	Visible = true,
	Behavior = {
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_SPHERE_5"
},
SC_MVPCARD_TAOGUNKA = {
	Id = 368,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
		StatusEffectBehavior.IsDebuff,
	},
	Icon = "SI_MVPCARD_TAOGUNKA"
},
SC_MVPCARD_MISTRESS = {
	Id = 369,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
		StatusEffectBehavior.IsDebuff,
	},
	Icon = "SI_MVPCARD_MISTRESS"
},
SC_MVPCARD_ORCHERO = {
	Id = 370,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
		StatusEffectBehavior.IsDebuff,
	},
	Icon = "SI_MVPCARD_ORCHERO"
},
SC_MVPCARD_ORCLORD = {
	Id = 371,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
		StatusEffectBehavior.IsDebuff,
	},
	Icon = "SI_MVPCARD_ORCLORD"
},
SC_OVERHEAT_LIMITPOINT = {
	Id = 372,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_OVERHEAT_LIMITPOINT"
},
SC_OVERHEAT = {
	Id = 373,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_OVERHEAT"
},
SC_SHAPESHIFT = {
	Id = 374,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_SHAPESHIFT"
},
SC_INFRAREDSCAN = {
	Id = 375,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_INFRAREDSCAN"
},
SC_MAGNETICFIELD = {
	Id = 376,
	Behavior = {
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
		StatusEffectBehavior.NoBoss,
	},
	Icon = "SI_MAGNETICFIELD"
},
SC_NEUTRALBARRIER = {
	Id = 377,
	Behavior = {
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_NEUTRALBARRIER"
},
SC_NEUTRALBARRIER_MASTER = {
	Id = 378,
	Behavior = {
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_NEUTRALBARRIER_MASTER"
},
SC_STEALTHFIELD_MASTER = {
	Id = 380,
	Behavior = {
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_STEALTHFIELD_MASTER"
},
SC_MANU_ATK = {
	Id = 381,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_MANU_ATK"
},
SC_MANU_DEF = {
	Id = 382,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_MANU_DEF"
},
SC_SPL_ATK = {
	Id = 383,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_SPL_ATK"
},
SC_SPL_DEF = {
	Id = 384,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_SPL_DEF"
},
SC_MANU_MATK = {
	Id = 386,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_MANU_MATK"
},
SC_SPL_MATK = {
	Id = 387,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_SPL_MATK"
},
SC_STR_SCROLL = {
	Id = 388,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
		StatusEffectBehavior.IsDebuff,
	},
	Icon = "SI_STR_SCROLL"
},
SC_INT_SCROLL = {
	Id = 389,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
		StatusEffectBehavior.IsDebuff,
	},
	Icon = "SI_INT_SCROLL"
},
SC_FORCEOFVANGUARD = {
	Id = 391,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_FORCEOFVANGUARD"
},
SC_BUCHEDENOEL = {
	Id = 392,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
		StatusEffectBehavior.IsDebuff,
	},
	Icon = "SI_BUCHEDENOEL"
},
SC_RAID = {
	Id = 395,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
},
SC_SHIELDSPELL_DEF = {
	Id = 396,
	Behavior = {
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_SHIELDSPELL_DEF"
},
SC_SHIELDSPELL_MDEF = {
	Id = 397,
	Behavior = {
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_SHIELDSPELL_MDEF"
},
SC_SHIELDSPELL_REF = {
	Id = 398,
	Behavior = {
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_SHIELDSPELL_REF"
},
SC_EXEEDBREAK = {
	Id = 400,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_EXEEDBREAK"
},
SC_ADORAMUS = {
	Id = 401,
	Behavior = {
		StatusEffectBehavior.IsBuff,
		StatusEffectBehavior.NoBoss,
	},
	Icon = "SI_ADORAMUS"
},
SC_PRESTIGE = {
	Id = 402,
	Behavior = {
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_PRESTIGE"
},
SC_BANDING = {
	Id = 405,
	Visible = true,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_BANDING"
},
SC_BANDING_DEFENCE = {
	Id = 505,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_BANDING_DEFENCE"
},
SC_EARTHDRIVE = {
	Id = 406,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_EARTHDRIVE"
},
SC_INSPIRATION = {
	Id = 407,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_INSPIRATION"
},
SC_RAISINGDRAGON = {
	Id = 410,
	Behavior = {
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_RAISINGDRAGON"
},
SC_LIGHTNINGWALK = {
	Id = 413,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_LIGHTNINGWALK"
},
SC_ACARAJE = {
	Id = 414,
	Behavior = {
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_ACARAJE"
},
SC_CURSEDCIRCLE_ATKER = {
	Id = 416,
	Visible = true,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_CURSEDCIRCLE_ATKER"
},
SC_CURSEDCIRCLE_TARGET = {
	Id = 417,
	Visible = true,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_CURSEDCIRCLE_TARGET"
},
SC_CRESCENTELBOW = {
	Id = 419,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_CRESCENTELBOW"
},
SC_SWING = {
	Id = 429,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_SWINGDANCE"
},
SC_SYMPHONY_LOVE = {
	Id = 430,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_SYMPHONYOFLOVERS"
},
SC_PROPERTYWALK = {
	Id = 431,
	Behavior = {
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_PROPERTYWALK"
},
SC_SPELLFIST = {
	Id = 432,
	Behavior = {
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_SPELLFIST"
},
SC_NETHERWORLD = {
	Id = 433,
	Behavior = {
		StatusEffectBehavior.IsBuff,
		StatusEffectBehavior.NoBoss,
	},
	Icon = "SI_NETHERWORLD"
},
SC_SIREN = {
	Id = 434,
	Behavior = {
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_SIREN"
},
SC_DEEP_SLEEP = {
	Id = 435,
	Visible = true,
	Behavior = {
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.IsDebuff,
		StatusEffectBehavior.NoBoss,
	},
	Icon = "SI_DEEPSLEEP"
},
SC_SIRCLEOFNATURE = {
	Id = 436,
	Behavior = {
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_SIRCLEOFNATURE"
},
SC_GLOOMYDAY = {
	Id = 438,
	Behavior = {
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_GLOOMYDAY"
},
SC_SONG_OF_MANA = {
	Id = 439,
	Behavior = {
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_SONG_OF_MANA"
},
SC_DANCE_WITH_WUG = {
	Id = 441,
	Behavior = {
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_DANCEWITHWUG"
},
SC_RUSH_WINDMILL = {
	Id = 442,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_RUSHWINDMILL"
},
SC_ECHOSONG = {
	Id = 443,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_ECHOSONG"
},
SC_HARMONIZE = {
	Id = 444,
	Behavior = {
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_HARMONIZE"
},
SC_MOONLIT_SERENADE = {
	Id = 447,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_MOONLITSERENADE"
},
SC_SATURDAY_NIGHT_FEVER = {
	Id = 448,
	Behavior = {
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_SATURDAYNIGHTFEVER"
},
SC_SITDOWN_FORCE = {
	Id = 449,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
},
SC_ANALYZE = {
	Id = 450,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_ANALYZE"
},
SC_LERADS_DEW = {
	Id = 451,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_LERADSDEW"
},
SC_MELODYOFSINK = {
	Id = 452,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_MELODYOFSINK"
},
SC_BEYOND_OF_WARCRY = {
	Id = 453,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_WARCRYOFBEYOND"
},
SC_UNLIMITED_HUMMING_VOICE = {
	Id = 454,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_UNLIMITEDHUMMINGVOICE"
},
SC_WARMER = {
	Id = 446,
	Behavior = {
		StatusEffectBehavior.NoSave,
	},
},
SC_VENOMIMPRESS = {
	Id = 328,
	Visible = true,
	Behavior = {
		StatusEffectBehavior.CantDispell,
	},
	Icon = "SI_VENOMIMPRESS"
},
SC_FROSTMISTY = {
	Id = 351,
	Visible = true,
	Behavior = {
		StatusEffectBehavior.IsDebuff,
		StatusEffectBehavior.NoBoss,
	},
	Icon = "SI_FROSTMISTY"
},
SC_STOMACHACHE = {
	Id = 476,
	Behavior = {
		StatusEffectBehavior.IsDebuff,
	},
	Icon = "SI_STOMACHACHE"
},
SC_MYSTERIOUS_POWDER = {
	Id = 477,
	Behavior = {
		StatusEffectBehavior.IsDebuff,
	},
	Icon = "SI_MYSTERIOUS_POWDER"
},
SC_WATER_BARRIER = {
	Id = 527,
	Behavior = {
		StatusEffectBehavior.NoSave,
	},
	Icon = "SI_WATER_BARRIER"
},
SC_ZEPHYR = {
	Id = 528,
	Behavior = {
		StatusEffectBehavior.NoSave,
	},
	Icon = "SI_ZEPHYR"
},
SC_POWER_OF_GAIA = {
	Id = 533,
	Behavior = {
		StatusEffectBehavior.NoSave,
	},
	Icon = "SI_POWER_OF_GAIA"
},
SC_FIRE_INSIGNIA = {
	Id = 567,
	Behavior = {
		StatusEffectBehavior.NoSave,
	},
	Icon = "SI_FIRE_INSIGNIA"
},
SC_WATER_INSIGNIA = {
	Id = 568,
	Behavior = {
		StatusEffectBehavior.NoSave,
	},
	Icon = "SI_WATER_INSIGNIA"
},
SC_WIND_INSIGNIA = {
	Id = 569,
	Behavior = {
		StatusEffectBehavior.NoSave,
	},
	Icon = "SI_WIND_INSIGNIA"
},
SC_EARTH_INSIGNIA = {
	Id = 570,
	Behavior = {
		StatusEffectBehavior.NoSave,
	},
	Icon = "SI_EARTH_INSIGNIA"
},
SC_MORA_BUFF = {
	Id = 573,
	Behavior = {
		StatusEffectBehavior.NoSave,
	},
	Icon = "SI_MORA_BUFF"
},
SC_NEEDLE_OF_PARALYZE = {
	Id = 576,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.NoBoss,
	},
	Icon = "SI_NEEDLE_OF_PARALYZE"
},
SC_PAIN_KILLER = {
	Id = 577,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
	},
	Icon = "SI_PAIN_KILLER"
},
SC_G_LIFEPOTION = {
	Id = 578,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.NoMadoReset,
	},
	Icon = "SI_G_LIFEPOTION"
},
SC_LIGHT_OF_REGENE = {
	Id = 580,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
	},
	Icon = "SI_LIGHT_OF_REGENE"
},
SC_MAGIC_CANDY = {
	Id = 611,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
		StatusEffectBehavior.NoMadoReset,
	},
	Icon = "SI_MAGIC_CANDY"
},
SC_MONSTER_TRANSFORM = {
	Id = 621,
	Visible = true,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
	},
	Icon = "SI_MONSTER_TRANSFORM"
},
SC_MTF_ASPD = {
	Id = 624,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
	},
},
SC_MTF_RANGEATK = {
	Id = 625,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
	},
},
SC_MTF_MATK = {
	Id = 626,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
	},
},
SC_MTF_MLEATKED = {
	Id = 627,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
	},
},
SC_MTF_CRIDAMAGE = {
	Id = 628,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
	},
},
SC_FULL_THROTTLE = {
	Id = 720,
	Behavior = {
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_FULL_THROTTLE"
},
SC_REBOUND = {
	Id = 721,
	Behavior = {
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_REBOUND"
},
SC_TELEKINESIS_INTENSE = {
	Id = 717,
	Behavior = {
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_TELEKINESIS_INTENSE"
},
SC_SKELSCROLL = {
	Id = 506,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.NoMadoReset,
	},
},
SC_DISTRUCTIONSCROLL = {
	Id = 507,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.NoMadoReset,
	},
},
SC_ROYALSCROLL = {
	Id = 508,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.NoMadoReset,
	},
},
SC_IMMUNITYSCROLL = {
	Id = 509,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.NoMadoReset,
	},
},
SC_MYSTICSCROLL = {
	Id = 510,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.NoMadoReset,
	},
},
SC_BATTLESCROLL = {
	Id = 511,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.NoMadoReset,
	},
},
SC_ARMORSCROLL = {
	Id = 512,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.NoMadoReset,
	},
},
SC_FREYJASCROLL = {
	Id = 513,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.NoMadoReset,
	},
},
SC_SOULSCROLL = {
	Id = 514,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.NoMadoReset,
	},
},
SC_QUEST_BUFF1 = {
	Id = 705,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
	},
	Icon = "SI_QUEST_BUFF1"
},
SC_QUEST_BUFF2 = {
	Id = 706,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
	},
	Icon = "SI_QUEST_BUFF2"
},
SC_QUEST_BUFF3 = {
	Id = 707,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
	},
	Icon = "SI_QUEST_BUFF3"
},
SC_GEFFEN_MAGIC1 = {
	Id = 702,
	Behavior = {
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
	},
	Icon = "SI_GEFFEN_MAGIC1"
},
SC_GEFFEN_MAGIC2 = {
	Id = 703,
	Behavior = {
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
	},
	Icon = "SI_GEFFEN_MAGIC2"
},
SC_GEFFEN_MAGIC3 = {
	Id = 704,
	Behavior = {
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
	},
	Icon = "SI_GEFFEN_MAGIC3"
},
SC_OVERLAPEXPUP = {
	Id = 618,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
	},
	Icon = "SI_OVERLAPEXPUP"
},
SC_M_LIFEPOTION = {
	Id = 670,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.NoMadoReset,
	},
	Icon = "SI_M_LIFEPOTION"
},
SC_GDSKILL_REGENERATION = {
	Id = 174,
	Behavior = {
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.NoMadoReset,
	},
},
SC_WEIGHTOVER50 = {
	Id = 35,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.NoMadoReset,
		StatusEffectBehavior.NoAllReset,
	},
	Icon = "SI_WEIGHTOVER50"
},
SC_WEIGHTOVER90 = {
	Id = 36,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.NoMadoReset,
		StatusEffectBehavior.NoAllReset,
	},
	Icon = "SI_WEIGHTOVER90"
},
SC_EARTHSCROLL = {
	Id = 205,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.NoMadoReset,
	},
	Icon = "SI_EARTHSCROLL"
},
SC_STORMKICK_READY = {
	Id = 136,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.NoMadoReset,
	},
	Icon = "SI_STORMKICK_ON"
},
SC_DOWNKICK_READY = {
	Id = 138,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.NoMadoReset,
	},
	Icon = "SI_DOWNKICK_ON"
},
SC_TURNKICK_READY = {
	Id = 140,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.NoMadoReset,
	},
	Icon = "SI_TURNKICK_ON"
},
SC_DODGE_READY = {
	Id = 144,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.NoMadoReset,
	},
	Icon = "SI_DODGE_ON"
},
SC_WHISTLE = {
	Id = 70,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.NoMadoReset,
	},
},
SC_POEMBRAGI = {
	Id = 72,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.NoMadoReset,
	},
},
SC_APPLEIDUN = {
	Id = 73,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.NoMadoReset,
	},
},
SC_HUMMING = {
	Id = 74,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.NoMadoReset,
	},
},
SC_DONTFORGETME = {
	Id = 75,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.NoMadoReset,
	},
},
SC_SERVICEFORYOU = {
	Id = 77,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.NoMadoReset,
	},
},
SC_COLD = {
	Id = 437,
	Visible = true,
	Behavior = {
		StatusEffectBehavior.NoBoss,
	},
	Icon = "SI_COLD"
},
SC_BLOOD_SUCKER = {
	Id = 464,
	Visible = true,
	Behavior = {
	},
	Icon = "SI_BLOODSUCKER"
},
SC_MOONSTAR = {
	Id = 718,
	Visible = true,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.NoMadoReset,
		StatusEffectBehavior.NoAllReset,
	},
	Icon = "SI_MOONSTAR"
},
SC_SUPER_STAR = {
	Id = 728,
	Visible = true,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.NoMadoReset,
		StatusEffectBehavior.NoAllReset,
	},
	Icon = "SI_SUPER_STAR"
},
SC_STRANGELIGHTS = {
	Id = 719,
	Visible = true,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.NoMadoReset,
		StatusEffectBehavior.NoAllReset,
	},
	Icon = "SI_STRANGELIGHTS"
},
SC_DECORATION_OF_MUSIC = {
	Id = 779,
	Visible = true,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.NoMadoReset,
		StatusEffectBehavior.NoAllReset,
	},
	Icon = "SI_DECORATION_OF_MUSIC"
},
SC_LJOSALFAR = {
	Id = 826,
	Visible = true,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.NoMadoReset,
		StatusEffectBehavior.NoAllReset,
	},
	Icon = "SI_LJOSALFAR"
},
SC_MERMAID_LONGING = {
	Id = 863,
	Visible = true,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.NoMadoReset,
		StatusEffectBehavior.NoAllReset,
	},
	Icon = "SI_MERMAID_LONGING"
},
SC_HAT_EFFECT = {
	Id = 674,
	Visible = true,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.NoMadoReset,
		StatusEffectBehavior.NoAllReset,
	},
	Icon = "SI_HAT_EFFECT"
},
SC_TIME_ACCESSORY = {
	Id = 872,
	Visible = true,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.NoMadoReset,
		StatusEffectBehavior.NoAllReset,
	},
	Icon = "SI_TIME_ACCESSORY"
},
SC_SPRITEMABLE = {
	Id = 937,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.NoMadoReset,
		StatusEffectBehavior.NoAllReset,
	},
	Icon = "SI_SPRITEMABLE"
},
SC_BITESCAR = {
	Id = 917,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.NoBoss,
	},
	Icon = "SI_BITESCAR"
},
SC_CLAN_INFO = {
	Id = 696,
	Visible = true,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.NoMadoReset,
		StatusEffectBehavior.NoAllReset,
	},
	Icon = "SI_CLAN_INFO"
},
SC_ALL_RIDING = {
	Id = 613,
	Visible = true,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.NoAllReset,
	},
	Icon = "SI_ALL_RIDING"
},
SC_ATTHASTE_INFINITY = {
	Id = 40,
	Icon = "SI_ATTHASTE_INFINITY"
},
SC_PYROCLASTIC = {
	Id = 607,
	Icon = "SI_PYROCLASTIC"
},
SC_VACUUM_EXTREME = {
	Id = 490,
	Icon = "SI_VACUUM_EXTREME"
},
SC_MOON_COMFORT = {
	Id = 170,
	Icon = "SI_MOON_COMFORT"
},
SC_OFFERTORIUM = {
	Id = 716,
	Icon = "SI_OFFERTORIUM"
},
SC_WIND_STEP = {
	Id = 523,
	Icon = "SI_WIND_STEP"
},
SC_STEALTHFIELD = {
	Id = 379,
	Icon = "SI_STEALTHFIELD"
},
SC_INVINCIBLE = {
	Id = 311,
	Icon = "SI_INVINCIBLE"
},
SC_CURSED_SOIL = {
	Id = 559,
	Icon = "SI_CURSED_SOIL"
},
SC_RIDING = {
	Id = 27,
	Icon = "SI_RIDING"
},
SC_GRANITIC_ARMOR = {
	Id = 606,
	Icon = "SI_GRANITIC_ARMOR"
},
SC_CURSED_SOIL_OPTION = {
	Id = 560,
	Icon = "SI_CURSED_SOIL_OPTION"
},
SC_MOVHASTE_INFINITY = {
	Id = 42,
	Icon = "SI_MOVHASTE_INFINITY"
},
SC_GOLDENE_FERSE = {
	Id = 598,
	Icon = "SI_GOLDENE_FERSE"
},
SC_GS_ACCURACY = {
	Id = 210,
	Icon = "SI_GS_ACCURACY"
},
SC_GENSOU = {
	Id = 659,
	Icon = "SI_GENSOU"
},
SC_MAGMA_FLOW = {
	Id = 605,
	Icon = "SI_MAGMA_FLOW"
},
SC_SHRIMP = {
	Id = 920,
	Icon = "SI_SHRIMP"
},
SC_SPELLBOOK1 = {
	Id = 455,
	Icon = "SI_SPELLBOOK1"
},
SC_UNLIMIT = {
	Id = 722,
	Icon = "SI_UNLIMIT"
},
SC_AQUAPLAY_OPTION = {
	Id = 546,
	Icon = "SI_AQUAPLAY_OPTION"
},
SC_GS_GATLINGFEVER = {
	Id = 204,
	Icon = "SI_GS_GATLINGFEVER"
},
SC_ROCK_CRUSHER_ATK = {
	Id = 566,
	Icon = "SI_ROCK_CRUSHER_ATK"
},
SC_HEATER_OPTION = {
	Id = 542,
	Icon = "SI_HEATER_OPTION"
},
SC_FALLENEMPIRE = {
	Id = 424,
	Icon = "SI_FALLENEMPIRE"
},
SC_MANDRAGORA = {
	Id = 470,
	Icon = "SI_MANDRAGORA"
},
SC_ANKLESNARE = {
	Id = 45,
	Icon = "SI_ANKLESNARE"
},
SC_KAIZEL = {
	Id = 156,
	Icon = "SI_KAIZEL"
},
SC_DC_WINKCHARM = {
	Id = 199,
	Icon = "SI_DC_WINKCHARM"
},
SC_WUGRIDER = {
	Id = 357,
	Icon = "SI_WUGRIDER"
},
SC_SPELLBOOK7 = {
	Id = 502,
	Icon = "SI_SPELLBOOK7"
},
SC_CATNIPPOWDER = {
	Id = 894,
	Icon = "SI_CATNIPPOWDER"
},
SC_TIDAL_WEAPON_OPTION = {
	Id = 564,
	Icon = "SI_TIDAL_WEAPON_OPTION"
},
SC_ANGRIFFS_MODUS = {
	Id = 599,
	Icon = "SI_ANGRIFFS_MODUS"
},
SC_AUTOBERSERK = {
	Id = 132,
	Icon = "SI_AUTOBERSERK"
},
SC_CRUCIS = {
	Id = 11,
	Icon = "SI_CRUCIS"
},
SC_CRUSHSTRIKE = {
	Id = 620,
	Icon = "SI_CRUSHSTRIKE"
},
SC_SPELLBOOK3 = {
	Id = 457,
	Icon = "SI_SPELLBOOK3"
},
SC_BLAST = {
	Id = 553,
	Icon = "SI_BLAST"
},
SC_IZAYOI = {
	Id = 652,
	Icon = "SI_IZAYOI"
},
SC_ODINS_POWER = {
	Id = 583,
	Icon = "SI_ODINS_POWER"
},
SC_TING = {
	Id = 134,
	Icon = "SI_TING"
},
SC_SIT = {
	Id = 622,
	Icon = "SI_SIT"
},
SC_GS_MADNESSCANCEL = {
	Id = 203,
	Icon = "SI_GS_MADNESSCANCEL"
},
SC_SV_ROOTTWIST = {
	Id = 896,
	Icon = "SI_SV_ROOTTWIST"
},
SC_COOLER = {
	Id = 547,
	Icon = "SI_COOLER"
},
SC_WIND_STEP_OPTION = {
	Id = 524,
	Icon = "SI_WIND_STEP_OPTION"
},
SC_RESIST_PROPERTY_GROUND = {
	Id = 909,
	Icon = "SI_RESIST_PROPERTY_GROUND"
},
SC_ILLUSIONDOPING = {
	Id = 734,
	Icon = "SI_ILLUSIONDOPING"
},
SC_KO_JYUMONJIKIRI = {
	Id = 645,
	Icon = "SI_KO_JYUMONJIKIRI"
},
SC_PHI_DEMON = {
	Id = 658,
	Icon = "SI_PHI_DEMON"
},
SC_KYOUGAKU = {
	Id = 651,
	Icon = "SI_KYOUGAKU"
},
SC_KAGEMUSYA = {
	Id = 656,
	Icon = "SI_KAGEMUSYA"
},
SC_SPELLBOOK6 = {
	Id = 501,
	Icon = "SI_SPELLBOOK6"
},
SC_BLAST_OPTION = {
	Id = 554,
	Icon = "SI_BLAST_OPTION"
},
SC_DARKCROW = {
	Id = 730,
	Icon = "SI_DARKCROW"
},
SC_PYROTECHNIC = {
	Id = 539,
	Icon = "SI_PYROTECHNIC"
},
SC_STAR_COMFORT = {
	Id = 171,
	Icon = "SI_STAR_COMFORT"
},
SC_LG_REFLECTDAMAGE = {
	Id = 390,
	Icon = "SI_LG_REFLECTDAMAGE"
},
SC_GENTLETOUCH_REVITALIZE = {
	Id = 427,
	Icon = "SI_GENTLETOUCH_REVITALIZE"
},
SC_HEATER = {
	Id = 541,
	Icon = "SI_HEATER"
},
SC_CIRCLE_OF_FIRE_OPTION = {
	Id = 516,
	Icon = "SI_CIRCLE_OF_FIRE_OPTION"
},
SC_ROCK_CRUSHER = {
	Id = 565,
	Icon = "SI_ROCK_CRUSHER"
},
SC_MOON = {
	Id = 123,
	Icon = "SI_MOON"
},
SC_PETROLOGY = {
	Id = 557,
	Icon = "SI_PETROLOGY"
},
SC_SUN_COMFORT = {
	Id = 169,
	Icon = "SI_SUN_COMFORT"
},
SC_TROPIC_OPTION = {
	Id = 544,
	Icon = "SI_TROPIC_OPTION"
},
SC_ARCLOUSEDASH = {
	Id = 918,
	Icon = "SI_ARCLOUSEDASH"
},
SC_STRIKING = {
	Id = 445,
	Icon = "SI_STRIKING"
},
SC_AQUAPLAY = {
	Id = 545,
	Icon = "SI_AQUAPLAY"
},
SC_WATER_DROP = {
	Id = 521,
	Icon = "SI_WATER_DROP"
},
SC_GM_BATTLE2 = {
	Id = 663,
	Icon = "SI_GM_BATTLE2"
},
SC_BROKENWEAPON = {
	Id = 33,
	Icon = "SI_BROKENWEAPON"
},
SC_CUP_OF_BOZA = {
	Id = 751,
	Icon = "SI_CUP_OF_BOZA"
},
SC_FRIGG_SONG = {
	Id = 715,
	Icon = "SI_FRIGG_SONG"
},
SC_POSTDELAY = {
	Id = 46,
	Icon = "SI_POSTDELAY"
},
SC_BROKENARMOR = {
	Id = 32,
	Icon = "SI_BROKENARMOR"
},
SC_2011RWC = {
	Id = 650,
	Icon = "SI_2011RWC"
},
SC_WATER_SCREEN_OPTION = {
	Id = 520,
	Icon = "SI_WATER_SCREEN_OPTION"
},
SC_FIRE_CLOAK = {
	Id = 517,
	Icon = "SI_FIRE_CLOAK"
},
SC_FALCON = {
	Id = 28,
	Icon = "SI_FALCON"
},
SC_ZENKAI = {
	Id = 653,
	Icon = "SI_ZENKAI"
},
SC_CLAIRVOYANCE = {
	Id = 184,
	Icon = "SI_CLAIRVOYANCE"
},
SC_STONE_SHIELD = {
	Id = 531,
	Icon = "SI_STONE_SHIELD"
},
SC_FIRE_EXPANSION_TEAR_GAS = {
	Id = 468,
	Icon = "SI_FIRE_EXPANSION_TEAR_GAS"
},
SC_ZANGETSU = {
	Id = 657,
	Icon = "SI_ZANGETSU"
},
SC_RESIST_PROPERTY_WIND = {
	Id = 911,
	Icon = "SI_RESIST_PROPERTY_WIND"
},
SC_FLASHCOMBO = {
	Id = 740,
	Icon = "SI_FLASHCOMBO"
},
SC_GUST_OPTION = {
	Id = 552,
	Icon = "SI_GUST_OPTION"
},
SC_GENTLETOUCH_ENERGYGAIN = {
	Id = 425,
	Icon = "SI_GENTLETOUCH_ENERGYGAIN"
},
SC_PYROTECHNIC_OPTION = {
	Id = 540,
	Icon = "SI_PYROTECHNIC_OPTION"
},
SC_CIRCLE_OF_FIRE = {
	Id = 515,
	Icon = "SI_CIRCLE_OF_FIRE"
},
SC_DEVIL1 = {
	Id = 152,
	Icon = "SI_DEVIL1"
},
SC_GS_ADJUSTMENT = {
	Id = 209,
	Icon = "SI_GS_ADJUSTMENT"
},
SC_SPELLBOOK5 = {
	Id = 500,
	Icon = "SI_SPELLBOOK5"
},
SC_UPHEAVAL_OPTION = {
	Id = 562,
	Icon = "SI_UPHEAVAL_OPTION"
},
SC_SUHIDE = {
	Id = 933,
	Icon = "SI_SUHIDE"
},
SC_NJ_NEN = {
	Id = 208,
	Icon = "SI_NJ_NEN"
},
SC_VOLCANIC_ASH = {
	Id = 608,
	Icon = "SI_VOLCANIC_ASH"
},
SC_KYOMU = {
	Id = 655,
	Icon = "SI_KYOMU"
},
SC_WILD_STORM = {
	Id = 555,
	Icon = "SI_WILD_STORM"
},
SC_PETROLOGY_OPTION = {
	Id = 558,
	Icon = "SI_PETROLOGY_OPTION"
},
SC_SPELLBOOK2 = {
	Id = 456,
	Icon = "SI_SPELLBOOK2"
},
SC_MYSTICPOWDER = {
	Id = 666,
	Icon = "SI_MYSTICPOWDER"
},
SC_RESIST_PROPERTY_FIRE = {
	Id = 910,
	Icon = "SI_RESIST_PROPERTY_FIRE"
},
SC_COOLER_OPTION = {
	Id = 548,
	Icon = "SI_COOLER_OPTION"
},
SC_TROPIC = {
	Id = 543,
	Icon = "SI_TROPIC"
},
SC_UPHEAVAL = {
	Id = 561,
	Icon = "SI_UPHEAVAL"
},
SC_GENTLETOUCH_CHANGE = {
	Id = 426,
	Icon = "SI_GENTLETOUCH_CHANGE"
},
SC_WATER_DROP_OPTION = {
	Id = 522,
	Icon = "SI_WATER_DROP_OPTION"
},
SC_CHILLY_AIR_OPTION = {
	Id = 550,
	Icon = "SI_CHILLY_AIR_OPTION"
},
SC_FENRIR_CARD = {
	Id = 711,
	Icon = "SI_FENRIR_CARD"
},
SC_CLIENT_ONLY_EQUIP_ARROW = {
	Id = 695,
	Icon = "SI_CLIENT_ONLY_EQUIP_ARROW"
},
SC_STASIS = {
	Id = 356,
	Icon = "SI_STASIS"
},
SC_KINGS_GRACE = {
	Id = 723,
	Icon = "SI_KINGS_GRACE"
},
SC_OVERED_BOOST = {
	Id = 581,
	Icon = "SI_OVERED_BOOST"
},
SC_AKAITSUKI = {
	Id = 660,
	Icon = "SI_AKAITSUKI"
},
SC_MARIONETTE = {
	Id = 122,
	Icon = "SI_MARIONETTE"
},
SC_WIND_CURTAIN = {
	Id = 525,
	Icon = "SI_WIND_CURTAIN"
},
SC_ON_PUSH_CART = {
	Id = 673,
	Icon = "SI_ON_PUSH_CART"
},
SC_SPELLBOOK4 = {
	Id = 499,
	Icon = "SI_SPELLBOOK4"
},
SC_ILLUSION = {
	Id = 34,
	Icon = "SI_ILLUSION"
},
SC_WIND_CURTAIN_OPTION = {
	Id = 526,
	Icon = "SI_WIND_CURTAIN_OPTION"
},
SC_SU_STOOP = {
	Id = 893,
	Icon = "SI_SU_STOOP"
},
SC_SOLID_SKIN_OPTION = {
	Id = 530,
	Icon = "SI_SOLID_SKIN_OPTION"
},
SC_TUNAPARTY = {
	Id = 919,
	Icon = "SI_TUNAPARTY"
},
SC_RESIST_PROPERTY_WATER = {
	Id = 908,
	Icon = "SI_RESIST_PROPERTY_WATER"
},
SC_KG_KAGEHUMI = {
	Id = 654,
	Icon = "SI_KG_KAGEHUMI"
},
SC_SMA_READY = {
	Id = 159,
	Icon = "SI_SMA_READY"
},
SC_FIRE_CLOAK_OPTION = {
	Id = 518,
	Icon = "SI_FIRE_CLOAK_OPTION"
},
SC_WATER_SCREEN = {
	Id = 519,
	Icon = "SI_WATER_SCREEN"
},
SC_GM_BATTLE = {
	Id = 662,
	Icon = "SI_GM_BATTLE"
},
SC_GUST = {
	Id = 551,
	Icon = "SI_GUST"
},
SC_SOLID_SKIN = {
	Id = 529,
	Icon = "SI_SOLID_SKIN"
},
SC_CHILLY_AIR = {
	Id = 549,
	Icon = "SI_CHILLY_AIR"
},
SC_MEIKYOUSISUI = {
	Id = 646,
	Icon = "SI_MEIKYOUSISUI"
},
SC_FIRE_EXPANSION_SMOKE_POWDER = {
	Id = 467,
	Icon = "SI_FIRE_EXPANSION_SMOKE_POWDER"
},
SC_MARIONETTE_MASTER = {
	Id = 121,
	Icon = "SI_MARIONETTE_MASTER"
},
SC_FRESHSHRIMP = {
	Id = 921,
	Icon = "SI_FRESHSHRIMP"
},
SC_STONE_SHIELD_OPTION = {
	Id = 532,
	Icon = "SI_STONE_SHIELD_OPTION"
},
SC_SWORDREJECT = {
	Id = 120,
	Icon = "SI_SWORDREJECT"
},
SC_WILD_STORM_OPTION = {
	Id = 556,
	Icon = "SI_WILD_STORM_OPTION"
},
SC_GN_CARTBOOST = {
	Id = 461,
	Icon = "SI_CARTSBOOST"
},
SC_THORNS_TRAP = {
	Id = 463,
	Icon = "SI_THORNTRAP"
},
SC_RICHMANKIM = {
	Id = 78,
	Behavior = {
		StatusEffectBehavior.NoBoss,
	},
},
SC_ROKISWEIL = {
	Id = 82,
	Behavior = {
		StatusEffectBehavior.NoBoss,
	},
},
SC_VACUUM_EXTREME = {
	Id = 490,
	Behavior = {
		StatusEffectBehavior.NoBoss,
	},
},
SC_FRESHSHRIMP = {
	Id = 921,
	Behavior = {
		StatusEffectBehavior.NoBoss,
	},
},
SC_SV_ROOTTWIST = {
	Id = 896,
	Behavior = {
		StatusEffectBehavior.NoBoss,
	},
},
SC_POPECOOKIE = {
	Id = 423,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_POPECOOKIE"
},
SC_VITALIZE_POTION = {
	Id = 579,
	Behavior = {
		StatusEffectBehavior.CantDispell,
	},
	Icon = "SI_VITALIZE_POTION"
},
SC_SKF_MATK = {
	Id = 635,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_SKF_MATK"
},
SC_SKF_ATK = {
	Id = 634,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_SKF_ATK"
},
SC_SKF_ASPD = {
	Id = 633,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_SKF_ASPD"
},
SC_SKF_CAST = {
	Id = 632,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_SKF_CAST"
},
SC_ALMIGHTY = {
	Id = 685,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
	},
	Icon = "SI_ALMIGHTY"
},
SC_SKE = {
	Id = 160,
	Icon = "SI_SKE"
},

SC_FLOWERSMOKE = {
	Id = 9000,
	Visible = true,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.NoMadoReset,
		StatusEffectBehavior.NoAllReset,
	},
	Icon = "SI_FLOWERSMOKE"
},
SC_BABY = {
	Id = 9001,
	Icon = "SI_PROTECTEXP"
},
SC_EXTREMITYFIST2 = {
	Id = 9002,
	Icon = "SI_EXTREMITYFIST"
},
SC_MIRACLE = {
	Id = 9003,
	Icon = "SI_SOULLINK"
},
SC_POISON = {
	Id = 9004,
	Icon = "SI_CLOUDKILL"
},
SC_SILENCE = {
	Id = 9005,
	Icon = "SI_SILENT_BREEZE"
},
SC_WARM = {
	Id = 9006,
	Icon = "SI_SG_SUN_WARM"
},
SC_COMA = {
	Id = 9007,
	Behavior = {
		StatusEffectBehavior.NoBoss,
	},
},
SC_FSTONE = {
	Id = 9008,
	Visible = true,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.NoMadoReset,
		StatusEffectBehavior.NoAllReset,
	},
	Icon = "SI_FSTONE"
},
SC_HAPPINESS_STAR = {
	Id = 9009,
	Visible = true,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.NoMadoReset,
		StatusEffectBehavior.NoAllReset,
	},
	Icon = "SI_HAPPINESS_STAR"
},
SC_MAPLE_FALLS = {
	Id = 9010,
	Visible = true,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.NoMadoReset,
		StatusEffectBehavior.NoAllReset,
	},
	Icon = "SI_MAPLE_FALLS"
},
SC_MAGICAL_FEATHER = {
	Id = 9011,
	Visible = true,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.NoMadoReset,
		StatusEffectBehavior.NoAllReset,
	},
	Icon = "SI_MAGICAL_FEATHER"
},
SC_BLOSSOM_FLUTTERING = {
	Id = 9012,
	Visible = true,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.NoMadoReset,
		StatusEffectBehavior.NoAllReset,
	},
	Icon = "SI_BLOSSOM_FLUTTERING"
},
SC_DAILYSENDMAILCNT = {
	Id = 9013,
	Visible = true,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.NoMadoReset,
		StatusEffectBehavior.NoAllReset,
	},
	Icon = "SI_DAILYSENDMAILCNT"
},

SC_WEDDING = {
	Id = 9014,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.NoMadoReset,
	},
},
SC_XMAS = {
	Id = 9015,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.NoMadoReset,
	},
},
SC_SUMMER = {
	Id = 9016,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.NoMadoReset,
	},
},
SC_NOCHAT = {
	Id = 9017,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.NoMadoReset,
		StatusEffectBehavior.NoAllReset,
	},
},
SC_FUSION = {
	Id = 9018,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.NoMadoReset,
	},
},
SC_COUNTERKICK_READY = {
	Id = 9019,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.NoMadoReset,
	},
	Icon = "SI_COUNTER_ON"
},
SC_JAILED = {
	Id = 9020,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.NoMadoReset,
		StatusEffectBehavior.NoAllReset,
	},
},
SC_AUTOTRADE = {
	Id = 9021,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.NoMadoReset,
	},
},
SC_DANCING = {
	Id = 9022,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
	},
},
SC_ASSNCROS = {
	Id = 9023,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.NoMadoReset,
	},
},
SC_FORTUNE = {
	Id = 9024,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.NoMadoReset,
	},
},
SC_INCHIT = {
	Id = 9025,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.NoMadoReset,
	},
},
SC_MADOGEAR = {
	Id = 9026,
	Visible = true,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.NoAllReset,
		StatusEffectBehavior.NoBoss,
	},
	Icon = "SI_MADOGEAR"
},
SC_LEADERSHIP = {
	Id = 9027,
	Behavior = {
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.NoMadoReset,
		StatusEffectBehavior.NoAllReset,
	},
},
SC_GLORYWOUNDS = {
	Id = 9028,
	Behavior = {
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.NoMadoReset,
		StatusEffectBehavior.NoAllReset,
	},
},
SC_SOULCOLD = {
	Id = 9029,
	Behavior = {
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.NoMadoReset,
		StatusEffectBehavior.NoAllReset,
	},
},
SC_HAWKEYES = {
	Id = 9030,
	Behavior = {
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.NoMadoReset,
		StatusEffectBehavior.NoAllReset,
	},
},
SC_BURNING = {
	Id = 9031,
	Behavior = {
		StatusEffectBehavior.NoBoss,
	},
},

SC__REPRODUCE = {
	Id = 9032,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_REPRODUCE"
},
SC__AUTOSHADOWSPELL = {
	Id = 9033,
	Behavior = {
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_AUTOSHADOWSPELL"
},
SC__SHADOWFORM = {
	Id = 9034,
	Visible = true,
	Behavior = {
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_SHADOWFORM"
},
SC__BODYPAINT = {
	Id = 9035,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_BODYPAINT"
},
SC__INVISIBILITY = {
	Id = 9036,
	Behavior = {
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_INVISIBILITY"
},
SC__DEADLYINFECT = {
	Id = 9037,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_DEADLYINFECT"
},
SC__ENERVATION = {
	Id = 9038,
	Behavior = {
		StatusEffectBehavior.IsBuff,
		StatusEffectBehavior.NoBoss,
	},
	Icon = "SI_ENERVATION"
},
SC__GROOMY = {
	Id = 9039,
	Behavior = {
		StatusEffectBehavior.IsBuff,
		StatusEffectBehavior.NoBoss,
	},
	Icon = "SI_GROOMY"
},
SC__IGNORANCE = {
	Id = 9040,
	Behavior = {
		StatusEffectBehavior.IsBuff,
		StatusEffectBehavior.NoBoss,
	},
	Icon = "SI_IGNORANCE"
},
SC__LAZINESS = {
	Id = 9041,
	Behavior = {
		StatusEffectBehavior.IsBuff,
		StatusEffectBehavior.NoBoss,
	},
	Icon = "SI_LAZINESS"
},
SC__UNLUCKY = {
	Id = 9042,
	Behavior = {
		StatusEffectBehavior.IsBuff,
		StatusEffectBehavior.NoBoss,
	},
	Icon = "SI_UNLUCKY"
},
SC_GLOOMYDAY_SK = {
	Id = 9043,
	Behavior = {
		StatusEffectBehavior.IsBuff,
	},
},
SC__WEAKNESS = {
	Id = 9044,
	Behavior = {
		StatusEffectBehavior.IsBuff,
		StatusEffectBehavior.NoBoss,
	},
	Icon = "SI_WEAKNESS"
},
SC__STRIPACCESSARY = {
	Id = 9045,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_STRIPACCESSARY"
},
SC__MANHOLE = {
	Id = 9046,
	Behavior = {
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
		StatusEffectBehavior.NoMadoReset,
	},
	Icon = "SI_MANHOLE"
},
SC__BLOODYLUST = {
	Id = 9047,
	Behavior = {
		StatusEffectBehavior.IsDebuff,
	},
},
SC_MAXIMIZEPOWER = {
	Id = 9048,
	Behavior = {
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_MAXIMIZE"
},
SC_SAFETYWALL = {
	Id = 9049,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
},
SC_PNEUMA = {
	Id = 9050,
	Behavior = {
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
},
SC_VOLCANO = {
	Id = 9051,
	Behavior = {
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_GROUNDMAGIC"
},
SC_DELUGE = {
	Id = 9052,
	Behavior = {
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_GROUNDMAGIC"
},
SC_VIOLENTGALE = {
	Id = 9053,
	Behavior = {
		StatusEffectBehavior.NoSave,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.IsBuff,
	},
	Icon = "SI_GROUNDMAGIC"
},
SC_SECRAMENT = {
	Id = 9054,
	Icon = "SI_SECRAMENT"
},
SC_DRESS_UP = {
	Id = 9055,
	Icon = "SI_DRESS_UP"
},
SC_ORCISH = {
	Id = 9056,
	Behavior = {
		StatusEffectBehavior.NoSave,
	},
},
SC_PUSH_CART = {
	Id = 9057,
	Visible = true,
	Behavior = {
		StatusEffectBehavior.NoDeathReset,
		StatusEffectBehavior.CantDispell,
		StatusEffectBehavior.CantClearance,
		StatusEffectBehavior.NoMadoReset,
		StatusEffectBehavior.NoAllReset,
	},
	Icon = "SI_ON_PUSH_CART"
},
}

return status_effect_db