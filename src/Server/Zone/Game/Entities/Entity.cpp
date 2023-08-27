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

#include "Entity.hpp"
#include "Core/Logging/Logger.hpp"
#include "Server/Zone/Game/Map/MapManager.hpp"
#include "Server/Zone/Game/Map/Map.hpp"
#include "Server/Zone/Game/Entities/NPC/NPC.hpp"
#include "Server/Zone/Game/Entities/Battle/Combat.hpp"
#include "Server/Zone/Game/Entities/Item/Item.hpp"
#include "Server/Zone/Game/Map/Grid/Container/GridReferenceContainerVisitor.hpp"
#include "Server/Zone/Game/Map/Grid/Notifiers/GridNotifiers.hpp"
#include "Server/Zone/Game/Entities/Traits/Status.hpp"
#include "Server/Zone/Packets/TransmittedPackets.hpp"
#include "Server/Zone/Definitions/ClientDefinitions.hpp"
#include "Server/Zone/Zone.hpp"

using namespace Horizon::Zone;

Entity::Entity(uint64_t uuid, entity_type type, entity_type_mask type_mask, std::shared_ptr<Map> map, MapCoords map_coords)
	: _type(type), _type_mask(type_mask), _map_coords(map_coords)
{
	set_uuid(uuid);
	set_map(map);
}

// For Player
Entity::Entity(uint64_t uuid, entity_type type, entity_type_mask type_mask)
	: _type(type), _type_mask(type_mask), _map_coords(MapCoords(0, 0))
{
	set_uuid(uuid);
	// Map is set in player::load()
}

void Entity::set_uuid(uint64_t uuid)
{
	sZone->from_uuid(uuid, _s_uuid.type, _s_uuid.guid, _s_uuid.uid2, _s_uuid.uid3);
	_uuid = uuid;
}

Entity::~Entity()
{
	_combat = nullptr;
	_combat_registry = nullptr;
}

bool Entity::initialize()
{
	if (type() == ENTITY_ITEM || type() == ENTITY_SKILL) {
		_is_initialized = true;
		return _is_initialized;
	}
		
	_status = std::make_shared<Horizon::Zone::Traits::Status>(shared_from_this(), type());
	_combat_registry = std::make_shared<CombatRegistry>(shared_from_this());
	_is_initialized = true;

	return _is_initialized;
}

bool Entity::finalize()
{
	set_finalized(true);

	return _is_finalized;
}

std::shared_ptr<AStar::CoordinateList> Entity::path_to(std::shared_ptr<Entity> e)
{
	std::shared_ptr<AStar::CoordinateList> wp = std::make_shared<AStar::CoordinateList>(map()->get_pathfinder().findPath(map_coords(), e->map_coords()));

	if (wp->size() == 0 || wp->empty())
		return nullptr;

	return std::move(wp);
}

bool Entity::schedule_walk()
{
	MapCoords source_pos = {map_coords().x(), map_coords().y()};

	if (!_walk_path.empty())
		_walk_path.clear();

	if (!map())
	{
		// HLog(error) << "Reference to map object has been lost for entity " << (void *) this << ".";
		_dest_pos = {0, 0};
		return false;
	}

	// This method returns vector of coordinates from target to source.
	_walk_path = map()->get_pathfinder().findPath(source_pos, _dest_pos); // ~5us

	_changed_dest_pos = {0, 0};

	// If destination was a collision, nothing is returned.
	if (_walk_path.size() == 0)
	{
		// HLog(warning) << "Entity::schedule_walk: Destination was a collision, no walk path available.";
		_dest_pos = {0, 0};
		return false;
	}

	std::reverse(_walk_path.begin(), _walk_path.end());
	_walk_path.erase(_walk_path.begin());

	if (_walk_path.empty())
	{
		on_pathfinding_failure();
		// HLog(warning) << "Entity::schedule_walk: Path too short or empty, failed to schedule movement.";
		_dest_pos = {0, 0};
		return false;
	}

	// @NOTE It is possible that at the time of begining movement, that a creature is not in the viewport of the player.
	on_movement_begin();				 // 0us
	notify_nearby_players_of_movement(); // 3us
	walk();								 // ~173us
	return true;
}

