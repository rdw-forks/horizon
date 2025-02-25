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

#ifndef HORIZON_ZONE_GAME_TRAITS_STATUS_HPP
#define HORIZON_ZONE_GAME_TRAITS_STATUS_HPP

#include "Server/Zone/Game/Units/Traits/Attribute.hpp"
#include "Server/Zone/Game/Units/Traits/AttributesImpl.hpp"
#include "Server/Zone/Game/Units/Traits/BonusesImpl.hpp"
#include "Server/Zone/Game/Units/Traits/Appearance.hpp"
#include "Server/Zone/Definitions/UnitDefinitions.hpp"

#include <ctime>
#include <queue>
#include <algorithm>
#include <memory>
#include <vector>

 // Linux

struct item_entry_data;
struct monster_config_data;
struct job_config_data;

namespace Horizon
{
namespace Zone
{
class Unit;
namespace Units
{
	class Player;
	class NPC;
	class Mob;
}
namespace Traits
{
class Status
{
public:
	class StatusRegistry
	{
	public:
        enum status_operation_type
        {
            STATUS_OPERATION_ADD_TO_BASE = 0,
            STATUS_OPERATION_SUBTRACT_FROM_BASE,
            STATUS_OPERATION_ADD_TO_EQUIP,
            STATUS_OPERATION_SUBTRACT_FROM_EQUIP,
            STATUS_OPERATION_ADD_TO_STATUS,
            STATUS_OPERATION_SUBTRACT_FROM_STATUS,
			STATUS_OPERATION_ADD_TO_BASE_TEMPORARY,
			STATUS_OPERATION_SUBTRACT_FROM_BASE_TEMPORARY,
			STATUS_OPERATION_ADD_TO_EQUIP_TEMPORARY,
			STATUS_OPERATION_SUBTRACT_FROM_EQUIP_TEMPORARY,
			STATUS_OPERATION_ADD_TO_STATUS_TEMPORARY,
			STATUS_OPERATION_SUBTRACT_FROM_STATUS_TEMPORARY,
			STATUS_OPERATION_ADD_TO_BASE_INTERVAL,
			STATUS_OPERATION_SUBTRACT_FROM_BASE_INTERVAL,
			STATUS_OPERATION_ADD_TO_EQUIP_INTERVAL,
			STATUS_OPERATION_SUBTRACT_FROM_EQUIP_INTERVAL,
			STATUS_OPERATION_ADD_TO_STATUS_INTERVAL,
			STATUS_OPERATION_SUBTRACT_FROM_STATUS_INTERVAL
        };

		class StatusOperation
		{
		public:
			StatusOperation(Attribute *attribute, status_operation_type type, uint32_t value, std::string source)
			: _priority(std::time(nullptr)), _attribute(attribute), _type(type), _value(value), _source(source) { }
			StatusOperation(Attribute *attribute, status_operation_type type, uint32_t value, uint64_t duration, std::string source)
			: _priority(std::time(nullptr)), _attribute(attribute), _type(type), _value(value), _duration(duration), _source(source) { }
			StatusOperation(Attribute *attribute, status_operation_type type, uint32_t value, s_min_max minmax, uint64_t duration, uint64_t interval, std::string source)
			: _priority(std::time(nullptr)), _attribute(attribute), _type(type), _value(value), _minmax(minmax), _duration(duration), _interval(interval), _source(source) { }

			virtual ~StatusOperation() {}

			void execute();

			uint16_t get_priority() { return _priority; }
			void set_priority(uint16_t priority) { _priority = priority; }

			status_operation_type get_type() { return _type; }
			uint16_t get_value() { return _value; }

			void set_duration(uint64_t duration) { _duration = duration; }
			uint64_t get_duration() { return _duration; }

			void set_interval(uint64_t interval) { _interval = interval; }
			uint64_t get_interval() { return _interval; }

			void set_source(const std::string &source) { _source = source; }
			std::string get_source() { return _source; }

		protected:
			Attribute *_attribute{nullptr};
			status_operation_type _type{STATUS_OPERATION_ADD_TO_BASE};
			uint32_t _value{0};
			s_min_max _minmax{0, 0};
			uint16_t _priority{0};
			uint64_t _duration{0};
			uint64_t _interval{0};
			std::string _source{""};
		};

    	// Define a comparison function for the priority queue
    	struct CompareStatusOperation {
    	    bool operator()(StatusOperation* op1, StatusOperation* op2) {
    	        return op1->get_priority() < op2->get_priority();
    	    }
    	};

		void add_to_base(Attribute *attribute, uint32_t value, std::string source);
		void subtract_from_base(Attribute *attribute, uint32_t value, std::string source);
		void add_to_equip(Attribute *attribute, uint32_t value, std::string source);
		void subtract_from_equip(Attribute *attribute, uint32_t value, std::string source);
		void add_to_status(Attribute *attribute, uint32_t value, std::string source);
		void subtract_from_status(Attribute *attribute, uint32_t value, std::string source);

		void add_to_base_temporary(Attribute *attribute, uint32_t value, uint64_t duration, std::string source);
		void sub_from_base_temporary(Attribute *attribute, uint32_t value, uint64_t duration, std::string source);
		void add_to_equip_temporary(Attribute *attribute, uint32_t value, uint64_t duration, std::string source);
		void sub_from_equip_temporary(Attribute *attribute, uint32_t value, uint64_t duration, std::string source);
		void add_to_status_temporary(Attribute *attribute, uint32_t value, uint64_t duration, std::string source);
		void sub_from_status_temporary(Attribute *attribute, uint32_t value, uint64_t duration, std::string source);

		void add_to_base_interval(Attribute *attribute, uint32_t value, s_min_max minmax, uint64_t duration, uint64_t interval, std::string source);
		void sub_from_base_interval(Attribute *attribute, uint32_t value, s_min_max minmax, uint64_t duration, uint64_t interval, std::string source);
		void add_to_equip_interval(Attribute *attribute, uint32_t value, s_min_max minmax, uint64_t duration, uint64_t interval, std::string source);
		void sub_from_equip_interval(Attribute *attribute, uint32_t value, s_min_max minmax, uint64_t duration, uint64_t interval, std::string source);
		void add_to_status_interval(Attribute *attribute, uint32_t value, s_min_max minmax, uint64_t duration, uint64_t interval, std::string source);
		void sub_from_status_interval(Attribute *attribute, uint32_t value, s_min_max minmax, uint64_t duration, uint64_t interval, std::string source);

		bool has_next_operation() { return !_status_operation_queue.empty(); }
		StatusOperation *get_next_operation() { return _status_operation_queue.top(); }
		void process_queue();

	protected:
    	std::priority_queue<StatusOperation *, std::vector<StatusOperation *>, CompareStatusOperation> _status_operation_queue;
	};

	Status(std::weak_ptr<Unit> unit, unit_type type);
	~Status();

	bool initialize(std::shared_ptr<Horizon::Zone::Units::Mob> creature, std::shared_ptr<const monster_config_data> md);
	bool initialize(std::shared_ptr<Horizon::Zone::Units::Player> player);
	bool initialize(std::shared_ptr<Horizon::Zone::Units::NPC> npc);
	
	uint32_t get_required_statpoints(uint16_t from, uint16_t to);
	uint32_t get_status_base(status_point_type type);
	bool increase_status_point(status_point_type type, uint16_t amount);
	
	bool save(std::shared_ptr<Horizon::Zone::Units::Player> pl);
	bool load(std::shared_ptr<Horizon::Zone::Units::Player> pl);

	void on_equipment_changed(bool equipped, std::shared_ptr<const item_entry_data> item);
	void on_job_changed(uint32_t job_id);

	/**
	 * Attributes
	 */
	std::shared_ptr<Strength> strength() { return _str; }
	void set_strength(std::shared_ptr<Strength> str) {
		if (_str != nullptr)
			remove_attribute(_str);
		add_attribute(str);
		_str = str;
	}

	std::shared_ptr<Agility> agility() { return _agi; }
	void set_agility(std::shared_ptr<Agility> agi) {
		if (_agi != nullptr)
			remove_attribute(_agi);
		add_attribute(agi);
		_agi = agi;
	}

	std::shared_ptr<Vitality> vitality() { return _vit; }
	void set_vitality(std::shared_ptr<Vitality> vit) {
		if (_vit != nullptr)
			remove_attribute(_vit);
		add_attribute(vit);
		_vit = vit;
	}

	std::shared_ptr<Dexterity> dexterity() { return _dex; }
	void set_dexterity(std::shared_ptr<Dexterity> dex) {
		if (_dex != nullptr)
			remove_attribute(_dex);
		add_attribute(dex);
		_dex = dex;
	}

	std::shared_ptr<Intelligence> intelligence() { return _int; }
	void set_intelligence(std::shared_ptr<Intelligence> int_) {
		if (_int != nullptr)
			remove_attribute(_int);
		add_attribute(int_);
		_int = int_;
	}

	std::shared_ptr<Luck> luck() { return _luk; }
	void set_luck(std::shared_ptr<Luck> luck) {
		if (_luk != nullptr)
			remove_attribute(_luk);
		add_attribute(luck);
		_luk = luck;
	}

	std::shared_ptr<StrengthPointCost> strength_cost() { return _str_cost; }
	void set_strength_cost(std::shared_ptr<StrengthPointCost> str) {
		if (_str_cost != nullptr)
			remove_attribute(_str_cost);
		add_attribute(str);
		_str_cost = str;
	}

	std::shared_ptr<AgilityPointCost> agility_cost() { return _agi_cost; }
	void set_agility_cost(std::shared_ptr<AgilityPointCost> agi) {
		if (_agi_cost != nullptr)
			remove_attribute(_agi_cost);
		add_attribute(agi);
		_agi_cost = agi;
	}

	std::shared_ptr<VitalityPointCost> vitality_cost() { return _vit_cost; }
	void set_vitality_cost(std::shared_ptr<VitalityPointCost> vit) {
		if (_vit_cost != nullptr)
			remove_attribute(_vit_cost);
		add_attribute(vit);
		_vit_cost = vit;
	}

	std::shared_ptr<DexterityPointCost> dexterity_cost() { return _dex_cost; }
	void set_dexterity_cost(std::shared_ptr<DexterityPointCost> dex) {
		if (_dex_cost != nullptr)
			remove_attribute(_dex_cost);
		add_attribute(dex);
		_dex_cost = dex;
	}

	std::shared_ptr<IntelligencePointCost> intelligence_cost() { return _int_cost; }
	void set_intelligence_cost(std::shared_ptr<IntelligencePointCost> int_) {
		if (_int_cost != nullptr)
			remove_attribute(_int_cost);
		add_attribute(int_);
		_int_cost = int_;
	}

	std::shared_ptr<LuckPointCost> luck_cost() { return _luk_cost; }
	void set_luck_cost(std::shared_ptr<LuckPointCost> luck) {
		if (_luk_cost != nullptr)
			remove_attribute(_luk_cost);
		add_attribute(luck);
		_luk_cost = luck;
	}

	std::shared_ptr<StatusPoint> status_point() { return _status_point; }
	void set_status_point(std::shared_ptr<StatusPoint> st) {
		if (_status_point != nullptr)
			remove_attribute(_status_point);
		add_attribute(st);
		_status_point = st;
	}

	std::shared_ptr<SkillPoint> skill_point() { return _skill_point; }
	void set_skill_point(std::shared_ptr<SkillPoint> sk) {
		if (_skill_point != nullptr)
			remove_attribute(_skill_point);
		add_attribute(sk);
		_skill_point = sk;
	}

	std::shared_ptr<MaxHP> max_hp() { return _max_hp; }
	void set_max_hp(std::shared_ptr<MaxHP> max_hp) {
		if (_max_hp != nullptr)
			remove_attribute(_max_hp);
		add_attribute(max_hp);
		_max_hp = max_hp;
	}

	std::shared_ptr<MaxSP> max_sp() { return _max_sp; }
	void set_max_sp(std::shared_ptr<MaxSP> max_sp) {
		if (_max_sp != nullptr)
			remove_attribute(_max_sp);
		add_attribute(max_sp);
		_max_sp = max_sp;
	}

	std::shared_ptr<CurrentHP> current_hp() { return _current_hp; }
	void set_current_hp(std::shared_ptr<CurrentHP> hp) {
		if (_current_hp != nullptr)
			remove_attribute(_current_hp);
		add_attribute(hp);
		_current_hp = hp;
	}

	std::shared_ptr<CurrentSP> current_sp() { return _current_sp; }
	void set_current_sp(std::shared_ptr<CurrentSP> sp) {
		if (_current_sp != nullptr)
			remove_attribute(_current_sp);
		add_attribute(sp);
		_current_sp = sp;
	}

	std::shared_ptr<BaseLevel> base_level() { return _base_level; }
	void set_base_level(std::shared_ptr<BaseLevel> blvl) {
		if (_base_level != nullptr)
			remove_attribute(_base_level);
		add_attribute(blvl);
		_base_level = blvl;
	}

	std::shared_ptr<JobLevel> job_level() { return _job_level; }
	void set_job_level(std::shared_ptr<JobLevel> jlvl) {
		if (_job_level != nullptr)
			remove_attribute(_job_level);
		add_attribute(jlvl);
		_job_level = jlvl;
	}

	std::shared_ptr<BaseExperience> base_experience() { return _base_exp; }
	void set_base_experience(std::shared_ptr<BaseExperience> bexp) {
		if (_base_exp != nullptr)
			remove_attribute(_base_exp);
		add_attribute(bexp);
		_base_exp = bexp;
	}

	std::shared_ptr<JobExperience> job_experience() { return _job_exp; }
	void set_job_experience(std::shared_ptr<JobExperience> jexp) {
		if (_job_exp != nullptr)
			remove_attribute(_job_exp);
		add_attribute(jexp);
		_job_exp = jexp;
	}

