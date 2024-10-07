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

#include "PersistenceManager.hpp"
#include "Server/Zone/Zone.hpp"
#include <thread>

#if WIN32
	#include <Windows.h>
#elif __linux__
	#include <sched.h>
#endif

using namespace Horizon::Zone;

PersistenceManager::PersistenceManager()
: KernelComponent(sZone, Horizon::System::RUNTIME_PERSISTENCE),
_resource_manager(PrimaryResource(RESOURCE_PRIORITY_PRIMARY, std::make_shared<s_segment_storage<uint64_t, std::shared_ptr<Units::Player>>>()))
{
}

void PersistenceManager::initialize(int segment_number)
{
	set_segment_number(segment_number);
	_thread = std::thread(&PersistenceManager::start, this);

	_is_initialized.exchange(true);
}

void PersistenceManager::finalize()
{
	if (_thread.joinable())
	    _thread.join();
    
	_is_finalized.exchange(true);
}

void PersistenceManager::start()
{
	while (!sZone->general_conf().is_test_run_minimal() && get_shutdown_stage() == SHUTDOWN_NOT_STARTED) {
		update(std::time(nullptr));
		std::this_thread::sleep_for(std::chrono::microseconds(MAX_CORE_UPDATE_INTERVAL));
	}
}

void PersistenceManager::update(uint64_t diff)
{
	std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
	get_system_routine_manager().process_queue();
#if WIN32
	DWORD cpu = GetCurrentProcessorNumber();
	if (get_thread_cpu_id() != (int) cpu) 
		set_thread_cpu_id(cpu);
#elif __linux__
	int cpu = sched_getcpu();
	if (get_thread_cpu_id() != cpu)
		set_thread_cpu_id(cpu);
#endif
	calculate_and_set_cpu_load();
	std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
	std::chrono::nanoseconds time_span = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
	set_total_execution_time(time_span.count());
}