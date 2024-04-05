/***************************************************
 *	   _   _			_						*
 *	  | | | |		  (_)					   *
 *	  | |_| | ___  _ __ _ _______  _ __		  *
 *	  |  _  |/ _ \| '__| |_  / _ \| '_  \		*
 *	  | | | | (_) | |  | |/ / (_) | | | |		*
 *	  \_| |_/\___/|_|  |_/___\___/|_| |_|		*
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

#include "CombatComponent.hpp"

#include "Server/Common/Configuration/Horizon.hpp"
#include "Server/Zone/Game/Units/Traits/Attribute.hpp"
#include "Server/Zone/Game/Units/Battle/Combat.hpp"
#include "BattleDefinitions.hpp"

using namespace Horizon::Zone;

void CombatComponent::sync_definitions(std::shared_ptr<sol::state> state)
{
	state->create_named_table("TargetCheckType",
		"Noone", (int) BTC_NONE,
		"Self", (int) BTC_SELF,
		"Enemy", (int) BTC_ENEMY,
		"Party", (int) BTC_PARTY,
		"AllianceOnly", (int) BTC_GUILD_ALLY,
		"Neutral", (int) BTC_NEUTRAL,
		"Guild", (int) BTC_GUILD,
		"GuildAndAlliance", (int) BTC_GUILD_AND_ALLY,
		"AllExceptGuild", (int) BTC_ALL_EXCEPT_GUILD,
		"AllExceptParty", (int) BTC_ALL_EXCEPT_PARTY,
		"AllExceptEnemy", (int) BTC_ALL_EXCEPT_ENEMY,
		"All", (int) BTC_ALL
	);

	state->create_named_table("AttackType",
		"None", (int) BAT_NONE,
		"Weapon", (int) BAT_WEAPON,
		"Magic", (int) BAT_MAGIC,
		"Misc", (int) BAT_MISC
	);

	state->create_named_table("DamageBehavior",
		"NoDamage", (int) DMG_BHVR_NONE,
		"NonOffensive", (int) DMG_BHVR_NON_OFFENSIVE,
		"SplashArea", (int) DMG_BHVR_SPLASH,
		"SplitBetweenTargets", (int) DMG_BHVR_SPLIT_BW_TARGETS,
		"IgnoreEquipATK", (int) DMG_BHVR_IGNORE_EQUIP_ATK,
		"IgnoreDefElement", (int) DMG_BHVR_IGNORE_DEF_ELE,
		"IgnoreSoftDef", (int) DMG_BHVR_IGNORE_SOFT_DEF,
		"IgnoreFLEE", (int) DMG_BHVR_IGNORE_FLEE,
		"IgnoreEquipDef", (int) DMG_BHVR_IGNORE_EQUIP_DEF
	);

	state->create_named_table("AttributeOperationType",
		"AddToBase", (int) CombatRegistry::AttributeOperation::ATTRIBUTE_OPERATION_ADD_TO_BASE,
		"SubFromBase", (int) CombatRegistry::AttributeOperation::ATTRIBUTE_OPERATION_SUBTRACT_FROM_BASE,
		"AddToEquip", (int) CombatRegistry::AttributeOperation::ATTRIBUTE_OPERATION_ADD_TO_EQUIP,
		"SubFromEquip", (int) CombatRegistry::AttributeOperation::ATTRIBUTE_OPERATION_SUBTRACT_FROM_EQUIP,
		"AddToStatus", (int) CombatRegistry::AttributeOperation::ATTRIBUTE_OPERATION_ADD_TO_STATUS,
		"SubtractFromStatus", (int) CombatRegistry::AttributeOperation::ATTRIBUTE_OPERATION_SUBTRACT_FROM_STATUS
	);

	state->create_named_table("StatusOperationType",
		"Add", (int) CombatRegistry::StatusOperation::STATUS_OPERATION_ADD,
		"Remove", (int) CombatRegistry::StatusOperation::STATUS_OPERATION_REMOVE
	);

	state->create_named_table("SkillExecutionOperationType",
		"Cast", (int) CombatRegistry::SkillExecutionOperation::SKILL_EXECUTION_OPERATION_CAST,
		"Target", (int) CombatRegistry::SkillExecutionOperation::SKILL_EXECUTION_OPERATION_TARGET,
		"Ground", (int) CombatRegistry::SkillExecutionOperation::SKILL_EXECUTION_OPERATION_GROUND
	);
	
	state->create_named_table("SkillResultOperationType",
		"Damage", (int) CombatRegistry::SkillResultOperation::SKILL_RESULT_OPERATION_DAMAGE,
		"Healing", (int) CombatRegistry::SkillResultOperation::SKILL_RESULT_OPERATION_HEALING
	);

	state->create_named_table("MeleeExecutionOperationType",
		"Target", (int) CombatRegistry::MeleeExecutionOperation::MELEE_EXECUTION_OPERATION_TARGET
	);
	
	state->create_named_table("MeleeResultOperationType",
		"Damage", (int) CombatRegistry::MeleeResultOperation::MELEE_RESULT_OPERATION_DAMAGE,
		"Healing", (int) CombatRegistry::MeleeResultOperation::MELEE_RESULT_OPERATION_HEALING
	);

	state->create_named_table("CombatDamageHitType",
		"Normal", (int) combat_damage_hit_type::CBT_DMG_HIT_NORMAL,
		"Endure", (int) combat_damage_hit_type::CBT_DMG_HIT_ENDURE,
		"Splash", (int) combat_damage_hit_type::CBT_DMG_HIT_SPLASH,
		"Skill", (int) combat_damage_hit_type::CBT_DMG_HIT_SKILL,
		"MultiHit", (int) combat_damage_hit_type::CBT_DMG_HIT_MULTIHIT,
		"MultiEndure", (int) combat_damage_hit_type::CBT_DMG_HIT_MULTIENDURE,
		"Critical", (int) combat_damage_hit_type::CBT_DMG_HIT_CRIT,
		"PerfectDodge", (int) combat_damage_hit_type::CBT_DMG_HIT_PDODGE
	);
}

void CombatComponent::sync_data_types(std::shared_ptr<sol::state> state)
{
	state->new_usertype<CombatRegistry::StatusOperation::StatusOperand::s_combat_status_operation_config>("s_combat_status_operation_config",
		"type", &CombatRegistry::StatusOperation::StatusOperand::s_combat_status_operation_config::type,
		"total_time", &CombatRegistry::StatusOperation::StatusOperand::s_combat_status_operation_config::total_time,
		"val1", &CombatRegistry::StatusOperation::StatusOperand::s_combat_status_operation_config::val1,
		"val2", &CombatRegistry::StatusOperation::StatusOperand::s_combat_status_operation_config::val2,
		"val3", &CombatRegistry::StatusOperation::StatusOperand::s_combat_status_operation_config::val3,
		"val4", &CombatRegistry::StatusOperation::StatusOperand::s_combat_status_operation_config::val4
	);

	state->new_usertype<CombatRegistry::SkillExecutionOperation::SkillExecutionOperand::s_skill_execution_operation_config>("s_skill_execution_operation_config",
		"skill_id", &CombatRegistry::SkillExecutionOperation::SkillExecutionOperand::s_skill_execution_operation_config::skill_id,
		"skill_lv", &CombatRegistry::SkillExecutionOperation::SkillExecutionOperand::s_skill_execution_operation_config::skill_lv,
		"pos_x", &CombatRegistry::SkillExecutionOperation::SkillExecutionOperand::s_skill_execution_operation_config::pos_x,
		"pos_y", &CombatRegistry::SkillExecutionOperation::SkillExecutionOperand::s_skill_execution_operation_config::pos_y,
		"contents", &CombatRegistry::SkillExecutionOperation::SkillExecutionOperand::s_skill_execution_operation_config::contents,
		"skd", &CombatRegistry::SkillExecutionOperation::SkillExecutionOperand::s_skill_execution_operation_config::skd,
		"skill_execution", &CombatRegistry::SkillExecutionOperation::SkillExecutionOperand::s_skill_execution_operation_config::skill_execution,
		"cast_time", &CombatRegistry::SkillExecutionOperation::SkillExecutionOperand::s_skill_execution_operation_config::cast_time,
		"element", &CombatRegistry::SkillExecutionOperation::SkillExecutionOperand::s_skill_execution_operation_config::element,
		"cast_end_function", &CombatRegistry::SkillExecutionOperation::SkillExecutionOperand::s_skill_execution_operation_config::cast_end_function,
		"skill_cast_data", &CombatRegistry::SkillExecutionOperation::SkillExecutionOperand::s_skill_execution_operation_config::skill_cast_data
	);

	state->new_usertype<CombatRegistry::SkillResultOperation::SkillResultOperand::s_skill_result_operation_config>("s_skill_result_operation_config",
		"skill_id", &CombatRegistry::SkillResultOperation::SkillResultOperand::s_skill_result_operation_config::skill_id,
		"skill_lv", &CombatRegistry::SkillResultOperation::SkillResultOperand::s_skill_result_operation_config::skill_lv,
		"pos_x", &CombatRegistry::SkillResultOperation::SkillResultOperand::s_skill_result_operation_config::pos_x,
		"pos_y", &CombatRegistry::SkillResultOperation::SkillResultOperand::s_skill_result_operation_config::pos_y,
		"contents", &CombatRegistry::SkillResultOperation::SkillResultOperand::s_skill_result_operation_config::contents,
		"skd", &CombatRegistry::SkillResultOperation::SkillResultOperand::s_skill_result_operation_config::skd,
		"action_type", &CombatRegistry::SkillResultOperation::SkillResultOperand::s_skill_result_operation_config::action_type
	);

	state->new_usertype<CombatRegistry::MeleeExecutionOperation::MeleeExecutionOperand::s_melee_execution_operation_config>("s_melee_execution_operation_config",
		"continuous", &CombatRegistry::MeleeExecutionOperation::MeleeExecutionOperand::s_melee_execution_operation_config::continuous
	);
	
	state->new_usertype<combat_damage>("combat_damage", 
		"right_damage", &combat_damage::right_damage,
		"left_damage", &combat_damage::left_damage,
		"type", &combat_damage::type,
		"number_of_hits", &combat_damage::number_of_hits,
		"amotion", &combat_damage::amotion,
		"dmotion", &combat_damage::dmotion,
		"blewcount", &combat_damage::blewcount,
		"damage_type", &combat_damage::damage_type,
		"ret_type", &combat_damage::ret_type,
		"ele_type", &combat_damage::ele_type,
		"element_level", &combat_damage::element_level,
		"skill_id", &combat_damage::skill_id,
		"skill_lv", &combat_damage::skill_lv,
		"skill_cast_data", &combat_damage::skill_cast_data
	);
	
	state->new_usertype<combat_healing>("combat_healing",
		"heal_amount", &combat_healing::heal_amount,
		"skill_id", &combat_healing::skill_id,
		"success", &combat_healing::success,
		"skill_lv", &combat_healing::skill_lv,
		"skill_cast_data", &combat_healing::skill_cast_data
	);

	state->new_usertype<CombatRegistry::CombatOperationValue>("CombatOperationValue",
		sol::constructors<CombatRegistry::CombatOperationValue()>()
	);

	state->new_usertype<CombatRegistry::CombatValueInteger>("CombatValueInteger",
		sol::constructors<CombatRegistry::CombatValueInteger(int)>(),
		"get_value", &CombatRegistry::CombatValueInteger::get_value
	);

	state->new_usertype<CombatRegistry::CombatValueDamage>("CombatValueDamage",
		sol::constructors<CombatRegistry::CombatValueDamage(combat_damage)>(),
		"get_damage", &CombatRegistry::CombatValueDamage::get_damage
	);

	state->new_usertype<CombatRegistry::CombatValueHealing>("CombatValueHealing",
		sol::constructors<CombatRegistry::CombatValueHealing(combat_healing)>(),
		"get_healing", &CombatRegistry::CombatValueHealing::get_healing
	);

	state->new_usertype<CombatRegistry>("CombatRegistry",
		"create_combat_stage", &CombatRegistry::create_combat_stage,
		"queue_combat_stage", &CombatRegistry::queue_combat_stage
	);

	state->new_usertype<CombatRegistry::AttributeOperation::AttributeOperand>("AttributeOperand",
		sol::constructors<CombatRegistry::AttributeOperation::AttributeOperand(std::shared_ptr<Horizon::Zone::Unit>, std::shared_ptr<Horizon::Zone::Unit>, std::shared_ptr<Horizon::Zone::Traits::Attribute>)>(),
		"get_attribute", &CombatRegistry::AttributeOperation::AttributeOperand::get_attribute
	);

	state->new_usertype<CombatRegistry::AttributeOperation>("AttributeOperation",
		sol::constructors<CombatRegistry::AttributeOperation(
			CombatRegistry::AttributeOperation::AttributeOperand *,
			CombatRegistry::AttributeOperation::attribute_operation_type,
			CombatRegistry::CombatValueInteger *)>(), 
		"get_operation_type", &CombatRegistry::AttributeOperation::get_operation_type,
		"get_operation_sub_type", &CombatRegistry::AttributeOperation::get_operation_sub_type,
		"get_operand", &CombatRegistry::AttributeOperation::get_operand,
		"get_operation_value", &CombatRegistry::AttributeOperation::get_operation_value
	);

	state->new_usertype<CombatRegistry::StatusOperation::StatusOperand>("StatusOperand",
		sol::constructors<CombatRegistry::StatusOperation::StatusOperand(std::shared_ptr<Horizon::Zone::Unit>, std::shared_ptr<Horizon::Zone::Unit>, CombatRegistry::StatusOperation::StatusOperand::s_combat_status_operation_config)>(),
		"get_config", &CombatRegistry::StatusOperation::StatusOperand::get_config
	);

	state->new_usertype<CombatRegistry::StatusOperation>("StatusOperation",
		sol::constructors<
			CombatRegistry::StatusOperation(CombatRegistry::StatusOperation::StatusOperand *, CombatRegistry::StatusOperation::status_operation_type)
		>(),
		"get_operation_type", &CombatRegistry::StatusOperation::get_operation_type,
		"get_operation_sub_type", &CombatRegistry::StatusOperation::get_operation_sub_type,
		"get_operand", &CombatRegistry::StatusOperation::get_operand
	);
	
	state->new_usertype<CombatRegistry::SkillExecutionOperation::SkillExecutionOperand>("SkillExecutionOperand",
		sol::constructors<CombatRegistry::SkillExecutionOperation::SkillExecutionOperand(std::shared_ptr<Horizon::Zone::Unit>, std::shared_ptr<Horizon::Zone::Unit>, CombatRegistry::SkillExecutionOperation::SkillExecutionOperand::s_skill_execution_operation_config)>(),
		"get_config", &CombatRegistry::SkillExecutionOperation::SkillExecutionOperand::get_config
	);

	state->new_usertype<CombatRegistry::SkillExecutionOperation>("SkillExecutionOperation",
		sol::constructors<CombatRegistry::SkillExecutionOperation(CombatRegistry::SkillExecutionOperation::SkillExecutionOperand *, CombatRegistry::SkillExecutionOperation::skill_execution_operation_type)>(), 
		"get_operation_type", &CombatRegistry::SkillExecutionOperation::get_operation_type,
		"get_operation_sub_type", &CombatRegistry::SkillExecutionOperation::get_operation_sub_type,
		"get_operand", &CombatRegistry::SkillExecutionOperation::get_operand,
		"get_operation_value", &CombatRegistry::SkillExecutionOperation::get_operation_value
	);
	
	state->new_usertype<CombatRegistry::SkillResultOperation::SkillResultOperand>("SkillResultOperand",
		sol::constructors<CombatRegistry::SkillResultOperation::SkillResultOperand(std::shared_ptr<Horizon::Zone::Unit>, std::shared_ptr<Horizon::Zone::Unit>, CombatRegistry::SkillResultOperation::SkillResultOperand::s_skill_result_operation_config)>(),
		"get_config", &CombatRegistry::SkillResultOperation::SkillResultOperand::get_config
	);

	state->new_usertype<CombatRegistry::SkillResultOperation>("SkillResultOperation",
		sol::constructors<
			CombatRegistry::SkillResultOperation(CombatRegistry::SkillResultOperation::SkillResultOperand *, CombatRegistry::SkillResultOperation::skill_result_operation_type, CombatRegistry::CombatValueDamage *),
			CombatRegistry::SkillResultOperation(CombatRegistry::SkillResultOperation::SkillResultOperand *, CombatRegistry::SkillResultOperation::skill_result_operation_type, CombatRegistry::CombatValueHealing *)
		>(), 
		"get_operation_type", &CombatRegistry::SkillResultOperation::get_operation_type,
		"get_operation_sub_type", &CombatRegistry::SkillResultOperation::get_operation_sub_type,
		"get_operand", &CombatRegistry::SkillResultOperation::get_operand,
		"get_operation_value", &CombatRegistry::SkillResultOperation::get_operation_value
	);
	
	state->new_usertype<CombatRegistry::MeleeExecutionOperation::MeleeExecutionOperand>("MeleeExecutionOperand",
		sol::constructors<CombatRegistry::MeleeExecutionOperation::MeleeExecutionOperand(std::shared_ptr<Horizon::Zone::Unit>, std::shared_ptr<Horizon::Zone::Unit>, CombatRegistry::MeleeExecutionOperation::MeleeExecutionOperand::s_melee_execution_operation_config)>(),
		"get_config", &CombatRegistry::MeleeExecutionOperation::MeleeExecutionOperand::get_config
	);

	state->new_usertype<CombatRegistry::MeleeExecutionOperation>("MeleeExecutionOperation",
		sol::constructors<CombatRegistry::MeleeExecutionOperation(CombatRegistry::MeleeExecutionOperation::MeleeExecutionOperand *, CombatRegistry::MeleeExecutionOperation::melee_execution_operation_type)>(), 
		"get_operation_type", &CombatRegistry::MeleeExecutionOperation::get_operation_type,
		"get_operation_sub_type", &CombatRegistry::MeleeExecutionOperation::get_operation_sub_type,
		"get_operand", &CombatRegistry::MeleeExecutionOperation::get_operand,
		"get_operation_value", &CombatRegistry::MeleeExecutionOperation::get_operation_value
	);
	
	state->new_usertype<CombatRegistry::MeleeResultOperation::MeleeResultOperand>("MeleeResultOperand",
		sol::constructors<CombatRegistry::MeleeResultOperation::MeleeResultOperand(std::shared_ptr<Horizon::Zone::Unit>, std::shared_ptr<Horizon::Zone::Unit>)>()
	);

	state->new_usertype<CombatRegistry::MeleeResultOperation>("MeleeResultOperation",
		sol::constructors<
			CombatRegistry::MeleeResultOperation(CombatRegistry::MeleeResultOperation::MeleeResultOperand *, CombatRegistry::MeleeResultOperation::melee_result_operation_type, CombatRegistry::CombatValueDamage *),
			CombatRegistry::MeleeResultOperation(CombatRegistry::MeleeResultOperation::MeleeResultOperand *, CombatRegistry::MeleeResultOperation::melee_result_operation_type, CombatRegistry::CombatValueHealing *)
		>(), 
		"get_operation_type", &CombatRegistry::MeleeResultOperation::get_operation_type,
		"get_operation_sub_type", &CombatRegistry::MeleeResultOperation::get_operation_sub_type,
		"get_operand", &CombatRegistry::MeleeResultOperation::get_operand,
		"get_operation_value", &CombatRegistry::MeleeResultOperation::get_operation_value
	);

	state->new_usertype<CombatRegistry::CombatStage>("CombatStage",
		sol::constructors<CombatRegistry::CombatStage(int)>(),
		"get_priority", &CombatRegistry::CombatStage::get_priority,
        "push_attribute_operation", &CombatRegistry::CombatStage::push_attribute_operation,
		"push_status_add_operation", &CombatRegistry::CombatStage::push_status_add_operation,
		"push_status_remove_operation", &CombatRegistry::CombatStage::push_status_remove_operation,
		"push_skill_execution_operation", &CombatRegistry::CombatStage::push_skill_execution_operation,
		"push_skill_result_damage_operation", &CombatRegistry::CombatStage::push_skill_result_damage_operation,
		"push_skill_result_healing_operation", &CombatRegistry::CombatStage::push_skill_result_healing_operation,
		"push_melee_execution_operation", &CombatRegistry::CombatStage::push_melee_execution_operation,
		"push_melee_result_damage_operation", &CombatRegistry::CombatStage::push_melee_result_damage_operation,
		"push_melee_result_healing_operation", &CombatRegistry::CombatStage::push_melee_result_healing_operation
	);
}

void CombatComponent::sync_functions(std::shared_ptr<sol::state> state)
{
}