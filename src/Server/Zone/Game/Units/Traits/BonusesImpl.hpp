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
 *  (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 **************************************************/

#ifndef HORIZON_ZONE_GAME_TRAITS_BONUSESIMPL_HPP
#define HORIZON_ZONE_GAME_TRAITS_BONUSESIMPL_HPP

#include "Attribute.hpp"
#include "Server/Zone/Definitions/UnitDefinitions.hpp"
#include "Server/Zone/Definitions/ItemDefinitions.hpp"
#include "Server/Zone/Definitions/MonsterDefinitions.hpp"
#include "Server/Zone/Game/Units/Traits/ObservableStatus.hpp"
 // Linux

namespace Horizon
{
namespace Zone
{
class Unit;
class Player;
namespace Bonuses
{
	class Bonus : public Traits::Attribute
	{
	public:
		// default for the clear() method in BonusArray, which is used to clear all bonuses of a certain type.
		// It shouldn't affect the copy and move semantics of Bonus.
		Bonus() : Traits::Attribute(std::shared_ptr<Unit>(), STATUS_POINT_INVALID, 0, 0, 0), _unit(std::shared_ptr<Unit>()), _applied(false),
		_parameter_1(0), _parameter_2(0), _parameter_3(0) { }

		Bonus(std::shared_ptr<Unit> unit, status_point_type status_point_type, int bonus, int parameter_1 = 0, int parameter_2 = 0, int parameter_3 = 0) 
		: Traits::Attribute(unit, status_point_type, 0, bonus, 0), _unit(unit), _applied(false),
		_parameter_1(parameter_1), _parameter_2(parameter_2), _parameter_3(parameter_3) { }

		// create copy and move constructors for Bonus
		Bonus(Bonus &other) : Traits::Attribute(other), _parameter_1(other._parameter_1), _parameter_2(other._parameter_2), _parameter_3(other._parameter_3) { }
		Bonus(Bonus &&other) noexcept : Traits::Attribute(std::move(other)), _parameter_1(other._parameter_1), _parameter_2(other._parameter_2), _parameter_3(other._parameter_3) { }

		// create copy and move assignment operators for Bonus
		Bonus& operator=(Bonus &other) { 
			if (this != &other) {
				Traits::Attribute::operator=(other);
            	_parameter_1 = other._parameter_1;
            	_parameter_2 = other._parameter_2;
            	_parameter_3 = other._parameter_3;
				_unit = other._unit;
				_applied = other._applied;
			}
			return *this; 
		}
		Bonus& operator=(Bonus &&other) noexcept { 
			if (this != &other) {
				Traits::Attribute::operator=(std::move(other));
				_parameter_1 = other._parameter_1;
				_parameter_2 = other._parameter_2;
				_parameter_3 = other._parameter_3;
				_unit = std::move(other._unit);
				_applied = other._applied;
			}
			return *this;
		}

		int32_t get() { return get_equip(); }
		void set(int bonus, bool notify_client = true) { set_equip(bonus, notify_client); }

		int32_t get_parameter_1() { return _parameter_1;}
		void set_parameter_1(int parameter_1) { _parameter_1 = parameter_1; }

		int32_t get_parameter_2() { return _parameter_2;}
		void set_parameter_2(int parameter_2) { _parameter_2 = parameter_2; }

		int32_t get_parameter_3() { return _parameter_3;}
		void set_parameter_3(int parameter_3) { _parameter_3 = parameter_3; }

		virtual void apply(int64_t &ret) { ret += get(); }
		virtual void remove(int64_t &ret) { ret -= get(); }

		std::shared_ptr<Unit> unit() { return _unit.lock(); }
		void unit(std::shared_ptr<Unit> e) { _unit = e; }

		void set_applied(bool applied) { _applied = applied; }
		bool is_applied() { return _applied; }
	private: 
		std::weak_ptr<Unit> _unit;
		bool _applied{false};
		int _parameter_1;
		int _parameter_2;
		int _parameter_3;
	};
	
	class IBonusArray
	{
	public:
		IBonusArray(status_point_type type) : _st_type(type) { }
		virtual ~IBonusArray() { }
		virtual void clear() = 0;
		virtual void clear(int type) = 0;

		status_point_type get_type() { return _st_type; }
		void set_type(status_point_type st_type) { _st_type = st_type; }
	
		status_point_type _st_type;
	};

	template <typename BONUSTYPE, int TYPEMAX>
	class BonusArray : public IBonusArray
	{
	public:
		BonusArray(std::shared_ptr<Unit> unit, status_point_type status_point_type) 
		: IBonusArray(status_point_type) { }

		// create copy and move constructors for BonusArray
		BonusArray(const BonusArray &other) : _types(other._types) { }
		BonusArray(BonusArray &&other) : _types(std::move(other._types)) { }

		// create copy and move assignment operators for BonusArray
		BonusArray& operator=(const BonusArray &other) { _types = other._types; return *this; }
		BonusArray& operator=(BonusArray &&other) { _types = std::move(other._types); return *this; }

		BONUSTYPE& operator[](int type) { return _types[type]; }
		const BONUSTYPE& operator[](int type) const { return _types[type]; }

		BONUSTYPE get(int type) { return _types[type]; }
		void set(int type, BONUSTYPE bonus) { _types[type] = std::move(bonus); }

		void clear()
		{
			for (int i = 0; i < TYPEMAX; i++)
				clear(i);
		}

		void clear(int type)
		{
			_types[type] = BONUSTYPE();
		}
		
		std::array<BONUSTYPE, TYPEMAX> _types;
	};

	/**
	 * Bonus
	 */
	class BonusAllStatus : public Bonus
	{
	public:
		BonusAllStatus(std::shared_ptr<Unit> unit, int value) : Bonus(unit, STATUS_ALLSTATUS, value) { }
	};

	class BonusAttackElement : public Bonus
	{
	public:
		BonusAttackElement(std::shared_ptr<Unit> unit, int value) : Bonus(unit, STATUS_ATKELE, value) { }
	};

	class BonusDefenseElement : public Bonus
	{
	public:
		BonusDefenseElement(std::shared_ptr<Unit> unit, int value) : Bonus(unit, STATUS_DEFELE, value) { }
	};

	class BonusCastPercent : public Bonus
	{
	public:
		BonusCastPercent(std::shared_ptr<Unit> unit, int value) : Bonus(unit, STATUS_CASTRATE, value) { }
	};

	class BonusMaxHPPercent : public Bonus
	{
	public:
		BonusMaxHPPercent(std::shared_ptr<Unit> unit, int value) : Bonus(unit, STATUS_MAXHPRATE, value) { }
	};

	class BonusMaxSPPercent : public Bonus
	{
	public:
		BonusMaxSPPercent(std::shared_ptr<Unit> unit, int value) : Bonus(unit, STATUS_MAXSPRATE, value) { }
	};

	class BonusSPPercent : public Bonus
	{
	public:
		BonusSPPercent(std::shared_ptr<Unit> unit, int value) : Bonus(unit, STATUS_SPRATE, value) { }
	};

	class BonusAttackRange : public Bonus
	{
	public:
		BonusAttackRange(std::shared_ptr<Unit> unit, int value) : Bonus(unit, STATUS_ATTACKRANGE, value) { }
	};

	class BonusAttackRangePercent : public Bonus
	{
	public:
		BonusAttackRangePercent(std::shared_ptr<Unit> unit, int value) : Bonus(unit, STATUS_ATTACKRANGE_RATE, value) { }
	};

	class BonusAddMovementSpeedPercent : public Bonus
	{
	public:
		BonusAddMovementSpeedPercent(std::shared_ptr<Unit> unit, int value) : Bonus(unit, STATUS_ADD_SPEED_RATE, value) { }
	};
	
	class BonusAttackSpeedPercent : public Bonus
	{
	public:
		BonusAttackSpeedPercent(std::shared_ptr<Unit> unit, int value) : Bonus(unit, STATUS_ASPD_RATE, value) { }
	};

	class BonusHPRecoveryPercent : public Bonus
	{
	public:
		BonusHPRecoveryPercent(std::shared_ptr<Unit> unit, int value) : Bonus(unit, STATUS_HP_RECOV_RATE, value) { }
	};

	class BonusSPRecoveryPercent : public Bonus
	{
	public:
		BonusSPRecoveryPercent(std::shared_ptr<Unit> unit, int value) : Bonus(unit, STATUS_SP_RECOV_RATE, value) { }
	};

	class BonusCriticalDefense : public Bonus
	{
	public:
		BonusCriticalDefense(std::shared_ptr<Unit> unit, int value) : Bonus(unit, STATUS_CRITICAL_DEF, value) { }
	};

	class BonusMeleeDefense : public Bonus
	{
	public:
		BonusMeleeDefense(std::shared_ptr<Unit> unit, int value) : Bonus(unit, STATUS_NEAR_DEF, value) { }
	};

	class BonusRangedDefense : public Bonus
	{
	public:
		BonusRangedDefense(std::shared_ptr<Unit> unit, int value) : Bonus(unit, STATUS_LONG_DEF, value) { }
	};

	class BonusDoubleAttackPercent : public Bonus
	{
	public:
		BonusDoubleAttackPercent(std::shared_ptr<Unit> unit, int value) : Bonus(unit, STATUS_DOUBLE_RATE, value) { }
	};

	class BonusMagicAttackPercent : public Bonus
	{
	public:
		BonusMagicAttackPercent(std::shared_ptr<Unit> unit, int value) : Bonus(unit, STATUS_MAGIC_ATK_RATE, value) { }
	};

	class BonusAttackPercent : public Bonus
	{
	public:
		BonusAttackPercent(std::shared_ptr<Unit> unit, int value) : Bonus(unit, STATUS_ATK_RATE, value) { }
	};

	class BonusMagicDefensePercent : public Bonus
	{
	public:
		BonusMagicDefensePercent(std::shared_ptr<Unit> unit, int value) : Bonus(unit, STATUS_MAGIC_DEF, value) { }
	};

	class BonusMiscDefensePercent : public Bonus
	{
	public:
		BonusMiscDefensePercent(std::shared_ptr<Unit> unit, int value) : Bonus(unit, STATUS_MISC_DEF, value) { }
	};

	class BonusPerfectHitPercent : public Bonus
	{
	public:
		BonusPerfectHitPercent(std::shared_ptr<Unit> unit, int value) : Bonus(unit, STATUS_PERFECT_HIT_RATE, value) { }
	};

	class BonusCriticalPercent : public Bonus
	{
	public:
		BonusCriticalPercent(std::shared_ptr<Unit> unit, int value) : Bonus(unit, STATUS_CRITICAL_RATE, value) { }
	};

	class BonusGetZenyNum : public Bonus
	{
	public:
		BonusGetZenyNum(std::shared_ptr<Unit> unit, int value) : Bonus(unit, STATUS_GET_ZENY_NUM, value) { }
	};

	class BonusAttackOnDefenseRatioForElement : public Bonus
	{
	public:
		BonusAttackOnDefenseRatioForElement(std::shared_ptr<Unit> unit, int value) : Bonus(unit, STATUS_DEF_RATIO_ATK_ELE, value) { }
	};

	class BonusAttackOnDefenseRatioForRace : public Bonus
	{
	public:
		BonusAttackOnDefenseRatioForRace(std::shared_ptr<Unit> unit, int value) : Bonus(unit, STATUS_DEF_RATIO_ATK_RACE, value) { }
	};
	
	class BonusHitPercent : public Bonus
	{
	public:
		BonusHitPercent(std::shared_ptr<Unit> unit, int value) : Bonus(unit, STATUS_HIT_RATE, value) { }
	};

	class BonusFleePercent : public Bonus
	{
	public:
		BonusFleePercent(std::shared_ptr<Unit> unit, int value) : Bonus(unit, STATUS_FLEE_RATE, value) { }
	};

	class BonusPerfectDodgePercent : public Bonus
	{
	public:
		BonusPerfectDodgePercent(std::shared_ptr<Unit> unit, int value) : Bonus(unit, STATUS_FLEE2_RATE, value) { }
	};

	class BonusSoftDefensePercent : public Bonus
	{
	public:
		BonusSoftDefensePercent(std::shared_ptr<Unit> unit, int value) : Bonus(unit, STATUS_DEF_RATE, value) { }
	};

	class BonusHardDefensePercent : public Bonus
	{
	public:
		BonusHardDefensePercent(std::shared_ptr<Unit> unit, int value) : Bonus(unit, STATUS_DEF2_RATE, value) { }
	};

	class BonusSoftMagicalDefensePercent : public Bonus
	{
	public:
		BonusSoftMagicalDefensePercent(std::shared_ptr<Unit> unit, int value) : Bonus(unit, STATUS_MDEF_RATE, value) { }
	};

	class BonusHardMagicalDefensePercent : public Bonus
	{
	public:
		BonusHardMagicalDefensePercent(std::shared_ptr<Unit> unit, int value) : Bonus(unit, STATUS_MDEF2_RATE, value) { }
	};

	class BonusRestartWithFullRecovery : public Bonus
	{
	public:
		BonusRestartWithFullRecovery(std::shared_ptr<Unit> unit, int value) : Bonus(unit, STATUS_RESTART_FULL_RECORVER, value) { }
	};

	class BonusCastCancelImmunity : public Bonus
	{
	public:
		BonusCastCancelImmunity(std::shared_ptr<Unit> unit, int value) : Bonus(unit, STATUS_NO_CASTCANCEL, value) { }
	};
	
	class BonusSizeModifierImmunity : public Bonus
	{
	public:
		BonusSizeModifierImmunity(std::shared_ptr<Unit> unit, int value) : Bonus(unit, STATUS_NO_SIZEFIX, value) { }
	};

	class BonusMagicDamageImmunity : public Bonus
	{
	public:
		BonusMagicDamageImmunity(std::shared_ptr<Unit> unit, int value) : Bonus(unit, STATUS_NO_MAGIC_DAMAGE, value) { }
	};

	class BonusWeaponDamageImmunity : public Bonus
	{
	public:
		BonusWeaponDamageImmunity(std::shared_ptr<Unit> unit, int value) : Bonus(unit, STATUS_NO_WEAPON_DAMAGE, value) { }
	};

	class BonusGemstoneImmunity : public Bonus
	{
	public:
		BonusGemstoneImmunity(std::shared_ptr<Unit> unit, int value) : Bonus(unit, STATUS_NO_GEMSTONE, value) { }
	};

	class BonusGearFuelImmunity : public Bonus
	{
	public:
		BonusGearFuelImmunity(std::shared_ptr<Unit> unit, int value) : Bonus(unit, STATUS_NO_GEARFUEL, value) { }
	};

	class BonusInfiniteEndure : public Bonus
	{
	public:
		BonusInfiniteEndure(std::shared_ptr<Unit> unit, int value) : Bonus(unit, STATUS_INFINITE_ENDURE, value) { }
	};

	class BonusUnbreakableWeapon : public Bonus
	{
	public:
		BonusUnbreakableWeapon(std::shared_ptr<Unit> unit, int value) : Bonus(unit, STATUS_UNBREAKABLE_WEAPON, value) { }
	};

	class BonusUnbreakableArmor : public Bonus
	{
	public:
		BonusUnbreakableArmor(std::shared_ptr<Unit> unit, int value) : Bonus(unit, STATUS_UNBREAKABLE_ARMOR, value) { }
	};	

	class BonusUnbreakableHelm : public Bonus
	{	
	public:
		BonusUnbreakableHelm(std::shared_ptr<Unit> unit, int value) : Bonus(unit, STATUS_UNBREAKABLE_HELM, value) { }
	};

	class BonusUnbreakableShield : public Bonus
	{
	public:
		BonusUnbreakableShield(std::shared_ptr<Unit> unit, int value) : Bonus(unit, STATUS_UNBREAKABLE_SHIELD, value) { }
	};

	class BonusSPGainOnMobKill : public Bonus
	{
	public:
		BonusSPGainOnMobKill(std::shared_ptr<Unit> unit, int value) : Bonus(unit, STATUS_SP_GAIN_VALUE, value) { }
	};
	
	class BonusHPGainOnMobKill : public Bonus
	{
	public:
		BonusHPGainOnMobKill(std::shared_ptr<Unit> unit, int value) : Bonus(unit, STATUS_HP_GAIN_VALUE, value) { }
	};

	class BonusDamageSplashRange : public Bonus
	{
	public:
		BonusDamageSplashRange(std::shared_ptr<Unit> unit, int value) : Bonus(unit, STATUS_SPLASH_RANGE, value) { }
	};

	class BonusMeleeWeaponDamageReflectPercentOnSelf : public Bonus
	{
	public:
		BonusMeleeWeaponDamageReflectPercentOnSelf(std::shared_ptr<Unit> unit, int value) : Bonus(unit, STATUS_SHORT_WEAPON_DAMAGE_RETURN, value) { }
	};

	class BonusRangedWeaponDamageReflectPercentOnSelf : public Bonus
	{
	public:
		BonusRangedWeaponDamageReflectPercentOnSelf(std::shared_ptr<Unit> unit, int value) : Bonus(unit, STATUS_LONG_WEAPON_DAMAGE_RETURN, value) { }
	};

	class BonusWeaponBreakPercent : public Bonus
	{
	public:
		BonusWeaponBreakPercent(std::shared_ptr<Unit> unit, int value) : Bonus(unit, STATUS_BREAK_WEAPON_RATE, value) { }
	};

	class BonusArmorBreakPercent : public Bonus
	{
	public:
		BonusArmorBreakPercent(std::shared_ptr<Unit> unit, int value) : Bonus(unit, STATUS_BREAK_ARMOR_RATE, value) { }
	};

	class BonusAddStealPercent : public Bonus
	{
	public:
		BonusAddStealPercent(std::shared_ptr<Unit> unit, int value) : Bonus(unit, STATUS_ADD_STEAL_RATE, value) { }
	};

	class BonusCriticalDamagePercent : public Bonus
	{
	public:
		BonusCriticalDamagePercent(std::shared_ptr<Unit> unit, int value) : Bonus(unit, STATUS_CRITICAL_DAMAGE_RATE, value) { }
	};

	class BonusDisableHPRecovery : public Bonus
	{
	public:
		BonusDisableHPRecovery(std::shared_ptr<Unit> unit, int value) : Bonus(unit, STATUS_HP_RECOV_STOP, value) { }
	};

	class BonusDisableSPRecovery : public Bonus
	{
	public:
		BonusDisableSPRecovery(std::shared_ptr<Unit> unit, int value) : Bonus(unit, STATUS_SP_RECOV_STOP, value) { }
	};

	class BonusMagicDamageReflectPercentOnSelf : public Bonus
	{
	public:
		BonusMagicDamageReflectPercentOnSelf(std::shared_ptr<Unit> unit, int value) : Bonus(unit, STATUS_MAGIC_DAMAGE_RETURN, value) { }
	};

	class BonusShortWeaponDamagePercent : public Bonus
	{
	public:
		BonusShortWeaponDamagePercent(std::shared_ptr<Unit> unit, int value) : Bonus(unit, STATUS_ADD_SHORT_WEAPON_DAMAGE, value) { }
	};

	class BonusLongWeaponDamagePercent : public Bonus
	{
	public:
		BonusLongWeaponDamagePercent(std::shared_ptr<Unit> unit, int value) : Bonus(unit, STATUS_ADD_LONG_WEAPON_DAMAGE, value) { }
	};

	class BonusItemUsageImmunity : public Bonus
	{
	public:
		BonusItemUsageImmunity(std::shared_ptr<Unit> unit, int value) : Bonus(unit, STATUS_ITEM_NO_USE, value) { }
	};

	class BonusKnockBackImmunity : public Bonus
	{
	public:
		BonusKnockBackImmunity(std::shared_ptr<Unit> unit, int value) : Bonus(unit, STATUS_NO_KNOCKBACK, value) { }
	};

	/**
	 * Bonus
	 */
	class BonusAddAttackPercentageToElement : public BonusArray<Bonus, ELE_MAX>
	{
	public:
		BonusAddAttackPercentageToElement(std::shared_ptr<Unit> unit) : BonusArray<Bonus, ELE_MAX>(unit, STATUS_ADDATKELE) { }
		
		void set(int type, int bonus, bool notify_client = true) { _types[type].set(bonus, notify_client); }
	};

	class BonusAddAttackPercentageToRace : public BonusArray<Bonus, MONSTER_RACE_MAX>
	{
	public:
		BonusAddAttackPercentageToRace(std::shared_ptr<Unit> unit) : BonusArray<Bonus, MONSTER_RACE_MAX>(unit, STATUS_ADDATKRACE) { }
	
		void set(int type, int bonus, bool notify_client = true) { _types[type].set(bonus, notify_client); }
	};

	class BonusAddAttackPercentageToSize : public BonusArray<Bonus, ESZ_MAX>
	{
	public:
		BonusAddAttackPercentageToSize(std::shared_ptr<Unit> unit) : BonusArray<Bonus, ESZ_MAX>(unit, STATUS_ADDSIZE) { }
	
		void set(int type, int bonus, bool notify_client = true) { _types[type].set(bonus, notify_client); }
	};

	class BonusSubAttackPercentageFromElement : public BonusArray<Bonus, ELE_MAX>
	{
	public:
		BonusSubAttackPercentageFromElement(std::shared_ptr<Unit> unit) : BonusArray<Bonus, ELE_MAX>(unit, STATUS_SUBELE) { }
	
		void set(int type, int bonus, bool notify_client = true) { _types[type].set(bonus, notify_client); }
	};

	class BonusSubAttackPercentageFromRace : public BonusArray<Bonus, MONSTER_RACE_MAX>
	{
	public:
		BonusSubAttackPercentageFromRace(std::shared_ptr<Unit> unit) : BonusArray<Bonus, MONSTER_RACE_MAX>(unit, STATUS_SUBRACE) { }
	
		void set(int type, int bonus, bool notify_client = true) { _types[type].set(bonus, notify_client); }
	};

	struct s_add_effect
	{
		enum auto_trigger_type {
			ATF_SELF      = 0x01,
			ATF_TARGET    = 0x02,
			ATF_SHORT     = 0x04,
			ATF_LONG      = 0x08,
			ATF_WEAPON    = 0x10,
			ATF_MAGIC     = 0x20,
			ATF_MISC      = 0x40
		};

		int eff_id;  ///< Effect ID
		int16_t rate;       ///< Base success rate
		int16_t arrow_rate; ///< Success rate for ranged attacks.
		uint8_t tigger_type;       ///< Trigger flag (@see enum auto_trigger_flag)
		uint16_t duration;  ///< Optional, non-reducible duration in ms. If 0, the default, reducible effect's duration is used.
	};

	class BonusAddEffectOnDamage : public BonusArray<s_add_effect, MAX_STATUS_EFFECT_BONUSES>
	{
	public:
		BonusAddEffectOnDamage(std::shared_ptr<Unit> unit) : BonusArray<s_add_effect, MAX_STATUS_EFFECT_BONUSES>(unit, STATUS_ADDEFF) { }
	
		void set(int type, s_add_effect bonus, bool notify_client = true) { _types[type] = bonus; }
	};

	class BonusAddEffectWhenDamaged : public BonusArray<s_add_effect, MAX_STATUS_EFFECT_BONUSES>
	{
	public:
		BonusAddEffectWhenDamaged(std::shared_ptr<Unit> unit) : BonusArray<s_add_effect, MAX_STATUS_EFFECT_BONUSES>(unit, STATUS_ADDEFF2) { }
	
		void set(int type, s_add_effect bonus, bool notify_client = true) { _types[type] = bonus; }
	};

	class BonusRessistEffect : public BonusArray<s_add_effect, MAX_STATUS_EFFECT_BONUSES>
	{
	public:
		BonusRessistEffect(std::shared_ptr<Unit> unit) : BonusArray<s_add_effect, MAX_STATUS_EFFECT_BONUSES>(unit, STATUS_RESEFF) { }
	
		void set(int type, s_add_effect bonus, bool notify_client = true) { _types[type] = bonus; }
	};

	class BonusAddMagicAttackPercentageToElement : public BonusArray<Bonus, ELE_MAX>
	{
	public:
		BonusAddMagicAttackPercentageToElement(std::shared_ptr<Unit> unit) : BonusArray<Bonus, ELE_MAX>(unit, STATUS_MAGIC_ADDELE) { }
	
		void set(int type, int bonus, bool notify_client = true) { _types[type].set(bonus, notify_client); }
	};

	class BonusAddMagicAttackPercentageToRace : public BonusArray<Bonus, MONSTER_RACE_MAX>
	{
	public:
		BonusAddMagicAttackPercentageToRace(std::shared_ptr<Unit> unit) : BonusArray<Bonus, MONSTER_RACE_MAX>(unit, STATUS_MAGIC_ADDRACE) { }
	
		void set(int type, int bonus, bool notify_client = true) { _types[type].set(bonus, notify_client); }
	};

	class BonusAddMagicAttackPercentageToSize : public BonusArray<Bonus, ESZ_MAX>
	{
	public:
		BonusAddMagicAttackPercentageToSize(std::shared_ptr<Unit> unit) : BonusArray<Bonus, ESZ_MAX>(unit, STATUS_MAGIC_ADDSIZE) { }
	
		void set(int type, int bonus, bool notify_client = true) { _types[type].set(bonus, notify_client); }
	};
	
	class BonusAddEffectOnMagicAttack : public BonusArray<s_add_effect, MAX_STATUS_EFFECT_BONUSES>
	{
	public:
		BonusAddEffectOnMagicAttack(std::shared_ptr<Unit> unit) : BonusArray<s_add_effect, MAX_STATUS_EFFECT_BONUSES>(unit, STATUS_ADDEFFMAGIC) { }
	
		void set(int type, s_add_effect bonus, bool notify_client = true) { _types[type] = bonus; }
	};

	class BonusResistMagicAttackFromRace : public BonusArray<Bonus, MONSTER_RACE_MAX>
	{
	public:
		BonusResistMagicAttackFromRace(std::shared_ptr<Unit> unit) : BonusArray<Bonus, MONSTER_RACE_MAX>(unit, STATUS_MAGIC_SUBRACE) { }
	
		void set(int type, int bonus, bool notify_client = true) { _types[type].set(bonus, notify_client); }
	};

	class BonusAddDamageToClass : public BonusArray<Bonus, MAX_PC_BONUSES_PER_GROUP>
	{
	public:
		BonusAddDamageToClass(std::shared_ptr<Unit> unit) : BonusArray<Bonus, MAX_PC_BONUSES_PER_GROUP>(unit, STATUS_ADD_DAMAGE_CLASS) { }
	
		void set(int type, int bonus, bool notify_client = true) { _types[type].set(bonus, notify_client); }
	};

	class BonusAddMagicDamageToClass : public BonusArray<Bonus, MAX_PC_BONUSES_PER_GROUP>
	{
	public:
		BonusAddMagicDamageToClass(std::shared_ptr<Unit> unit) : BonusArray<Bonus, MAX_PC_BONUSES_PER_GROUP>(unit, STATUS_ADD_MAGIC_DAMAGE_CLASS) { }
	
		void set(int type, int bonus, bool notify_client = true) { _types[type].set(bonus, notify_client); }
	};

	class BonusAddDefenseToClass : public BonusArray<Bonus, MAX_PC_BONUSES_PER_GROUP>
	{
	public:
		BonusAddDefenseToClass(std::shared_ptr<Unit> unit) : BonusArray<Bonus, MAX_PC_BONUSES_PER_GROUP>(unit, STATUS_ADD_DEF_CLASS) { }
	
		void set(int type, int bonus, bool notify_client = true) { _types[type].set(bonus, notify_client); }
	};

	class BonusAddMagicalDefenseToClass : public BonusArray<Bonus, MAX_PC_BONUSES_PER_GROUP>
	{
	public:
		BonusAddMagicalDefenseToClass(std::shared_ptr<Unit> unit) : BonusArray<Bonus, MAX_PC_BONUSES_PER_GROUP>(unit, STATUS_ADD_MDEF_CLASS) { }
	
		void set(int type, int bonus, bool notify_client = true) { _types[type].set(bonus, notify_client); }
	};

	class BonusHPDrainPercent : public Bonus
	{
	public:
		BonusHPDrainPercent(std::shared_ptr<Unit> unit, int chance, int rate) : Bonus(unit, STATUS_HP_DRAIN_RATE, chance, rate) { }
	};

	class BonusHPDrainValue : public Bonus
	{
	public:
		BonusHPDrainValue(std::shared_ptr<Unit> unit, int chance, int value) : Bonus(unit, STATUS_HP_DRAIN_VALUE, chance, value) { }
	};

	class BonusSPDrainPercent : public Bonus
	{
	public:
		BonusSPDrainPercent(std::shared_ptr<Unit> unit, int chance, int rate) : Bonus(unit, STATUS_SP_DRAIN_RATE, chance, rate) { }
	};

	class BonusSPDrainValue : public Bonus
	{
	public:
		BonusSPDrainValue(std::shared_ptr<Unit> unit, int chance, int value) : Bonus(unit, STATUS_SP_DRAIN_VALUE, chance, value) { }
	};
	
	class BonusAddWeaponComaToElement : public BonusArray<Bonus, ELE_MAX>
	{
	public:
		BonusAddWeaponComaToElement(std::shared_ptr<Unit> unit) : BonusArray<Bonus, ELE_MAX>(unit, STATUS_WEAPON_COMA_ELE) { }
	
		void set(int type, int bonus, bool notify_client = true) { _types[type].set(bonus, notify_client); }
	};

	class BonusAddWeaponComaToRace : public BonusArray<Bonus, MONSTER_RACE_MAX>
	{
	public:
		BonusAddWeaponComaToRace(std::shared_ptr<Unit> unit) : BonusArray<Bonus, MONSTER_RACE_MAX>(unit, STATUS_WEAPON_COMA_RACE) { }
	
		void set(int type, int bonus, bool notify_client = true) { _types[type].set(bonus, notify_client); }
	};

	class BonusAddWeaponComaToSubElement : public BonusArray<Bonus, ELE_MAX>
	{
	public:
		BonusAddWeaponComaToSubElement(std::shared_ptr<Unit> unit) : BonusArray<Bonus, ELE_MAX>(unit, STATUS_WEAPON_COMA_ELE2) { }
	
		void set(int type, int bonus, bool notify_client = true) { _types[type].set(bonus, notify_client); }
	};

	class BonusAddWeaponComaToSubRace : public BonusArray<Bonus, MONSTER_RACE2_MAX>
	{
	public:
		BonusAddWeaponComaToSubRace(std::shared_ptr<Unit> unit) : BonusArray<Bonus, MONSTER_RACE2_MAX>(unit, STATUS_WEAPON_COMA_RACE2) { }
	
		void set(int type, int bonus, bool notify_client = true) { _types[type].set(bonus, notify_client); }
	};

	class BonusAddAttack : public BonusArray<Bonus, IT_WT_MAX_WEAPON_TYPE>
	{
	public:
		BonusAddAttack(std::shared_ptr<Unit> unit) : BonusArray<Bonus, IT_WT_MAX_WEAPON_TYPE>(unit, STATUS_WEAPON_ATK) { }
	
		void set(int type, int bonus, bool notify_client = true) { _types[type].set(bonus, notify_client); }
	};

	class BonusAddAttackPercent : public BonusArray<Bonus, IT_WT_MAX_WEAPON_TYPE>
	{
	public:
		BonusAddAttackPercent(std::shared_ptr<Unit> unit) : BonusArray<Bonus, IT_WT_MAX_WEAPON_TYPE>(unit, STATUS_WEAPON_ATK_RATE) { }
	
		void set(int type, int bonus, bool notify_client = true) { _types[type].set(bonus, notify_client); }
	};

	class BonusCriticalRace : public BonusArray<Bonus, MONSTER_RACE_MAX>
	{
	public:
		BonusCriticalRace(std::shared_ptr<Unit> unit) : BonusArray<Bonus, MONSTER_RACE_MAX>(unit, STATUS_CRITICALRACE) { }
	
		void set(int type, int bonus, bool notify_client = true) { _types[type].set(bonus, notify_client); }
	};

	class BonusCriticalRacePercent : public BonusArray<Bonus, MONSTER_RACE_MAX>
	{
	public:
		BonusCriticalRacePercent(std::shared_ptr<Unit> unit) : BonusArray<Bonus, MONSTER_RACE_MAX>(unit, STATUS_CRITICALRACERATE) { }
	
		void set(int type, int bonus, bool notify_client = true) { _types[type].set(bonus, notify_client); }
	};

	class BonusDamageReductionAgainstSize : public BonusArray<Bonus, ESZ_MAX>
	{
	public:
		BonusDamageReductionAgainstSize(std::shared_ptr<Unit> unit) : BonusArray<Bonus, ESZ_MAX>(unit, STATUS_SUB_SIZE) { }
	
		void set(int type, int bonus, bool notify_client = true) { _types[type].set(bonus, notify_client); }
	};

	class BonusMagicDamageReductionAgainstSize : public BonusArray<Bonus, ESZ_MAX>
	{
	public:
		BonusMagicDamageReductionAgainstSize(std::shared_ptr<Unit> unit) : BonusArray<Bonus, ESZ_MAX>(unit, STATUS_MAGIC_SUB_SIZE) { }
	
		void set(int type, int bonus, bool notify_client = true) { _types[type].set(bonus, notify_client); }
	};

	class BonusExpPercentPerRace : public BonusArray<Bonus, MONSTER_RACE_MAX>
	{
	public:
		BonusExpPercentPerRace(std::shared_ptr<Unit> unit) : BonusArray<Bonus, MONSTER_RACE_MAX>(unit, STATUS_EXP_RATE) { }
	
		void set(int type, int bonus, bool notify_client = true) { _types[type].set(bonus, notify_client); }
	};

	class BonusJobPercentPerRace : public BonusArray<Bonus, MONSTER_RACE_MAX>
	{
	public:
		BonusJobPercentPerRace(std::shared_ptr<Unit> unit) : BonusArray<Bonus, MONSTER_RACE_MAX>(unit, STATUS_JOB_RATE) { }
	
		void set(int type, int bonus, bool notify_client = true) { _types[type].set(bonus, notify_client); }
	};

	class BonusSkillAttack : public BonusArray<Bonus, MAX_PC_BONUSES_PER_GROUP>
	{
	public:
		BonusSkillAttack(std::shared_ptr<Unit> unit) : BonusArray<Bonus, MAX_PC_BONUSES_PER_GROUP>(unit, STATUS_SKILL_ATK) { }
	
		void set(int type, int bonus, bool notify_client = true) { _types[type].set(bonus, notify_client); }
	};

	class BonusReduceSPConsumptionOfSkillByPercent : public BonusArray<Bonus, MAX_PC_BONUSES_PER_GROUP>
	{
	public:
		BonusReduceSPConsumptionOfSkillByPercent(std::shared_ptr<Unit> unit) : BonusArray<Bonus, MAX_PC_BONUSES_PER_GROUP>(unit, STATUS_SKILL_USESPRATE) { }
	
		void set(int type, int bonus, bool notify_client = true) { _types[type].set(bonus, notify_client); }
	};

	class BonusReduceSPConsumptionOfSkill : public BonusArray<Bonus, MAX_PC_BONUSES_PER_GROUP>
	{
	public:
		BonusReduceSPConsumptionOfSkill(std::shared_ptr<Unit> unit) : BonusArray<Bonus, MAX_PC_BONUSES_PER_GROUP>(unit, STATUS_SKILL_USESP) { }
	
		void set(int type, int bonus, bool notify_client = true) { _types[type].set(bonus, notify_client); }
	};

	class BonusLearnedSkillHeal : public BonusArray<Bonus, MAX_PC_BONUSES_PER_GROUP>
	{
	public:
		BonusLearnedSkillHeal(std::shared_ptr<Unit> unit) : BonusArray<Bonus, MAX_PC_BONUSES_PER_GROUP>(unit, STATUS_SKILL_LEARNED_HEAL) { }
	
		void set(int type, int bonus, bool notify_client = true) { _types[type].set(bonus, notify_client); }
	};

	class BonusHealOfSkillCastedOnSelf : public BonusArray<Bonus, MAX_PC_BONUSES_PER_GROUP>
	{
	public:
		BonusHealOfSkillCastedOnSelf(std::shared_ptr<Unit> unit) : BonusArray<Bonus, MAX_PC_BONUSES_PER_GROUP>(unit, STATUS_SKILL_HEALPOWER_OF_SKILL) { }
	
		void set(int type, int bonus, bool notify_client = true) { _types[type].set(bonus, notify_client); }
	};

	class BonusSkillKnockback : public BonusArray<Bonus, MAX_PC_BONUSES_PER_GROUP>
	{
	public:
		BonusSkillKnockback(std::shared_ptr<Unit> unit) : BonusArray<Bonus, MAX_PC_BONUSES_PER_GROUP>(unit, STATUS_SKILL_BLOWN) { }
	
		void set(int type, int bonus, bool notify_client = true) { _types[type].set(bonus, notify_client); }
	};

	class BonusSkillCastPercent : public BonusArray<Bonus, MAX_PC_BONUSES_PER_GROUP>
	{
	public:
		BonusSkillCastPercent(std::shared_ptr<Unit> unit) : BonusArray<Bonus, MAX_PC_BONUSES_PER_GROUP>(unit, STATUS_SKILL_CAST) { }
	
		void set(int type, int bonus, bool notify_client = true) { _types[type].set(bonus, notify_client); }
	};

	class BonusSkillCooldown : public BonusArray<Bonus, MAX_PC_BONUSES_PER_GROUP>
	{
	public:
		BonusSkillCooldown(std::shared_ptr<Unit> unit) : BonusArray<Bonus, MAX_PC_BONUSES_PER_GROUP>(unit, STATUS_SKILL_COOLDOWN) { }
	
		void set(int type, int bonus, bool notify_client = true) { _types[type].set(bonus, notify_client); }
	};

	class BonusSkillFixCastPercent : public BonusArray<Bonus, MAX_PC_BONUSES_PER_GROUP>
	{
	public:
		BonusSkillFixCastPercent(std::shared_ptr<Unit> unit) : BonusArray<Bonus, MAX_PC_BONUSES_PER_GROUP>(unit, STATUS_SKILL_FIXCAST) { }
	
		void set(int type, int bonus, bool notify_client = true) { _types[type].set(bonus, notify_client); }
	};

	class BonusSkillVariableCastPercent : public BonusArray<Bonus, MAX_PC_BONUSES_PER_GROUP>
	{
	public:
		BonusSkillVariableCastPercent(std::shared_ptr<Unit> unit) : BonusArray<Bonus, MAX_PC_BONUSES_PER_GROUP>(unit, STATUS_SKILL_VARCAST) { }
	
		void set(int type, int bonus, bool notify_client = true) { _types[type].set(bonus, notify_client); }
	};

	class BonusResistSkillDamagePercent : public BonusArray<Bonus, MAX_PC_BONUSES_PER_GROUP>
	{
	public:
		BonusResistSkillDamagePercent(std::shared_ptr<Unit> unit) : BonusArray<Bonus, MAX_PC_BONUSES_PER_GROUP>(unit, STATUS_SKILL_RESIST) { }
	
		void set(int type, int bonus, bool notify_client = true) { _types[type].set(bonus, notify_client); }
	};

	class BonusIgnoreDefenseFromElement : public BonusArray<Bonus, ELE_MAX>
	{
	public:
		BonusIgnoreDefenseFromElement(std::shared_ptr<Unit> unit) : BonusArray<Bonus, ELE_MAX>(unit, STATUS_IGNORE_DEF_ELE) { }
	
		void set(int type, int bonus, bool notify_client = true) { _types[type].set(bonus, notify_client); }
	};

	class BonusIgnoreDefenseFromRace : public BonusArray<Bonus, MONSTER_RACE_MAX>
	{
	public:
		BonusIgnoreDefenseFromRace(std::shared_ptr<Unit> unit) : BonusArray<Bonus, MONSTER_RACE_MAX>(unit, STATUS_IGNORE_DEF_RACE) { }
	
		void set(int type, int bonus, bool notify_client = true) { _types[type].set(bonus, notify_client); }
	};

	class BonusIgnoreMagicDefenseFromElement : public BonusArray<Bonus, ELE_MAX>
	{
	public:
		BonusIgnoreMagicDefenseFromElement(std::shared_ptr<Unit> unit) : BonusArray<Bonus, ELE_MAX>(unit, STATUS_IGNORE_MDEF_ELE) { }
	
		void set(int type, int bonus, bool notify_client = true) { _types[type].set(bonus, notify_client); }
	};

	class BonusIgnoreMagicDefenseFromRace : public BonusArray<Bonus, MONSTER_RACE_MAX>
	{
	public:
		BonusIgnoreMagicDefenseFromRace(std::shared_ptr<Unit> unit) : BonusArray<Bonus, MONSTER_RACE_MAX>(unit, STATUS_IGNORE_MDEF_RACE) { }
	
		void set(int type, int bonus, bool notify_client = true) { _types[type].set(bonus, notify_client); }
	};

	class BonusAddEleWeaponDamagePercent : public BonusArray<Bonus, ELE_MAX>
	{
	public:
		BonusAddEleWeaponDamagePercent(std::shared_ptr<Unit> unit) : BonusArray<Bonus, ELE_MAX>(unit, STATUS_ADD_ELEWEAPONDAMAGE_RATE) { }
	
		void set(int type, int bonus, bool notify_client = true) { _types[type].set(bonus, notify_client); }
	};

	class BonusAddEleMagicDamagePercent : public BonusArray<Bonus, ELE_MAX>
	{
	public:
		BonusAddEleMagicDamagePercent(std::shared_ptr<Unit> unit) : BonusArray<Bonus, ELE_MAX>(unit, STATUS_ADD_ELEMAGICDAMAGE_RATE) { }
	
		void set(int type, int bonus, bool notify_client = true) { _types[type].set(bonus, notify_client); }
	};

	struct s_autospell
	{
		short lv;
		short id;
		short rate;
		unsigned int flag;
		short card_id;
		short skill;
		short count;
	};

	class BonusAutoSpellOnSkill : public BonusArray<s_autospell, MAX_AUTOSPELL>
	{
	public:
		BonusAutoSpellOnSkill(std::shared_ptr<Unit> unit) : BonusArray<s_autospell, MAX_AUTOSPELL>(unit, STATUS_AUTOSPELL) { }
	
		void set(int type, s_autospell bonus, bool notify_client = true) { _types[type] = bonus; }
	};

	class BonusAutoSpellOnAttack : public BonusArray<s_autospell, MAX_AUTOSPELL>
	{
	public:
		BonusAutoSpellOnAttack(std::shared_ptr<Unit> unit) : BonusArray<s_autospell, MAX_AUTOSPELL>(unit, STATUS_AUTOSPELLONATK) { }
	
		void set(int type, s_autospell bonus, bool notify_client = true) { _types[type] = bonus; }
	};

	class BonusAutoSpellOnReceiveDamage : public BonusArray<s_autospell, MAX_AUTOSPELL>
	{
	public:
		BonusAutoSpellOnReceiveDamage(std::shared_ptr<Unit> unit) : BonusArray<s_autospell, MAX_AUTOSPELL>(unit, STATUS_AUTOSPELLHIT) { }
	
		void set(int type, s_autospell bonus, bool notify_client = true) { _types[type] = bonus; }
	};

	class BonusAutoSpellOnSelf : public BonusArray<s_autospell, MAX_AUTOSPELL>
	{
	public:
		BonusAutoSpellOnSelf(std::shared_ptr<Unit> unit) : BonusArray<s_autospell, MAX_AUTOSPELL>(unit, STATUS_AUTOSPELLONSELF) { }
	
		void set(int type, s_autospell bonus, bool notify_client = true) { _types[type] = bonus; }
	};


	/** 
	 * Bonus
	 */

	class BonusHPVanishPercent : public Bonus
	{
	public:
		BonusHPVanishPercent(std::shared_ptr<Unit> unit, int proc_rate, int /* (battle_attack_type) */ attack_trigger, int percent_vanish) 
		: Bonus(unit, STATUS_HPVANISH, proc_rate, attack_trigger, percent_vanish) { }
	};

	class BonusSPVanishPercent : public Bonus
	{
	public:
		BonusSPVanishPercent(std::shared_ptr<Unit> unit, int proc_rate, int /* (battle_attack_type) */ attack_trigger, int percent_vanish) 
		: Bonus(unit, STATUS_SPVANISH, proc_rate, attack_trigger, percent_vanish) { }
	};

	class BonusRaise : public Bonus
	{
	public:
		BonusRaise(std::shared_ptr<Unit> unit, int hp_rate, int sp_rate, int proc_rate) : Bonus(unit, STATUS_RAISE, hp_rate, sp_rate, proc_rate) { }
	};

	class BonusAddItemDropOnMonsterKill : public Bonus
	{
	public:
		BonusAddItemDropOnMonsterKill(std::shared_ptr<Unit> unit, int item_id, int race, int count) : Bonus(unit, STATUS_ADD_MONSTER_DROP_ITEM, item_id, race, count) { }
	};

	class BonusHPDrainOnMonsterKill : public Bonus
	{
	public:
		BonusHPDrainOnMonsterKill(std::shared_ptr<Unit> unit, int race, int proc_rate, int value) : Bonus(unit, STATUS_DEF_HP_DRAIN_VALUE, race, proc_rate, value) { }
	};

	class BonusSPDrainOnMonsterKill : public Bonus
	{
	public:
		BonusSPDrainOnMonsterKill(std::shared_ptr<Unit> unit, int race, int proc_rate, int value) : Bonus(unit, STATUS_DEF_SP_DRAIN_VALUE, race, proc_rate, value) { }
	};
}
}
}

#endif /* HORIZON_ZONE_GAME_TRAITS_BONUSESIMPL_HPP */
