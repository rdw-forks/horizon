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


#define BOOST_TEST_MODULE "ObservableStatusTest"

#include <boost/test/unit_test.hpp>

#include <cstring>
#include <fstream>
#include <memory>

#include "Server/Zone/Game/Units/Traits/ObservableStatus.hpp"

class B;
class C;

class D
{
public:
	D(int a) : _a(a) { }
	int _a;
};

class A : public D, public ObservableStatus<A*, B*, C*>
{
public:
	A(int a = 100) : D(a), ObservableStatus(nullptr, nullptr) { }
};

class C : public D
{
public:
	C(int a = 10) : D(a) { }

	void on_observable_changed(A *a)
	{
		_a = a->_a;
	}
};

class B : public D
{
public:
	B(int a = 20) : D(a) { }

	void on_observable_changed(A *a)
	{
		_a = a->_a;
	}
};

/**
 * @brief This is a powerful templated Observer Pattern using pointers.
 * The goal of the this test is to simply notify the observers of
 * the observable's state and update accordingly.
 * @author Sagun Khosla <sagunxp@gmail.com
 */
BOOST_AUTO_TEST_CASE(ObservableStatusTest)
{
	A *a = new A();
	B *b = new B();
	C *c = new C();

	a->register_observable(a);
	a->register_observers(b, c);

	BOOST_CHECK_NE(a->_a, b->_a);
	BOOST_CHECK_NE(a->_a, c->_a);

	a->notify_observers();

	BOOST_CHECK_EQUAL(a->_a, b->_a);
	BOOST_CHECK_EQUAL(a->_a, c->_a);

	delete a;
	delete b;
	delete c;
}

