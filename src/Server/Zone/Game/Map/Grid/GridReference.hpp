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

#ifndef HORIZON_ZONE_GAME_GRIDREFERENCE_HPP
#define HORIZON_ZONE_GAME_GRIDREFERENCE_HPP

#include "Core/Structures/LinkedList/ReferenceList/Reference.hpp"

//! @brief Forward declaration of GridRefManager, the class that manages GridReference.
template <class OBJECT>
class GridRefManager;

//! @brief GridReference is a reference to an object in GridRefManager. It is used to link objects.
//! @tparam OBJECT The type of object to be linked.
template <class OBJECT>
class GridReference : public Horizon::Structures::LinkedList::Reference<GridRefManager<OBJECT>, OBJECT>
{
public:
    GridReference() : Horizon::Structures::LinkedList::Reference<GridRefManager<OBJECT>, OBJECT>()
    {
    	//
    }

    ~GridReference() override { this->remove(); }

    GridReference *next()
    {
    	return static_cast<GridReference *>(Horizon::Structures::LinkedList::Reference<GridRefManager<OBJECT>, OBJECT>::next());
    }

protected:
    void target_object_build_link() override
    {
        // called from link()
        this->target()->push_front(this);
        this->target()->inc_size();
    }

    void target_object_destroy_link() override
    {
        // called from erase()
        if (this->is_valid())
        	this->target()->dec_size();
    }

    void source_object_destroy_link() override
    {
        // called from invalidate()
        this->target()->dec_size();
    }
};

#endif /* HORIZON_ZONE_GAME_GRIDREFERENCE_HPP */
