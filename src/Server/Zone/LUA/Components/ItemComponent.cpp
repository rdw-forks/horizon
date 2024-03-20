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

#include "ItemComponent.hpp"

#include "Server/Common/Configuration/Horizon.hpp"
#include "Server/Zone/Game/StaticDB/ItemDB.hpp"
#include "Server/Zone/Game/Map/Grid/Notifiers/GridNotifiers.hpp"

#include "ItemDefinitions.hpp"

using namespace Horizon::Zone;

void ItemComponent::sync_definitions(std::shared_ptr<sol::state> state)
{
	state->create_named_table("RefineType",
		"Armor", (int) REFINE_TYPE_ARMOR,
		"Weapon1", (int) REFINE_TYPE_WEAPON1,
		"Weapon2", (int) REFINE_TYPE_WEAPON2,
		"Weapon3", (int) REFINE_TYPE_WEAPON3,
		"Weapon4", (int) REFINE_TYPE_WEAPON4,
		"Max", (int) REFINE_TYPE_MAX
	);

	state->create_named_table("RefineChanceType",
		"Normal", (int) REFINE_CHANCE_TYPE_NORMAL,
		"Enriched", (int) REFINE_CHANCE_TYPE_ENRICHED,
		"EventNormal", (int) REFINE_CHANCE_TYPE_E_NORMAL,
		"EventEnriched", (int) REFINE_CHANCE_TYPE_E_ENRICHED,
		"Max", (int) REFINE_CHANCE_TYPE_MAX
	);

	state->create_named_table("WeaponType",
		"Fist", (int) IT_WT_FIST,
		"Dagger", (int) IT_WT_DAGGER,
		"OneHandedSword", (int) IT_WT_1HSWORD,
		"TwoHandedSword", (int) IT_WT_2HSWORD,
		"OneHandedSpear", (int) IT_WT_1HSPEAR,
		"TwoHandedSpear", (int) IT_WT_2HSPEAR,
		"OneHandedAxe", (int) IT_WT_1HAXE,
		"TwoHandedAxe", (int) IT_WT_2HAXE,
		"OneHandedMace", (int) IT_WT_1HMACE,
		"TwoHandedMace", (int) IT_WT_2HMACE,
		"OneHandedStaff", (int) IT_WT_STAFF,
		"Bow", (int) IT_WT_BOW,
		"Knuckle", (int) IT_WT_KNUCKLE,
		"MusicalInstrument", (int) IT_WT_MUSICAL,
		"Whip", (int) IT_WT_WHIP,
		"Book", (int) IT_WT_BOOK,
		"Katar", (int) IT_WT_KATAR,
		"Revolver", (int) IT_WT_REVOLVER,
		"Rifle", (int) IT_WT_RIFLE,
		"GatlingGun", (int) IT_WT_GATLING,
		"Shotgun", (int) IT_WT_SHOTGUN,
		"GrenadeLauncher", (int) IT_WT_GRENADE,
		"FuumaShuriken", (int) IT_WT_HUUMA,
		"TwoHandedStaff", (int) IT_WT_2HSTAFF,
		"DWDaggers", (int) IT_WT_DOUBLE_DAGGERS, ///< 2 daggers
		"DWSwords", (int) IT_WT_DOUBLE_SWORDS, ///< 2 swords
		"DWAxes", (int) IT_WT_DOUBLE_AXES, ///< 2 axes
		"DWDaggerSword", (int) IT_WT_DOUBLE_DAGGER_SWORD, ///< dagger + sword
		"DWDaggerAxe", (int) IT_WT_DOUBLE_DAGGER_AXE, ///< dagger + axe
		"DWSwordAxe", (int) IT_WT_DOUBLE_SWORD_AXE ///< sword + axe
	);

	state->create_named_table("WeaponTypeMask",
		"Ranged", (int) IT_WTM_RANGED,
		"Melee", (int) IT_WTM_MELEE
	);

	state->create_named_table("ItemLevelType",
		"Armor", (int) IT_LVL_ARMOR,
		"Weapon1", (int) IT_LVL_WEAPON1,
		"Weapon2", (int) IT_LVL_WEAPON2,
		"Weapon3", (int) IT_LVL_WEAPON3,
		"Weapon4", (int) IT_LVL_WEAPON4,
		"Max", (int) IT_LVL_MAX
	);

	state->create_named_table("ItemGenderType",
		"Female", (int) IT_GENDER_FEMALE,
		"Male", (int) IT_GENDER_MALE,
		"Any", (int) IT_GENDER_ANY
	);

	state->create_named_table("EquipLocationMask",
		"None", (int) IT_EQPM_NONE,
		"LowerHead", (int) IT_EQPM_HEAD_LOW,
		"RightHand", (int) IT_EQPM_HAND_R,
		"Garment", (int) IT_EQPM_GARMENT,
		"LeftAccessory", (int) IT_EQPM_ACC_L,
		"Armor", (int) IT_EQPM_ARMOR,
		"LeftHand", (int) IT_EQPM_HAND_L,
		"Shoes", (int) IT_EQPM_SHOES,
		"RightAccessory", (int) IT_EQPM_ACC_R,
		"TopHead", (int) IT_EQPM_HEAD_TOP,
		"MidHead", (int) IT_EQPM_HEAD_MID,
		"CostumeTopHead", (int) IT_EQPM_COSTUME_HEAD_TOP,
		"CostumeMidHead", (int) IT_EQPM_COSTUME_HEAD_MID,
		"CostumeLowerHead", (int) IT_EQPM_COSTUME_HEAD_LOW,
		"CostumeGarment", (int) IT_EQPM_COSTUME_GARMENT,
		"Ammunition", (int) IT_EQPM_AMMO,
		"ShadowArmor", (int) IT_EQPM_SHADOW_ARMOR,
		"ShadowWeapon", (int) IT_EQPM_SHADOW_WEAPON,
		"ShadowShield", (int) IT_EQPM_SHADOW_SHIELD,
		"ShadowShoes", (int) IT_EQPM_SHADOW_SHOES,
		"ShadowRightAccessory", (int) IT_EQPM_SHADOW_ACC_R,
		"ShadowLeftAccessory", (int) IT_EQPM_SHADOW_ACC_L,
		"Weapon", (int) IT_EQPM_WEAPON,
		"Shield", (int) IT_EQPM_SHIELD,
		"BothArms", (int) IT_EQPM_ARMS,
		"AllHeadgear", (int) IT_EQPM_HELM,
		"AllAccessory", (int) IT_EQPM_ACC,
		"AllCostume", (int) IT_EQPM_COSTUME,
		"ShadowAccessory", (int) IT_EQPM_SHADOW_ACC,
		"ShadowArms", (int) IT_EQPM_SHADOW_ARMS
	);

	state->create_named_table("EquipLocationIndex",
		"LeftAccessory", (int) IT_EQPI_ACC_L,
		"RightAccessory", (int) IT_EQPI_ACC_R,
		"Shoes", (int) IT_EQPI_SHOES,
		"Garment", (int) IT_EQPI_GARMENT,
		"LowerHead", (int) IT_EQPI_HEAD_LOW,
		"MidHead", (int) IT_EQPI_HEAD_MID,
		"TopHead", (int) IT_EQPI_HEAD_TOP,
		"Armor", (int) IT_EQPI_ARMOR,
		"LeftHand", (int) IT_EQPI_HAND_L,
		"RightHand", (int) IT_EQPI_HAND_R,
		"CostumeTopHead", (int) IT_EQPI_COSTUME_TOP,
		"CostumeMidHead", (int) IT_EQPI_COSTUME_MID,
		"CostumeLowHead", (int) IT_EQPI_COSTUME_LOW,
		"CostumeGarment", (int) IT_EQPI_COSTUME_GARMENT,
		"Ammunition", (int) IT_EQPI_AMMO,
		"ShadowArmor", (int) IT_EQPI_SHADOW_ARMOR,
		"ShadowWeapon", (int) IT_EQPI_SHADOW_WEAPON,
		"ShadowShield", (int) IT_EQPI_SHADOW_SHIELD,
		"ShadowShoes", (int) IT_EQPI_SHADOW_SHOES,
		"ShadowRightAccessory", (int) IT_EQPI_SHADOW_ACC_R,
		"ShadowLeftAccessory", (int) IT_EQPI_SHADOW_ACC_L,
		"Max", (int) IT_EQPI_MAX
	);

	state->create_named_table("ItemTradeMask",
		"None", (int) ITRMASK_NONE,
		"Drop", (int) ITRMASK_DROP,
		"Trade", (int) ITRMASK_TRADE,
		"TradeWithPartner", (int) ITRMASK_TRADEWPARTNER,
		"SellToNPC", (int) ITRMASK_SELL_TO_NPC,
		"StoreInCart", (int) ITRMASK_CART,
		"StoreInStorage", (int) ITRMASK_STORAGE,
		"StoreInGuildStorage", (int) ITRMASK_GSTORAGE,
		"Mail", (int) ITRMASK_MAIL,
		"Auction", (int) ITRMASK_AUCTION,
		"SellInBuyingStore", (int) ITRMASK_BUYING_STORE,
		"AllowAll", (int) ITRMASK_ALL
	);

	state->create_named_table("ItemUsageMask",
		"Sitting", (int) IURMASK_SITTING,
		"All", (int) IURMASK_ALL
	);

	state->create_named_table("ItemType",
		"Healing", (int) IT_TYPE_HEALING,
		"Unknown", (int) IT_TYPE_UNKNOWN,
		"Usable", (int) IT_TYPE_USABLE,
		"Etc", (int) IT_TYPE_ETC,
		"Weapon", (int) IT_TYPE_WEAPON,
		"Armor", (int) IT_TYPE_ARMOR,
		"Card", (int) IT_TYPE_CARD,
		"PetEgg", (int) IT_TYPE_PET_EGG,
		"PetArmor", (int) IT_TYPE_PET_ARMOR,
		"Unknown2", (int) IT_TYPE_UNKNOWN2,
		"Ammunition", (int) IT_TYPE_AMMO,
		"ConsumptionDelay", (int) IT_TYPE_CONSUMPTION_DELAY,
		"Cash", (int) IT_TYPE_CASH,
		"Max", (int) IT_TYPE_MAX
	);

	state->create_named_table("AmmoType",
		"None", (int) IT_AT_NONE,
		"Arrow", (int) IT_AT_ARROW,
		"ThrowableDagger", (int) IT_AT_DAGGER,
		"Bullet", (int) IT_AT_BULLET,
		"Shell", (int) IT_AT_SHELL,
		"Grenade", (int) IT_AT_GRENADE,
		"Shuriken", (int) IT_AT_SHURIKEN,
		"Kunai", (int) IT_AT_KUNAI,
		"CannonBall", (int) IT_AT_CANNONBALL,
		"ThrowableItem", (int) IT_AT_THROWABLE_ITEM,
		"Max", (int) IT_AT_MAX
	);

	state->create_named_table("ItemBindType",
		"None", (int) IT_BIND_NONE,
		"Account", (int) IT_BIND_ACCOUNT,
		"Guild", (int) IT_BIND_GUILD,
		"Party", (int) IT_BIND_PARTY,
		"Character", (int) IT_BIND_CHARACTER,
		"Max", (int) IT_BIND_MAX
	);
}

