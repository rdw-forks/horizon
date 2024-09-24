a/***************************************************
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

#ifndef HORIZON_SERVER_DEFINITIONS
#define HORIZON_SERVER_DEFINITIONS

#include <boost/log/trivial.hpp>
#include <boost/log/sources/severity_logger.hpp>

#define MainLog(type) BOOST_LOG_SEV(get_core_log(), boost::log::trivial::type)
#define HLog(type) BOOST_LOG_SEV(this->get_core_log(), boost::log::trivial::type)

#endif /* HORIZON_SERVER_DEFINITIONS */