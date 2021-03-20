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

#include "Server/Zone/Game/Entities/Player/Player.hpp"
#include "Server/Zone/Game/Entities/Player/Assets/Inventory.hpp"
#include "Server/Zone/Game/StaticDB/JobDB.hpp"
#include "Server/Zone/Game/StaticDB/ExpDB.hpp"
#include "Server/Zone/Game/StaticDB/ItemDB.hpp"
#include "Server/Zone/Game/Entities/Traits/Status.hpp"
#include "Server/Common/Definitions/EntityDefinitions.hpp"
#include "Server/Zone/Session/ZoneSession.hpp"
#include "Server/Zone/Interface/ZoneClientInterface.hpp"
#include "Core/Logging/Logger.hpp"

using namespace Horizon::Zone;
using namespace Horizon::Zone::Entities::Traits;

template <class STATUS_COST_T, class STATUS_T>
void set_new_point_cost(std::shared_ptr<Horizon::Zone::Entity> entity, STATUS_COST_T *cost_t, std::weak_ptr<STATUS_T> stat)
{
	std::shared_ptr<STATUS_T> sstat = stat.lock();
	if (!entity || !sstat)
		return;

	int32_t new_cost = entity->status()->get_required_statpoints(sstat->get_base(), sstat->get_base() + 1);

	cost_t->set_base(new_cost);
}

void StrengthPointCost::on_observable_changed(std::weak_ptr<Strength> str)
{
	set_new_point_cost(get_entity(), this, str);
}

void AgilityPointCost::on_observable_changed(std::weak_ptr<Agility> agi)
{
	set_new_point_cost(get_entity(), this, agi);
}

void VitalityPointCost::on_observable_changed(std::weak_ptr<Vitality> vit)
{
	set_new_point_cost(get_entity(), this, vit);
}

void IntelligencePointCost::on_observable_changed(std::weak_ptr<Intelligence> _int)
{
	set_new_point_cost(get_entity(), this, _int);
}

void DexterityPointCost::on_observable_changed(std::weak_ptr<Dexterity> dex)
{
	set_new_point_cost(get_entity(), this, dex);
}

void LuckPointCost::on_observable_changed(std::weak_ptr<Luck> luk)
{
	set_new_point_cost(get_entity(), this, luk);
}

void BaseLevel::on_observable_changed(std::weak_ptr<BaseExperience> wbexp)
{
	std::shared_ptr<BaseExperience> bexp = wbexp.lock();

	if (get_entity() == nullptr || wbexp.expired())
		return;

	if (get_base() >= MAX_LEVEL)
		return;

	if (bexp->get_base() == get_entity()->status()->next_base_experience()->get_base()) {
		add_base(1);
		bexp->set_base(0);
	}
}

void JobLevel::on_observable_changed(std::weak_ptr<JobExperience> wjexp)
{
	std::shared_ptr<JobExperience> jexp = wjexp.lock();

	if (get_entity() == nullptr || wjexp.expired())
		return;

	if (jexp->get_base() == get_entity()->status()->next_job_experience()->get_base()) {
		add_base(1);
		jexp->set_base(0);
	}
}

void NextBaseExperience::on_observable_changed(std::weak_ptr<BaseLevel> wblvl)
{
	if (get_entity() == nullptr || wblvl.expired())
		return;

	std::shared_ptr<BaseLevel> blvl = wblvl.lock();
	std::shared_ptr<const job_config_data> job = JobDB->get_job_by_id(get_entity()->job_id());
	std::shared_ptr<const exp_group_data> bexpg = ExpDB->get_exp_group(job->base_exp_group, EXP_GROUP_TYPE_BASE);

	set_base(bexpg->exp[blvl->get_base() - 1]);
}

void NextJobExperience::on_observable_changed(std::weak_ptr<JobLevel> jlvl)
{
	if (get_entity() == nullptr || jlvl.expired())
		return;

	std::shared_ptr<const job_config_data> job = JobDB->get_job_by_id(get_entity()->job_id());
	std::shared_ptr<const exp_group_data> jexpg = ExpDB->get_exp_group(job->job_exp_group, EXP_GROUP_TYPE_JOB);

	set_base(jexpg->exp[get_base() - 1]);
}

void StatusPoint::on_observable_changed(std::weak_ptr<BaseLevel> wblvl)
{
	std::shared_ptr<BaseLevel> blvl = wblvl.lock();

	if (get_entity() == nullptr || wblvl.expired())
		return;

	add_base(ExpDB->get_status_point(blvl->get_base()) - ExpDB->get_status_point(*blvl - 1));
}