// This method begins the movement of the entity and schedules movement, server side.
// @NOTE This method is called when the entity is already in motion and a new destination is set.
void Entity::walk()
{
	// Fixes the jumping walk bug that happens when the walk is invoked while entity is already walking.
	if (map()->container()->getScheduler().Count(get_scheduler_task_id(ENTITY_SCHEDULE_WALK)) > 0)
	{
		return;
	}

	if (status() == nullptr || status()->movement_speed() == nullptr)
	{
		// HLog(error) << "Entity::walk: Status is null, cannot walk.";
		return;
	}

	if (is_attacking())
		stop_attacking();

	MapCoords c = _walk_path.at(0); // for the first step.

	map()->container()->getScheduler().Schedule(
		Milliseconds(status()->movement_speed()->get_with_cost(c.move_cost())), get_scheduler_task_id(ENTITY_SCHEDULE_WALK),
		[this](TaskContext context)
		{
			if (_walk_path.size() == 0) // to fix the "invalid vector subscript" error.
				return;

			MapCoords c = _walk_path.at(0);

			// Force stop as the current coordinates might asynchronously update after map has changed
			// and co-ordinates are reset to something in a previous walk path.
			// This force stop will return before changing co-ordinates and
			// prevent further movement updates after map has changed.
			if (_jump_walk_stop)
			{
				stop_walking(true);
				force_movement_stop_internal(false);
				return;
			}

			MapCoords step_coords(c.x(), c.y());

			// set_direction((directions) my_coords.direction_to(step_coords));

			notify_nearby_players_of_existence(EVP_NOTIFY_OUT_OF_SIGHT);
			set_map_coords(step_coords);
			on_movement_step();
			notify_nearby_players_of_existence(EVP_NOTIFY_IN_SIGHT);

			_walk_path.erase(_walk_path.begin());

			if (_changed_dest_pos != MapCoords(0, 0))
			{
				_dest_pos = _changed_dest_pos;
				context.CancelGroup(get_scheduler_task_id(ENTITY_SCHEDULE_WALK));
				schedule_walk();
				return;
			}
			else if (_dest_pos == MapCoords(c.x(), c.y()) || _walk_path.empty())
			{
				context.CancelGroup(get_scheduler_task_id(ENTITY_SCHEDULE_WALK));
				stop_walking();
			}

			if (!_walk_path.empty())
				context.Repeat(Milliseconds(status()->movement_speed()->get_with_cost(c.move_cost())));
		});
}

// Walking cancel and stopping algorithm.
// Stops the Entity from walking and triggers the on_movement_end event.
// If cancel is true, the Entity will be forced to stop walking and the scheduler task will be cancelled.
// returns true if the Entity was walking and was stopped.
bool Entity::stop_walking(bool cancel, bool notify)
{
	_dest_pos = {0, 0};
	_changed_dest_pos = {0, 0};

	if (cancel)
		map()->container()->getScheduler().CancelGroup(get_scheduler_task_id(ENTITY_SCHEDULE_WALK));

	if (notify)
		this->notify_nearby_players_of_movement_stop(map_coords());

	on_movement_end();

	return true;
}

void Entity::on_attack_end()
{
	set_attacking(false);
}

bool Entity::walk_to_coordinates(int16_t x, int16_t y)
{
	if (_dest_pos.x() != 0 && _dest_pos.y() != 0 && _dest_pos.x() != x && _dest_pos.y() != y)
	{
		_changed_dest_pos = {x, y};
		return true;
	}

	if (is_attacking())
		stop_attacking();

	_dest_pos = {x, y};

	if (schedule_walk() == false)
	{
		// HLog(warning) << "Entity (" << guid() << ") could not schedule movement.";
		return false;
	}
	return true;
}

