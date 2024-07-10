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
#include <memory>

#include "Server/Common/System.hpp"
#include "Core/Logging/Logger.hpp"

struct work_request
{
    int i{20};
};

class TestWork : public Horizon::System::RuntimeRoutineContext::Work<work_request>
{
public:
	TestWork(work_request req) : Work(req) { }

	bool execute() { 
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

		return true;
	}
};

class TestWork2 : public Horizon::System::RuntimeRoutineContext::Work<work_request>
{
public:
	TestWork2(work_request req) : Work(req) { }

	bool execute() { 
		using ResultType = Horizon::System::RuntimeRoutineContext::Result<int>;
		std::promise<ResultType> p;
		// Assuming this is the thread that will work on getting the result for either of the Mainframe Components...
		// We can use a promise / future combination of techniques to derive the final result.
		std::thread t = std::thread([&]()
		{ 
			std::cout << "Calculating 2..." << std::endl;
			p.set_value(ResultType(get_request().i * 10)); 
		});
		std::future<ResultType> f = p.get_future();
		set_result(std::make_shared<ResultType>(f.get())); 
		t.join();

		return true;
	}
};

BOOST_AUTO_TEST_CASE(SystemRoutinesTest)
{
    Horizon::System::SystemRoutineManager srm(Horizon::System::RUNTIME_MAIN);
    std::shared_ptr<Horizon::System::RuntimeRoutineContext> routine_1 = std::make_shared<Horizon::System::RuntimeRoutineContext>(srm, Horizon::System::RUNTIME_SYNC_NONE);

    work_request req;
    
	auto work = std::make_shared<TestWork>(work_request{ 20 });
	work->execute();
	while(!work->has_result());
    auto work2 = std::make_shared<Horizon::System::RuntimeRoutineContext::Work<work_request, int, int>>(work_request{30}, work->get_result());
    auto work3 = std::make_shared<TestWork2>(work_request{ 40 });
    auto work4 = std::make_shared<TestWork>(work_request{ 50 });
    
	routine_1->push(work2);
	routine_1->push(work3);
	routine_1->push(work4);
    
	srm.push(routine_1);
    srm.process_queue();

	BOOST_CHECK_EQUAL(work->get_result()->get_one(), 400);
	BOOST_CHECK_EQUAL(work2->get_result()->get_one(), 600);
	BOOST_CHECK_EQUAL(work3->get_result()->get_one(), 400);
	BOOST_CHECK_EQUAL(work4->get_result()->get_one(), 1000);
}

BOOST_AUTO_TEST_CASE(RuntimeRoutineContextChainTest)
{
    Horizon::System::SystemRoutineManager srm(Horizon::System::RUNTIME_MAIN);
	std::shared_ptr<Horizon::System::RuntimeContextChain> chain_1 = std::make_shared<Horizon::System::RuntimeContextChain>(Horizon::System::RUNTIME_MAIN);

    std::shared_ptr<Horizon::System::RuntimeRoutineContext> routine_1 = std::make_shared<Horizon::System::RuntimeRoutineContext>(srm, Horizon::System::RUNTIME_SYNC_NONE);
    std::shared_ptr<Horizon::System::RuntimeRoutineContext> routine_2 = std::make_shared<Horizon::System::RuntimeRoutineContext>(srm, Horizon::System::RUNTIME_SYNC_NONE);

    work_request req;
    
	auto work = std::make_shared<TestWork>(work_request{ 20 });
    auto work2 = std::make_shared<TestWork>(work_request{ 30 });
    auto work3 = std::make_shared<TestWork>(work_request{ 40 });
    auto work4 = std::make_shared<TestWork>(work_request{ 50 });
    
	routine_1->push(work);
	routine_1->push(work2);

	routine_2->push(work3);
	routine_2->push(work4);
    
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

BOOST_AUTO_TEST_CASE(SystemRoutinesDispatchTest)
{
    Horizon::System::SystemRoutineManager srm(Horizon::System::RUNTIME_MAIN);
    Horizon::System::SystemRoutineManager srm_gl(Horizon::System::RUNTIME_GAMELOGIC);
    Horizon::System::SystemRoutineManager srm_p(Horizon::System::RUNTIME_PERSISTENCE);
    std::shared_ptr<Horizon::System::RuntimeRoutineContext> routine_1 = std::make_shared<Horizon::System::RuntimeRoutineContext>(srm, Horizon::System::RUNTIME_SYNC_NONE);
	std::shared_ptr<Horizon::System::RuntimeRoutineContext> routine_2 = std::make_shared<Horizon::System::RuntimeRoutineContext>(srm_gl, Horizon::System::RUNTIME_SYNC_WAIT_CHECK_STATE);
	std::shared_ptr<Horizon::System::RuntimeRoutineContext> routine_3 = std::make_shared<Horizon::System::RuntimeRoutineContext>(srm_p, Horizon::System::RUNTIME_SYNC_WAIT_CHECK_STATE);
    work_request req;
    
	auto work = std::make_shared<TestWork>(work_request{ 20 });
	work->execute();
	while(!work->has_result());
    auto work2 = std::make_shared<Horizon::System::RuntimeRoutineContext::Work<work_request, int, int>>(work_request{30}, work->get_result());
    auto work3 = std::make_shared<TestWork2>(work_request{ 40 });
    auto work4 = std::make_shared<TestWork>(work_request{ 50 });
    
	routine_1->push(work2);
	routine_1->push(work3);
	routine_1->push(work4);
    
	auto work_gl_1 = std::make_shared<Horizon::System::RuntimeRoutineContext::Work<work_request, int, int>>(work_request{30}, work->get_result());

	routine_2->push(work_gl_1);
    
	auto work_p_1 = std::make_shared<Horizon::System::RuntimeRoutineContext::Work<work_request, int, int>>(work_request{30}, work->get_result());

	routine_3->push(work_p_1);

	srm.push(routine_1);
	srm.push(routine_2);
	srm.push(routine_3);

	std::thread thread_1 = std::thread([&](){
	    srm.process_queue(); 
	});
	
	std::cout << "Work 1 to 4 Executed on Thread 1." << std::endl;

	std::thread thread_2 = std::thread([&]() { 
		while(!work_gl_1->has_result()) { srm_gl.process_queue(); }
		std::cout << "Work_GL_1 Executed on Thread 2." << std::endl; 
	});
	
	std::thread thread_3 = std::thread([&]() { 
		while(!work_p_1->has_result()) { srm_p.process_queue(); }
		std::cout << "Work_P_1 Executed on Thread 3." << std::endl; 
	});

	while (!(work->has_result() && work2->has_result() && work3->has_result() && work4->has_result() && work_gl_1->has_result() && work_p_1->has_result()));

	BOOST_CHECK_EQUAL(work->get_result()->get_one(), 400);
	BOOST_CHECK_EQUAL(work2->get_result()->get_one(), 600);
	BOOST_CHECK_EQUAL(work3->get_result()->get_one(), 400);
	BOOST_CHECK_EQUAL(work4->get_result()->get_one(), 1000);
	BOOST_CHECK_EQUAL(work_gl_1->get_result()->get_one(), 600);
	BOOST_CHECK_EQUAL(work_p_1->get_result()->get_one(), 600);

	thread_1.join();
	thread_2.join();
	thread_3.join();
}