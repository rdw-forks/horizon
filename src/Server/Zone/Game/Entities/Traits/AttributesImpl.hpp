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

#ifndef HORIZON_ZONE_GAME_TRAITS_ATTRIBUTESIMPL_HPP
#define HORIZON_ZONE_GAME_TRAITS_ATTRIBUTESIMPL_HPP

#include "Attribute.hpp"
#include "Server/Zone/Definitions/EntityDefinitions.hpp"
#include "Server/Zone/Definitions/ItemDefinitions.hpp"
#include "Server/Zone/Definitions/MonsterDefinitions.hpp"
#include "Server/Zone/Game/Entities/Traits/ObservableStatus.hpp"
 // Linux

namespace Horizon
{
namespace Zone
{
class Entity;
namespace Entities
{
class Player;
namespace Traits
{
	class StatusATK;
	class EquipATK;
	class StatusMATK;
	class SoftDEF;
	class SoftMDEF;
	class HIT;
	class CRIT;
	class FLEE;
	class StrengthPointCost;
	class AgilityPointCost;
	class VitalityPointCost;
	class IntelligencePointCost;
	class DexterityPointCost;
	class LuckPointCost;
	class BaseExperience;
	class JobExperience;
	class Zeny;
	class Honor;
	class Manner;
	class Virtue;
	class StatusPoint;
	class SkillPoint;
	class NextBaseExperience;
	class NextJobExperience;
	class MaxWeight;
	class AttackSpeed;
	class MovementSpeed;
	class AttackMotion;
	class AttackDelay;
	class DamageMotion;

	class BaseLevel
	: public Attribute<BaseLevel>,
	  public ObservableStatus<BaseLevel *, StatusPoint *, NextBaseExperience *, StatusATK *, StatusMATK *, SoftMDEF *, HIT *, FLEE *, AttackSpeed *>
	{
	public:
		BaseLevel(std::weak_ptr<Entity> entity,  int32_t base = 0)
		: Attribute(entity, base, 0, 0),
		  ObservableStatus(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr)
		{ }
		~BaseLevel() { };

		void set_base(int32_t val) override
		{
			Attribute::set_base(val);
			this->notify_observers();
		}

		void on_observable_changed(BaseExperience *wbexp);
	};

	class JobLevel
	: public Attribute<JobLevel>,
	  public ObservableStatus<JobLevel *, SkillPoint *, NextJobExperience *>
	{
	public:
		JobLevel(std::weak_ptr<Entity> entity, int32_t base = 0)
		: Attribute(entity, base, 0, 0),
		  ObservableStatus(nullptr, nullptr)
		{ }
		~JobLevel() { };

		void set_base(int32_t val) override
		{
			Attribute::set_base(val);
			this->notify_observers();
		}

		void on_observable_changed(JobExperience *wjexp);
	};

	class MaxHP
	: public Attribute<MaxHP>
	{
	public:
		MaxHP(std::weak_ptr<Entity> entity, int32_t base = 0, int32_t equip = 0, int32_t status = 0)
		: Attribute(entity, base, equip, status)
		{ }
		~MaxHP() { };
	};

	class MaxSP
	: public Attribute<MaxSP>
	{
	public:
		MaxSP(std::weak_ptr<Entity> entity, int32_t base = 0, int32_t equip = 0, int32_t status = 0)
		: Attribute(entity, base, equip, status)
		{ }
		~MaxSP() { };
	};

	class CurrentHP
	: public Attribute<CurrentHP>
	{
	public:
		CurrentHP(std::weak_ptr<Entity> entity, int32_t base = 0, int32_t equip = 0, int32_t status = 0)
		: Attribute(entity, base, equip, status)
		{ }
		~CurrentHP() { };

		void damage(int damage);
	};

	class CurrentSP
	: public Attribute<CurrentSP>
	{
	public:
		CurrentSP(std::weak_ptr<Entity> entity, int32_t base = 0, int32_t equip = 0, int32_t status = 0)
		: Attribute(entity, base, equip, status)
		{ }
		~CurrentSP() { };

		void reduce(int amount);
	};

