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

#include "Inventory.hpp"

#include "Server/Zone/Game/Map/Grid/Notifiers/GridNotifiers.hpp"
#include "Server/Zone/Game/Map/Grid/Container/GridReferenceContainer.hpp"
#include "Server/Zone/Game/Map/Grid/Container/GridReferenceContainerVisitor.hpp"
#include "Server/Zone/Game/Entities/Player/Player.hpp"
#include "Server/Zone/Game/StaticDB/ItemDB.hpp"
#include "Server/Zone/Game/StaticDB/JobDB.hpp"
#include "Server/Zone/Game/Entities/Traits/Status.hpp"
#include "Server/Zone/Game/Entities/Traits/AttributesImpl.hpp"
#include "Server/Zone/Interface/ZoneClientInterface.hpp"
#include "Server/Zone/Session/ZoneSession.hpp"
#include "Server/Zone/Zone.hpp"

using namespace Horizon::Zone::Entities::Traits;
using namespace Horizon::Zone::Assets;

Inventory::Inventory(std::shared_ptr<Horizon::Zone::Entities::Player> player, uint32_t max_storage)
: _player(player), _max_storage(max_storage)
{
	_equipments[IT_EQPI_ACC_L].first = IT_EQPM_ACC_L;
	_equipments[IT_EQPI_ACC_R].first = IT_EQPM_ACC_R;
	_equipments[IT_EQPI_SHOES].first = IT_EQPM_SHOES;
	_equipments[IT_EQPI_GARMENT].first = IT_EQPM_GARMENT;
	_equipments[IT_EQPI_HEAD_LOW].first = IT_EQPM_HEAD_LOW;
	_equipments[IT_EQPI_HEAD_MID].first = IT_EQPM_HEAD_MID;
	_equipments[IT_EQPI_HEAD_TOP].first = IT_EQPM_HEAD_TOP;
	_equipments[IT_EQPI_ARMOR].first = IT_EQPM_ARMOR;
	_equipments[IT_EQPI_HAND_L].first = IT_EQPM_HAND_L;
	_equipments[IT_EQPI_HAND_R].first = IT_EQPM_HAND_R;
	_equipments[IT_EQPI_COSTUME_TOP].first = IT_EQPM_COSTUME_HEAD_TOP;
	_equipments[IT_EQPI_COSTUME_MID].first = IT_EQPM_COSTUME_HEAD_MID;
	_equipments[IT_EQPI_COSTUME_LOW].first = IT_EQPM_COSTUME_HEAD_LOW;
	_equipments[IT_EQPI_COSTUME_GARMENT].first = IT_EQPM_COSTUME_GARMENT;
	_equipments[IT_EQPI_AMMO].first = IT_EQPM_AMMO;
	_equipments[IT_EQPI_SHADOW_ARMOR].first = IT_EQPM_SHADOW_ARMOR;
	_equipments[IT_EQPI_SHADOW_WEAPON].first = IT_EQPM_SHADOW_WEAPON;
	_equipments[IT_EQPI_SHADOW_SHIELD].first = IT_EQPM_SHADOW_SHIELD;
	_equipments[IT_EQPI_SHADOW_SHOES].first = IT_EQPM_SHADOW_SHOES;
	_equipments[IT_EQPI_SHADOW_ACC_R].first = IT_EQPM_SHADOW_ACC_R;
	_equipments[IT_EQPI_SHADOW_ACC_L].first = IT_EQPM_SHADOW_ACC_L;
}

Inventory::~Inventory()
{
	//
}

/**
 * Inventory initialization for player, called after Status is computed and notified.
 */
void Inventory::initialize()
{
	for (auto item : _inventory_items) {
		player()->status()->current_weight()->add_base(item->config->weight * item->amount);
	}

	player()->get_session()->clif()->notify_compound_attribute_update(STATUS_CURRENT_WEIGHT, player()->status()->current_weight()->total());
}

bool Inventory::use_item(uint32_t inventory_index, uint32_t guid)
{
	std::shared_ptr<item_entry_data> inv_item = _inventory_items.at(inventory_index - 2);

	if (inv_item == nullptr)
		return false;

	if (inv_item->config == nullptr) {
		player()->get_session()->clif()->notify_use_item(inv_item, false);
		return false;
	}

	player()->get_session()->clif()->notify_use_item(inv_item, true);
	return true;
}