	std::shared_ptr<NextBaseExperience> next_base_experience() { return _next_base_exp; }
	void set_next_base_experience(std::shared_ptr<NextBaseExperience> nbexp) {
		if (_next_base_exp != nullptr)
			remove_attribute(_next_base_exp);
		add_attribute(nbexp);
		_next_base_exp = nbexp;
	}

	std::shared_ptr<NextJobExperience> next_job_experience() { return _next_job_exp; }
	void set_next_job_experience(std::shared_ptr<NextJobExperience> njexp) {
		if (_next_job_exp != nullptr)
			remove_attribute(_next_job_exp);
		add_attribute(njexp);
		_next_job_exp = njexp;
	}

	std::shared_ptr<MovementSpeed> movement_speed() { return _movement_speed; }
	void set_movement_speed(std::shared_ptr<MovementSpeed> speed) {
		if (_movement_speed != nullptr)
			remove_attribute(_movement_speed);
		add_attribute(speed);
		_movement_speed = speed;
	}

	std::shared_ptr<MaxWeight> max_weight() { return _max_weight; }
	void set_max_weight(std::shared_ptr<MaxWeight> mw) {
		if (_max_weight != nullptr)
			remove_attribute(_max_weight);
		add_attribute(mw);
		_max_weight = mw;
	}

	std::shared_ptr<CurrentWeight> current_weight() { return _current_weight; }
	void set_current_weight(std::shared_ptr<CurrentWeight> cw) {
		if (_current_weight != nullptr)
			remove_attribute(_current_weight);
		add_attribute(cw);
		_current_weight = cw;
	}

	std::shared_ptr<AttackRange> attack_range() { return _attack_range; }
	void set_attack_range(std::shared_ptr<AttackRange> m) {
		if (_attack_range != nullptr)
			remove_attribute(_attack_range);
		add_attribute(m);
		_attack_range = m;
	}

	/**
	 * SubAttributes
	 */
	std::shared_ptr<StatusATK> status_atk() { return _status_atk; }
	void set_status_atk(std::shared_ptr<StatusATK> satk) {
		if (_status_atk != nullptr)
			remove_attribute(_status_atk);
		add_attribute(satk);
		_status_atk = satk;
	}

	std::shared_ptr<EquipATK> equip_atk() { return _equip_atk; }
	void set_equip_atk(std::shared_ptr<EquipATK> eatk) {
		if (_equip_atk != nullptr)
			remove_attribute(_equip_atk);
		add_attribute(eatk);
		_equip_atk = eatk;
	}

	std::shared_ptr<StatusMATK> status_matk() { return _status_matk; }
	void set_status_matk(std::shared_ptr<StatusMATK> smatk) {
		if (_status_matk != nullptr)
			remove_attribute(_status_matk);
		add_attribute(smatk);
		_status_matk = smatk;
	}
	
	std::shared_ptr<EquipMATK> equip_matk() { return _equip_matk; }
	void set_equip_matk(std::shared_ptr<EquipMATK> ematk) {
		if (_equip_matk != nullptr)
			remove_attribute(_equip_matk);
		add_attribute(ematk);
		_equip_matk = ematk;
	}

	std::shared_ptr<SoftDEF> soft_def() { return _soft_def; }
	void set_soft_def(std::shared_ptr<SoftDEF> sdef) {
		if (_soft_def != nullptr)
			remove_attribute(_soft_def);
		add_attribute(sdef);
		_soft_def = sdef;
	}

	std::shared_ptr<HardDEF> hard_def() { return _hard_def; }
	void set_hard_def(std::shared_ptr<HardDEF> hdef) {
		if (_hard_def != nullptr)
			remove_attribute(_hard_def);
		add_attribute(hdef);
		_hard_def = hdef;
	}

	std::shared_ptr<SoftMDEF> soft_mdef() { return _soft_mdef; }
	void set_soft_mdef(std::shared_ptr<SoftMDEF> smdef) {
		if (_soft_mdef != nullptr)
			remove_attribute(_soft_mdef);
		add_attribute(smdef);
		_soft_mdef = smdef;
	}
	
	std::shared_ptr<HardMDEF> hard_mdef() { return _hard_mdef; }
	void set_hard_mdef(std::shared_ptr<HardMDEF> hmdef) {
		if (_hard_mdef != nullptr)
			remove_attribute(_hard_mdef);
		add_attribute(hmdef);
		_hard_mdef = hmdef;
	}

	std::shared_ptr<HIT> hit() { return _hit; }
	void set_hit(std::shared_ptr<HIT> hit) {
		if (_hit != nullptr)
			remove_attribute(_hit);
		add_attribute(hit);
		_hit = hit;
	}

	std::shared_ptr<CRIT> crit() { return _crit; }
	void set_crit(std::shared_ptr<CRIT> crit) {
		if (_crit != nullptr)
			remove_attribute(_crit);
		add_attribute(crit);
		_crit = crit;
	}

	std::shared_ptr<FLEE> flee() { return _flee; }
	void set_flee(std::shared_ptr<FLEE> flee) {
		if (_flee != nullptr)
			remove_attribute(_flee);
		add_attribute(flee);
		_flee = flee;
	}

	std::shared_ptr<AttackSpeed> attack_speed() { return _aspd; }
	void set_attack_speed(std::shared_ptr<AttackSpeed> aspd) {
		if (_aspd != nullptr)
			remove_attribute(_aspd);
		add_attribute(aspd);
		_aspd = aspd;
	}

	std::shared_ptr<HPRegeneration> hp_regeneration() { return _hp_regeneration; }
	void set_hp_regeneration(std::shared_ptr<HPRegeneration> hpr) {
		if (_hp_regeneration != nullptr)
			remove_attribute(_hp_regeneration);
		add_attribute(hpr);
		_hp_regeneration = hpr;
	}

	std::shared_ptr<SPRegeneration> sp_regeneration() { return _sp_regeneration; }
	void set_sp_regeneration(std::shared_ptr<SPRegeneration> spr) {
		if (_sp_regeneration != nullptr)
			remove_attribute(_sp_regeneration);
		add_attribute(spr);
		_sp_regeneration = spr;
	}

	/**
	 * Appearance
	 */
	std::shared_ptr<BaseAppearance> base_appearance() { return _base_appearance; }
	void set_base_appearance(std::shared_ptr<BaseAppearance> ba) { add_appearance(ba); _base_appearance = ba; }

	std::shared_ptr<HairColor> hair_color() { return _hair_color; }
	void set_hair_color(std::shared_ptr<HairColor> hc) { add_appearance(hc); _hair_color = hc; }

	std::shared_ptr<ClothColor> cloth_color() { return _cloth_color; }
	void set_cloth_color(std::shared_ptr<ClothColor> cc) { add_appearance(cc); _cloth_color = cc; }

	std::shared_ptr<WeaponSprite> weapon_sprite() { return _weapon_sprite; }
	void set_weapon_sprite(std::shared_ptr<WeaponSprite> ws) { add_appearance(ws); _weapon_sprite = ws; }

	std::shared_ptr<ShieldSprite> shield_sprite() { return _shield_sprite; }
	void set_shield_sprite(std::shared_ptr<ShieldSprite> ss) { add_appearance(ss); _shield_sprite = ss; }

	std::shared_ptr<RobeSprite> robe_sprite() { return _robe_sprite; }
	void set_robe_sprite(std::shared_ptr<RobeSprite> rs) { add_appearance(rs); _robe_sprite = rs; }

	std::shared_ptr<HeadTopSprite> head_top_sprite() { return _head_top_sprite; }
	void set_head_top_sprite(std::shared_ptr<HeadTopSprite> hts) { add_appearance(hts); _head_top_sprite = hts; }

	std::shared_ptr<HeadMidSprite> head_mid_sprite() { return _head_mid_sprite; }
	void set_head_mid_sprite(std::shared_ptr<HeadMidSprite> hms) { add_appearance(hms); _head_mid_sprite = hms; }

	std::shared_ptr<HeadBottomSprite> head_bottom_sprite() { return _head_bottom_sprite; }
	void set_head_bottom_sprite(std::shared_ptr<HeadBottomSprite> hbs) { add_appearance(hbs); _head_bottom_sprite = hbs; }

	std::shared_ptr<HairStyle> hair_style() { return _hair_style; }
	void set_hair_style(std::shared_ptr<HairStyle> hs) { add_appearance(hs); _hair_style = hs; }

	std::shared_ptr<BodyStyle> body_style() { return _body_style; }
	void set_body_style(std::shared_ptr<BodyStyle> bs) { add_appearance(bs); _body_style = bs; }

	std::shared_ptr<Zeny> zeny() { return _zeny; }
	void set_zeny(std::shared_ptr<Zeny> z) {
		if (_zeny != nullptr)
			remove_attribute(_zeny);
		add_attribute(z);
		_zeny = z;
	}

	std::shared_ptr<Honor> honor() { return _honor; }
	void set_honor(std::shared_ptr<Honor> h) {
		if (_honor != nullptr)
			remove_attribute(_honor);
		add_attribute(h);
		_honor = h;
	}

	std::shared_ptr<Manner> manner() { return _manner; }
	void set_manner(std::shared_ptr<Manner> m) {
		if (_manner != nullptr)
			remove_attribute(_manner);
		add_attribute(m);
		_manner = m;
	}

	std::shared_ptr<Virtue> virtue() { return _virtue; }
	void set_virtue(std::shared_ptr<Virtue> v) {
		if (_virtue != nullptr)
			remove_attribute(_virtue);
		add_attribute(v);
		_virtue = v;
	}

	/**
	 * Combat Status
	 */
	std::shared_ptr<AttackDelay> attack_delay() { return _attack_delay; }
	void set_attack_delay(std::shared_ptr<AttackDelay> a) {
		if (_attack_delay != nullptr)
			remove_attribute(_attack_delay);
		add_attribute(a);
		_attack_delay = a;
	}

	std::shared_ptr<DamageWalkDelay> damage_walk_delay() { return _damage_walk_delay; }
	void set_damage_walk_delay(std::shared_ptr<DamageWalkDelay> m) {
		if (_damage_walk_delay != nullptr)
			remove_attribute(_damage_walk_delay);
		add_attribute(m);
		_damage_walk_delay = m;
	} 

	std::shared_ptr<BaseAttack> base_attack() { return _base_attack; }
	void set_base_attack(std::shared_ptr<BaseAttack> b) {
		if (_base_attack != nullptr)
			remove_attribute(_base_attack);
		add_attribute(b);
		_base_attack = b;
	}

	std::shared_ptr<WeaponAttackLeft> weapon_attack_left() { return _weapon_attack_left; }
	void set_weapon_attack_left(std::shared_ptr<WeaponAttackLeft> w) {
		if (_weapon_attack_left != nullptr)
			remove_attribute(_weapon_attack_left);
		add_attribute(w);
		_weapon_attack_left = w;
	}

	std::shared_ptr<WeaponAttackRight> weapon_attack_right() { return _weapon_attack_right; }
	void set_weapon_attack_right(std::shared_ptr<WeaponAttackRight> w) {
		if (_weapon_attack_right != nullptr)
			remove_attribute(_weapon_attack_right);
		add_attribute(w);
		_weapon_attack_right = w;
	}

	std::shared_ptr<WeaponAttackCombined> weapon_attack_combined() { return _weapon_attack_combined; }
	void set_weapon_attack_combined(std::shared_ptr<WeaponAttackCombined> w) {
		if (_weapon_attack_combined != nullptr)
			remove_attribute(_weapon_attack_combined);
		add_attribute(w);
		_weapon_attack_combined = w;
	}

	std::shared_ptr<UnitSize> size() { return _size; }
	void set_size(std::shared_ptr<UnitSize> s) {
		if (_size != nullptr)
			remove_attribute(_size);
		add_attribute(s);
		_size = s;
	}
	
	/* Mob Status */
	std::shared_ptr<MobWeaponAttack> creature_weapon_attack() { return _creature_weapon_attack; }
	void set_creature_weapon_attack(std::shared_ptr<MobWeaponAttack> m) {
		if (_creature_weapon_attack != nullptr)
			remove_attribute(_creature_weapon_attack);
		add_attribute(m);
		_creature_weapon_attack = m;
	}

	std::shared_ptr<MobWeaponAttack> creature_weapon_attack_magic() { return _creature_weapon_attack_magic; }
	void set_creature_weapon_attack_magic(std::shared_ptr<MobWeaponAttack> m) {
		if (_creature_weapon_attack_magic != nullptr)
			remove_attribute(_creature_weapon_attack_magic);
		add_attribute(m);
		_creature_weapon_attack_magic = m;
	}

	std::shared_ptr<MobAttackDamage> creature_attack_damage() { return _creature_attack_damage; }
	void set_creature_attack_damage(std::shared_ptr<MobAttackDamage> m) {
		if (_creature_attack_damage != nullptr)
			remove_attribute(_creature_attack_damage);
		add_attribute(m);
		_creature_attack_damage = m;
	}

	std::shared_ptr<MobMagicAttackDamage> creature_magic_attack_damage() { return _creature_magic_attack_damage; }
	void set_creature_magic_attack_damage(std::shared_ptr<MobMagicAttackDamage> m) {
		if (_creature_magic_attack_damage != nullptr)
			remove_attribute(_creature_magic_attack_damage);
		add_attribute(m);
		_creature_magic_attack_damage = m;
	}

	std::shared_ptr<MobViewRange> creature_view_range() { return _creature_view_range; }
	void set_creature_view_range(std::shared_ptr<MobViewRange> m) {
		if (_creature_view_range != nullptr)
			remove_attribute(_creature_view_range);
		add_attribute(m);
		_creature_view_range = m;
	}