	class StatusPoint
	: public Attribute<StatusPoint>
	{
	public:
		StatusPoint(std::weak_ptr<Entity> entity, int32_t base = 0)
		: Attribute(entity, base, 0, 0)
		{ }
		~StatusPoint() { };

		void on_observable_changed(BaseLevel *wblvl);
	};

	class SkillPoint
	: public Attribute<SkillPoint>
	{
	public:
		SkillPoint(std::weak_ptr<Entity> entity, int32_t base = 0)
		: Attribute(entity, base, 0, 0)
		{ }
		~SkillPoint() { };

		virtual void set_base(int32_t val) override;
		
		void on_observable_changed(JobLevel *wjlvl);
	};

	class Strength
	: public Attribute<Strength>,
	  public ObservableStatus<Strength *, StrengthPointCost *, MaxWeight *, StatusATK *, EquipATK *>
	{
	public:
		Strength(std::weak_ptr<Entity> entity, int32_t base = 0, int32_t equip = 0, int32_t status = 0)
		: Attribute(entity, base, equip, status),
		  ObservableStatus(nullptr, nullptr, nullptr, nullptr)
		{ }
		~Strength() { };

		void set_base(int32_t val) override
		{
			Attribute::set_base(val);
			this->notify_observers();
		}
	};

	class Agility
	: public Attribute<Agility>,
	  public ObservableStatus<Agility *, AgilityPointCost *, FLEE *, AttackSpeed *>
	{
	public:
		Agility(std::weak_ptr<Entity> entity, int32_t base = 0, int32_t equip = 0, int32_t status = 0)
		: Attribute(entity, base, equip, status),
		  ObservableStatus(nullptr, nullptr, nullptr)
		{ }
		~Agility() { };

		void set_base(int32_t val) override
		{
			Attribute::set_base(val);
			this->notify_observers();
		}
	};

	class Vitality
	: public Attribute<Vitality>,
	  public ObservableStatus<Vitality *, VitalityPointCost *, SoftDEF *, SoftMDEF *>
	{
	public:
		Vitality(std::weak_ptr<Entity> entity, int32_t base = 0, int32_t equip = 0, int32_t status = 0)
		: Attribute(entity, base, equip, status),
		  ObservableStatus(nullptr, nullptr, nullptr)
		{ }
		~Vitality() { };

		void set_base(int32_t val) override
		{
			Attribute::set_base(val);
			this->notify_observers();
		}
	};

	class Intelligence
	: public Attribute<Intelligence>,
	  public ObservableStatus<Intelligence *, IntelligencePointCost *, StatusMATK *, SoftMDEF *>
	{
	public:
		Intelligence(std::weak_ptr<Entity> entity, int32_t base = 0, int32_t equip = 0, int32_t status = 0)
		: Attribute(entity, base, equip, status),
		  ObservableStatus(nullptr, nullptr, nullptr)
		{ }
		~Intelligence() { };

		void set_base(int32_t val) override
		{
			Attribute::set_base(val);
			this->notify_observers();
		}
	};

	class Dexterity
	: public Attribute<Dexterity>,
	  public ObservableStatus<Dexterity *, DexterityPointCost *, StatusATK *, EquipATK *, StatusMATK *, SoftMDEF *, HIT *, AttackSpeed *>
	{
	public:
		Dexterity(std::weak_ptr<Entity> entity, int32_t base = 0, int32_t equip = 0, int32_t status = 0)
		: Attribute(entity, base, equip, status),
		  ObservableStatus(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr)
		{ }
		~Dexterity() { };

		void set_base(int32_t val) override
		{
			Attribute::set_base(val);
			this->notify_observers();
		}
	};

