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

#ifndef HORIZON_ZONE_SCRIPTMANAGER
#define HORIZON_ZONE_SCRIPTMANAGER

#include "Server/Zone/Definitions/NPCDefinitions.hpp"
#include "Server/Zone/Definitions/MonsterDefinitions.hpp"

#include "Server/Zone/Script/Components/StatusEffectComponent.hpp"
#include "Server/Zone/Script/Components/SkillComponent.hpp"
#include "Server/Zone/Script/Components/CombatComponent.hpp"
#include "Server/Zone/Script/Components/EntityComponent.hpp"
#include "Server/Zone/Script/Components/ItemComponent.hpp"
#include "Server/Zone/Script/Components/MapComponent.hpp"
#include "Server/Zone/Script/Components/MonsterComponent.hpp"
#include "Server/Zone/Script/Components/NPCComponent.hpp"
#include "Server/Zone/Script/Components/PlayerComponent.hpp"

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
class ScriptManager
{
public:
	ScriptManager();
	~ScriptManager();

	void initialize_basic_state(std::shared_ptr<sol::state> state);
	void initialize_player_state(std::shared_ptr<sol::state> state);
	void initialize_npc_state(std::shared_ptr<sol::state> state);
	void initialize_monster_state(std::shared_ptr<sol::state> state);

	std::shared_ptr<PlayerComponent> player() { return _player_component; }
	std::shared_ptr<NPCComponent> npc() { return _npc_component; }
	std::shared_ptr<MonsterComponent> monster() { return _monster_component; }
	std::shared_ptr<MapComponent> map() { return _map_component; }
	std::shared_ptr<ItemComponent> item() { return _item_component; }
	std::shared_ptr<EntityComponent> entity() { return _entity_component; }
	std::shared_ptr<SkillComponent> skill() { return _skill_component; }
	std::shared_ptr<StatusEffectComponent> status_effect() { return _status_effect_component; }
	std::shared_ptr<CombatComponent> combat() { return _combat_component; }

	std::shared_ptr<sol::state> lua_state() { return _lua_state; }

	bool is_initialized() { return _is_initialized.load(); }

	void initialize();
	void finalize();
	void prepare_lua_state(std::shared_ptr<sol::state> &lua);

	void start();
	void update(uint64_t diff);
	
private:
	void load_constants();
	void load_scripts();
	void load_scripts_internal();

	std::vector<std::string> _script_files;
	std::shared_ptr<sol::state> _lua_state;

	std::shared_ptr<PlayerComponent> _player_component;
	std::shared_ptr<NPCComponent> _npc_component;
	std::shared_ptr<MonsterComponent> _monster_component;
	std::shared_ptr<MapComponent> _map_component;
	std::shared_ptr<ItemComponent> _item_component;
	std::shared_ptr<EntityComponent> _entity_component;
	std::shared_ptr<SkillComponent> _skill_component;
	std::shared_ptr<StatusEffectComponent> _status_effect_component;
	std::shared_ptr<CombatComponent> _combat_component;

	std::thread _thread;
	std::atomic<bool> _is_initialized;
};
}
}

#endif /* HORIZON_ZONE_SCRIPTMANAGER */
