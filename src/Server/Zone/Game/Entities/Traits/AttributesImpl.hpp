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
#include "Server/Common/Definitions/EntityDefinitions.hpp"
#include "Server/Common/Definitions/ItemDefinitions.hpp"
#include "Server/Zone/Game/Entities/Traits/ObservableStatus.hpp"

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
	class StatusPoint;
	class SkillPoint;
	class NextBaseExperience;
	class NextJobExperience;
	class MaxWeight;
	class AttackSpeed;

	class BaseLevel
	: public Attribute<BaseLevel>,
	  public ObservableStatus<std::weak_ptr<BaseLevel>, std::weak_ptr<StatusPoint>, std::weak_ptr<NextBaseExperience>, std::weak_ptr<StatusATK>, std::weak_ptr<StatusMATK>, std::weak_ptr<SoftMDEF>, std::weak_ptr<HIT>, std::weak_ptr<FLEE>, std::weak_ptr<AttackSpeed>>
	{
	public:
		BaseLevel(std::weak_ptr<Entity> entity,  uint32_t base = 0)
		: Attribute(entity, base, 0, 0),
		  ObservableStatus(std::weak_ptr<StatusPoint>(), std::weak_ptr<NextBaseExperience>(), std::weak_ptr<StatusATK>(), std::weak_ptr<StatusMATK>(), std::weak_ptr<SoftMDEF>(), std::weak_ptr<HIT>(), std::weak_ptr<FLEE>(), std::weak_ptr<AttackSpeed>())
		{ }
		~BaseLevel() { };

		void set_base(uint32_t val) override
		{
			Attribute::set_base(val);
			this->notify_observers();
		}

		void on_observable_changed(std::weak_ptr<BaseExperience> wbexp);
	};

	class JobLevel
	: public Attribute<JobLevel>,
	  public ObservableStatus<std::weak_ptr<JobLevel>, std::weak_ptr<SkillPoint>, std::weak_ptr<NextJobExperience>>
	{
	public:
		JobLevel(std::weak_ptr<Entity> entity, uint32_t base = 0)
		: Attribute(entity, base, 0, 0),
		  ObservableStatus(std::weak_ptr<SkillPoint>(), std::weak_ptr<NextJobExperience>())
		{ }
		~JobLevel() { };

		void set_base(uint32_t val) override
		{
			Attribute::set_base(val);
			this->notify_observers();
		}

		void on_observable_changed(std::weak_ptr<JobExperience> wjexp);
	};

	class MaxHP
	: public Attribute<MaxHP>
	{
	public:
		MaxHP(std::weak_ptr<Entity> entity, uint32_t base = 0, uint32_t equip = 0, uint32_t status = 0)
		: Attribute(entity, base, equip, status)
		{ }
		~MaxHP() { };
	};

	class MaxSP
	: public Attribute<MaxSP>
	{
	public:
		MaxSP(std::weak_ptr<Entity> entity, uint32_t base = 0, uint32_t equip = 0, uint32_t status = 0)
		: Attribute(entity, base, equip, status)
		{ }
		~MaxSP() { };
	};

	class CurrentHP
	: public Attribute<CurrentHP>
	{
	public:
		CurrentHP(std::weak_ptr<Entity> entity, uint32_t base = 0, uint32_t equip = 0, uint32_t status = 0)
		: Attribute(entity, base, equip, status)
		{ }
		~CurrentHP() { };
	};

	class CurrentSP
	: public Attribute<CurrentSP>
	{
	public:
		CurrentSP(std::weak_ptr<Entity> entity, uint32_t base = 0, uint32_t equip = 0, uint32_t status = 0)
		: Attribute(entity, base, equip, status)
		{ }
		~CurrentSP() { };
	};

	class MovementSpeed
	: public Attribute<MovementSpeed>
	{
	public:
		MovementSpeed(std::weak_ptr<Entity> entity, uint32_t base = 0, uint32_t equip = 0, uint32_t status = 0)
		: Attribute(entity, base, equip, status)
		{ }
		~MovementSpeed() { }

		uint32_t get_with_cost(int cost) { return total() * cost / 10; };
	};

	class StatusPoint
	: public Attribute<StatusPoint>
	{
	public:
		StatusPoint(std::weak_ptr<Entity> entity, uint32_t base = 0)
		: Attribute(entity, base, 0, 0)
		{ }
		~StatusPoint() { };

		void on_observable_changed(std::weak_ptr<BaseLevel> wblvl);
	};

	class SkillPoint
	: public Attribute<SkillPoint>
	{
	public:
		SkillPoint(std::weak_ptr<Entity> entity, uint32_t base = 0)
		: Attribute(entity, base, 0, 0)
		{ }
		~SkillPoint() { };

		void on_observable_changed(std::weak_ptr<JobLevel> wjlvl);
	};

	class Strength
	: public Attribute<Strength>,
	  public ObservableStatus<std::weak_ptr<Strength>, std::weak_ptr<StrengthPointCost>, std::weak_ptr<MaxWeight>, std::weak_ptr<StatusATK>, std::weak_ptr<EquipATK>>
	{
	public:
		Strength(std::weak_ptr<Entity> entity, uint32_t base = 0, uint32_t equip = 0, uint32_t status = 0)
		: Attribute(entity, base, equip, status),
		  ObservableStatus(std::weak_ptr<StrengthPointCost>(), std::weak_ptr<MaxWeight>(), std::weak_ptr<StatusATK>(), std::weak_ptr<EquipATK>())
		{ }
		~Strength() { };

		void set_base(uint32_t val) override
		{
			Attribute::set_base(val);
			this->notify_observers();
		}
	};

	class Agility
	: public Attribute<Agility>,
	  public ObservableStatus<std::weak_ptr<Agility>, std::weak_ptr<AgilityPointCost>, std::weak_ptr<FLEE>, std::weak_ptr<AttackSpeed>>
	{
	public:
		Agility(std::weak_ptr<Entity> entity, uint32_t base = 0, uint32_t equip = 0, uint32_t status = 0)
		: Attribute(entity, base, equip, status),
		  ObservableStatus(std::weak_ptr<AgilityPointCost>(), std::weak_ptr<FLEE>(), std::weak_ptr<AttackSpeed>())
		{ }
		~Agility() { };

		void set_base(uint32_t val) override
		{
			Attribute::set_base(val);
			this->notify_observers();
		}
	};

	class Vitality
	: public Attribute<Vitality>,
	  public ObservableStatus<std::weak_ptr<Vitality>, std::weak_ptr<VitalityPointCost>, std::weak_ptr<SoftDEF>, std::weak_ptr<SoftMDEF>>
	{
	public:
		Vitality(std::weak_ptr<Entity> entity, uint32_t base = 0, uint32_t equip = 0, uint32_t status = 0)
		: Attribute(entity, base, equip, status),
		  ObservableStatus(std::weak_ptr<VitalityPointCost>(), std::weak_ptr<SoftDEF>(), std::weak_ptr<SoftMDEF>())
		{ }
		~Vitality() { };

		void set_base(uint32_t val) override
		{
			Attribute::set_base(val);
			this->notify_observers();
		}
	};

	class Intelligence
	: public Attribute<Intelligence>,
	  public ObservableStatus<std::weak_ptr<Intelligence>, std::weak_ptr<IntelligencePointCost>, std::weak_ptr<StatusMATK>, std::weak_ptr<SoftMDEF>>
	{
	public:
		Intelligence(std::weak_ptr<Entity> entity, uint32_t base = 0, uint32_t equip = 0, uint32_t status = 0)
		: Attribute(entity, base, equip, status),
		  ObservableStatus(std::weak_ptr<IntelligencePointCost>(), std::weak_ptr<StatusMATK>(), std::weak_ptr<SoftMDEF>())
		{ }
		~Intelligence() { };

		void set_base(uint32_t val) override
		{
			Attribute::set_base(val);
			this->notify_observers();
		}
	};

	class Dexterity
	: public Attribute<Dexterity>,
	  public ObservableStatus<std::weak_ptr<Dexterity>, std::weak_ptr<DexterityPointCost>, std::weak_ptr<StatusATK>, std::weak_ptr<EquipATK>, std::weak_ptr<StatusMATK>, std::weak_ptr<SoftMDEF>, std::weak_ptr<HIT>, std::weak_ptr<AttackSpeed>>
	{
	public:
		Dexterity(std::weak_ptr<Entity> entity, uint32_t base = 0, uint32_t equip = 0, uint32_t status = 0)
		: Attribute(entity, base, equip, status),
		  ObservableStatus(std::weak_ptr<DexterityPointCost>(), std::weak_ptr<StatusATK>(), std::weak_ptr<EquipATK>(), std::weak_ptr<StatusMATK>(), std::weak_ptr<SoftMDEF>(), std::weak_ptr<HIT>(), std::weak_ptr<AttackSpeed>())
		{ }
		~Dexterity() { };

		void set_base(uint32_t val) override
		{
			Attribute::set_base(val);
			this->notify_observers();
		}
	};

	class Luck
	: public Attribute<Luck>,
	  public ObservableStatus<std::weak_ptr<Luck>, std::weak_ptr<LuckPointCost>, std::weak_ptr<StatusATK>, std::weak_ptr<StatusMATK>, std::weak_ptr<HIT>, std::weak_ptr<CRIT>, std::weak_ptr<FLEE>>
	{
	public:
		Luck(std::weak_ptr<Entity> entity, uint32_t base = 0, uint32_t equip = 0, uint32_t status = 0)
		: Attribute(entity, base, equip, status),
		  ObservableStatus(std::weak_ptr<LuckPointCost>(), std::weak_ptr<StatusATK>(), std::weak_ptr<StatusMATK>(), std::weak_ptr<HIT>(), std::weak_ptr<CRIT>(), std::weak_ptr<FLEE>())
		{ }
		~Luck() { };

		void set_base(uint32_t val) override
		{
			Attribute::set_base(val);
			this->notify_observers();
		}
	};

	class StrengthPointCost
	: public Attribute<StrengthPointCost>
	{
	public:
		StrengthPointCost(std::weak_ptr<Entity> entity, uint32_t base = 0)
		: Attribute(entity, base, 0, 0)
		{ }
		~StrengthPointCost() { };

		void on_observable_changed(std::weak_ptr<Strength>);
	};

	class AgilityPointCost
	: public Attribute<AgilityPointCost>
	{
	public:
		AgilityPointCost(std::weak_ptr<Entity> entity, uint32_t base = 0)
		: Attribute(entity, base, 0, 0)
		{ }
		~AgilityPointCost() { };

		void on_observable_changed(std::weak_ptr<Agility>);
	};

	class VitalityPointCost
	: public Attribute<VitalityPointCost>
	{
	public:
		VitalityPointCost(std::weak_ptr<Entity> entity, uint32_t base = 0)
		: Attribute(entity, base, 0, 0)
		{ }
		~VitalityPointCost() { };

		void on_observable_changed(std::weak_ptr<Vitality>);
	};

	class IntelligencePointCost
	: public Attribute<IntelligencePointCost>
	{
	public:
		IntelligencePointCost(std::weak_ptr<Entity> entity, uint32_t base = 0)
		: Attribute(entity, base, 0, 0)
		{ }
		~IntelligencePointCost() { };

		void on_observable_changed(std::weak_ptr<Intelligence>);
	};

	class DexterityPointCost
	: public Attribute<DexterityPointCost>
	{
	public:
		DexterityPointCost(std::weak_ptr<Entity> entity, uint32_t base = 0)
		: Attribute(entity, base, 0, 0)
		{ }
		~DexterityPointCost() { };

		void on_observable_changed(std::weak_ptr<Dexterity>);
	};

	class LuckPointCost
	: public Attribute<LuckPointCost>
	{
	public:
		LuckPointCost(std::weak_ptr<Entity> entity, uint32_t base = 0)
		: Attribute(entity, base, 0, 0)
		{ }
		~LuckPointCost() { };

		void on_observable_changed(std::weak_ptr<Luck>);
	};

	class BaseExperience
	: public Attribute<BaseExperience>,
	  public ObservableStatus<std::weak_ptr<BaseExperience>, std::weak_ptr<BaseLevel>>
	{
	public:
		BaseExperience(std::weak_ptr<Entity> entity,  uint32_t base = 0)
		: Attribute(entity, base, 0, 0),
		  ObservableStatus(std::weak_ptr<BaseLevel>())
		{ }
		~BaseExperience() { };

		void set_base(uint32_t val) override
		{
			Attribute::set_base(val);
			this->notify_observers();
		}
	};

	class JobExperience
	: public Attribute<JobExperience>,
	  public ObservableStatus<std::weak_ptr<JobExperience>, std::weak_ptr<JobLevel>>
	{
	public:
		JobExperience(std::weak_ptr<Entity> entity,  uint32_t base = 0)
		: Attribute(entity, base, 0, 0),
		ObservableStatus(std::weak_ptr<JobLevel>())
		{ }
		~JobExperience() { };

		void set_base(uint32_t val) override
		{
			Attribute::set_base(val);
			this->notify_observers();
		}
	};

	class NextBaseExperience
	: public Attribute<NextBaseExperience>
	{
	public:
		NextBaseExperience(std::weak_ptr<Entity> entity,  uint32_t base = 0)
		: Attribute(entity, base, 0, 0)
		{ }
		~NextBaseExperience() { };

		void on_observable_changed(std::weak_ptr<BaseLevel> blvl);
	};

	class NextJobExperience
	: public Attribute<NextJobExperience>
	{
	public:
		NextJobExperience(std::weak_ptr<Entity> entity,  uint32_t base = 0)
		: Attribute(entity, base, 0, 0)
		{ }
		~NextJobExperience() { };

		void on_observable_changed(std::weak_ptr<JobLevel> jlvl);
	};

	class MaxWeight
	: public Attribute<MaxWeight>
	{
	public:
		MaxWeight(std::weak_ptr<Entity> entity, uint32_t base = 0, uint32_t equip = 0, uint32_t status = 0)
		: Attribute(entity, base, equip, status)
		{ }
		~MaxWeight() { };

		void on_observable_changed(std::weak_ptr<Strength> wstr) { compute(true); }

		uint32_t compute(bool notify);

		void set_strength(std::weak_ptr<Strength> str) { _str = str; }

	private:
		std::weak_ptr<Strength> _str;
	};

	class CurrentWeight
	: public Attribute<CurrentWeight>
	{
	public:
		CurrentWeight(std::weak_ptr<Entity> entity, uint32_t base = 0, uint32_t equip = 0, uint32_t status = 0)
		: Attribute(entity, base, equip, status)
		{ }
		~CurrentWeight() { };
	};

	class StatusATK
	: public Attribute<StatusATK>
	{
	public:
		StatusATK(std::weak_ptr<Entity> entity)
		: Attribute(entity)
		{ }
		~StatusATK() { }

		void on_observable_changed(std::weak_ptr<Strength>) { compute(true); }
		void on_observable_changed(std::weak_ptr<Dexterity>) { compute(true); }
		void on_observable_changed(std::weak_ptr<Luck>) { compute(true); }
		void on_observable_changed(std::weak_ptr<BaseLevel>) { compute(true); }

		uint32_t compute(bool notify);

		void set_base_level(std::weak_ptr<BaseLevel> blvl) { _blvl = blvl; }
		void set_strength(std::weak_ptr<Strength> str) { _str = str; }
		void set_dexterity(std::weak_ptr<Dexterity> dex) { _dex = dex; }
		void set_luck(std::weak_ptr<Luck> luk) { _luk = luk; }
		void set_weapon_type(item_weapon_type type) { _weapon_type = type; compute(true); }

	private:
		std::weak_ptr<BaseLevel> _blvl;
		std::weak_ptr<Strength> _str;
		std::weak_ptr<Dexterity> _dex;
		std::weak_ptr<Luck> _luk;
		item_weapon_type _weapon_type;
	};

	class EquipATK
	: public Attribute<EquipATK>
	{
	public:
		EquipATK(std::weak_ptr<Entity> entity)
		: Attribute(entity)
		{ }
		~EquipATK() { }

		void on_observable_changed(std::weak_ptr<Strength>) { compute(true); }
		void on_observable_changed(std::weak_ptr<Dexterity>) { compute(true); }
		void on_weapon_changed() { compute(true); }

		void set_strength(std::weak_ptr<Strength> str) { _str = str; }
		void set_dexterity(std::weak_ptr<Dexterity> dex) { _dex = dex; }

		uint32_t compute(bool notify);
		uint32_t compute_variance(uint8_t weapon_lvl, uint32_t base_weapon_dmg);

		//void notify_update() override { _notifier.notify_sum(); }

		uint32_t get_lhw_overupgrade() { return _lhw_overupgrade; }
		uint32_t get_rhw_overupgrade() { return _rhw_overupgrade; }

	private:
		std::weak_ptr<Strength> _str;
		std::weak_ptr<Dexterity> _dex;
		uint32_t _left_hand_val{0};
		uint32_t _right_hand_val{0};
		uint32_t _lhw_overupgrade{0};
		uint32_t _rhw_overupgrade{0};
	};

	class StatusMATK
	: public Attribute<StatusMATK>
	{
	public:
		StatusMATK(std::weak_ptr<Entity> entity)
		: Attribute(entity)
		{ }
		~StatusMATK() { }

		void on_observable_changed(std::weak_ptr<Intelligence>) { compute(true); }
		void on_observable_changed(std::weak_ptr<Dexterity>) { compute(true); }
		void on_observable_changed(std::weak_ptr<Luck>) { compute(true); }
		void on_observable_changed(std::weak_ptr<BaseLevel>) { compute(true); }

		uint32_t compute(bool notify);

		void set_base_level(std::weak_ptr<BaseLevel> blvl) { _blvl = blvl; }
		void set_intelligence(std::weak_ptr<Intelligence> int_) { _int = int_; }
		void set_dexterity(std::weak_ptr<Dexterity> dex) { _dex = dex; }
		void set_luck(std::weak_ptr<Luck> luk) { _luk = luk; }

	private:
		std::weak_ptr<BaseLevel> _blvl;
		std::weak_ptr<Intelligence> _int;
		std::weak_ptr<Dexterity> _dex;
		std::weak_ptr<Luck> _luk;
	};

	class SoftDEF
	: public Attribute<SoftDEF>
	{
	public:
		SoftDEF(std::weak_ptr<Entity> entity)
		: Attribute(entity)
		{ }
		~SoftDEF() { }

		void on_observable_changed(std::weak_ptr<Vitality>) { compute(true); }

		uint32_t compute(bool notify);

		void set_vitality(std::weak_ptr<Vitality> vit) { _vit = vit; }

	private:
		std::weak_ptr<Vitality> _vit;
	};

	class SoftMDEF
	: public Attribute<SoftMDEF>
	{
	public:
		SoftMDEF(std::weak_ptr<Entity> entity)
		: Attribute(entity)
		{ }
		~SoftMDEF() { }

		void on_observable_changed(std::weak_ptr<Intelligence>) { compute(true); }
		void on_observable_changed(std::weak_ptr<Dexterity>) { compute(true); }
		void on_observable_changed(std::weak_ptr<Vitality>) { compute(true); }
		void on_observable_changed(std::weak_ptr<BaseLevel>) { compute(true); }

		uint32_t compute(bool notify);

		void set_base_level(std::weak_ptr<BaseLevel> blvl) { _blvl = blvl; }
		void set_intelligence(std::weak_ptr<Intelligence> int_) { _int = int_; }
		void set_dexterity(std::weak_ptr<Dexterity> dex) { _dex = dex; }
		void set_vitality(std::weak_ptr<Vitality> vit) { _vit = vit; }

	private:
		std::weak_ptr<BaseLevel> _blvl;
		std::weak_ptr<Intelligence> _int;
		std::weak_ptr<Dexterity> _dex;
		std::weak_ptr<Vitality> _vit;
	};

	class HIT
	: public Attribute<HIT>
	{
	public:
		HIT(std::weak_ptr<Entity> entity)
		: Attribute(entity)
		{ }
		~HIT() { }

		void on_observable_changed(std::weak_ptr<Dexterity>) { compute(true); }
		void on_observable_changed(std::weak_ptr<Luck>) { compute(true); }
		void on_observable_changed(std::weak_ptr<BaseLevel>) { compute(true); }

		uint32_t compute(bool notify);

		void set_base_level(std::weak_ptr<BaseLevel> blvl) { _blvl = blvl; }
		void set_dexterity(std::weak_ptr<Dexterity> dex) { _dex = dex; }
		void set_luck(std::weak_ptr<Luck> luk) { _luk = luk; }

	private:
		std::weak_ptr<BaseLevel> _blvl;
		std::weak_ptr<Dexterity> _dex;
		std::weak_ptr<Luck> _luk;
	};

	class CRIT
	: public Attribute<CRIT>
	{
	public:
		CRIT(std::weak_ptr<Entity> entity)
		: Attribute(entity)
		{ }
		~CRIT() { }

		void on_observable_changed(std::weak_ptr<Luck>) { compute(true); }

		uint32_t compute(bool notify);

		void set_luck(std::weak_ptr<Luck> luk) { _luk = luk; }

	private:
		std::weak_ptr<Luck> _luk;
	};

	class FLEE
	: public Attribute<FLEE>
	{
	public:
		FLEE(std::weak_ptr<Entity> entity)
		: Attribute(entity)
		{ }
		~FLEE() { }

		void on_observable_changed(std::weak_ptr<Agility>) { compute(true); }
		void on_observable_changed(std::weak_ptr<BaseLevel>) { compute(true); }
		void on_observable_changed(std::weak_ptr<Luck>) { compute(true); }

		uint32_t compute(bool notify);

		void set_agility(std::weak_ptr<Agility> agi) { _agi = agi; }
		void set_base_level(std::weak_ptr<BaseLevel> blvl) { _blvl = blvl; }
		void set_luck(std::weak_ptr<Luck> luk) { _luk = luk; }

	private:
		std::weak_ptr<Agility> _agi;
		std::weak_ptr<BaseLevel> _blvl;
		std::weak_ptr<Luck> _luk;
	};

	class AttackSpeed
	: public Attribute<AttackSpeed>
	{
	public:
		AttackSpeed(std::weak_ptr<Entity> entity)
		: Attribute(entity)
		{ }
		~AttackSpeed() { }

		void on_observable_changed(std::weak_ptr<Agility>) { compute(true); }
		void on_observable_changed(std::weak_ptr<BaseLevel>) { compute(true); }
		void on_observable_changed(std::weak_ptr<Dexterity>) { compute(true); }
		void on_weapon_changed() { compute(true); }

		uint32_t compute(bool notify);
		uint32_t compute_amotion();

		void set_agility(std::weak_ptr<Agility> agi) { _agi = agi; }
		void set_base_level(std::weak_ptr<BaseLevel> blvl) { _blvl = blvl; }
		void set_dexterity(std::weak_ptr<Dexterity> dex) { _dex = dex; }

	private:
		std::weak_ptr<Agility> _agi;
		std::weak_ptr<BaseLevel> _blvl;
		std::weak_ptr<Dexterity> _dex;
	};
}
}
}
}

#endif /* HORIZON_ZONE_GAME_TRAITS_ATTRIBUTESIMPL_HPP */