	class Luck
	: public Attribute<Luck>,
	  public ObservableStatus<Luck *, LuckPointCost *, StatusATK *, StatusMATK *, HIT *, CRIT *, FLEE *>
	{
	public:
		Luck(std::weak_ptr<Entity> entity, int32_t base = 0, int32_t equip = 0, int32_t status = 0)
		: Attribute(entity, base, equip, status),
		  ObservableStatus(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr)
		{ }
		~Luck() { };

		void set_base(int32_t val) override
		{
			Attribute::set_base(val);
			this->notify_observers();
		}
	};

	class StrengthPointCost
	: public Attribute<StrengthPointCost>
	{
	public:
		StrengthPointCost(std::weak_ptr<Entity> entity, int32_t base = 0)
		: Attribute(entity, base, 0, 0)
		{ }
		~StrengthPointCost() { };

		void on_observable_changed(Strength *);
	};

	class AgilityPointCost
	: public Attribute<AgilityPointCost>
	{
	public:
		AgilityPointCost(std::weak_ptr<Entity> entity, int32_t base = 0)
		: Attribute(entity, base, 0, 0)
		{ }
		~AgilityPointCost() { };

		void on_observable_changed(Agility *);
	};

	class VitalityPointCost
	: public Attribute<VitalityPointCost>
	{
	public:
		VitalityPointCost(std::weak_ptr<Entity> entity, int32_t base = 0)
		: Attribute(entity, base, 0, 0)
		{ }
		~VitalityPointCost() { };

		void on_observable_changed(Vitality *);
	};

	class IntelligencePointCost
	: public Attribute<IntelligencePointCost>
	{
	public:
		IntelligencePointCost(std::weak_ptr<Entity> entity, int32_t base = 0)
		: Attribute(entity, base, 0, 0)
		{ }
		~IntelligencePointCost() { };

		void on_observable_changed(Intelligence *);
	};

	class DexterityPointCost
	: public Attribute<DexterityPointCost>
	{
	public:
		DexterityPointCost(std::weak_ptr<Entity> entity, int32_t base = 0)
		: Attribute(entity, base, 0, 0)
		{ }
		~DexterityPointCost() { };

		void on_observable_changed(Dexterity *);
	};

	class LuckPointCost
	: public Attribute<LuckPointCost>
	{
	public:
		LuckPointCost(std::weak_ptr<Entity> entity, int32_t base = 0)
		: Attribute(entity, base, 0, 0)
		{ }
		~LuckPointCost() { };

		void on_observable_changed(Luck *);
	};

	class BaseExperience
	: public Attribute<BaseExperience>,
	  public ObservableStatus<BaseExperience *, BaseLevel *>
	{
	public:
		BaseExperience(std::weak_ptr<Entity> entity,  int32_t base = 0)
		: Attribute(entity, base, 0, 0),
		  ObservableStatus(nullptr)
		{ }
		~BaseExperience() { };

		void set_base(int32_t val) override
		{
			Attribute::set_base(val);
			this->notify_observers();
		}
	};

	class JobExperience
	: public Attribute<JobExperience>,
	  public ObservableStatus<JobExperience *, JobLevel *>
	{
	public:
		JobExperience(std::weak_ptr<Entity> entity,  int32_t base = 0)
		: Attribute(entity, base, 0, 0),
		ObservableStatus(nullptr)
		{ }
		~JobExperience() { };

		void set_base(int32_t val) override
		{
			Attribute::set_base(val);
			this->notify_observers();
		}
	};

	class Zeny
	: public Attribute<Zeny>
	{
	public:
		Zeny(std::weak_ptr<Entity> entity,  int32_t base = 0)
		: Attribute(entity, base, 0, 0)
		{ }
		~Zeny() { };

		void set_base(int32_t val) override
		{
			Attribute::set_base(val);
		}
	};

	class Honor
	: public Attribute<Honor>
	{
	public:
		Honor(std::weak_ptr<Entity> entity,  int32_t base = 0)
		: Attribute(entity, base, 0, 0)
		{ }
		~Honor() { };

		void set_base(int32_t val) override
		{
			Attribute::set_base(val);
		}
	};

