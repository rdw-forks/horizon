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
 *  (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 **************************************************/

#include "JobDB.hpp"
#include "Server/Zone/Zone.hpp"

using namespace Horizon::Zone;

JobDatabase::JobDatabase()
{
	_name2id_list.emplace("Novice", JOB_NOVICE);
	_name2id_list.emplace("Swordsman", JOB_SWORDMAN);
	_name2id_list.emplace("Magician", JOB_MAGE);
	_name2id_list.emplace("Archer", JOB_ARCHER);
	_name2id_list.emplace("Acolyte", JOB_ACOLYTE);
	_name2id_list.emplace("Merchant", JOB_MERCHANT);
	_name2id_list.emplace("Thief", JOB_THIEF);
	_name2id_list.emplace("Knight", JOB_KNIGHT);
	_name2id_list.emplace("Priest", JOB_PRIEST);
	_name2id_list.emplace("Wizard", JOB_WIZARD);
	_name2id_list.emplace("Blacksmith", JOB_BLACKSMITH);
	_name2id_list.emplace("Hunter", JOB_HUNTER);
	_name2id_list.emplace("Assassin", JOB_ASSASSIN);
	_name2id_list.emplace("Crusader", JOB_CRUSADER);
	_name2id_list.emplace("Monk", JOB_MONK);
	_name2id_list.emplace("Sage", JOB_SAGE);
	_name2id_list.emplace("Rogue", JOB_ROGUE);
	_name2id_list.emplace("Alchemist", JOB_ALCHEMIST);
	_name2id_list.emplace("Bard", JOB_BARD);
	_name2id_list.emplace("Dancer", JOB_DANCER);
	_name2id_list.emplace("SuperNovice", JOB_SUPER_NOVICE);
	_name2id_list.emplace("Gunslinger", JOB_GUNSLINGER);
	_name2id_list.emplace("Ninja", JOB_NINJA);
	_name2id_list.emplace("HighNovice", JOB_NOVICE_HIGH);
	_name2id_list.emplace("HighSwordsman", JOB_SWORDMAN_HIGH);
	_name2id_list.emplace("HighMagician", JOB_MAGE_HIGH);
	_name2id_list.emplace("HighArcher", JOB_ARCHER_HIGH);
	_name2id_list.emplace("HighAcolyte", JOB_ACOLYTE_HIGH);
	_name2id_list.emplace("HighMerchant", JOB_MERCHANT_HIGH);
	_name2id_list.emplace("HighThief", JOB_THIEF_HIGH);
	_name2id_list.emplace("LordKnight", JOB_LORD_KNIGHT);
	_name2id_list.emplace("HighPriest", JOB_HIGH_PRIEST);
	_name2id_list.emplace("HighWizard", JOB_HIGH_WIZARD);
	_name2id_list.emplace("Whitesmith", JOB_WHITESMITH);
	_name2id_list.emplace("Sniper", JOB_SNIPER);
	_name2id_list.emplace("AssassinCross", JOB_ASSASSIN_CROSS);
	_name2id_list.emplace("Paladin", JOB_PALADIN);
	_name2id_list.emplace("Champion", JOB_CHAMPION);
	_name2id_list.emplace("Professor", JOB_PROFESSOR);
	_name2id_list.emplace("Stalker", JOB_STALKER);
	_name2id_list.emplace("Creator", JOB_CREATOR);
	_name2id_list.emplace("Clown", JOB_CLOWN);
	_name2id_list.emplace("Gypsy", JOB_GYPSY);
	_name2id_list.emplace("BabyNovice", JOB_BABY_NOVICE);
	_name2id_list.emplace("BabySwordsman", JOB_BABY_SWORDMAN);
	_name2id_list.emplace("BabyMagician", JOB_BABY_MAGE);
	_name2id_list.emplace("BabyArcher", JOB_BABY_ARCHER);
	_name2id_list.emplace("BabyAcolyte", JOB_BABY_ACOLYTE);
	_name2id_list.emplace("BabyMerchant", JOB_BABY_MERCHANT);
	_name2id_list.emplace("BabyThief", JOB_BABY_THIEF);
	_name2id_list.emplace("BabyKnight", JOB_BABY_KNIGHT);
	_name2id_list.emplace("BabyPriest", JOB_BABY_PRIEST);
	_name2id_list.emplace("BabyWizard", JOB_BABY_WIZARD);
	_name2id_list.emplace("BabyBlacksmith", JOB_BABY_BLACKSMITH);
	_name2id_list.emplace("BabyHunter", JOB_BABY_HUNTER);
	_name2id_list.emplace("BabyAssassin", JOB_BABY_ASSASSIN);
	_name2id_list.emplace("BabyCrusader", JOB_BABY_CRUSADER);
	_name2id_list.emplace("BabyMonk", JOB_BABY_MONK);
	_name2id_list.emplace("BabySage", JOB_BABY_SAGE);
	_name2id_list.emplace("BabyRogue", JOB_BABY_ROGUE);
	_name2id_list.emplace("BabyAlchemist", JOB_BABY_ALCHEMIST);
	_name2id_list.emplace("BabyBard", JOB_BABY_BARD);
	_name2id_list.emplace("BabyDancer", JOB_BABY_DANCER);
	_name2id_list.emplace("SuperBaby", JOB_SUPER_BABY);
	_name2id_list.emplace("Taekwon", JOB_TAEKWON);
	_name2id_list.emplace("StarGladiator", JOB_STAR_GLADIATOR);
	_name2id_list.emplace("SoulLinker", JOB_SOUL_LINKER);
	_name2id_list.emplace("Gangsi", JOB_GANGSI);
	_name2id_list.emplace("DeathKnight", JOB_DEATH_KNIGHT);
	_name2id_list.emplace("DarkCollector", JOB_DARK_COLLECTOR);
	_name2id_list.emplace("RuneKnight", JOB_RUNE_KNIGHT);
	_name2id_list.emplace("Warlock", JOB_WARLOCK);
	_name2id_list.emplace("Ranger", JOB_RANGER);
	_name2id_list.emplace("ArchBishop", JOB_ARCH_BISHOP);
	_name2id_list.emplace("Mechanic", JOB_MECHANIC);
	_name2id_list.emplace("GuillotineCross", JOB_GUILLOTINE_CROSS);
	_name2id_list.emplace("RuneKnightTrans", JOB_RUNE_KNIGHT_T);
	_name2id_list.emplace("WarlockTrans", JOB_WARLOCK_T);
	_name2id_list.emplace("RangerTrans", JOB_RANGER_T);
	_name2id_list.emplace("ArchBishopTrans", JOB_ARCH_BISHOP_T);
	_name2id_list.emplace("MechanicTrans", JOB_MECHANIC_T);
	_name2id_list.emplace("GuillotineCrossTrans", JOB_GUILLOTINE_CROSS_T);
	_name2id_list.emplace("RoyalGuard", JOB_ROYAL_GUARD);
	_name2id_list.emplace("Sorcerer", JOB_SORCERER);
	_name2id_list.emplace("Minstrel", JOB_MINSTREL);
	_name2id_list.emplace("Wanderer", JOB_WANDERER);
	_name2id_list.emplace("Sura", JOB_SURA);
	_name2id_list.emplace("Genetic", JOB_GENETIC);
	_name2id_list.emplace("ShadowChaser", JOB_SHADOW_CHASER);
	_name2id_list.emplace("RoyalGuardTrans", JOB_ROYAL_GUARD_T);
	_name2id_list.emplace("SorcererTrans", JOB_SORCERER_T);
	_name2id_list.emplace("MinstrelTrans", JOB_MINSTREL_T);
	_name2id_list.emplace("WandererTrans", JOB_WANDERER_T);
	_name2id_list.emplace("SuraTrans", JOB_SURA_T);
	_name2id_list.emplace("GeneticTrans", JOB_GENETIC_T);
	_name2id_list.emplace("ShadowChaserTrans", JOB_SHADOW_CHASER_T);
	_name2id_list.emplace("BabyRuneKnight", JOB_BABY_RUNE_KNIGHT);
	_name2id_list.emplace("BabyWarlock", JOB_BABY_WARLOCK);
	_name2id_list.emplace("BabyRanger", JOB_BABY_RANGER);
	_name2id_list.emplace("BabyArchBishop", JOB_BABY_ARCH_BISHOP);
	_name2id_list.emplace("BabyMechanic", JOB_BABY_MECHANIC);
	_name2id_list.emplace("BabyGuillotineCross", JOB_BABY_GUILLOTINE_CROSS);
	_name2id_list.emplace("BabyRoyalGuard", JOB_BABY_ROYAL_GUARD);
	_name2id_list.emplace("BabySorcerer", JOB_BABY_SORCERER);
	_name2id_list.emplace("BabyMinstrel", JOB_BABY_MINSTREL);
	_name2id_list.emplace("BabyWanderer", JOB_BABY_WANDERER);
	_name2id_list.emplace("BabySura", JOB_BABY_SURA);
	_name2id_list.emplace("BabyGenetic", JOB_BABY_GENETIC);
	_name2id_list.emplace("BabyShadowChaser", JOB_BABY_SHADOW_CHASER);
	_name2id_list.emplace("ExpandedSuperNovice", JOB_SUPER_NOVICE_E);
	_name2id_list.emplace("ExpandedSuperBaby", JOB_SUPER_BABY_E);
	_name2id_list.emplace("Kagerou", JOB_KAGEROU);
	_name2id_list.emplace("Oboro", JOB_OBORO);
	_name2id_list.emplace("Rebellion", JOB_REBELLION);
	_name2id_list.emplace("Summoner", JOB_SUMMONER);
}

job_class_type JobDatabase::get_job_class_by_name(std::string name) const
{
	auto id = _name2id_list.find(name);

	if (id == _name2id_list.end())
		return JOB_INVALID;

	return job_class_type(id->second);
}

bool JobDatabase::load()
{
	sol::state lua;

	int total_entries = 0;
	std::string tmp_string;
	std::string file_path = sZone->config().get_static_db_path().string() + "job_db.lua";

	// Read the file. If there is an error, report it and exit.
	try {
		lua.script_file(file_path);
		sol::table job_tbl = lua.get<sol::table>("job_db");
		total_entries = load_job(job_tbl);
		HLog(info) << "Loaded " << total_entries << " entries from '" << file_path << "'";
	} catch(const std::exception &e) {
		HLog(error) << "JobDB::load: " << e.what();
		return false;
	}

	return true;
}

int JobDatabase::load_job(sol::table &job_tbls, std::string name)
{
	int count = 0;

	if (name.empty()) {
		job_tbls.for_each([this, &count](sol::object const &/*key*/, sol::object const &value) {
			job_config_data data;
			sol::table job_tbl = value.as<sol::table>();
			std::string name = job_tbl.get_or("Name", std::string(""));
			job_class_type jc = get_job_class_by_name(name);
			data.id = (int) jc;
			data.name = name;
			if (load_job_internal(job_tbl, data, name) == true) {
				_job_db.insert(jc, std::make_shared<job_config_data>(data));
				count++;
			}
		});
	} else {
		sol::optional<sol::table> maybe_job = job_tbls.get<sol::optional<sol::table>>(name);
		if (maybe_job) {
			job_config_data data;
			job_class_type jc = get_job_class_by_name(name);
			data.id = (int) jc;
			data.name = name;
			if (load_job_internal(maybe_job.value(), data, name) == true)
				_job_db.insert(jc, std::make_shared<job_config_data>(data));
		} else {
			HLog(warning) << "JobDB::load_job: Job named '" << name << "' was not found.";
		}
	}

	return count;
}

bool JobDatabase::load_job_internal(sol::table &job_tbl, job_config_data &data, std::string job_name)
{
	std::string t_str;

	t_str = job_tbl.get_or("BaseExpGroup", std::string(""));
	if (t_str.empty()) {
		HLog(warning) << "JobDB::load_job_internal: Invalid or non-existant BaseExpGroup for job '" << job_name << "', skipping...";
		return false;
	}
	data.base_exp_group = t_str;

	t_str = job_tbl.get_or("JobExpGroup", std::string(""));
	if (t_str.empty()) {
		HLog(warning) << "JobDB::load_job_internal: Invalid or non-existant JobExpGroup for job '" << job_name << "', skipping...";
		return false;
	}
	data.job_exp_group = t_str;

	t_str = job_tbl.get_or("Inherit", std::string(""));
	if (t_str.empty()) {
		// Max Weight
		data.max_weight = job_tbl.get_or("Weight", 20000);

		sol::optional<sol::table> aspd_tbl = job_tbl.get<sol::optional<sol::table>>("BaseASPD");
		if (aspd_tbl) {
			aspd_tbl.value().for_each([&data, &job_name] (sol::object const &key, sol::object const &value) {
				std::string w_name = key.as<std::string>();

				if (value.get_type() != sol::type::number) {
					HLog(warning) << "JobDB::load_job_internal: Invalid entry in BaseASPD setting weapon " << w_name << " for job '" << job_name << "'.";
					return;
				}

				int val = value.as<int>();
				if (!w_name.compare("Fist")) {
					data.weapon_base_aspd[IT_WT_FIST] = val;
				} else if (!w_name.compare("Dagger")) {
					data.weapon_base_aspd[IT_WT_DAGGER] = val;
				} else if (!w_name.compare("Sword")) {
					data.weapon_base_aspd[IT_WT_1HSWORD] = val;
				} else if (!w_name.compare("TwoHandSword")) {
					data.weapon_base_aspd[IT_WT_2HSWORD] = val;
				} else if (!w_name.compare("Spear")) {
					data.weapon_base_aspd[IT_WT_1HSPEAR] = val;
				} else if (!w_name.compare("TwoHandSpear")) {
					data.weapon_base_aspd[IT_WT_2HSPEAR] = val;
				} else if (!w_name.compare("Axe")) {
					data.weapon_base_aspd[IT_WT_1HAXE] = val;
				} else if (!w_name.compare("TwoHandAxe")) {
					data.weapon_base_aspd[IT_WT_2HAXE] = val;
				} else if (!w_name.compare("Mace")) {
					data.weapon_base_aspd[IT_WT_1HMACE] = val;
				} else if (!w_name.compare("TwoHandMace")) {
					data.weapon_base_aspd[IT_WT_2HMACE] = val;
				} else if (!w_name.compare("Rod")) {
					data.weapon_base_aspd[IT_WT_STAFF] = val;
				} else if (!w_name.compare("Bow")) {
					data.weapon_base_aspd[IT_WT_BOW] = val;
				} else if (!w_name.compare("Knuckle")) {
					data.weapon_base_aspd[IT_WT_KNUCKLE] = val;
				} else if (!w_name.compare("Instrument")) {
					data.weapon_base_aspd[IT_WT_MUSICAL] = val;
				} else if (!w_name.compare("Whip")) {
					data.weapon_base_aspd[IT_WT_WHIP] = val;
				} else if (!w_name.compare("Book")) {
					data.weapon_base_aspd[IT_WT_BOOK] = val;
				} else if (!w_name.compare("Katar")) {
					data.weapon_base_aspd[IT_WT_KATAR] = val;
				} else if (!w_name.compare("Revolver")) {
					data.weapon_base_aspd[IT_WT_REVOLVER] = val;
				} else if (!w_name.compare("Rifle")) {
					data.weapon_base_aspd[IT_WT_RIFLE] = val;
				} else if (!w_name.compare("GatlingGun")) {
					data.weapon_base_aspd[IT_WT_GATLING] = val;
				} else if (!w_name.compare("Shotgun")) {
					data.weapon_base_aspd[IT_WT_SHOTGUN] = val;
				} else if (!w_name.compare("GrenadeLauncher")) {
					data.weapon_base_aspd[IT_WT_GRENADE] = val;
				} else if (!w_name.compare("FuumaShuriken")) {
					data.weapon_base_aspd[IT_WT_HUUMA] = val;
				} else if (!w_name.compare("TwoHandRod")) {
					data.weapon_base_aspd[IT_WT_2HSTAFF] = val;
				}
			});

		}
	} else {
		job_class_type jc = get_job_class_by_name(t_str);

		if (jc == JOB_INVALID) {
			HLog(warning) << "JobDB::load_job_internal:1: Unable to inherit from non-existent job '" << t_str << "' for '" << job_name << "', make sure the job is read before being inherited. Skipping...";
			return false;
		}

		auto jobi = _job_db.at(jc);
		if (!jobi) {
			HLog(warning) << "JobDB::load_job_internal:2: Unable to inherit from non-existent job '" << t_str << "' for '" << job_name << "', make sure the job is read before being inherited. Skipping...";
			return false;
		}

		data.weapon_base_aspd = jobi->weapon_base_aspd;
		data.max_weight = jobi->max_weight;
	}

	if (load_hp_sp_table(job_tbl, data, job_name, "HPTable") == false)
		return false;

	if (load_hp_sp_table(job_tbl, data, job_name, "SPTable") == false)
		return false;

	return true;
}

bool JobDatabase::load_hp_sp_table(sol::table &job_tbl, job_config_data &data, std::string &job_name, std::string table_name)
{
	std::string t_str;

	t_str = job_tbl.get_or("Inherit", t_str);
	t_str = job_tbl.get_or("InheritHP", t_str);
	t_str = job_tbl.get_or("InheritSP", t_str);

	if (!t_str.empty()) {
		job_class_type jc = get_job_class_by_name(t_str);
		if (jc == JOB_INVALID) {
			HLog(warning) <<"JobDB::load_hp_sp_table:1: Unable to inherit from non-existent job '" << t_str << "' for '" << job_name << "', make sure the job is read before being inherited. Skipping...";
			return false;
		}
		auto jobi = _job_db.at(jc);
		if (!jobi) {
			HLog(warning) <<"JobDB::load_hp_sp_table:2: Unable to inherit " << table_name << " from non-existent job '" << t_str << "' for '" << job_name << "', make sure the job is read before being inherited. Skipping...";
			return false;
		}
		std::shared_ptr<const job_config_data> inherited_data = jobi;

		data.hp_table = inherited_data->hp_table;
		data.sp_table = inherited_data->sp_table;
		return true;
	}

	sol::optional<sol::table> tbl = job_tbl.get<sol::optional<sol::table>>(table_name);

	if (!tbl) {
		HLog(warning) << "JobDB::load_hp_sp_table: Job '" << job_name << "' does not have a " << table_name << ", skipping...";
		return false;
	}

	tbl.value().for_each([&data, &job_name, &table_name](sol::object const &key, sol::object const &val) {
		if (key.get_type() != sol::type::number) {
			HLog(warning) << "JobDB::load_hp_sp_table: Invalid index " << key.as<int>() << " for entry " << job_name << " in job '" << table_name << "', skipping...";
			return;
		}

		if (!table_name.compare("HPTable"))
			data.hp_table.push_back(val.as<int>());
		else if (!table_name.compare("SPTable"))
			data.sp_table.push_back(val.as<int>());
	});

	return true;
}

job_class_mask JobDatabase::job_id_to_mask(job_class_type job_id) const
{
	switch (job_id)
	{
	//Novice And 1-1 Jobs
	case JOB_NOVICE:                return JMASK_NOVICE;
	case JOB_SWORDMAN:              return JMASK_SWORDMAN;
	case JOB_MAGE:                  return JMASK_MAGE;
	case JOB_ARCHER:                return JMASK_ARCHER;
	case JOB_ACOLYTE:               return JMASK_ACOLYTE;
	case JOB_MERCHANT:              return JMASK_MERCHANT;
	case JOB_THIEF:                 return JMASK_THIEF;
	case JOB_WEDDING:               return JMASK_WEDDING;
	case JOB_GANGSI:                return JMASK_GANGSI;
	case JOB_SUMMONER:              return JMASK_SUMMONER;
	//2-1 Jobs
	case JOB_KNIGHT:                return JMASK_KNIGHT;
	case JOB_WIZARD:                return JMASK_WIZARD;
	case JOB_HUNTER:                return JMASK_HUNTER;
	case JOB_PRIEST:                return JMASK_PRIEST;
	case JOB_BLACKSMITH:            return JMASK_BLACKSMITH;
	case JOB_ASSASSIN:              return JMASK_ASSASSIN;
	case JOB_DEATH_KNIGHT:          return JMASK_DEATH_KNIGHT;
	//2-2 Jobs
	case JOB_CRUSADER:              return JMASK_CRUSADER;
	case JOB_SAGE:                  return JMASK_SAGE;
	case JOB_BARD:
	case JOB_DANCER:                return JMASK_BARDDANCER;
	case JOB_MONK:                  return JMASK_MONK;
	case JOB_ALCHEMIST:             return JMASK_ALCHEMIST;
	case JOB_ROGUE:                 return JMASK_ROGUE;
	case JOB_DARK_COLLECTOR:        return JMASK_DARK_COLLECTOR;
	//Trans Novice And Trans 1-1 Jobs
	case JOB_NOVICE_HIGH:           return JMASK_NOVICE_HIGH;
	case JOB_SWORDMAN_HIGH:         return JMASK_SWORDMAN_HIGH;
	case JOB_MAGE_HIGH:             return JMASK_MAGE_HIGH;
	case JOB_ARCHER_HIGH:           return JMASK_ARCHER_HIGH;
	case JOB_ACOLYTE_HIGH:          return JMASK_ACOLYTE_HIGH;
	case JOB_MERCHANT_HIGH:         return JMASK_MERCHANT_HIGH;
	case JOB_THIEF_HIGH:            return JMASK_THIEF_HIGH;
	//Trans 2-1 Jobs
	case JOB_LORD_KNIGHT:           return JMASK_LORD_KNIGHT;
	case JOB_HIGH_WIZARD:           return JMASK_HIGH_WIZARD;
	case JOB_SNIPER:                return JMASK_SNIPER;
	case JOB_HIGH_PRIEST:           return JMASK_HIGH_PRIEST;
	case JOB_WHITESMITH:            return JMASK_WHITESMITH;
	case JOB_ASSASSIN_CROSS:        return JMASK_ASSASSIN_CROSS;
	//Trans 2-2 Jobs
	case JOB_PALADIN:               return JMASK_PALADIN;
	case JOB_PROFESSOR:             return JMASK_PROFESSOR;
	case JOB_CLOWN:
	case JOB_GYPSY:                 return JMASK_CLOWNGYPSY;
	case JOB_CHAMPION:              return JMASK_CHAMPION;
	case JOB_CREATOR:               return JMASK_CREATOR;
	case JOB_STALKER:               return JMASK_STALKER;
	//Baby Novice And Baby 1-1 Jobs
	case JOB_BABY_NOVICE:           return JMASK_BABY_NOVICE;
	case JOB_BABY_SWORDMAN:         return JMASK_BABY_SWORDMAN;
	case JOB_BABY_MAGE:             return JMASK_BABY_MAGE;
	case JOB_BABY_ARCHER:           return JMASK_BABY_ARCHER;
	case JOB_BABY_ACOLYTE:          return JMASK_BABY_ACOLYTE;
	case JOB_BABY_MERCHANT:         return JMASK_BABY_MERCHANT;
	case JOB_BABY_THIEF:            return JMASK_BABY_THIEF;
	//Baby 2-1 Jobs
	case JOB_SUPER_BABY:            return JMASK_SUPER_BABY;
	case JOB_BABY_KNIGHT:           return JMASK_BABY_KNIGHT;
	case JOB_BABY_WIZARD:           return JMASK_BABY_WIZARD;
	case JOB_BABY_HUNTER:           return JMASK_BABY_HUNTER;
	case JOB_BABY_PRIEST:           return JMASK_BABY_PRIEST;
	case JOB_BABY_BLACKSMITH:       return JMASK_BABY_BLACKSMITH;
	case JOB_BABY_ASSASSIN:         return JMASK_BABY_ASSASSIN;
	//Baby 2-2 Jobs
	case JOB_BABY_CRUSADER:         return JMASK_BABY_CRUSADER;
	case JOB_BABY_SAGE:             return JMASK_BABY_SAGE;
	case JOB_BABY_BARD:
	case JOB_BABY_DANCER:           return JMASK_BABY_BARDDANCER;
	case JOB_BABY_MONK:             return JMASK_BABY_MONK;
	case JOB_BABY_ALCHEMIST:        return JMASK_BABY_ALCHEMIST;
	case JOB_BABY_ROGUE:            return JMASK_BABY_ROGUE;
	//3-1 Jobs
	case JOB_RUNE_KNIGHT:           return JMASK_RUNE_KNIGHT;
	case JOB_WARLOCK:               return JMASK_WARLOCK;
	case JOB_RANGER:                return JMASK_RANGER;
	case JOB_ARCH_BISHOP:           return JMASK_ARCH_BISHOP;
	case JOB_MECHANIC:              return JMASK_MECHANIC;
	case JOB_GUILLOTINE_CROSS:      return JMASK_GUILLOTINE_CROSS;
	//3-2 Jobs
	case JOB_ROYAL_GUARD:           return JMASK_ROYAL_GUARD;
	case JOB_SORCERER:              return JMASK_SORCERER;
	case JOB_MINSTREL:
	case JOB_WANDERER:              return JMASK_MINSTRELWANDERER;
	case JOB_SURA:                  return JMASK_SURA;
	case JOB_GENETIC:               return JMASK_GENETIC;
	case JOB_SHADOW_CHASER:         return JMASK_SHADOW_CHASER;
	//Trans 3-1 Jobs
	case JOB_RUNE_KNIGHT_T:         return JMASK_RUNE_KNIGHT_T;
	case JOB_WARLOCK_T:             return JMASK_WARLOCK_T;
	case JOB_RANGER_T:              return JMASK_RANGER_T;
	case JOB_ARCH_BISHOP_T:         return JMASK_ARCH_BISHOP_T;
	case JOB_MECHANIC_T:            return JMASK_MECHANIC_T;
	case JOB_GUILLOTINE_CROSS_T:    return JMASK_GUILLOTINE_CROSS_T;
	//Trans 3-2 Jobs
	case JOB_ROYAL_GUARD_T:         return JMASK_ROYAL_GUARD_T;
	case JOB_SORCERER_T:            return JMASK_SORCERER_T;
	case JOB_MINSTREL_T:
	case JOB_WANDERER_T:            return JMASK_MINSTRELWANDERER_T;
	case JOB_SURA_T:                return JMASK_SURA_T;
	case JOB_GENETIC_T:             return JMASK_GENETIC_T;
	case JOB_SHADOW_CHASER_T:       return JMASK_SHADOW_CHASER_T;
	//Baby 3-1 Jobs
	case JOB_BABY_RUNE_KNIGHT:      return JMASK_BABY_RUNE_KNIGHT;
	case JOB_BABY_WARLOCK:          return JMASK_BABY_WARLOCK;
	case JOB_BABY_RANGER:           return JMASK_BABY_RANGER;
	case JOB_BABY_ARCH_BISHOP:           return JMASK_BABY_ARCH_BISHOP;
	case JOB_BABY_MECHANIC:         return JMASK_BABY_MECHANIC;
	case JOB_BABY_GUILLOTINE_CROSS: return JMASK_BABY_GUILLOTINE_CROSS;
	//Baby 3-2 Jobs
	case JOB_BABY_ROYAL_GUARD:            return JMASK_BABY_ROYAL_GUARD;
	case JOB_BABY_SORCERER:         return JMASK_BABY_SORCERER;
	case JOB_BABY_MINSTREL:
	case JOB_BABY_WANDERER:         return JMASK_BABY_MINSTRELWANDERER;
	case JOB_BABY_SURA:             return JMASK_BABY_SURA;
	case JOB_BABY_GENETIC:          return JMASK_BABY_GENETIC;
	case JOB_BABY_SHADOW_CHASER:           return JMASK_BABY_SHADOW_CHASER;
	// Expanded Jobs
	case JOB_SUPER_NOVICE_E:        return JMASK_SUPER_NOVICE_E;
	case JOB_SUPER_NOVICE:          return JMASK_SUPER_NOVICE;
	case JOB_SUPER_BABY_E:          return JMASK_SUPER_BABY_E;
	case JOB_TAEKWON:               return JMASK_TAEKWON;
	case JOB_SOUL_LINKER:           return JMASK_SOUL_LINKER;
	case JOB_STAR_GLADIATOR:        return JMASK_STAR_GLADIATOR;
	case JOB_GUNSLINGER:            return JMASK_GUNSLINGER;
	case JOB_REBELLION:             return JMASK_REBELLION;
	case JOB_NINJA:                 return JMASK_NINJA;
	case JOB_KAGEROU:
	case JOB_OBORO:                 return JMASK_KAGEROUOBORO;
	default:                        return JMASK_INVALID;
	}
}