	std::shared_ptr<MobChaseRange> creature_chase_range() { return _creature_chase_range; }
	void set_creature_chase_range(std::shared_ptr<MobChaseRange> m) {
		if (_creature_chase_range != nullptr)
			remove_attribute(_creature_chase_range);
		add_attribute(m);
		_creature_chase_range = m;
	}
	
	std::shared_ptr<MobPrimaryRace> creature_primary_race() { return _creature_primary_race; }
	void set_creature_primary_race(std::shared_ptr<MobPrimaryRace> m) {
		if (_creature_primary_race != nullptr)
			remove_attribute(_creature_primary_race);
		add_attribute(m);
		_creature_primary_race = m;
	}
	
	std::shared_ptr<MobSecondaryRace> creature_secondary_race() { return _creature_secondary_race; }
	void set_creature_secondary_race(std::shared_ptr<MobSecondaryRace> m) {
		if (_creature_secondary_race != nullptr)
			remove_attribute(_creature_secondary_race);
		add_attribute(m);
		_creature_secondary_race = m;
	}
	
	std::shared_ptr<MobElement> creature_element() { return _creature_element; }
	void set_creature_element(std::shared_ptr<MobElement> m) {
		if (_creature_element != nullptr)
			remove_attribute(_creature_element);
		add_attribute(m);
		_creature_element = m;
	}
	
	std::shared_ptr<MobElementLevel> creature_element_level() { return _creature_element_level; }
	void set_creature_element_level(std::shared_ptr<MobElementLevel> m) {
		if (_creature_element_level != nullptr)
			remove_attribute(_creature_element_level);
		add_attribute(m);
		_creature_element_level = m;
	}
	
	std::shared_ptr<MobMode> creature_mode() { return _creature_mode; }
	void set_creature_mode(std::shared_ptr<MobMode> m) {
		if (_creature_mode != nullptr)
			remove_attribute(_creature_mode);
		add_attribute(m);
		_creature_mode = m;
	}

	std::shared_ptr<StatusRegistry> status_registry() { return _status_registry; }

	bool is_initialized() { return _is_initialized; }
	void set_initialized(bool b) { _is_initialized = b; }

	void add_attribute(std::shared_ptr<Attribute> attribute) { _attributes.push_back(attribute); }
	void remove_attribute(std::shared_ptr<Attribute> attribute)
	{
		_attributes.erase(std::remove(_attributes.begin(), _attributes.end(), attribute), _attributes.end());
	}
	std::shared_ptr<Attribute> get_attribute(status_point_type type)
	{
		for (auto &attribute : _attributes)
		{
			if (attribute->get_type() == type)
				return attribute;
		}

		return nullptr;
	}

	void add_appearance(std::shared_ptr<Appearance> appearance) { _appearances.push_back(appearance); }
	void remove_appearance(std::shared_ptr<Appearance> appearance)
	{
		_appearances.erase(std::remove(_appearances.begin(), _appearances.end(), appearance), _appearances.end());
	}
	std::shared_ptr<Appearance> get_appearance(unit_appearance_type type)
	{
		for (auto &appearance : _appearances)
		{
			if (appearance->get_type() == type)
				return appearance;
		}

		return nullptr;
	}

	void calculate(bool notify = true);
	bool recalculate(bool notify = true);
	bool update(uint64_t delta);
	
	void add_bonus(std::shared_ptr<Bonuses::Bonus> bonus) { _bonuses.push_back(bonus); }
	void remove_bonus(std::shared_ptr<Bonuses::Bonus> bonus)
	{
		_bonuses.erase(std::remove(_bonuses.begin(), _bonuses.end(), bonus), _bonuses.end());
	}
	std::shared_ptr<Bonuses::Bonus> get_bonus(status_point_type type)
	{
		for (auto &bonus : _bonuses)
		{
			if (bonus->get_type() == type)
				return bonus;
		}

		return nullptr;
	}

	std::shared_ptr<Bonuses::BonusAllStatus> bonus_all_status() { return _bonus->_all_status; }
	void set_bonus_all_status(std::shared_ptr<Bonuses::BonusAllStatus> b) {
		if (_bonus->_all_status != nullptr)
			remove_bonus(_bonus->_all_status);
		add_bonus(b);
		_bonus->_all_status = b;
	}

	std::shared_ptr<Bonuses::BonusAttackElement> bonus_attack_element() { return _bonus->_attack_element; }
	void set_bonus_attack_element(std::shared_ptr<Bonuses::BonusAttackElement> b) {
		if (_bonus->_attack_element != nullptr)
			remove_bonus(_bonus->_attack_element);
		add_bonus(b);
		_bonus->_attack_element = b;
	}

	std::shared_ptr<Bonuses::BonusDefenseElement> bonus_defense_element() { return _bonus->_defense_element; }
	void set_bonus_defense_element(std::shared_ptr<Bonuses::BonusDefenseElement> b) {
		if (_bonus->_defense_element != nullptr)
			remove_bonus(_bonus->_defense_element);
		add_bonus(b);
		_bonus->_defense_element = b;
	}

	std::shared_ptr<Bonuses::BonusCastPercent> bonus_cast_percent() { return _bonus->_cast_percent; }
	void set_bonus_cast_percent(std::shared_ptr<Bonuses::BonusCastPercent> b) {
		if (_bonus->_cast_percent != nullptr)
			remove_bonus(_bonus->_cast_percent);
		add_bonus(b);
		_bonus->_cast_percent = b;
	}

	std::shared_ptr<Bonuses::BonusMaxHPPercent> bonus_max_hp_percent() { return _bonus->_max_hp_percent; }
	void set_bonus_max_hp_percent(std::shared_ptr<Bonuses::BonusMaxHPPercent> b) {
		if (_bonus->_max_hp_percent != nullptr)
			remove_bonus(_bonus->_max_hp_percent);
		add_bonus(b);
		_bonus->_max_hp_percent = b;
	}

	std::shared_ptr<Bonuses::BonusMaxSPPercent> bonus_max_sp_percent() { return _bonus->_max_sp_percent; }
	void set_bonus_max_sp_percent(std::shared_ptr<Bonuses::BonusMaxSPPercent> b) {
		if (_bonus->_max_sp_percent != nullptr)
			remove_bonus(_bonus->_max_sp_percent);
		add_bonus(b);
		_bonus->_max_sp_percent = b;
	}

	std::shared_ptr<Bonuses::BonusSPPercent> bonus_sp_percent() { return _bonus->_sp_percent; }
	void set_bonus_sp_percent(std::shared_ptr<Bonuses::BonusSPPercent> b) {
		if (_bonus->_sp_percent != nullptr)
			remove_bonus(_bonus->_sp_percent);
		add_bonus(b);
		_bonus->_sp_percent = b;
	}

	std::shared_ptr<Bonuses::BonusAttackRange> bonus_attack_range() { return _bonus->_attack_range; }
	void set_bonus_attack_range(std::shared_ptr<Bonuses::BonusAttackRange> b) {
		if (_bonus->_attack_range != nullptr)
			remove_bonus(_bonus->_attack_range);
		add_bonus(b);
		_bonus->_attack_range = b;
	}

	std::shared_ptr<Bonuses::BonusAttackRangePercent> bonus_attack_range_percent() { return _bonus->_attack_range_percent; }
	void set_bonus_attack_range_percent(std::shared_ptr<Bonuses::BonusAttackRangePercent> b) {
		if (_bonus->_attack_range_percent != nullptr)
			remove_bonus(_bonus->_attack_range_percent);
		add_bonus(b);
		_bonus->_attack_range_percent = b;
	}

	std::shared_ptr<Bonuses::BonusAddMovementSpeedPercent> bonus_add_movement_speed_percent() { return _bonus->_bonus_add_movement_speed_percent; }
	void set_bonus_add_movement_speed_percent(std::shared_ptr<Bonuses::BonusAddMovementSpeedPercent> b) {
		if (_bonus->_bonus_add_movement_speed_percent != nullptr)
			remove_bonus(_bonus->_bonus_add_movement_speed_percent);
		add_bonus(b);
		_bonus->_bonus_add_movement_speed_percent = b;
	}

	std::shared_ptr<Bonuses::BonusAttackSpeedPercent> bonus_attack_speed_percent() { return _bonus->_attack_speed_percent; }
	void set_bonus_attack_speed_percent(std::shared_ptr<Bonuses::BonusAttackSpeedPercent> b) {
		if (_bonus->_attack_speed_percent != nullptr)
			remove_bonus(_bonus->_attack_speed_percent);
		add_bonus(b);
		_bonus->_attack_speed_percent = b;
	}
	
	std::shared_ptr<Bonuses::BonusHPRecoveryPercent> bonus_hp_recovery_percent() { return _bonus->_hp_recovery_percent; }
	void set_bonus_hp_recovery_percent(std::shared_ptr<Bonuses::BonusHPRecoveryPercent> b) {
		if (_bonus->_hp_recovery_percent != nullptr)
			remove_bonus(_bonus->_hp_recovery_percent);
		add_bonus(b);
		_bonus->_hp_recovery_percent = b;
	}

	std::shared_ptr<Bonuses::BonusSPRecoveryPercent> bonus_sp_recovery_percent() { return _bonus->_sp_recovery_percent; }
	void set_bonus_sp_recovery_percent(std::shared_ptr<Bonuses::BonusSPRecoveryPercent> b) {
		if (_bonus->_sp_recovery_percent != nullptr)
			remove_bonus(_bonus->_sp_recovery_percent);
		add_bonus(b);
		_bonus->_sp_recovery_percent = b;
	}

	std::shared_ptr<Bonuses::BonusCriticalDefense> bonus_critical_defense() { return _bonus->_critical_defense; }
	void set_bonus_critical_defense(std::shared_ptr<Bonuses::BonusCriticalDefense> b) {
		if (_bonus->_critical_defense != nullptr)
			remove_bonus(_bonus->_critical_defense);
		add_bonus(b);
		_bonus->_critical_defense = b;
	}

	std::shared_ptr<Bonuses::BonusMeleeDefense> bonus_melee_defense() { return _bonus->_melee_defense; }
	void set_bonus_melee_defense(std::shared_ptr<Bonuses::BonusMeleeDefense> b) {
		if (_bonus->_melee_defense != nullptr)
			remove_bonus(_bonus->_melee_defense);
		add_bonus(b);
		_bonus->_melee_defense = b;
	}

	std::shared_ptr<Bonuses::BonusRangedDefense> bonus_ranged_defense() { return _bonus->_ranged_defense; }
	void set_bonus_ranged_defense(std::shared_ptr<Bonuses::BonusRangedDefense> b) {
		if (_bonus->_ranged_defense != nullptr)
			remove_bonus(_bonus->_ranged_defense);
		add_bonus(b);
		_bonus->_ranged_defense = b;
	}

	std::shared_ptr<Bonuses::BonusDoubleAttackPercent> bonus_double_attack_percent() { return _bonus->_double_attack_percent; }
	void set_bonus_double_attack_percent(std::shared_ptr<Bonuses::BonusDoubleAttackPercent> b) {
		if (_bonus->_double_attack_percent != nullptr)
			remove_bonus(_bonus->_double_attack_percent);
		add_bonus(b);
		_bonus->_double_attack_percent = b;
	}

	std::shared_ptr<Bonuses::BonusMagicAttackPercent> bonus_magic_attack_percent() { return _bonus->_magic_attack_percent; }
	void set_bonus_magic_attack_percent(std::shared_ptr<Bonuses::BonusMagicAttackPercent> b) {
		if (_bonus->_magic_attack_percent != nullptr)
			remove_bonus(_bonus->_magic_attack_percent);
		add_bonus(b);
		_bonus->_magic_attack_percent = b;
	}

	std::shared_ptr<Bonuses::BonusAttackPercent> bonus_attack_percent() { return _bonus->_attack_percent; }
	void set_bonus_attack_percent(std::shared_ptr<Bonuses::BonusAttackPercent> b) {
		if (_bonus->_attack_percent != nullptr)
			remove_bonus(_bonus->_attack_percent);
		add_bonus(b);
		_bonus->_attack_percent = b;
	}

	std::shared_ptr<Bonuses::BonusMagicDefensePercent> bonus_magic_defense_percent() { return _bonus->_magic_defense_percent; }
	void set_bonus_magic_defense_percent(std::shared_ptr<Bonuses::BonusMagicDefensePercent> b) {
		if (_bonus->_magic_defense_percent != nullptr)
			remove_bonus(_bonus->_magic_defense_percent);
		add_bonus(b);
		_bonus->_magic_defense_percent = b;
	}

	std::shared_ptr<Bonuses::BonusMiscDefensePercent> bonus_misc_defense_percent() { return _bonus->_misc_defense_percent; }
	void set_bonus_misc_defense_percent(std::shared_ptr<Bonuses::BonusMiscDefensePercent> b) {
		if (_bonus->_misc_defense_percent != nullptr)
			remove_bonus(_bonus->_misc_defense_percent);
		add_bonus(b);
		_bonus->_misc_defense_percent = b;
	}

	std::shared_ptr<Bonuses::BonusPerfectHitPercent> bonus_perfect_hit_percent() { return _bonus->_perfect_hit_percent; }
	void set_bonus_perfect_hit_percent(std::shared_ptr<Bonuses::BonusPerfectHitPercent> b) {
		if (_bonus->_perfect_hit_percent != nullptr)
			remove_bonus(_bonus->_perfect_hit_percent);
		add_bonus(b);
		_bonus->_perfect_hit_percent = b;
	}

	std::shared_ptr<Bonuses::BonusCriticalPercent> bonus_critical_percent() { return _bonus->_critical_percent; }
	void set_bonus_critical_percent(std::shared_ptr<Bonuses::BonusCriticalPercent> b) {
		if (_bonus->_critical_percent != nullptr)
			remove_bonus(_bonus->_critical_percent);
		add_bonus(b);
		_bonus->_critical_percent = b;
	}

