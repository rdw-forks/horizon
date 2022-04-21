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

#include "Player.hpp"

#include "Server/Zone/Definitions/EntityDefinitions.hpp"
#include "Server/Common/SQL/Character/Character.hpp"
#include "Server/Common/SQL/Character/Status.hpp"

#include "Server/Zone/Game/Entities/Player/Assets/Inventory.hpp"
#include "Server/Zone/Game/Map/Grid/Notifiers/GridNotifiers.hpp"
#include "Server/Zone/Game/Map/Grid/Container/GridReferenceContainer.hpp"
#include "Server/Zone/Game/Map/Grid/Container/GridReferenceContainerVisitor.hpp"
#include "Server/Zone/Game/StaticDB/ItemDB.hpp"
#include "Server/Zone/Game/StaticDB/SkillDB.hpp"
#include "Server/Zone/Game/Entities/Creature/Hostile/Monster.hpp"
#include "Server/Zone/Game/Entities/Entity.hpp"
#include "Server/Zone/Game/Entities/Traits/AttributesImpl.hpp"
#include "Server/Zone/Game/Entities/Traits/Status.hpp"
#include "Server/Zone/Session/ZoneSession.hpp"
#include "Server/Zone/Socket/ZoneSocket.hpp"
#include "Server/Zone/Zone.hpp"

#include <sqlpp11/sqlpp11.h>

#include "version.hpp"

using namespace Horizon::Zone;
using namespace Horizon::Zone::Entities;

Player::Player(std::shared_ptr<ZoneSession> session, uint32_t guid)
: Entity(guid, ENTITY_PLAYER), _session(session), _lua_state(std::make_shared<sol::state>())
{
}

Player::~Player()
{
	if (has_valid_grid_reference())
		remove_grid_reference();
}

uint64_t Player::new_unique_id()
{
	int64_t char_id = (int64_t) character()._character_id;
	
	if (character()._last_unique_id > 0)
		return ++character()._last_unique_id;

	return (character()._last_unique_id = (char_id << 32));
}

void Player::create(int char_id, std::string account_gender, int group_id)
{
	character()._character_id = char_id;
	account()._account_gender = account_gender;
	account()._group_id = group_id;

	load();
}

void Player::initialize()
{
	Entity::initialize();

	// Inventory.
	_inventory = std::make_shared<Assets::Inventory>(downcast<Player>(), get_max_inventory_size());
	_inventory->load();

	// Initialize Status, after inventory is loaded to compute EquipAtk etc.
	status()->initialize(shared_from_this());

	// Inventory is initialized for the player, notifying weight etc.
	_inventory->initialize();

	// Ensure grid for entity.
	map()->ensure_grid_for_entity(this, map_coords());
	
	// Populate skill tree.
	std::vector<std::shared_ptr<const skill_tree_config>> sktree = SkillDB->get_skill_tree_by_job_id((job_class_type) job_id());

	for (auto s : sktree) {
		skill_learnt_info info;
		info.skill_id = s->skill_id;
		info.level = 0;
		info.learn_type = SKILL_LEARN_PERMANENT;
		add_learnt_skill(std::make_shared<skill_learnt_info>(info));
	}

	// On map entry processing.
	on_map_enter();

	lua_manager()->initialize_player_state(lua_state());

	try {
		sol::load_result fx = lua_state()->load_file("scripts/internal/on_login_event.lua");
		sol::protected_function_result result = fx(shared_from_this()->downcast<Player>(), VER_PRODUCTVERSION_STR);
		if (!result.valid()) {
			sol::error err = result;
			HLog(error) << "Player::initialize: " << err.what();
		}
	} catch (sol::error &e) {
		HLog(error) << "Player::initialize: " << e.what();
	}
}

void Player::stop_movement()
{
	MapCoords const &coords = map_coords();
	get_session()->clif()->notify_movement_stop(guid(), coords.x(), coords.y());
}

