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
 * This is proprietary software. Unauthorized copying,
 * distribution, or modification of this file, via any
 * medium, is strictly prohibited. All rights reserved.
 **************************************************/

#include "Server/Zone/Game/Units/Mob/Hostile/Monster.hpp"
#include "Server/Zone/Game/Units/Unit.hpp"
#include "Server/Zone/Game/Units/Traits/Status.hpp"
#include "Server/Zone/Game/Units/Player/Player.hpp"
#include "Server/Zone/Game/Units/Player/Assets/Inventory.hpp"
#include "Server/Zone/Game/StaticDB/JobDB.hpp"
#include "Server/Zone/Game/StaticDB/ExpDB.hpp"
#include "Server/Zone/Game/Units/Traits/Status.hpp"
#include "Server/Zone/Definitions/UnitDefinitions.hpp"
#include "Server/Zone/Session/ZoneSession.hpp"
#include "Server/Zone/Interface/ZoneClientInterface.hpp"

using namespace Horizon::Zone;
using namespace Horizon::Zone::Traits;

void s_attribute_change_values::ApplyLiveAttribute::update_with_live_attribute(s_attribute_change_values *change)
{
	if (change->get_base() != _attr->get_base())
		change->set_base(_attr->get_base());
	if (change->get_equip() != _attr->get_equip())
		change->set_equip(_attr->get_equip());
	if (change->get_status() != _attr->get_status())
		change->set_status(_attr->get_status());

	assert(change->get_base() == _attr->get_base());
	assert(change->get_equip() == _attr->get_equip());
	assert(change->get_status() == _attr->get_status());
}
s_attribute_change_values::s_attribute_min_max::s_attribute_min_max(int32_t min, Attribute *attr) : s_min_max(0, attr->total()), _attr(attr) {}

void s_attribute_change_values::s_attribute_min_max::update_with_live_attribute()
{
	if (get_max() != _attr->total())
	{
		set_max(_attr->total());
	}

	assert(get_max() == _attr->total());
}

void PermanentChanges::add_change(s_attribute_change_values change, std::string source)
{
	_changes.push_back({ change, source });
}

void PermanentChanges::remove_change(std::string source)
{
	_changes.erase(std::remove_if(_changes.begin(), _changes.end(), [source](s_permanent_change const &change) { return change.source == source; }), _changes.end());
}

void PermanentChanges::apply(bool notify)
{
	for (auto &change : _changes)
	{
		if (change.change.get_base() > 0)
			_attr->add_base(change.change.get_base(), notify);
		else
			_attr->sub_base(change.change.get_base(), notify);
		
		if (change.change.get_equip() > 0)
			_attr->add_equip(change.change.get_equip(), notify);
		else
			_attr->sub_equip(change.change.get_equip(), notify);
		
		if (change.change.get_status() > 0)
			_attr->add_status(change.change.get_status(), notify);
		else
			_attr->sub_status(change.change.get_status(), notify);
	}
}

void TemporaryChanges::add_change(s_attribute_change_values change, uint64_t duration, std::string source)
{
	_changes.push_back({ change, duration, source });
}

void TemporaryChanges::remove_change(std::string source)
{
	_changes.erase(std::remove_if(_changes.begin(), _changes.end(), [source](s_temporary_change const &change) { return change.source == source; }), _changes.end());
}

void TemporaryChanges::apply(bool notify)
{
	for (auto &change : _changes)
	{
		if (change.change.get_base() > 0)
			_attr->add_base(change.change.get_base(), notify);
		else
			_attr->sub_base(change.change.get_base(), notify);
		
		if (change.change.get_equip() > 0)
			_attr->add_equip(change.change.get_equip(), notify);
		else
			_attr->sub_equip(change.change.get_equip(), notify);
		
		if (change.change.get_status() > 0)
			_attr->add_status(change.change.get_status(), notify);
		else
			_attr->sub_status(change.change.get_status(), notify);
	}
}

void TemporaryChanges::update(uint64_t delta)
{
	for (auto &change : _changes)
	{
		if (std::chrono::duration_cast<std::chrono::milliseconds>(change.start_time.time_since_epoch() + std::chrono::milliseconds(change.duration)).count() < delta)
		{
			remove_change(change.source);
			_attr->recalculate(true);
			continue;
		}
	}
}

