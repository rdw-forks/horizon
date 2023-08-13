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

#ifndef HORIZON_ZONE_GAME_MAP_GRIDNOTIFIERS_HPP
#define HORIZON_ZONE_GAME_MAP_GRIDNOTIFIERS_HPP

#include "Libraries/Networking/Buffer/ByteBuffer.hpp"
#include "Server/Zone/Definitions/EntityDefinitions.hpp"
#include "Server/Zone/Definitions/ClientDefinitions.hpp"
#include "Server/Zone/Game/Map/Grid/Notifiers/GridNotifierPredicates.hpp"
#include "Server/Zone/Game/SkillSystem/SkillExecution.hpp"

#define entity_ns(class) Horizon::Zone::Entities::class
struct GridViewPortUpdater
{
	std::weak_ptr<Horizon::Zone::Entity> _entity;

	explicit GridViewPortUpdater(const std::shared_ptr<Horizon::Zone::Entity>& entity) : _entity(entity) { }

	template <class T>
	void update(GridRefManager<T> &m);

	void Visit(GridRefManager<entity_ns(Player)> &m);
	void Visit(GridRefManager<entity_ns(NPC)> &m);
	void Visit(GridRefManager<entity_ns(Elemental)> &m);
	void Visit(GridRefManager<entity_ns(Homunculus)> &m);
	void Visit(GridRefManager<entity_ns(Mercenary)> &m);
	void Visit(GridRefManager<entity_ns(Pet)> &m);
	void Visit(GridRefManager<entity_ns(Monster)> &m);
	void Visit(GridRefManager<entity_ns(Skill)> &m);

	template<class NOT_INTERESTED>
	void Visit(GridRefManager<NOT_INTERESTED> &) { }
};

struct GridEntityExistenceNotifier
{
	std::weak_ptr<Horizon::Zone::Entity> _entity;
	entity_viewport_notification_type _notif_type;

	explicit GridEntityExistenceNotifier(const std::shared_ptr<Horizon::Zone::Entity>& entity, entity_viewport_notification_type notif_type)
	: _entity(entity), _notif_type(notif_type)
	{ }

	template <class T>
	void notify(GridRefManager<T> &m);

	void Visit(GridRefManager<entity_ns(Player)> &m);

	template<class NOT_INTERESTED>
	void Visit(GridRefManager<NOT_INTERESTED> &) { }
};

struct GridEntitySpawnNotifier
{
	std::weak_ptr<Horizon::Zone::Entity> _entity;

	explicit GridEntitySpawnNotifier(const std::shared_ptr<Horizon::Zone::Entity>& entity)
	: _entity(entity)
	{ }

	template <class T>
	void notify(GridRefManager<T> &m);

	void Visit(GridRefManager<entity_ns(Player)> &m);

	template<class NOT_INTERESTED>
	void Visit(GridRefManager<NOT_INTERESTED> &) { }
};

struct GridEntityMovementNotifier
{
	std::weak_ptr<Horizon::Zone::Entity> _entity;
	bool _new_entry{ false };

	explicit GridEntityMovementNotifier(const std::shared_ptr<Horizon::Zone::Entity>& entity, bool new_entry = false)
	: _entity(entity), _new_entry(new_entry)
	{ }

	template <class T>
	void notify(GridRefManager<T> &m);

	void Visit(GridRefManager<entity_ns(Player)> &m);

	template<class NOT_INTERESTED>
	void Visit(GridRefManager<NOT_INTERESTED> &) { }
};

struct GridEntitySearcher
{
	std::weak_ptr<Horizon::Zone::Entity> _result;
	GUIDCheckPredicate _predicate;

	explicit GridEntitySearcher(uint32_t guid)
	: _predicate(guid)
	{ }

	[[nodiscard]] std::shared_ptr<Horizon::Zone::Entity> get_result() const;

	template <class T>
	void search(GridRefManager<T> &m);

