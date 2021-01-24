/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 *
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

#include "Status.hpp"
#include "Server/Common/Configuration/Horizon.hpp"
#include "Server/Zone/Game/StaticDB/JobDB.hpp"
#include "Server/Zone/Game/StaticDB/ExpDB.hpp"
#include "Server/Zone/Game/Entities/Traits/Appearance.hpp"
#include "Server/Zone/Game/Entities/Traits/Attributes.hpp"
#include "Server/Zone/Game/Entities/Traits/SubAttributes.hpp"
#include "Server/Zone/Game/Entities/Traits/ObservableStatus.hpp"
#include "Server/Zone/Game/Entities/Player/Player.hpp"
#include "Server/Common/SQL/Character/Status.hpp"
#include "Server/Zone/Packets/TransmittedPackets.hpp"
#include "Server/Zone/Session/ZoneSession.hpp"
#include "Server/Zone/Zone.hpp"

#include <stdio.h>
#include <sqlpp11/sqlpp11.h>
#include <sqlpp11/mysql/connection.h>

using namespace Horizon::Zone::Entities::Traits;

void Status::initialize()
{
	set_movement_speed(std::make_shared<MovementSpeed>(_entity, DEFAULT_MOVEMENT_SPEED));

	set_base_level(std::make_shared<BaseLevel>(_entity, 1));
	set_job_level(std::make_shared<JobLevel>(_entity, 1));

	set_current_hp(std::make_shared<CurrentHP>(_entity, 1));
	set_current_sp(std::make_shared<CurrentSP>(_entity, 1));
	set_max_hp(std::make_shared<MaxHP>(_entity, 1));
	set_max_sp(std::make_shared<MaxSP>(_entity, 1));

	set_hair_color(std::make_shared<HairColor>(_entity, 0));
	set_cloth_color(std::make_shared<ClothColor>(_entity, 0));
	set_head_top_sprite(std::make_shared<HeadTopSprite>(_entity, 0));
	set_head_mid_sprite(std::make_shared<HeadMidSprite>(_entity, 0));
	set_head_bottom_sprite(std::make_shared<HeadBottomSprite>(_entity, 0));
	set_hair_style(std::make_shared<HairStyle>(_entity, 0));
	set_shield_sprite(std::make_shared<ShieldSprite>(_entity, 0));
	set_weapon_sprite(std::make_shared<WeaponSprite>(_entity, 0));
	set_robe_sprite(std::make_shared<RobeSprite>(_entity, 0));
	set_body_style(std::make_shared<BodyStyle>(_entity, 0));
}

