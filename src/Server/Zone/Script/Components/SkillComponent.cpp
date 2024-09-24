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

#include "SkillComponent.hpp"

#include "Server/Zone/Game/Units/Unit.hpp"
#include "Server/Zone/Game/Map/Grid/GridDefinitions.hpp"
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

	state->create_named_table("SkillTargetType",
		"Single", SKTT_SINGLE_TARGETED,
		"Ground", SKTT_GROUND_TARGETED
	);

	state->create_named_table("SkillUseFailCauseType",
		"Level", SKILL_USE_FAIL_LEVEL,
		"SpInsufficient", SKILL_USE_FAIL_SP_INSUFFICIENT,
		"HpInsufficient", SKILL_USE_FAIL_HP_INSUFFICIENT,
		"StuffInsufficient", SKILL_USE_FAIL_STUFF_INSUFFICIENT,
		"SkillInterval", SKILL_USE_FAIL_SKILLINTERVAL,
		"Money", SKILL_USE_FAIL_MONEY,
		"WeaponType", SKILL_USE_FAIL_THIS_WEAPON,
		"RedJemStone", SKILL_USE_FAIL_REDJAMSTONE,
		"BlueJemStone", SKILL_USE_FAIL_BLUEJAMSTONE,
		"OverWeight", SKILL_USE_FAIL_WEIGHTOVER,
		"Generic", SKILL_USE_FAIL,
		"ToTarget", SKILL_USE_FAIL_TOTARGET,
		"ReqAncilla", SKILL_USE_FAIL_ANCILLA_NUMOVER,
		"ReqHolyWater", SKILL_USE_FAIL_HOLYWATER,
		"ReqAncilla", SKILL_USE_FAIL_ANCILLA,
		"DuplicateRangeIn", SKILL_USE_FAIL_DUPLICATE_RANGEIN,
		"ReqSkill", SKILL_USE_FAIL_NEED_OTHER_SKILL,
		"NeedHelper", SKILL_USE_FAIL_NEED_HELPER,
		"InvalidDirection", SKILL_USE_FAIL_INVALID_DIR,
		"Summon", SKILL_USE_FAIL_SUMMON,
		"SummonNone", SKILL_USE_FAIL_SUMMON_NONE,
		"ReqImitationSkill", SKILL_USE_FAIL_IMITATION_SKILL_NONE,
		"Duplicate", SKILL_USE_FAIL_DUPLICATE,
		"Condition", SKILL_USE_FAIL_CONDITION,
		"Paintbrush", SKILL_USE_FAIL_PAINTBRUSH,
		"Dragon", SKILL_USE_FAIL_DRAGON,
		"Position", SKILL_USE_FAIL_POS,
		"HelperSpInsufficient", SKILL_USE_FAIL_HELPER_SP_INSUFFICIENT,
		"NearWall", SKILL_USE_FAIL_NEER_WALL,
		"Need1PercentExp", SKILL_USE_FAIL_NEED_EXP_1PERCENT,
		"ChorusSpInsufficient", SKILL_USE_FAIL_CHORUS_SP_INSUFFICIENT,
		"GCWeaponBlocking", SKILL_USE_FAIL_GC_WEAPONBLOCKING,
		"GCPoisoningWeapon", SKILL_USE_FAIL_GC_POISONINGWEAPON,
		"ReqMadogear", SKILL_USE_FAIL_MADOGEAR,
		"ReqKunai", SKILL_USE_FAIL_NEED_EQUIPMENT_KUNAI,
		"TargetPlayer", SKILL_USE_FAIL_TOTARGET_PLAYER,
		"FailSize", SKILL_USE_FAIL_SIZE,
		"ReqCannonball", SKILL_USE_FAIL_CANONBALL,
		"ReqGuillotinePoison", SKILL_USE_FAIL_GUILLONTINE_POISON,
		"ReqMadoRide", SKILL_USE_FAIL_MADOGEAR_RIDE,
		"ReqSpellbook", SKILL_USE_FAIL_SPELLBOOK,
		"ReqSpellbookDifficultSleep", SKILL_USE_FAIL_SPELLBOOK_DIFFICULT_SLEEP,
		"SpellbookReservationPoint", SKILL_USE_FAIL_SPELLBOOK_PRESERVATION_POINT,
		"SpellbookReading", SKILL_USE_FAIL_SPELLBOOK_READING,
		"FailCart", SKILL_USE_FAIL_CART,
		"NoMoreSpell", SKILL_USE_FAIL_NO_MORE_SPELL,
		"ManualNotify", SKILL_USE_FAIL_MANUAL_NOTIFY,
		"FailNeedItem", SKILL_USE_FAIL_NEED_ITEM,
		"ReqEquipment", SKILL_USE_FAIL_NEED_EQUIPMENT,
		"ComboSkill", SKILL_USE_FAIL_COMBOSKILL,
		"ReqSpirits", SKILL_USE_FAIL_SPIRITS,
		"ReqExplosionSpirits", SKILL_USE_FAIL_EXPLOSIONSPIRITS,
		"HpTooMany", SKILL_USE_FAIL_HP_TOOMANY,
		"ReqBanding", SKILL_USE_FAIL_NEED_ROYAL_GUARD_BANDING,
		"ReqWeaponClass", SKILL_USE_FAIL_NEED_EQUIPPED_WEAPON_CLASS,
		"ReqElSummon", SKILL_USE_FAIL_EL_SUMMON,
		"ReqRelationGrade", SKILL_USE_FAIL_RELATIONGRADE,
		"ReqStyleChangeFighter", SKILL_USE_FAIL_STYLE_CHANGE_FIGHTER,
		"ReqStyleChangeGrappler", SKILL_USE_FAIL_STYLE_CHANGE_GRAPPLER,
		"NearNPC", SKILL_USE_FAIL_THERE_ARE_NPC_AROUND,
		"ReqBullet", SKILL_USE_FAIL_NEED_MORE_BULLET
	);

	state->create_named_table("zc_notify_act_3_action_types",
    	"Damage", (int) ZCNA3_DAMAGE,
    	"PickupItem", (int) ZCNA3_PICKUP_ITEM,
    	"Sit", (int) ZCNA3_SIT,
    	"Stand", (int) ZCNA3_STAND,
    	"EndureDamage", (int) ZCNA3_ENDURE_DAMAGE,
    	"Splash", (int) ZCNA3_SPLASH,
    	"Skill", (int) ZCNA3_SKILL,
    	"RepeatDamage", (int) ZCNA3_REPEAT_DAMAGE,
    	"MultiHitDamage", (int) ZCNA3_MULTI_HIT_DAMAGE,
    	"MultiHitEndureDamage", (int) ZCNA3_MULTI_HIT_ENDURE_DAMAGE,
    	"CriticalHit", (int) ZCNA3_CRITICAL_HIT,
    	"LuckyDodge", (int) ZCNA3_LUCKY_DODGE,
    	"TouchSkill", (int) ZCNA3_TOUCH_SKILL,
    	"MultiHitCritical", (int) ZCNA3_MULTI_HIT_CRITICAL
	);
}