bool Player::save()
{
	SQL::TableCharacters tch;
	std::shared_ptr<sqlpp::mysql::connection> conn = sZone->get_db_connection();
	
	(*conn)(update(tch).set(tch.account_id = account()._account_id, tch.slot = character()._slot, tch.name = name(), tch.online = character()._online, tch.gender = character()._gender == ENTITY_GENDER_MALE ? "M" : "F",
		tch.unban_time = character()._unban_time, tch.rename_count = character()._rename_count, tch.last_unique_id = character()._last_unique_id, tch.hotkey_row_index = character()._hotkey_row_index, 
		tch.change_slot_count = character()._change_slot_count, tch.font = character()._font, tch.show_equip = character()._show_equip, tch.allow_party = character()._allow_party, 
		tch.partner_aid = character()._partner_aid, tch.father_aid = character()._father_aid, tch.mother_aid = character()._mother_aid, tch.child_aid = character()._child_aid, tch.party_id = character()._party_id,
		tch.guild_id = character()._guild_id, tch.pet_id = character()._pet_id, tch.homun_id = character()._homun_id, tch.elemental_id = character()._elemental_id,
		tch.current_map = map()->get_name(), tch.current_x = map_coords().x(), tch.current_y = map_coords().y(),
		tch.saved_map = character()._saved_map, tch.saved_x = character()._saved_x, tch.saved_y = character()._saved_y).where(tch.id == character()._character_id));

	// Status
	status()->save(shared_from_this()->downcast<Player>());

	// Inventory
	inventory()->save();

	return true;
}

bool Player::load()
{
	SQL::TableCharacters tch;
	std::shared_ptr<sqlpp::mysql::connection> conn = sZone->get_db_connection();
	
	auto res = (*conn)(select(all_of(tch)).from(tch).where(tch.id == character()._character_id));
	
	if (res.empty()) {
		HLog(error) << "Error loading player, character with ID " << character()._character_id << " does not exist.";
		return false;
	}

	/* Initialize Player Model */
	character()._character_id = res.front().id;
	account()._account_id = res.front().account_id;
	character()._slot = res.front().slot;
	set_name(res.front().name);
	set_posture(POSTURE_STANDING);
	character()._font = res.front().font;
	
	std::string char_gender = res.front().gender;

	character()._gender = strcmp(char_gender.c_str(), "U") == 0
		? (strcmp(account()._account_gender.c_str(), "M") == 0 ? ENTITY_GENDER_MALE : ENTITY_GENDER_FEMALE)
		: strcmp(char_gender.c_str(), "M") == 0 ? ENTITY_GENDER_MALE : ENTITY_GENDER_FEMALE;
	
	character()._online = 1;
	set_last_unique_id((uint64_t) res.front().last_unique_id);

	character()._saved_map = res.front().saved_map;
	character()._saved_x = res.front().saved_x;
	character()._saved_y = res.front().saved_y;

	/**
	 * Set map and coordinates for entity.
	 */
	MapCoords mcoords(res.front().current_x, res.front().current_y);
	std::shared_ptr<Map> map = MapMgr->get_map(res.front().current_map);
	
	map->container()->add_player(shared_from_this()->downcast<Player>());

	set_map(map);
	set_map_coords(mcoords);

	return true;
}

void Player::on_pathfinding_failure()
{
	HLog(debug) << "Player " << name() << " has failed to find path from (" << map_coords().x() << "," << map_coords().y() << ") to (" << dest_coords().x() << ", " << dest_coords().y() << ").";
}

void Player::on_movement_begin()
{
	get_session()->clif()->notify_player_movement(map_coords(), dest_coords());
}

void Player::on_movement_end()
{
}

void Player::on_movement_step()
{
	GridNPCTrigger npc_trigger(shared_from_this());
	GridReferenceContainerVisitor<GridNPCTrigger, GridReferenceContainer<AllEntityTypes>> npc_trigger_performer(npc_trigger);

	map()->ensure_grid_for_entity(this, map_coords());

	update_viewport();

	map()->visit_in_range(map_coords(), npc_trigger_performer, MAX_NPC_TRIGGER_RANGE);
}

bool Player::is_overweight_50() { return status()->current_weight()->total() * 100 >= status()->max_weight()->total() * 50; }
bool Player::is_overweight_90() { return status()->current_weight()->total() * 10 >= status()->max_weight()->total() * 9; }

void Player::update_viewport()
{
	GridViewPortUpdater updater(shared_from_this());
	GridReferenceContainerVisitor<GridViewPortUpdater, GridReferenceContainer<AllEntityTypes>> update_caller(updater);

	map()->visit_in_range(map_coords(), update_caller);
}

