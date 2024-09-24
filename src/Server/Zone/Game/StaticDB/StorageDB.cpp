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

#include "StorageDB.hpp"
#include "Server/Zone/Zone.hpp"

using namespace Horizon::Zone;

StorageDatabase::StorageDatabase()
{
}

StorageDatabase::~StorageDatabase()
{
}

bool StorageDatabase::load()
{
	sol::state lua;

	int total_entries = 0;
	std::string tmp_string;
	std::string file_path = sZone->config().get_static_db_path().string() + "storage_db.lua";

	// Read the file. If there is an error, report it and exit.
	try {
		lua.script_file(file_path);
		sol::table storage_tbl = lua.get<sol::table>("storage_db");
		total_entries = load_storage(storage_tbl);
		HLog(info) << "Loaded " << total_entries << " entries from '" << file_path << "'";
	} catch(const std::exception &e) {
		HLog(error) << "StorageDB::load: " << e.what();
		return false;
	}

	return true;
}

bool StorageDatabase::load_storage(sol::table const &storage_tbl)
{
    int total_entries = 0;
    for (auto &kv : storage_tbl) {
        if (load_internal(kv.first, kv.second)) {
            total_entries++;
        }
    }
    return total_entries > 0;
}

bool StorageDatabase::load_internal(sol::object const &key, sol::object const &value)
{
    storage_config_data config;

    if (key.is<int>()) {
        config.storage_id = key.as<int>();
    } else {
        HLog(error) << "StorageDB::load_internal: Invalid storage id '" << key.as<std::string>() << "', key must be numeric.";
        return false;
    }

    if (!value.is<sol::table>()) {
        HLog(error) << "StorageDB::load_internal: Invalid value type for storage id '" << config.storage_id << "', value must be a table.";
        return false;
    }

    sol::table storage_tbl = value.as<sol::table>();
    config.name = storage_tbl.get_or<std::string>("Name", "Storage");
    config.capacity = storage_tbl.get_or("Capacity", 600);

    _storage_db.insert(config.storage_id, std::make_shared<const storage_config_data>(config));

    return true;
}