void SkillPoint::on_observable_changed(std::weak_ptr<JobLevel> wjlvl)
{
	std::shared_ptr<JobLevel> jlvl = wjlvl.lock();

	if (get_entity() == nullptr || wjlvl.expired())
		return;

	add_base(1);
}

int32_t MaxWeight::compute(bool notify)
{
	if (get_entity() == nullptr || _str.expired())
		return 0;

	std::shared_ptr<const job_config_data> job = JobDB->get_job_by_id(get_entity()->job_id());
	std::shared_ptr<Strength> str = _str.lock();

	set_base(job->max_weight + str->get_base() * 300);

	if (get_entity()->type() == ENTITY_PLAYER && notify)
		get_entity()->downcast<Player>()->get_session()->clif()->notify_compound_attribute_update(STATUS_MAX_WEIGHT, total());
	
	return total();
}

void MovementSpeed::set_base(int32_t val)
{
	Attribute<MovementSpeed>::set_base(val);

	if (get_entity()->type() == ENTITY_PLAYER)
		get_entity()->downcast<Player>()->get_session()->clif()->notify_compound_attribute_update(STATUS_MOVEMENT_SPEED, total());
}

int32_t StatusATK::compute(bool notify)
{
	int32_t blvl = 1, str = 1, dex = 1, luk = 1;

	std::shared_ptr<BaseLevel> sblvl = _blvl.lock();
	std::shared_ptr<Strength> sstr = _str.lock();
	std::shared_ptr<Dexterity> sdex = _dex.lock();
	std::shared_ptr<Luck> sluk = _luk.lock();

	if (sblvl != nullptr)
		blvl = sblvl->get_base();

	if (sstr != nullptr)
		str = sstr->total();

	if (sdex != nullptr)
		dex = sdex->total();

	if (sluk != nullptr)
		luk = sluk->total();

	// Ranged: floor[(BaseLevel ÷ 4) + (Str ÷ 5) + Dex + (Luk ÷ 3)]
	if (((1ULL << _weapon_type) & IT_WTM_RANGED) & ~(1ULL<<IT_WT_FIST))
		set_base(dex + (blvl / 4) + (str / 5) + (luk / 3));

	// Melee: floor[(BaseLevel ÷ 4) + Str + (Dex ÷ 5) + (Luk ÷ 3)]
	set_base(str + (blvl / 4) + (dex / 5) + (luk / 3));

	if (get_entity()->type() == ENTITY_PLAYER && notify)
		get_entity()->downcast<Player>()->get_session()->clif()->notify_compound_attribute_update(STATUS_STATUS_ATK, total());
	
	return total();
}

int32_t StatusMATK::compute(bool notify)
{
	int32_t blvl = 1, int_ = 1, dex = 1, luk = 1;

	std::shared_ptr<BaseLevel> sblvl = _blvl.lock();
	std::shared_ptr<Intelligence> sint = _int.lock();
	std::shared_ptr<Dexterity> sdex = _dex.lock();
	std::shared_ptr<Luck> sluk = _luk.lock();

	if (sblvl != nullptr)
		blvl = sblvl->get_base();
	if (sint != nullptr)
		int_ = sint->total();
	if (sdex != nullptr)
		dex = sdex->total();
	if (sluk != nullptr)
		luk = sluk->total();

	// floor[floor[BaseLevel ÷ 4] + Int + floor[Int ÷ 2] + floor[Dex ÷ 5] + floor[Luk ÷ 3]]
	set_base(int_ + (blvl / 4) + (int_ / 2) + (dex / 5) + (luk / 3));

	if (get_entity()->type() == ENTITY_PLAYER && notify)
		get_entity()->downcast<Player>()->get_session()->clif()->notify_compound_attribute_update(STATUS_STATUS_MATK, total());
	
	return total();
}

int32_t SoftDEF::compute(bool notify)
{
	int32_t vit = 1;

	std::shared_ptr<Vitality> svit = _vit.lock();

	if (svit != nullptr)
		vit = svit->total();

	// (VIT ÷ 2) + Max[(VIT × 0.3), (VIT ^ 2 ÷ 150) − 1]
	set_base((vit / 2) + std::max((vit * 0.3), (std::pow(vit, 2) / 150) - 1));

	if (get_entity()->type() == ENTITY_PLAYER && notify)
		get_entity()->downcast<Player>()->get_session()->clif()->notify_compound_attribute_update(STATUS_SOFT_DEF, total());
	
	return total();
}