	class Manner
	: public Attribute<Manner>
	{
	public:
		Manner(std::weak_ptr<Entity> entity,  int32_t base = 0)
		: Attribute(entity, base, 0, 0)
		{ }
		~Manner() { };

		void set_base(int32_t val) override
		{
			Attribute::set_base(val);
		}
	};

	class Virtue
	: public Attribute<Virtue>
	{
	public:
		Virtue(std::weak_ptr<Entity> entity,  int32_t base = 0)
		: Attribute(entity, base, 0, 0)
		{ }
		~Virtue() { };

		void set_base(int32_t val) override
		{
			Attribute::set_base(val);
		}
	};

	class NextBaseExperience
	: public Attribute<NextBaseExperience>
	{
	public:
		NextBaseExperience(std::weak_ptr<Entity> entity,  int32_t base = 0)
		: Attribute(entity, base, 0, 0)
		{ }
		~NextBaseExperience() { };

		void on_observable_changed(BaseLevel *blvl);
	};

	class NextJobExperience
	: public Attribute<NextJobExperience>
	{
	public:
		NextJobExperience(std::weak_ptr<Entity> entity,  int32_t base = 0)
		: Attribute(entity, base, 0, 0)
		{ }
		~NextJobExperience() { };

		void on_observable_changed(JobLevel *jlvl);
	};

	class MaxWeight
	: public Attribute<MaxWeight>,
	ObservableStatus<MaxWeight *, Strength *>
	{
	public:
		MaxWeight(std::weak_ptr<Entity> entity, int32_t base = 0, int32_t equip = 0, int32_t status = 0)
		: Attribute(entity, base, equip, status),
		ObservableStatus(nullptr)
		{ }
		~MaxWeight() { };

		void on_observable_changed(Strength *wstr) { compute(true); }

		int32_t compute(bool notify);

		void set_strength(Strength *str) { _str = str; }

	private:
		Strength *_str{nullptr};
	};

	class MovementSpeed
	: public Attribute<MovementSpeed>
	{
	public:
		MovementSpeed(std::weak_ptr<Entity> entity, int32_t base = 0, int32_t equip = 0, int32_t status = 0)
		: Attribute(entity, base, equip, status)
		{ }
		~MovementSpeed() { }

		virtual void set_base(int32_t val) override;

		int32_t get_with_cost(int cost) { return (total() * cost) / 10; };
	};

	class CurrentWeight
	: public Attribute<CurrentWeight>
	{
	public:
		CurrentWeight(std::weak_ptr<Entity> entity, int32_t base = 0, int32_t equip = 0, int32_t status = 0)
		: Attribute(entity, base, equip, status)
		{ }
		~CurrentWeight() { };
	};

	class StatusATK
	: public Attribute<StatusATK>,
	  public ObservableStatus<StatusATK *, Strength *, Dexterity *, Luck *, BaseLevel *>
	{
	public:
		StatusATK(std::weak_ptr<Entity> entity)
		: Attribute(entity),
		ObservableStatus(nullptr, nullptr, nullptr, nullptr)
		{ }
		~StatusATK() { }

		void on_observable_changed(Strength *) { compute(true); }
		void on_observable_changed(Dexterity *) { compute(true); }
		void on_observable_changed(Luck *) { compute(true); }
		void on_observable_changed(BaseLevel *) { compute(true); }

		int32_t compute(bool notify);

		void set_base_level(BaseLevel *blvl) { _blvl = blvl; }
		void set_strength(Strength *str) { _str = str; }
		void set_dexterity(Dexterity *dex) { _dex = dex; }
		void set_luck(Luck *luk) { _luk = luk; }
		void set_weapon_type(item_weapon_type type) { _weapon_type = type; compute(true); }

	private:
		BaseLevel *_blvl{nullptr};
		Strength *_str{nullptr};
		Dexterity *_dex{nullptr};
		Luck *_luk{nullptr};
		item_weapon_type _weapon_type;
	};

