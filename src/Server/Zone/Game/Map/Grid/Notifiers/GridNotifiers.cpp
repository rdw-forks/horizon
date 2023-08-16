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

#include "GridNotifiers.hpp"

#include "Server/Zone/Definitions/NPCDefinitions.hpp"
#include "Core/Logging/Logger.hpp"
#include "Server/Zone/Game/Entities/Player/Player.hpp"
#include "Server/Zone/Game/Entities/Skill/Skill.hpp"
#include "Server/Zone/Game/Entities/Traits/Status.hpp"
#include "Server/Zone/Game/Entities/NPC/NPC.hpp"
#include "Server/Zone/Game/Entities/Creature/Companion/Pet.hpp"
#include "Server/Zone/Game/Entities/Creature/Companion/Homunculus.hpp"
#include "Server/Zone/Game/Entities/Creature/Companion/Mercenary.hpp"
#include "Server/Zone/Game/Entities/Creature/Companion/Elemental.hpp"
#include "Server/Zone/Game/Entities/Creature/Hostile/Monster.hpp"
#include "Server/Zone/Game/Map/Grid/GridRefManager.hpp"
#include "Server/Zone/Game/Map/Path/AStar.hpp"
#include "Server/Zone/Session/ZoneSession.hpp"

using namespace Horizon::Zone::Entities;

void GridPlayerNotifier::notify(GridRefManager<Horizon::Zone::Entities::Player> &m)
{
	using namespace Horizon::Zone::Entities;

	std::shared_ptr<Player> pl = _entity.lock()->template downcast<Player>();

	for (typename GridRefManager<Player>::iterator iter = m.begin(); iter != typename GridRefManager<Player>::iterator(nullptr); ++iter) {
		if (iter->source() == nullptr)
			continue;

		switch (_type)
		{
			case GRID_NOTIFY_AREA_WOS:
				if (pl != nullptr && iter->source()->guid() == pl->guid())
					continue;
			default:
				break;
		}
		iter->source()->get_session()->transmit_buffer(_buf, _buf.active_length());
	}
}

void GridPlayerNotifier::Visit(GridRefManager<Player> &m) { notify(m); }
template<> void GridPlayerNotifier::Visit<NPC>(GridRefManager<NPC> &m);
template<> void GridPlayerNotifier::Visit<Elemental>(GridRefManager<Elemental> &m);
template<> void GridPlayerNotifier::Visit<Homunculus>(GridRefManager<Homunculus> &m);
template<> void GridPlayerNotifier::Visit<Mercenary>(GridRefManager<Mercenary> &m);
template<> void GridPlayerNotifier::Visit<Pet>(GridRefManager<Pet> &m);
template<> void GridPlayerNotifier::Visit<Monster>(GridRefManager<Monster> &m);
template<> void GridPlayerNotifier::Visit<Skill>(GridRefManager<Skill> &m);

template <class T>
void GridViewPortUpdater::update(GridRefManager<T> &m)
{
    using namespace Horizon::Zone::Entities;

    if (_entity.expired())
        return;

    std::shared_ptr<Player> pl = _entity.lock()->template downcast<Player>();

    for (typename GridRefManager<T>::iterator iter = m.begin(); iter != typename GridRefManager<T>::iterator(nullptr); ++iter) {
        if (iter->source() == nullptr || iter->source()->guid() == pl->guid())
            continue;

        if (pl->get_session() == nullptr || pl->get_session()->clif() == nullptr)
            continue;

        std::shared_ptr<Horizon::Zone::Entity> vp_e = iter->source()->shared_from_this();

        if (pl->is_in_range_of(vp_e, MAX_VIEW_RANGE) && !vp_e->is_walking())
            pl->add_entity_to_viewport(vp_e);
        else if (!pl->is_in_range_of(vp_e, MAX_VIEW_RANGE))
            pl->remove_entity_from_viewport(vp_e, EVP_NOTIFY_OUT_OF_SIGHT);
    }
}

