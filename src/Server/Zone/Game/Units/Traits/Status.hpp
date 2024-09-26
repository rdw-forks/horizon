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
};
}
}
}

#endif /* Status_hpp */
