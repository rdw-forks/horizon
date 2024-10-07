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