	void Visit(GridRefManager<entity_ns(Player)> &m);
	void Visit(GridRefManager<entity_ns(NPC)> &m);
	void Visit(GridRefManager<entity_ns(Elemental)> &m);
	void Visit(GridRefManager<entity_ns(Homunculus)> &m);
	void Visit(GridRefManager<entity_ns(Mercenary)> &m);
	void Visit(GridRefManager<entity_ns(Pet)> &m);
	void Visit(GridRefManager<entity_ns(Monster)> &m);
	void Visit(GridRefManager<entity_ns(Skill)> &m);

	template<class NOT_INTERESTED>
	void Visit(GridRefManager<NOT_INTERESTED> &) { }
};

struct GridMonsterActiveAIExecutor
{
	std::weak_ptr<Horizon::Zone::Entities::Player> _player;

	explicit GridMonsterActiveAIExecutor(const std::shared_ptr<Horizon::Zone::Entities::Player> &player)
	: _player(player)
	{ }

	template <class T>
	void perform(GridRefManager<T> &m);

	void Visit(GridRefManager<entity_ns(Monster)> &m);

	template<class NOT_INTERESTED>
	void Visit(GridRefManager<NOT_INTERESTED> &) { }
};

struct GridMonsterAIActiveSearchTarget
{
	std::weak_ptr<Horizon::Zone::Entities::Monster> _monster;

	explicit GridMonsterAIActiveSearchTarget(const std::shared_ptr<Horizon::Zone::Entities::Monster> &monster)
	: _monster(monster)
	{ }

	template <class T>
	void search(GridRefManager<T> &m);

	void Visit(GridRefManager<entity_ns(Player)> &m);
	void Visit(GridRefManager<entity_ns(Elemental)> &m);
	void Visit(GridRefManager<entity_ns(Homunculus)> &m);
	void Visit(GridRefManager<entity_ns(Mercenary)> &m);
	void Visit(GridRefManager<entity_ns(Skill)> &m);

	template<class NOT_INTERESTED>
	void Visit(GridRefManager<NOT_INTERESTED> &) { }	
};

struct GridMonsterAIChangeChaseTarget
{
	std::weak_ptr<Horizon::Zone::Entities::Monster> _monster;

	explicit GridMonsterAIChangeChaseTarget(const std::shared_ptr<Horizon::Zone::Entities::Monster> &monster)
	: _monster(monster)
	{ }

	template <class T>
	void search(GridRefManager<T> &m);

	void Visit(GridRefManager<entity_ns(Player)> &m);
	void Visit(GridRefManager<entity_ns(Elemental)> &m);
	void Visit(GridRefManager<entity_ns(Homunculus)> &m);
	void Visit(GridRefManager<entity_ns(Mercenary)> &m);
	void Visit(GridRefManager<entity_ns(Skill)> &m);

	template<class NOT_INTERESTED>
	void Visit(GridRefManager<NOT_INTERESTED> &) { }	
};

struct GridNPCTrigger
{
	std::weak_ptr<Horizon::Zone::Entity> _source;
	RangeCheckPredicate _predicate;

	explicit GridNPCTrigger(const std::shared_ptr<Horizon::Zone::Entity>& entity)
	: _source(entity), _predicate(entity)
	{ }

	template <class T>
	void check_and_trigger(GridRefManager<T> &m);

	void Visit(GridRefManager<entity_ns(NPC)> &m);

	template<class NOT_INTERESTED>
	void Visit(GridRefManager<NOT_INTERESTED> &) { }
};

struct GridPlayerNotifier
{
	std::weak_ptr<Horizon::Zone::Entity> _entity;
	ByteBuffer _buf;
	grid_notifier_type _type;

	explicit GridPlayerNotifier(ByteBuffer &buf, const std::shared_ptr<Horizon::Zone::Entity>& entity, grid_notifier_type type = GRID_NOTIFY_AREA)
	: _entity(entity), _buf(buf), _type(type)
	{ }

	void notify(GridRefManager<entity_ns(Player)> &m);

	void Visit(GridRefManager<entity_ns(Player)> &m);

	template<class NOT_INTERESTED>
	void Visit(GridRefManager<NOT_INTERESTED> &) { }
};