bool Entity::walk_to_entity(std::shared_ptr<Entity> entity)
{
	if (entity == nullptr)
		return false;

	if (walk_to_coordinates(entity->map_coords().x(), entity->map_coords().y()))
	{
		// HLog(warning) << "Entity (" << guid() << ") could not walk to (" << entity->guid() << ").";
		return false;
	}

	return true;
}

bool Entity::is_in_range_of(std::shared_ptr<Entity> e, uint8_t range)
{
	if (e->map()->get_name().compare(map()->get_name()))
		return false;

	return map_coords().is_within_range(e->map_coords(), range);
}

std::shared_ptr<Entity> Entity::get_nearby_entity(uint32_t guid)
{
	GridEntitySearcher searcher(guid);
	GridReferenceContainerVisitor<GridEntitySearcher, GridReferenceContainer<AllEntityTypes>> search_visitor(searcher);

	map()->visit_in_range(map_coords(), search_visitor);

	return searcher.get_result();
}

void Entity::notify_nearby_players_of_existence(entity_viewport_notification_type notif_type)
{
	GridEntityExistenceNotifier existence_notify(shared_from_this(), notif_type);
	GridReferenceContainerVisitor<GridEntityExistenceNotifier, GridReferenceContainer<AllEntityTypes>> entity_visitor(existence_notify);

	map()->visit_in_range(map_coords(), entity_visitor);
}

void Entity::notify_nearby_players_of_spawn()
{
	GridEntitySpawnNotifier spawn_notify(shared_from_this());
	GridReferenceContainerVisitor<GridEntitySpawnNotifier, GridReferenceContainer<AllEntityTypes>> entity_visitor(spawn_notify);

	map()->visit_in_range(map_coords(), entity_visitor);
}

void Entity::notify_nearby_players_of_movement(bool new_entry)
{
	GridEntityMovementNotifier movement_notify(shared_from_this(), new_entry);
	GridReferenceContainerVisitor<GridEntityMovementNotifier, GridReferenceContainer<AllEntityTypes>> entity_visitor(movement_notify);

	map()->visit_in_range(map_coords(), entity_visitor);
}

void Entity::notify_nearby_players_of_movement_stop(MapCoords stop_coords)
{
	GridEntityMovementStopNotifier movement_stop_notify(guid(), stop_coords.x(), stop_coords.y());
	GridReferenceContainerVisitor<GridEntityMovementStopNotifier, GridReferenceContainer<AllEntityTypes>> entity_visitor(movement_stop_notify);

	map()->visit_in_range(map_coords(), entity_visitor);
}

void Entity::notify_nearby_players_of_skill_use(grid_entity_skill_use_notification_type notification_type, s_entity_skill_use_notifier_config config)
{
	GridEntitySkillUseNotifier notifier(shared_from_this(), notification_type, config);
	GridReferenceContainerVisitor<GridEntitySkillUseNotifier, GridReferenceContainer<AllEntityTypes>> skill_use_notifier(notifier);

	map()->visit_in_range(map_coords(), skill_use_notifier);
}

void Entity::notify_nearby_players_of_basic_attack(s_grid_entity_basic_attack_config config)
{
	GridEntityBasicAttackNotifier notifier(shared_from_this(), config);
	GridReferenceContainerVisitor<GridEntityBasicAttackNotifier, GridReferenceContainer<AllEntityTypes>> basic_attack_notifier(notifier);

	map()->visit_in_range(map_coords(), basic_attack_notifier);
}

void Entity::notify_nearby_players_of_item_drop(s_grid_notify_item_drop_entry entry)
{
	GridEntityItemDropNotifier notifier(entry);
	GridReferenceContainerVisitor<GridEntityItemDropNotifier, GridReferenceContainer<AllEntityTypes>> item_drop_notifier(notifier);

	map()->visit_in_range(map_coords(), item_drop_notifier);
}