	std::shared_ptr<Bonuses::BonusGetZenyNum> bonus_get_zeny_num() { return _bonus->_get_zeny_num; }
	void set_bonus_get_zeny_num(std::shared_ptr<Bonuses::BonusGetZenyNum> b) {
		if (_bonus->_get_zeny_num != nullptr)
			remove_bonus(_bonus->_get_zeny_num);
		add_bonus(b);
		_bonus->_get_zeny_num = b;
	}

	std::shared_ptr<Bonuses::BonusAttackOnDefenseRatioForElement> bonus_attack_on_defense_ratio_for_element() { return _bonus->_attack_on_defense_ratio_for_element; }
	void set_bonus_attack_on_defense_ratio_for_element(std::shared_ptr<Bonuses::BonusAttackOnDefenseRatioForElement> b) {
		if (_bonus->_attack_on_defense_ratio_for_element != nullptr)
			remove_bonus(_bonus->_attack_on_defense_ratio_for_element);
		add_bonus(b);
		_bonus->_attack_on_defense_ratio_for_element = b;
	}

	std::shared_ptr<Bonuses::BonusAttackOnDefenseRatioForRace> bonus_attack_on_defense_ratio_for_race() { return _bonus->_attack_on_defense_ratio_for_race; }
	void set_bonus_attack_on_defense_ratio_for_race(std::shared_ptr<Bonuses::BonusAttackOnDefenseRatioForRace> b) {
		if (_bonus->_attack_on_defense_ratio_for_race != nullptr)
			remove_bonus(_bonus->_attack_on_defense_ratio_for_race);
		add_bonus(b);
		_bonus->_attack_on_defense_ratio_for_race = b;
	};

	std::shared_ptr<Bonuses::BonusHitPercent> bonus_hit_percent() { return _bonus->_hit_percent; }
	void set_bonus_hit_percent(std::shared_ptr<Bonuses::BonusHitPercent> b) {
		if (_bonus->_hit_percent != nullptr)
			remove_bonus(_bonus->_hit_percent);
		add_bonus(b);
		_bonus->_hit_percent = b;
	}

	std::shared_ptr<Bonuses::BonusFleePercent> bonus_flee_percent() { return _bonus->_flee_percent; }
	void set_bonus_flee_percent(std::shared_ptr<Bonuses::BonusFleePercent> b) {
		if (_bonus->_flee_percent != nullptr)
			remove_bonus(_bonus->_flee_percent);
		add_bonus(b);
		_bonus->_flee_percent = b;
	}

	std::shared_ptr<Bonuses::BonusPerfectDodgePercent> bonus_perfect_dodge_percent() { return _bonus->_perfect_dodge_percent; }
	void set_bonus_perfect_dodge_percent(std::shared_ptr<Bonuses::BonusPerfectDodgePercent> b) {
		if (_bonus->_perfect_dodge_percent != nullptr)
			remove_bonus(_bonus->_perfect_dodge_percent);
		add_bonus(b);
		_bonus->_perfect_dodge_percent = b;
	}

	std::shared_ptr<Bonuses::BonusSoftDefensePercent> bonus_soft_defense_percent() { return _bonus->_soft_defense_percent; }
	void set_bonus_soft_defense_percent(std::shared_ptr<Bonuses::BonusSoftDefensePercent> b) {
		if (_bonus->_soft_defense_percent != nullptr)
			remove_bonus(_bonus->_soft_defense_percent);
		add_bonus(b);
		_bonus->_soft_defense_percent = b;
	}

	std::shared_ptr<Bonuses::BonusHardDefensePercent> bonus_hard_defense_percent() { return _bonus->_hard_defense_percent; }
	void set_bonus_hard_defense_percent(std::shared_ptr<Bonuses::BonusHardDefensePercent> b) {
		if (_bonus->_hard_defense_percent != nullptr)
			remove_bonus(_bonus->_hard_defense_percent);
		add_bonus(b);
		_bonus->_hard_defense_percent = b;
	}

	std::shared_ptr<Bonuses::BonusSoftMagicalDefensePercent> bonus_soft_magical_defense_percent() { return _bonus->_soft_magical_defense_percent; }
	void set_bonus_soft_magical_defense_percent(std::shared_ptr<Bonuses::BonusSoftMagicalDefensePercent> b) {
		if (_bonus->_soft_magical_defense_percent != nullptr)
			remove_bonus(_bonus->_soft_magical_defense_percent);
		add_bonus(b);
		_bonus->_soft_magical_defense_percent = b;
	}

	std::shared_ptr<Bonuses::BonusHardMagicalDefensePercent> bonus_hard_magical_defense_percent() { return _bonus->_hard_magical_defense_percent; }
	void set_bonus_hard_magical_defense_percent(std::shared_ptr<Bonuses::BonusHardMagicalDefensePercent> b) {
		if (_bonus->_hard_magical_defense_percent != nullptr)
			remove_bonus(_bonus->_hard_magical_defense_percent);
		add_bonus(b);
		_bonus->_hard_magical_defense_percent = b;
	}

	std::shared_ptr<Bonuses::BonusRestartWithFullRecovery> bonus_restart_with_full_recovery() { return _bonus->_restart_with_full_recovery; }
	void set_bonus_restart_with_full_recovery(std::shared_ptr<Bonuses::BonusRestartWithFullRecovery> b) {
		if (_bonus->_restart_with_full_recovery != nullptr)
			remove_bonus(_bonus->_restart_with_full_recovery);
		add_bonus(b);
		_bonus->_restart_with_full_recovery = b;
	}

	std::shared_ptr<Bonuses::BonusCastCancelImmunity> bonus_cast_cancel_immunity() { return _bonus->_cast_cancel_immunity; }
	void set_bonus_cast_cancel_immunity(std::shared_ptr<Bonuses::BonusCastCancelImmunity> b) {
		if (_bonus->_cast_cancel_immunity != nullptr)
			remove_bonus(_bonus->_cast_cancel_immunity);
		add_bonus(b);
		_bonus->_cast_cancel_immunity = b;
	}

	std::shared_ptr<Bonuses::BonusSizeModifierImmunity> bonus_size_modifier_immunity() { return _bonus->_size_modifier_immunity; }
	void set_bonus_size_modifier_immunity(std::shared_ptr<Bonuses::BonusSizeModifierImmunity> b) {
		if (_bonus->_size_modifier_immunity != nullptr)
			remove_bonus(_bonus->_size_modifier_immunity);
		add_bonus(b);
		_bonus->_size_modifier_immunity = b;
	}

	std::shared_ptr<Bonuses::BonusMagicDamageImmunity> bonus_magic_damage_immunity() { return _bonus->_magic_damage_immunity; }
	void set_bonus_magic_damage_immunity(std::shared_ptr<Bonuses::BonusMagicDamageImmunity> b) {
		if (_bonus->_magic_damage_immunity != nullptr)
			remove_bonus(_bonus->_magic_damage_immunity);
		add_bonus(b);
		_bonus->_magic_damage_immunity = b;
	}

	std::shared_ptr<Bonuses::BonusWeaponDamageImmunity> bonus_weapon_damage_immunity() { return _bonus->_weapon_damage_immunity; }
	void set_bonus_weapon_damage_immunity(std::shared_ptr<Bonuses::BonusWeaponDamageImmunity> b) {
		if (_bonus->_weapon_damage_immunity != nullptr)
			remove_bonus(_bonus->_weapon_damage_immunity);
		add_bonus(b);
		_bonus->_weapon_damage_immunity = b;
	}

	std::shared_ptr<Bonuses::BonusGemstoneImmunity> bonus_gemstone_immunity() { return _bonus->_gemstone_immunity; }
	void set_bonus_gemstone_immunity(std::shared_ptr<Bonuses::BonusGemstoneImmunity> b) {
		if (_bonus->_gemstone_immunity != nullptr)
			remove_bonus(_bonus->_gemstone_immunity);
		add_bonus(b);
		_bonus->_gemstone_immunity = b;
	}

	std::shared_ptr<Bonuses::BonusGearFuelImmunity> bonus_gear_fuel_immunity() { return _bonus->_gear_fuel_immunity; }
	void set_bonus_gear_fuel_immunity(std::shared_ptr<Bonuses::BonusGearFuelImmunity> b) {
		if (_bonus->_gear_fuel_immunity != nullptr)
			remove_bonus(_bonus->_gear_fuel_immunity);
		add_bonus(b);
		_bonus->_gear_fuel_immunity = b;
	}

	std::shared_ptr<Bonuses::BonusInfiniteEndure> bonus_infinite_endure() { return _bonus->_infinite_endure; }
	void set_bonus_infinite_endure(std::shared_ptr<Bonuses::BonusInfiniteEndure> b) {
		if (_bonus->_infinite_endure != nullptr)
			remove_bonus(_bonus->_infinite_endure);
		add_bonus(b);
		_bonus->_infinite_endure = b;
	}

	std::shared_ptr<Bonuses::BonusUnbreakableWeapon> bonus_unbreakable_weapon() { return _bonus->_unbreakable_weapon; }
	void set_bonus_unbreakable_weapon(std::shared_ptr<Bonuses::BonusUnbreakableWeapon> b) {
		if (_bonus->_unbreakable_weapon != nullptr)
			remove_bonus(_bonus->_unbreakable_weapon);
		add_bonus(b);
		_bonus->_unbreakable_weapon = b;
	}

	std::shared_ptr<Bonuses::BonusUnbreakableArmor> bonus_unbreakable_armor() { return _bonus->_unbreakable_armor; }
	void set_bonus_unbreakable_armor(std::shared_ptr<Bonuses::BonusUnbreakableArmor> b) {
		if (_bonus->_unbreakable_armor != nullptr)
			remove_bonus(_bonus->_unbreakable_armor);
		add_bonus(b);
		_bonus->_unbreakable_armor = b;
	}

	std::shared_ptr<Bonuses::BonusUnbreakableHelm> bonus_unbreakable_helm() { return _bonus->_unbreakable_helm; }
	void set_bonus_unbreakable_helm(std::shared_ptr<Bonuses::BonusUnbreakableHelm> b) {
		if (_bonus->_unbreakable_helm != nullptr)
			remove_bonus(_bonus->_unbreakable_helm);
		add_bonus(b);
		_bonus->_unbreakable_helm = b;
	}

	std::shared_ptr<Bonuses::BonusUnbreakableShield> bonus_unbreakable_shield() { return _bonus->_unbreakable_shield; }
	void set_bonus_unbreakable_shield(std::shared_ptr<Bonuses::BonusUnbreakableShield> b) {
		if (_bonus->_unbreakable_shield != nullptr)
			remove_bonus(_bonus->_unbreakable_shield);
		add_bonus(b);
		_bonus->_unbreakable_shield = b;
	}

	std::shared_ptr<Bonuses::BonusSPGainOnMobKill> bonus_sp_gain_on_mob_kill() { return _bonus->_sp_gain_on_mob_kill; }
	void set_bonus_sp_gain_on_mob_kill(std::shared_ptr<Bonuses::BonusSPGainOnMobKill> b) {
		if (_bonus->_sp_gain_on_mob_kill != nullptr)
			remove_bonus(_bonus->_sp_gain_on_mob_kill);
		add_bonus(b);
		_bonus->_sp_gain_on_mob_kill = b;
	}

	std::shared_ptr<Bonuses::BonusHPGainOnMobKill> bonus_hp_gain_on_mob_kill() { return _bonus->_hp_gain_on_mob_kill; }
	void set_bonus_hp_gain_on_mob_kill(std::shared_ptr<Bonuses::BonusHPGainOnMobKill> b) {
		if (_bonus->_hp_gain_on_mob_kill != nullptr)
			remove_bonus(_bonus->_hp_gain_on_mob_kill);
		add_bonus(b);
		_bonus->_hp_gain_on_mob_kill = b;
	}

	std::shared_ptr<Bonuses::BonusDamageSplashRange> bonus_damage_splash_range() { return _bonus->_damage_splash_range; }
	void set_bonus_damage_splash_range(std::shared_ptr<Bonuses::BonusDamageSplashRange> b) {
		if (_bonus->_damage_splash_range != nullptr)
			remove_bonus(_bonus->_damage_splash_range);
		add_bonus(b);
		_bonus->_damage_splash_range = b;
	}

	std::shared_ptr<Bonuses::BonusMeleeWeaponDamageReflectPercentOnSelf> bonus_melee_weapon_damage_reflect_percent_on_self() { return _bonus->_melee_weapon_damage_reflect_percent_on_self; }
	void set_bonus_melee_weapon_damage_reflect_percent_on_self(std::shared_ptr<Bonuses::BonusMeleeWeaponDamageReflectPercentOnSelf> b) {
		if (_bonus->_melee_weapon_damage_reflect_percent_on_self != nullptr)
			remove_bonus(_bonus->_melee_weapon_damage_reflect_percent_on_self);
		add_bonus(b);
		_bonus->_melee_weapon_damage_reflect_percent_on_self = b;
	}

	std::shared_ptr<Bonuses::BonusRangedWeaponDamageReflectPercentOnSelf> bonus_ranged_weapon_damage_reflect_percent_on_self() { return _bonus->_ranged_weapon_damage_reflect_percent_on_self; }
	void set_bonus_ranged_weapon_damage_reflect_percent_on_self(std::shared_ptr<Bonuses::BonusRangedWeaponDamageReflectPercentOnSelf> b) {
		if (_bonus->_ranged_weapon_damage_reflect_percent_on_self != nullptr)
			remove_bonus(_bonus->_ranged_weapon_damage_reflect_percent_on_self);
		add_bonus(b);
		_bonus->_ranged_weapon_damage_reflect_percent_on_self = b;
	}

