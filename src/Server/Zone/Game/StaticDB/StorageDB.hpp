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

#ifndef HORIZON_ZONE_STATICDB_STORAGEDB_HPP
#define HORIZON_ZONE_STATICDB_STORAGEDB_HPP
#include "Core/Multithreading/LockedLookupTable.hpp"
#include <cinttypes>
#include <string>
#include <memory>
#include <sol/sol.hpp>
#include <map>

namespace Horizon
{
namespace Zone
{
struct storage_config_data
{
	int32_t storage_id{0};
	std::string name{""};
    int32_t capacity{600};
};
class StorageDatabase
{
public:
	StorageDatabase();
	~StorageDatabase();
	
	static StorageDatabase *get_instance()
	{
		static StorageDatabase instance;
		return &instance;
	}

	bool load();

protected:
    bool load_storage(sol::table const &storage_tbl);
	bool load_internal(sol::object const &key, sol::object const &value);

public:
	std::shared_ptr<const storage_config_data> get_storage_by_id(int32_t id) { return _storage_db.at(id); }
	int32_t get_storage_db_size() { return _storage_db.size(); }

	std::map<uint32_t, std::shared_ptr<const storage_config_data>> const get_storage_db() const { return _storage_db.get_map(); }

private:
	LockedLookupTable<uint32_t, std::shared_ptr<const storage_config_data>> _storage_db;
};
}
}

#define StorageDB Horizon::Zone::StorageDatabase::get_instance()

#endif /* HORIZON_ZONE_STATICDB_STORAGEDB_HPP */