	class EquipATK
	: public Attribute<EquipATK>,
	  public ObservableStatus<EquipATK *, Strength *, Dexterity *>
	{
	public:
		EquipATK(std::weak_ptr<Entity> entity)
		: Attribute(entity),
		ObservableStatus(nullptr, nullptr)
		{ }
		~EquipATK() { }

		void on_observable_changed(Strength *) { compute(true); }
		void on_observable_changed(Dexterity *) { compute(true); }
		void on_weapon_changed() { compute(true); }

		void set_strength(Strength *str) { _str = str; }
		void set_dexterity(Dexterity *dex) { _dex = dex; }

		int32_t compute(bool notify);
		int32_t compute_variance(int8_t weapon_lvl, int32_t base_weapon_dmg);

		//void notify_update() override { _notifier.notify_sum(); }

		int32_t get_lhw_overupgrade() { return _lhw_overupgrade; }
		int32_t get_rhw_overupgrade() { return _rhw_overupgrade; }

	private:
		Strength *_str{nullptr};
		Dexterity *_dex{nullptr};
		int32_t _left_hand_val{0};
		int32_t _right_hand_val{0};
		int32_t _lhw_overupgrade{0};
		int32_t _rhw_overupgrade{0};
	};

	class StatusMATK
	: public Attribute<StatusMATK>,
	  public ObservableStatus<StatusMATK *, Intelligence *, Dexterity *, Luck *, BaseLevel *>
	{
	public:
		StatusMATK(std::weak_ptr<Entity> entity)
		: Attribute(entity),
		ObservableStatus(nullptr, nullptr, nullptr, nullptr)
		{ }
		~StatusMATK() { }

		void on_observable_changed(Intelligence *) { compute(true); }
		void on_observable_changed(Dexterity *) { compute(true); }
		void on_observable_changed(Luck *) { compute(true); }
		void on_observable_changed(BaseLevel *) { compute(true); }

		int32_t compute(bool notify);

		void set_base_level(BaseLevel *blvl) { _blvl = blvl; }
		void set_intelligence(Intelligence *int_) { _int = int_; }
		void set_dexterity(Dexterity *dex) { _dex = dex; }
		void set_luck(Luck *luk) { _luk = luk; }

	private:
		BaseLevel *_blvl{nullptr};
		Intelligence *_int{nullptr};
		Dexterity *_dex{nullptr};
		Luck *_luk{nullptr};
	};

	class SoftDEF
	: public Attribute<SoftDEF>,
	  public ObservableStatus<SoftDEF *, Vitality *>
	{
	public:
		SoftDEF(std::weak_ptr<Entity> entity)
		: Attribute(entity),
		ObservableStatus(nullptr)
		{ }
		~SoftDEF() { }

		void on_observable_changed(Vitality *) { compute(true); }

		int32_t compute(bool notify);

		void set_vitality(Vitality *vit) { _vit = vit; }

	private:
		Vitality *_vit{nullptr};
	};

	class SoftMDEF
	: public Attribute<SoftMDEF>,
	  public ObservableStatus<SoftMDEF *, Intelligence *, Dexterity *, Vitality *, BaseLevel *>
	{
	public:
		SoftMDEF(std::weak_ptr<Entity> entity)
		: Attribute(entity),
		ObservableStatus(nullptr, nullptr, nullptr, nullptr)
		{ }
		~SoftMDEF() { }

		void on_observable_changed(Intelligence *) { compute(true); }
		void on_observable_changed(Dexterity *) { compute(true); }
		void on_observable_changed(Vitality *) { compute(true); }
		void on_observable_changed(BaseLevel *) { compute(true); }

		int32_t compute(bool notify);

		void set_base_level(BaseLevel *blvl) { _blvl = blvl; }
		void set_intelligence(Intelligence *int_) { _int = int_; }
		void set_dexterity(Dexterity *dex) { _dex = dex; }
		void set_vitality(Vitality *vit) { _vit = vit; }

	private:
		BaseLevel *_blvl{nullptr};
		Intelligence *_int{nullptr};
		Dexterity *_dex{nullptr};
		Vitality *_vit{nullptr};
	};