	std::shared_ptr<Bonuses::BonusWeaponBreakPercent> bonus_weapon_break_percent() { return _bonus->_weapon_break_percent; }
	void set_bonus_weapon_break_percent(std::shared_ptr<Bonuses::BonusWeaponBreakPercent> b) {
		if (_bonus->_weapon_break_percent != nullptr)
			remove_bonus(_bonus->_weapon_break_percent);
		add_bonus(b);
		_bonus->_weapon_break_percent = b;
	}

	std::shared_ptr<Bonuses::BonusArmorBreakPercent> bonus_armor_break_percent() { return _bonus->_armor_break_percent; }
	void set_bonus_armor_break_percent(std::shared_ptr<Bonuses::BonusArmorBreakPercent> b) {
		if (_bonus->_armor_break_percent != nullptr)
			remove_bonus(_bonus->_armor_break_percent);
		add_bonus(b);
		_bonus->_armor_break_percent = b;
	}

	std::shared_ptr<Bonuses::BonusAddStealPercent> bonus_add_steal_percent() { return _bonus->_add_steal_percent; }
	void set_bonus_add_steal_percent(std::shared_ptr<Bonuses::BonusAddStealPercent> b) {
		if (_bonus->_add_steal_percent != nullptr)
			remove_bonus(_bonus->_add_steal_percent);
		add_bonus(b);
		_bonus->_add_steal_percent = b;
	}

	std::shared_ptr<Bonuses::BonusCriticalDamagePercent> bonus_critical_damage_percent() { return _bonus->_critical_damage_percent; }
	void set_bonus_critical_damage_percent(std::shared_ptr<Bonuses::BonusCriticalDamagePercent> b) {
		if (_bonus->_critical_damage_percent != nullptr)
			remove_bonus(_bonus->_critical_damage_percent);
		add_bonus(b);
		_bonus->_critical_damage_percent = b;
	}

	std::shared_ptr<Bonuses::BonusDisableHPRecovery> bonus_disable_hp_recovery() { return _bonus->_disable_hp_recovery; }
	void set_bonus_disable_hp_recovery(std::shared_ptr<Bonuses::BonusDisableHPRecovery> b) {
		if (_bonus->_disable_hp_recovery != nullptr)
			remove_bonus(_bonus->_disable_hp_recovery);
		add_bonus(b);
		_bonus->_disable_hp_recovery = b;
	}

	std::shared_ptr<Bonuses::BonusDisableSPRecovery> bonus_disable_sp_recovery() { return _bonus->_disable_sp_recovery; }
	void set_bonus_disable_sp_recovery(std::shared_ptr<Bonuses::BonusDisableSPRecovery> b) {
		if (_bonus->_disable_sp_recovery != nullptr)
			remove_bonus(_bonus->_disable_sp_recovery);
		add_bonus(b);
		_bonus->_disable_sp_recovery = b;
	}

	std::shared_ptr<Bonuses::BonusMagicDamageReflectPercentOnSelf> bonus_magic_damage_reflect_percent_on_self() { return _bonus->_magic_damage_reflect_percent_on_self; }
	void set_bonus_magic_damage_reflect_percent_on_self(std::shared_ptr<Bonuses::BonusMagicDamageReflectPercentOnSelf> b) {
		if (_bonus->_magic_damage_reflect_percent_on_self != nullptr)
			remove_bonus(_bonus->_magic_damage_reflect_percent_on_self);
		add_bonus(b);
		_bonus->_magic_damage_reflect_percent_on_self = b;
	}

	std::shared_ptr<Bonuses::BonusShortWeaponDamagePercent> bonus_short_weapon_damage_percent() { return _bonus->_short_weapon_damage_percent; }
	void set_bonus_short_weapon_damage_percent(std::shared_ptr<Bonuses::BonusShortWeaponDamagePercent> b) {
		if (_bonus->_short_weapon_damage_percent != nullptr)
			remove_bonus(_bonus->_short_weapon_damage_percent);
		add_bonus(b);
		_bonus->_short_weapon_damage_percent = b;
	}

	std::shared_ptr<Bonuses::BonusLongWeaponDamagePercent> bonus_long_weapon_damage_percent() { return _bonus->_long_weapon_damage_percent; }
	void set_bonus_long_weapon_damage_percent(std::shared_ptr<Bonuses::BonusLongWeaponDamagePercent> b) {
		if (_bonus->_long_weapon_damage_percent != nullptr)
			remove_bonus(_bonus->_long_weapon_damage_percent);
		add_bonus(b);
		_bonus->_long_weapon_damage_percent = b;
	}

	std::shared_ptr<Bonuses::BonusItemUsageImmunity> bonus_item_usage_immunity() { return _bonus->_item_usage_immunity; }
	void set_bonus_item_usage_immunity(std::shared_ptr<Bonuses::BonusItemUsageImmunity> b) {
		if (_bonus->_item_usage_immunity != nullptr)
			remove_bonus(_bonus->_item_usage_immunity);
		add_bonus(b);
		_bonus->_item_usage_immunity = b;
	}

	std::shared_ptr<Bonuses::BonusKnockBackImmunity> bonus_knock_back_immunity() { return _bonus->_knockback_immunity; }
	void set_bonus_knock_back_immunity(std::shared_ptr<Bonuses::BonusKnockBackImmunity> b) {
		if (_bonus->_knockback_immunity != nullptr)
			remove_bonus(_bonus->_knockback_immunity);
		add_bonus(b);
		_bonus->_knockback_immunity = b;
	}

	std::shared_ptr<Bonuses::BonusHPVanishPercent> bonus_hp_vanish_percent() { return _bonus->_hp_vanish_percent; }
	void set_bonus_hp_vanish_percent(std::shared_ptr<Bonuses::BonusHPVanishPercent> b) {
		if (_bonus->_hp_vanish_percent != nullptr)
			remove_bonus(_bonus->_hp_vanish_percent);
		add_bonus(b);
		_bonus->_hp_vanish_percent = b;
	}

	std::shared_ptr<Bonuses::BonusSPVanishPercent> bonus_sp_vanish_percent() { return _bonus->_sp_vanish_percent; }
	void set_bonus_sp_vanish_percent(std::shared_ptr<Bonuses::BonusSPVanishPercent> b) {
		if (_bonus->_sp_vanish_percent != nullptr)
			remove_bonus(_bonus->_sp_vanish_percent);
		add_bonus(b);
		_bonus->_sp_vanish_percent = b;
	}

	std::shared_ptr<Bonuses::BonusRaise> bonus_raise() { return _bonus->_raise; }
	void set_bonus_raise(std::shared_ptr<Bonuses::BonusRaise> b) {
		if (_bonus->_raise != nullptr)
			remove_bonus(_bonus->_raise);
		add_bonus(b);
		_bonus->_raise = b;
	}

	std::shared_ptr<Bonuses::BonusAddItemDropOnMonsterKill> bonus_add_item_drop_on_monster_kill() { return _bonus->_add_item_drop_on_monster_kill; }
	void set_bonus_add_item_drop_on_monster_kill(std::shared_ptr<Bonuses::BonusAddItemDropOnMonsterKill> b) {
		if (_bonus->_add_item_drop_on_monster_kill != nullptr)
			remove_bonus(_bonus->_add_item_drop_on_monster_kill);
		add_bonus(b);
		_bonus->_add_item_drop_on_monster_kill = b;
	}

	std::shared_ptr<Bonuses::BonusHPDrainOnMonsterKill> bonus_hp_drain_on_monster_kill() { return _bonus->_hp_drain_on_monster_kill; }
	void set_bonus_hp_drain_on_monster_kill(std::shared_ptr<Bonuses::BonusHPDrainOnMonsterKill> b) {
		if (_bonus->_hp_drain_on_monster_kill != nullptr)
			remove_bonus(_bonus->_hp_drain_on_monster_kill);
		add_bonus(b);
		_bonus->_hp_drain_on_monster_kill = b;
	}

	std::shared_ptr<Bonuses::BonusSPDrainOnMonsterKill> bonus_sp_drain_on_monster_kill() { return _bonus->_sp_drain_on_monster_kill; }
	void set_bonus_sp_drain_on_monster_kill(std::shared_ptr<Bonuses::BonusSPDrainOnMonsterKill> b) {
		if (_bonus->_sp_drain_on_monster_kill != nullptr)
			remove_bonus(_bonus->_sp_drain_on_monster_kill);
		add_bonus(b);
		_bonus->_sp_drain_on_monster_kill = b;
	}

	void add_bonus(std::shared_ptr<Bonuses::IBonusArray> ba) { _bonus_arrays.push_back(ba); }
	void remove_bonus(std::shared_ptr<Bonuses::IBonusArray> ba)
	{
		_bonus_arrays.erase(std::remove(_bonus_arrays.begin(), _bonus_arrays.end(), ba), _bonus_arrays.end());
	}
	std::shared_ptr<Bonuses::IBonusArray> get_bonus_array(status_point_type type)
	{
		for (auto &ba : _bonus_arrays)
		{
			if (ba->get_type() == type)
				return ba;
		}

		return nullptr;
	}

	std::shared_ptr<Bonuses::BonusAddAttackPercentageToElement> bonus_add_attack_percentage_to_element() { return _bonus->_add_attack_percentage_to_element; }
	void set_bonus_add_attack_percentage_to_element(std::shared_ptr<Bonuses::BonusAddAttackPercentageToElement> b) {
		if (_bonus->_add_attack_percentage_to_element != nullptr)
			remove_bonus(_bonus->_add_attack_percentage_to_element);
		add_bonus(b);
		_bonus->_add_attack_percentage_to_element = b;
	}

	std::shared_ptr<Bonuses::BonusAddAttackPercentageToRace> bonus_add_attack_percentage_to_race() { return _bonus->_add_attack_percentage_to_race; }
	void set_bonus_add_attack_percentage_to_race(std::shared_ptr<Bonuses::BonusAddAttackPercentageToRace> b) {
		if (_bonus->_add_attack_percentage_to_race != nullptr)
			remove_bonus(_bonus->_add_attack_percentage_to_race);
		add_bonus(b);
		_bonus->_add_attack_percentage_to_race = b;
	}

	std::shared_ptr<Bonuses::BonusAddAttackPercentageToSize> bonus_add_attack_percentage_to_size() { return _bonus->_add_attack_percentage_to_size; }
	void set_bonus_add_attack_percentage_to_size(std::shared_ptr<Bonuses::BonusAddAttackPercentageToSize> b) {
		if (_bonus->_add_attack_percentage_to_size != nullptr)
			remove_bonus(_bonus->_add_attack_percentage_to_size);
		add_bonus(b);
		_bonus->_add_attack_percentage_to_size = b;
	}

	std::shared_ptr<Bonuses::BonusSubAttackPercentageFromElement> bonus_sub_attack_percentage_from_element() { return _bonus->_sub_attack_percentage_from_element; }
	void set_bonus_sub_attack_percentage_from_element(std::shared_ptr<Bonuses::BonusSubAttackPercentageFromElement> b) {
		if (_bonus->_sub_attack_percentage_from_element != nullptr)
			remove_bonus(_bonus->_sub_attack_percentage_from_element);
		add_bonus(b);
		_bonus->_sub_attack_percentage_from_element = b;
	}

	std::shared_ptr<Bonuses::BonusSubAttackPercentageFromRace> bonus_sub_attack_percentage_from_race() { return _bonus->_sub_attack_percentage_from_race; }
	void set_bonus_sub_attack_percentage_from_race(std::shared_ptr<Bonuses::BonusSubAttackPercentageFromRace> b) {
		if (_bonus->_sub_attack_percentage_from_race != nullptr)
			remove_bonus(_bonus->_sub_attack_percentage_from_race);
		add_bonus(b);
		_bonus->_sub_attack_percentage_from_race = b;
	}

	std::shared_ptr<Bonuses::BonusAddEffectOnDamage> bonus_add_effect_on_damage() { return _bonus->_add_effect_on_damage; }
	void set_bonus_add_effect_on_damage(std::shared_ptr<Bonuses::BonusAddEffectOnDamage> b) {
		if (_bonus->_add_effect_on_damage != nullptr)
			remove_bonus(_bonus->_add_effect_on_damage);
		add_bonus(b);
		_bonus->_add_effect_on_damage = b;
	}

	std::shared_ptr<Bonuses::BonusAddEffectWhenDamaged> bonus_add_effect_when_damaged() { return _bonus->_add_effect_when_damaged; }
	void set_bonus_add_effect_when_damaged(std::shared_ptr<Bonuses::BonusAddEffectWhenDamaged> b) {
		if (_bonus->_add_effect_when_damaged != nullptr)
			remove_bonus(_bonus->_add_effect_when_damaged);
		add_bonus(b);
		_bonus->_add_effect_when_damaged = b;
	}

	std::shared_ptr<Bonuses::BonusRessistEffect> bonus_ressist_effect() { return _bonus->_ressist_effect; }
	void set_bonus_ressist_effect(std::shared_ptr<Bonuses::BonusRessistEffect> b) {
		if (_bonus->_ressist_effect != nullptr)
			remove_bonus(_bonus->_ressist_effect);
		add_bonus(b);
		_bonus->_ressist_effect = b;
	}

	std::shared_ptr<Bonuses::BonusAddMagicAttackPercentageToElement> bonus_add_magic_attack_percentage_to_element() { return _bonus->_add_magic_attack_percentage_to_element; }
	void set_bonus_add_magic_attack_percentage_to_element(std::shared_ptr<Bonuses::BonusAddMagicAttackPercentageToElement> b) {
		if (_bonus->_add_magic_attack_percentage_to_element != nullptr)
			remove_bonus(_bonus->_add_magic_attack_percentage_to_element);
		add_bonus(b);
		_bonus->_add_magic_attack_percentage_to_element = b;
	}

