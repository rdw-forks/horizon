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
}

void SkillComponent::sync_data_types(std::shared_ptr<sol::state> state)
{
	// state.create_new_user_type<skill_cast_data>("SkillCastData",
	// 	"skill_id", skill_id;                                                              ///< Skill Id.
	// int16_t skill_lv{0};                                                              ///< Skill level.
	// std::shared_ptr<Entity> source_caster{nullptr};                                   ///< Source caster's block data.
	// std::shared_ptr<Entity> owner_of_source_caster{nullptr}; 
	// //struct status_change *sc;                                                       ///< Source caster's status change data.
	// //struct status_change_entry *sce;                                                ///< Status change entry of the target.
	// //int sc_type;                                                                    ///< Status change type of the skill.
	// int cast_time{0};                                                                 ///< Cast Time of the skill.

	// int hp_cost{0};                                                                   ///< hp
	// int sp_cost{0};                                                                   ///< sp
	// int hp_percent_cost{0};                                                           ///< hp_rate_cost
	// int sp_percent_cost{0};                                                           ///< sp_rate_cost
	// int max_hp_trigger{0};                                                            ///< mhp
	// int max_sp_trigger{0};                                                            ///< msp
	// int zeny_cost{0};
	// int weapon_type{IT_WT_FIST};                                                      ///< item_weapon_type  / weapon
	// int ammunition_type{IT_AT_NONE};                                                  ///< item_ammunition_type / ammo
	// int ammunition_cost{0};                                                           ///<
	// int required_state{0};                                                            ///< skill_required_state_types
	// int spirit_sphere_cost{0};

	// struct skill_required_item_data_for_cast {
	// 	struct {
	// 		int id{0};
	// 		int amount{0};
	// 	} item[MAX_SKILL_ITEM_REQUIRE]{0};
	// 	bool any{false};
	// } req_items, req_equip;

	// unsigned int splash_target{0};                                                    ///< Mask of entity_types as splash targets (@see skill->splash_target).
	// int splash_range{0};                                                              ///< Splash-range of the skill.
	// int64_t cast_start_time{0};                                                       ///< Time of skill packet reception.
	// int attack_type{0};                                                               ///< Attack Properties of the skill cast.
	// // Enum bit masks.
	// int display_flags{0};                                                             ///< Display flags from e_skill_display.
	// int target_flags{0};                                                              ///< Mask of e_battle_check_target.
	// // AoE specific data.
	// int area_target_count{0};                                                         ///< Count of targets in the area of a splash range.
	// int area_target_invoked{0};                                                       ///< Temporary count for the number of targets that
	// 												                                  ///! have been recursively invoked by @see skill_cast_area_sub().
	// // Knock back information.
	// int knock_back_cells{0};                                                          ///< Distance to knock back if any.
	// int knock_back_dir{0};                                                            ///< Direction to knock back (-1 for default).
	// int knock_back_flag{0};                                                           ///< @see skill_blown() for flag types.

	// // Target/AoE specific data.
	// union {
	// 	struct {
	// 		uint16_t x{0}, y{0};                                                      ///< coordinates of the AOE skill
	// 	} aoe;
	// 	struct {
	// 		std::shared_ptr<Entity> entity{nullptr};                                  ///< Entity data of the target
	// 	} target;
	// } u;                                                                              ///< Union

	// // Skill Switches / Flags.
	// struct {
	// 	unsigned int is_aoe : 1;                                                      ///< AoE/Targeted skill toggle. (Type specifier for union u)
	// 	unsigned int record_last_casted : 1;                                          ///< Records latest casted skill even on failure.
	// 	unsigned int splash_ignore_caster : 1;                                        ///< Splash skills that ignore the caster.
	// 	unsigned int foreach_retain_properties : 1;                                   ///< Retain original cast properties.
	// 	unsigned int ignore_requirements : 1;                                         ///< Ignore requirements.
	// 	unsigned int attract_cast_sensors : 1;                                        ///< Pulls cast-sensing mobs even if no casttime.
	// 	unsigned int interrupt_cast : 1;                                              ///< Interrupts the target's current cast.
	// 	unsigned int item_invoked : 1;                                                ///< Invoked via an item.
	// 	unsigned int splash_ignore_primary_target : 1;                                ///< Ignore the primary target of a splash attack. (In cases where the primary target is handled separately.)
	// } flags;

	// // Client interface specific data.
	// struct {
	// 	std::shared_ptr<Entity> skill_animation_target{nullptr};                      ///< Target of the skill animation.
	// 	int skill_id{0};                                                              ///< Skill Id sent to the client.
	// 	int display_value{0};                                                         ///< Healed amount sent to the client.
	// 	int damage_value{0};                                                          ///< Damage value to be displayed for @see clif_skill_damage
	// } clif;
}

void SkillComponent::sync_functions(std::shared_ptr<sol::state> state)
{
}