void ItemComponent::sync_data_types(std::shared_ptr<sol::state> state)
{

	
	state->new_usertype<item_entry_data::options>("item_options",
		"index", sol::property(&item_entry_data::options::get_index, &item_entry_data::options::set_index),
		"value", sol::property(&item_entry_data::options::get_value, &item_entry_data::options::set_value)
	);

	state->new_usertype<item_entry_data>("item_entry_data",
		"is_equipment", &item_entry_data::is_equipment,
		"is_stackable", &item_entry_data::is_stackable,
		"is_same_as", &item_entry_data::operator ==,
		"storage_type", &item_entry_data::storage_type,
		"storage_index", [] (item_entry_data &item) {
			return std::ref(item.index.storage);
		},
		"inventory_index", [] (item_entry_data &item) {
			return std::ref(item.index.inventory);
		},
		"item_id", sol::readonly(&item_entry_data::item_id),
		"type", sol::readonly(&item_entry_data::type),
		"amount", sol::readonly(&item_entry_data::amount),
		"current_equip_location_mask", sol::readonly(&item_entry_data::current_equip_location_mask),
		"actual_equip_location_mask", sol::readonly(&item_entry_data::actual_equip_location_mask),
		"refine_level", sol::property(&item_entry_data::get_refine_level, &item_entry_data::set_refine_level),
		"slot_item_id", sol::property([] (item_entry_data &item) {
			return std::ref(item.slot_item_id);
		}),
		"hire_expire_date", sol::property(&item_entry_data::get_hire_expire_date, &item_entry_data::set_hire_expire_date),
		"bind_type", sol::property(&item_entry_data::get_bind_type, &item_entry_data::set_bind_type),
		"sprite_id", sol::readonly(&item_entry_data::sprite_id),
		"ele_type", sol::readonly(&item_entry_data::ele_type),
		"option_count", sol::property(&item_entry_data::get_option_count, &item_entry_data::set_option_count),
		"options_data", sol::property([] (item_entry_data &item) {
			return std::ref(item.option_data);
		}),
		"unique_id", sol::readonly(&item_entry_data::unique_id)
	);

	state->new_usertype<item_config_data>("item_config_data",
		"item_id", sol::readonly(&item_config_data::item_id),
		"name", sol::readonly(&item_config_data::name),
		"key_name", sol::readonly(&item_config_data::key_name),
		"value_buy", sol::readonly(&item_config_data::value_buy),
	  	"value_sell", sol::readonly(&item_config_data::value_sell),
		"type", sol::readonly(&item_config_data::type),
		"item_sub_type", sol::readonly_property([] (item_config_data &item) {
			return item.type == IT_TYPE_WEAPON ? item.sub_type.weapon_t : item.sub_type.ammo_t;
		}),
		"equip_location_mask", sol::readonly(&item_config_data::equip_location_mask),
		"weight", sol::readonly(&item_config_data::weight),
		"attack", sol::readonly(&item_config_data::attack),
		"defense", sol::readonly(&item_config_data::defense),
		"attack_range", sol::readonly(&item_config_data::attack_range),
		"card_slot_count", sol::readonly(&item_config_data::card_slot_count),
		"sprite_id", sol::readonly(&item_config_data::sprite_id),
		"level", sol::readonly_property([] (item_config_data &item) {
			return item.type == IT_TYPE_WEAPON ? (uint8_t) item.level.weapon : (uint8_t) item.level.armor;
		}),
		"magic_atk", sol::readonly(&item_config_data::magic_atk),
		"req_min_lv", sol::readonly_property([] (item_config_data &item) {
			return item.requirements.min_lv;
		}),
		"req_max_lv", sol::readonly_property([] (item_config_data &item) {
			return item.requirements.max_lv;
		}),
		"req_job_ids", sol::readonly_property([] (item_config_data &item) {
			return item.requirements.job_ids;
		}),
		"req_gender", sol::readonly_property([] (item_config_data &item) {
			return item.requirements.gender;
		}),
		"default_script", sol::readonly(&item_config_data::default_script),
		"equip_script", sol::readonly(&item_config_data::equip_script),
		"unequip_script", sol::readonly(&item_config_data::unequip_script),
		"available", sol::readonly_property([] (item_config_data &item) {
			return item.config.available ? 1 : 0;
		}),
		"refineable", sol::readonly_property([] (item_config_data &item) {
			return item.config.refineable ? 1 : 0;
		}),
		"trade_restriction_mask", sol::readonly_property([] (item_config_data &item) {
			return (int) item.trade_restriction_mask;
		}),
		"trade_restriction_group_override_id", sol::readonly_property([] (item_config_data &item) {
			return (int) item.trade_restriction_group_override_id;
		}),
		"trade_restriction_partner_override", sol::readonly_property([] (item_config_data &item) {
			return (bool) item.trade_restriction_partner_override;
		}),
		"usage_restriction_mask", sol::readonly_property([] (item_config_data &item) {
			return (int) item.usage_restriction_mask;
		}),
		"usage_restriction_group_override_id", sol::readonly_property([] (item_config_data &item) {
			return (int) item.usage_restriction_group_override_id;
		}),
		"allow_item_options", sol::readonly_property([] (item_config_data &item) {
			return item.config.allow_item_options ? 1 : 0;
		}),
		"bind_on_equip", sol::readonly_property([] (item_config_data &item) {
			return item.config.bind_on_equip ? 1 : 0;
		}),
		"drop_announce", sol::readonly_property([] (item_config_data &item) {
			return item.config.drop_announce ? 1 :0;
		})
	);

	sol::usertype<s_grid_notify_item_drop_entry> item_drop = state->new_usertype<s_grid_notify_item_drop_entry>("s_grid_notify_item_drop_entry");
	item_drop["guid"] = &s_grid_notify_item_drop_entry::guid;
	item_drop["item_id"] = &s_grid_notify_item_drop_entry::item_id;
	item_drop["type"] = &s_grid_notify_item_drop_entry::type;
	item_drop["is_identified"] = &s_grid_notify_item_drop_entry::is_identified;
	item_drop["x"] = &s_grid_notify_item_drop_entry::x;
	item_drop["y"] = &s_grid_notify_item_drop_entry::y;
	item_drop["x_area"] = &s_grid_notify_item_drop_entry::x_area;
	item_drop["y_area"] = &s_grid_notify_item_drop_entry::y_area;
	item_drop["amount"] = &s_grid_notify_item_drop_entry::amount;
	item_drop["show_drop_effect"] = &s_grid_notify_item_drop_entry::show_drop_effect;
	item_drop["drop_effect_mode"] = &s_grid_notify_item_drop_entry::drop_effect_mode;
}

void ItemComponent::sync_functions(std::shared_ptr<sol::state> state)
{
	state->set_function("get_item_info",
					[] (uint32_t item_id) {
						return ItemDB->get_item_by_id(item_id);
					});
}