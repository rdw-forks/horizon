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

#include "MonsterDB.hpp"

#include "Server/Zone/Script/LuaDefinitionSync.hpp"
#include "Server/Zone/Zone.hpp"

using namespace Horizon::Zone;

MonsterDatabase::MonsterDatabase()
{
	//
}

MonsterDatabase::~MonsterDatabase()
{
	//
}

bool MonsterDatabase::load()
{
	sol::state lua;
	int total_entries = 0;

	lua.open_libraries(sol::lib::base);
	lua.open_libraries(sol::lib::package);

	sync_monster_definitions(lua);
	sync_item_definitions(lua);
	sync_entity_definitions(lua);

	std::string tmp_string;
	std::string file_path = sZone->config().get_static_db_path().string() + "mob_db.lua";


	// Read the file. If there is an error, report it and exit.
	try {
		lua.script_file(file_path);
		sol::table mob_tbl = lua.get<sol::table>("mob_db");
		mob_tbl.for_each([this, &total_entries] (sol::object const &key, sol::object const &value) {
			total_entries += load_internal(key, value);
		});
		HLog(info) << "Loaded " << total_entries << " entries from '" << file_path << "'.";
	} catch(const std::exception &e) {
		HLog(error) << "Monster::load: " << e.what();
		return false;
	}

	return true;
}

bool MonsterDatabase::load_internal(const sol::object &key, const sol::object &value)
{
	monster_config_data data;

// 	-- ================ Mandatory fields ==============================
	std::string sprite_name = key.as<std::string>();
	std::strncpy(data.sprite_name, sprite_name.c_str(), MAX_UNIT_NAME_LENGTH);

	if (value.get_type() != sol::type::table) {
		HLog(error) << "Value for '" << data.sprite_name << "' is not a table... skipping.";
		return false;
	}

	sol::table m_tbl = value.as<sol::table>();
	
	data.monster_id = m_tbl.get_or<uint16_t>("Id", 0);

	if (data.monster_id <= 0 || data.monster_id > MAX_MOB_DB) {
		HLog(warning) << "Monster ID for '" << data.name << "' is out of range... skipping.";
		return false;
	}

	std::string name = m_tbl.get_or<std::string>("Name", "");
	std::strncpy(data.name, name.c_str(), MAX_UNIT_NAME_LENGTH);

	if (name.size() == 0) {
		HLog(warning) << "Monster Name for '" << data.monster_id << "' is a mandatory field... skipping.";
		return false;
	}

// 	-- ================ Optional fields ==============================
	std::string alt_name = m_tbl.get_or<std::string>("JName", "");
	std::strncpy(data.alt_name, alt_name.c_str(), MAX_UNIT_NAME_LENGTH);

	try {
		sol::optional<int> maybe_val = m_tbl.get<sol::optional<int>>("Lv");
		if (maybe_val) {
			data.level = maybe_val.value();
		}
	} catch (sol::error &error) {
		HLog(error) << "Error parsing Lv for monster '" << data.name << "' - " << error.what() << ".";
	}

	
	return true;
}

// {
// 	-- ================ Mandatory fields ==============================
// 	Id = ID                                (int),
// 	SpriteName = "SPRITE_NAME"             (string),
// 	Name = "Mob name"                      (string),
// 	-- ================ Optional fields ===============================
// 	JName = "Mob name"                     (string),
// 	Lv = level                             (int, defaults to 1),
// 	Hp = health                            (int, defaults to 1),
// 	Sp = mana                              (int, defaults to 0),
// 	Exp = basic experience                 (int, defaults to 0),
// 	JExp = job experience                  (int, defaults to 0),
// 	AttackRange = attack range             (int, defaults to 1),
// 	Attack = [attack1, attack2]            (int, defaults to 0),
// 	Def = defence                          (int, defaults to 0),
// 	Mdef = magic defence                   (int, defaults to 0),
// 	Stats = {
// 		Str = strength                 (int, defaults to 0),
// 		Agi = agility                  (int, defaults to 0),
// 		Vit = vitality                 (int, defaults to 0),
// 		Int = intelligence             (int, defaults to 0),
// 		Dex = dexterity                (int, defaults to 0),
// 		Luk = luck                     (int, defaults to 0),
// 	},
// 	ViewRange = view range                 (int, defaults to 1),
// 	ChaseRange = chase range               (int, defaults to 1),
// 	Size = size                            (string, defaults to "Size_Small"),
// 	Race = race                            (string, defaults to "RC_Formless"),
// 	Element = (type, level)                (string/int, defaults to "Ele_Neutral"/1),
// 	Mode = {
// 		MonsterMode.CanMove                (bool, defaults to false),
// 		MonsterMode.Looter                 (bool, defaults to false),
// 		MonsterMode.Aggressive             (bool, defaults to false),
// 		MonsterMode.Assist                 (bool, defaults to false),
// 		MonsterMode.CastSensorIdle         (bool, defaults to false),
// 		MonsterMode.Boss                   (bool, defaults to false),
// 		MonsterMode.Plant                  (bool, defaults to false),
// 		MonsterMode.CanAttack              (bool, defaults to false),
// 		MonsterMode.Detector               (bool, defaults to false),
// 		MonsterMode.CastSensorChase        (bool, defaults to false),
// 		MonsterMode.ChangeChase            (bool, defaults to false),
// 		MonsterMode.Angry                  (bool, defaults to false),
// 		MonsterMode.ChangeTargetMelee      (bool, defaults to false),
// 		MonsterMode.ChangeTargetChase      (bool, defaults to false),
// 		MonsterMode.TargetWeak             (bool, defaults to false),
// 		MonsterMode.NoKnockback            (bool, defaults to false),
// 	},
// 	MoveSpeed = move speed                 (int, defaults to 0),
// 	AttackDelay = attack delay             (int, defaults to 4000),
// 	AttackMotion = attack motion           (int, defaults to 2000),
// 	DamageMotion = damage motion           (int, defaults to 0),
// 	MvpExp = mvp experience                (int, defaults to 0),
// 	MvpDrops = {
// 		AegisName = chance             (string = int),
// 		-- ...
// 	},
// 	Drops = {
// 		AegisName = chance         (string = int),
// 		-- or,
// 		AegisName = (chance, "Option Drop Group"),
// 		-- ...
// 	},
// 	DamageTakenRate = damage taken rate    (int, defaults to 100),
// 	ViewData = {
// 		SpriteId = sprite id              (int, defaults to Id),
// 		WeaponId = weapon id              (int, defaults to 0),
// 		ShieldId = shield id              (int, defaults to 0),
// 		RobeId = garment id               (int, defaults to 0),
// 		HeadTopId = top headgear id       (int, defaults to 0),
// 		HeadMidId = middle headgear id    (int, defaults to 0),
// 		HeadLowId = lower headgear id     (int, defaults to 0),
// 		HairStyleId = hair style id       (int, defaults to 1),
// 		BodyStyleId = clothes id          (int, defaults to 0),
// 		HairColorId = hair color id       (int, defaults to 0),
// 		BodyColorId = clothes color id    (int, defaults to 0),
// 		Gender = gender                   (string, defaults to "SEX_FEMALE"),
// 		Options = options                 (int, defaults to 0),
// 	},
// },