void GridViewPortUpdater::Visit(GridRefManager<Player> &m) { update(m); }
void GridViewPortUpdater::Visit(GridRefManager<NPC> &m) { update(m); }
void GridViewPortUpdater::Visit(GridRefManager<Elemental> &m) { update(m); }
void GridViewPortUpdater::Visit(GridRefManager<Homunculus> &m) { update(m); }
void GridViewPortUpdater::Visit(GridRefManager<Mercenary> &m) { update(m); }
void GridViewPortUpdater::Visit(GridRefManager<Pet> &m) { update(m); }
void GridViewPortUpdater::Visit(GridRefManager<Monster> &m) { update(m); }
void GridViewPortUpdater::Visit(GridRefManager<Skill> &m) { update(m); }

template <class T>
void GridEntityExistenceNotifier::notify(GridRefManager<T> &m)
{
    using namespace Horizon::Zone::Entities;

    if (!m.get_size())
        return;

    std::shared_ptr<Horizon::Zone::Entity> src_entity = _entity.lock();

    for (typename GridRefManager<T>::iterator iter = m.begin(); iter != typename GridRefManager<T>::iterator(nullptr); ++iter) {
        if (iter->source() == nullptr)
            continue;

        std::shared_ptr<Player> tpl = iter->source()->template downcast<Player>();

        if (src_entity == nullptr || src_entity->guid() == tpl->guid())
            continue;

        if (tpl->get_session() == nullptr || tpl->get_session()->clif() == nullptr)
            continue;

        bool is_in_range = tpl->is_in_range_of(src_entity);

        if (_notif_type == EVP_NOTIFY_IN_SIGHT && is_in_range) {
            if (tpl->entity_is_in_viewport(src_entity))
                continue;
            // Target player realizes new entity in viewport.
            // Source entity doesn't need to realize target as update_viewport() is called when needed/
            tpl->add_entity_to_viewport(src_entity);
        } else if (_notif_type == EVP_NOTIFY_OUT_OF_SIGHT && !is_in_range) {
            if (!tpl->entity_is_in_viewport(src_entity))
                continue;
            
            tpl->remove_entity_from_viewport(src_entity, EVP_NOTIFY_OUT_OF_SIGHT);
        }
        else if (_notif_type > EVP_NOTIFY_OUT_OF_SIGHT) {
            if (!tpl->entity_is_in_viewport(src_entity))
                continue;

            tpl->remove_entity_from_viewport(src_entity, _notif_type);
        }
    }
}

void GridEntityExistenceNotifier::Visit(GridRefManager<Player> &m) { notify(m); }
template <> void GridEntityExistenceNotifier::Visit<NPC>(GridRefManager<NPC> &m);
template <> void GridEntityExistenceNotifier::Visit<Elemental>(GridRefManager<Elemental> &m);
template <> void GridEntityExistenceNotifier::Visit<Homunculus>(GridRefManager<Homunculus> &m);
template <> void GridEntityExistenceNotifier::Visit<Mercenary>(GridRefManager<Mercenary> &m);
template <> void GridEntityExistenceNotifier::Visit<Pet>(GridRefManager<Pet> &m);
template <> void GridEntityExistenceNotifier::Visit<Monster>(GridRefManager<Monster> &m);
template <> void GridEntityExistenceNotifier::Visit<Skill>(GridRefManager<Skill> &m);

template <class T>
void GridEntitySpawnNotifier::notify(GridRefManager<T> &m)
{
    using namespace Horizon::Zone::Entities;

    if (!m.get_size())
        return;

    std::shared_ptr<Horizon::Zone::Entity> src_entity = _entity.lock();

    for (typename GridRefManager<T>::iterator iter = m.begin(); iter != typename GridRefManager<T>::iterator(nullptr); ++iter) {
        if (iter->source() == nullptr)
            continue;

        std::shared_ptr<Player> tpl = iter->source()->template downcast<Player>();

        if (src_entity == nullptr || src_entity->guid() == tpl->guid())
            continue;

        if (tpl->get_session() == nullptr || tpl->get_session()->clif() == nullptr)
            continue;

        tpl->spawn_entity_in_viewport(src_entity);
    }
}