	class HIT
	: public Attribute<HIT>,
	  public ObservableStatus<HIT *, Dexterity *, Luck *, BaseLevel *>
	{
	public:
		HIT(std::weak_ptr<Entity> entity)
		: Attribute(entity),
		ObservableStatus(nullptr, nullptr, nullptr)
		{ }
		~HIT() { }

		void on_observable_changed(Dexterity *) { compute(true); }
		void on_observable_changed(Luck *) { compute(true); }
		void on_observable_changed(BaseLevel *) { compute(true); }

		int32_t compute(bool notify);

		void set_base_level(BaseLevel *blvl) { _blvl = blvl; }
		void set_dexterity(Dexterity *dex) { _dex = dex; }
		void set_luck(Luck *luk) { _luk = luk; }

	private:
		BaseLevel *_blvl{nullptr};
		Dexterity *_dex{nullptr};
		Luck *_luk{nullptr};
	};

	class CRIT
	: public Attribute<CRIT>,
	  public ObservableStatus<CRIT *, Luck *>
	{
	public:
		CRIT(std::weak_ptr<Entity> entity)
		: Attribute(entity),
		ObservableStatus(nullptr)
		{ }
		~CRIT() { }

		void on_observable_changed(Luck *) { compute(true); }

		int32_t compute(bool notify);

		void set_luck(Luck *luk) { _luk = luk; }

	private:
		Luck *_luk{nullptr};
	};

	class FLEE
	: public Attribute<FLEE>,
	  public ObservableStatus<FLEE *, Agility *, BaseLevel *, Luck *>
	{
	public:
		FLEE(std::weak_ptr<Entity> entity)
		: Attribute(entity),
		ObservableStatus(nullptr, nullptr, nullptr)
		{ }
		~FLEE() { }

		void on_observable_changed(Agility *) { compute(true); }
		void on_observable_changed(BaseLevel *) { compute(true); }
		void on_observable_changed(Luck *) { compute(true); }

		int32_t compute(bool notify);

		void set_agility(Agility *agi) { _agi = agi; }
		void set_base_level(BaseLevel *blvl) { _blvl = blvl; }
		void set_luck(Luck *luk) { _luk = luk; }

	private:
		Agility *_agi{nullptr};
		BaseLevel *_blvl{nullptr};
		Luck *_luk{nullptr};
	};

	class AttackSpeed
	: public Attribute<AttackSpeed>,
	  public ObservableStatus<AttackSpeed *, Agility *, Dexterity *, BaseLevel *>
	{
	public:
		AttackSpeed(std::weak_ptr<Entity> entity)
		: Attribute(entity),
		ObservableStatus(nullptr, nullptr, nullptr)
		{ }
		~AttackSpeed() { }

		void on_observable_changed(Agility *) { compute(true); }
		void on_observable_changed(Dexterity *) { compute(true); }
		void on_observable_changed(BaseLevel *) { compute(true); }
		void on_equipment_changed() { compute(true); }

		int32_t compute(bool notify);

		void set_agility(Agility *agi) { _agi = agi; }
		void set_dexterity(Dexterity *dex) { _dex = dex; }
		void set_base_level(BaseLevel *blvl) { _blvl = blvl; }

	private:
		Agility *_agi{nullptr};
		Dexterity *_dex{nullptr};
		BaseLevel *_blvl{nullptr};
	};

	class AttackRange
	: public Attribute<AttackRange>
	{
	public:
		AttackRange(std::weak_ptr<Entity> entity)
		: Attribute(entity)
		{ }
		~AttackRange() { }

		void on_equipment_changed() { compute(true); }

		int32_t compute(bool notify);
	};

