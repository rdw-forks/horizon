/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
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

#include "NPCComponent.hpp"

#include "Server/Common/Configuration/Horizon.hpp"
#include "Server/Zone/Game/Entities/NPC/NPC.hpp"
#include "Server/Zone/Game/Entities/Player/Player.hpp"
#include "Server/Zone/Zone.hpp"

using namespace Horizon::Zone;
using namespace Horizon::Zone::Entities;

void NPCComponent::sync_definitions(std::shared_ptr<sol::state> state)
{
}

void NPCComponent::sync_data_types(std::shared_ptr<sol::state> state)
{
	state->new_usertype<NPC>("NPC",
		"entity", [](std::shared_ptr<Horizon::Zone::Entities::NPC> npc) { return npc->shared_from_this(); },
		"name", &NPC::name,
		"map_coords", &NPC::map_coords,
		"get_nearby_entity", &NPC::get_nearby_entity,
		"init", &NPC::initialize,
		"set_map", &NPC::set_map
	);
}

void NPCComponent::sync_functions(std::shared_ptr<sol::state> state, std::shared_ptr<MapContainerThread> container)
{
	state->set_function("cast_entity_to_npc",
		[](std::shared_ptr<Entity> e)
		{
			return e->template downcast<Horizon::Zone::Entities::NPC>();
		});

	state->set_function("NewNPC",
		[this, container] (std::string const &name, std::string const &map_name, uint16_t x, uint16_t y, uint32_t job_id, directions dir, std::string const &script_file) {
			std::shared_ptr<Map> map;
			
			MAP_CONTAINER_THREAD_ASSERT_MAP(map, container, map_name);

			std::shared_ptr<NPC> npc = std::make_shared<NPC>(name, map, x, y, job_id, dir);
			npc->initialize();

			npc_db_data nd;
			nd.npc_name = name;
			nd.map_name = map->get_name();
			nd.coords = MapCoords(x, y);
			nd.direction = dir;
			nd.script = script_file;
			nd.script_is_file = true;
			nd._npc = npc;

			std::shared_ptr<npc_db_data> p_nd = std::make_shared<npc_db_data>(nd);

			add_npc_to_db(npc->guid(), p_nd);
		});

	state->set_function("DupNPC",
		[this, container] (std::string const &name, std::string const &map_name, uint16_t x, uint16_t y, uint32_t job_id, directions dir, std::shared_ptr<NPC> duplicate) {

			std::shared_ptr<Map> map;
			
			MAP_CONTAINER_THREAD_ASSERT_MAP(map, container, map_name);

			std::shared_ptr<NPC> npc = std::make_shared<NPC>(name, map, x, y, job_id, dir);
			npc->initialize();

			npc_db_data nd;
			nd.npc_name = name;
			nd.map_name = map->get_name();
			nd.coords = MapCoords(x, y);
			nd.direction = dir;
			nd._npc = npc;

			std::shared_ptr<npc_db_data> dup_nd = _npc_db.at(duplicate->guid());

			nd.script = dup_nd->script;
			nd.script_is_file = true;

			std::shared_ptr<npc_db_data> p_nd = std::make_shared<npc_db_data>(nd);

			add_npc_to_db(npc->guid(), p_nd);
		});

	state->set_function("SilentNPC",
		[this, container] (std::string const &name, std::string const &map_name, uint16_t x, uint16_t y, uint32_t job_id, directions dir) {
			std::shared_ptr<Map> map;

			MAP_CONTAINER_THREAD_ASSERT_MAP(map, container, map_name);

			std::shared_ptr<NPC> npc = std::make_shared<NPC>(name, map, x, y, job_id, dir);
			npc->initialize();

			npc_db_data nd;
			nd.npc_name = name;
			nd.map_name = map->get_name();
			nd.coords = MapCoords(x, y);
			nd.direction = dir;
			nd._npc = npc;

			std::shared_ptr<npc_db_data> p_nd = std::make_shared<npc_db_data>(nd);

			add_npc_to_db(npc->guid(), p_nd);
		});

	state->set_function("Warp",
		[this, container] (std::string const &name, std::string const &map_name, uint16_t x, uint16_t y, std::string const &script, uint16_t trigger_range) 
		{
			if (container == nullptr)
				return;
			
			std::shared_ptr<Map> map;

			MAP_CONTAINER_THREAD_ASSERT_MAP(map, container, map_name);

			std::shared_ptr<NPC> npc = std::make_shared<NPC>(name, map, x, y, script);
			npc->initialize();

			npc_db_data nd;
			nd.npc_name = name;
			nd.map_name = map->get_name();
			nd.coords = MapCoords(x, y);
			nd.script = script;
			nd.script_is_file = false;
			nd.trigger_range = trigger_range;
			nd._npc = npc;
			
			std::shared_ptr<npc_db_data> p_nd = std::make_shared<npc_db_data>(nd);

			add_npc_to_db(npc->guid(), p_nd);
		});
}

void NPCComponent::contact_npc_for_player(std::shared_ptr<Player> player, uint32_t npc_guid)
{
	std::shared_ptr<npc_db_data> const &nd = _npc_db.at(npc_guid);

	if (nd->script_is_file)
		player->set_npc_contact_guid(npc_guid);

	try {
		sol::protected_function fx = player->lua_state()->load_file(sZone->config().get_script_root_path().string().append("/internal/script_command_main.lua"));
		sol::protected_function_result result = fx(player, nd->_npc, nd->script, nd->script_is_file);
		if (!result.valid()) {
			sol::error err = result;
			HLog(error) << "LUAManager::contact_npc_for_player: " << err.what();
		}
	} catch (sol::error &e) {
		HLog(error) << e.what();
	}
}

void NPCComponent::continue_npc_script_for_player(std::shared_ptr<Entities::Player> player, uint32_t npc_guid, uint32_t select_idx)
{
	sol::thread cr_thread = (*player->lua_state())["script_exec_routine"];
	sol::state_view cr_state = cr_thread.state();
	sol::coroutine cr = cr_state["script_exec"];

	// Set npc menu selection index (if any, defaulted to 0).
	cr_state["script_commands"]["select_idx"] = select_idx;

	sol::protected_function_result result = cr(cr_state["script_commands"]);
	if (!result.valid()) {
		sol::error err = result;
		HLog(error) << "LUAManager::continue_npc_script_for_player: " << err.what();
	}
}