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

#ifndef HORIZON_ZONE_STATICDB_EXPDB_HPP
#define HORIZON_ZONE_STATICDB_EXPDB_HPP

#include "Core/Multithreading/LockedLookupTable.hpp"
#include "Server/Common/Configuration/Horizon.hpp"
#include <vector>
#include <sol/sol.hpp>

namespace Horizon
{
namespace Zone
{

struct exp_group_data
{
	uint32_t max_level;
	std::vector<uint64_t> exp;
};

enum exp_group_type
{
	EXP_GROUP_TYPE_BASE,
	EXP_GROUP_TYPE_JOB
};

class ExpDatabase
{
public:
	ExpDatabase() { }
	~ExpDatabase() { }

	static ExpDatabase *get_instance()
	{
		static ExpDatabase instance;
		return &instance;
	}

	bool load();

	std::shared_ptr<const exp_group_data> get_exp_group(std::string const &name, exp_group_type type)
	{
		return type == EXP_GROUP_TYPE_BASE ? _base_exp_group_db.at(name) : _job_exp_group_db.at(name);
	}

	uint32_t get_status_point(uint32_t level)
	{
		if (level <= 0 || level > _stat_point_db.size() || level > MAX_LEVEL)
			return 0;
		return _stat_point_db.at(level);
	}

	bool load_status_point_table();

protected:
	int load_group(sol::table &tbl, exp_group_type type);
	LockedLookupTable<std::string, std::shared_ptr<const exp_group_data>> _base_exp_group_db;
	LockedLookupTable<std::string, std::shared_ptr<const exp_group_data>> _job_exp_group_db;
	LockedLookupTable<uint32_t, uint32_t> _stat_point_db;
};

}
}

#define ExpDB Horizon::Zone::ExpDatabase::get_instance()

#endif /* HORIZON_ZONE_STATICDB_EXPDB_HPP */