struct s_grid_sc_apply_in_skill_area_config
{
	int type{ 0 }, total_time{ 0 }, val1{ 0 }, val2{ 0 }, val3{ 0 }, val4{ 0 };
};

struct s_grid_apply_in_area_config
{
	int aoe_range{ 0 };
	int aoe_target_mask{ 0 };
};

// Searches a skillarea for an entity that is within the splash range of the target.
// If found, the status change is applied to the target.
struct GridSCApplyInSkillArea
{
	std::weak_ptr<Horizon::Zone::Entity> _source;
	std::weak_ptr<Horizon::Zone::Entity> _target;
	s_grid_sc_apply_in_skill_area_config _sc_config;
	s_grid_apply_in_area_config _aoe_config;

	explicit GridSCApplyInSkillArea(const std::shared_ptr<Horizon::Zone::Entity>& source, const std::shared_ptr<Horizon::Zone::Entity>& target, const s_grid_sc_apply_in_skill_area_config sc_config, s_grid_apply_in_area_config aoe_config)
	: _source(source), _target(target), _sc_config(sc_config), _aoe_config(aoe_config)
	{ }

	template <class T>
	void apply(GridRefManager<T> &m);

	void Visit(GridRefManager<entity_ns(Player)> &m);
	void Visit(GridRefManager<entity_ns(NPC)> &m);
	void Visit(GridRefManager<entity_ns(Elemental)> &m);
	void Visit(GridRefManager<entity_ns(Homunculus)> &m);
	void Visit(GridRefManager<entity_ns(Mercenary)> &m);
	void Visit(GridRefManager<entity_ns(Pet)> &m);
	void Visit(GridRefManager<entity_ns(Monster)> &m);
	void Visit(GridRefManager<entity_ns(Skill)> &m);

	template<class NOT_INTERESTED>
	void Visit(GridRefManager<NOT_INTERESTED> &) { }
};

// Removes a status change from an entity that is within the splash range of the target and area with target as center.
struct GridSCRemoveInSkillArea
{
	std::weak_ptr<Horizon::Zone::Entity> _source;
	std::weak_ptr<Horizon::Zone::Entity> _target;
	s_grid_apply_in_area_config _aoe_config;
	int _sc_type;

	explicit GridSCRemoveInSkillArea(const std::shared_ptr<Horizon::Zone::Entity>& source, const std::shared_ptr<Horizon::Zone::Entity>& target, int sc_type, s_grid_apply_in_area_config aoe_config)
	: _source(source), _target(target), _sc_type(sc_type), _aoe_config(aoe_config)
	{ }

	template <class T>
	void apply(GridRefManager<T> &m);

	void Visit(GridRefManager<entity_ns(Player)> &m);
	void Visit(GridRefManager<entity_ns(NPC)> &m);
	void Visit(GridRefManager<entity_ns(Elemental)> &m);
	void Visit(GridRefManager<entity_ns(Homunculus)> &m);
	void Visit(GridRefManager<entity_ns(Mercenary)> &m);
	void Visit(GridRefManager<entity_ns(Pet)> &m);
	void Visit(GridRefManager<entity_ns(Monster)> &m);
	void Visit(GridRefManager<entity_ns(Skill)> &m);

	template<class NOT_INTERESTED>
	void Visit(GridRefManager<NOT_INTERESTED> &) { }
};

// Executes a skill in an area with the target as the center.
struct GridExecuteSkillInArea
{
	std::weak_ptr<Horizon::Zone::Entity> _initial_source;
	std::weak_ptr<Horizon::Zone::Entity> _initial_target;
	s_grid_apply_in_area_config _aoe_config;
	std::shared_ptr<Horizon::Zone::SkillExecution> _skill_execution;

	explicit GridExecuteSkillInArea(const std::shared_ptr<Horizon::Zone::Entity>& source,
		const std::shared_ptr<Horizon::Zone::Entity>& target,
		std::shared_ptr<Horizon::Zone::SkillExecution> skill_execution,
		s_grid_apply_in_area_config aoe_config)
	: _initial_source(source), _initial_target(target), _skill_execution(skill_execution), _aoe_config(aoe_config)
	{ }