bool Entity::status_effect_start(int type, int total_time, int val1, int val2, int val3, int val4)
{
	std::map<int16_t, std::shared_ptr<status_change_entry>>::iterator it = get_status_effects().find(type);

	if (it == get_status_effects().end())
	{
		std::shared_ptr<status_change_entry> sce = std::make_shared<status_change_entry>();
		sce->type = type;
		sce->val1 = val1;
		sce->val2 = val2;
		sce->val3 = val3;
		sce->val4 = val4;

		if (total_time < 0)
		{
			sce->infinite_duration = true;
			sce->current_time = 0;
			sce->total_time = 0;
		}
		else
		{
			sce->current_time = std::time(nullptr) + total_time;
			sce->total_time = total_time;
		}

		get_status_effects().insert(std::pair(type, sce));
		on_status_effect_start(sce);
	}
	else
	{
		std::shared_ptr<status_change_entry> sce = it->second;
		sce->current_time = std::time(nullptr) + total_time;
		sce->total_time = total_time;

		on_status_effect_change(sce);
	}

	if (map()->container()->getScheduler().Count(get_scheduler_task_id(ENTITY_SCHEDULE_STATUS_EFFECT_CLEAR)) == 0)
		map()->container()->getScheduler().Schedule(
			Milliseconds(ENTITY_STATUS_EFFECT_CHECK_TIME),
			get_scheduler_task_id(ENTITY_SCHEDULE_STATUS_EFFECT_CLEAR),
			[this](TaskContext context)
			{
				std::map<int16_t, std::shared_ptr<status_change_entry>>::iterator it = get_status_effects().begin();

				int infinite_statuses = 0;
				for (; it != get_status_effects().end(); it++)
				{
					std::shared_ptr<status_change_entry> sce = it->second;

					if (sce->infinite_duration == false)
					{
						infinite_statuses++;
						continue;
					}

					if (sce->current_time - std::time(nullptr) <= 0)
						status_effect_end(sce->type);
				}

				if (get_status_effects().size() > infinite_statuses)
					context.Repeat(Milliseconds(ENTITY_STATUS_EFFECT_CHECK_TIME));
			});

	return true;
}

bool Entity::status_effect_end(int type)
{
	std::map<int16_t, std::shared_ptr<status_change_entry>>::iterator it = get_status_effects().find(type);

	if (it == get_status_effects().end())
	{
		HLog(warning) << "Trying to end status effect that doesn't exist. ID " << type << ", ignoring...";
		return false;
	}

	on_status_effect_end(it->second);

	get_status_effects().erase(it);

	return true;
}

bool Entity::is_dead()
{
	if (status() == nullptr)
		return true;
		
	return status()->current_hp()->get_base() <= 0;
}

void Entity::on_damage_received(std::shared_ptr<Entity> damage_dealer, int damage)
{
	if (status()->current_hp()->total() < damage)
	{
		status()->current_hp()->set_base(0);
		on_killed(damage_dealer);
		return;
	}
}

void Entity::on_killed(std::shared_ptr<Entity> killer, bool with_drops, bool with_exp)
{
}

bool Entity::stop_attacking()
{
	if (!is_attacking())
		return false;

	map()->container()->getScheduler().CancelGroup(get_scheduler_task_id(ENTITY_SCHEDULE_ATTACK));
	combat().reset();

	return true;
}

bool Entity::attack(std::shared_ptr<Entity> target, bool continuous)
{
	if (target == nullptr)
		return false;

	set_combat(std::make_shared<Combat>(shared_from_this(), target));

	map()->container()->getScheduler().Schedule(
		Milliseconds(0), get_scheduler_task_id(ENTITY_SCHEDULE_ATTACK),
		[this, continuous, target](TaskContext context)
		{
			if (target == nullptr)
			{
				on_attack_end();
				return;
			}

			if (target->is_dead())
			{
				on_attack_end();
				return;
			}

			if (path_to(target)->size() == 0)
			{
				on_attack_end();
				return;
			}

			int range = this->status()->attack_range()->get_base();

			_attackable_time = status()->attack_delay()->total();

			if (!is_in_range_of(target, range) && !is_walking())
			{

				walk_to_entity(target);

				if (continuous)
					context.Repeat(Milliseconds(_attackable_time));

				return;
			}

			if (!is_in_range_of(target, range) && is_walking())
			{
				context.Repeat(Milliseconds(_attackable_time));
				return;
			}

			if (is_in_range_of(target, range) && is_walking())
				stop_walking();

			if (!is_attacking())
				set_attacking(true);

			combat()->weapon_attack();

			if (continuous)
				context.Repeat(Milliseconds(_attackable_time));
		});

	return true;
}

