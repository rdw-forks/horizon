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

#ifndef HORIZON_ZONE_PERSISTENCE_PERSISTENCEMANAGER
#define HORIZON_ZONE_PERSISTENCE_PERSISTENCEMANAGER
#include "Server/Common/System.hpp"
#include "Server/Common/Server.hpp"


namespace Horizon
{
namespace Zone
{
	namespace Units
	{
		class Player;
	}
class PersistenceManager : public MainframeComponent
{
public:
	PersistenceManager() 
	: MainframeComponent(Horizon::System::RUNTIME_PERSISTENCE),
	_resource_manager(PrimaryResource(SEGMENT_PRIORITY_PRIMARY, std::make_shared<s_segment_storage<uint64_t, std::shared_ptr<Units::Player>>>()))
	{
	}
    void initialize(int segment_number = 1);
    void finalize();
    void start();
    void update(uint64_t diff);

	bool is_initialized() { return _is_initialized.load(); }
    
private:
    std::thread _thread;
	std::atomic<bool> _is_initialized;

protected:
	using PrimaryResource = SharedPriorityResourceMedium<s_segment_storage<uint64_t, std::shared_ptr<Units::Player>>>;
	using ResourceManager = SharedPriorityResourceManager<PrimaryResource>;
	ResourceManager _resource_manager;
};
}
}
#endif /* HORIZON_ZONE_PERSISTENCE_PERSISTENCEMANAGER */