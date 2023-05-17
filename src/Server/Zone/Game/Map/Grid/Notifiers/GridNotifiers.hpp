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

#undef entity_ns

#endif /* HORIZON_ZONE_GAME_MAP_GRIDNOTIFIERS_HPP */
