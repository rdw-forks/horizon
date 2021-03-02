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

#ifndef HORIZON_ZONE_GAME_MAP_SCRIPTMANAGER
#define HORIZON_ZONE_GAME_MAP_SCRIPTMANAGER

#include "Common/Definitions/NPCDefinitions.hpp"
#include "Common/Definitions/MonsterDefinitions.hpp"

#include <sol.hpp>

namespace Horizon
{
namespace Zone
{
namespace Entities
{
	class NPC;
	class Player;
	class Monster;
}
class MapContainerThread;
class ScriptManager
{
friend class MapContainerThread;
public:
	explicit ScriptManager(std::shared_ptr<MapContainerThread> container);
	~ScriptManager();

	std::shared_ptr<MapContainerThread> get_map_container() { return _container.lock(); }

	void contact_npc_for_player(std::shared_ptr<Entities::Player> player, uint32_t npc_guid);
	void continue_npc_script_for_player(std::shared_ptr<Entities::Player> player, uint32_t npc_guid, uint32_t select_idx = 0);

	void send_dialog_to_player(std::shared_ptr<Entities::Player> player, uint32_t npc_guid, std::string const &HLog);
	void send_next_dialog_to_player(std::shared_ptr<Entities::Player> player, uint32_t npc_guid);
	void send_close_dialog_to_player(std::shared_ptr<Entities::Player> player, uint32_t npc_guid);
	void perform_command_from_player(std::shared_ptr<Entities::Player> player, std::string const &cmd);
	void initialize_state(sol::state &st);

	void add_npc_to_db(uint32_t guid, std::shared_ptr<npc_db_data> const &data) { _npc_db.insert(guid, data); }
	std::shared_ptr<npc_db_data> get_npc_from_db(uint32_t guid) { return _npc_db.at(guid); }

	void add_monster_spawn_to_db(uint32_t guid, std::shared_ptr<monster_spawn_data> data) { _monster_spawn_db.insert(guid, data); }
	std::shared_ptr<monster_spawn_data> get_monster_spawn_from_db(uint32_t guid) { return _monster_spawn_db.at(guid); }

	void add_spawned_monster_to_db(uint32_t guid, std::shared_ptr<Entities::Monster> data) { _monster_spawned_map.insert(std::pair<uint32_t, std::shared_ptr<Entities::Monster>>(guid, data)); }
	std::shared_ptr<Entities::Monster> get_spawned_monster_from_db(uint32_t guid) 
	{
		auto it = _monster_spawned_map.find(guid);
		if (it != _monster_spawned_map.end())
			return it->second;

		return nullptr;
	}
	std::map<uint32_t, std::shared_ptr<Entities::Monster>> get_spawned_monster_db() { return _monster_spawned_map; }

protected:
	void initialize();
	void finalize();
	void prepare_lua_state(sol::state &lua);

private:
	void load_constants();
	void load_scripts();
	void load_scripts_internal();

	std::vector<std::string> _script_files;
	LockedLookupTable<uint32_t, std::shared_ptr<npc_db_data>> _npc_db;
	LockedLookupTable<uint32_t, std::shared_ptr<monster_spawn_data>> _monster_spawn_db;
	std::map<uint32_t, std::shared_ptr<Entities::Monster>> _monster_spawned_map;
	sol::state _lua_state;
	std::weak_ptr<MapContainerThread> _container;
	int32_t _last_monster_spawn_id{0};
	
};
}
}

#endif /* HORIZON_ZONE_GAME_MAP_SCRIPTMANAGER */
