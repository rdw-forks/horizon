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

#ifndef HORIZON_SERVER_HPP
#define HORIZON_SERVER_HPP

#include "CLI/CLICommand.hpp"
#include "Core/Database/ConnectionPool.hpp"

using boost::asio::ip::tcp;

extern enum shutdown_stages
{
	SHUTDOWN_NOT_STARTED      = 0,
	SHUTDOWN_INITIATED        = 1,
	SHUTDOWN_CLEANUP_COMPLETE = 2,
	SHUTDOWN_COMPLETE         = 3
};

extern std::atomic<shutdown_stages> _shutdown_stage;
extern std::atomic<int> _shutdown_signal;

extern inline void set_shutdown_signal(int signal) { _shutdown_signal.exchange(signal); }
extern inline shutdown_stages get_shutdown_stage() { return _shutdown_stage.load(); };
extern inline void set_shutdown_stage(shutdown_stages new_stage) { _shutdown_stage.exchange(new_stage); };

class CommandLineProcess
{
public:
	CommandLineProcess() { }
	~CommandLineProcess() { }

	void process();
	void queue(CLICommand &&cmdMgr) { _cli_cmd_queue.push(std::move(cmdMgr)); }
	void add_function(std::string cmd, std::function<bool(std::string)> func) { _cli_function_map.insert(std::make_pair(cmd, func)); };

	/* CLI Function getter */
	std::function<bool(std::string)> find(std::string &cmd)
	{
		auto it = _cli_function_map.find(cmd);
		return (it != _cli_function_map.end()) ? it->second : nullptr;
	}

	void initialize();
	void finalize();

	/**
	 * CLI Commands
	 */
	bool clicmd_shutdown(std::string /*cmd*/);

private:
	std::unordered_map<std::string, std::function<bool(std::string)>> _cli_function_map;
	// CLI command holder to be thread safe
	ThreadSafeQueue<CLICommand> _cli_cmd_queue;
	std::thread _cli_thread;
};

class DatabaseProcess
{
public:
	DatabaseProcess() { }
	~DatabaseProcess() { }

	void initialize(std::string host, int port, std::string user, std::string pass, std::string database, int threads) 
	{
		_mysql_connections = std::make_shared<ConnectionPool>(host, port, user, pass, database, threads);
	}
	std::shared_ptr<ConnectionPool> pool() { return _mysql_connections; }
protected:
	std::shared_ptr<ConnectionPool> _mysql_connections;
};

class Mainframe
{
public:
	Mainframe(general_server_configuration &config);
	~Mainframe();

	virtual void initialize() = 0; //< Mainframe initialization routine
	virtual void finalize() = 0;   //< Mainframe finalization routine

	struct general_server_configuration &general_conf() { return this->_config; }

	CommandLineProcess &get_command_line_process() { return _cmd_line_process; }
	DatabaseProcess &get_databse_process() { return _database_process; }
	
	/* Command Line Interface */
	void initialize_command_line();

protected:
	CommandLineProcess _cmd_line_process;
	DatabaseProcess _database_process;
	general_server_configuration _config;
};

class Server : public Mainframe
{
public:
	Server();
	~Server();

	void parse_exec_args(const char *argv[], int argc);

	void initialize();
	void finalize();
	
	void print_help();

	/* Core I/O Service*/
	boost::asio::io_service &get_io_service();

	/* General Configuration */
	struct general_server_configuration &general_conf() { return this->general_config; }
	/* Common Configuration */
	bool parse_common_configs(sol::table &cfg);
    
	std::shared_ptr<ConnectionPool> database_pool() { return _database_process.pool(); }
	
protected:
	/* General Configuration */
	struct general_server_configuration general_config;
    
	/**
	 * Core IO Service
	 */
	boost::asio::io_service _io_service;
};

#endif /* HORIZON_SERVER_HPP */