void PeriodicChanges::add_change(s_attribute_change_values change, uint64_t duration, uint64_t interval, std::string source)
{
	_changes.push_back({ change, duration, interval, source });
}

void PeriodicChanges::remove_change(std::string source)
{
	_changes.erase(std::remove_if(_changes.begin(), _changes.end(), [source](s_periodic_change const &change) { return change.source == source; }), _changes.end());
}

void PeriodicChanges::update(uint64_t delta)
{
	for (auto &change : _changes)
	{
		if (change.duration && std::chrono::duration_cast<std::chrono::milliseconds>(change.start_time.time_since_epoch() + std::chrono::milliseconds(change.duration)).count() < delta)
		{
			remove_change(change.source);
			continue;
		}

		if (std::chrono::duration_cast<std::chrono::milliseconds>(change.last_update.time_since_epoch() + std::chrono::milliseconds(change.interval)).count() < delta)
		{
			std::function<bool(int, int, int)> over_min = [](int attr, int change, int min) { return (attr - change) < min; };
			std::function<bool(int, int, int)> over_max = [](int attr, int change, int max) { return (attr + change) > max; };

			if (_attr->unit() && _attr->unit()->is_dead() == true)
				return;

			change.change.update_with_live_attribute();

			bool changed = false;
			if (change.change.get_base() > 0) {
				if (!over_max(_attr->get_base(), change.change.get_base(), change.change.get_max())) {
					_attr->add_base(change.change.get_base(), false);
					changed = true;
				} else {
					_attr->add_base(change.change.get_max() - _attr->get_base(), false);
					changed = (change.change.get_max() - _attr->get_base() > 0);
				}
			}
			else if (change.change.get_base() < 0) {
				if (!over_min(_attr->get_base(), change.change.get_base(), change.change.get_min())) {
					_attr->sub_base(change.change.get_base(), false);
					changed = true;
				} else {
					_attr->sub_base(_attr->get_base() - change.change.get_min(), false);
					changed = (_attr->get_base() - change.change.get_min() > 0);
				}
			}

			if (change.change.get_equip() > 0) {
				if (!over_max(_attr->get_equip(), change.change.get_equip(), change.change.get_max())) {
					_attr->add_equip(change.change.get_equip(), false);
					changed = true;
				} else {
					_attr->add_equip(change.change.get_max() - _attr->get_equip(), false);
					changed = (change.change.get_max() - _attr->get_equip()) > 0;
				}
			}
			else if (change.change.get_equip() < 0) {
				if (!over_min(_attr->get_equip(), change.change.get_equip(), change.change.get_min())) {
					_attr->sub_equip(change.change.get_equip(), false);
					changed = true;
				} else {
					_attr->sub_equip(_attr->get_equip() - change.change.get_min(), false);
					changed = (_attr->get_equip() - change.change.get_min()) > 0;
				}
			}

			if (change.change.get_status() > 0) {
				if (!over_max(_attr->get_status(), change.change.get_status(), change.change.get_max())) {
					_attr->add_status(change.change.get_status(), false);
					changed = true;
				} else {
					_attr->add_status(change.change.get_max() - _attr->get_status(), false);
					changed = (change.change.get_max() - _attr->get_status()) > 0;
				}
			}
			else if (change.change.get_status() < 0) {
				if (!over_min(_attr->get_status(), change.change.get_status(), change.change.get_min())) {
					_attr->sub_status(change.change.get_status(), false);
					changed = true;
				} else {
					_attr->sub_status(_attr->get_status() - change.change.get_min(), false);
					changed = (_attr->get_status() - change.change.get_min()) > 0;
				}
			}

			_attr->compute();

			if (changed)
				change.change.client_notify_function(change.change);

			change.last_update = std::chrono::high_resolution_clock::now();
		}
	}
}

void Attribute::add_base(int32_t val, bool notify) { 
	_base_val += val;
	if (notify) this->notify();
}
void Attribute::sub_base(int32_t val, bool notify) { 
	_base_val -= std::min(_base_val, val);
	if (notify) this->notify();
}
void Attribute::add_equip(int32_t val, bool notify) { 
	_equip_val += val;
	if (notify) this->notify();
}
void Attribute::sub_equip(int32_t val, bool notify) { 
	_equip_val -= std::min(_equip_val, val);
	if (notify) this->notify();
}
void Attribute::add_status(int32_t val, bool notify) { 
	_status_val += val;
	if (notify) this->notify();
}
void Attribute::sub_status(int32_t val, bool notify) { 
	_status_val -= std::min(_status_val, val);
	if (notify) this->notify();
}

