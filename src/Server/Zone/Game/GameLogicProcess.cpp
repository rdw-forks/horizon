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
 * Base Author - Sxyz <sagunxp@gmail.com>
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

#include "GameLogicProcess.hpp"

#include "Server/Zone/Game/StaticDB/ExpDB.hpp"
#include "Server/Zone/Game/StaticDB/JobDB.hpp"
#include "Server/Zone/Game/StaticDB/ItemDB.hpp"
#include "Server/Zone/Game/StaticDB/MonsterDB.hpp"
#include "Server/Zone/Game/StaticDB/SkillDB.hpp"
#include "Server/Zone/Game/StaticDB/StatusEffectDB.hpp"
#include "Server/Zone/Game/StaticDB/StorageDB.hpp"

using namespace Horizon::Zone;

void GameLogicProcess::initialize()
{
	/**
	 * Static Databases
	 */
	ExpDB->load();
	ExpDB->load_status_point_table();
	JobDB->load();
	ItemDB->load();
	ItemDB->load_refine_db();
	ItemDB->load_weapon_target_size_modifiers_db();
	ItemDB->load_weapon_attribute_modifiers_db();
	StatusEffectDB->load();
	SkillDB->load();
	MonsterDB->load();
	StorageDB->load();

    get_map_process().initialize();

    bool value = _is_initialized;
	_is_initialized.compare_exchange_strong(value, true);
}

void GameLogicProcess::finalize()
{
    get_map_process().finalize();

    bool value = _is_initialized;
	_is_initialized.compare_exchange_strong(value, false);
}