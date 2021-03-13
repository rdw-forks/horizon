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

#ifndef HORIZON_ZONE_GAME_SKILLDB_HPP
#define HORIZON_ZONE_GAME_SKILLDB_HPP

#include "Core/Multithreading/LockedLookupTable.hpp" // Linux
#include "Server/Common/Definitions/BattleDefinitions.hpp"
#include "Server/Common/Definitions/ItemDefinitions.hpp"
#include "Server/Common/Definitions/SkillDefinitions.hpp"
#include <cstdlib>

#include <sol.hpp>

namespace Horizon
{
namespace Zone
{
struct skill_config_data
{
	uint16_t skill_id{0};
	std::string name, desc;
	int max_level{1};
	int use_range[MAX_SKILL_LEVEL]{0};
	battle_damage_type damage_type[MAX_SKILL_LEVEL]{BDT_NORMAL}; // hittype
	int primary_type{SK_TYPE_PASSIVE}; // skill_primary_type / inf
	int sub_type{SK_SUBTYPE_NONE};   // skill_sub_type / inf2
	battle_attack_type attack_type[MAX_SKILL_LEVEL]{BAT_NONE}; // skill_type
	element_type element[MAX_SKILL_LEVEL]{ELE_NEUTRAL};
	int dmg_property{SK_DMG_PROP_NONE};  // skill_damage_property_type /< nk
	int splash_range[MAX_SKILL_LEVEL]{0};
	int number_of_hits[MAX_SKILL_LEVEL]{0};           ///< num
	bool interrupt_cast[MAX_SKILL_LEVEL]{0};
	int cast_defense_rate[MAX_SKILL_LEVEL]{0};
	int max_skill_instances[MAX_SKILL_LEVEL]{0};
	int knock_back_tiles[MAX_SKILL_LEVEL]{0};                 // blewcount
	int cast_time[MAX_SKILL_LEVEL]{0};                ///< cast
	int after_cast_actor_delay[MAX_SKILL_LEVEL]{0};   ///< delay
	int after_cast_walk_delay[MAX_SKILL_LEVEL]{0};
	int upkeep_time[MAX_SKILL_LEVEL]{0};
	int upkeep_time2[MAX_SKILL_LEVEL]{0};
	int cooldown[MAX_SKILL_LEVEL]{0};
	int fixed_cast_time[MAX_SKILL_LEVEL]{0};
	int cast_time_options{0};
	int skill_delay_options{0};
	int hp_cost[MAX_SKILL_LEVEL]{0};                   // hp
	int sp_cost[MAX_SKILL_LEVEL]{0};                   // sp
	int hp_percent_cost[MAX_SKILL_LEVEL]{0};           // hp_rate_cost
	int sp_percent_cost[MAX_SKILL_LEVEL]{0};           // sp_rate_cost
	int max_hp_trigger[MAX_SKILL_LEVEL]{0};            // mhp
	int max_sp_trigger[MAX_SKILL_LEVEL]{0};            // msp
	int zeny_cost[MAX_SKILL_LEVEL]{0};
	int weapon_type{IT_WT_FIST};                       // item_weapon_type  / weapon
	int ammunition_type{IT_AT_NONE};                   // item_ammunition_type / ammo
	int ammunition_cost[MAX_SKILL_LEVEL]{0};
	int required_state[MAX_SKILL_LEVEL]{0};            // skill_required_state_types
	int spirit_sphere_cost[MAX_SKILL_LEVEL]{0};

	struct skill_required_item_data {
		struct {
			int id;
			int amount[MAX_SKILL_LEVEL];
		} item[MAX_SKILL_ITEM_REQUIRE];
		bool any[MAX_SKILL_LEVEL];
	};

	struct skill_required_item_data req_items;
	struct skill_required_item_data req_equip;

	int placement_id[MAX_SKILL_LEVEL][2]{{0}};
	int placement_layout_type[MAX_SKILL_LEVEL]{0};
	int placement_range[MAX_SKILL_LEVEL]{0};
	int placement_interval[MAX_SKILL_LEVEL]{0};
	int placement_target[MAX_SKILL_LEVEL]{0};
	int placement_flag{0};
};

struct skill_tree_config 
{
	struct requirement {
		int skill_id{0};
		unsigned char level{0};
	};

	int skill_id{0};
	unsigned char max_level{0};
	unsigned char job_level{0};
	job_class_type inherited_from{JOB_INVALID};
	std::vector<struct requirement> requirements;
};

class SkillDatabase
{
public:
	SkillDatabase();
	~SkillDatabase();
	
	static SkillDatabase *get_instance()
	{
		static SkillDatabase instance;
		return &instance;
	}

	bool load();

protected:
	bool load_internal_skill_db(sol::object const &key, sol::object const &value);
	bool load_internal_skill_tree(sol::object const &key, sol::object const &value);

