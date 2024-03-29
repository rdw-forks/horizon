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

#ifndef HORIZON_AUTH_HPP
#define HORIZON_AUTH_HPP

#include "Server/pch.hpp"

#include "Common/Server.hpp"

namespace Horizon
{
namespace Auth
{
/**
 * Main Auth Server Singleton Class.
 */
struct auth_config_type {
	std::string _password_salt_mix;

	struct char_server
	{
	    std::string _name, _host;
	    uint16_t _port, _type, _is_new;  
	};

    void add_char_server(char_server c) { _char_servers.push_back(c); }
    std::vector<char_server> &get_char_servers() { return _char_servers; }

    std::vector<char_server> _char_servers;
};

class AuthServer : public Server
{
public:
	AuthServer();
	~AuthServer();

	static AuthServer *getInstance()
	{
		static AuthServer instance;
		return &instance;
	}

	bool read_config();

	void initialize_core();
	/* CLI */
	void initialize_cli_commands();
	bool clicmd_reload_config(std::string /*cmd*/);
	bool clicmd_create_new_account(std::string /*cmd*/);

	/* Task Scheduler */
	TaskScheduler &getScheduler() { return _task_scheduler; }
    
	auth_config_type &get_auth_config()
	{
		std::lock_guard<std::mutex> lock(_conf_lock);
		return _auth_config;
	}
	
	void update(uint64_t time);
	
protected:
	TaskScheduler _task_scheduler;
	std::mutex _conf_lock;
	auth_config_type _auth_config;
	boost::asio::deadline_timer _update_timer;

};
}
}

#define sAuth Horizon::Auth::AuthServer::getInstance()

#endif /* HORIZON_AUTH_HPP */
