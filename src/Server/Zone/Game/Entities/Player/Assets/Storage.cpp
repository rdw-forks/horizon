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

#include "Storage.hpp"
#include "Inventory.hpp"
#include "Server/Zone/Game/Entities/Player/Player.hpp"
#include "Server/Zone/Game/StaticDB/ItemDB.hpp"
#include "Server/Zone/Interface/ZoneClientInterface.hpp"
#include "Server/Zone/Session/ZoneSession.hpp"
#include "Server/Zone/Zone.hpp"

using namespace Horizon::Zone::Assets;

Storage::Storage(std::shared_ptr<Horizon::Zone::Entities::Player> player, int32_t storage_id, std::string name, uint32_t max_storage)
: _player(player), _storage_id(storage_id), _name(name), _max_storage(max_storage)
{
}

Storage::~Storage()
{
}

int16_t Storage::get_free_index()
{
	for (auto i = _storage_items.begin(); i != _storage_items.end(); i++) {
		if (*i == nullptr)
			return std::distance(_storage_items.begin(), i);
	}

	_storage_items.resize(_storage_items.size() + 1);

	return _storage_items.size() - 1;
}
Horizon::Zone::storage_add_item_result_type Storage::add_item_from_inventory(int16_t inventory_index, int amount)
{
    std::shared_ptr<item_entry_data> item = player()->inventory()->get_item(inventory_index);

    if (item == nullptr)
        return Horizon::Zone::storage_add_item_result_type::STORAGE_ADD_INVALID;

    if (amount == 0)
        return Horizon::Zone::storage_add_item_result_type::STORAGE_ADD_INVALID;

    if (_storage_items.size() >= _max_storage)
        return Horizon::Zone::storage_add_item_result_type::STORAGE_ADD_OVER_QUANTITY;

    if (item->amount > MAX_STORAGE_STACK_LIMIT)
        return Horizon::Zone::storage_add_item_result_type::STORAGE_ADD_OVER_STACK_LIMIT;
	
	if (add_item(item, amount) == Horizon::Zone::storage_add_item_result_type::STORAGE_ADD_SUCCESS)
	  	player()->inventory()->remove_item(inventory_index, amount, item_deletion_reason_type::ITEM_DEL_TOSTORAGE);

    return Horizon::Zone::storage_add_item_result_type::STORAGE_ADD_SUCCESS;
}

Horizon::Zone::storage_add_item_result_type Storage::add_item(std::shared_ptr<item_entry_data> item, int amount)
{
    if (amount == 0)
        return Horizon::Zone::storage_add_item_result_type::STORAGE_ADD_INVALID;

	// Check if item is stackable
	if (item->is_stackable()) {
		// Check if item exists in inventory.
		auto storitem = std::find_if(_storage_items.begin(), _storage_items.end(), 
			[&item] (std::shared_ptr<item_entry_data> storeit) {
				if (storeit == nullptr)
					return false;
				return (storeit->amount < MAX_STORAGE_STACK_LIMIT && *storeit == *item); 
			}
		);
		// If item was found in inventory...
		if (storitem != _storage_items.end()) {
			std::shared_ptr<item_entry_data> store_item = *storitem;
			// Check if amount exeeds stack size.
			if (store_item->amount + amount > MAX_STORAGE_STACK_LIMIT) {
				// Add appropriately
				int left_amt = store_item->amount - MAX_STORAGE_STACK_LIMIT;
				store_item->amount += left_amt;
				item->amount -= left_amt;
				if (amount - left_amt > 0)
	  				add_item_from_inventory(item->index.inventory, amount - left_amt);
				return Horizon::Zone::storage_add_item_result_type::STORAGE_ADD_SUCCESS;
			} else {
				store_item->amount += amount;
			}
            player()->get_session()->clif()->notify_storage_add_item(store_item, amount);
		} else {
			int16_t index = get_free_index();

			std::shared_ptr<item_entry_data> item_new_stack = std::make_shared<item_entry_data>(*item);
			item_new_stack->amount = amount;
			item_new_stack->storage_type = ITEM_STORE_STORAGE;
			item_new_stack->index.storage = index + 1;
			_storage_items[index] = item_new_stack;
            player()->get_session()->clif()->notify_storage_add_item(item_new_stack, amount);
		}
	} else {
		int16_t index = get_free_index();

		item->amount = 1;
		item->storage_type = ITEM_STORE_STORAGE;
		item->index.storage = index + 1;
		_storage_items[index] = item;
        player()->get_session()->clif()->notify_storage_add_item(item, 1);
	}

	return Horizon::Zone::storage_add_item_result_type::STORAGE_ADD_SUCCESS;
}