	bool parse_range(sol::table const &table, skill_config_data &data);
	bool parse_hit(sol::table const &table, skill_config_data &data);
	bool parse_skill_type(sol::table const &table, skill_config_data &data);
	bool parse_skill_info(sol::table const &table, skill_config_data &data);
	bool parse_attack_type(sol::table const &table, skill_config_data &data);
	bool parse_element(sol::table const &table, skill_config_data &data);
	bool parse_damage_type(sol::table const &table, skill_config_data &data);
	bool parse_splash_range(sol::table const &table, skill_config_data &data);
	bool parse_number_of_hits(sol::table const &table, skill_config_data &data);
	bool parse_interrupt_cast(sol::table const &table, skill_config_data &data);
	bool parse_cast_defense_rate(sol::table const &table, skill_config_data &data);
	bool parse_max_skill_instances(sol::table const &table, skill_config_data &data);
	bool parse_knock_back_tiles(sol::table const &table, skill_config_data &data);
	bool parse_cast_time(sol::table const &table, skill_config_data &data);
	bool parse_after_cast_act_delay(sol::table const &table, skill_config_data &data);
	bool parse_after_cast_walk_delay(sol::table const &table, skill_config_data &data);
	bool parse_skill_data1(sol::table const &table, skill_config_data &data);
	bool parse_skill_data2(sol::table const &table, skill_config_data &data);
	bool parse_cooldown(sol::table const &table, skill_config_data &data);
	bool parse_fixed_cast_time(sol::table const &table, skill_config_data &data);
	bool parse_cast_time_options(sol::table const &table, skill_config_data &data);
	bool parse_skill_delay_options(sol::table const &table, skill_config_data &data);
	bool parse_requirements(sol::table const &table, skill_config_data &data);

	bool parse_req_hp_cost(sol::table const &table, skill_config_data &data);
	bool parse_req_sp_cost(sol::table const &table, skill_config_data &data);
	bool parse_req_hp_rate_cost(sol::table const &table, skill_config_data &data);
	bool parse_req_sp_rate_cost(sol::table const &table, skill_config_data &data);
	bool parse_req_max_hp_trigger(sol::table const &table, skill_config_data &data);
	bool parse_req_max_sp_trigger(sol::table const &table, skill_config_data &data);
	bool parse_req_zeny_cost(sol::table const &table, skill_config_data &data);
	bool parse_req_weapon_types(sol::table const &table, skill_config_data &data);
	bool parse_req_ammunition_type(sol::table const &table, skill_config_data &data);
	bool parse_req_ammunition_cost(sol::table const &table, skill_config_data &data);
	bool parse_req_state(sol::table const &table, skill_config_data &data);
	bool parse_req_spirit_sphere_cost(sol::table const &table, skill_config_data &data);
	bool parse_req_items(sol::table const &table, skill_config_data &data, bool equips);

	bool parse_placement(sol::table const &table, skill_config_data &data);
	bool parse_placement_id(sol::table const &table, skill_config_data &data);
	bool parse_placement_layout(sol::table const &table, skill_config_data &data);
	bool parse_placement_range(sol::table const &table, skill_config_data &data);
	bool parse_placement_interval(sol::table const &table, skill_config_data &data);
	bool parse_placement_target(sol::table const &table, skill_config_data &data);
	bool parse_placement_flag(sol::table const &table, skill_config_data &data);

	template <typename T>
	void fill_lvl_range(T *setting, T value);

public:
	std::shared_ptr<const skill_config_data> get_skill_by_id(int32_t id) { return _skill_db.at(id); }
	std::shared_ptr<const skill_config_data> get_skill_by_name(std::string name) 
	{
		std::map<uint32_t, std::shared_ptr<const skill_config_data>> s_db = _skill_db.get_map();
		for (auto const &sk : s_db) {
			if (sk.second->name.compare(name) == 0)
				return sk.second;
		}
		
		return nullptr;
	}

	std::vector<std::shared_ptr<const skill_tree_config>> get_skill_tree_by_job_id(job_class_type job_id) 
	{
		return _skill_tree_db.at(job_id, std::vector<std::shared_ptr<const skill_tree_config>>()); 
	}

private:
	LockedLookupTable<uint32_t, std::shared_ptr<const skill_config_data>> _skill_db;
	LockedLookupTable<job_class_type, std::vector<std::shared_ptr<const skill_tree_config>>> _skill_tree_db;
};
}
}

template <typename T>
void Horizon::Zone::SkillDatabase::fill_lvl_range(T *setting, T value)
{
	for (int i = 0; i < MAX_SKILL_LEVEL; i++)
		setting[i] = value;
}

#define SkillDB Horizon::Zone::SkillDatabase::get_instance()

#endif /* HORIZON_ZONE_GAME_SKILLDB_HPP */
