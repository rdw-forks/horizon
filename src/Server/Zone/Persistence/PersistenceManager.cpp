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

#include "PersistenceManager.hpp"
#include "Server/Zone/Zone.hpp"
#include <thread>

using namespace Horizon::Zone;

void PersistenceManager::initialize()
{
	_thread = std::thread(&PersistenceManager::start, this);
}

void PersistenceManager::finalize()
{
    _thread.join();
    
    bool value = _is_initialized;
	_is_initialized.compare_exchange_strong(value, false);
}

void PersistenceManager::start()
{
    bool value = _is_initialized;
	_is_initialized.compare_exchange_strong(value, true);
	
	while (!sZone->general_conf().is_test_run() && get_shutdown_stage() == SHUTDOWN_NOT_STARTED) {
		update(std::time(nullptr));
	}
}

void PersistenceManager::update(uint64_t diff)
{
	
}