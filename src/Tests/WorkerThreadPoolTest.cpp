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
 * This is proprietary software. Unauthorized copying,
 * distribution, or modification of this file, via any
 * medium, is strictly prohibited. All rights reserved.
 **************************************************/


#define BOOST_TEST_MODULE "WorkerThreadPoolTest"

#include "Core/Multithreading/WorkerThreadPool.hpp"
#include <boost/test/unit_test.hpp>
#include <cstring>
#include <thread>
#include <cstdio>
#include <iostream>

int work_1(int num = 10)
{
	for (int i = 0; i < 100000000; i += num)
		;
	return num;
}

BOOST_AUTO_TEST_CASE(WorkerThreadPoolTest)
{
	WorkerThreadPool pool;

	for (int i = 0; i < 1000; i++) {
		std::function<int(int)> func = std::bind(work_1, 20);
		func(29);
	}
}