Horizon::Zone::storage_to_inventory_result_type Storage::add_item_to_inventory(int storage_index, int amount)
{
    std::shared_ptr<item_entry_data> item = get_item(storage_index);

    if (item == nullptr)
        return Horizon::Zone::storage_to_inventory_result_type::STORAGE_TO_INVENTORY_INVALID;

	if (amount > MAX_STORAGE_STACK_LIMIT)
		return Horizon::Zone::storage_to_inventory_result_type::STORAGE_TO_INVENTORY_OVER_STACK_LIMIT;

    if (remove_item(storage_index, amount) == Horizon::Zone::storage_remove_item_result_type::STORAGE_REMOVE_SUCCESS)
	    player()->get_session()->clif()->notify_storage_remove_item(storage_index, amount);
	else
		return Horizon::Zone::storage_to_inventory_result_type::STORAGE_TO_INVENTORY_INVALID;
    
    player()->inventory()->add_item(item, amount);

    return Horizon::Zone::storage_to_inventory_result_type::STORAGE_TO_INVENTORY_SUCCESS;
}
std::shared_ptr<item_entry_data> Storage::get_item(int32_t storage_index)
{
	if (storage_index - 1 < 0)
		return nullptr;

	if (_storage_items.size() - 1 < storage_index - 1) {
		HLog(error) << "Storage::get_item: Attempted to get item from storage index " << storage_index << " but storage size is " << _storage_items.size();
		return nullptr;
	}

    return _storage_items[storage_index - 1];
}

Horizon::Zone::storage_remove_item_result_type Storage::remove_item(int32_t storage_index, int amount)
{
    std::shared_ptr<item_entry_data> item = get_item(storage_index);

    if (item == nullptr)
        return Horizon::Zone::storage_remove_item_result_type::STORAGE_REMOVE_INVALID;

    if (item->amount < amount)
        return Horizon::Zone::storage_remove_item_result_type::STORAGE_REMOVE_INVALID;

    if (amount > item->amount)
		return Horizon::Zone::storage_remove_item_result_type::STORAGE_REMOVE_INVALID;

    item->amount -= amount;

    if (item->amount == 0)
        _storage_items[storage_index - 1] = nullptr;

    return Horizon::Zone::storage_remove_item_result_type::STORAGE_REMOVE_SUCCESS;
}

void Storage::notify_all()
{
    if (_storage_items.size()) {
        notify_normal();
        notify_equips();
    }
    player()->get_session()->clif()->notify_storage_size(_storage_items.size(), _max_storage);
    player()->set_current_storage_id(_storage_id);
}

void Storage::notify_normal()
{
	std::vector<std::shared_ptr<const item_entry_data>> normal_items;

	for (auto nit = _storage_items.begin(); nit != _storage_items.end(); nit++) {
		if ((*nit)->is_equipment() == false)
			normal_items.push_back(*nit);
	}

	player()->get_session()->clif()->notify_storage_normal_items(_name, normal_items);
}

void Storage::notify_equips()
{
	std::vector<std::shared_ptr<const item_entry_data>> equipments;

	for (auto eit = _storage_items.begin(); eit != _storage_items.end(); eit++) {
		if ((*eit)->is_equipment())
			equipments.push_back(*eit);
	}

	player()->get_session()->clif()->notify_storage_equip_items(_name, equipments);
}

