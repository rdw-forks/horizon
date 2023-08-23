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

#ifndef HORIZON_ZONE_GAME_ENTITY_HPP
#define HORIZON_ZONE_GAME_ENTITY_HPP

#include "Server/Common/Configuration/Horizon.hpp"
#include "Server/Zone/Definitions/EntityDefinitions.hpp"
#include "Server/Zone/Definitions/ClientDefinitions.hpp"
#include "Server/Zone/Definitions/SkillDefinitions.hpp"
#include "Server/Zone/Definitions/StatusEffectDefinitions.hpp"
#include "Server/Zone/Game/Map/Grid/GridDefinitions.hpp"
#include "Server/Zone/Game/Map/Coordinates.hpp"
#include "Server/Zone/Game/Map/Map.hpp"
#include "Server/Zone/Game/SkillSystem/SkillExecution.hpp"
#include "Server/Zone/LUA/LUAManager.hpp"
#include "Utility/TaskScheduler.hpp"

#define MIN_RANDOM_TRAVEL_TIME 4000
#define MOB_LAZY_MOVE_RATE 1000
#define MOB_MIN_THINK_TIME 100
#define MOB_MIN_THINK_TIME_LAZY (MOB_MIN_THINK_TIME * 10)

enum entity_task_schedule_group
{
	ENTITY_SCHEDULE_WALK       = 1,
	ENTITY_SCHEDULE_SAVE       = 2,
	ENTITY_SCHEDULE_AI_THINK   = 3,
	ENTITY_SCHEDULE_AI_WALK    = 4,
	ENTITY_SCHEDULE_STATUS_EFFECT_CLEAR = 5,
	ENTITY_SCHEDULE_AI_ACTIVE  = 6,
	ENTITY_SCHEDULE_ATTACK     = 7,
	ENTITY_SCHEDULE_SKILL_CAST = 8
};

enum entity_walk_state
{
	ENTITY_WALK_STOPPED = 0,
	ENTITY_WALK_MOVING = 1
};

#define ENTITY_STATUS_EFFECT_CHECK_TIME 1000

struct s_grid_sc_apply_in_skill_area_config;
struct s_grid_apply_in_area_config;
struct s_entity_skill_use_notifier_config;
struct s_grid_entity_basic_attack_config;

namespace Horizon
{
namespace Zone
{
	namespace Traits
	{
		class Status;
	}
class Map;
class Combat;
class CombatRegistry;
static int32_t _last_np_entity_guid = NPC_START_GUID;

class Entity : public std::enable_shared_from_this<Entity>
{
public:
	Entity(uint32_t guid, entity_type type, entity_type_mask type_mask, std::shared_ptr<Map> map, MapCoords map_coords);
	Entity(uint32_t guid, entity_type type, entity_type_mask type_mask);
	virtual ~Entity();

	bool initialize();
	virtual bool finalize();

	bool is_initialized() const { return _is_initialized; }
	bool is_finalized() const { return _is_finalized; }
	void set_finalized(bool finalized) { _is_finalized = finalized; }

	/**
	 * Movement
	 */
	MapCoords const &dest_coords() const { return _dest_pos; }
	virtual bool walk_to_coordinates(int16_t x, int16_t y);
	virtual bool walk_to_entity(std::shared_ptr<Entity> entity);
	bool is_walking() const { return (dest_coords() != MapCoords(0, 0)) || ((_changed_dest_pos) != MapCoords(0, 0)); }

	virtual void stop_movement() = 0;
	
	bool stop_walking(bool cancel = false, bool notify = false);

protected:
	bool schedule_walk();
	void walk();
	
	virtual void on_pathfinding_failure() = 0;
	virtual void on_movement_begin() = 0;
	virtual void on_movement_step() = 0;
	virtual void on_movement_end() = 0;

	/**
	 * Unit Data
	 */
public:
	uint32_t guid() const { return _guid; }
	void set_guid(uint32_t guid) { _guid = guid; }

	uint16_t job_id() const { return _job_id; }
	void set_job_id(uint16_t job_id) { _job_id = job_id; }

	entity_posture_type posture() const { return _posture; }
	void set_posture(entity_posture_type posture) { _posture = posture; }

	const std::string &name() const { return _name; }
	void set_name(const std::string &name) { _name = name; }

	directions direction() const { return _facing_dir; }
	void set_direction(directions dir) { _facing_dir = dir; }

	std::shared_ptr<Horizon::Zone::Traits::Status> status() { return _status; }
	void set_status(std::shared_ptr<Horizon::Zone::Traits::Status> st) { _status = st; }

	void force_movement_stop_internal(bool stop = false) { _jump_walk_stop = stop; }
	/**
	 * Map & Map Container
	 */
	std::shared_ptr<Map> map() { return _map.expired() ? nullptr : _map.lock(); }
	void set_map(std::shared_ptr<Map> map) { _map = map; }

	AStar::CoordinateList get_walk_path() { return _walk_path; }

	/**
	 * Entity applications
	 */
	entity_type type() const { return _type; }
	entity_type_mask type_mask() const { return _type_mask; }
	bool is_of_type(int type_mask) { return !((type_mask & (int) _type_mask) == 0); }

