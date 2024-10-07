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
 * This is proprietary software. Unauthorized copying,
 * distribution, or modification of this file, via any
 * medium, is strictly prohibited. All rights reserved.
 **************************************************/

#ifndef HORIZON_NETWORKING_NETWORKTHREAD_HPP
#define HORIZON_NETWORKING_NETWORKTHREAD_HPP

#include "Core/Logging/Logger.hpp"

#include <thread>
#include <atomic>
#include <mutex>
#include <cassert>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/deadline_timer.hpp>

using boost::asio::ip::tcp;

namespace Horizon
{
namespace Networking
{
/**
 * @brief A Network Thread object that handles a number of sockets.
 *        Sockets are moved into the thread by SocketMgr, once accepted or connected.
 *        Once started, the object blocks to handle I/O events and requires explicit stopping.
 */
template <class SocketType>
class NetworkThread
{
	typedef std::vector<std::shared_ptr<SocketType>> SocketContainer;
public:
	NetworkThread()
	: _connections(0), _finalizing(false), _update_timer(_io_context)
	{
		// Constructor
	}

	/**
	 * @brief Destructor of the network thread,
	 *        performs a clean network finalisation routine before deleting.
	 */
	virtual ~NetworkThread()
	{
		finalize();
	}

	/**
	 * @brief Halts the IO Service and marks the network thread as stopped.
	 */
	virtual void finalize()
	{
		_finalizing.exchange(true);
	}

	void join()
	{
		try {
			_thread->join();
		} catch (std::system_error &error) {
			HLog(error) << "Error joining network thread2: " << error.what();
		}
	}

	/**
	 * @brief Initializes the network thread and runs.
	 * @return true on success, false if thread is a nullptr.
	 */
	virtual bool start(int segment_number = 1)
	{
		if (_thread != nullptr)
			return false;

		_segment_number = segment_number;
		_thread.reset(new std::thread(&NetworkThread::run, this));
		return true;
	}

	/**
	 * @brief Adds a new socket to a queue that is processed
	 *        frequently within this network thread. The method
	 *        update() is called regularly to add new sockets
	 *        to the thread's active socket list.
	 */
	virtual void add_socket(std::shared_ptr<SocketType> sock)
	{
		std::lock_guard<std::mutex> lock(_new_socket_queue_lock);

		_new_socket_queue.push_back(sock);  // Add socket to queue.
	}

	/**
	 * @brief Gets a socket for a new connection.
	 *        This method is used as a socket factory in AsyncAcceptor and Connector classes.
	 *        Once a socket is accepted or connected, its ownership is moved into a network thread.
	 * @return a new shared pointer to a tcp::socket.
	 */
	std::shared_ptr<tcp::socket> get_new_socket() { return std::make_shared<tcp::socket>(_io_context); }

	/**
	 * @brief Gets the total number of network connections or sockets
	 *        handled by this network thread.
	 * @return total number of connections in this network thread.
	 */
	int32_t connection_count() const { return _connections; }

	/**
	 * @brief Issues the status of network thread whether it is finalizing or not.
	 * @return boolean finalizing of the network thread status.
	 */
	bool is_finalizing() { return _finalizing; }
protected:
	/**
	 * @brief Run the I/O Service loop within this network thread.
	 *        Before running, this method gives the I/O service some work
	 *        by asynchronously running a deadline timer on @see update()
	 */
	virtual void run()
	{
		_update_timer.expires_from_now(boost::posix_time::microseconds(500));
		_update_timer.async_wait(std::bind(&NetworkThread<SocketType>::update, this));

		_io_context.run();

		_new_socket_queue.clear();
		_active_sockets.clear();
	}

	virtual void on_socket_removed(std::shared_ptr<SocketType> sock) = 0;
	virtual void on_socket_added(std::shared_ptr<SocketType> sock) = 0;

	/**
	 * @brief Updates the network thread and schedules a recursive call to itself.
	 *        This method is responsible for the following tasks -
	 *        1) Issuing a routine to process the new sockets queue.
	 *        2) Closes sockets that cannot be updated. @see Socket<SocketType>::update()
	 */
	virtual void update()
	{
		_update_timer.expires_from_now(boost::posix_time::microseconds(500));
		_update_timer.async_wait(std::bind(&NetworkThread<SocketType>::update, this));

		add_new_sockets();
		
		// The following code removes all non-active from the active sockets list by shifting all 
		// active sockets to the left and then erasing the extra
		_active_sockets.erase(std::remove_if(_active_sockets.begin(), _active_sockets.end(),
			[this] (std::shared_ptr<SocketType> sock)
			{
				if (!sock->update() || is_finalizing()) {

					if (sock->is_open())
						sock->close_socket();

					on_socket_removed(sock);

					--_connections;

					HLog(info) << "Socket closed in networking thread " << (void *) (_thread.get()) << " (Connections: " << _connections << ")";

					return true;
				}

				return false;
			}), _active_sockets.end());

		if (is_finalizing()) {
			_io_context.stop();
			_finalizing.exchange(false);
			HLog(info) << "Network thread " << (void *) (_thread.get()) << " has been finalized.";
		}
	}

	/**
	 * @brief Processess the new socket queue.
	 *        This method is responsible for -
	 *        1) Processing the entire list of new sockets and clearing it on every call.
	 *        2) removing / closing new sockets that are not open.
	 *        3) Starting the new socket once added to the container. (@see Socket<SocketType>::start())
	 */
	virtual void add_new_sockets()
	{
		if (is_finalizing())
			return;

		std::lock_guard<std::mutex> lock(_new_socket_queue_lock);

		if (_new_socket_queue.empty())
			return;

		for (std::shared_ptr<SocketType> sock : _new_socket_queue) {
			if (sock->is_open()) {
				_active_sockets.push_back(sock);
				// Start receiving from the socket.
				sock->start();

				on_socket_added(sock);

				++_connections; // Increment network connections.

				HLog(trace) << "A new socket has been added to network thread " << (void *) (_thread.get()) << " (Connections: " << _connections << ")";
			}
		}

		_new_socket_queue.clear();
	}

protected:
	SocketContainer _active_sockets;
private:
	int _segment_number{1};
	std::atomic<int32_t> _connections;
	std::atomic<bool> _finalizing;

	std::unique_ptr<std::thread> _thread;

	SocketContainer _new_socket_queue;

	std::mutex _new_socket_queue_lock;

	boost::asio::io_context _io_context;
	boost::asio::deadline_timer _update_timer;
};
}
}

#endif // HORIZON_NETWORKING_NETWORKTHREAD_HPP
