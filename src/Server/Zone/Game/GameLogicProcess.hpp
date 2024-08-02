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
#include "Server/Zone/Zone.hpp"
namespace Horizon
{
namespace Zone
{
class GameLogicProcess : public MainframeComponent
{
public:
	GameLogicProcess() 
	: MainframeComponent(Horizon::System::RUNTIME_GAMELOGIC),
	_resource_manager(
		PrimaryResource(SEGMENT_PRIORITY_PRIMARY, std::make_shared<s_segment_storage<std::string, std::shared_ptr<Map>>>()),
		SecondaryResource(SEGMENT_PRIORITY_SECONDARY, std::make_shared<s_segment_storage<uint64_t, std::shared_ptr<Units::Player>>>())
	)
	{
	}
    void initialize(int segment_number = 1);
    void finalize();

	bool is_initialized() override { return _is_initialized.load(); }
	bool is_finalized() override { return _is_finalized.load(); }

	/* Map / Maps */
	bool load_map_cache();
	void start_containers();
	
	TaskScheduler &getScheduler() { return _scheduler; }

	void on_map_update(int64_t diff);

protected:
    std::atomic<bool> _is_initialized{false};
	std::atomic<bool> _is_finalized{false};
	
	using PrimaryResource = SharedPriorityResourceMedium<s_segment_storage<std::string /* Map Name */, std::shared_ptr<Map>>>;
	using SecondaryResource = SharedPriorityResourceMedium<s_segment_storage<uint64_t, std::shared_ptr<Units::Player>>>;
	using ResourceManager = SharedPriorityResourceManager<PrimaryResource, SecondaryResource>;
	ResourceManager _resource_manager;
public:
	ResourceManager &get_resource_manager() { return _resource_manager; }

private:
	TaskScheduler _scheduler;
	LockedLookupTable<int32_t, std::shared_ptr<MapContainerThread>> _map_containers;
	std::map<std::string, map_data> _maps;
};
}
}

#endif /* HORIZON_ZONE_GAME_GAMELOGICPROCESS_HPP */