void Status::initialize_player(std::shared_ptr<Entity> entity)
{
	std::shared_ptr<Player> pl = entity->template downcast<Player>();
	SQL::TableCharacterStatus tcs;
	
	std::shared_ptr<sqlpp::mysql::connection> conn = sZone->get_db_connection();
	
	auto res = (*conn)(select(all_of(tcs)).from(tcs).where(tcs.id == pl->character()._character_id));
	
	if (res.empty()) {
		ZC_REFUSE_ENTER zre(pl->get_session());
		HLog(error) << "Error initializing status for character " << pl->character()._character_id << ".";
		zre.deliver(ZONE_SERV_ERROR_REJECT);
		return;
	}
	
	uint32_t job_id = res.front().job_id;
	
	pl->set_job_id(job_id);
	
	std::shared_ptr<const job_db_data> job = JobDB->get(job_id);
	std::shared_ptr<const exp_group_data> bexpg = ExpDB->get_exp_group(job->base_exp_group, EXP_GROUP_TYPE_BASE);
	std::shared_ptr<const exp_group_data> jexpg = ExpDB->get_exp_group(job->job_exp_group, EXP_GROUP_TYPE_JOB);

	uint32_t str = res.front().strength;
	uint32_t agi = res.front().agility;
	uint32_t vit = res.front().vitality;
	uint32_t _int = res.front().intelligence;
	uint32_t dex = res.front().dexterity;
	uint32_t luk = res.front().luck;

	/**
	 * Main Attributes.
	 */
	set_strength(std::make_shared<Strength>(_entity, str));
	set_agility(std::make_shared<Agility>(_entity, agi, 0, 0));
	set_vitality(std::make_shared<Vitality>(_entity, vit, 0, 0));
	set_intelligence(std::make_shared<Intelligence>(_entity, _int, 0, 0));
	set_dexterity(std::make_shared<Dexterity>(_entity, dex, 0, 0));
	set_luck(std::make_shared<Luck>(_entity, luk, 0, 0));

	set_strength_cost(std::make_shared<StrengthPointCost>(_entity, get_required_statpoints(str, str + 1)));
	set_agility_cost(std::make_shared<AgilityPointCost>(_entity, get_required_statpoints(agi, agi + 1)));
	set_vitality_cost(std::make_shared<VitalityPointCost>(_entity, get_required_statpoints(vit, vit + 1)));
	set_intelligence_cost(std::make_shared<IntelligencePointCost>(_entity, get_required_statpoints(_int, _int + 1)));
	set_dexterity_cost(std::make_shared<DexterityPointCost>(_entity, get_required_statpoints(dex, dex + 1)));
	set_luck_cost(std::make_shared<LuckPointCost>(_entity, get_required_statpoints(luk, luk + 1)));

	set_status_point(std::make_shared<StatusPoint>(_entity, uint32_t(res.front().status_points)));
	set_skill_point(std::make_shared<SkillPoint>(_entity, uint32_t(res.front().skill_points)));

	set_current_hp(std::make_shared<CurrentHP>(_entity, uint32_t(res.front().hp)));
	set_current_sp(std::make_shared<CurrentSP>(_entity, uint32_t(res.front().sp)));
	set_max_hp(std::make_shared<MaxHP>(_entity, uint32_t(res.front().maximum_hp)));
	set_max_sp(std::make_shared<MaxSP>(_entity, uint32_t(res.front().maximum_sp)));

	uint32_t base_level = uint32_t(res.front().base_level);
	uint32_t job_level = uint32_t(res.front().job_level);
	
	set_base_level(std::make_shared<BaseLevel>(_entity, base_level));
	set_job_level(std::make_shared<JobLevel>(_entity, job_level));

	set_base_experience(std::make_shared<BaseExperience>(_entity, uint64_t(res.front().base_experience)));
	set_job_experience(std::make_shared<JobExperience>(_entity, uint64_t(res.front().job_experience)));
	set_next_base_experience(std::make_shared<NextBaseExperience>(_entity, bexpg->exp[base_level - 1]));
	set_next_job_experience(std::make_shared<NextJobExperience>(_entity, bexpg->exp[job_level - 1]));
	set_movement_speed(std::make_shared<MovementSpeed>(_entity, DEFAULT_MOVEMENT_SPEED));

	set_hair_color(std::make_shared<HairColor>(_entity, uint32_t(res.front().hair_color_id)));
	set_cloth_color(std::make_shared<ClothColor>(_entity, uint32_t(res.front().cloth_color_id)));
	set_head_top_sprite(std::make_shared<HeadTopSprite>(_entity, uint32_t(res.front().head_top_view_id)));
	set_head_mid_sprite(std::make_shared<HeadMidSprite>(_entity, uint32_t(res.front().head_mid_view_id)));
	set_head_bottom_sprite(std::make_shared<HeadBottomSprite>(_entity, uint32_t(res.front().head_bottom_view_id)));
	set_hair_style(std::make_shared<HairStyle>(_entity, uint32_t(res.front().hair_style_id)));
	set_shield_sprite(std::make_shared<ShieldSprite>(_entity, uint32_t(res.front().shield_id)));
	set_weapon_sprite(std::make_shared<WeaponSprite>(_entity, uint32_t(res.front().weapon_id)));
	set_robe_sprite(std::make_shared<RobeSprite>(_entity, uint32_t(res.front().robe_view_id)));
	set_body_style(std::make_shared<BodyStyle>(_entity, uint32_t(res.front().body_id)));

	initialize_sub_attributes(job);

	initialize_observable_statuses();
	initialize_notifiable_statuses();

	pl->get_session()->clif()->notify_status(shared_from_this());
}