	class AttackMotion
	: public Attribute<AttackMotion>,
	  public ObservableStatus<AttackMotion *, AttackSpeed *, Agility *>
	{
	public:
		AttackMotion(std::weak_ptr<Entity> entity)
		: Attribute(entity),
		ObservableStatus(nullptr, nullptr)
		{ }
		~AttackMotion() { }

		void on_observable_changed(AttackSpeed *) { compute(); }
		void on_observable_changed(Agility *) { compute(); }

		int32_t compute();

		void on_equipment_changed() { compute(); }

		void set_attack_speed(AttackSpeed *aspd) { _attack_speed = aspd; }
		void set_agility(Agility *agi) { _agi = agi; }

	private:
		Agility *_agi{nullptr};
		AttackSpeed *_attack_speed{nullptr};
	};

	class AttackDelay
	: public Attribute<AttackDelay>,
	  public ObservableStatus<AttackDelay *, AttackMotion *>
	{
	public:
		AttackDelay(std::weak_ptr<Entity> entity)
		: Attribute(entity),
		ObservableStatus(nullptr)
		{ }
		~AttackDelay() { }

		void on_observable_changed(AttackMotion *) { compute(); }
		void on_equipment_changed() { compute(); }
		
		int32_t compute();

		void set_attack_motion(AttackMotion *amotion) { _attack_motion = amotion; }

	private:
		AttackMotion *_attack_motion{nullptr};
	};

	class DamageMotion
	: public Attribute<DamageMotion>,
	  public ObservableStatus<DamageMotion *, Agility *>
	{
	public:
		DamageMotion(std::weak_ptr<Entity> entity)
		: Attribute(entity),
		ObservableStatus(nullptr)
		{ }
		~DamageMotion() { }

		void on_observable_changed(Agility *) { compute(); }
		void on_equipment_changed() { compute(); }

		int32_t compute();

		void set_agility(Agility *agi) { _agi = agi; }

	private:
		Agility *_agi{nullptr};
	};

	class BaseAttack
	: public Attribute<BaseAttack>,
	  public ObservableStatus<BaseAttack *, Strength *, Dexterity *, Luck *, BaseLevel *>
	{
	public:
		BaseAttack(std::weak_ptr<Entity> entity)
		: Attribute(entity),
		ObservableStatus(nullptr, nullptr, nullptr, nullptr)
		{ }
		~BaseAttack() { }

		void on_observable_changed(Strength *) { compute(); }
		void on_observable_changed(Dexterity *) { compute(); }
		void on_observable_changed(Luck *) { compute(); }
		void on_observable_changed(BaseLevel *) { compute(); }

		void on_equipment_changed() { compute(); }

		int32_t compute();

		void set_strength(Strength *str) { _str = str; }
		void set_dexterity(Dexterity *dex) { _dex = dex; }
		void set_luck(Luck *luk) { _luk = luk; }
		void set_base_level(BaseLevel *blvl) { _blvl = blvl; }

	private:
		Strength *_str{nullptr};
		Dexterity *_dex{nullptr};
		Luck *_luk{nullptr};
		BaseLevel *_blvl{nullptr};
	};

	class EntitySize
	: public Attribute<EntitySize>
	{
	public:
		EntitySize(std::weak_ptr<Entity> entity)
		: Attribute(entity)
		{ }
		~EntitySize() { }
	};

	class CreatureWeaponAttack
		: public Attribute<CreatureWeaponAttack>
	{
		CreatureWeaponAttack(std::weak_ptr<Entity> entity)
			: Attribute(entity)
		{ }
		~CreatureWeaponAttack() { }
	};

