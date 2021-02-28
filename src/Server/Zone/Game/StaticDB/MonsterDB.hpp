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

#ifndef HORIZON_ZONE_STATICDB_MONSTERDB_HPP
#define HORIZON_ZONE_STATICDB_MONSTERDB_HPP

#include "Server/Common/Definitions/EntityDefinitions.hpp"
#include "Server/Common/Definitions/MonsterDefinitions.hpp"

#include <sol.hpp>

namespace Horizon
{
namespace Zone
{
struct monster_skill_config_data {
	uint16_t skill_id{0};
	uint16_t skill_level{0};
	int16_t skill_invoke_rate{0};
	int cast_time{0};
	int delay{0};
	bool cancelable{0};
	int16_t cast_condition{0};
	int32_t condition_data{0};
	int val[5]{0};
	int16_t emotion_id{0};
	uint16_t msg_id{0};
	enum monster_skill_target_type target{MONSTER_SKILL_TARGET_CURRENT};
	enum monster_skill_state_type state{MONSTER_SKILL_STATE_ANY};
};

struct monster_config_data
{
	uint16_t monster_id{0};
	char sprite_name[MAX_UNIT_NAME_LENGTH]{0};
	char name[MAX_UNIT_NAME_LENGTH]{0};
	char alt_name[MAX_UNIT_NAME_LENGTH]{0};

	uint16_t level{1};
	int32_t hp{0};
	int32_t sp{0};
	int32_t attack_range{0};
	int32_t attack_damage[2]{0};
	int32_t defense{0};
	int32_t magic_defense{0};

	struct {
		int16_t str{0};
		int16_t agi{0};
		int16_t vit{0};
		int16_t int_{0};
		int16_t dex{0};
		int16_t luk{0};
	} stats;

	short view_range{1};
	short chase_range{1};
	entity_size_type size{ESZ_MEDIUM};
	monster_primary_race_type race{MONSTER_RACE_FORMLESS};
	element_type element{ELE_NEUTRAL};
	int8_t element_level{0};
	int32_t mode{0};
	int32_t move_speed{0};
	int32_t attack_delay{0};
	int32_t attack_motion{0};
	int32_t damage_motion{0};
	int32_t damage_taken_rate{100};

	struct monster_view_data {
		int32_t sprite_id{0};
		int32_t weapon_id{0};
		int32_t shield_id{0};
		int32_t robe_id{0};
		int32_t headgear_top_id{0};
		int32_t headgear_middle_id{0};
		int32_t headgear_bottom_id{0};
		int32_t hair_style_id{0};
		int32_t body_style_id{0};
		int32_t hair_color_id{0};
		int32_t body_color_id{0};
		entity_gender_types gender{ENTITY_GENDER_FEMALE};
	} view{0};
	//struct view_data vd;
	unsigned int option;
	//struct mob_skill skill[MAX_MOBSKILL];
	//struct spawn_info spawn[10];
	struct rewards
	{
		struct drops { int item_id{0}, chance{0}; };

		unsigned int base_exp{0}, job_exp{0};
		unsigned int mvp_exp{0};
		struct drops items[MAX_MOB_DROP]{0};
		struct drops items_mvp[MAX_MVP_DROP]{0};
	} rewards;
};

class MonsterDatabase
{
public:
	MonsterDatabase();
	~MonsterDatabase();
	
	static MonsterDatabase *get_instance()
	{
		static MonsterDatabase instance;
		return &instance;
	}
	
	bool load();

protected:
	bool load_internal(sol::object const &key, sol::object const &value);

	bool parse_level(sol::table const &table, monster_config_data &data);
	bool parse_hp(sol::table const &table, monster_config_data &data);
	bool parse_sp(sol::table const &table, monster_config_data &data);
	bool parse_reward_base_exp(sol::table const &table, monster_config_data &data);
	bool parse_reward_job_exp(sol::table const &table, monster_config_data &data);
	bool parse_attack_range(sol::table const &table, monster_config_data &data);
	bool parse_attack(sol::table const &table, monster_config_data &data);
	bool parse_defense(sol::table const &table, monster_config_data &data);
	bool parse_magic_defense(sol::table const &table, monster_config_data &data);
	bool parse_view_range(sol::table const &table, monster_config_data &data);
	bool parse_chase_range(sol::table const &table, monster_config_data &data);
	bool parse_size(sol::table const &table, monster_config_data &data);
	bool parse_race(sol::table const &table, monster_config_data &data);
	bool parse_element(sol::table const &table, monster_config_data &data);
	bool parse_mode(sol::table const &table, monster_config_data &data);
	bool parse_move_speed(sol::table const &table, monster_config_data &data);
	bool parse_attack_delay(sol::table const &table, monster_config_data &data);
	bool parse_attack_motion(sol::table const &table, monster_config_data &data);
	bool parse_damage_motion(sol::table const &table, monster_config_data &data);
	bool parse_mvp_exp(sol::table const &table, monster_config_data &data);
	bool parse_damage_taken_rate(sol::table const &table, monster_config_data &data);

	bool parse_stats(sol::table const &table, monster_config_data &data);
	bool parse_drops(sol::table const &table, monster_config_data &data, bool mvp);
	bool parse_view(sol::table const &table, monster_config_data &data);


	bool load_skill_internal(sol::object const &key, sol::object const &value);

public:
	std::shared_ptr<const monster_config_data> get_monster_by_id(uint32_t id) { return _monster_db.at(id, nullptr); }
	std::shared_ptr<const monster_config_data> get_monster_by_name(std::string name) 
	{
		std::map<uint32_t, std::shared_ptr<const monster_config_data>> db = _monster_db.get_map();
		
		for (auto it = db.begin(); it != db.end(); it++) {
			std::shared_ptr<const monster_config_data> m = it->second;
			if (std::strncmp(m->sprite_name, name.c_str(), MAX_UNIT_NAME_LENGTH) == 0)
				return m;
		}
		
		return nullptr;
	}

private:
	LockedLookupTable<uint32_t, std::shared_ptr<const monster_config_data>> _monster_db;
	LockedLookupTable<uint32_t, std::vector<std::shared_ptr<const monster_skill_config_data>>> _monster_skill_db;
};
}
}

#define MonsterDB Horizon::Zone::MonsterDatabase::get_instance()

#endif /* HORIZON_ZONE_STATICDB_MONSTERDB_HPP */
