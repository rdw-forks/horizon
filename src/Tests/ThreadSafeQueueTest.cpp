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


#define BOOST_TEST_MODULE "ThreadSafeQueueTest"

#include "Core/Multithreading/ThreadSafeQueue.hpp"
#include <boost/test/unit_test.hpp>
#include <cstring>
#include <thread>
#include <atomic>

#define MAX_PUSHES 1000000

BOOST_AUTO_TEST_CASE(ThreadSafeQueueTest)
{
	ThreadSafeQueue<int> queue;
	std::thread *t[4];
	std::atomic<bool> go;

	for (int i = 0; i < MAX_PUSHES; i++)
		queue.push(std::move(i));

	BOOST_CHECK_EQUAL(queue.size(), MAX_PUSHES);

	t[0] = new std::thread([&queue, &go]() {
		while (!go);
		for (int i = 0; i < MAX_PUSHES; i++)
			queue.push(std::move(i));
	});

	t[1] = new std::thread([&queue, &go]() {
		while (!go);
		for (int i = 0; i < MAX_PUSHES; i++)
			queue.push(std::move(i));
	});

	t[2] = new std::thread([&queue, &go]() {
		while (!go);
		for (int i = 0; i < MAX_PUSHES; i++)
			queue.try_pop();
	});

	t[3] = new std::thread([&queue, &go]() {
		while (!go);
		for (int i = 0; i < MAX_PUSHES; i++)
			queue.try_pop();
	});

	go.exchange(true);

	t[0]->join();
	t[1]->join();
	t[2]->join();
	t[3]->join();

	delete t[0];
	delete t[1];
	delete t[2];
	delete t[3];

	BOOST_CHECK_EQUAL(queue.size(), MAX_PUSHES);
}
