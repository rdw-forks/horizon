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
#include "Utility/TaskScheduler.hpp"
#include "MapContainerThread.hpp"
#include "Libraries/MapCache/MapCache.hpp"
#include "Libraries/Networking/Buffer/ByteBuffer.hpp"

namespace Horizon
{
namespace Zone
{
class GameLogicProcess : public MainframeComponent
{
public:
	GameLogicProcess() : MainframeComponent(Horizon::System::RUNTIME_GAMELOGIC) { }
    void initialize(int segment_number = 1);
    void finalize();

	bool is_initialized() { return _is_initialized.load(); }

	/* Map / Maps */
	bool manage_session_in_map(map_container_session_action action, std::string map_name, std::shared_ptr<ZoneSession> s);
	bool load_map_cache();
	void start_containers();
	
	TaskScheduler &getScheduler() { return _scheduler; }

	void on_map_update(int64_t diff);

protected:
    std::atomic<bool> _is_initialized;
private:
	TaskScheduler _scheduler;
	LockedLookupTable<int32_t, std::shared_ptr<MapContainerThread>> _map_containers;
	std::map<std::string, map_data> _maps;
};
}
}

#endif /* HORIZON_ZONE_GAME_GAMELOGICPROCESS_HPP */