item_equip_result_type Inventory::equip_item(uint32_t inventory_index, uint16_t equip_location_mask)
{
	uint32_t job_id = player()->job_id();
	std::shared_ptr<item_entry_data> inv_item = _inventory_items.at(inventory_index - 2);

	if (inv_item == nullptr) {
		HLog(debug) << "Inventory::equip_item: Could not wear item at inventory index " << inventory_index << " - Inventory data not found.";
		return IT_EQUIP_FAIL;
	}

	if (inv_item->config == nullptr) {
		player()->get_session()->clif()->notify_equip_item(inv_item, IT_EQUIP_FAIL);
		return IT_EQUIP_FAIL;
	}

	if (inv_item->current_equip_location_mask != 0 || inv_item->config->equip_location_mask != equip_location_mask) {
		player()->get_session()->clif()->notify_equip_item(inv_item, IT_EQUIP_FAIL);
		return IT_EQUIP_FAIL;
	}

	auto req_job_it = std::find_if(inv_item->config->requirements.job_ids.begin(), inv_item->config->requirements.job_ids.end(),
		[job_id](uint32_t id) {
			return job_id == id;
		});
	if (req_job_it == inv_item->config->requirements.job_ids.end()) {
		player()->get_session()->clif()->notify_equip_item(inv_item, IT_EQUIP_FAIL);
		return IT_EQUIP_FAIL;
	}

	if (inv_item->config->config.bind_on_equip != 0 && inv_item->bind_type == IT_BIND_NONE) {
		inv_item->bind_type = IT_BIND_CHARACTER;
		player()->get_session()->clif()->notify_bind_on_equip(inv_item->inventory_index);
	}

	inv_item->current_equip_location_mask = calculate_current_equip_location_mask(inv_item->config);

	add_to_equipment_list(inv_item);

	if (inv_item->type == IT_TYPE_AMMO) {
		player()->get_session()->clif()->notify_equip_arrow(inv_item);
		player()->get_session()->clif()->notify_action_failure(3);
	} else {
		HLog(debug) << "Inventory Item " << inv_item->inventory_index << " - " << inv_item->item_id << "worn.";
		
		player()->get_session()->clif()->notify_equip_item(inv_item, IT_EQUIP_SUCCESS);
		
		player()->on_item_equip(inv_item);
		
		print_inventory();
	}

	return IT_EQUIP_SUCCESS;
}

item_unequip_result_type Inventory::unequip_item(uint32_t inventory_index)
{
	std::shared_ptr<item_entry_data> inv_item = _inventory_items.at(inventory_index - 2);

	if (inv_item == nullptr) {
		player()->get_session()->clif()->notify_unequip_item(inv_item, IT_UNEQUIP_FAIL);
		return IT_UNEQUIP_FAIL;
	}

	if (inv_item->config == nullptr) {
		player()->get_session()->clif()->notify_unequip_item(inv_item, IT_UNEQUIP_FAIL);
		return IT_UNEQUIP_FAIL;
	}

	player()->get_session()->clif()->notify_unequip_item(inv_item, IT_UNEQUIP_SUCCESS);

	remove_from_equipment_list(inv_item);

	player()->on_item_unequip(inv_item);

	print_inventory();

	return IT_UNEQUIP_SUCCESS;
}

void Inventory::add_to_equipment_list(std::shared_ptr<item_entry_data> item)
{
	for (int i = 0; i < (item_equip_location_index) IT_EQPI_MAX; i++) {
		auto &equip = equipments()[i];
		std::shared_ptr<item_entry_data> id = equip.second.lock();

		// Unequip the existing item and wear the new item.
		if ((item->current_equip_location_mask & equip.first)) {
			if (!equip.second.expired() && unequip_item(id->inventory_index) == IT_UNEQUIP_FAIL)
				return;
			equip.second = item;
		}
	}
}

void Inventory::remove_from_equipment_list(std::shared_ptr<item_entry_data> item)
{
	for (int i = 0; i < (item_equip_location_index)  IT_EQPI_MAX; i++) {
		auto &equip = equipments()[i];
		std::shared_ptr<const item_entry_data> id = equip.second.lock();

		if ((item->current_equip_location_mask & equip.first)) {
			item->current_equip_location_mask &= ~equip.first;
			equip.second.reset();
		}
	}
}