void Attribute::notify()
{
	if (unit()->type() != UNIT_PLAYER) 
		return;
		
	switch(_status_point_type)
	{
	case STATUS_POINT_INVALID:
		break;
	case STATUS_MOVEMENT_SPEED:
	case STATUS_MAX_WEIGHT:
	case STATUS_CURRENT_WEIGHT:      
	case STATUS_BASELEVEL:    
	case STATUS_JOBLEVEL:
	case STATUS_KARMA:
	case STATUS_MANNER:     
	case STATUS_STATUSPOINT:
	case STATUS_SKILLPOINT:   
	case STATUS_HIT:
	case STATUS_FLEE:
	case STATUS_PERFECT_DODGE:
	case STATUS_MAXHP:    
	case STATUS_MAXSP:        
	case STATUS_CURRENTHP:
	case STATUS_CURRENTSP:        
	case STATUS_ASPD:       
	case STATUS_STATUS_ATK:
	case STATUS_EQUIP_ATK:
	case STATUS_EQUIP_MATK:
	case STATUS_STATUS_MATK:
	case STATUS_SOFT_DEF:
	case STATUS_HARD_DEF:
	case STATUS_SOFT_MDEF:
	case STATUS_HARD_MDEF:
	case STATUS_ZENY:
	{
		unit()->downcast<Horizon::Zone::Units::Player>()->get_session()->clif()->notify_compound_attribute_update(_status_point_type, total());
	}
	break;
	case STATUS_CRITICAL: 
	{
		unit()->downcast<Horizon::Zone::Units::Player>()->get_session()->clif()->notify_compound_attribute_update(_status_point_type, total() / 10);
	} 
	break;
	case STATUS_BASEEXP:
	case STATUS_JOBEXP:
	case STATUS_NEXTBASEEXP:
	case STATUS_NEXTJOBEXP:
	{
		unit()->downcast<Horizon::Zone::Units::Player>()->get_session()->clif()->notify_experience_update(_status_point_type, total());
	}
	break;
	case STATUS_STRENGTH_COST:
	case STATUS_AGILITY_COST:
	case STATUS_VITALITY_COST:
	case STATUS_INTELLIGENCE_COST:
	case STATUS_DEXTERITY_COST:
	case STATUS_LUCK_COST:
	{
		unit()->downcast<Horizon::Zone::Units::Player>()->get_session()->clif()->notify_required_attribute_update(_status_point_type, total());
	}
	break;
	case STATUS_ATTACKRANGE:
	{
		unit()->downcast<Horizon::Zone::Units::Player>()->get_session()->clif()->notify_attack_range_update(total());
	}
	break;            
	case STATUS_STRENGTH:
	case STATUS_AGILITY:
	case STATUS_VITALITY:
	case STATUS_INTELLIGENCE:
	case STATUS_DEXTERITY:
	case STATUS_LUCK:
	{
		unit()->downcast<Horizon::Zone::Units::Player>()->get_session()->clif()->notify_attribute_update(_status_point_type, get_base(), get_status() + get_equip());
	}
	break;
	case STATUS_CARTINFO:
	{
		unit()->downcast<Horizon::Zone::Units::Player>()->get_session()->clif()->notify_cart_weight_update();
	}
	break;
	default:
		HLog(debug) << "Tried to send attribute update for status point type " << _status_point_type << " which is not implemented yet.";
	break;
	}
}
template <class STATUS_COST_T, class STATUS_T>
void set_new_point_cost(std::shared_ptr<Horizon::Zone::Unit> unit, STATUS_COST_T *cost_t, STATUS_T *stat)
{
	if (unit == nullptr || stat == nullptr)
		return;

	int32_t new_cost = unit->status()->get_required_statpoints(stat->get_base(), stat->get_base() + 1);

	cost_t->set_base(new_cost);
}

void StrengthPointCost::on_observable_changed(Strength *str)
{
	set_new_point_cost(unit(), this, str);
}

void AgilityPointCost::on_observable_changed(Agility *agi)
{
	set_new_point_cost(unit(), this, agi);
}

