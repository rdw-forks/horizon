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
 * Base Author - Sagun Khosla <sagunxp@gmail.com>
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

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "SystemRoutinesTest"

#include <boost/test/unit_test.hpp>

#include <cstring>
#include <fstream>
#include <iostream>
#include <future>

#include "Server/Common/System.hpp"
#include "Core/Logging/Logger.hpp"

struct work_request
{
    int i{20};
};

class TestWork : public Horizon::System::RuntimeRoutineContext::Work<work_request>
{
public:
	TestWork(work_request req, std::shared_ptr<Horizon::System::RuntimeRoutineContext> context) : Work(req, context) { }

	void execute() { 
		using ResultType = Horizon::System::RuntimeRoutineContext::Result<int>;
		std::promise<ResultType> p;
		// Assuming this is the thread that will work on getting the result for either of the Mainframe Components...
		// We can use a promise / future combination of techniques to derive the final result.
		std::thread t = std::thread([&]()
		{ 
			std::cout << "Calculating..." << std::endl;
			p.set_value(ResultType(get_request().i * 20)); 
		});
		std::future<ResultType> f = p.get_future();
		set_result(std::make_shared<ResultType>(f.get())); 
		t.join();
	}
};

BOOST_AUTO_TEST_CASE(SystemRoutinesTest)
{
    Horizon::System::SystemRoutineManager srm;
    std::shared_ptr<Horizon::System::RuntimeRoutineContext> routine_1 = std::make_shared<Horizon::System::RuntimeRoutineContext>();

    work_request req;
    
	auto work = std::make_shared<TestWork>(work_request{ 20 }, routine_1);
	work->execute();
	while(!work->has_result());
    auto work2 = std::make_shared<Horizon::System::RuntimeRoutineContext::Work<work_request, int, int>>(work_request{30}, routine_1, work->get_result());
    auto work3 = std::make_shared<TestWork>(work_request{ 40 }, routine_1);
    auto work4 = std::make_shared<TestWork>(work_request{ 50 }, routine_1);
    
	routine_1->add_work(work2);
	routine_1->add_work(work3);
	routine_1->add_work(work4);
    
	srm.push(routine_1);
    srm.process_queue();

	BOOST_CHECK_EQUAL(work->get_result()->get_one(), 400);
	BOOST_CHECK_EQUAL(work2->get_result()->get_one(), 600);
	BOOST_CHECK_EQUAL(work3->get_result()->get_one(), 800);
	BOOST_CHECK_EQUAL(work4->get_result()->get_one(), 1000);
}

BOOST_AUTO_TEST_CASE(RuntimeRoutineContextChainTest)
{
    Horizon::System::SystemRoutineManager srm;
	std::shared_ptr<Horizon::System::RuntimeRoutineContextChain> chain_1 = std::make_shared<Horizon::System::RuntimeRoutineContextChain>();

    std::shared_ptr<Horizon::System::RuntimeRoutineContext> routine_1 = std::make_shared<Horizon::System::RuntimeRoutineContext>();
    std::shared_ptr<Horizon::System::RuntimeRoutineContext> routine_2 = std::make_shared<Horizon::System::RuntimeRoutineContext>();

    work_request req;
    
	auto work = std::make_shared<TestWork>(work_request{ 20 }, routine_1);
    auto work2 = std::make_shared<TestWork>(work_request{ 30 }, routine_1);
    auto work3 = std::make_shared<TestWork>(work_request{ 40 }, routine_1);
    auto work4 = std::make_shared<TestWork>(work_request{ 50 }, routine_1);
    
	routine_1->add_work(work);
	routine_1->add_work(work2);

	routine_2->add_work(work3);
	routine_2->add_work(work4);
    
	chain_1->push(routine_1);
	chain_1->push(routine_2);

	std::thread t = std::thread([&](){ chain_1->process(); });
	
	while (!work->has_result() || !work2->has_result() || !work3->has_result() || !work4->has_result());
	
	BOOST_CHECK_EQUAL(work->get_result()->get_one(), 400);
	BOOST_CHECK_EQUAL(work2->get_result()->get_one(), 600);
	BOOST_CHECK_EQUAL(work3->get_result()->get_one(), 800);
	BOOST_CHECK_EQUAL(work4->get_result()->get_one(), 1000);

	t.join();
}

BOOST_AUTO_TEST_CASE(SystemRoutinesUseResultTest)
{
    Horizon::System::SystemRoutineManager srm;
    std::shared_ptr<Horizon::System::RuntimeRoutineContext> routine_1 = std::make_shared<Horizon::System::RuntimeRoutineContext>();

    work_request req;
    
	auto work = std::make_shared<TestWork>(work_request{ 20 }, routine_1);
    auto work2 = std::make_shared<TestWork>(work_request{ 30 }, routine_1);
    
	routine_1->add_work(work);
	routine_1->add_work(work2);
    
	srm.push(routine_1);
    srm.process_queue();

	BOOST_CHECK_EQUAL(work->get_result()->get_one(), 400);
	BOOST_CHECK_EQUAL(work2->get_result()->get_one(), 600);
}