	class CreatureAttackDamage
		: public Attribute<CreatureAttackDamage>,
		public ObservableStatus<CreatureAttackDamage*, Strength*, BaseLevel*, CreatureWeaponAttack*>,
		public AttributeVariance
	{
	public:
		CreatureAttackDamage(std::weak_ptr<Entity> entity)
			: Attribute(entity),
			ObservableStatus(nullptr, nullptr, nullptr),
			AttributeVariance()
		{ }
		~CreatureAttackDamage() { }

		void on_observable_changed(Strength*) { compute(); }
		void on_observable_changed(BaseLevel*) { compute(); }
		void on_observable_changed(CreatureWeaponAttack*) { compute(); }

		void set_strength(Strength* str) { _str = str; }
		void set_base_level(BaseLevel* blvl) { _blvl = blvl; }
		void set_creature_weapon_attack(CreatureWeaponAttack* cw_atk) { _cw_atk = cw_atk; }

		int32_t compute();

	private:
		int32_t _min{ 0 }, _max{ 0 };
		Strength* _str{ nullptr };
		BaseLevel* _blvl{ nullptr };
		CreatureWeaponAttack* _cw_atk{ nullptr };
	};

	class CreatureMagicAttackDamage
		: public Attribute<CreatureAttackDamage>,
		public ObservableStatus<CreatureAttackDamage*, Intelligence*, BaseLevel*, CreatureWeaponAttack*>,
		public AttributeVariance
	{
	public:
		CreatureMagicAttackDamage(std::weak_ptr<Entity> entity)
			: Attribute(entity),
			ObservableStatus(nullptr, nullptr, nullptr),
			AttributeVariance()
		{ }
		~CreatureMagicAttackDamage() { }

		void on_observable_changed(Intelligence*) { compute(); }
		void on_observable_changed(BaseLevel*) { compute(); }
		void on_observable_changed(CreatureWeaponAttack*) { compute(); }

		void set_intelligence(Intelligence* _intelligence) { _int = _intelligence; }
		void set_base_level(BaseLevel* blvl) { _blvl = blvl; }
		void set_creature_weapon_attack(CreatureWeaponAttack* cw_atk) { _cw_atk = cw_atk; }

		int32_t compute();

	private:
		int32_t _min{ 0 }, _max{ 0 };
		Intelligence* _int{ nullptr };
		BaseLevel* _blvl{ nullptr };
		CreatureWeaponAttack* _cw_atk{ nullptr };
	};

	class CreatureViewRange
		: public Attribute<CreatureViewRange>
	{
	public:
		CreatureViewRange(std::weak_ptr<Entity> entity) : Attribute(entity) { }
		~CreatureViewRange() { }
	};

	class CreatureChaseRange
		: public Attribute<CreatureChaseRange>
	{
	public:
		CreatureChaseRange(std::weak_ptr<Entity> entity) : Attribute(entity) { }
		~CreatureChaseRange() { }
	};

	class CreaturePrimaryRace
		: public Attribute<CreaturePrimaryRace>
	{
	public:
		CreaturePrimaryRace(std::weak_ptr<Entity> entity) : Attribute(entity, (int32_t) MONSTER_RACE_FORMLESS) { }
		~CreaturePrimaryRace() { }
	};

	class CreatureSecondaryRace
		: public Attribute<CreatureSecondaryRace>
	{
	public:
		CreatureSecondaryRace(std::weak_ptr<Entity> entity) : Attribute(entity, (int32_t) MONSTER_RACE2_NONE) { }
		~CreatureSecondaryRace() { }
	};

	class CreatureElement
		: public Attribute<CreatureElement>
	{
	public:
		CreatureElement(std::weak_ptr<Entity> entity) : Attribute(entity, (int32_t) ELE_NEUTRAL) { }
		~CreatureElement() { }
	};

	class CreatureElementLevel
		: public Attribute<CreatureElementLevel>
	{
	public:
		CreatureElementLevel(std::weak_ptr<Entity> entity) : Attribute(entity) { }
		~CreatureElementLevel() { }
	};

	class CreatureMode
		: public Attribute<CreatureMode>
	{
	public:
		CreatureMode(std::weak_ptr<Entity> entity) : Attribute(entity, MONSTER_MODE_MASK_NONE) { }
		~CreatureMode() { }
	};
}
}
}
}

#endif /* HORIZON_ZONE_GAME_TRAITS_ATTRIBUTESIMPL_HPP */
