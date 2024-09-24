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

#ifndef HORIZON_ZONE_STATICDB_STATUSEFFECTDB_HPP
#define HORIZON_ZONE_STATICDB_STATUSEFFECTDB_HPP

#include "Core/Multithreading/LockedLookupTable.hpp"
#include <cinttypes>
#include <string>
#include <sol/sol.hpp>

namespace Horizon
{
namespace Zone
{
struct status_effect_config_data
{
	int32_t status_id{0};
	std::string name{""};
	int32_t behavior{0};
	std::string icon{""};
	bool visible{true};
	std::string on_start_script{""}, on_end_script{""}, per_second_script{""};
};
class StatusEffectDatabase
{
public:
	StatusEffectDatabase();
	~StatusEffectDatabase();
	
	static StatusEffectDatabase *get_instance()
	{
		static StatusEffectDatabase instance;
		return &instance;
	}

	bool load();

protected:
	bool load_internal(sol::object const &key, sol::object const &value);

public:
	std::shared_ptr<const status_effect_config_data> get_status_effect_by_id(int32_t id) { return _status_effect_db.at(id); }

private:
	LockedLookupTable<uint32_t, std::shared_ptr<const status_effect_config_data>> _status_effect_db;
};
}
}

#define StatusEffectDB Horizon::Zone::StatusEffectDatabase::get_instance()

#endif /* HORIZON_ZONE_STATICDB_STATUSEFFECTDB_HPP */
