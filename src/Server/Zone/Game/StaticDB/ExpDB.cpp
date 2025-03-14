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

#include "ExpDB.hpp"

#include "Server/Zone/Zone.hpp"

using namespace Horizon::Zone;

bool ExpDatabase::load()
{
	sol::state lua;
	int total_entries[2] = { 0, 0 };
	std::string tmp_string;
	std::string file_path = sZone->config().get_static_db_path().string() + "exp_group_db.lua";

	// Read the file. If there is an error, report it and exit.
	try {
		lua.script_file(file_path);
		sol::table base_exp_tbl = lua["base_exp_group_db"];
		sol::table job_exp_tbl = lua["job_exp_group_db"];
		total_entries[0] = load_group(base_exp_tbl, EXP_GROUP_TYPE_BASE);
		total_entries[1] = load_group(job_exp_tbl, EXP_GROUP_TYPE_JOB);
	} catch(const std::exception &e) {
		HLog(error) << "ExpDB::error: " << e.what();
		return false;
	}

	HLog(info) << "Read " << total_entries[0] << " Base and " << total_entries[1] << " Job EXP groups from '" << file_path << "'";

	return true;
}

int ExpDatabase::load_group(sol::table &group_tbl, exp_group_type type)
{
	LockedLookupTable<std::string, std::shared_ptr<const exp_group_data>> *group_db = type == EXP_GROUP_TYPE_BASE ? &_base_exp_group_db : &_job_exp_group_db;
	int total_entries = 0;

	group_tbl.for_each([group_db, &total_entries, type](sol::object const &key, sol::object const &value) {
		std::string group_name = key.as<std::string>();
		sol::table tbl = value.as<sol::table>();
		exp_group_data expd;

		std::shared_ptr<const exp_group_data> dup;
		if ((dup = group_db->at(group_name)) != nullptr) {
			HLog(warning) << "ExpDB::load: Found duplicate " << (type == EXP_GROUP_TYPE_BASE ? "base" : "job") << " Exp group for '" << group_name << "', overwriting...";
			group_db->erase(group_name);
		}

		expd.max_level = tbl.get_or("MaxLevel", 0);
		if (expd.max_level == 0) {
			HLog(error) << "ExpDB::load: Max Level not given for group '" << group_name << "', skipping...";
			return;
		}

		sol::optional<sol::table> maybe_exp_tbl = tbl.get<sol::optional<sol::table>>("Exp");
		if (!maybe_exp_tbl) {
			HLog(error) << "ExpDB::load: Missing Exp data for group '" << group_name << "', skipping...";
			return;
		}

		sol::table &exp_tbl = maybe_exp_tbl.value();
		exp_tbl.for_each([&expd, &group_name](sol::object const &key, sol::object const &value) {
			if (key.get_type() != sol::type::number) {
				HLog(error) << "ExpDB::load: Invalid Exp data found in array of group '" << group_name << "', aborting with '" << key.as<int>() << "' entries...";
				return;
			}
			expd.exp.push_back(value.as<int>());
		});

		group_db->insert(group_name, std::make_shared<exp_group_data>(expd));
		total_entries++;
	});

	return total_entries;
}

bool ExpDatabase::load_status_point_table()
{
	sol::state lua;
	int total_entries = 0;
	std::string tmp_string;
	std::string file_path = sZone->config().get_static_db_path().string() + "status_points.lua";

	// Read the file. If there is an error, report it and exit.
	try {
		lua.script_file(file_path);
		sol::table status_points_tbl = lua["status_points"];
		status_points_tbl.for_each([this, &file_path, &total_entries](sol::object const &key, sol::object const &value) {
			if (key.get_type() != sol::type::number || value.get_type() != sol::type::number) {
				HLog(error) << "Non-numeric key/value pair was found in '" << file_path << "'. Skipping...";
				return;
			}
			_stat_point_db.insert(key.as<uint32_t>(), value.as<uint32_t>());
			total_entries++;
		});
	} catch(const std::exception &e) {
		HLog(error) << "ExpDatabase::load_status_point_table: " << e.what() << ".";
		return false;
	}

	HLog(info) << "Read status points for " << total_entries << " levels from '" << file_path << "'";

	return true;
}
