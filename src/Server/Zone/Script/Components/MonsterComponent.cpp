/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
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

#include "MonsterComponent.hpp"

#include "Server/Common/Configuration/Horizon.hpp"
#include "Server/Zone/Game/Units/Mob/Hostile/Monster.hpp"
#include "Server/Zone/Game/Map/Map.hpp"
#include "Server/Zone/Game/StaticDB/MonsterDB.hpp"
#include "Server/Zone/Zone.hpp"

using namespace Horizon::Zone;
using namespace Horizon::Zone::Units;

void MonsterComponent::sync_definitions(std::shared_ptr<sol::state> state)
{
	sol::table tbl_1 = state->create_named_table("MonsterRace");
	tbl_1["Formless"] = (int) MONSTER_RACE_FORMLESS; 
	tbl_1["Undead"] = (int) MONSTER_RACE_UNDEAD; 
	tbl_1["Brute"] = (int) MONSTER_RACE_BRUTE; 
	tbl_1["Plant"] = (int) MONSTER_RACE_PLANT; 
	tbl_1["Insect"] = (int) MONSTER_RACE_INSECT; 
	tbl_1["Fish"] = (int) MONSTER_RACE_FISH; 
	tbl_1["Demon"] = (int) MONSTER_RACE_DEMON; 
	tbl_1["DemiHuman"] = (int) MONSTER_RACE_DEMIHUMAN; 
	tbl_1["Angel"] = (int) MONSTER_RACE_ANGEL; 
	tbl_1["Dragon"] = (int) MONSTER_RACE_DRAGON; 
	tbl_1["Player"] = (int) MONSTER_RACE_PLAYER; 
	tbl_1["Boss"] = (int) MONSTER_RACE_BOSS; 
	tbl_1["NonBoss"] = (int) MONSTER_RACE_NONBOSS;

	sol::table tbl_2 = state->create_named_table("MonsterMode");
	tbl_2["None"] = (int) MONSTER_MODE_MASK_NONE; 
	tbl_2["CanMove"] = (int) MONSTER_MODE_MASK_CANMOVE; 
	tbl_2["Looter"] = (int) MONSTER_MODE_MASK_LOOTER; 
	tbl_2["Aggressive"] = (int) MONSTER_MODE_MASK_AGGRESSIVE; 
	tbl_2["Assist"] = (int) MONSTER_MODE_MASK_ASSIST; 
	tbl_2["CastSensorIdle"] = (int) MONSTER_MODE_MASK_CASTSENSOR_IDLE; 
	tbl_2["Boss"] = (int) MONSTER_MODE_MASK_BOSS; 
	tbl_2["Plant"] = (int) MONSTER_MODE_MASK_PLANT; 
	tbl_2["CanAttack"] = (int) MONSTER_MODE_MASK_CANATTACK; 
	tbl_2["Detector"] = (int) MONSTER_MODE_MASK_DETECTOR; 
	tbl_2["CastSensorChase"] = (int) MONSTER_MODE_MASK_CASTSENSOR_CHASE; 
	tbl_2["ChangeChase"] = (int) MONSTER_MODE_MASK_CHANGECHASE; 
	tbl_2["Angry"] = (int) MONSTER_MODE_MASK_ANGRY; 
	tbl_2["ChangeTargetMelee"] = (int) MONSTER_MODE_MASK_CHANGETARGET_MELEE; 
	tbl_2["ChangeTargetChase"] = (int) MONSTER_MODE_MASK_CHANGETARGET_CHASE; 
	tbl_2["TargetWeak"] = (int) MONSTER_MODE_MASK_TARGETWEAK; 
	tbl_2["NoKnockBack"] = (int) MONSTER_MODE_MASK_NOKNOCKBACK;

	sol::table tbl_3 = state->create_named_table("MonsterSkillState");
	tbl_3["Any"] = (int) MONSTER_SKILL_STATE_ANY; 
	tbl_3["Idle"] = (int) MONSTER_SKILL_STATE_IDLE; 
	tbl_3["Walk"] = (int) MONSTER_SKILL_STATE_WALK; 
	tbl_3["Loot"] = (int) MONSTER_SKILL_STATE_LOOT; 
	tbl_3["Dead"] = (int) MONSTER_SKILL_STATE_DEAD; 
	tbl_3["Berserk"] = (int) MONSTER_SKILL_STATE_BERSERK;  //Aggressive mob attacking
	tbl_3["Angry"] = (int) MONSTER_SKILL_STATE_ANGRY;    //Mob retaliating from being attacked.
	tbl_3["Rush"] = (int) MONSTER_SKILL_STATE_RUSH;     //Mob following a player after being attacked.
	tbl_3["Follow"] = (int) MONSTER_SKILL_STATE_FOLLOW;   //Mob following a player without being attacked.
	tbl_3["AnyTarget"] = (int) MONSTER_SKILL_STATE_ANYTARGET;

	sol::table tbl_4 = state->create_named_table("MonsterSkillTarget");
	tbl_4["CurrentTarget"] = (int) MONSTER_SKILL_TARGET_CURRENT; 
	tbl_4["Random"] = (int) MONSTER_SKILL_TARGET_RANDOM; 
	tbl_4["Self"] = (int) MONSTER_SKILL_TARGET_SELF; 
	tbl_4["Friend"] = (int) MONSTER_SKILL_TARGET_FRIEND; 
	tbl_4["Master"] = (int) MONSTER_SKILL_TARGET_MASTER; 
	tbl_4["Around5"] = (int) MONSTER_SKILL_TARGET_AROUND5; 
	tbl_4["Around6"] = (int) MONSTER_SKILL_TARGET_AROUND6; 
	tbl_4["Around7"] = (int) MONSTER_SKILL_TARGET_AROUND7; 
	tbl_4["Around8"] = (int) MONSTER_SKILL_TARGET_AROUND8; 
	tbl_4["Around1"] = (int) MONSTER_SKILL_TARGET_AROUND1; 
	tbl_4["Around2"] = (int) MONSTER_SKILL_TARGET_AROUND2; 
	tbl_4["Around3"] = (int) MONSTER_SKILL_TARGET_AROUND3; 
	tbl_4["Around4"] = (int) MONSTER_SKILL_TARGET_AROUND4; 
	tbl_4["Around"] = (int) MONSTER_SKILL_TARGET_AROUND;

	sol::table tbl_5 = state->create_named_table("MonsterSkillCastCondition");
	tbl_5["Always"] = (int) MONSTER_SKILL_CC_ALWAYS; 
	tbl_5["MyHpLtMaxRate"] = (int) MONSTER_SKILL_CC_MYHPLTMAXRATE; 
	tbl_5["MyHpInRate"] = (int) MONSTER_SKILL_CC_MYHPINRATE; 
	tbl_5["FriendHpLtMaxRate"] = (int) MONSTER_SKILL_CC_FRIENDHPLTMAXRATE; 
	tbl_5["FriendHpInRate"] = (int) MONSTER_SKILL_CC_FRIENDHPINRATE; 
	tbl_5["MyStatusOn"] = (int) MONSTER_SKILL_CC_MYSTATUSON; 
	tbl_5["MyStatusOff"] = (int) MONSTER_SKILL_CC_MYSTATUSOFF; 
	tbl_5["FriendStatusOn"] = (int) MONSTER_SKILL_CC_FRIENDSTATUSON; 
	tbl_5["FriendStatusOff"] = (int) MONSTER_SKILL_CC_FRIENDSTATUSOFF; 
	tbl_5["AttackPCGT"] = (int) MONSTER_SKILL_CC_ATTACKPCGT; 
	tbl_5["AttackPCGE"] = (int) MONSTER_SKILL_CC_ATTACKPCGE; 
	tbl_5["SlaveLT"] = (int) MONSTER_SKILL_CC_SLAVELT; 
	tbl_5["SlaveLE"] = (int) MONSTER_SKILL_CC_SLAVELE; 
	tbl_5["CloseRangeAttacked"] = (int) MONSTER_SKILL_CC_CLOSERANGEATTACKED; 
	tbl_5["LongRangeAttacked"] = (int) MONSTER_SKILL_CC_LONGRANGEATTACKED; 
	tbl_5["AfterSkill"] = (int) MONSTER_SKILL_CC_AFTERSKILL; 
	tbl_5["SkillUsed"] = (int) MONSTER_SKILL_CC_SKILLUSED; 
	tbl_5["CastTargeted"] = (int) MONSTER_SKILL_CC_CASTTARGETED; 
	tbl_5["RudeAttacked"] = (int) MONSTER_SKILL_CC_RUDEATTACKED; 
	tbl_5["MasterHPLTMaxRate"] = (int) MONSTER_SKILL_CC_MASTERHPLTMAXRATE; 
	tbl_5["MasterAttacked"] = (int) MONSTER_SKILL_CC_MASTERATTACKED; 
	tbl_5["Alchemist"] = (int) MONSTER_SKILL_CC_ALCHEMIST; 
	tbl_5["Spawn"] = (int) MONSTER_SKILL_CC_SPAWN; 
	tbl_5["MagicAttacked"] = (int) MONSTER_SKILL_CC_MAGICATTACKED;
}

