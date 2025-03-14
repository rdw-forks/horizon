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
 *  (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 **************************************************/

#ifndef HORIZON_NETWORKING_SOCKETMGR_HPP
#define HORIZON_NETWORKING_SOCKETMGR_HPP

#include "Libraries/Networking/AsyncAcceptor.hpp"
#include "Libraries/Networking/NetworkThread.hpp"
#include "Libraries/Networking/Connector.hpp"
#include "Server/Common/Configuration/Horizon.hpp"

#include <boost/asio.hpp>
#include <assert.h>
#include <iostream>
#include <memory>
#include <boost/scoped_ptr.hpp>

namespace Horizon
{
namespace Networking
{
template <class SocketType, class NetworkThreadType>
class SocketMgr
{
	typedef std::shared_ptr<NetworkThreadType> NetworkThreadPtr;
	typedef std::unordered_map<uint32_t, NetworkThreadPtr> network_thread_map;
public:
	virtual ~SocketMgr()
	{
		assert(_thread_map.empty());
	}

	/**
	 * @brief Main function that deals with network thread initiation.
	 * @param[in] threads  Number of threads to start.
	 * @return true on success, false on failure.
	 */
	virtual bool StartNetworkThreads(uint32_t threads = 1)
	{
		for (uint32_t i = 0; i < threads; i++) {
			NetworkThreadPtr network_thr = std::make_shared<NetworkThreadType>();

			if (network_thr == nullptr) {
				HLog(error) << "Networking: Error in creating threads, SocketMgr::StartThreadForNetworks.";
				return false;
			}

			network_thr->start(i + 1);

			_thread_map.insert(std::make_pair(i, network_thr));
		}

		return true;
	}

	/**
	 * @brief Stops network threads and clears the thread map.
	 */
	virtual bool stop_network()
	{
		/* Clear the thread map. */
		for (auto it = _thread_map.begin(); it != _thread_map.end();) {
			NetworkThreadPtr thr = it->second;
			thr->finalize();
			// Wait for thread to finalize all sockets.
			while (thr->is_finalizing())
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
			};
			thr->join();
			it = _thread_map.erase(it);
		}

		return true;
	}

	/**
	 * Get the current size of the thread map.
	 * @return size of the thread.
	 */
	uint32_t GetNetworkThreadCount() const { return (uint32_t) _thread_map.size(); }

	/**
	 * Select the thread with the least number of connections, for new socket additions.
	 * @return thread index.
	 */
	uint32_t SelectThreadWithMinConnections() const
	{
		uint32_t min_idx = 0;

		for (auto &thr : _thread_map)
			if (thr.second->connection_count() < NetworkThreadPtr(_thread_map.at(min_idx))->connection_count())
				min_idx = thr.first;

		return min_idx;
	}

	/**
	 * @brief On Socket Open / Start Routine.
	 *        - Move the socket ownership from the caller to a new socket and add it to a thread.
	 * @param[in|out] conn_name      as the name of the connection.
	 * @param[in]     socket         shared pointer.
	 * @param[in]     thread_index   index of the thread that the socket is being moved from.
	 */
	std::shared_ptr<SocketType> on_socket_open(std::shared_ptr<tcp::socket> const &socket, uint32_t thread_index)
	{
		std::shared_ptr<SocketType> new_socket = std::make_shared<SocketType>(++_last_socket_id, std::move(socket));

		try {
			// Add socket to thread.
			NetworkThreadPtr(_thread_map.at(thread_index))->add_socket(new_socket);
		} catch (boost::system::system_error const &error) {
			HLog(error) << "Networking: Failed to retrieve client's remote address " << error.what();
		}

		return new_socket;
	}

	/**
	 * @brief Get a socket from the thread for new server connection.
	 * @return std::pair of the socket and index of the thread it was taken from.
	 */
	std::pair<std::shared_ptr<tcp::socket>, uint32_t> get_new_socket()
	{
		int min_idx = SelectThreadWithMinConnections();
		return std::make_pair(NetworkThreadPtr(_thread_map.at(min_idx))->get_new_socket(), min_idx);
	}

	network_thread_map &get_thread_map() { return _thread_map; }

private:
	uint64_t _last_socket_id{0};                                      ///< ID of the last socket connection. Used for new connection IDs.
	network_thread_map _thread_map;       ///< Unordered map of threads with a unique integer as the key.
};
}
}

#endif /* HORIZON_NETWORKING_SOCKETMGR_HPP */