void GridEntitySpawnNotifier::Visit(GridRefManager<Player> &m) { notify<Player>(m); }
template <> void GridEntitySpawnNotifier::Visit<NPC>(GridRefManager<NPC> &m);
template <> void GridEntitySpawnNotifier::Visit<Elemental>(GridRefManager<Elemental> &m);
template <> void GridEntitySpawnNotifier::Visit<Homunculus>(GridRefManager<Homunculus> &m);
template <> void GridEntitySpawnNotifier::Visit<Mercenary>(GridRefManager<Mercenary> &m);
template <> void GridEntitySpawnNotifier::Visit<Pet>(GridRefManager<Pet> &m);
template <> void GridEntitySpawnNotifier::Visit<Monster>(GridRefManager<Monster> &m);
template <> void GridEntitySpawnNotifier::Visit<Skill>(GridRefManager<Skill> &m);

template <class T>
void GridEntityMovementNotifier::notify(GridRefManager<T> &m)
{
    using namespace Horizon::Zone::Entities;

    if (m.get_size() == 0)
        return;

    std::shared_ptr<Horizon::Zone::Entity> src_entity = _entity.lock();

    if (src_entity == nullptr)
        return;

    for (typename GridRefManager<T>::iterator iter = m.begin(); iter != typename GridRefManager<T>::iterator(nullptr); iter++) {
        if (iter->source() == nullptr)
            continue;

        std::shared_ptr<Player> tpl = iter->source()->template downcast<Player>();

        if (src_entity->guid() == tpl->guid())
            continue;

        if (tpl->get_session() == nullptr || tpl->get_session()->clif() == nullptr)
            continue;

        if (_new_entry == true)
            tpl->realize_entity_movement_entry(src_entity);
        else
            tpl->realize_entity_movement(src_entity);
    }
}

void GridEntityMovementNotifier::Visit(GridRefManager<Player> &m) { notify(m); }

template <> void GridEntityMovementNotifier::Visit<NPC>(GridRefManager<NPC> &m);
template <> void GridEntityMovementNotifier::Visit<Elemental>(GridRefManager<Elemental> &m);
template <> void GridEntityMovementNotifier::Visit<Homunculus>(GridRefManager<Homunculus> &m);
template <> void GridEntityMovementNotifier::Visit<Mercenary>(GridRefManager<Mercenary> &m);
template <> void GridEntityMovementNotifier::Visit<Pet>(GridRefManager<Pet> &m);
template <> void GridEntityMovementNotifier::Visit<Monster>(GridRefManager<Monster> &m);
template <> void GridEntityMovementNotifier::Visit<Skill>(GridRefManager<Skill> &m);

template <class T>
void GridEntitySearcher::search(GridRefManager<T> &m)
{
    // Found check.
    if (!_result.expired())
        return;

    using namespace Horizon::Zone;
    for (typename GridRefManager<T>::iterator iter = m.begin(); iter != typename GridRefManager<T>::iterator(nullptr); ++iter) {
        if (iter->source() == nullptr)
            continue;

        std::weak_ptr<Entity> entity = iter->source()->shared_from_this();
        if (!entity.expired() && _predicate(entity)) {
            _result = entity;
            return;
        }
    }
}

std::shared_ptr<Horizon::Zone::Entity> GridEntitySearcher::get_result() const { return _result.lock(); }

void GridEntitySearcher::Visit(GridRefManager<Player> &m) { search<Player>(m); }
void GridEntitySearcher::Visit(GridRefManager<NPC> &m) { search<NPC>(m); }
void GridEntitySearcher::Visit(GridRefManager<Elemental> &m) { search<Elemental>(m); }
void GridEntitySearcher::Visit(GridRefManager<Homunculus> &m) { search<Homunculus>(m); }
void GridEntitySearcher::Visit(GridRefManager<Mercenary> &m) { search<Mercenary>(m); }
void GridEntitySearcher::Visit(GridRefManager<Pet> &m) { search<Pet>(m); }
void GridEntitySearcher::Visit(GridRefManager<Monster> &m) { search<Monster>(m); }
void GridEntitySearcher::Visit(GridRefManager<Skill> &m) { search<Skill>(m); }