uint32_t Inventory::calculate_current_equip_location_mask(std::shared_ptr<const item_config_data> item)
{
	job_class_mask job_mask = JobDB->job_id_to_mask((job_class_type) player()->job_id());
	uint32_t current_equip_location_mask = item->equip_location_mask;

	if (item->type == IT_TYPE_WEAPON) {
		if (item->sub_type.weapon_t == IT_WT_DAGGER ||
			item->sub_type.weapon_t == IT_WT_1HSWORD ||
			item->sub_type.weapon_t == IT_WT_1HAXE) {
			if ((job_mask & JMASK_ASSASSIN) == JMASK_ASSASSIN
				 || (job_mask & JMASK_KAGEROUOBORO) == JMASK_KAGEROUOBORO) {
				if (item->equip_location_mask == IT_EQPM_HAND_R)
					current_equip_location_mask = IT_EQPM_ARMS;
				if (item->equip_location_mask == IT_EQPM_SHADOW_WEAPON)
					current_equip_location_mask = IT_EQPM_SHADOW_ARMS;
			}
		}
	}

	if (current_equip_location_mask == IT_EQPM_ACC)
		current_equip_location_mask = equipments()[IT_EQPI_ACC_L].second.expired() ? IT_EQPM_ACC_L : IT_EQPM_ACC_R;
	else if (current_equip_location_mask == IT_EQPM_ARMS && item->equip_location_mask == IT_EQPM_WEAPON)
		current_equip_location_mask = equipments()[IT_EQPI_HAND_L].second.expired() ? IT_EQPM_HAND_L : IT_EQPM_HAND_R;
	else if (current_equip_location_mask == IT_EQPM_SHADOW_ACC)
		current_equip_location_mask = equipments()[IT_EQPI_SHADOW_ACC_L].second.expired() ? IT_EQPM_SHADOW_ACC_L : IT_EQPM_SHADOW_ACC_R;
	else if (current_equip_location_mask == IT_EQPM_SHADOW_ARMS && item->equip_location_mask == IT_EQPM_SHADOW_WEAPON)
		current_equip_location_mask = equipments()[IT_EQPI_SHADOW_WEAPON].second.expired() ? IT_EQPM_SHADOW_WEAPON : IT_EQPM_SHADOW_SHIELD;

	return current_equip_location_mask;
}

void Inventory::print_inventory()
{
	HLog(debug) << " -- Inventory List --";
	for (auto i : _inventory_items)
		HLog(debug) << "Idx: " << i->inventory_index << " ItemID: " << i->item_id << " Amount: " << i->amount;


	HLog(debug) << " -- Equipments List --";
	for (int i = 0; i < IT_EQPI_MAX; i++) {
		auto &equip = equipments()[i];
		std::shared_ptr<const item_entry_data> id = equip.second.lock();
		if (id != nullptr)
			HLog(debug) << "Loc:" << std::hex << id->current_equip_location_mask << " Loc2: " << id->actual_equip_location_mask << " Idx: " << std::dec << id->inventory_index << " ItemID: " << id->item_id << " Amount: " << id->amount;
	}
}


void Inventory::notify_all()
{
	notify_only_equipments();
	notify_without_equipments();
}

void Inventory::notify_without_equipments()
{
	std::vector<std::shared_ptr<const item_entry_data>> normal_items;

	for (auto nit = _inventory_items.begin(); nit != _inventory_items.end(); nit++) {
		if ((*nit)->is_equipment() == false)
			normal_items.push_back((*nit));
	}

	player()->get_session()->clif()->notify_normal_item_list(normal_items);

}

void Inventory::notify_only_equipments()
{
	std::vector<std::shared_ptr<const item_entry_data>> equipments;

	for (auto eit = _inventory_items.begin(); eit != _inventory_items.end(); eit++) {
		if ((*eit)->is_equipment())
			equipments.push_back(*eit);
	}

	player()->get_session()->clif()->notify_equipment_item_list(equipments);
}