void Status::initialize_sub_attributes(std::shared_ptr<const job_db_data> job)
{
	std::shared_ptr<StatusATK> status_atk;
	std::shared_ptr<WeaponATK> weapon_atk;
	std::shared_ptr<StatusMATK> status_matk;
	std::shared_ptr<SoftDEF> soft_def;
	std::shared_ptr<SoftMDEF> soft_mdef;
	std::shared_ptr<HIT> hit;
	std::shared_ptr<CRIT> crit;
	std::shared_ptr<FLEE> flee;
	std::shared_ptr<MaxWeight> max_weight;

	set_max_weight(max_weight = std::make_shared<MaxWeight>(_entity, job->max_weight));
	max_weight->set_strength(get_strength());

	// Calculated when inventory is synced.
	set_current_weight(std::make_shared<CurrentWeight>(_entity, 0));

	set_status_atk(status_atk = std::make_shared<StatusATK>(_entity));
	status_atk->set_base_level(get_base_level());
	status_atk->set_strength(get_strength());
	status_atk->set_dexterity(get_dexterity());
	status_atk->set_luck(get_luck());

	set_weapon_atk(weapon_atk = std::make_shared<WeaponATK>(_entity));
	weapon_atk->set_strength(get_strength());
	weapon_atk->set_dexterity(get_dexterity());

	set_equip_atk(std::make_shared<EquipATK>(_entity));

	set_status_matk(status_matk = std::make_shared<StatusMATK>(_entity));
	status_matk->set_base_level(get_base_level());
	status_matk->set_intelligence(get_intelligence());
	status_matk->set_dexterity(get_dexterity());
	status_matk->set_luck(get_luck());

	set_soft_def(soft_def = std::make_shared<SoftDEF>(_entity));
	soft_def->set_vitality(get_vitality());

	set_soft_mdef(soft_mdef = std::make_shared<SoftMDEF>(_entity));
	soft_mdef->set_base_level(get_base_level());
	soft_mdef->set_intelligence(get_intelligence());
	soft_mdef->set_dexterity(get_dexterity());
	soft_mdef->set_vitality(get_vitality());

	set_hit(hit = std::make_shared<HIT>(_entity));
	hit->set_base_level(get_base_level());
	hit->set_dexterity(get_dexterity());
	hit->set_luck(get_luck());

	set_crit(crit = std::make_shared<CRIT>(_entity));
	crit->set_luck(get_luck());

	set_flee(flee = std::make_shared<FLEE>(_entity));
	flee->set_base_level(get_base_level());
	flee->set_agility(get_agility());
	flee->set_luck(get_luck());
}

//! @brief Registers client-notifiable statuses.
//!
void Status::initialize_notifiable_statuses()
{
	// Status Point Notifiables (ZC_STATUS_CHANGE)
	get_strength()->get_notifier().set_notifiable(get_strength());
	get_agility()->get_notifier().set_notifiable(get_agility());
	get_vitality()->get_notifier().set_notifiable(get_vitality());
	get_intelligence()->get_notifier().set_notifiable(get_intelligence());
	get_dexterity()->get_notifier().set_notifiable(get_dexterity());
	get_luck()->get_notifier().set_notifiable(get_luck());

	// Status Point Cost Notifiables (ZC_COUPLE_STATUS)
	get_strength_cost()->get_notifier().set_notifiable(get_strength_cost());
	get_agility_cost()->get_notifier().set_notifiable(get_agility_cost());
	get_vitality_cost()->get_notifier().set_notifiable(get_vitality_cost());
	get_intelligence_cost()->get_notifier().set_notifiable(get_intelligence_cost());
	get_dexterity_cost()->get_notifier().set_notifiable(get_dexterity_cost());
	get_luck_cost()->get_notifier().set_notifiable(get_luck_cost());

	// Basic Status Notifiables. (Single or Summed/Multiple) (ZC_PAR_CHANGE)
	get_status_point()->get_notifier().register_notifiables(get_status_point());
	get_skill_point()->get_notifier().register_notifiables(get_skill_point());
	get_current_hp()->get_notifier().register_notifiables(get_current_hp());
	get_current_sp()->get_notifier().register_notifiables(get_current_sp());
	get_max_hp()->get_notifier().register_notifiables(get_max_hp());
	get_max_sp()->get_notifier().register_notifiables(get_max_sp());
	get_base_level()->get_notifier().register_notifiables(get_base_level());
	get_job_level()->get_notifier().register_notifiables(get_job_level());
	get_movement_speed()->get_notifier().register_notifiables(get_movement_speed());
	// Sub-statuses.
	get_status_atk()->get_notifier().register_notifiables(get_status_atk());
	get_weapon_atk()->get_notifier().register_notifiables(get_weapon_atk(), get_equip_atk());
	get_status_matk()->get_notifier().register_notifiables(get_status_matk());
	get_soft_def()->get_notifier().register_notifiables(get_soft_def());
	get_soft_mdef()->get_notifier().register_notifiables(get_soft_mdef());
	get_hit()->get_notifier().register_notifiables(get_hit());
	get_crit()->get_notifier().register_notifiables(get_crit());
	get_flee()->get_notifier().register_notifiables(get_flee());
	get_max_weight()->get_notifier().register_notifiables(get_max_weight());
	get_current_weight()->get_notifier().register_notifiables(get_current_weight());

	// Experience Notifiers (ZC_LONG_PAR_CHANGE)
	get_base_experience()->get_notifier().set_notifiable(get_base_experience());
	get_job_experience()->get_notifier().set_notifiable(get_job_experience());
	get_next_base_experience()->get_notifier().set_notifiable(get_next_base_experience());
	get_next_job_experience()->get_notifier().set_notifiable(get_next_job_experience());
}