template <class T>
void GridMonsterActiveAIExecutor::perform(GridRefManager<T> &m)
{
    if (_player.expired())
        return;

    using namespace Horizon::Zone;
    for (typename GridRefManager<T>::iterator iter = m.begin(); iter != typename GridRefManager<T>::iterator(nullptr); ++iter) {
        if (iter->source() == nullptr)
            continue;

        std::shared_ptr<Monster> monster = iter->source()->template downcast<Monster>();

        if (monster == nullptr)
            continue;

        monster->behavior_active(_player.lock());
    }
}

template <> void GridMonsterActiveAIExecutor::Visit<Player>(GridRefManager<Player> &m);
template <> void GridMonsterActiveAIExecutor::Visit<NPC>(GridRefManager<NPC> &m);
template <> void GridMonsterActiveAIExecutor::Visit<Elemental>(GridRefManager<Elemental> &m);
template <> void GridMonsterActiveAIExecutor::Visit<Homunculus>(GridRefManager<Homunculus> &m);
template <> void GridMonsterActiveAIExecutor::Visit<Mercenary>(GridRefManager<Mercenary> &m);
template <> void GridMonsterActiveAIExecutor::Visit<Pet>(GridRefManager<Pet> &m);
void GridMonsterActiveAIExecutor::Visit(GridRefManager<Monster> &m) { perform<Monster>(m); }
template <> void GridMonsterActiveAIExecutor::Visit<Skill>(GridRefManager<Skill> &m);

template <class T>
void GridMonsterAIActiveSearchTarget::search(GridRefManager<T> &m)
{
    if (_monster.expired())
        return;

    using namespace Horizon::Zone;
    for (typename GridRefManager<T>::iterator iter = m.begin(); iter != typename GridRefManager<T>::iterator(nullptr); ++iter) {
        if (iter->source() == nullptr)
            continue;

        std::shared_ptr<Entity> e = iter->source()->shared_from_this();
        std::shared_ptr<Monster> m = _monster.lock();

        if (m == nullptr || e == nullptr)
            continue;

        if (m->monster_config()->mode & MONSTER_MODE_MASK_TARGETWEAK && e->status()->base_level()->get_base() >= m->monster_config()->level - 5)
            return;

#ifdef ACTIVE_PATH_SEARCH
        // On official servers, monsters will only seek targets that are closer to walk to than their
        // search range. The search range is affected depending on if the monster is walking or not.
        // On some maps there can be a quite long path for just walking two cells in a direction and
        // the client does not support displaying walk paths that are longer than 14 cells, so this
        // option reduces position lag in such situation. But doing a complex search for every possible
        // target, might be CPU intensive.
        // Disable this to make monsters not do any path search when looking for a target (old behavior).
        AStar::CoordinateList wp = m->map()->get_pathfinder().findPath(m->map_coords(), e->map_coords());

        if (wp.size() == 0) 
            continue; // no walk path available.

        //Standing monsters use view range, walking monsters use chase range
        if ((m->is_walking() == false && wp.size() > m->monster_config()->view_range)
            || (m->is_walking() == true && wp.size() > m->monster_config()->chase_range))
            continue;
#endif
        m->set_target(e);

        break;
    }
}