inventory_addition_result_type Inventory::add_item(uint32_t item_id, uint16_t amount, bool is_identified)
{
	item_entry_data data;
	std::shared_ptr<const item_config_data> item = ItemDB->get_item_by_id(item_id);
	std::shared_ptr<const job_config_data> job = JobDB->get_job_by_id(player()->job_id());
	std::shared_ptr<Horizon::Zone::Traits::CurrentWeight> current_weight = player()->status()->current_weight();
	std::shared_ptr<Horizon::Zone::Traits::MaxWeight> max_weight = player()->status()->max_weight();

	if (item == nullptr)
		return INVENTORY_ADD_INVALID;

	if (*current_weight + (amount * item->weight) > max_weight->total()) {
		notify_add(data, amount, INVENTORY_ADD_OVER_WEIGHT);
		return INVENTORY_ADD_OVER_WEIGHT;
	}

	if (item->stack.inventory > 0 && (amount > item->stack.inventory)) {
		notify_add(data, amount, INVENTORY_ADD_OVER_STACK_LIMIT);
		return INVENTORY_ADD_OVER_STACK_LIMIT;
	}

	if (amount > MAX_INVENTORY_STACK_LIMIT) {
		notify_add(data, amount, INVENTORY_ADD_OVER_QUANTITY);
		return INVENTORY_ADD_OVER_QUANTITY;
	}

	// Copy item properties from static db entry.
	data.item_id = item->item_id;
	data.type = item->type;
	data.actual_equip_location_mask = item->equip_location_mask;
	data.bind_type = IT_BIND_NONE;
	data.info.is_identified = is_identified;
	data.info.is_favorite = 0;
	data.config = item;

	if (_inventory_items.size() >= max_storage()) {
		notify_add(data, amount, INVENTORY_ADD_NO_INV_SPACE);
		return INVENTORY_ADD_NO_INV_SPACE;
	}

	// Check if item is stackable
	if (data.is_stackable()) {
		// Check if item exists in inventory.
		auto invitem = std::find_if(_inventory_items.begin(), _inventory_items.end(), 
			[&data] (std::shared_ptr<item_entry_data> invit) { return (invit->amount < MAX_INVENTORY_STACK_LIMIT && *invit == data); }
		);
		// If item was found in inventory...
		if (invitem != _inventory_items.end()) {
			// Check if amount exeeds stack size.
			if ((*invitem)->amount + amount > MAX_INVENTORY_STACK_LIMIT) {
				// Add appropriately
				int left_amt = (*invitem)->amount - MAX_INVENTORY_STACK_LIMIT;
				(*invitem)->amount += left_amt;
				amount -= left_amt;
				add_item(item_id, amount, is_identified);
			} else {
				(*invitem)->amount += amount;
				notify_add(*(*invitem), amount, INVENTORY_ADD_SUCCESS);

				current_weight->add_base(item->weight * amount);
				player()->get_session()->clif()->notify_compound_attribute_update(STATUS_CURRENT_WEIGHT, current_weight->total());
			}
		} else {
			data.amount += amount;
			data.inventory_index = _inventory_items.size() + 2;
			_inventory_items.push_back(std::make_shared<item_entry_data>(data));
			notify_add(data, amount, INVENTORY_ADD_SUCCESS);

			current_weight->add_base(item->weight * amount);
			player()->get_session()->clif()->notify_compound_attribute_update(STATUS_CURRENT_WEIGHT, current_weight->total());
		}
	} else {
		for (int i = 0; i < amount; i++) {
			std::shared_ptr<item_entry_data> itd = std::make_shared<item_entry_data>(data);
			itd->unique_id = player()->new_unique_id();
			itd->amount = 1;
			itd->inventory_index = _inventory_items.size() + 2;
			_inventory_items.push_back(itd);
			notify_add(*itd, itd->amount, INVENTORY_ADD_SUCCESS);
		}
		current_weight->add_base(item->weight * amount);
		player()->get_session()->clif()->notify_compound_attribute_update(STATUS_CURRENT_WEIGHT, current_weight->total());
	}

	return INVENTORY_ADD_SUCCESS;
}

void Inventory::notify_add(item_entry_data const &data, uint16_t amount, inventory_addition_result_type result)
{
	item_inventory_addition_notif_type notif_type;

	switch (result)
	{
	case INVENTORY_ADD_SUCCESS: notif_type = ITEM_INV_ADD_SUCCESS; break;
	case INVENTORY_ADD_INVALID: notif_type = ITEM_INV_ADD_INVALID; break;
	case INVENTORY_ADD_OVER_WEIGHT: notif_type = ITEM_INV_ADD_OVER_WEIGHT; break;
	case INVENTORY_ADD_NO_INV_SPACE: notif_type = ITEM_INV_ADD_NO_INV_SPACE; break;
	case INVENTORY_ADD_OVER_QUANTITY: notif_type = ITEM_INV_ADD_OVER_QUANTITY; break;
	case INVENTORY_ADD_OVER_STACK_LIMIT: notif_type = ITEM_INV_ADD_OVER_STACK_LIMIT; break;
	}

	player()->get_session()->clif()->notify_pickup_item(data, amount, notif_type);
}