void MonsterComponent::sync_data_types(std::shared_ptr<sol::state> state)
{
	sol::usertype<Monster> config_1 = state->new_usertype<Monster>("Monster");
	config_1["unit"] = [](std::shared_ptr<Horizon::Zone::Units::Monster> monster) { return monster->shared_from_this(); };
	config_1["stop_movement"] = &Monster::stop_movement;
	config_1["on_pathfinding_failure"] = &Monster::on_pathfinding_failure;
	config_1["on_movement_begin"] = &Monster::on_movement_begin;
	config_1["on_movement_step"] = &Monster::on_movement_step;
	config_1["on_movement_end"] = &Monster::on_movement_end;
	config_1["set_spotted"] = &Monster::set_spotted,
	config_1["was_spotted_once"] = &Monster::was_spotted_once;
	config_1["on_status_effect_start"] = &Monster::on_status_effect_start;
	config_1["on_status_effect_end"] = &Monster::on_status_effect_end;
	config_1["on_status_effect_change"] = &Monster::on_status_effect_change;
	config_1["set_next_walk_time"] = &Monster::set_next_walk_time;
	config_1["next_walk_time"] = &Monster::next_walk_time;
	config_1["on_damage_received"] = &Monster::on_damage_received;
}

void MonsterComponent::sync_functions(std::shared_ptr<sol::state> state, std::shared_ptr<MapContainerThread> container)
{
	state->set_function("cast_unit_to_monster",
					[] (std::shared_ptr<Unit> e)
					{
						return e->template downcast<Monster>();
					});

	// Monster Spawn Script Function
	state->set_function("Monster",
		[this, container] (std::string const &map_name, uint16_t x, uint16_t y, uint16_t x_area, uint16_t y_area, std::string const &name, uint16_t monster_id, uint16_t amount, uint16_t spawn_delay_base, uint16_t spawn_delay_variance) 
		{
			if (container == nullptr)
				return;
			
			std::shared_ptr<Map> map;

			MAP_CONTAINER_THREAD_ASSERT_MAP(map, container, map_name);

			HLog(info) << "Monster spawn set (" << name << ") in " << map_name << " at (" << x << "," << y << ")[" << x_area << "," << y_area << "]" " for a total of " << amount << " monsters is initializing...";

			monster_spawn_data spwd;

			spwd.spawn_dataset_id = _last_monster_spawn_id++;
			spwd.map_name = map_name;
			spwd.x = x;
			spwd.y = y;
			spwd.x_area = x_area;
			spwd.y_area = y_area;
			spwd.mob_name = name;
			spwd.monster_id = monster_id;
			spwd.amount = amount;
			spwd.spawn_delay_base = spawn_delay_base;
			spwd.spawn_delay_variance = spawn_delay_variance;

			register_monster_spawn_info(spwd.spawn_dataset_id, std::make_shared<monster_spawn_data>(spwd));
		});
}

