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
#include "Auth.hpp"

#include "Server/Auth/SocketMgr/ClientSocketMgr.hpp"
#include "Server/Common/Server.hpp"
#include "Server/Common/SQL/SessionData.hpp"
#include "Server/Common/SQL/GameAccount.hpp"

#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/asio.hpp>
#include <boost/filesystem.hpp>
#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/make_shared.hpp>
#include <boost/filesystem.hpp>
#include <boost/bind/placeholders.hpp>

#include <sol.hpp>

#include <sqlpp11/sqlpp11.h>
#include <sqlpp11/insert.h>

using boost::asio::ip::udp;
using namespace std::chrono_literals;
using namespace Horizon::Auth;

/**
 * Horizon Constructor.
 */
AuthServer::AuthServer()
: Server(), _update_timer(_io_service)
{
	initialize_cli_commands();
}

/**
 * Horizon Destructor.
 */
AuthServer::~AuthServer()
{
}

#define horizon_config_error(setting_name, default) \
	HLog(error) << "No setting for '" << setting_name << "' in configuration file, defaulting to " << default;

/**
 * Read /config/horizon-server.yaml
 * @return true on success, false on failure.
 */
bool AuthServer::read_config()
{
	sol::state lua;

	std::string file_path = general_conf().get_config_file_path().string();
	std::string tmp_string;
	sol::table tbl;

    if (!boost::filesystem::exists(file_path)) {
        HLog(error) << "Configuration file does not exist at " << file_path << "." << std::endl;
        return false;
    }
    
	// Read the file. If there is an error, report it and exit.
	try {
		lua.script_file(file_path);
		tbl = lua["horizon_config"];
	} catch (const std::exception &error) {
		HLog(error) << "Horizon::ReadConfig: '" << error.what() << "'.";
		return false;
	}
	
	try {
		sol::table char_servers = tbl.get<sol::table>("character_servers");
		char_servers.for_each([&](sol::object const &key, sol::object const &value) {
			auth_config_type::char_server c;
			sol::table cfg = value.as<sol::table>();
			
			c._name = cfg.get<std::string>("Name");
			c._host = cfg.get<std::string>("Host");
			c._port = cfg.get<uint16_t>("Port");
			c._type = cfg.get<uint16_t>("Type");
			c._is_new = cfg.get<uint16_t>("IsNew");
			
			sAuth->get_auth_config().add_char_server(c);
			
			HLog(info) << "Character server '" << c._name << "' is configured.";
		});
	} catch (std::exception &error) {
		HLog(error) << "Character server configuration error:" << error.what() << ".";
		return false;
	}
	
	int char_server_count = sAuth->get_auth_config().get_char_servers().size();
	HLog(info) << char_server_count << " character servers were configured.";
	
	/**
	 * Process Configuration that is common between servers.
	 */
	if (!parse_common_configs(tbl))
		return false;

	HLog(info) << "Done reading server configuration from '" << file_path << "'.";

	return true;
}

#undef horizon_config_error

/**
 * CLI Command: Reload Configuration
 * @return boolean value from AuthServer->ReadConfig()
 */
bool AuthServer::clicmd_reload_config(std::string /*cmd*/)
{
	HLog(info) << "Reloading configuration from '" << general_conf().get_config_file_path() << "'";

	return sAuth->read_config();
}

bool AuthServer::clicmd_create_new_account(std::string cmd)
{
	SQL::TableGameAccounts tga;
	std::vector<std::string> separated_args;
	std::string help_str = "Usage: create-account <username> <password> <email> <birthdate: YYYY-MM-DD> <pincode> {<group_id>, {<character_slots>}}";
	
	boost::algorithm::split(separated_args, cmd, boost::algorithm::is_any_of(" "));

	if (separated_args.size() < 3) {
		HLog(error) << "create-account command requires at least 5 arguments.";
		HLog(error) << help_str;
		return false;
	}

	std::string username = separated_args[1];
	std::string password = separated_args[2];
	std::string email = separated_args[3];
	std::string birthdate = separated_args[4];
	std::string pincode = separated_args[5];

	int group_id = separated_args.size() >= 7 ? std::stoi(separated_args[6]) : 0;
	int character_slots = separated_args.size() >= 8 ? std::stoi(separated_args[7]) : 3;

	std::shared_ptr<sqlpp::mysql::connection> conn = sAuth->get_db_connection();

	auto res = (*conn)(select(count(tga.id)).from(tga).where(tga.username == username));

	if (res.front().count) {
		HLog(error) << "Account with username '" << username << "' already exists.";
		return false;
	}
	
	(*conn)(insert_into(tga).set(tga.username = username, tga.hash = password, tga.gender = "U", tga.email = email,
		tga.birth_date = birthdate, tga.character_slots = character_slots, tga.pincode = pincode, 
		tga.group_id = group_id, tga.state = (int) ACCOUNT_STATE_NONE, tga.last_ip = "", tga.login_count = 0, tga.last_login = std::chrono::system_clock::now()));

	HLog(info) << "Account '" << username << "' has been created successfully.";

	return true;
}