int32_t Storage::save()
{
	int32_t changes = 0;

	_saved_storage_items.clear();

	std::copy(_storage_items.begin(), _storage_items.end(), std::inserter(_saved_storage_items, _saved_storage_items.end()));

	mysqlx::Session session = sZone->database_pool()->get_connection();
	
	try {
		session.sql("DELETE FROM `storage` WHERE `account_id` = ? AND `storage_id` = ?")
			.bind(player()->account()._account_id, _storage_id)
			.execute();

		mysqlx::Schema schema = session.getSchema("horizon");
		mysqlx::Table table = schema.getTable("storage");
		mysqlx::TableInsert ti = table.insert("account_id", "storage_id", "item_id", "amount", "equip_location_mask",
			"is_identified", "refine_level", "element_type", "slot_item_id_0", "slot_item_id_1", "slot_item_id_2", "slot_item_id_3", "opt_idx0", "opt_val0",
			"opt_idx1", "opt_val1", "opt_idx2", "opt_val2", "opt_idx3", "opt_val3", "opt_idx4", "opt_val4", "hire_expire_date", "is_favorite", "is_broken", "bind_type", "unique_id");

		int count = 0;
		for (auto mit_i = _saved_storage_items.begin(); mit_i != _saved_storage_items.end(); mit_i++) {
			std::shared_ptr<const item_entry_data> mit = *mit_i;
			
			if (mit == nullptr)
				continue;

			ti.values(player()->account()._account_id,
                (int)_storage_id,
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

		changes = count;
	}
	catch (mysqlx::Error& error) {
		HLog(error) << "Storage::save:" << error.what();
		return false;
	}
	catch (std::exception& error) {
		HLog(error) << "Storage::save:" << error.what();
		return false;
	}
	
	sZone->database_pool()->release_connection(std::move(session));

	HLog(info) << "Saved Storage (" << _name << ") for (Account ID: " << player()->account()._account_id << ") with " << changes << " changes.";

	return changes;
}

int32_t Storage::load()
{	
	mysqlx::Session session = sZone->database_pool()->get_connection();
	
	try {
		mysqlx::RowResult rr = session.sql("SELECT `item_id`, `amount`, `equip_location_mask`, `refine_level`, `slot_item_id_0`,"
			"`slot_item_id_1`, `slot_item_id_2`, `slot_item_id_3`, `hire_expire_date`, `element_type`, `opt_idx0`, `opt_val0`, `opt_idx1`, `opt_val1`,"
			"`opt_idx2`, `opt_val2`, `opt_idx3`, `opt_val3`, `opt_idx4`, `opt_val4`, `is_identified`, `is_broken`, `is_favorite`, `bind_type`, `unique_id`"
			" FROM `storage` WHERE `account_id` = ? AND `storage_id` = ?")
			.bind(player()->account()._account_id, _storage_id)
			.execute();

		std::list<mysqlx::Row> rows = rr.fetchAll();

		if (_storage_items.size() != 0) {
			HLog(warning) << "Attempt to synchronize the saved storage, which should be empty at the time of load or re-load, size: " << _storage_items.size();
			return 0;
		}

		int storage_index = 1;
		for (std::list<mysqlx::Row>::iterator r = rows.begin(); r != rows.end(); r++) {
			mysqlx::Row row = *r;
			item_entry_data i;

			std::shared_ptr<const item_config_data> d = ItemDB->get_item_by_id(row[0].get<int>());
            
            i.storage_type = ITEM_STORE_STORAGE;
            i.index.storage = storage_index++;
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

			_saved_storage_items.push_back(item);
			_storage_items.push_back(item);
		}
	}
	catch (mysqlx::Error& error) {
		HLog(error) << "Storage::load:" << error.what();
		return false;
	}
	catch (std::exception& error) {
		HLog(error) << "Storage::load:" << error.what();
		return false;
	}

	sZone->database_pool()->release_connection(std::move(session));
	
	HLog(info) << "Loaded Storage (" << _name << ") for (Account ID: " << player()->account()._account_id << ") with " << _storage_items.size() << " items.";

	return _storage_items.size();
}