void MonsterComponent::deregister_single_spawned_monster(uint64_t uuid) {
	for (auto i = _monster_spawned_map.begin(); i != _monster_spawned_map.end(); i++)
		if ((*i).second->uuid() == uuid) {
			reschedule_single_monster_spawn((*i).second);
			(*i).second->finalize();
			// Remove the unit from the containers.
			std::shared_ptr<MapContainerThread> container = (*i).second->map()->container();
			container->remove_unit((*i).second);
			_monster_spawned_map.erase(i);
			return;
		}
}

void MonsterComponent::reschedule_single_monster_spawn(std::shared_ptr<Horizon::Zone::Units::Monster> monster) 
{
	uint8_t type = 0;
	uint32_t guid = 0;
	uint16_t spawn_dataset_id = 0;
	uint8_t spawn_id = 0;

	sZone->from_uuid(monster->uuid(), type, guid, spawn_dataset_id, spawn_id);

	std::shared_ptr<monster_spawn_data> msd = get_monster_spawn_info(spawn_dataset_id);
	std::shared_ptr<Map> map = monster->map();

	msd->dead_amount++;
	// Set the spawn time cache. This is used to calculate the time to spawn the monster.
	monster_spawn_data::s_monster_spawn_time_cache spawn_time_cache;
	spawn_time_cache.dead_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

	spawn_time_cache.spawn_time = msd->spawn_delay_base + std::rand() % (msd->spawn_delay_variance + 1);
	msd->dead_spawn_time_list.emplace(monster->uuid(), spawn_time_cache);

	get_container()->getScheduler().Schedule(
		Milliseconds(spawn_time_cache.spawn_time), 
		monster->get_scheduler_task_id(UNIT_SCHEDULE_MONSTER_RESPAWN),
		[this, monster, map, msd](TaskContext /*&context*/) {
			if (map->get_user_count() == 0)
				return;

			this->spawn_monster(map, msd->spawn_dataset_id, msd->monster_id, 1, msd->x, msd->y, msd->x_area, msd->y_area);
			msd->dead_spawn_time_list.erase(monster->uuid());
			msd->dead_amount--;
		});
}

