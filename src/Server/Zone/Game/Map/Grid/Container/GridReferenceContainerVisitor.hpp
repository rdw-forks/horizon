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
 *  (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 **************************************************/

#ifndef HORIZON_CORE_STRUCTURES_GRIDREFERENCECONTAINERVISITOR_HPP
#define HORIZON_CORE_STRUCTURES_GRIDREFERENCECONTAINERVISITOR_HPP

#include "Server/Zone/Game/Map/Grid/Container/GridReferenceContainer.hpp"

/*============================*
 * Visitor Helper Functions
 *============================*/
template<class VISITOR>
void VisitorHelper(VISITOR &/*v*/, GridTypeListContainer<TypeNull> &/*c*/)
{
	// terminate condition container map list
}

template<class VISITOR, class T>
void VisitorHelper(VISITOR &v, GridTypeListContainer<T> &c)
{
	v.Visit(c._element);
}

// recursion container map list
template<class VISITOR, class H, class T>
void VisitorHelper(VISITOR &v, GridTypeListContainer<TypeList<H, T>> &c)
{
	VisitorHelper(v, c._elements);
	VisitorHelper(v, c._tail_elements);
}

// for GridReferenceContainer
template<class VISITOR, class OBJECT_TYPES>
void VisitorHelper(VISITOR &v, GridReferenceContainer<OBJECT_TYPES> &c)
{
	VisitorHelper(v, c.getElements());
}

/*============================*
 * TypeContainerVisitor
 *============================*/
template<class VISITOR, class TYPE_CONTAINER>
class GridReferenceContainerVisitor
{
public:
	GridReferenceContainerVisitor(VISITOR &v) : _visitor(v) { }

	void Visit(TYPE_CONTAINER &c)
	{
		VisitorHelper(_visitor, c);
	}

	void Visit(const TYPE_CONTAINER &c) const
	{
		VisitorHelper(_visitor, c);
	}

private:
	VISITOR &_visitor;
};

#endif /* HORIZON_CORE_STRUCTURES_GRIDREFERENCECONTAINERVISITOR_HPP */