void VitalityPointCost::on_observable_changed(Vitality *vit)
{
	set_new_point_cost(unit(), this, vit);
}

void IntelligencePointCost::on_observable_changed(Intelligence *_int)
{
	set_new_point_cost(unit(), this, _int);
}

void DexterityPointCost::on_observable_changed(Dexterity *dex)
{
	set_new_point_cost(unit(), this, dex);
}

void LuckPointCost::on_observable_changed(Luck *luk)
{
	set_new_point_cost(unit(), this, luk);
}

void BaseLevel::on_observable_changed(BaseExperience *bexp)
{
	if (unit() == nullptr || bexp == nullptr)
		return;

	std::shared_ptr<const job_config_data> job = JobDB->get_job_by_id(unit()->job_id());
	std::shared_ptr<const exp_group_data> bexpg = ExpDB->get_exp_group(job->base_exp_group, EXP_GROUP_TYPE_BASE);

	if (get_base() >= bexpg->max_level)
		return;
		
	if (bexp->get_base() >= unit()->status()->next_base_experience()->get_base()) {
		int carried_over = bexp->get_base() - unit()->status()->next_base_experience()->get_base();
		add_base(1);
		bexp->set_base(carried_over);
	}
}

void JobLevel::on_observable_changed(JobExperience *jexp)
{
	if (unit() == nullptr || jexp == nullptr)
		return;

	std::shared_ptr<const job_config_data> job = JobDB->get_job_by_id(unit()->job_id());
	std::shared_ptr<const exp_group_data> jexpg = ExpDB->get_exp_group(job->job_exp_group, EXP_GROUP_TYPE_JOB);

	if (get_base() >= jexpg->max_level)
		return;

	if (jexp->get_base() >= unit()->status()->next_job_experience()->get_base()) {
		int carried_over = jexp->get_base() - unit()->status()->next_job_experience()->get_base();
		add_base(1);
		jexp->set_base(carried_over);
	}
}

int32_t MaxHP::compute()
{
	std::shared_ptr<const job_config_data> job = JobDB->get_job_by_id(unit()->job_id());
	int val = 0;

	if (job == nullptr)
		return 0;

	job_class_mask job_mask = JobDB->job_id_to_mask((job_class_type) job->id);
	
	int base_level = _blvl->total();
	val += job->hp_table[base_level - 1];
	
	if ((job_mask & JMASK_EXPANDED) == JOB_SUPER_NOVICE && base_level >= 99)
		val += 2000; //Supernovice lvl99 hp bonus.
		
	if ((job_mask & JMASK_EXPANDED_2_1) == JOB_SUPER_NOVICE_E && base_level >= 150)
		val += 2000; //Extented Supernovice lvl150 hp bonus.

	if ((job_mask & JMASK_TRANS) != 0)
		val += val * 25 / 100; //Trans classes get a 25% hp bonus
	else if ((job_mask & JMASK_BABY) != 0)
		val = val * 70 / 100; //Baby classes get a 30% hp penalty

	val += val * unit()->status()->vitality()->total() / 100; // +1% per each point of VIT

	set_base(val);

	return total();
}

int32_t MaxSP::compute()
{
	std::shared_ptr<const job_config_data> job = JobDB->get_job_by_id(unit()->job_id());
	int val = 0;

	if (job == nullptr)
		return 0;

	job_class_mask job_mask = JobDB->job_id_to_mask((job_class_type) job->id);
	
	int base_level = _blvl->total();

	val += job->sp_table[base_level - 1];

	if ((job_mask & JMASK_TRANS) != 0)
		val += val * 25 / 100;
	else if ((job_mask & JMASK_BABY) != 0)
		val = val * 70 / 100;

	val += val * _int->total() / 100;

	set_base(val);

	return total();
}

void CurrentHP::damage(int damage)
{
	if (damage >= total())
		set_base(0);
	else
		sub_base(damage);
}

void CurrentSP::reduce(int amount)
{
	if (amount >= total())
		set_base(0);
	else
		sub_base(amount);
}

void NextBaseExperience::on_observable_changed(BaseLevel *blvl)
{
	if (unit() == nullptr || blvl == nullptr)
		return;

	std::shared_ptr<const job_config_data> job = JobDB->get_job_by_id(unit()->job_id());
	std::shared_ptr<const exp_group_data> bexpg = ExpDB->get_exp_group(job->base_exp_group, EXP_GROUP_TYPE_BASE);

	if (blvl->get_base() >= bexpg->max_level)
		return;

	set_base(bexpg->exp[blvl->get_base() - 1]);
}