void GridMonsterAIActiveSearchTarget::Visit(GridRefManager<Player> &m) { search<Player>(m); }
template <> void GridMonsterAIActiveSearchTarget::Visit<NPC>(GridRefManager<NPC> &m);
void GridMonsterAIActiveSearchTarget::Visit(GridRefManager<Elemental> &m) { search<Elemental>(m); }
void GridMonsterAIActiveSearchTarget::Visit(GridRefManager<Homunculus> &m) { search<Homunculus>(m); }
void GridMonsterAIActiveSearchTarget::Visit(GridRefManager<Mercenary> &m) { search<Mercenary>(m); }
template <> void GridMonsterAIActiveSearchTarget::Visit<Pet>(GridRefManager<Pet> &m);
template <> void GridMonsterAIActiveSearchTarget::Visit<Monster>(GridRefManager<Monster> &m);
void GridMonsterAIActiveSearchTarget::Visit(GridRefManager<Skill> &m) { search<Skill>(m); }

template <class T>
void GridMonsterAIChangeChaseTarget::search(GridRefManager<T> &m)
{
    if (_monster.expired())
        return;

    using namespace Horizon::Zone;
    for (typename GridRefManager<T>::iterator iter = m.begin(); iter != typename GridRefManager<T>::iterator(nullptr); ++iter) {
        if (iter->source() == nullptr)
            continue;

        std::shared_ptr<Entity> e = iter->source()->shared_from_this();
        std::shared_ptr<Monster> m = _monster.lock();

        if (m == nullptr || e == nullptr)
            continue;

        std::shared_ptr<AStar::CoordinateList> wp = m->path_to(e);
        
        if (wp->size() > m->monster_config()->attack_range)
            continue;

        m->set_target(e);

        break;
    }
}

void GridMonsterAIChangeChaseTarget::Visit(GridRefManager<Player> &m) { search<Player>(m); }
template <> void GridMonsterAIChangeChaseTarget::Visit<NPC>(GridRefManager<NPC> &m);
void GridMonsterAIChangeChaseTarget::Visit(GridRefManager<Elemental> &m) { search<Elemental>(m); }
void GridMonsterAIChangeChaseTarget::Visit(GridRefManager<Homunculus> &m) { search<Homunculus>(m); }
void GridMonsterAIChangeChaseTarget::Visit(GridRefManager<Mercenary> &m) { search<Mercenary>(m); }
template <> void GridMonsterAIChangeChaseTarget::Visit<Pet>(GridRefManager<Pet> &m);
template <> void GridMonsterAIChangeChaseTarget::Visit<Monster>(GridRefManager<Monster> &m);
void GridMonsterAIChangeChaseTarget::Visit(GridRefManager<Skill> &m) { search<Skill>(m); }


template <class T>
void GridNPCTrigger::check_and_trigger(GridRefManager<T> &m)
{
    if (_source.expired())
        return;

    using namespace Horizon::Zone::Entities;
    for (typename GridRefManager<T>::iterator iter = m.begin(); iter != typename GridRefManager<T>::iterator(nullptr); ++iter) {
        std::shared_ptr<NPC> npc = iter->source()->template downcast<NPC>();
        if (npc == nullptr)
            continue;

        std::shared_ptr<npc_db_data> const &nd = npc->map()->container()->get_lua_manager()->npc()->get_npc_from_db(npc->guid());
        if (nd != nullptr && nd->trigger_range && _predicate(npc, nd->trigger_range)) {
            std::shared_ptr<Player> player = _source.lock()->downcast<Player>();
            _source.lock()->map()->container()->get_lua_manager()->npc()->contact_npc_for_player(player, npc->guid());
        }
    }
}

void GridNPCTrigger::Visit(GridRefManager<NPC> &m) { check_and_trigger(m); }
template<> void GridNPCTrigger::Visit<Player>(GridRefManager<Player> &m);
template<> void GridNPCTrigger::Visit<Elemental>(GridRefManager<Elemental> &m);
template<> void GridNPCTrigger::Visit<Homunculus>(GridRefManager<Homunculus> &m);
template<> void GridNPCTrigger::Visit<Mercenary>(GridRefManager<Mercenary> &m);
template<> void GridNPCTrigger::Visit<Pet>(GridRefManager<Pet> &m);
template<> void GridNPCTrigger::Visit<Monster>(GridRefManager<Monster> &m);
template<> void GridNPCTrigger::Visit<Skill>(GridRefManager<Skill> &m);

