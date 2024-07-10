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

#include "System.hpp"
#include "CLI/CLICommand.hpp"
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/random_generator.hpp>
#include <boost/asio.hpp>
#include <queue>

#include <boost/mysql/error_with_diagnostics.hpp>
#include <boost/mysql/handshake_params.hpp>
#include <boost/mysql/results.hpp>
#include <boost/mysql/static_results.hpp>
#include <boost/mysql/tcp_ssl.hpp>

#include "Server/Common/Configuration/ServerConfiguration.hpp"

#include <sol/sol.hpp>

using boost::asio::ip::tcp;

enum shutdown_stages
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

class MainframeComponent
{
public:
	MainframeComponent(Horizon::System::runtime_module_type module_type) : _module_type(module_type), _hsr_manager(module_type), _uuid(boost::uuids::random_generator()()) { }
	virtual void initialize(int segment_number = 1) { }
	virtual void finalize(int segment_number = 1) { }

	virtual bool is_initialized() { return false; }

	void system_routine_queue_push(std::shared_ptr<Horizon::System::RuntimeContext> context);
	void system_routine_queue_push(std::shared_ptr<Horizon::System::RuntimeContextChain> context);
	void system_routine_process_queue();
	void system_routine_register(Horizon::System::runtime_module_type module_t, Horizon::System::runtime_synchronization_method sync_t, std::shared_ptr<Horizon::System::RuntimeContext> context);

	const std::string get_uuid_string() { return boost::uuids::to_string(_uuid); }

	const std::string get_type_string() 
	{ 
		switch (_module_type)
		{
			case Horizon::System::RUNTIME_MAIN: return "Main";
			case Horizon::System::RUNTIME_GAMELOGIC: return "Game-logic";
			case Horizon::System::RUNTIME_PERSISTENCE: return "Persistence";
			case Horizon::System::RUNTIME_DATABASE: return "Database";
			case Horizon::System::RUNTIME_COMMANDLINE: return "Command-Line";
			case Horizon::System::RUNTIME_SCRIPTVM: return "Script-VM";
			case Horizon::System::RUNTIME_NETWORKING: return "Networking";
			default: return "Unknown";
		}
	}
	
	Horizon::System::SystemRoutineManager &get_system_routine_manager() { return _hsr_manager; }
	
private:
	Horizon::System::runtime_module_type _module_type{Horizon::System::RUNTIME_MAIN};
	Horizon::System::SystemRoutineManager _hsr_manager;
	boost::uuids::uuid _uuid;
};

class CommandLineProcess : public MainframeComponent
{
public:
	CommandLineProcess() : MainframeComponent(Horizon::System::RUNTIME_COMMANDLINE) { }
	void process();
	void queue(CLICommand &&cmdMgr) { _cli_cmd_queue.push(std::move(cmdMgr)); }
	void add_function(std::string cmd, std::function<bool(std::string)> func) { _cli_function_map.insert(std::make_pair(cmd, func)); };

	/* CLI Function getter */
	std::function<bool(std::string)> find(std::string &cmd)
	{
		auto it = _cli_function_map.find(cmd);
		return (it != _cli_function_map.end()) ? it->second : nullptr;
	}

	void initialize(int segment_number = 1) override;
	void finalize(int segment_number = 1) override;

	/**
	 * CLI Commands
	 */
	bool clicmd_shutdown(std::string /*cmd*/);

	bool is_initialized() { return _is_initialized; }

private:
	std::unordered_map<std::string, std::function<bool(std::string)>> _cli_function_map;
	// CLI command holder to be thread safe
	std::queue<CLICommand> _cli_cmd_queue;
	std::thread _cli_thread;
	std::atomic<bool> _is_initialized;
};

class DatabaseProcess : public MainframeComponent
{
public:
	// MainframeComponent dispatch module type is set to Main because DatabaseProcess doesn't run on its own thread.
	DatabaseProcess(boost::asio::io_context &io_context) : _io_context(io_context), MainframeComponent(Horizon::System::RUNTIME_MAIN) { }
	
	void initialize(int segment_number = 1) override { HLog(error) << "Database not configured"; }
	void initialize(int segment_number, std::string host, int port, std::string user, std::string pass, std::string database)
	{
		try {
    		boost::asio::ssl::context ssl_ctx(boost::asio::ssl::context::tls_client);
    		_connection = std::make_shared<boost::mysql::tcp_ssl_connection>(_io_context.get_executor(), ssl_ctx);
    		boost::asio::ip::tcp::resolver resolver(_io_context.get_executor());
    		auto endpoints = resolver.resolve(host, std::to_string(port));
    		boost::mysql::handshake_params params(user, pass, database);
    		_connection->connect(*endpoints.begin(), params);
		} catch (boost::mysql::error_with_diagnostics &error) {
			HLog(error) << error.what();
		}

		bool value = _is_initialized;
		_is_initialized.compare_exchange_strong(value, true);
	}

