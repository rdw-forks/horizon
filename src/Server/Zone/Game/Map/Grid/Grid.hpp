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

#ifndef HORIZON_ZONE_GAME_GRID_HPP
#define HORIZON_ZONE_GAME_GRID_HPP

#include "Container/GridReferenceContainer.hpp"
#include "Container/GridReferenceContainerVisitor.hpp"

//! @details Grid is used to store objects in a 2D grid. This is used to speed up the search for objects in a given area.
//! The grid is divided into cells of a given size. Each grid-cell contains a list of objects that are in that grid-cell.
//! The grid is actually stored in the GridHolder class.
//!	- The GridHolder class is a container for Grids.
//! - The Grid class is a container for objects.
//! - The GridReferenceContainer class is a container for objects in a grid-cell.
//! - The GridReferenceContainerVisitor class is used to visit the objects in a grid-cell.
//! @tparam ACTIVE_OBJECT is the object that is stored in the grid.
//! @tparam GRID_OBJECT_TYPES is a type-list of object types that are stored in the grid.
//! @param _container is the container for objects in the grid-cell.
template
<
	class GRID_OBJECT_TYPES
>
class Grid
{
public:
	template <class SPECIFIC_OBJECT>
	void add_object(SPECIFIC_OBJECT *obj)
	{
		_container.template insert<SPECIFIC_OBJECT>(obj);
		assert(obj->has_valid_grid_reference());
	}

	template <class VISITOR>
	void visit(GridReferenceContainerVisitor<VISITOR, GridReferenceContainer<GRID_OBJECT_TYPES>> &visitor)
	{
		visitor.Visit(_container);
	}

	/** Returns the number of object within the grid.
	 */
	template <class T>
	uint32_t getObjectCount() const { return uint32_t(_container.template count<T>()); }

	GridReferenceContainer<GRID_OBJECT_TYPES> _container;
};

#endif /* HORIZON_ZONE_GAME_GRID_HPP */
