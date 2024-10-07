/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 * Copyright (c) 2019 Sagun K. (sagunxp@gmail.com).
 * Copyright (c) 2019 Horizon Dev Team.
 *
 * Base Author - Sagun K. (sagunxp@gmail.com)
 *
 * This is proprietary software. Unauthorized copying,
 * distribution, or modification of this file, via any
 * medium, is strictly prohibited. All rights reserved.
 **************************************************/

#ifndef HORIZON_ZONE_UNIT_LUA_COMPONENT_HPP
#define HORIZON_ZONE_UNIT_LUA_COMPONENT_HPP

#include "Server/Zone/Script/Components/LUAComponent.hpp"

namespace Horizon
{
namespace Zone
{
class GameLogicProcess;
class UnitComponent : public LUAComponent
{
public:
    UnitComponent() { }
    UnitComponent(std::shared_ptr<GameLogicProcess> container) : LUAComponent(container) { }
    ~UnitComponent() { }

    void sync_definitions(std::shared_ptr<sol::state> state);
    void sync_data_types(std::shared_ptr<sol::state> state);
    void sync_functions(std::shared_ptr<sol::state> state);
};
}    
}

#endif /* HORIZON_ZONE_UNIT_LUA_COMPONENT_HPP */