void Inventory::notify_deletion(uint16_t idx, uint16_t amount, inventory_deletion_reason_type reason)
{

}

void Inventory::notify_drop(uint16_t idx, uint16_t amount)
{

}

void Inventory::notify_move_fail(uint16_t idx, bool silent)
{

}

int32_t Inventory::save()
{
	int32_t changes = 0;

	for (auto &i : _inventory_items) {
		auto mit_i = std::find_if(_saved_inventory_items.begin(), _saved_inventory_items.end(), [&i](std::shared_ptr<item_entry_data> si) {
			return *si == *i; // 'item_entry_data' and 'std::shared_ptr<item_entry_data>'
		});

		if (mit_i != _saved_inventory_items.end()) {
			std::shared_ptr<item_entry_data> mit = *mit_i;
			bool changed = false;

			if (mit->amount != i->amount) {
				mit->amount = i->amount;
				changed = true;
			}
			if (mit->current_equip_location_mask != i->current_equip_location_mask) {
				mit->current_equip_location_mask = i->current_equip_location_mask;
				changed = true;
			}
			if (changed)
				changes++;
		} else {
			_saved_inventory_items.push_back(i);
			changes++;
		}
	}

	// Delete Non-existent items.
	for (auto mit = _saved_inventory_items.begin(); mit != _saved_inventory_items.end(); mit++) {
		auto it = std::find_if(_inventory_items.begin(), _inventory_items.end(), [&mit] (std::shared_ptr<item_entry_data> it) {
			return *it == *(*mit); // 'item_entry_data' and 'std::shared_ptr<item_entry_data>'
		});

		if (it == _inventory_items.end()) {
			mit = _saved_inventory_items.erase(mit);
			changes++;
		}
	}

	mysqlx::Session session = sZone->database_pool()->get_connection();
	
	try {
		session.sql("DELETE FROM `character_inventory` WHERE `char_id` = ?")
			.bind(player()->character()._character_id)
			.execute();

		mysqlx::Schema schema = session.getSchema("horizon");
		mysqlx::Table table = schema.getTable("character_inventory");
		mysqlx::TableInsert ti = table.insert("char_id", "item_id", "amount", "equip_location_mask",
			"is_identified", "refine_level", "element_type", "slot_item_id_0", "slot_item_id_1", "slot_item_id_2", "slot_item_id_3", "opt_idx0", "opt_val0",
			"opt_idx1", "opt_val1", "opt_idx2", "opt_val2", "opt_idx3", "opt_val3", "opt_idx4", "opt_val4", "hire_expire_date", "is_favorite", "is_broken", "bind_type", "unique_id");

		int count = 0;
		for (auto mit_i = _saved_inventory_items.begin(); mit_i != _saved_inventory_items.end(); mit_i++) {
			std::shared_ptr<const item_entry_data> mit = *mit_i;
			ti.values(player()->character()._character_id,
				(int)mit->item_id,
				(int)mit->amount,
				(int)mit->current_equip_location_mask,
				(int)mit->info.is_identified,
				(int)mit->refine_level,
				(int)mit->ele_type,
				(int)mit->slot_item_id[0],
				(int)mit->slot_item_id[1],
				(int)mit->slot_item_id[2],
				(int)mit->slot_item_id[3],
				(int)mit->option_data[0].get_index(),
				(int)mit->option_data[0].get_value(),
				(int)mit->option_data[1].get_index(),
				(int)mit->option_data[1].get_value(),
				(int)mit->option_data[2].get_index(),
				(int)mit->option_data[2].get_value(),
				(int)mit->option_data[3].get_index(),
				(int)mit->option_data[3].get_value(),
				(int)mit->option_data[4].get_index(),
				(int)mit->option_data[4].get_value(),
				(int)mit->hire_expire_date,
				(int)mit->info.is_favorite,
				(int)mit->info.is_broken,
				(int)mit->bind_type,
				(int64_t)mit->unique_id);

			count++;
		}

		if (count)
			ti.execute();
	}
	catch (mysqlx::Error& error) {
		HLog(error) << "Inventory::save:" << error.what();
		return false;
	}
	catch (std::exception& error) {
		HLog(error) << "Inventory::save:" << error.what();
		return false;
	}
	
	sZone->database_pool()->release_connection(std::move(session));

	return changes;
}

