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

#ifndef HORIZON_CORE_STRUCTURES_GRIDREFERENCECONTAINER_HPP
#define HORIZON_CORE_STRUCTURES_GRIDREFERENCECONTAINER_HPP

#include "Core/Structures/TypeList.hpp"
#include "Server/Zone/Game/Map/Grid/GridRefManager.hpp"

/*============================*
 * Container Data Type
 *============================*/
template<class OBJECT>
struct GridTypeListContainer
{
	GridRefManager<OBJECT> _element;
};

template<>
struct GridTypeListContainer<TypeNull>
{
};

template<class HEAD, class TAIL>
struct GridTypeListContainer<TypeList<HEAD, TAIL>>
{
	GridTypeListContainer<HEAD> _elements;
	GridTypeListContainer<TAIL> _tail_elements;
};

/*============================*
 * TypeListIterator Insert Functions
 *============================*/
// non-const insert functions
namespace GridTypeListIterator
{
	// Invoked in the condition that the SPECIFIC_TYPE has been visited.
	template<class SPECIFIC_TYPE>
	SPECIFIC_TYPE *Insert(GridTypeListContainer<SPECIFIC_TYPE> &elements, SPECIFIC_TYPE *obj)
	{
		obj->add_grid_reference(elements._element);
		return obj;
	}
	// Invoked in the condition that a TypeNull has been visited.
	template<class SPECIFIC_TYPE>
	SPECIFIC_TYPE *Insert(GridTypeListContainer<TypeNull> &/*elements*/, SPECIFIC_TYPE */*obj*/)
	{
		return nullptr;
	}
	// In a case such as the following, where the GridTypeListContainer is not one of the specific type
	// that we are in search of, the resulting return of the function is a nullptr. 
	template<class SPECIFIC_TYPE, class T>
	SPECIFIC_TYPE *Insert(GridTypeListContainer<T> &/*elements*/, SPECIFIC_TYPE */*obj*/)
	{
		return nullptr;
	}
	// In a condition such as the following where a GridTypeListContainer of a TypeList<HEAD, TAIL> is invoked,
	// and the specific object that is to be inserted is also a valid argument. The function definition matches the 
	// search criteria of the template function that is to be invoked. We try recursing to iterate through the TypeLists
	// contained in the GridTypeListContainer until a reference has been added or the end of the TypeList (TypeNull) is met and the 
	// appropriate function has been invoked to return a nullptr or a valid pointer to the object.
	template<class SPECIFIC_TYPE, class HEAD, class TAIL>
	SPECIFIC_TYPE* Insert(GridTypeListContainer<TypeList<HEAD, TAIL>> &elements, SPECIFIC_TYPE* obj)
	{
		SPECIFIC_TYPE *t = Insert(elements._elements, obj);
		return (t != nullptr ? t : Insert(elements._tail_elements, obj));
	}
/*============================*
 * TypeListIterator Count Functions
 *============================*/
	// Function for when the specific type has been invoked and the requirement of meeting the function
	// definition has been successful.
	template <class SPECIFIC_TYPE>
	size_t count(GridTypeListContainer<SPECIFIC_TYPE> const &elements, SPECIFIC_TYPE */*fake*/)
	{
		return elements._element.get_size();
	}
	// Function for when a TypeNull has been visited.
	template <class SPECIFIC_TYPE>
	size_t count(GridTypeListContainer<TypeNull> const &/*elements*/, SPECIFIC_TYPE */*fake*/)
	{
		return 0;
	}
	// Function containing any other type than the one we are in search of, will be invoked.
	template <class SPECIFIC_TYPE, class T>
	size_t count(GridTypeListContainer<T> const &/*elements*/, SPECIFIC_TYPE */*fake*/)
	{
		return 0;
	}
	// Invoked in the condition that the a TypeList of type <SPECIFIC_TYPE, T> has been met. 
	template <class SPECIFIC_TYPE, class T>
	size_t count(GridTypeListContainer<TypeList<SPECIFIC_TYPE, T>> const &elements, SPECIFIC_TYPE *fake)
	{
		return count(elements._elements, fake);
	}
	// Invoked in the condition that any other TypeList, the ones that are not of the SPECIFIC_TYPE we 
	// are in search of, has been met. All of the element types will be visited, invoking the count() function 
	// for the specific type we are in search of.
	template <class SPECIFIC_TYPE, class H, class T>
	size_t count(GridTypeListContainer<TypeList<H, T>> const &elements, SPECIFIC_TYPE *fake)
	{
		return count(elements._tail_elements, fake);
	}

	template <class TypeNull>
	size_t count_all(GridTypeListContainer<TypeNull> const &elements)
	{
		return 0;
	}

	// Counts all of the objects in a GridTypeListContainer.
	template <class H, class T>
	size_t count_all(GridTypeListContainer<TypeList<H, T>> const &elements)
	{
		return count(elements._elements, (H *) nullptr) + count_all(elements._tail_elements);
	}
}
/*============================*
 * GridReferenceContainer
 *============================*/
template<class OBJECT_TYPES>
class GridReferenceContainer
{
public:
	template <class SPECIFIC_TYPE>
	size_t count() const
	{
		return GridTypeListIterator::count(_elements, (SPECIFIC_TYPE *) nullptr);
	}

	size_t count_all() const
	{
		return GridTypeListIterator::count_all(_elements);
	}

	/// inserts a specific object into the container
	template <class SPECIFIC_TYPE>
	bool insert(SPECIFIC_TYPE *obj)
	{
		assert(obj && !obj->has_valid_grid_reference());
		SPECIFIC_TYPE* t = GridTypeListIterator::Insert(_elements, obj);
		return (t != nullptr);
	}

	GridTypeListContainer<OBJECT_TYPES> &getElements(void) { return _elements; }
	const GridTypeListContainer<OBJECT_TYPES> &getElements(void) const { return _elements;}

private:
	GridTypeListContainer<OBJECT_TYPES> _elements;
};

#endif /* HORIZON_CORE_STRUCTURES_GRIDREFERENCECONTAINER_HPP */