	std::shared_ptr<Bonuses::BonusAddMagicAttackPercentageToRace> bonus_add_magic_attack_to_Race() { return _bonus->_add_magic_attack_percentage_to_race; }
	void set_bonus_add_magic_attack_percentage_to_race(std::shared_ptr<Bonuses::BonusAddMagicAttackPercentageToRace> b) {
		if (_bonus->_add_magic_attack_percentage_to_race != nullptr)
			remove_bonus(_bonus->_add_magic_attack_percentage_to_race);
		add_bonus(b);
		_bonus->_add_magic_attack_percentage_to_race = b;
	}

	std::shared_ptr<Bonuses::BonusAddMagicAttackPercentageToSize> bonus_add_magic_attack_percentage_to_size() { return _bonus->_add_magic_attack_percentage_to_size; }
	void set_bonus_add_magic_attack_percentage_to_size(std::shared_ptr<Bonuses::BonusAddMagicAttackPercentageToSize> b) {
		if (_bonus->_add_magic_attack_percentage_to_size != nullptr)
			remove_bonus(_bonus->_add_magic_attack_percentage_to_size);
		add_bonus(b);
		_bonus->_add_magic_attack_percentage_to_size = b;
	}

	std::shared_ptr<Bonuses::BonusAddEffectOnMagicAttack> bonus_add_effect_on_magic_attack() { return _bonus->_add_effect_on_magic_attack; }
	void set_bonus_add_effect_on_magic_attack(std::shared_ptr<Bonuses::BonusAddEffectOnMagicAttack> b) {
		if (_bonus->_add_effect_on_magic_attack != nullptr)
			remove_bonus(_bonus->_add_effect_on_magic_attack);
		add_bonus(b);
		_bonus->_add_effect_on_magic_attack = b;
	}

	std::shared_ptr<Bonuses::BonusResistMagicAttackFromRace> bonus_resist_magic_attack_from_race() { return _bonus->_resist_magic_attack_from_race; }
	void set_bonus_resist_magic_attack_from_race(std::shared_ptr<Bonuses::BonusResistMagicAttackFromRace> b) {
		if (_bonus->_resist_magic_attack_from_race != nullptr)
			remove_bonus(_bonus->_resist_magic_attack_from_race);
		add_bonus(b);
		_bonus->_resist_magic_attack_from_race = b;
	}

	std::shared_ptr<Bonuses::BonusAddDamageToClass> bonus_add_damage_to_class() { return _bonus->_add_damage_to_class; }
	void set_bonus_add_damage_to_class(std::shared_ptr<Bonuses::BonusAddDamageToClass> b) {
		if (_bonus->_add_damage_to_class != nullptr)
			remove_bonus(_bonus->_add_damage_to_class);
		add_bonus(b);
		_bonus->_add_damage_to_class = b;
	}

	std::shared_ptr<Bonuses::BonusAddMagicDamageToClass> bonus_add_magic_damage_to_class() { return _bonus->_add_magic_damage_to_class; }
	void set_bonus_add_magic_damage_to_class(std::shared_ptr<Bonuses::BonusAddMagicDamageToClass> b) {
		if (_bonus->_add_magic_damage_to_class != nullptr)
			remove_bonus(_bonus->_add_magic_damage_to_class);
		add_bonus(b);
		_bonus->_add_magic_damage_to_class = b;
	}

	std::shared_ptr<Bonuses::BonusAddDefenseToClass> bonus_add_defense_to_class() { return _bonus->_add_defense_to_class; }
	void set_bonus_add_defense_to_class(std::shared_ptr<Bonuses::BonusAddDefenseToClass> b) {
		if (_bonus->_add_defense_to_class != nullptr)
			remove_bonus(_bonus->_add_defense_to_class);
		add_bonus(b);
		_bonus->_add_defense_to_class = b;
	}

	std::shared_ptr<Bonuses::BonusAddMagicalDefenseToClass> bonus_add_magical_defense_to_class() { return _bonus->_add_magical_defense_to_class; }
	void set_bonus_add_magical_defense_to_class(std::shared_ptr<Bonuses::BonusAddMagicalDefenseToClass> b) {
		if (_bonus->_add_magical_defense_to_class != nullptr)
			remove_bonus(_bonus->_add_magical_defense_to_class);
		add_bonus(b);
		_bonus->_add_magical_defense_to_class = b;
	}

	std::shared_ptr<Bonuses::BonusHPDrainPercent> bonus_hp_drain_percent() { return _bonus->_hp_drain_percent; }
	void set_bonus_hp_drain_percent(std::shared_ptr<Bonuses::BonusHPDrainPercent> b) {
		if (_bonus->_hp_drain_percent != nullptr)
			remove_bonus(_bonus->_hp_drain_percent);
		add_bonus(b);
		_bonus->_hp_drain_percent = b;
	}

	std::shared_ptr<Bonuses::BonusHPDrainValue> bonus_hp_drain_value() { return _bonus->_hp_drain_value; }
	void set_bonus_hp_drain_value(std::shared_ptr<Bonuses::BonusHPDrainValue> b) {
		if (_bonus->_hp_drain_value != nullptr)
			remove_bonus(_bonus->_hp_drain_value);
		add_bonus(b);
		_bonus->_hp_drain_value = b;
	}

	std::shared_ptr<Bonuses::BonusSPDrainPercent> bonus_sp_drain_percent() { return _bonus->_sp_drain_percent; }
	void set_bonus_sp_drain_percent(std::shared_ptr<Bonuses::BonusSPDrainPercent> b) {
		if (_bonus->_sp_drain_percent != nullptr)
			remove_bonus(_bonus->_sp_drain_percent);
		add_bonus(b);
		_bonus->_sp_drain_percent = b;
	}

	std::shared_ptr<Bonuses::BonusSPDrainValue> bonus_sp_drain_value() { return _bonus->_bonus_sp_drain_value; }
	void set_bonus_sp_drain_value(std::shared_ptr<Bonuses::BonusSPDrainValue> b) {
		if (_bonus->_bonus_sp_drain_value != nullptr)
			remove_bonus(_bonus->_bonus_sp_drain_value);
		add_bonus(b);
		_bonus->_bonus_sp_drain_value = b;
	}

	std::shared_ptr<Bonuses::BonusAddWeaponComaToElement> bonus_add_weapon_coma_to_element() { return _bonus->_add_weapon_coma_to_element; }
	void set_bonus_add_weapon_coma_to_element(std::shared_ptr<Bonuses::BonusAddWeaponComaToElement> b) {
		if (_bonus->_add_weapon_coma_to_element != nullptr)
			remove_bonus(_bonus->_add_weapon_coma_to_element);
		add_bonus(b);
		_bonus->_add_weapon_coma_to_element = b;
	}

	std::shared_ptr<Bonuses::BonusAddWeaponComaToRace> bonus_add_weapon_coma_to_race() { return _bonus->_add_weapon_coma_to_race; }
	void set_bonus_add_weapon_coma_to_race(std::shared_ptr<Bonuses::BonusAddWeaponComaToRace> b) {
		if (_bonus->_add_weapon_coma_to_race != nullptr)
			remove_bonus(_bonus->_add_weapon_coma_to_race);
		add_bonus(b);
		_bonus->_add_weapon_coma_to_race = b;
	}

	std::shared_ptr<Bonuses::BonusAddWeaponComaToSubElement> bonus_add_weapon_coma_to_sub_element() { return _bonus->_add_weapon_coma_to_sub_element; }
	void set_bonus_add_weapon_coma_to_sub_element(std::shared_ptr<Bonuses::BonusAddWeaponComaToSubElement> b) {
		if (_bonus->_add_weapon_coma_to_sub_element != nullptr)
			remove_bonus(_bonus->_add_weapon_coma_to_sub_element);
		add_bonus(b);
		_bonus->_add_weapon_coma_to_sub_element = b;
	}

	std::shared_ptr<Bonuses::BonusAddWeaponComaToSubRace> bonus_add_weapon_coma_to_sub_race() { return _bonus->_add_weapon_coma_to_sub_race; }
	void set_bonus_add_weapon_coma_to_sub_race(std::shared_ptr<Bonuses::BonusAddWeaponComaToSubRace> b) {
		if (_bonus->_add_weapon_coma_to_sub_race != nullptr)
			remove_bonus(_bonus->_add_weapon_coma_to_sub_race);
		add_bonus(b);
		_bonus->_add_weapon_coma_to_sub_race = b;
	}

	std::shared_ptr<Bonuses::BonusAddAttack> bonus_add_attack() { return _bonus->_add_attack; }
	void set_bonus_add_attack(std::shared_ptr<Bonuses::BonusAddAttack> b) {
		if (_bonus->_add_attack != nullptr)
			remove_bonus(_bonus->_add_attack);
		add_bonus(b);
		_bonus->_add_attack = b;
	}

	std::shared_ptr<Bonuses::BonusAddAttackPercent> bonus_add_attack_percent() { return _bonus->_add_attack_percent; }
	void set_bonus_add_attack_percent(std::shared_ptr<Bonuses::BonusAddAttackPercent> b) {
		if (_bonus->_add_attack_percent != nullptr)
			remove_bonus(_bonus->_add_attack_percent);
		add_bonus(b);
		_bonus->_add_attack_percent = b;
	}

	std::shared_ptr<Bonuses::BonusCriticalRace> bonus_critical_race() { return _bonus->_critical_race; }
	void set_bonus_critical_race(std::shared_ptr<Bonuses::BonusCriticalRace> b) {
		if (_bonus->_critical_race != nullptr)
			remove_bonus(_bonus->_critical_race);
		add_bonus(b);
		_bonus->_critical_race = b;
	}

	std::shared_ptr<Bonuses::BonusCriticalRacePercent> bonus_critical_race_percent() { return _bonus->_critical_race_percent; }
	void set_bonus_critical_race_percent(std::shared_ptr<Bonuses::BonusCriticalRacePercent> b) {
		if (_bonus->_critical_race_percent != nullptr)
			remove_bonus(_bonus->_critical_race_percent);
		add_bonus(b);
		_bonus->_critical_race_percent = b;
	}

	std::shared_ptr<Bonuses::BonusDamageReductionAgainstSize> bonus_damage_reduction_against_size() { return _bonus->_damage_reduction_against_size; }
	void set_bonus_damage_reduction_against_size(std::shared_ptr<Bonuses::BonusDamageReductionAgainstSize> b) {
		if (_bonus->_damage_reduction_against_size != nullptr)
			remove_bonus(_bonus->_damage_reduction_against_size);
		add_bonus(b);
		_bonus->_damage_reduction_against_size = b;
	}

	std::shared_ptr<Bonuses::BonusMagicDamageReductionAgainstSize> bonus_magic_damage_reduction_against_size() { return _bonus->_magic_damage_reduction_against_size; }
	void set_bonus_magic_damage_reduction_against_size(std::shared_ptr<Bonuses::BonusMagicDamageReductionAgainstSize> b) {
		if (_bonus->_magic_damage_reduction_against_size != nullptr)
			remove_bonus(_bonus->_magic_damage_reduction_against_size);
		add_bonus(b);
		_bonus->_magic_damage_reduction_against_size = b;
	}

	std::shared_ptr<Bonuses::BonusExpPercentPerRace> bonus_exp_percent_per_race() { return _bonus->_exp_percent_per_race; }
	void set_bonus_exp_percent_per_race(std::shared_ptr<Bonuses::BonusExpPercentPerRace> b) {
		if (_bonus->_exp_percent_per_race != nullptr)
			remove_bonus(_bonus->_exp_percent_per_race);
		add_bonus(b);
		_bonus->_exp_percent_per_race = b;
	}

	std::shared_ptr<Bonuses::BonusJobPercentPerRace> bonus_job_percent_per_race() { return _bonus->_job_percent_per_race; }
	void set_bonus_job_percent_per_race(std::shared_ptr<Bonuses::BonusJobPercentPerRace> b) {
		if (_bonus->_job_percent_per_race != nullptr)
			remove_bonus(_bonus->_job_percent_per_race);
		add_bonus(b);
		_bonus->_job_percent_per_race = b;
	}

	std::shared_ptr<Bonuses::BonusSkillAttack> bonus_skill_attack() { return _bonus->_skill_attack; }
	void set_bonus_skill_attack(std::shared_ptr<Bonuses::BonusSkillAttack> b) {
		if (_bonus->_skill_attack != nullptr)
			remove_bonus(_bonus->_skill_attack);
		add_bonus(b);
		_bonus->_skill_attack = b;
	}

	std::shared_ptr<Bonuses::BonusReduceSPConsumptionOfSkillByPercent> bonus_reduce_sp_consumption_of_skill_by_percent() { return _bonus->_reduce_sp_consumption_of_skill_by_percent; }
	void set_bonus_reduce_sp_consumption_of_skill_by_percent(std::shared_ptr<Bonuses::BonusReduceSPConsumptionOfSkillByPercent> b) {
		if (_bonus->_reduce_sp_consumption_of_skill_by_percent != nullptr)
			remove_bonus(_bonus->_reduce_sp_consumption_of_skill_by_percent);
		add_bonus(b);
		_bonus->_reduce_sp_consumption_of_skill_by_percent = b;
	}

	std::shared_ptr<Bonuses::BonusReduceSPConsumptionOfSkill> bonus_reduce_sp_consumption_of_skill() { return _bonus->_reduce_sp_consumption_of_skill; }
	void set_bonus_reduce_sp_consumption_of_skill(std::shared_ptr<Bonuses::BonusReduceSPConsumptionOfSkill> b) {
		if (_bonus->_reduce_sp_consumption_of_skill != nullptr)
			remove_bonus(_bonus->_reduce_sp_consumption_of_skill);
		add_bonus(b);
		_bonus->_reduce_sp_consumption_of_skill = b;
	}