	template <class T>
	std::shared_ptr<T> downcast()
	{
		return std::dynamic_pointer_cast<T>(shared_from_this());
	}

	/**
	 * Grid applications.
	 */
	MapCoords const &map_coords() const { return _map_coords; }
	void set_map_coords(MapCoords const &coords) { _map_coords = coords; }

	GridCoords const &grid_coords() const { return _grid_coords; }
	void set_grid_coords(GridCoords const &coords) { _grid_coords = coords; }

	bool is_in_range_of(std::shared_ptr<Entity> entity, uint8_t range = MAX_VIEW_RANGE);
	void notify_nearby_players_of_existence(entity_viewport_notification_type notif_type);
	void notify_nearby_players_of_spawn();
	void notify_nearby_players_of_movement(bool new_entry = false);
	void notify_nearby_players_of_movement_stop(MapCoords stop_coords);
	void notify_nearby_players_of_skill_use(grid_entity_skill_use_notification_type notification_type, s_entity_skill_use_notifier_config config);
	void notify_nearby_players_of_basic_attack(s_grid_entity_basic_attack_config config);

	// Essentials
	std::shared_ptr<Entity> get_nearby_entity(uint32_t guid);
	uint64_t get_scheduler_task_id(entity_task_schedule_group group) { return ((uint64_t) guid() << 32) + (int) group; }
	std::map<int16_t, std::shared_ptr<status_change_entry>> &get_status_effects() { return _status_effects; }
	
	// Skills
	void apply_status_change_in_area(std::shared_ptr<Entity> target, s_grid_sc_apply_in_skill_area_config const &config, s_grid_apply_in_area_config const &aoe_config);
	void remove_status_change_in_area(std::shared_ptr<Entity> target, int sc_type, s_grid_apply_in_area_config const &aoe_config);
	void execute_skill_in_area(std::shared_ptr<Entity> target, std::shared_ptr<SkillExecution> skill_execution, s_grid_apply_in_area_config const &aoe_config);
	void execute_skill_in_cell(std::shared_ptr<Entity> target, MapCoords cell, std::shared_ptr<SkillExecution> skill_execution, s_grid_apply_in_area_config const &aoe_config);
	
	void use_skill_on_target(int16_t skill_lv, int16_t skill_id, int target_guid);
	void use_skill_on_ground(int16_t skill_lv, int16_t skill_id, int16_t pos_x, int16_t pos_y);
	void use_skill_on_ground(int16_t skill_lv, int16_t skill_id, int16_t pos_x, int16_t pos_y, std::string contents);

	/**
	 * Status Effects
	 */
	bool status_effect_start(int type, int total_time, int val1, int val2, int val3, int val4);
	bool status_effect_end(int type);

	virtual void on_status_effect_start(std::shared_ptr<status_change_entry> sce) = 0;
	virtual void on_status_effect_end(std::shared_ptr<status_change_entry> sce) = 0;
	virtual void on_status_effect_change(std::shared_ptr<status_change_entry> sce) = 0;

	std::shared_ptr<AStar::CoordinateList> path_to(std::shared_ptr<Entity> e);
	int distance_from(std::shared_ptr<Entity> e) { return path_to(e)->size(); }

	virtual bool attack(std::shared_ptr<Entity> target, bool continuous = false);
	virtual bool stop_attacking();

	void set_attacking(bool attacking) { _is_attacking = attacking; }
	bool is_attacking() { return _is_attacking; }
	void on_attack_end();

	bool is_dead();

	virtual void on_damage_received(std::shared_ptr<Entity> damage_dealer, int damage);
	virtual void on_killed(std::shared_ptr<Entity> killer, bool with_drops = false, bool with_exp = false);

	/**
	 * Combat
	 */
	std::shared_ptr<Combat> combat() { return _combat; }
	void set_combat(std::shared_ptr<Combat> combat)
	{
		_combat = combat;
	}

	/**
	 * Extremely time-sensitive functions
	 */
	void update(uint64_t tick);

	std::shared_ptr<CombatRegistry> combat_registry() { return _combat_registry; }
	
private:
	bool _is_initialized{false}, _jump_walk_stop{false}, _is_finalized{ false };
	bool _is_attacking{false};
	uint32_t _guid{0};
	entity_type _type{ENTITY_UNKNOWN};
	entity_type_mask _type_mask{ENTITY_MASK_UNKNOWN};
	std::weak_ptr<Map> _map;
	MapCoords _map_coords{0, 0};
	GridCoords _grid_coords{0, 0};

	MapCoords _changed_dest_pos{0, 0}, _dest_pos{0, 0};
	AStar::CoordinateList _walk_path;
    int16_t _walk_path_index{0};

	std::shared_ptr<Horizon::Zone::Traits::Status> _status;

	// General Data
	std::string _name{""};
	uint16_t _job_id{0};
	entity_posture_type _posture{POSTURE_STANDING};
	directions _facing_dir{DIR_SOUTH};

	std::map<int16_t, std::shared_ptr<status_change_entry>> _status_effects;

	int32_t _attackable_time{0};

	// Combat data
	std::shared_ptr<Combat> _combat;
    std::shared_ptr<CombatRegistry> _combat_registry;
};
}
}

#endif /* HORIZON_ZONE_GAME_ENTITY_HPP */