void SkillComponent::sync_data_types(std::shared_ptr<sol::state> state)
{
	sol::usertype<skill_learnt_info> config_1 = state->new_usertype<skill_learnt_info>("SkillLearntInfo");
	config_1["skill_id"] = &skill_learnt_info::skill_id;
	config_1["level"] = &skill_learnt_info::level;
	config_1["learn_type"] = &skill_learnt_info::learn_type;

	sol::usertype<skill_config_data> config_2 = state->new_usertype<skill_config_data>("SkillConfigData");
	config_2["skill_id"] = &skill_config_data::skill_id;
	config_2["name"] = &skill_config_data::name;
	config_2["desc"] = &skill_config_data::desc;
	config_2["max_level"] = &skill_config_data::max_level;
	config_2["primary_type"] = &skill_config_data::primary_type;
	config_2["secondary_type"] = &skill_config_data::secondary_type;
	config_2["dmg_property"] = &skill_config_data::dmg_property;
	config_2["cast_time_options"] = &skill_config_data::cast_time_options;
	config_2["skill_delay_options"] = &skill_config_data::skill_delay_options;
	config_2["weapon_type"] = &skill_config_data::weapon_type;
	config_2["ammunition_type"] = &skill_config_data::ammunition_type;
	config_2["placement_flag"] = &skill_config_data::placement_flag;
	config_2["get_cast_time"] = [] (std::shared_ptr<const skill_config_data> skd, int16_t skill_lv)
		{
			return skd->cast_time[skill_lv - 1];
		};
	config_2["get_element"] = [] (std::shared_ptr<const skill_config_data> skd, int16_t skill_lv)
		{
			// TODO: see how to return error in case of skill_lv is < 0 or > MAX_SKILL_LEVEL
			return skd->element[skill_lv - 1];
		};
	config_2["get_use_range"] = [] (std::shared_ptr<const skill_config_data> skd, int16_t skill_lv)
		{
			// TODO: see how to return error in case of skill_lv is < 0 or > MAX_SKILL_LEVEL
			return skd->use_range[skill_lv - 1];
		};

	sol::usertype<SkillExecution> config_3 = state->new_usertype<SkillExecution>("SkillExecution");
	config_3["execute_on_target"] = sol::resolve<void(int)>(&SkillExecution::execute);
	config_3["execute_on_ground"] = sol::resolve<void(MapCoords)>(&SkillExecution::execute);
	config_3["execute_on_ground_xy"] = sol::resolve<void(int16_t, int16_t)>(&SkillExecution::execute);
	config_3["execute_on_ground_with_message"] = sol::resolve<void(MapCoords, std::string)>(&SkillExecution::execute);
	config_3["execute_on_ground_xy_with_message"] = sol::resolve<void(int16_t, int16_t, std::string)>(&SkillExecution::execute);
	config_3["get_skill_cast_data"] = &SkillExecution::get_skill_cast_data;
}

void SkillComponent::sync_functions(std::shared_ptr<sol::state> state)
{
}