void NextJobExperience::on_observable_changed(JobLevel *jlvl)
{
	if (unit() == nullptr || jlvl == nullptr)
		return;

	std::shared_ptr<const job_config_data> job = JobDB->get_job_by_id(unit()->job_id());
	std::shared_ptr<const exp_group_data> jexpg = ExpDB->get_exp_group(job->job_exp_group, EXP_GROUP_TYPE_JOB);

	if (jlvl->get_base() >= jexpg->max_level)
		return;

	set_base(jexpg->exp[jlvl->get_base() - 1]);
}

void StatusPoint::on_observable_changed(BaseLevel *blvl)
{
	if (unit() == nullptr || blvl == nullptr)
		return;

	add_base(ExpDB->get_status_point(blvl->get_base()) - ExpDB->get_status_point(blvl->get_base() - 1));
}

void SkillPoint::on_observable_changed(JobLevel *jlvl)
{
	if (unit() == nullptr || jlvl == nullptr)
		return;

	add_base(1);
}

void SkillPoint::set_base(int32_t val, bool notify_client)
{
	Attribute::set_base(val, notify_client);
}

int32_t MaxWeight::compute()
{
	if (unit() == nullptr || _str == nullptr)
		return 0;

	std::shared_ptr<const job_config_data> job = JobDB->get_job_by_id(unit()->job_id());

	set_base(job->max_weight + _str->get_base() * 300);
	
	return total();
}

void MovementSpeed::set_base(int32_t val, bool notify_client)
{
	Attribute::set_base(val, notify_client);
}

int32_t StatusATK::compute()
{
	int32_t blvl = 1, str = 1, dex = 1, luk = 1;

	if (_blvl != nullptr)
		blvl = _blvl->get_base();

	if (_str != nullptr)
		str = _str->total();

	if (_dex != nullptr)
		dex = _dex->total();

	if (_luk != nullptr)
		luk = _luk->total();

	// Ranged: floor[(BaseLevel ÷ 4) + (Str ÷ 5) + Dex + (Luk ÷ 3)]
	if (((1ULL << _weapon_type) & IT_WTM_RANGED) & ~(1ULL<<IT_WT_FIST))
		set_base(dex + (blvl / 4) + (str / 5) + (luk / 3));
	else // Melee: floor[(BaseLevel ÷ 4) + Str + (Dex ÷ 5) + (Luk ÷ 3)]
		set_base(str + (blvl / 4) + (dex / 5) + (luk / 3));
	
	return total();
}

int32_t EquipMATK::compute()
{
	if (unit() == nullptr || unit()->type() != UNIT_PLAYER)
		return 0;

	std::shared_ptr<Horizon::Zone::Units::Player> player = unit()->downcast<Horizon::Zone::Units::Player>();
	EquipmentListType const &equipments = player->inventory()->equipments();
	
	std::shared_ptr<const item_entry_data> lhw = equipments[IT_EQPI_HAND_L].second.lock();
	std::shared_ptr<const item_entry_data> rhw = equipments[IT_EQPI_HAND_R].second.lock();
	
	set_base(0, false);

	if (lhw) add_base(lhw->config->magic_atk);
	if (rhw) add_base(rhw->config->magic_atk);
	
	int variance = 0;
	
	if (rhw) 
		variance = total() * rhw->config->level.weapon / 10;

	set_min(total() - variance);
	set_max(total() + variance);
	
	return total();
}

int32_t StatusMATK::compute()
{
	int32_t blvl = 1, int_ = 1, dex = 1, luk = 1;

	if (_blvl != nullptr)
		blvl = _blvl->get_base();

	if (_int != nullptr)
		int_ = _int->total();

	if (_dex != nullptr)
		dex = _dex->total();

	if (_luk != nullptr)
		luk = _luk->total();

	// floor[floor[BaseLevel ÷ 4] + Int + floor[Int ÷ 2] + floor[Dex ÷ 5] + floor[Luk ÷ 3]]
	set_base(int_ + (blvl / 4) + (int_ / 2) + (dex / 5) + (luk / 3));
	
	return total();
}

