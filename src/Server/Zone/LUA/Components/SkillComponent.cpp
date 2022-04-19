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

#include "SkillComponent.hpp"

#include "Server/Common/Configuration/Horizon.hpp"
#include "SkillDefinitions.hpp"

using namespace Horizon::Zone;

void SkillComponent::sync_definitions(std::shared_ptr<sol::state> state)
{
	state->create_named_table("SkillType",
		"Passive", SK_TYPE_PASSIVE,
		"Attack", SK_TYPE_ATTACK,
		"Placement", SK_TYPE_PLACEMENT,
		"Self", SK_TYPE_SELF,
		"Friendly", SK_TYPE_FRIENDLY,
		"Trap", SK_TYPE_TRAP
	);

	state->create_named_table("SkillPlacementBehavior", 
		"None", (int) SPB_NONE,
		"DefNotEnemy", (int) SPB_DEFNOTENEMY,
		"CannotOverlap", (int) SPB_NOREITERATION,
		"AllowPlacementOnTarget", (int) SPB_NOFOOTSET,
		"CannotOverlap", (int) SPB_NOOVERLAP,
		"CheckObstructionInPath", (int) SPB_PATHCHECK,
		"WontTargetPlayers", (int) SPB_NOPC,
		"WontTargetMobs", (int) SPB_NOMOB,
		"CanTargetSkills", (int) SPB_SKILL,
		"IsDance", (int) SPB_DANCE,
		"IsEnsemble", (int) SPB_ENSEMBLE,
		"IsSong", (int) SPB_SONG,
		"AffectOnContact", (int) SPB_DUALMODE,
		"OnlyDisplayCenter", (int) SPB_RANGEDSINGLEUNIT
	);

	state->create_named_table("SkillRequiredState",
		"None", (int) SRS_NONE,
		"Hiding", (int) SRS_HIDING,
		"Cloaking", (int) SRS_CLOAKING,
		"Hidden", (int) SRS_HIDDEN,
		"Riding", (int) SRS_RIDING,
		"Falcon", (int) SRS_FALCON,
		"Cart", (int) SRS_CART,
		"Shield", (int) SRS_SHIELD,
		"Sight", (int) SRS_SIGHT,
		"ExplosionSpirits", (int) SRS_EXPLOSIONSPIRITS,
		"CartBoost", (int) SRS_CARTBOOST,
		"NotOverWeight", (int) SRS_RECOV_WEIGHT_RATE,
		"Moveable", (int) SRS_MOVE_ENABLE,
		"InWater", (int) SRS_WATER,
		"Dragon", (int) SRS_RIDINGDRAGON,
		"Warg", (int) SRS_WUG,
		"RidingWarg", (int) SRS_RIDINGWUG,
		"MadoGear", (int) SRS_MADO,
		"ElementalSpirit", (int) SRS_ELEMENTALSPIRIT,
		"PoisonWeapon", (int) SRS_POISONINGWEAPON,
		"RollingCutter", (int) SRS_ROLLINGCUTTER,
		"MH_Fighting", (int) SRS_MH_FIGHTING,
		"MH_Grappling", (int) SRS_MH_GRAPPLING,
		"Peco", (int) SRS_PECO
	);

	state->create_named_table("SkillSubType",
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

	state->create_named_table("SkillLearnType",
		"Permanent", SKILL_LEARN_PERMANENT,
		"Temporary", SKILL_LEARN_TEMPORARY,
		"Plagiarized", SKILL_LEARN_PLAGIARIZED,
		"Unused", SKILL_LEARN_UNUSED,
		"PermanentlyGranted", SKILL_LEARN_PERM_GRANTED,
		"ReplacedLv0", SKILL_LEARN_REPLACED_LV_0
	);
}

void SkillComponent::sync_data_types(std::shared_ptr<sol::state> state)
{
	state->new_usertype<skill_learnt_info>("SkillLearntInfo",
		"skill_id", &skill_learnt_info::skill_id,
		"level", &skill_learnt_info::level,
		"learn_type", &skill_learnt_info::learn_type
	);
}

void SkillComponent::sync_functions(std::shared_ptr<sol::state> state)
{
}