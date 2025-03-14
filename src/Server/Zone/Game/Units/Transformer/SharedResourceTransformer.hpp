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

#ifndef HORIZON_ZONE_GAME_SHARED_RESOURCE_TRANSFORMER_HPP
#define HORIZON_ZONE_GAME_SHARED_RESOURCE_TRANSFORMER_HPP

namespace Horizon
{
namespace Zone
{
namespace Game
{
template <typename T>
class SharedGameResourceTransformer
{
public:
    SharedResourceTransformer(std::shared_ptr<T> transformation) : _transformation(transformation) { }
    ~SharedResourceTransformer() { }

private:
    std::shared_ptr<T> _transformation;
};

template <typename T>
class SharedResourceTransformationSaver : public SharedResourceTransformer
{
public:
    SharedResourceTransformationSaver() : SharedResourceTransformer()
    {

    }

    ~SharedResourceTransformationSaver() { }

    void prepare();
    void verify();
    void save();
};

template <typename T>
class SharedResourceTransformationLoader : public SharedResourceTransformer
{
public:
    SharedResourceTransformationLoader() : SharedResourceTransformer()
    {

    }

    ~SharedResourceTransformationLoader() { }

    void prepare();
    void verify();
    void load();
};
}
}
}

#endif /* HORIZON_ZONE_GAME_SHARED_RESOURCE_TRANSFORMER_HPP */