int32_t Inventory::load()
{	
	mysqlx::Session session = sZone->database_pool()->get_connection();
	
	try {
		mysqlx::RowResult rr = session.sql("SELECT `item_id`, `amount`, `equip_location_mask`, `refine_level`, `slot_item_id_0`,"
			"`slot_item_id_1`, `slot_item_id_2`, `slot_item_id_3`, `hire_expire_date`, `element_type`, `opt_idx0`, `opt_val0`, `opt_idx1`, `opt_val1`,"
			"`opt_idx2`, `opt_val2`, `opt_idx3`, `opt_val3`, `opt_idx4`, `opt_val4`, `is_identified`, `is_broken`, `is_favorite`, `bind_type`, `unique_id`"
			" FROM `character_inventory` WHERE `char_id` = ?")
			.bind(player()->character()._character_id)
			.execute();

		std::list<mysqlx::Row> rows = rr.fetchAll();

		if (_inventory_items.size() != 0) {
			HLog(warning) << "Attempt to synchronize the saved inventory, which should be empty at the time of load or re-load, size: " << _inventory_items.size();
			return 0;
		}

		int inventory_index = 2;
		for (std::list<mysqlx::Row>::iterator r = rows.begin(); r != rows.end(); r++) {
			mysqlx::Row row = *r;
			item_entry_data i;

			std::shared_ptr<const item_config_data> d = ItemDB->get_item_by_id(row[0].get<int>());

			i.inventory_index = inventory_index++;
			i.item_id = row[0].get<int>();
			i.type = d->type;
			i.amount = row[1].get<int>();
			i.current_equip_location_mask = row[2].get<int>();
			i.actual_equip_location_mask = d->equip_location_mask;
			i.refine_level = row[3].get<int>();
			i.config = d;

			i.slot_item_id[0] = row[4].get<int>();
			i.slot_item_id[1] = row[5].get<int>();
			i.slot_item_id[2] = row[6].get<int>();
			i.slot_item_id[3] = row[7].get<int>();

			i.hire_expire_date = row[8].get<int>();
			i.sprite_id = d->sprite_id;

			i.ele_type = (element_type)(int)row[9].get<int>();

			if (row[10].get<int>()) {
				i.option_data[0].set_index(row[10].get<int>());
				i.option_data[0].set_value(row[11].get<int>());
				i.option_count = 1;
			}

			if (row[12].get<int>()) {
				i.option_data[1].set_index(row[12].get<int>());
				i.option_data[1].set_value(row[13].get<int>());
				i.option_count = 2;
			}

			if (row[14].get<int>()) {
				i.option_data[2].set_index(row[14].get<int>());
				i.option_data[2].set_value(row[15].get<int>());
				i.option_count = 3;
			}

			if (row[16].get<int>()) {
				i.option_data[3].set_index(row[16].get<int>());
				i.option_data[3].set_value(row[17].get<int>());
				i.option_count = 4;
			}

			if (row[18].get<int>()) {
				i.option_data[4].set_index(row[18].get<int>());
				i.option_data[4].set_value(row[19].get<int>());
				i.option_count = 5;
			}

			i.info.is_identified = row[20].get<int>();
			i.info.is_broken = row[21].get<int>();
			i.info.is_favorite = row[22].get<int>();

			i.bind_type = (item_bind_type)(int)row[23].get<int>(); // int16_t
			i.unique_id = row[24].get<int>();

			std::shared_ptr<item_entry_data> item = std::make_shared<item_entry_data>(i);

			_saved_inventory_items.push_back(item);
			_inventory_items.push_back(item);
		}
	}
	catch (mysqlx::Error& error) {
		HLog(error) << "Inventory::load:" << error.what();
		return false;
	}
	catch (std::exception& error) {
		HLog(error) << "Inventory::load:" << error.what();
		return false;
	}

	sZone->database_pool()->release_connection(std::move(session));
	
	return _inventory_items.size();
}