// Searches a skillarea for an entity that is within the splash range of the target.
// If found, the status change is applied to the entity.
template <class T>
void GridSCApplyInSkillArea::apply(GridRefManager<T> &m)
{
    if (_source.expired())
        return;

    using namespace Horizon::Zone::Entities;
    for (typename GridRefManager<T>::iterator iter = m.begin(); iter != typename GridRefManager<T>::iterator(nullptr); ++iter) {
        std::shared_ptr<Horizon::Zone::Entity> entity = iter->source()->shared_from_this();
        
        if (entity == nullptr)
            continue;
        
        // AOE Target Type check.       
        AOETargetTypePredicate aoe_predicate(_aoe_config.aoe_target_mask);

        if (!aoe_predicate(entity))
            continue;

        RangeCheckPredicate range_predicate(entity);
        
        // If the entity is not in range of target's splash range, 
        // ignore.
        if (!range_predicate(_target, _aoe_config.aoe_range))
            continue;
        
        entity->status_effect_start(_sc_config.type, _sc_config.total_time, _sc_config.val1, _sc_config.val2, _sc_config.val3, _sc_config.val4);
    }
}

void GridSCApplyInSkillArea::Visit(GridRefManager<NPC> &m) { apply(m); }
void GridSCApplyInSkillArea::Visit(GridRefManager<Player> &m) { apply(m); }
void GridSCApplyInSkillArea::Visit(GridRefManager<Elemental> &m) { apply(m); }
void GridSCApplyInSkillArea::Visit(GridRefManager<Homunculus> &m) { apply(m); }
void GridSCApplyInSkillArea::Visit(GridRefManager<Mercenary> &m) { apply(m); }
void GridSCApplyInSkillArea::Visit(GridRefManager<Pet> &m) { apply(m); }
void GridSCApplyInSkillArea::Visit(GridRefManager<Monster> &m) { apply(m); }
void GridSCApplyInSkillArea::Visit(GridRefManager<Skill> &m) { apply(m); }

template <class T>
void GridSCRemoveInSkillArea::apply(GridRefManager<T> &m)
{
    if (_source.expired())
        return;

    using namespace Horizon::Zone::Entities;
    for (typename GridRefManager<T>::iterator iter = m.begin(); iter != typename GridRefManager<T>::iterator(nullptr); ++iter) {
        std::shared_ptr<Horizon::Zone::Entity> entity = iter->source()->shared_from_this();
        
        if (entity == nullptr)
            continue;

        // AOE Target Type check.       
        AOETargetTypePredicate aoe_predicate(_aoe_config.aoe_target_mask);

        if (!aoe_predicate(entity))
            continue;

        // @Todo: check map type PvP, GvG, etc.
        RangeCheckPredicate range_predicate(entity);
        
        // If the entity is not in range of target's splash range, 
        // ignore.
        if (!range_predicate(_target, _aoe_config.aoe_range))
            continue;
        
        entity->status_effect_end(_sc_type);
    }
}

void GridSCRemoveInSkillArea::Visit(GridRefManager<NPC> &m) { apply(m); }
void GridSCRemoveInSkillArea::Visit(GridRefManager<Player> &m) { apply(m); }
void GridSCRemoveInSkillArea::Visit(GridRefManager<Elemental> &m) { apply(m); }
void GridSCRemoveInSkillArea::Visit(GridRefManager<Homunculus> &m) { apply(m); }
void GridSCRemoveInSkillArea::Visit(GridRefManager<Mercenary> &m) { apply(m); }
void GridSCRemoveInSkillArea::Visit(GridRefManager<Pet> &m) { apply(m); }
void GridSCRemoveInSkillArea::Visit(GridRefManager<Monster> &m) { apply(m); }
void GridSCRemoveInSkillArea::Visit(GridRefManager<Skill> &m) { apply(m); }