void Entity::apply_status_change_in_area(std::shared_ptr<Entity> target, s_grid_sc_apply_in_skill_area_config const &config, s_grid_apply_in_area_config const &aoe_config)
{
	GridSCApplyInSkillArea sc_apply_in_skill_area(shared_from_this(), target, config, aoe_config);
	GridReferenceContainerVisitor<GridSCApplyInSkillArea, GridReferenceContainer<AllEntityTypes>> container(sc_apply_in_skill_area);

	map()->visit_in_range(map_coords(), container, MAX_VIEW_RANGE);
}

void Entity::remove_status_change_in_area(std::shared_ptr<Entity> target, int sc_type, s_grid_apply_in_area_config const &aoe_config)
{
	GridSCRemoveInSkillArea sc_remove_in_skill_area(shared_from_this(), target, sc_type, aoe_config);
	GridReferenceContainerVisitor<GridSCRemoveInSkillArea, GridReferenceContainer<AllEntityTypes>> container(sc_remove_in_skill_area);

	map()->visit_in_range(map_coords(), container, MAX_VIEW_RANGE);
}

void Entity::execute_skill_in_area(std::shared_ptr<Entity> target, std::shared_ptr<SkillExecution> skill_execution, s_grid_apply_in_area_config const &aoe_config)
{
	GridExecuteSkillInArea execute_skill_in_area(shared_from_this(), target, skill_execution, aoe_config);
	GridReferenceContainerVisitor<GridExecuteSkillInArea, GridReferenceContainer<AllEntityTypes>> container(execute_skill_in_area);

	map()->visit_in_range(map_coords(), container, MAX_VIEW_RANGE);
}

void Entity::execute_skill_in_cell(std::shared_ptr<Entity> target, MapCoords cell, std::shared_ptr<SkillExecution> skill_execution, s_grid_apply_in_area_config const &aoe_config)
{
	GridExecuteSkillInCell execute_skill_in_cell(shared_from_this(), cell, skill_execution, aoe_config);
	GridReferenceContainerVisitor<GridExecuteSkillInCell, GridReferenceContainer<AllEntityTypes>> container(execute_skill_in_cell);

	map()->visit_in_range(map_coords(), container, MAX_VIEW_RANGE);
}

void Entity::use_skill_on_target(int16_t skill_lv, int16_t skill_id, int target_guid)
{
	auto ske = std::make_shared<SkillExecution>(shared_from_this(), skill_id, skill_lv);
	ske->execute(target_guid);
}

void Entity::use_skill_on_ground(int16_t skill_lv, int16_t skill_id, int16_t pos_x, int16_t pos_y)
{
	auto ske = std::make_shared<SkillExecution>(shared_from_this(), skill_id, skill_lv);
	ske->execute(pos_x, pos_y);
}

void Entity::use_skill_on_ground(int16_t skill_lv, int16_t skill_id, int16_t pos_x, int16_t pos_y, std::string contents)
{
	auto ske = std::make_shared<SkillExecution>(shared_from_this(), skill_id, skill_lv);
	ske->execute(pos_x, pos_y, contents);
}

/**
 * Extremely time-sensitive, do not use for any other purpose than to check for very small calculations.
 */
void Entity::update(uint64_t tick)
{
	if (_combat_registry != nullptr)
		combat_registry()->process_queue();
	if (status() != nullptr && status()->is_initialized() != false)
		status()->status_registry()->process_queue();
}