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
#include "Server/Auth/Auth.hpp"

#define BOOST_TEST_MODULE AuthServerTest
#include <boost/test/included/unit_test.hpp>
#include <boost/asio/deadline_timer.hpp>

void function_timer(const boost::system::error_code& e)
{
	std::cout << "Timer executed" << std::endl;
	if(e)
	{
		std::cerr << "Error: " << e.message() << std::endl;
	}
}

BOOST_AUTO_TEST_CASE(AuthServerIOContextTest)
{
	try {
		boost::asio::deadline_timer timer(sAuth->get_io_context());

		timer.expires_from_now(boost::posix_time::seconds(1));
		timer.async_wait(std::bind(&function_timer, boost::asio::placeholders::error));

		sAuth->get_io_context().run();
		sAuth->get_io_context().stop();
	} catch(std::length_error &e) {
		std::cerr << "Exception caught: " << e.what() << std::endl;
	} catch(std::bad_alloc &e) {
		std::cerr << "Exception caught: " << e.what() << std::endl;
	} catch(std::exception &e) {
		std::cerr << "Exception caught: " << e.what() << std::endl;
	} catch(...) {
		std::cerr << "Unknown exception caught." << std::endl;
	}
}


BOOST_AUTO_TEST_CASE(AuthServerTest)
{
	try {
		std::thread thread = std::thread([&]() {
			sAuth->general_conf().set_test_run(TEST_RUN_MINIMAL);

			sAuth->general_conf().set_config_file_path("config/auth-server.lua.dist");
			sAuth->read_config();
			set_shutdown_signal(SHUTDOWN_INITIATED);
			sAuth->initialize_core();
		});
		thread.join();
		HLogShutdown;
	} catch(std::length_error &e) {
		std::cerr << "Exception caught: " << e.what() << std::endl;
	} catch(std::bad_alloc &e) {
		std::cerr << "Exception caught: " << e.what() << std::endl;
	} catch(std::exception &e) {
		std::cerr << "Exception caught: " << e.what() << std::endl;
	} catch(...) {
		std::cerr << "Unknown exception caught." << std::endl;
	}
}