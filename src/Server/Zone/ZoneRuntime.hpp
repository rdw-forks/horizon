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

#ifndef HORIZON_ZONE_ZONERUNTIME_HPP
#define HORIZON_ZONE_ZONERUNTIME_HPP

#include "Server/Common/System.hpp"
#include "Server/Common/Configuration/ServerConfiguration.hpp"
#include <boost/lockfree/queue.hpp>
#include <optional> 
#include <array>
#include <boost/asio/io_context.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/random_generator.hpp>

class DatabaseProcess;
class CommandLineProcess;

namespace Horizon
{
namespace Zone
{
class ZoneNetworkThread;
class ScriptManager;
class PersistenceManager;
class GameLogicProcess;

/**
 * @brief The User class represents a user in the system.
 *        It stores information about the user's processes and properties.
 */
class User
{
public:
	/**
	 * @brief Default constructor for the User class.
	 *        Generates a random UUID for the user.
	 */
	User() : _uuid(boost::uuids::random_generator()()) { }

	/**
	 * @brief Getter function for the script process.
	 * @return A shared pointer to the ScriptManager object.
	 */
	std::shared_ptr<ScriptManager> get_script_process();

	/**
	 * @brief Setter function for the script process.
	 * @param uuid The UUID of the script process.
	 */
	void set_script_process(std::string uuid);

	/**
	 * @brief Getter function for the database process.
	 * @return A shared pointer to the DatabaseProcess object.
	 */
	std::shared_ptr<DatabaseProcess> get_database_process();

	/**
	 * @brief Setter function for the database process.
	 * @param uuid The UUID of the database process.
	 */
	void set_database_process(std::string uuid);

	/**
	 * @brief Getter function for the command line process.
	 * @return A shared pointer to the CommandLineProcess object.
	 */
	std::shared_ptr<CommandLineProcess> get_commandline_process();

	/**
	 * @brief Setter function for the command line process.
	 * @param uuid The UUID of the command line process.
	 */
	void set_commandline_process(std::string uuid);

	/**
	 * @brief Getter function for the networking process.
	 * @return A shared pointer to the ClientSocketMgr object.
	 */
	std::shared_ptr<ZoneNetworkThread> get_networking_process();

	/**
	 * @brief Setter function for the networking process.
	 * @param uuid The UUID of the networking process.
	 */
	void set_networking_process(std::string uuid);

	/**
	 * @brief Getter function for the persistence process.
	 * @return A shared pointer to the PersistenceManager object.
	 */
	std::shared_ptr<PersistenceManager> get_persistence_process();

	/**
	 * @brief Setter function for the persistence process.
	 * @param uuid The UUID of the persistence process.
	 */
	void set_persistence_process(std::string uuid);

	/**
	 * @brief Getter function for the game logic process.
	 * @return A shared pointer to the GameLogicProcess object.
	 */
	std::shared_ptr<GameLogicProcess> get_game_logic_process();

	/**
	 * @brief Setter function for the game logic process.
	 * @param uuid The UUID of the game logic process.
	 */
	void set_game_logic_process(std::string uuid);

	/**
	 * @brief Getter function for the UUID as a string.
	 * @return The UUID as a string.
	 */
	std::string get_uuid_string() { return boost::uuids::to_string(_uuid); }

	/**
	 * @brief Getter function for the map name.
	 * @return The map name.
	 */
	std::string get_map_name() { return _map_name; }

	/**
	 * @brief Setter function for the map name.
	 * @param map_name The map name to set.
	 */
	void set_map_name(std::string map_name) { _map_name = map_name; }

private:
	std::array<std::string, Horizon::System::RUNTIME_MODULE_MAX> _module_allocation; // Array to store module allocations
	boost::uuids::uuid _uuid; // UUID for the user
	std::string _map_name{""}; // Name of the map
};
// @brief Routines that go into the main Horizon runtime.
/**
 * @class ZoneRuntime
 * @brief Represents the runtime environment for a zone in the server.
 * 
 * The ZoneRuntime class provides functionality to manage and interact with the users and resources within a zone.
 * It handles initialization, finalization, and the main loop for the zone.
 */
class ZoneRuntime
{
	typedef std::map<std::string, std::shared_ptr<User>> zone_user_map;
public:
/**
 * @brief Constructs a `ZoneRuntime` object.
 *
 * This constructor initializes a `ZoneRuntime` object with the provided `io_context` and `config`.
 *
 * @param io_context The `boost::asio::io_context` object to be used for asynchronous operations.
 * @param config The reference to the `general_server_configuration` object containing server configuration settings.
 */
	ZoneRuntime(general_server_configuration &config);

	/**
	 * @brief Destroys the `ZoneRuntime` object.
	 */
	~ZoneRuntime();

	/**
	 * @brief Returns a reference to the `general_server_configuration` object.
	 *
	 * @return A reference to the `general_server_configuration` object.
	 */
	general_server_configuration &general_conf() { return _config; }

	/**
	 * @brief Initializes the `ZoneRuntime` object.
	 */
	void initialize();

	/**
	 * @brief Finalizes the `ZoneRuntime` object.
	 */
	void finalize();

	/**
	 * @brief Runs the `ZoneRuntime` object with the specified time difference.
	 *
	 * @param diff The time difference in milliseconds.
	 */
	void run(uint64_t diff);

	/**
	 * @brief Returns the `User` object associated with the specified UUID.
	 *
	 * @param uuid The UUID of the user.
	 * @return The `User` object associated with the specified UUID, or `nullptr` if not found.
	 */
	std::shared_ptr<User> get_zone_user(std::string uuid) 
	{
		auto it = _zone_users.find(uuid);
		if (it != _zone_users.end())
			return it->second;
		
		return nullptr;
	}

	/**
	 * @brief Adds a `User` object to the `ZoneRuntime` object.
	 *
	 * @param user The `User` object to be added.
	 */
	void add_zone_user(std::shared_ptr<User> user) 
	{
		_zone_users.emplace(user->get_uuid_string(), user);
	}

protected:
	general_server_configuration &_config; /**< The reference to the `general_server_configuration` object. */
	boost::asio::deadline_timer _update_timer; /**< The `boost::asio::deadline_timer` object for updating the zone. */
	zone_user_map _zone_users; /**< The map of zone users. */
};
}
}

#endif // HORIZON_ZONE_ZONERUNTIME_HPP