	std::shared_ptr<Bonuses::BonusLearnedSkillHeal> bonus_learned_skill_heal() { return _bonus->_learned_skill_heal; }
	void set_bonus_learned_skill_heal(std::shared_ptr<Bonuses::BonusLearnedSkillHeal> b) {
		if (_bonus->_learned_skill_heal != nullptr)
			remove_bonus(_bonus->_learned_skill_heal);
		add_bonus(b);
		_bonus->_learned_skill_heal = b;
	}

	std::shared_ptr<Bonuses::BonusHealOfSkillCastedOnSelf> bonus_heal_of_skill_casted_on_self() { return _bonus->_heal_of_skill_casted_on_self; }
	void set_bonus_heal_of_skill_casted_on_self(std::shared_ptr<Bonuses::BonusHealOfSkillCastedOnSelf> b) {
		if (_bonus->_heal_of_skill_casted_on_self != nullptr)
			remove_bonus(_bonus->_heal_of_skill_casted_on_self);
		add_bonus(b);
		_bonus->_heal_of_skill_casted_on_self = b;
	}

	std::shared_ptr<Bonuses::BonusSkillKnockback> bonus_skill_knockback() { return _bonus->_skill_knockback; }
	void set_bonus_skill_knockback(std::shared_ptr<Bonuses::BonusSkillKnockback> b) {
		if (_bonus->_skill_knockback != nullptr)
			remove_bonus(_bonus->_skill_knockback);
		add_bonus(b);
		_bonus->_skill_knockback = b;
	}

	std::shared_ptr<Bonuses::BonusSkillCastPercent> bonus_skill_cast_percent() { return _bonus->_skill_cast_percent; }
	void set_bonus_skill_cast_percent(std::shared_ptr<Bonuses::BonusSkillCastPercent> b) {
		if (_bonus->_skill_cast_percent != nullptr)
			remove_bonus(_bonus->_skill_cast_percent);
		add_bonus(b);
		_bonus->_skill_cast_percent = b;
	}

	std::shared_ptr<Bonuses::BonusSkillCooldown> bonus_skill_cooldown() { return _bonus->_skill_cooldown; }
	void set_bonus_skill_cooldown(std::shared_ptr<Bonuses::BonusSkillCooldown> b) {
		if (_bonus->_skill_cooldown != nullptr)
			remove_bonus(_bonus->_skill_cooldown);
		add_bonus(b);
		_bonus->_skill_cooldown = b;
	}
	
	std::shared_ptr<Bonuses::BonusSkillFixCastPercent> bonus_skill_fix_cast_percent() { return _bonus->_skill_fix_cast_percent; }
	void set_bonus_skill_fix_cast_percent(std::shared_ptr<Bonuses::BonusSkillFixCastPercent> b) {
		if (_bonus->_skill_fix_cast_percent != nullptr)
			remove_bonus(_bonus->_skill_fix_cast_percent);
		add_bonus(b);
		_bonus->_skill_fix_cast_percent = b;
	}

	std::shared_ptr<Bonuses::BonusSkillVariableCastPercent> bonus_skill_variable_cast_percent() { return _bonus->_skill_variable_cast_percent; }
	void set_bonus_skill_variable_cast_percent(std::shared_ptr<Bonuses::BonusSkillVariableCastPercent> b) {
		if (_bonus->_skill_variable_cast_percent != nullptr)
			remove_bonus(_bonus->_skill_variable_cast_percent);
		add_bonus(b);
		_bonus->_skill_variable_cast_percent = b;
	}

	std::shared_ptr<Bonuses::BonusResistSkillDamagePercent> bonus_resist_skill_damage_percent() { return _bonus->_resist_skill_damage_percent; }
	void set_bonus_resist_skill_damage_percent(std::shared_ptr<Bonuses::BonusResistSkillDamagePercent> b) {
		if (_bonus->_resist_skill_damage_percent != nullptr)
			remove_bonus(_bonus->_resist_skill_damage_percent);
		add_bonus(b);
		_bonus->_resist_skill_damage_percent = b;
	}

	std::shared_ptr<Bonuses::BonusIgnoreDefenseFromElement> bonus_ignore_defense_from_element() { return _bonus->_ignore_defense_from_element; }
	void set_bonus_ignore_defense_from_element(std::shared_ptr<Bonuses::BonusIgnoreDefenseFromElement> b) {
		if (_bonus->_ignore_defense_from_element != nullptr)
			remove_bonus(_bonus->_ignore_defense_from_element);
		add_bonus(b);
		_bonus->_ignore_defense_from_element = b;
	}

	std::shared_ptr<Bonuses::BonusIgnoreDefenseFromRace> bonus_ignore_defense_from_race() { return _bonus->_ignore_defense_from_race; }
	void set_bonus_ignore_defense_from_race(std::shared_ptr<Bonuses::BonusIgnoreDefenseFromRace> b) {
		if (_bonus->_ignore_defense_from_race != nullptr)
			remove_bonus(_bonus->_ignore_defense_from_race);
		add_bonus(b);
		_bonus->_ignore_defense_from_race = b;
	}

	std::shared_ptr<Bonuses::BonusIgnoreMagicDefenseFromElement> bonus_ignore_magic_defense_from_element() { return _bonus->_ignore_magic_defense_from_element; }
	void set_bonus_ignore_magic_defense_from_element(std::shared_ptr<Bonuses::BonusIgnoreMagicDefenseFromElement> b) {
		if (_bonus->_ignore_magic_defense_from_element != nullptr)
			remove_bonus(_bonus->_ignore_magic_defense_from_element);
		add_bonus(b);
		_bonus->_ignore_magic_defense_from_element = b;
	}

	std::shared_ptr<Bonuses::BonusIgnoreMagicDefenseFromRace> bonus_ignore_magic_defense_from_race() { return _bonus->_ignore_magic_defense_from_race; }
	void set_bonus_ignore_magic_defense_from_race(std::shared_ptr<Bonuses::BonusIgnoreMagicDefenseFromRace> b) {
		if (_bonus->_ignore_magic_defense_from_race != nullptr)
			remove_bonus(_bonus->_ignore_magic_defense_from_race);
		add_bonus(b);
		_bonus->_ignore_magic_defense_from_race = b;
	}

	std::shared_ptr<Bonuses::BonusAddEleWeaponDamagePercent> bonus_add_ele_weapon_damage_percent() { return _bonus->_add_ele_weapon_damage_percent; }
	void set_bonus_add_ele_weapon_damage_percent(std::shared_ptr<Bonuses::BonusAddEleWeaponDamagePercent> b) {
		if (_bonus->_add_ele_weapon_damage_percent != nullptr)
			remove_bonus(_bonus->_add_ele_weapon_damage_percent);
		add_bonus(b);
		_bonus->_add_ele_weapon_damage_percent = b;
	}

	std::shared_ptr<Bonuses::BonusAddEleMagicDamagePercent> bonus_add_ele_magic_damage_percent() { return _bonus->_add_ele_magic_damage_percent; }
	void set_bonus_add_ele_magic_damage_percent(std::shared_ptr<Bonuses::BonusAddEleMagicDamagePercent> b) {
		if (_bonus->_add_ele_magic_damage_percent != nullptr)
			remove_bonus(_bonus->_add_ele_magic_damage_percent);
		add_bonus(b);
		_bonus->_add_ele_magic_damage_percent = b;
	}

	std::shared_ptr<Bonuses::BonusAutoSpellOnSkill> bonus_auto_spell_on_skill() { return _bonus->_auto_spell_on_skill; }
	void set_bonus_auto_spell_on_skill(std::shared_ptr<Bonuses::BonusAutoSpellOnSkill> b) {
		if (_bonus->_auto_spell_on_skill != nullptr)
			remove_bonus(_bonus->_auto_spell_on_skill);
		add_bonus(b);
		_bonus->_auto_spell_on_skill = b;
	}

	std::shared_ptr<Bonuses::BonusAutoSpellOnAttack> bonus_auto_spell_on_attack() { return _bonus->_auto_spell_on_attack; }
	void set_bonus_auto_spell_on_attack(std::shared_ptr<Bonuses::BonusAutoSpellOnAttack> b) {
		if (_bonus->_auto_spell_on_attack != nullptr)
			remove_bonus(_bonus->_auto_spell_on_attack);
		add_bonus(b);
		_bonus->_auto_spell_on_attack = b;
	}

	std::shared_ptr<Bonuses::BonusAutoSpellOnReceiveDamage> bonus_auto_spell_on_receive_damage() { return _bonus->_auto_spell_on_receive_damage; }
	void set_bonus_auto_spell_on_receive_damage(std::shared_ptr<Bonuses::BonusAutoSpellOnReceiveDamage> b) {
		if (_bonus->_auto_spell_on_receive_damage != nullptr)
			remove_bonus(_bonus->_auto_spell_on_receive_damage);
		add_bonus(b);
		_bonus->_auto_spell_on_receive_damage = b;
	}

	std::shared_ptr<Bonuses::BonusAutoSpellOnSelf> bonus_auto_spell_on_self() { return _bonus->_auto_spell_on_self; }
	void set_bonus_auto_spell_on_self(std::shared_ptr<Bonuses::BonusAutoSpellOnSelf> b) {
		if (_bonus->_auto_spell_on_self != nullptr)
			remove_bonus(_bonus->_auto_spell_on_self);
		add_bonus(b);
		_bonus->_auto_spell_on_self = b;
	}

protected:
	std::shared_ptr<Unit> unit() { return _unit.lock(); }
	unit_type _type{ UNIT_PLAYER };
	bool _is_initialized{ false };

private:
	std::shared_ptr<StatusRegistry> _status_registry{ nullptr };
	std::weak_ptr<Unit> _unit;
	// Attributes
	std::shared_ptr<Strength> _str;
	std::shared_ptr<Agility> _agi;
	std::shared_ptr<Vitality> _vit;
	std::shared_ptr<Intelligence> _int;
	std::shared_ptr<Dexterity> _dex;
	std::shared_ptr<Luck> _luk;
	std::shared_ptr<StrengthPointCost> _str_cost;
	std::shared_ptr<AgilityPointCost> _agi_cost;
	std::shared_ptr<VitalityPointCost> _vit_cost;
	std::shared_ptr<IntelligencePointCost> _int_cost;
	std::shared_ptr<DexterityPointCost> _dex_cost;
	std::shared_ptr<LuckPointCost> _luk_cost;
	std::shared_ptr<StatusPoint> _status_point;
	std::shared_ptr<SkillPoint> _skill_point;
	std::shared_ptr<MaxHP> _max_hp;
	std::shared_ptr<MaxSP> _max_sp;
	std::shared_ptr<CurrentHP> _current_hp;
	std::shared_ptr<CurrentSP> _current_sp;
	std::shared_ptr<BaseLevel> _base_level;
	std::shared_ptr<JobLevel> _job_level;
	std::shared_ptr<BaseExperience> _base_exp;
	std::shared_ptr<JobExperience> _job_exp;
	std::shared_ptr<NextBaseExperience> _next_base_exp;
	std::shared_ptr<NextJobExperience> _next_job_exp;
	std::shared_ptr<MovementSpeed> _movement_speed;
	std::shared_ptr<MaxWeight> _max_weight;
	std::shared_ptr<CurrentWeight> _current_weight;
	std::shared_ptr<AttackRange> _attack_range;
	/* Sub Attributes */
	std::shared_ptr<StatusATK> _status_atk;
	std::shared_ptr<EquipATK> _equip_atk;
	std::shared_ptr<StatusMATK> _status_matk;
	std::shared_ptr<EquipMATK> _equip_matk;
	std::shared_ptr<SoftDEF> _soft_def;
	std::shared_ptr<HardDEF> _hard_def;
	std::shared_ptr<SoftMDEF> _soft_mdef;
	std::shared_ptr<HardMDEF> _hard_mdef;
	std::shared_ptr<HIT> _hit;
	std::shared_ptr<CRIT> _crit;
	std::shared_ptr<FLEE> _flee;
	std::shared_ptr<AttackSpeed> _aspd;
	std::shared_ptr<HPRegeneration> _hp_regeneration;
	std::shared_ptr<SPRegeneration> _sp_regeneration;
	/* Appearance */
	std::shared_ptr<BaseAppearance> _base_appearance;
	std::shared_ptr<HairColor> _hair_color;
	std::shared_ptr<ClothColor> _cloth_color;
	std::shared_ptr<WeaponSprite> _weapon_sprite;
	std::shared_ptr<ShieldSprite> _shield_sprite;
	std::shared_ptr<RobeSprite> _robe_sprite;
	std::shared_ptr<HeadTopSprite> _head_top_sprite;
	std::shared_ptr<HeadMidSprite> _head_mid_sprite;
	std::shared_ptr<HeadBottomSprite> _head_bottom_sprite;
	std::shared_ptr<HairStyle> _hair_style;
	std::shared_ptr<BodyStyle> _body_style;
	/* Misc */
	std::shared_ptr<Zeny> _zeny;
	std::shared_ptr<Honor> _honor;
	std::shared_ptr<Manner> _manner;
	std::shared_ptr<Virtue> _virtue;
	/* Combat Status */
	std::shared_ptr<AttackDelay> _attack_delay;
	std::shared_ptr<DamageWalkDelay> _damage_walk_delay;
	std::shared_ptr<BaseAttack> _base_attack;
	std::shared_ptr<WeaponAttackLeft> _weapon_attack_left;
	std::shared_ptr<WeaponAttackRight> _weapon_attack_right;
	std::shared_ptr<WeaponAttackCombined> _weapon_attack_combined;
	std::shared_ptr<UnitSize> _size;
	/* Mobs */
	std::shared_ptr<MobWeaponAttack> _creature_weapon_attack;
	std::shared_ptr<MobWeaponAttack> _creature_weapon_attack_magic;
	std::shared_ptr<MobAttackDamage> _creature_attack_damage;
	std::shared_ptr<MobMagicAttackDamage> _creature_magic_attack_damage;
	std::shared_ptr<MobViewRange> _creature_view_range;
	std::shared_ptr<MobChaseRange> _creature_chase_range;
	std::shared_ptr<MobPrimaryRace> _creature_primary_race;
	std::shared_ptr<MobSecondaryRace> _creature_secondary_race;
	std::shared_ptr<MobElement> _creature_element;
	std::shared_ptr<MobElementLevel> _creature_element_level;
	std::shared_ptr<MobMode> _creature_mode;