int32_t SoftMDEF::compute(bool notify)
{
	int32_t blvl = 1, int_ = 1, dex = 1, vit = 1;

	std::shared_ptr<BaseLevel> sblvl = _blvl.lock();
	std::shared_ptr<Intelligence> sint = _int.lock();
	std::shared_ptr<Dexterity> sdex = _dex.lock();
	std::shared_ptr<Vitality> svit = _vit.lock();

	if (sblvl != nullptr)
		blvl = sblvl->get_base();
	if (sint != nullptr)
		int_ = sint->total();
	if (sdex != nullptr)
		dex = sdex->total();
	if (svit != nullptr)
		vit = svit->total();

	// INT + VIT ÷ 5 + DEX ÷ 5 + BaseLv ÷ 4
	set_base(int_ + (vit / 5) + (dex / 5) + (blvl / 4));

	if (get_entity()->type() == ENTITY_PLAYER && notify)
		get_entity()->downcast<Player>()->get_session()->clif()->notify_compound_attribute_update(STATUS_SOFT_MDEF, total());
	
	return total();
}

int32_t HIT::compute(bool notify)
{
	int32_t blvl = 1, dex = 1, luk = 1;

	std::shared_ptr<BaseLevel> sblvl = _blvl.lock();
	std::shared_ptr<Dexterity> sdex = _dex.lock();
	std::shared_ptr<Luck> sluk = _luk.lock();

	if (sblvl != nullptr)
		blvl = sblvl->get_base();
	if (sdex != nullptr)
		dex = sdex->total();
	if (sluk != nullptr)
		luk = sluk->total();

	// 175 + BaseLv + DEX + Floor(LUK ÷ 3) + Bonus
	set_base(175 + blvl + dex + (luk / 3));

	if (get_entity()->type() == ENTITY_PLAYER && notify)
		get_entity()->downcast<Player>()->get_session()->clif()->notify_compound_attribute_update(STATUS_HIT, total());
	
	return total();
}

int32_t CRIT::compute(bool notify)
{
	int32_t luk = 1;

	std::shared_ptr<Luck> sluk = _luk.lock();

	if (sluk != nullptr)
		luk = sluk->total();

	// LUK × 0.3 + Bonus
	set_base(luk / 3);

	if (get_entity()->type() == ENTITY_PLAYER && notify)
		get_entity()->downcast<Player>()->get_session()->clif()->notify_compound_attribute_update(STATUS_CRITICAL, total());
	
	return total();
}

//! @brief Computes FLEE status based on agility, luck and Base Level.
//! FLEE = 100 + BaseLv + AGI + Floor(LUK ÷ 5)
int32_t FLEE::compute(bool notify)
{
	int32_t blvl = 1, agi = 1, luk = 1;

	std::shared_ptr<Agility> sagi = _agi.lock();
	std::shared_ptr<BaseLevel> sblvl = _blvl.lock();
	std::shared_ptr<Luck> sluk = _luk.lock();

	if (sagi != nullptr)
		agi = sagi->total();
	if (sblvl != nullptr)
		blvl = sblvl->get_base();
	if (sluk != nullptr)
		luk = sluk->total();

	set_base(100 + blvl + agi + (luk / 5));

	if (get_entity()->type() == ENTITY_PLAYER && notify)
		get_entity()->downcast<Player>()->get_session()->clif()->notify_compound_attribute_update(STATUS_FLEE, total());
	
	return total();
}