template <class T>
void GridExecuteSkillInArea::apply(GridRefManager<T> &m)
{
    if (_initial_source.expired())
        return;

    using namespace Horizon::Zone::Entities;
    for (typename GridRefManager<T>::iterator iter = m.begin(); iter != typename GridRefManager<T>::iterator(nullptr); ++iter) {
        std::shared_ptr<Horizon::Zone::Entity> entity = iter->source()->shared_from_this();
        
        if (entity == nullptr)
            continue;

        // AOE Target Type check.       
        AOETargetTypePredicate aoe_predicate(_aoe_config.aoe_target_mask);

        if (!aoe_predicate(entity))
            continue;

        // @Todo: check map type PvP, GvG, etc.
        RangeCheckPredicate range_predicate(entity);
        
        // If the entity is not in range of target's splash range, 
        // ignore.
        if (!range_predicate(_initial_source, _aoe_config.aoe_range))
            continue;
        
        _skill_execution->execute(entity->guid());
    }
}

void GridExecuteSkillInArea::Visit(GridRefManager<NPC> &m) { apply(m); }
void GridExecuteSkillInArea::Visit(GridRefManager<Player> &m) { apply(m); }
void GridExecuteSkillInArea::Visit(GridRefManager<Elemental> &m) { apply(m); }
void GridExecuteSkillInArea::Visit(GridRefManager<Homunculus> &m) { apply(m); }
void GridExecuteSkillInArea::Visit(GridRefManager<Mercenary> &m) { apply(m); }
void GridExecuteSkillInArea::Visit(GridRefManager<Pet> &m) { apply(m); }
void GridExecuteSkillInArea::Visit(GridRefManager<Monster> &m) { apply(m); }
void GridExecuteSkillInArea::Visit(GridRefManager<Skill> &m) { apply(m); }

template <class T>
void GridExecuteSkillInCell::apply(GridRefManager<T> &m)
{
    if (_initial_source.expired())
        return;

    using namespace Horizon::Zone::Entities;
    for (typename GridRefManager<T>::iterator iter = m.begin(); iter != typename GridRefManager<T>::iterator(nullptr); ++iter) {
        std::shared_ptr<Horizon::Zone::Entity> entity = iter->source()->shared_from_this();
        
        if (entity == nullptr)
            continue;

        // AOE Target Type check.       
        AOETargetTypePredicate aoe_predicate(_aoe_config.aoe_target_mask);

        if (!aoe_predicate(entity))
            continue;
        
        CellCheckPredicate cell_predicate(_cell);

        if (!cell_predicate(entity->map_coords()))
            continue;

        _skill_execution->execute(entity->guid());
    }
}

void GridExecuteSkillInCell::Visit(GridRefManager<NPC> &m) { apply(m); }
void GridExecuteSkillInCell::Visit(GridRefManager<Player> &m) { apply(m); }
void GridExecuteSkillInCell::Visit(GridRefManager<Elemental> &m) { apply(m); }
void GridExecuteSkillInCell::Visit(GridRefManager<Homunculus> &m) { apply(m); }
void GridExecuteSkillInCell::Visit(GridRefManager<Mercenary> &m) { apply(m); }
void GridExecuteSkillInCell::Visit(GridRefManager<Pet> &m) { apply(m); }
void GridExecuteSkillInCell::Visit(GridRefManager<Monster> &m) { apply(m); }
void GridExecuteSkillInCell::Visit(GridRefManager<Skill> &m) { apply(m); }