	std::vector<std::shared_ptr<Attribute>> _attributes;
	std::vector<std::shared_ptr<Appearance>> _appearances;
	std::vector<std::shared_ptr<Bonuses::Bonus>> _bonuses;
	std::vector<std::shared_ptr<Bonuses::IBonusArray>> _bonus_arrays;

	struct bonuses {
		// Bonuses
		std::shared_ptr<Bonuses::BonusAllStatus> _all_status;
		std::shared_ptr<Bonuses::BonusAttackElement> _attack_element;
		std::shared_ptr<Bonuses::BonusDefenseElement> _defense_element;
		std::shared_ptr<Bonuses::BonusCastPercent> _cast_percent;
		std::shared_ptr<Bonuses::BonusMaxHPPercent> _max_hp_percent;
		std::shared_ptr<Bonuses::BonusMaxSPPercent> _max_sp_percent;
		std::shared_ptr<Bonuses::BonusSPPercent> _sp_percent;
		std::shared_ptr<Bonuses::BonusAttackRange> _attack_range;
		std::shared_ptr<Bonuses::BonusAttackRangePercent> _attack_range_percent;
		std::shared_ptr<Bonuses::BonusAddMovementSpeedPercent>	_bonus_add_movement_speed_percent;
		std::shared_ptr<Bonuses::BonusAttackSpeedPercent> _attack_speed_percent;
		std::shared_ptr<Bonuses::BonusHPRecoveryPercent> _hp_recovery_percent;
		std::shared_ptr<Bonuses::BonusSPRecoveryPercent> _sp_recovery_percent;
		std::shared_ptr<Bonuses::BonusCriticalDefense> _critical_defense;
		std::shared_ptr<Bonuses::BonusMeleeDefense> _melee_defense;
		std::shared_ptr<Bonuses::BonusRangedDefense> _ranged_defense;
		std::shared_ptr<Bonuses::BonusDoubleAttackPercent> _double_attack_percent;
		std::shared_ptr<Bonuses::BonusMagicAttackPercent> _magic_attack_percent;
		std::shared_ptr<Bonuses::BonusAttackPercent> _attack_percent;
		std::shared_ptr<Bonuses::BonusMagicDefensePercent> _magic_defense_percent;
		std::shared_ptr<Bonuses::BonusMiscDefensePercent> _misc_defense_percent;
		std::shared_ptr<Bonuses::BonusPerfectHitPercent> _perfect_hit_percent;
		std::shared_ptr<Bonuses::BonusCriticalPercent> _critical_percent;
		std::shared_ptr<Bonuses::BonusGetZenyNum> _get_zeny_num;
		std::shared_ptr<Bonuses::BonusAttackOnDefenseRatioForElement> _attack_on_defense_ratio_for_element;
		std::shared_ptr<Bonuses::BonusAttackOnDefenseRatioForRace> _attack_on_defense_ratio_for_race;
		std::shared_ptr<Bonuses::BonusHitPercent> _hit_percent;
		std::shared_ptr<Bonuses::BonusFleePercent> _flee_percent;
		std::shared_ptr<Bonuses::BonusPerfectDodgePercent> _perfect_dodge_percent;
		std::shared_ptr<Bonuses::BonusSoftDefensePercent> _soft_defense_percent;
		std::shared_ptr<Bonuses::BonusHardDefensePercent> _hard_defense_percent;
		std::shared_ptr<Bonuses::BonusSoftMagicalDefensePercent> _soft_magical_defense_percent;
		std::shared_ptr<Bonuses::BonusHardMagicalDefensePercent> _hard_magical_defense_percent;
		std::shared_ptr<Bonuses::BonusRestartWithFullRecovery> _restart_with_full_recovery;
		std::shared_ptr<Bonuses::BonusCastCancelImmunity> _cast_cancel_immunity;
		std::shared_ptr<Bonuses::BonusSizeModifierImmunity> _size_modifier_immunity;
		std::shared_ptr<Bonuses::BonusMagicDamageImmunity> _magic_damage_immunity;
		std::shared_ptr<Bonuses::BonusWeaponDamageImmunity> _weapon_damage_immunity;
		std::shared_ptr<Bonuses::BonusGemstoneImmunity> _gemstone_immunity;
		std::shared_ptr<Bonuses::BonusGearFuelImmunity> _gear_fuel_immunity;
		std::shared_ptr<Bonuses::BonusInfiniteEndure> _infinite_endure;
		std::shared_ptr<Bonuses::BonusUnbreakableWeapon> _unbreakable_weapon;
		std::shared_ptr<Bonuses::BonusUnbreakableArmor> _unbreakable_armor;
		std::shared_ptr<Bonuses::BonusUnbreakableHelm> _unbreakable_helm;
		std::shared_ptr<Bonuses::BonusUnbreakableShield> _unbreakable_shield;
		std::shared_ptr<Bonuses::BonusSPGainOnMobKill> _sp_gain_on_mob_kill;
		std::shared_ptr<Bonuses::BonusHPGainOnMobKill> _hp_gain_on_mob_kill;
		std::shared_ptr<Bonuses::BonusDamageSplashRange> _damage_splash_range;
		std::shared_ptr<Bonuses::BonusMeleeWeaponDamageReflectPercentOnSelf> _melee_weapon_damage_reflect_percent_on_self;
		std::shared_ptr<Bonuses::BonusRangedWeaponDamageReflectPercentOnSelf> _ranged_weapon_damage_reflect_percent_on_self;
		std::shared_ptr<Bonuses::BonusWeaponBreakPercent> _weapon_break_percent;
		std::shared_ptr<Bonuses::BonusArmorBreakPercent> _armor_break_percent;
		std::shared_ptr<Bonuses::BonusAddStealPercent> _add_steal_percent;
		std::shared_ptr<Bonuses::BonusCriticalDamagePercent> _critical_damage_percent;
		std::shared_ptr<Bonuses::BonusDisableHPRecovery> _disable_hp_recovery;
		std::shared_ptr<Bonuses::BonusDisableSPRecovery> _disable_sp_recovery;
		std::shared_ptr<Bonuses::BonusMagicDamageReflectPercentOnSelf> _magic_damage_reflect_percent_on_self;
		std::shared_ptr<Bonuses::BonusShortWeaponDamagePercent> _short_weapon_damage_percent;
		std::shared_ptr<Bonuses::BonusLongWeaponDamagePercent> _long_weapon_damage_percent;
		std::shared_ptr<Bonuses::BonusItemUsageImmunity> _item_usage_immunity; 
		std::shared_ptr<Bonuses::BonusKnockBackImmunity> _knockback_immunity;
		// Bonus2
		std::shared_ptr<Bonuses::BonusAddAttackPercentageToElement> _add_attack_percentage_to_element;
		std::shared_ptr<Bonuses::BonusAddAttackPercentageToRace> _add_attack_percentage_to_race;
		std::shared_ptr<Bonuses::BonusAddAttackPercentageToSize> _add_attack_percentage_to_size;
		std::shared_ptr<Bonuses::BonusSubAttackPercentageFromElement> _sub_attack_percentage_from_element;
		std::shared_ptr<Bonuses::BonusSubAttackPercentageFromRace> _sub_attack_percentage_from_race;
		std::shared_ptr<Bonuses::BonusAddEffectOnDamage> _add_effect_on_damage;
		std::shared_ptr<Bonuses::BonusAddEffectWhenDamaged> _add_effect_when_damaged;
		std::shared_ptr<Bonuses::BonusRessistEffect> _ressist_effect;
		std::shared_ptr<Bonuses::BonusAddMagicAttackPercentageToElement> _add_magic_attack_percentage_to_element;
		std::shared_ptr<Bonuses::BonusAddMagicAttackPercentageToRace> _add_magic_attack_percentage_to_race;
		std::shared_ptr<Bonuses::BonusAddMagicAttackPercentageToSize> _add_magic_attack_percentage_to_size;
		std::shared_ptr<Bonuses::BonusAddEffectOnMagicAttack> _add_effect_on_magic_attack;
		std::shared_ptr<Bonuses::BonusResistMagicAttackFromRace> _resist_magic_attack_from_race;
		std::shared_ptr<Bonuses::BonusAddDamageToClass> _add_damage_to_class;
		std::shared_ptr<Bonuses::BonusAddMagicDamageToClass> _add_magic_damage_to_class;
		std::shared_ptr<Bonuses::BonusAddDefenseToClass> _add_defense_to_class;
		std::shared_ptr<Bonuses::BonusAddMagicalDefenseToClass> _add_magical_defense_to_class;
		std::shared_ptr<Bonuses::BonusHPDrainPercent> _hp_drain_percent;
		std::shared_ptr<Bonuses::BonusHPDrainValue> _hp_drain_value;
		std::shared_ptr<Bonuses::BonusSPDrainPercent> _sp_drain_percent;
		std::shared_ptr<Bonuses::BonusSPDrainValue>	 _bonus_sp_drain_value;
		std::shared_ptr<Bonuses::BonusAddWeaponComaToElement> _add_weapon_coma_to_element;
		std::shared_ptr<Bonuses::BonusAddWeaponComaToRace> _add_weapon_coma_to_race;
		std::shared_ptr<Bonuses::BonusAddWeaponComaToSubElement> _add_weapon_coma_to_sub_element;
		std::shared_ptr<Bonuses::BonusAddWeaponComaToSubRace> _add_weapon_coma_to_sub_race;
		std::shared_ptr<Bonuses::BonusAddAttack> _add_attack;
		std::shared_ptr<Bonuses::BonusAddAttackPercent>	_add_attack_percent;
		std::shared_ptr<Bonuses::BonusCriticalRace>	_critical_race;
		std::shared_ptr<Bonuses::BonusCriticalRacePercent> _critical_race_percent;
		std::shared_ptr<Bonuses::BonusDamageReductionAgainstSize> _damage_reduction_against_size;
		std::shared_ptr<Bonuses::BonusMagicDamageReductionAgainstSize> _magic_damage_reduction_against_size;
		std::shared_ptr<Bonuses::BonusExpPercentPerRace> _exp_percent_per_race;
		std::shared_ptr<Bonuses::BonusJobPercentPerRace> _job_percent_per_race;
		std::shared_ptr<Bonuses::BonusSkillAttack> _skill_attack;
		std::shared_ptr<Bonuses::BonusReduceSPConsumptionOfSkillByPercent> _reduce_sp_consumption_of_skill_by_percent;
		std::shared_ptr<Bonuses::BonusReduceSPConsumptionOfSkill> _reduce_sp_consumption_of_skill;
		std::shared_ptr<Bonuses::BonusLearnedSkillHeal> _learned_skill_heal;
		std::shared_ptr<Bonuses::BonusHealOfSkillCastedOnSelf> _heal_of_skill_casted_on_self;
		std::shared_ptr<Bonuses::BonusSkillKnockback> _skill_knockback;
		std::shared_ptr<Bonuses::BonusSkillCastPercent> _skill_cast_percent;
		std::shared_ptr<Bonuses::BonusSkillCooldown> _skill_cooldown;
		std::shared_ptr<Bonuses::BonusSkillFixCastPercent> _skill_fix_cast_percent;
		std::shared_ptr<Bonuses::BonusSkillVariableCastPercent> _skill_variable_cast_percent;
		std::shared_ptr<Bonuses::BonusResistSkillDamagePercent> _resist_skill_damage_percent;
		std::shared_ptr<Bonuses::BonusIgnoreDefenseFromElement> _ignore_defense_from_element;
		std::shared_ptr<Bonuses::BonusIgnoreDefenseFromRace> _ignore_defense_from_race;
		std::shared_ptr<Bonuses::BonusIgnoreMagicDefenseFromElement> _ignore_magic_defense_from_element;
		std::shared_ptr<Bonuses::BonusIgnoreMagicDefenseFromRace> _ignore_magic_defense_from_race;
		std::shared_ptr<Bonuses::BonusAddEleWeaponDamagePercent> _add_ele_weapon_damage_percent;
		std::shared_ptr<Bonuses::BonusAddEleMagicDamagePercent> _add_ele_magic_damage_percent;
		std::shared_ptr<Bonuses::BonusAutoSpellOnSkill> _auto_spell_on_skill;
		std::shared_ptr<Bonuses::BonusAutoSpellOnAttack> _auto_spell_on_attack;
		std::shared_ptr<Bonuses::BonusAutoSpellOnReceiveDamage> _auto_spell_on_receive_damage;
		std::shared_ptr<Bonuses::BonusAutoSpellOnSelf> _auto_spell_on_self;
		// Bonus3
		std::shared_ptr<Bonuses::BonusHPVanishPercent> _hp_vanish_percent;
		std::shared_ptr<Bonuses::BonusSPVanishPercent> _sp_vanish_percent;
		std::shared_ptr<Bonuses::BonusRaise> _raise;
		std::shared_ptr<Bonuses::BonusAddItemDropOnMonsterKill> _add_item_drop_on_monster_kill;
		std::shared_ptr<Bonuses::BonusHPDrainOnMonsterKill> _hp_drain_on_monster_kill;
		std::shared_ptr<Bonuses::BonusSPDrainOnMonsterKill> _sp_drain_on_monster_kill;
	};

	std::shared_ptr<bonuses> _bonus;
};
}
}
}

#endif /* Status_hpp */
