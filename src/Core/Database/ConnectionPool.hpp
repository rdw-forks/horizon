/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 * Copyright (c) 2023 Sagun K. (sagunxp@gmail.com).
 * Copyright (c) 2023 Horizon Dev Team.
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
#ifndef CONNECTION_POOL_H
#define CONNECTION_POOL_H

#include <queue>
#include <mutex>
#include <condition_variable>
#include <mysqlx/xdevapi.h>

#include "Core/Logging/Logger.hpp"

class ConnectionPool {
public:
    ConnectionPool(const std::string& host, int port, const std::string& user, const std::string& password, const std::string& schema, int pool_size)
        : _host(host), _port(port), _user(user), _password(password), _schema(schema), _pool_size(pool_size) {
        _initialized = true;
        initialize_pool();
    }

    mysqlx::Session get_connection() {
        std::unique_lock<std::mutex> lock(_mutex);

        // Wait for a connection to become available
        while (_connections.empty()) {
            _condition.wait(lock);
        }

        // Get the next available connection
        mysqlx::Session connection = std::move(_connections.front());
        _connections.pop();

        return connection;
    }

    void release_connection(mysqlx::Session connection) {
        std::lock_guard<std::mutex> lock(_mutex);

        // Release the connection back to the pool
        _connections.push(std::move(connection));

        // Notify a waiting thread that a connection is available
        _condition.notify_one();
    }

private:
    std::string _host;
    int _port;
    std::string _user;
    std::string _password;
    std::string _schema;
    int _pool_size;
    std::queue<mysqlx::Session> _connections;
    std::mutex _mutex;
    std::condition_variable _condition;
    bool _initialized = false;

    void create_connection() {
        if (!_initialized) {
            throw std::runtime_error("create_connection called before initialize_pool");
        }

        mysqlx::Session connection(_host, _port, _user, _password);
        connection.sql("USE " + _schema).execute();
        _connections.push(std::move(connection));
    }

    void initialize_pool() {
        for (int i = 0; i < _pool_size; ++i) {
            create_connection();
        }
		HLog(info) << "Database thread pool of " << _pool_size << " threads initialized.";
    }
};

#endif // CONNECTION_POOL_H