	void finalize(int segment_number = 1) override 
	{
		bool value = _is_initialized;
		_is_initialized.compare_exchange_strong(value, false);
	}

	std::shared_ptr<boost::mysql::tcp_ssl_connection> get_connection() { return _connection; }

	bool is_initialized() { return _is_initialized.load(); }
protected:
    std::shared_ptr<boost::mysql::tcp_ssl_connection> _connection;
	boost::asio::io_context &_io_context;
	std::atomic<bool> _is_initialized;
};

struct mainframe_component_state_holder
{
	Horizon::System::runtime_module_type type;
	std::shared_ptr<MainframeComponent> ptr;
	int segment_number;
};

typedef std::map<std::string, mainframe_component_state_holder> MainframeComponents;

class Mainframe
{
public:
	Mainframe(general_server_configuration &config);
	~Mainframe();

	virtual void initialize() = 0; //< Mainframe initialization routine
	virtual void finalize() = 0;   //< Mainframe finalization routine

	struct general_server_configuration &general_conf() { return this->_config; }

	template <typename T>
	std::shared_ptr<T> get_component(std::string uuid) 
	{ 
		auto it = _components.find(uuid);
		if (it == _components.end()) 
			return nullptr;

		return std::static_pointer_cast<T>(it->second.ptr);
	}

	template <typename T>
	std::shared_ptr<T> get_component_of_type(Horizon::System::runtime_module_type type, int segment_number = 1)
	{
		for (auto c : _components) {
			if (c.second.type == type && c.second.segment_number == segment_number)
				return std::static_pointer_cast<T>(c.second.ptr);
		}

		return nullptr;
	}

	template <typename T>
	void register_component(Horizon::System::runtime_module_type type, T &&component) { 
		mainframe_component_state_holder holder;
		holder.segment_number = get_registered_component_count_of_type(type) + 1;
		holder.type = type;
		holder.ptr = std::make_shared<T>(std::move(component));
		_components.insert(std::pair(component.get_uuid_string(), holder)); 
	}

	template <typename T>
	void register_component(Horizon::System::runtime_module_type type, std::shared_ptr<T> component) 
	{
		mainframe_component_state_holder holder;
		holder.segment_number = get_registered_component_count_of_type(type) + 1;
		holder.type = type;
		holder.ptr = component;
		_components.insert(std::pair(component->get_uuid_string(), holder)); 
	}

	int get_registered_component_count_of_type(Horizon::System::runtime_module_type type)
	{
		int count = 0;
		for (auto c : _components) {
			if (c.second.type == type)
				count++;
		}
		return count;
	}

	int get_component_count() { return _components.size(); }

	/* Command Line Interface */
	void initialize_command_line();

	MainframeComponents get_component_of_types() { return _components; }

	void system_routine_queue_push(std::shared_ptr<Horizon::System::RuntimeContext> context);
	void system_routine_queue_push(std::shared_ptr<Horizon::System::RuntimeContextChain> context);
	void system_routine_process_queue();
	void system_routine_register(Horizon::System::runtime_module_type module_t, Horizon::System::runtime_synchronization_method sync_t, std::shared_ptr<Horizon::System::RuntimeContext> context);

	Horizon::System::SystemRoutineManager &get_system_routine_manager() { return _hsr_manager; }
protected:
	MainframeComponents _components;
	general_server_configuration _config;
private:
	Horizon::System::SystemRoutineManager _hsr_manager;
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

	std::shared_ptr<boost::mysql::tcp_ssl_connection> get_database_connection() 
	{ 
		return get_component_of_type<DatabaseProcess>(Horizon::System::RUNTIME_DATABASE)->get_connection();
	}

	bool test_database_connection()
	{
		try {
			const char *sql = "SELECT 'Hello World!'";
			boost::mysql::results result;
			get_database_connection()->execute(sql, result);

			if (result.rows().at(0).at(0).as_string().compare("Hello World!") == 0)
				return true;
		} catch (boost::mysql::error_with_diagnostics &error) {
			HLog(error) << error.what();
		}
		return false;
	}

protected:
	/* General Configuration */
	struct general_server_configuration general_config;
    
	/**
	 * Core IO Service
	 */
	boost::asio::io_service _io_service;

};

#endif /* HORIZON_SERVER_HPP */