void MonsterComponent::spawn_monsters(std::string map_name, std::shared_ptr<MapContainerThread> container)
{
	if (container == nullptr)
		return;
	
	std::shared_ptr<Map> map;
	
	MAP_CONTAINER_THREAD_ASSERT_MAP(map, container, map_name);

	for (auto i = _monster_spawn_db.begin(); i != _monster_spawn_db.end(); i++) {
		std::shared_ptr<monster_spawn_data> msd = (*i).second;
		if (map_name.compare(msd->map_name) == 0) {
			if (msd->dead_amount > 0) {
				for (auto dead_it = msd->dead_spawn_time_list.begin(); dead_it != msd->dead_spawn_time_list.end();) {
					int64_t dead_monster_spawn_uuid = dead_it->first;
					monster_spawn_data::s_monster_spawn_time_cache dead_stc = dead_it->second;
					
					uint8_t type = 0;
					uint32_t guid = 0;
					uint16_t spawn_dataset_id = 0;
					uint8_t spawn_id = 0;

					sZone->from_uuid(dead_monster_spawn_uuid, type, guid, spawn_dataset_id, spawn_id);

					int64_t since_death_ms = (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() - dead_stc.dead_time);

					int64_t time_to_spawn_ms = dead_stc.spawn_time - since_death_ms;

					if (time_to_spawn_ms < 0)
						time_to_spawn_ms = 0;

					map->container()->getScheduler().Schedule(
						Milliseconds(time_to_spawn_ms),
						((uint64_t) guid << 32) + (int) UNIT_SCHEDULE_MONSTER_RESPAWN,
						[this, map, msd](TaskContext /*&context*/) {
							if (map->get_user_count() == 0)
								return;
							this->spawn_monster(map, msd->spawn_dataset_id, msd->monster_id, 1, msd->x, msd->y, msd->x_area, msd->y_area);
						});

					dead_it = msd->dead_spawn_time_list.erase(dead_it);
					msd->dead_amount--;
				}
			}

			spawn_monster(map, msd->spawn_dataset_id, msd->monster_id, msd->amount - msd->dead_amount, msd->x, msd->y, msd->x_area, msd->y_area);
		}
	}
}

void MonsterComponent::spawn_monster(std::shared_ptr<Map> map, int spawn_dataset_id, int monster_id, int16_t amount, int16_t x, int16_t y, int16_t x_area, int16_t y_area)
{
	std::shared_ptr<const monster_config_data> md = MonsterDB->get_monster_by_id(monster_id);
	
	if (md == nullptr) {
		HLog(warning) << "Monster " << monster_id << " set for spawn in " << map->get_name() << " does not exist in the database.";
		return;
	}

	std::shared_ptr<std::vector<std::shared_ptr<const monster_skill_config_data>>> mskd = MonsterDB->get_monster_skill_by_id(monster_id);
	
	for (int i = 0; i < amount; i++) {
		MapCoords mcoords = MapCoords(x, y);
		if (mcoords == MapCoords(0, 0))
			mcoords = map->get_random_accessible_coordinates();
		else if (x_area && y_area) {
			if ((mcoords = map->get_random_coordinates_in_walkable_area(x, y, x_area, y_area)) == MapCoords(0, 0)) {
				HLog(warning) << "Couldn't spawn monster " << md->name << " in area, spawning it on random co-ordinates.";
				mcoords = map->get_random_accessible_coordinates();
			}
		}
		std::shared_ptr<Monster> monster = std::make_shared<Monster>(spawn_dataset_id, i, map, mcoords, md, mskd);
		
		monster->initialize();
		get_container()->add_unit(monster);
		register_single_spawned_monster(monster->uuid(), monster);
	}

	return;
}

void MonsterComponent::despawn_monsters(std::string map_name, std::shared_ptr<MapContainerThread> container)
{
	if (container == nullptr)
		return;
	
	std::shared_ptr<Map> map;
	
	MAP_CONTAINER_THREAD_ASSERT_MAP(map, container, map_name);

	for (auto i = _monster_spawned_map.begin(); i != _monster_spawned_map.end();)
		if ((*i).second->map()->get_name() == map_name) {
			(*i).second->finalize();
			container->remove_unit((*i).second);
			i = _monster_spawned_map.erase(i);
		}
}