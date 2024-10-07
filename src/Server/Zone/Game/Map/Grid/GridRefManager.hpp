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

#ifndef HORIZON_ZONE_GAME_GRIDREFMANAGER_HPP
#define HORIZON_ZONE_GAME_GRIDREFMANAGER_HPP

#include "Core/Structures/LinkedList/ReferenceList/RefManager.hpp"
#include "Core/Structures/LinkedList/ReferenceList/Reference.hpp"
#include "GridReference.hpp"

//! @brief GridRefManager is a manager for GridReference. It is used to link objects and iterate through them.
//! @tparam OBJECT The type of object to be linked.
template <class OBJECT>
class GridRefManager : public Horizon::Structures::LinkedList::RefManager<GridRefManager<OBJECT>, OBJECT>
{
public:
	typedef Horizon::Structures::LinkedList::Head::Iterator<GridReference<OBJECT>> iterator;

	GridReference<OBJECT> *first()
	{
		return static_cast<GridReference<OBJECT> *> (Horizon::Structures::LinkedList::RefManager<GridRefManager<OBJECT>, OBJECT>::first());
	}
	GridReference<OBJECT> const *first() const
	{
		return static_cast<GridReference<OBJECT> const *> (Horizon::Structures::LinkedList::RefManager<GridRefManager<OBJECT>, OBJECT>::first());
	}

	iterator begin() { return iterator(first()); }
};

#endif /* HORIZON_ZONE_GAME_GRIDREFMANAGER_HPP */