template <class T>
void GridEntitySkillUseNotifier::notify(GridRefManager<T> &m)
{
    using namespace Horizon::Zone::Entities;

    if (!m.get_size())
        return;

    std::shared_ptr<Horizon::Zone::Entity> src_entity = _entity.lock();

    for (typename GridRefManager<T>::iterator iter = m.begin(); iter != typename GridRefManager<T>::iterator(nullptr); ++iter) {
        if (iter->source() == nullptr)
            continue;

        std::shared_ptr<Player> tpl = iter->source()->template downcast<Player>();

        if (tpl->get_session() == nullptr || tpl->get_session()->clif() == nullptr)
            continue;

        switch (_notification_type)
        {
            case GRID_ENTITY_SKILL_USE_NOTIFY_CASTTIME:
            {
                tpl->get_session()->clif()->notify_skill_cast(_config.skill_id, _config.source_guid, _config.target_guid, _config.target_x, _config.target_y, _config.element, _config.cast_time);
            }
                break;
            case GRID_ENTITY_SKILL_USE_NOTIFY_SUCCESS_DAMAGE:
            {
                tpl->get_session()->clif()->notify_hostile_skill_use(
                    _config.skill_id, 
                    _config.source_guid, 
                    _config.target_guid, 
                    _config.start_time,
                    _config.attack_motion,
                    _config.delay_motion,
                    _config.damage_value, 
                    _config.display_value,
                    _config.number_of_hits,
                    _config.action_type);
            }
                break;
            case GRID_ENTITY_SKILL_USE_NOTIFY_SUCCESS_NO_DAMAGE:
            {
                tpl->get_session()->clif()->notify_safe_skill_use(_config.skill_id, _config.display_value, _config.target_guid, ZC_USESKILL2_SUCCESS);
            }
                break;
            default:
                HLog(warning) << "GridEntitySkillUseNotifier::notify: Unknown notification type: " << _notification_type << "." << std::endl;
                break;
        }
    }
}

void GridEntitySkillUseNotifier::Visit(GridRefManager<Player> &m) { notify<Player>(m); }
template <> void GridEntitySkillUseNotifier::Visit<NPC>(GridRefManager<NPC> &m);
template <> void GridEntitySkillUseNotifier::Visit<Elemental>(GridRefManager<Elemental> &m);
template <> void GridEntitySkillUseNotifier::Visit<Homunculus>(GridRefManager<Homunculus> &m);
template <> void GridEntitySkillUseNotifier::Visit<Mercenary>(GridRefManager<Mercenary> &m);
template <> void GridEntitySkillUseNotifier::Visit<Pet>(GridRefManager<Pet> &m);
template <> void GridEntitySkillUseNotifier::Visit<Monster>(GridRefManager<Monster> &m);
template <> void GridEntitySkillUseNotifier::Visit<Skill>(GridRefManager<Skill> &m);


template <class T>
void GridEntityBasicAttackNotifier::notify(GridRefManager<T> &m)
{
    using namespace Horizon::Zone::Entities;

    if (!m.get_size())
        return;

    std::shared_ptr<Horizon::Zone::Entity> src_entity = _entity.lock();

    for (typename GridRefManager<T>::iterator iter = m.begin(); iter != typename GridRefManager<T>::iterator(nullptr); ++iter) {
        if (iter->source() == nullptr)
            continue;

        std::shared_ptr<Player> tpl = iter->source()->template downcast<Player>();

        if (tpl->get_session() == nullptr || tpl->get_session()->clif() == nullptr)
            continue;

        tpl->get_session()->clif()->notify_damage(_config.guid, _config.target_guid, _config.start_time, _config.delay_skill,
            _config.delay_damage, _config.damage, _config.is_sp_damaged, _config.number_of_hits, _config.action_type, _config.left_damage);
    }
}

void GridEntityBasicAttackNotifier::Visit(GridRefManager<Player> &m) { notify<Player>(m); }
template <> void GridEntityBasicAttackNotifier::Visit<NPC>(GridRefManager<NPC> &m);
template <> void GridEntityBasicAttackNotifier::Visit<Elemental>(GridRefManager<Elemental> &m);
template <> void GridEntityBasicAttackNotifier::Visit<Homunculus>(GridRefManager<Homunculus> &m);
template <> void GridEntityBasicAttackNotifier::Visit<Mercenary>(GridRefManager<Mercenary> &m);
template <> void GridEntityBasicAttackNotifier::Visit<Pet>(GridRefManager<Pet> &m);
template <> void GridEntityBasicAttackNotifier::Visit<Monster>(GridRefManager<Monster> &m);
template <> void GridEntityBasicAttackNotifier::Visit<Skill>(GridRefManager<Skill> &m);