int32_t SoftDEF::compute()
{
	int32_t vit = 1;

	if (_vit != nullptr)
		vit = _vit->total();

	int32_t base_level = 1;

	if (_blvl != nullptr)
		base_level = _blvl->get_base();

	int32_t agi = 1;

	if (_agi != nullptr)
		agi = _agi->total();

	// /base level + (every 2 vit = +1 def) + (every 5 agi = +1 def)
	set_base(((float)base_level + vit) / 2 + (unit()->type() == UNIT_PLAYER ? ((float)agi / 5) : 0));
	
	return total();
}

int32_t HardDEF::compute()
{
	if (unit()->type() == UNIT_PLAYER) {
		std::shared_ptr<Horizon::Zone::Units::Player> player = unit()->downcast<Horizon::Zone::Units::Player>();
		EquipmentListType const &equipments = player->inventory()->equipments();
		set_base(0, false);
		for (auto &equipment : equipments) {
			std::shared_ptr<const item_entry_data> armor = equipment.second.lock();
			if (armor != nullptr) {
				// ArmorDef + ShieldDef + CardDef + RefineDef + OverUpgradeDef
				add_base(armor->config->defense);
			}
		}
	}

	return total();
}

int32_t HardMDEF::compute()
{
	return total();
}

int32_t SoftMDEF::compute()
{
	int32_t blvl = 1, int_ = 1, dex = 1, vit = 1;

	if (_blvl != nullptr)
		blvl = _blvl->get_base();

	if (_int != nullptr)
		int_ = _int->total();

	if (_dex != nullptr)
		dex = _dex->total();

	if (_vit != nullptr)
		vit = _vit->total();

	// INT + VIT ÷ 5 + DEX ÷ 5 + BaseLv ÷ 4
	set_base(int_ + (vit / 5) + (dex / 5) + (blvl / 4));
	
	return total();
}

int32_t HIT::compute()
{
	int32_t blvl = 1, dex = 1, luk = 1;

	if (_blvl != nullptr)
		blvl = _blvl->get_base();

	if (_dex != nullptr)
		dex = _dex->total();

	if (_luk != nullptr)
		luk = _luk->total();

	// 175 + BaseLv + DEX + Floor(LUK ÷ 3) + Bonus
	set_base(175 + blvl + dex + (luk / 3));
	
	return total();
}

int32_t CRIT::compute()
{
	int32_t luk = 1;

	if (_luk != nullptr)
		luk = _luk->total();

	// LUK × 0.3 + Bonus
	set_base(10 + (luk * 10 / 3));
	
	return total();
}

//! @brief Computes FLEE status based on agility, luck and Base Level.
//! FLEE = 100 + BaseLv + AGI + Floor(LUK ÷ 5)
int32_t FLEE::compute()
{
	int32_t blvl = 1, agi = 1, luk = 1;

	if (_agi != nullptr)
		agi = _agi->total();

	if (_blvl != nullptr)
		blvl = _blvl->get_base();

	if (_luk != nullptr)
		luk = _luk->total();

	set_base(100 + blvl + agi + (luk / 5));
	
	return total();
}

//! @brief Computes the EquipATK property of physical attacks.
//! EquipATK = floor[((BaseWeaponDamage + Variance + StatBonus + RefinementBonus + OverUpgradeBonus) × SizePenaltyMultiplier]
int32_t EquipATK::compute()
{
	int32_t str = 1, dex = 1;

	if (unit() == nullptr || unit()->type() != UNIT_PLAYER)
		return 0;

	if (_str != nullptr)
		str = _str->total();

	if (_dex != nullptr)
		dex = _dex->total();

	std::shared_ptr<Horizon::Zone::Units::Player> player = unit()->downcast<Horizon::Zone::Units::Player>();
	EquipmentListType const &equipments = player->inventory()->equipments();

	std::shared_ptr<const item_entry_data> lhw = equipments[IT_EQPI_HAND_L].second.lock();
	std::shared_ptr<const item_entry_data> rhw = equipments[IT_EQPI_HAND_R].second.lock();

	if (lhw && lhw->type == IT_TYPE_WEAPON) {
		// Base Weapon Damage
		_left_hand_val = lhw->config->attack;
		// StatBonus = BaseWeaponDamage × (Melee: Str / Ranged: Dex) ÷ 200
		_left_hand_val += (lhw->config->attack * (((1ULL << lhw->config->sub_type.weapon_t) & IT_WTM_MELEE) ? str : dex) / 200.00f);
	} else {
		_left_hand_val = 0;
	}

	if (rhw && rhw->type == IT_TYPE_WEAPON) {
		// Base Weapon Damage
		_right_hand_val = rhw->config->attack;
		// StatBonus = BaseWeaponDamage × (Melee: Str / Ranged: Dex) ÷ 200
		_right_hand_val += (rhw->config->attack * ((( 1ULL << rhw->config->sub_type.weapon_t) & IT_WTM_MELEE) ? str : dex) / 200.00f);
	} else {
		_right_hand_val = 0;
	}

	set_base(_left_hand_val + _right_hand_val);

	return total();
}

