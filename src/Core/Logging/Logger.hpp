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

#ifndef HORIZON_LOGGER_H
#define HORIZON_LOGGER_H

#define BOOST_LOG_DYN_LINK 1

#include <cstring>

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

class Logger
{
public:
    enum status_message_type {
        LOG_ERROR  = 31,
        LOG_INFO   = 36,
        LOG_DEBUG  = 91
    };

private:
    typedef boost::log::sources::severity_logger<boost::log::trivial::severity_level> logtype;

public:
	Logger();
	~Logger();

	static Logger *getInstance()
	{
		static Logger instance;

        if (!instance._initialized)
            instance.initialize();
        
		return &instance;
	}

    void initialize();
    
    logtype &get_core_log() { return _core_log; }
    
    void colored_formatter(boost::log::record_view const& rec, boost::log::formatting_ostream& strm);
    std::string color(uint16_t color);

protected:
    logtype _core_log;
    std::atomic<bool> _initialized;

};

#define HLog(type) BOOST_LOG_SEV(Logger().getInstance()->get_core_log(), boost::log::trivial::type)

#endif //HORIZON_LOGGER_H