	template <class T>
	void apply(GridRefManager<T> &m);

	void Visit(GridRefManager<entity_ns(Player)> &m);
	void Visit(GridRefManager<entity_ns(NPC)> &m);
	void Visit(GridRefManager<entity_ns(Elemental)> &m);
	void Visit(GridRefManager<entity_ns(Homunculus)> &m);
	void Visit(GridRefManager<entity_ns(Mercenary)> &m);
	void Visit(GridRefManager<entity_ns(Pet)> &m);
	void Visit(GridRefManager<entity_ns(Monster)> &m);
	void Visit(GridRefManager<entity_ns(Skill)> &m);

	template<class NOT_INTERESTED>
	void Visit(GridRefManager<NOT_INTERESTED> &) { }
};

// Executes a skill targeted at all entities in a particular map coordinate.
struct GridExecuteSkillInCell
{
	std::weak_ptr<Horizon::Zone::Entity> _initial_source;
	MapCoords _cell;
	s_grid_apply_in_area_config _aoe_config;
	std::shared_ptr<Horizon::Zone::SkillExecution> _skill_execution;

	explicit GridExecuteSkillInCell(const std::shared_ptr<Horizon::Zone::Entity>& source,
		MapCoords cell,
		std::shared_ptr<Horizon::Zone::SkillExecution> skill_execution,
		s_grid_apply_in_area_config aoe_config)
	: _initial_source(source), _cell(cell), _skill_execution(skill_execution), _aoe_config(aoe_config)
	{ }

	template <class T>
	void apply(GridRefManager<T> &m);

	void Visit(GridRefManager<entity_ns(Player)> &m);
	void Visit(GridRefManager<entity_ns(NPC)> &m);
	void Visit(GridRefManager<entity_ns(Elemental)> &m);
	void Visit(GridRefManager<entity_ns(Homunculus)> &m);
	void Visit(GridRefManager<entity_ns(Mercenary)> &m);
	void Visit(GridRefManager<entity_ns(Pet)> &m);
	void Visit(GridRefManager<entity_ns(Monster)> &m);
	void Visit(GridRefManager<entity_ns(Skill)> &m);

	template<class NOT_INTERESTED>
	void Visit(GridRefManager<NOT_INTERESTED> &) { }
};

enum grid_entity_skill_use_notification_type
{
	GRID_ENTITY_SKILL_USE_NOTIFY_CASTTIME,
	GRID_ENTITY_SKILL_USE_NOTIFY_SUCCESS_DAMAGE,
	GRID_ENTITY_SKILL_USE_NOTIFY_SUCCESS_NO_DAMAGE,
};

struct s_entity_skill_use_notifier_config
{
	int source_guid, target_guid, skill_id, skill_lv, damage_value, display_value, start_time, attack_motion;
	int delay_motion, number_of_hits;
	zc_notify_act_3_action_types action_type;
	int item_id;
	int target_x, target_y;
	int element, cast_time;
};

struct GridEntitySkillUseNotifier
{
	std::weak_ptr<Horizon::Zone::Entity> _entity;
	grid_entity_skill_use_notification_type _notification_type;
	s_entity_skill_use_notifier_config _config;

	explicit GridEntitySkillUseNotifier(const std::shared_ptr<Horizon::Zone::Entity>& entity, grid_entity_skill_use_notification_type notification_type, s_entity_skill_use_notifier_config config)
	: _entity(entity), _notification_type(notification_type), _config(config)
	{ }

	template <class T>
	void notify(GridRefManager<T> &m);

	void Visit(GridRefManager<entity_ns(Player)> &m);

	template<class NOT_INTERESTED>
	void Visit(GridRefManager<NOT_INTERESTED> &) { }
};
#undef entity_ns

#endif /* HORIZON_ZONE_GAME_MAP_GRIDNOTIFIERS_HPP */