int32_t EquipATK::compute_variance(int8_t weapon_lvl, int32_t base_weapon_dmg)
{
	srand(time(0));

	return floor(((rand() % 1000 + (-500)) / 10000.f) * weapon_lvl * base_weapon_dmg);
}

int32_t AttackSpeed::compute()
{
	float temp_aspd = 0.00f;
	int amotion = 0;

	if (unit()->type() == UNIT_PLAYER) {
		EquipmentListType const &equipments = unit()->downcast<Horizon::Zone::Units::Player>()->inventory()->equipments();
		std::shared_ptr<const item_entry_data> rhw = equipments[IT_EQPI_HAND_R].second.lock();
		std::shared_ptr<const item_entry_data> lhw = equipments[IT_EQPI_HAND_L].second.lock();
		std::shared_ptr<const job_config_data> job = JobDB->get_job_by_id(unit()->job_id());

		item_weapon_type rhw_type, lhw_type;

		if (rhw == nullptr) { 
			rhw_type = IT_WT_FIST;
		} else {
			rhw_type = rhw->config->sub_type.weapon_t;
		}

		amotion = job->weapon_base_aspd[rhw_type];

		if (rhw_type > IT_WT_SINGLE_MAX && lhw != nullptr) {
			lhw_type = lhw->config->sub_type.weapon_t;
			amotion += job->weapon_base_aspd[lhw_type] / 4; // Dual-wield
		}

		if (_dex == nullptr || _blvl == nullptr || _agi == nullptr) {
			HLog(error) << "AttackSpeed::compute: Couldn't compute... Dex, Blvl or Agi was null.";
			return amotion;
		}

		switch(rhw_type) {
			case IT_WT_BOW:
			case IT_WT_MUSICAL:
			case IT_WT_WHIP:
			case IT_WT_REVOLVER:
			case IT_WT_RIFLE:
			case IT_WT_GATLING:
			case IT_WT_SHOTGUN:
			case IT_WT_GRENADE:
				temp_aspd = _dex->get_base() * _dex->get_base() / 7.0f + _agi->get_base() * _agi->get_base() * 0.5f;
				break;
			default:
				temp_aspd = _dex->get_base() * _dex->get_base() / 5.0f + _agi->get_base() * _agi->get_base() * 0.5f;
				break;
		}

		temp_aspd = (float)(sqrt(temp_aspd) * 0.25f) + 196;

#define ASPD_FROM_STATUS_EFFECTS 0
#define ASPD_FROM_SKILLS 0
		amotion = (int)(temp_aspd + ((float)((ASPD_FROM_STATUS_EFFECTS + ASPD_FROM_SKILLS) * _agi->get_base() / 200)) - std::min(amotion, 200));
		amotion += (std::max(0xc3 - amotion, 2) * (ASPD_FROM_STATUS_EFFECTS)) / 100;
		amotion = std::min(amotion, MAX_ATTACK_SPEED);
		amotion = 10 * (200 - amotion);
#undef ASPD_FROM_STATUS_EFFECTS
#undef ASPD_FROM_SKILLS
	}

	set_base(amotion);

	return total();
}

int32_t HPRegeneration::compute()
{
	if (unit()->type() == UNIT_PLAYER) {
		int vit = _vit->total();
		int max_hp = _max_hp->total();
		set_base(1 + (vit/5) + (max_hp/200));
	}

	return total();
}

int32_t SPRegeneration::compute()
{
	if (unit()->type() == UNIT_PLAYER) {
		int int_ = _int->total();
		int max_sp = _max_sp->total();
		set_base(1 + (int_/6) + (max_sp/100));
		if (int_ >= 120)
			add_base(((int_ - 120) >> 1) + 4);
	}

	return total();
}