//! @brief Computes the EquipATK property of physical attacks.
//! EquipATK = floor[((BaseWeaponDamage + Variance + StatBonus + RefinementBonus + OverUpgradeBonus) × SizePenaltyMultiplier]
int32_t EquipATK::compute(bool notify)
{
	int32_t str = 1, dex = 1;

	if (get_entity() == nullptr || get_entity()->type() != ENTITY_PLAYER)
		return 0;

	std::shared_ptr<Player> player = get_entity()->downcast<Player>();
	std::shared_ptr<Strength> sstr = _str.lock();
	std::shared_ptr<Dexterity> sdex = _dex.lock();

	if (sstr) str = sstr->total();
	if (sdex) dex = sdex->total();

	EquipmentListType const &equipments = player->inventory()->equipments();

	std::shared_ptr<const item_entry_data> lhw = equipments[IT_EQPI_HAND_L].second.lock();
	std::shared_ptr<const item_entry_data> rhw = equipments[IT_EQPI_HAND_R].second.lock();

	if (lhw && lhw->type == IT_TYPE_WEAPON) {
		std::shared_ptr<const item_config_data> lhwd = ItemDB->get_item_by_id(lhw->item_id);
		assert(lhwd);
		// Base Weapon Damage
		_left_hand_val = lhwd->attack;
		// StatBonus = BaseWeaponDamage × (Melee: Str / Ranged: Dex) ÷ 200
		_left_hand_val += (lhwd->attack * (((1ULL<<lhwd->sub_type.weapon_t) & IT_WTM_MELEE) ? str : dex) / 200.00f);
	} else {
		_left_hand_val = 0;
	}

	if (rhw && rhw->type == IT_TYPE_WEAPON) {
		std::shared_ptr<const item_config_data> rhwd = ItemDB->get_item_by_id(rhw->item_id);
		assert(rhwd);
		// Base Weapon Damage
		_right_hand_val = rhwd->attack;
		// StatBonus = BaseWeaponDamage × (Melee: Str / Ranged: Dex) ÷ 200
		_right_hand_val += (rhwd->attack * (((1ULL<<rhwd->sub_type.weapon_t) & IT_WTM_MELEE) ? str : dex) / 200.00f);
	} else {
		_right_hand_val = 0;
	}

	set_base(_left_hand_val + _right_hand_val);

	if (get_entity()->type() == ENTITY_PLAYER && notify)
		get_entity()->downcast<Player>()->get_session()->clif()->notify_compound_attribute_update(STATUS_EQUIP_ATK, total());

	return total();
}

int32_t EquipATK::compute_variance(int8_t weapon_lvl, int32_t base_weapon_dmg)
{
	srand(time(0));

	return floor(((rand() % 1000 + (-500)) / 10000.f) * weapon_lvl * base_weapon_dmg);
}

int32_t AttackSpeed::compute(bool notify)
{
	float temp_aspd = 0.00f;
	int amotion = 0;

	if (get_entity()->type() == ENTITY_PLAYER) {
		EquipmentListType const &equipments = get_entity()->downcast<Player>()->inventory()->equipments();
		std::shared_ptr<const item_entry_data> rhw = equipments[IT_EQPI_HAND_R].second.lock();
		std::shared_ptr<const item_entry_data> lhw = equipments[IT_EQPI_HAND_L].second.lock();
		std::shared_ptr<const job_config_data> job = JobDB->get_job_by_id(get_entity()->job_id());

		item_weapon_type rhw_type, lhw_type;

		if (rhw == nullptr) { 
			rhw_type = IT_WT_FIST;
		} else {
			std::shared_ptr<const item_config_data> rhwc = ItemDB->get_item_by_id(rhw->item_id);
			rhw_type = rhwc->sub_type.weapon_t;
		}

		amotion = job->weapon_base_aspd[rhw_type];

		if (rhw_type > IT_WT_SINGLE_MAX && lhw != nullptr) {
			std::shared_ptr<const item_config_data> lhwc = ItemDB->get_item_by_id(lhw->item_id);
			lhw_type = lhwc->sub_type.weapon_t;
			amotion += job->weapon_base_aspd[lhw_type] / 4; // Dual-wield
		}

		std::shared_ptr<Dexterity> dex = _dex.lock();
		std::shared_ptr<BaseLevel> blvl = _blvl.lock();
		std::shared_ptr<Agility> agi = _agi.lock();

		if (dex == nullptr || blvl == nullptr || agi == nullptr) {
			HLog(error) << "AttackSpeed::compute: Couldn't compute... Dex, Blvl or Agi were null.";
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
				temp_aspd = dex->get_base() * dex->get_base() / 7.0f + agi->get_base() * agi->get_base() * 0.5f;
				break;
			default:
				temp_aspd = dex->get_base() * dex->get_base() / 5.0f + agi->get_base() * agi->get_base() * 0.5f;
				break;
		}

		temp_aspd = (float)(sqrt(temp_aspd) * 0.25f) + 196;

#define ASPD_FROM_STATUS_EFFECTS 0
#define ASPD_FROM_SKILLS 0
		amotion = (int)(temp_aspd + ((float)((ASPD_FROM_STATUS_EFFECTS + ASPD_FROM_SKILLS) * agi->get_base() / 200)) - std::min(amotion, 200));
		amotion += (std::max(0xc3 - amotion, 2) * (ASPD_FROM_STATUS_EFFECTS)) / 100;
		amotion = 10 * (200 - amotion);
#undef ASPD_FROM_STATUS_EFFECTS
#undef ASPD_FROM_SKILLS
	}

 	set_base(amotion);

	if (get_entity()->type() == ENTITY_PLAYER && notify)
		get_entity()->downcast<Player>()->get_session()->clif()->notify_compound_attribute_update(STATUS_ASPD, total());

	return total();
}