/**
 * Initialize CLI Comamnds
 */
void AuthServer::initialize_cli_commands()
{
	add_cli_command_func("reloadconf", std::bind(&AuthServer::clicmd_reload_config, this, std::placeholders::_1));
	add_cli_command_func("create-account", std::bind(&AuthServer::clicmd_create_new_account, this, std::placeholders::_1));
	Server::initialize_cli_commands();
}

/**
 * Signal Handler from the main thread.
 * @param ioServiceRef
 * @param error
 */
void SignalHandler(const boost::system::error_code &error, int /*signal*/)
{
	if (!error) {
		sAuth->set_shutdown_stage(SHUTDOWN_INITIATED);
		sAuth->set_shutdown_signal(SIGTERM);
	}
}

void AuthServer::update(uint64_t time)
{
	process_cli_commands();

	getScheduler().Update();
	
	ClientSocktMgr->update_socket_sessions(time);
	
	if (get_shutdown_stage() == SHUTDOWN_NOT_STARTED && !general_conf().is_test_run()) {
		_update_timer.expires_from_now(boost::posix_time::microseconds(MAX_CORE_UPDATE_INTERVAL));
		_update_timer.async_wait(std::bind(&AuthServer::update, this, std::time(nullptr)));
	} else {
		get_io_service().stop();
	}
}

void AuthServer::initialize_core()
{
	/**
	 * Core Signal Handler
	 */
	boost::asio::signal_set signals(get_io_service(), SIGINT, SIGTERM);
	// Set signal handler for callbacks.
	// Set signal handlers (this must be done before starting io_service threads,
	// because otherwise they would unblock and exit)
	signals.async_wait(std::bind(&SignalHandler, std::placeholders::_1, std::placeholders::_2));

	// Start Horizon Network
	ClientSocktMgr->start(get_io_service(),
						  general_conf().get_listen_ip(),
						  general_conf().get_listen_port(),
						  MAX_NETWORK_THREADS);

	// Initialize core.
	Server::initialize_core();
	
	_update_timer.expires_from_now(boost::posix_time::microseconds(MAX_CORE_UPDATE_INTERVAL));
	_update_timer.async_wait(std::bind(&AuthServer::update, this, MAX_CORE_UPDATE_INTERVAL));

	get_io_service().run();

	HLog(info) << "Shutdown process initiated...";
	
	/**
	 * Cancel all pending tasks.
	 */
	getScheduler().CancelAll();

	/**
	 * Server shutdown routine begins here...
	 */
	Server::finalize_core();

	/**
	 * Stop all networks
	 */
	ClientSocktMgr->stop_network();

	/* Cancel signal handling. */
	signals.cancel();

	set_shutdown_stage(SHUTDOWN_CLEANUP_COMPLETE);
}

/**
 * Main Runtime Method
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, const char * argv[])
{
	if (argc > 1)
		sAuth->parse_exec_args(argv, argc);

	/*
	 * Read Configuration Settings for
	 * the Horizon Server.
	 */
	if (!sAuth->read_config())
		exit(SIGTERM); // Stop process if the file can't be read.

	/**
	 * Initialize the Common Core
	 */
	sAuth->initialize_core();

	/*
	 * Core Cleanup
	 */
	HLog(info) << "Server shutting down...";

	return sAuth->general_conf().get_shutdown_signal();
}
