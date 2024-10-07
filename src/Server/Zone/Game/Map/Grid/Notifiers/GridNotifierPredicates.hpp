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

#ifndef HORIZON_ZONE_GAME_MAP_GRIDNOTIFIERPREDICATES_HPP
#define HORIZON_ZONE_GAME_MAP_GRIDNOTIFIERPREDICATES_HPP

#include "Server/Zone/Game/Units/Unit.hpp"
#include "Server/Zone/Game/Map/Grid/GridDefinitions.hpp"

class GUIDCheckPredicate
{
public:
	GUIDCheckPredicate(uint32_t guid) : _guid(guid) { }

	bool operator()(std::weak_ptr<Horizon::Zone::Unit> unit)
	{
		return !unit.expired() && ((unit.lock())->guid() == _guid);
	}

private:
	uint32_t _guid;
};

class RangeCheckPredicate
{
public:
	RangeCheckPredicate(std::weak_ptr<Horizon::Zone::Unit> source)
	: _source(source){ }

	bool operator()(std::weak_ptr<Horizon::Zone::Unit> target, uint16_t range = MAX_VIEW_RANGE)
	{
		return !_source.expired() && !target.expired() && _source.lock()->is_in_range_of(target.lock(), range);
	}

private:
	std::weak_ptr<Horizon::Zone::Unit> _source;
};

class AOETargetTypePredicate
{
public:
	AOETargetTypePredicate(int aoe_target_mask)
	: _aoe_target_mask(aoe_target_mask){ }

	bool operator()(std::weak_ptr<Horizon::Zone::Unit> target)
	{
		return !target.expired() && (target.lock())->is_of_type(_aoe_target_mask);
	}

private:
	int _aoe_target_mask{ 0 };
};

class CellCheckPredicate
{
public:
	CellCheckPredicate(MapCoords cell)
	: _cell(cell){ }

	bool operator()(MapCoords cell)
	{
		return cell == _cell;
	}

private:
	MapCoords _cell{ 0, 0 };
};

#endif /* GRIDNOTIFIERPREDICATES_HPP */