int32_t AttackRange::compute()
{
	if (unit()->type() == UNIT_PLAYER) {
		EquipmentListType const &equipments = unit()->downcast<Horizon::Zone::Units::Player>()->inventory()->equipments();
		
		if (equipments[IT_EQPI_HAND_R].second.expired() == true)
			return 1;

		std::shared_ptr<const item_entry_data> rhw = equipments[IT_EQPI_HAND_R].second.lock();
		
		if (rhw == nullptr || rhw->config == nullptr)
			return 1;

		set_base(rhw->config->attack_range);

	} else if (unit()->type() == UNIT_MONSTER) {
		set_base(unit()->downcast<Horizon::Zone::Units::Monster>()->monster_config()->attack_range);
	}

	return total();
}

int32_t MobAttackDamage::compute()
{
	set_min(_blvl->total() + _str->total() + (_cw_atk->total() * 8 / 10));
	set_max(_blvl->total() + _str->total() + (_cw_atk->total() * 12 / 10));

	return std::rand() % ((_max - _min + 1) + _min);
}

int32_t MobMagicAttackDamage::compute()
{
	set_min(_blvl->total() + _int->total() + (_cw_atk->total() * 7 / 10));
	set_max(_blvl->total() + _int->total() + (_cw_atk->total() * 13 / 10));

	return std::rand() % (_max - _min + 1) + _min;
}

int32_t AttackDelay::compute()
{
	if (unit()->type() == UNIT_PLAYER)
		set_base(2 * _aspd->total());
	else if (unit()->type() == UNIT_MONSTER)
		set_base(unit()->downcast<Horizon::Zone::Units::Monster>()->monster_config()->attack_delay);

	return total();
}

int32_t DamageWalkDelay::compute()
{
	if (unit()->type() == UNIT_PLAYER)
		set_base(800 - _agi->get_base() * 4);
	else if (unit()->type() == UNIT_MONSTER)
		set_base(unit()->downcast<Horizon::Zone::Units::Monster>()->monster_config()->damage_motion);

	return total();
}

int32_t WeaponAttackLeft::compute()
{
	EquipmentListType const &equipments = unit()->downcast<Horizon::Zone::Units::Player>()->inventory()->equipments();
	
	if (equipments[IT_EQPI_HAND_L].second.expired() == true)
		return 0;
	
	set_base(equipments[IT_EQPI_HAND_L].second.lock()->config->attack, false);

	return total();
}

int32_t WeaponAttackCombined::compute()
{
	set_base(_watk_left->total() + _watk_right->total());

	return total();
}

int32_t WeaponAttackRight::compute()
{
	EquipmentListType const &equipments = unit()->downcast<Horizon::Zone::Units::Player>()->inventory()->equipments();
	
	if (equipments[IT_EQPI_HAND_R].second.expired() == true)
		return 0;
	
	set_base(equipments[IT_EQPI_HAND_R].second.lock()->config->attack, false);

	return total();
}

int32_t BaseAttack::compute()
{
	if (unit()->type() == UNIT_PLAYER) {
		bool melee = true;
		EquipmentListType const &equipments = unit()->downcast<Horizon::Zone::Units::Player>()->inventory()->equipments();
		std::shared_ptr<const item_entry_data> rhw = nullptr;

		if (!equipments[IT_EQPI_HAND_R].second.expired()) {
			rhw = equipments[IT_EQPI_HAND_R].second.lock();

			switch (rhw->config->sub_type.weapon_t)
			{
			case IT_WT_BOW:
			case IT_WT_MUSICAL:
			case IT_WT_WHIP:
			case IT_WT_REVOLVER:
			case IT_WT_RIFLE:
			case IT_WT_GATLING:
			case IT_WT_SHOTGUN:
			case IT_WT_GRENADE:
				melee = false;
			default:
				break;
			}
		}
		
		set_base((melee ? _str->total() : _dex->total()) + (float) ((melee ? _dex->get_base() : _str->total()) / 5) + (float) (_luk->get_base() / 3) + (_blvl->get_base() / 4));
	}
	else if (unit()->type() == UNIT_MONSTER)
		set_base(_str->total() + _blvl->get_base());

	return total();
}