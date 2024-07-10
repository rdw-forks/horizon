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

#ifndef HORIZON_ZONE_GAME_GAMELOGICPROCESS_HPP
#define HORIZON_ZONE_GAME_GAMELOGICPROCESS_HPP

#include "Server/Common/System.hpp"
#include "Server/Zone/Game/Map/MapManager.hpp"

namespace Horizon
{
namespace Zone
{
class GameLogicProcess : public MainframeComponent
{
public:
	GameLogicProcess() : MainframeComponent(Horizon::System::RUNTIME_GAMELOGIC) { }
    void initialize(int segment_number = 1);
    void finalize(int segment_number = 1);

    MapManager &get_map_process() { return _map_manager; }

	bool is_initialized() { return _is_initialized.load(); }
    
protected:
    MapManager _map_manager;
    std::atomic<bool> _is_initialized;
};
}
}

#endif /* HORIZON_ZONE_GAME_GAMELOGICPROCESS_HPP */