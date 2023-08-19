
#ifndef HORIZON_ZONE_GAME_SKILLEXECUTION_HPP
#define HORIZON_ZONE_GAME_SKILLEXECUTION_HPP

#include "Server/Common/Configuration/Horizon.hpp"
#include "Server/Zone/Definitions/SkillDefinitions.hpp"
#include "Server/Zone/Game/Map/Coordinates.hpp"
#include "Server/Zone/Game/Map/Map.hpp"

namespace Horizon
{
namespace Zone
{
class SkillExecution : public std::enable_shared_from_this<SkillExecution>
{
public:
	SkillExecution(std::shared_ptr<Entity> initial_source, int16_t skill_id, int16_t skill_lv);
	~SkillExecution();

	void execute(int initial_target_guid);
	void execute(MapCoords map_coords);
	void execute(int16_t x, int16_t y);
	void execute(MapCoords map_coords, std::string message);
	void execute(int16_t x, int16_t y, std::string message);

	sol::table get_skill_cast_data() { return _scd; }
private:
	void start_execution(enum skill_target_type target_type);
	std::shared_ptr<Map> map() { return _map.expired() ? nullptr : _map.lock(); }
	void set_map(std::shared_ptr<Map> map)
	{
		_map = map;
		_map_container_thread = map->container();
		_lua_mgr = map->container()->get_lua_manager();
		_lua_state = lua_manager()->lua_state();
	}
	std::shared_ptr<MapContainerThread> map_container() { return _map_container_thread.lock(); }
	std::shared_ptr<LUAManager> lua_manager() { return _lua_mgr.lock(); }
	std::shared_ptr<sol::state> lua_state() { return _lua_state.lock(); }

	std::weak_ptr<Map> _map;
	std::weak_ptr<MapContainerThread> _map_container_thread;
	std::weak_ptr<LUAManager> _lua_mgr;
	std::weak_ptr<sol::state> _lua_state;
	std::shared_ptr<Entity> _initial_source{nullptr};
	std::shared_ptr<Entity> _initial_target{nullptr};
	int16_t _skill_id;
	int16_t _skill_lv;
	MapCoords _map_coords;
	std::string _message;
	sol::table _scd;
};
}
}

#endif /* HORIZON_ZONE_GAME_SKILLEXECUTION_HPP */