void Player::add_entity_to_viewport(std::shared_ptr<Entity> entity)
{
	if (entity == nullptr)
		return;

	if (entity_is_in_viewport(entity))
		return;

	entity_viewport_entry entry = get_session()->clif()->create_viewport_entry(entity);
	get_session()->clif()->notify_viewport_add_entity(entry);
	
	_viewport_entities.push_back(entity);

	if (entity->type() == ENTITY_MONSTER) {
		if (map()->container()->getScheduler().Count(get_scheduler_task_id(ENTITY_SCHEDULE_AI_ACTIVE)) == 0)
			map()->container()->getScheduler().Schedule(Milliseconds(MOB_MIN_THINK_TIME), get_scheduler_task_id(ENTITY_SCHEDULE_AI_ACTIVE),
				[this] (TaskContext context)
				{
					GridMonsterActiveAIExecutor ai_executor(shared_from_this()->downcast<Player>());
					GridReferenceContainerVisitor<GridMonsterActiveAIExecutor, GridReferenceContainer<AllEntityTypes>> ai_executor_caller(ai_executor);

					map()->visit_in_range(map_coords(), ai_executor_caller);
					context.Repeat(Milliseconds(MOB_MIN_THINK_TIME));
				});
	}

	HLog(debug) << "------- VIEWPORT ENTITIES ----------";
	for (auto it = _viewport_entities.begin(); it != _viewport_entities.end(); it++)
		HLog(debug) << "Entity:" << it->lock()->name() << " " << it->lock()->guid();
	HLog(debug) << "--------------------";
}

void Player::remove_entity_from_viewport(std::shared_ptr<Entity> entity, entity_viewport_notification_type type)
{
	if (!entity_is_in_viewport(entity))
		return;

	_viewport_entities.erase(std::remove_if(_viewport_entities.begin(), _viewport_entities.end(),
		[entity] (std::weak_ptr<Entity> wp_e) {
			return wp_e.lock()->guid() == entity->guid();
		}
	), _viewport_entities.end());

	get_session()->clif()->notify_viewport_remove_entity(entity, type);

	HLog(debug) << "------- VIEWPORT ENTITIES ----------";
	for (auto it = _viewport_entities.begin(); it != _viewport_entities.end(); it++)
		HLog(debug) << "Entity:" << it->lock()->name() << " " << it->lock()->guid();
	HLog(debug) << "--------------------";
}

bool Player::entity_is_in_viewport(std::shared_ptr<Entity> entity)
{
	if (entity == nullptr)
		return false;

	std::vector<std::weak_ptr<Entity>>::iterator it = std::find_if (_viewport_entities.begin(), _viewport_entities.end(), 
		[entity] (const std::weak_ptr<Entity> &vp_ew) { 
			std::shared_ptr<Entity> vp_es = vp_ew.lock();

			if (vp_es == nullptr || entity == nullptr)
				return false;

			return (vp_es->guid() == entity->guid());
		}
	);
	
	return (it != _viewport_entities.end());
}

void Player::realize_entity_movement(std::shared_ptr<Entity> entity)
{
	if (entity == nullptr)
		return;

	get_session()->clif()->notify_entity_move(entity->guid(), entity->map_coords(), entity->dest_coords());
}

void Player::realize_entity_movement_entry(std::shared_ptr<Entity> entity)
{
	if (entity == nullptr)
		return;

	entity_viewport_entry entry = get_session()->clif()->create_viewport_entry(entity);
	get_session()->clif()->notify_viewport_moving_entity(entry);
}

void Player::spawn_entity_in_viewport(std::shared_ptr<Entity> entity)
{
	if (entity == nullptr)
		return;

	entity_viewport_entry entry = get_session()->clif()->create_viewport_entry(entity);
	get_session()->clif()->notify_viewport_spawn_entity(entry);
}

bool Player::move_to_map(std::shared_ptr<Map> dest_map, MapCoords coords)
{
	if (dest_map == nullptr)
		return false;

	force_movement_stop_internal(true);
	map()->container()->getScheduler().Count(get_scheduler_task_id(ENTITY_SCHEDULE_WALK));

	std::shared_ptr<Player> myself = downcast<Player>();

	notify_nearby_players_of_existence(EVP_NOTIFY_TELEPORT);

	{
		if (!dest_map->container()->get_map(map()->get_name())) {
			map()->container()->remove_player(myself);
			dest_map->container()->add_player(myself);
		}

		if (coords == MapCoords(0, 0))
			coords = dest_map->get_random_accessible_coordinates();

		dest_map->ensure_grid_for_entity(this, coords);
		set_map(dest_map);
		set_map_coords(coords);
	}

	get_session()->clif()->notify_move_to_map(dest_map->get_name(), coords.x(), coords.y());

	on_map_enter();

	return true;
}

void Player::send_npc_dialog(uint32_t npc_guid, std::string dialog)
{
	get_session()->clif()->notify_npc_dialog(npc_guid, dialog);
}

void Player::send_npc_next_dialog(uint32_t npc_guid)
{
	get_session()->clif()->notify_npc_next_dialog(npc_guid);
}

void Player::send_npc_close_dialog(uint32_t npc_guid)
{
	get_session()->clif()->notify_npc_close_dialog(npc_guid);
}

void Player::send_npc_menu_list(uint32_t npc_guid, std::string const &menu)
{
	get_session()->clif()->notify_npc_menu_list(npc_guid, menu);
}