//! Compute and notify client of sub-statuses
void Status::compute_and_notify()
{
	get_max_weight()->set_base(get_max_weight()->compute());
	get_status_atk()->set_base(get_status_atk()->compute());
	get_weapon_atk()->set_base(get_weapon_atk()->compute());
	get_status_matk()->set_base(get_status_matk()->compute());
	get_soft_def()->set_base(get_soft_def()->compute());
	get_soft_mdef()->set_base(get_soft_mdef()->compute());
	get_hit()->set_base(get_hit()->compute());
	get_crit()->set_base(get_crit()->compute());
	get_flee()->set_base(get_flee()->compute());
}

//! @brief Registers status observers for observable statuses.
void Status::initialize_observable_statuses()
{
	// Register Status Observables
	get_strength()->register_observable(get_strength());
	get_agility()->register_observable(get_agility());
	get_vitality()->register_observable(get_vitality());
	get_intelligence()->register_observable(get_intelligence());
	get_dexterity()->register_observable(get_dexterity());
	get_luck()->register_observable(get_luck());
	get_base_experience()->register_observable(get_base_experience());
	get_job_experience()->register_observable(get_job_experience());
	get_base_level()->register_observable(get_base_level());
	get_job_level()->register_observable(get_job_level());

	// Register Status Observers
	get_strength()->register_observers(get_strength_cost(), get_max_weight(), get_status_atk(), get_weapon_atk());
	get_agility()->register_observers(get_agility_cost(), get_flee());
	get_vitality()->register_observers(get_vitality_cost(), get_soft_def(), get_soft_mdef());
	get_intelligence()->register_observers(get_intelligence_cost(), get_status_matk(), get_soft_mdef());
	get_dexterity()->register_observers(get_dexterity_cost(), get_status_atk(), get_weapon_atk(), get_status_matk(), get_soft_mdef(), get_hit());
	get_luck()->register_observers(get_luck_cost(), get_status_atk(), get_status_matk(), get_hit(), get_crit(), get_flee());
	get_base_level()->register_observers(get_status_point(), get_next_base_experience(), get_status_atk(), get_status_matk(), get_soft_mdef(), get_hit(), get_flee());
	get_job_level()->register_observers(get_skill_point(), get_next_job_experience());
	get_base_experience()->register_observers(get_base_level());
	get_job_experience()->register_observers(get_job_level());
}

uint32_t Status::get_required_statpoints(uint16_t from, uint16_t to)
{
	uint32_t sp = 0;

	for (; from < to; from++)
		sp += (from < 100) ? (2 + (from - 1) / 10) : (16 + 4 * ((from - 100) / 5));

	return sp;
}

uint32_t Status::get_status_total(status_point_type type)
{
	uint32_t value = 0;
	switch (type)
	{
		case STATUS_STRENGTH: value = get_strength()->get_base(); break;
		case STATUS_AGILITY: value = get_agility()->get_base(); break;
		case STATUS_VITALITY: value = get_vitality()->get_base(); break;
		case STATUS_INTELLIGENCE: value = get_intelligence()->get_base(); break;
		case STATUS_DEXTERITY: value = get_dexterity()->get_base(); break;
		case STATUS_LUCK: value = get_luck()->get_base(); break;
		default: return 0;
	}

	return value;
}

/**
 * @brief Increases a status point to a certain limit
 * and returns the current total of the stat.
 * @param type[in] Type of the status point @see status_point_type
 * @param limit[in] Limit to increase the status point to.
 * @return The total base value of the current status point.
 */
uint32_t Status::increase_status_point(status_point_type type, uint16_t limit)
{
	uint32_t value = 0;

	if (limit <= 0 || limit > MAX_STATUS_POINTS)
		return 0;

	if (_entity.expired())
		return 0;

	uint32_t available_points = get_status_point()->get_base();
	uint32_t required_points = 0;

	limit += get_status_total(type);

	do {
		value = get_status_total(type);
		required_points = get_required_statpoints(value + 1, value + 2);

		if (required_points > available_points || value >= MAX_STATUS_POINTS)
			break;

		available_points -= required_points;

		switch (type)
		{
			case STATUS_STRENGTH:
				get_strength()->add_base(1, false);
				break;
			case STATUS_AGILITY:
				get_agility()->add_base(1, false);
				break;
			case STATUS_VITALITY:
				get_vitality()->add_base(1, false);
				break;
			case STATUS_INTELLIGENCE:
				get_intelligence()->add_base(1, false);
				break;
			case STATUS_DEXTERITY:
				get_dexterity()->add_base(1, false);
				break;
			case STATUS_LUCK:
				get_luck()->add_base(1, false);
				break;
			default: return false;
		}

		get_status_point()->set_base(available_points);
	} while (get_status_total(type) < limit);

	return get_status_total(type);
}