void Player::on_item_equip(std::shared_ptr<const item_entry_data> item)
{
	std::shared_ptr<const item_config_data> itemd = ItemDB->get_item_by_id(item->item_id);
	std::shared_ptr<Traits::Status> s = status();

	if (item->type == IT_TYPE_WEAPON) {
		s->status_atk()->set_weapon_type(itemd->sub_type.weapon_t);
		s->equip_atk()->on_weapon_changed();
		s->aspd()->on_weapon_changed();
	}
}

void Player::on_item_unequip(std::shared_ptr<const item_entry_data> item)
{
	std::shared_ptr<const item_config_data> itemd = ItemDB->get_item_by_id(item->item_id);
	std::shared_ptr<Traits::Status> s = status();

	if (item->type == IT_TYPE_WEAPON) {
		s->status_atk()->set_weapon_type(IT_WT_FIST);
		s->equip_atk()->on_weapon_changed();
		s->aspd()->on_weapon_changed();
	}
}

void Player::on_map_enter()
{
	force_movement_stop_internal(false);
    //get_packet_handler()->Send_ZC_MAPPROPERTY_R2(get_map());

	inventory()->notify_all();

	// clear viewport
	get_viewport_entities().clear();

	update_viewport();

	notify_nearby_players_of_spawn();

	// Notify learnt skill list.
	get_session()->clif()->notify_learnt_skill_list();
}

void Player::on_status_effect_start(std::shared_ptr<status_change_entry> sce)
{
	get_session()->clif()->notify_status_change(sce->type, guid(), 1, sce->current_time, sce->val1, sce->val2, sce->val3);
}

void Player::on_status_effect_end(std::shared_ptr<status_change_entry> sce)
{
	get_session()->clif()->notify_status_change_end(sce->type, guid(), 0);
}

void Player::on_status_effect_change(std::shared_ptr<status_change_entry> sce)
{

}

void Player::notify_in_area(ByteBuffer &buf, player_notifier_type type, uint16_t range)
{
	GridPlayerNotifier notifier(buf, static_cast<Entity *>(this)->shared_from_this(), type);
	GridReferenceContainerVisitor<GridPlayerNotifier, GridReferenceContainer<AllEntityTypes>> container(notifier);

	map()->visit_in_range(map_coords(), container, range);
}


bool Player::job_change(int32_t job_id)
{
	std::shared_ptr<const job_config_data> job = JobDB->get_job_by_id(job_id);

	if (job == nullptr) {
		HLog(error) << "Player::job_change: Invalid job_id " << job_id << " provided, job was not found or not supported.";
		return false;
	}

	set_job_id(job_id);
	status()->base_appearance()->set(job_id);

	return true;
}

bool Player::perform_skill(int16_t skill_id, int16_t skill_lv)
{
	std::shared_ptr<const skill_config_data> sk_d = SkillDB->get_skill_by_id(skill_id);

    if (sk_d == nullptr) {
        HLog(warning) << "Tried to perform skill for non-existent id " << skill_id << ", ignoring...";
        return false;
    }

    try {
        sol::load_result fx = lua_state()->load_file("scripts/skills/" + sk_d->name + ".lua");
        sol::protected_function_result result = fx(shared_from_this(), skill_id, skill_lv);
        if (!result.valid()) {
            sol::error err = result;
            HLog(error) << "Entity::perform_skill: " << err.what();
        }
    } catch (sol::error &e) {
        HLog(error) << "Entity::perform_skill: " << e.what();
        return false;
    }

    return true;
}

bool Player::on_skill_failure(int16_t skill_id, int message_type, int item_id, skill_use_fail_cause_type cause)
{
	get_session()->clif()->notify_skill_fail(skill_id, message_type, item_id, cause);
	return true;
}

bool Player::perform_action(player_action_type action)
{
	switch(action)
	{
		case PLAYER_ACT_SIT:
			get_session()->clif()->notify_action(PLAYER_ACT_SIT);
			break;
		case PLAYER_ACT_STAND:
			get_session()->clif()->notify_action(PLAYER_ACT_STAND);
			break;
		case PLAYER_ACT_ATTACK:
		case PLAYER_ACT_ATTACK_REPEAT:
			break;
		default:
			break;
	};

	return true;
}

bool Player::attack(std::shared_ptr<Entity> e, bool continuous = false)
{
	//set_combat(std::make_shared<Entities::Combat>(shared_from_this(), std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count()));
	map()->container()->getScheduler().Schedule(0, get_scheduler_task_id(ENTITY_SCHEDULE_ATTACK),
		[this] (TaskContext context) {

		});
}
