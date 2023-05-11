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
 * Base Author - Sagun Khosla <sagunxp@gmail.com>
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

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "MySQLTest"

#include <mysqlx/xdevapi.h>
#include <boost/test/unit_test.hpp>
#include <cstring>
#include <iostream>


BOOST_AUTO_TEST_CASE(MySQLTest)
{
    std::string host = "localhost";
    int port = 33060;
    std::string user = "horizon";
    std::string pass = "horizon";
    std::string schema = "horizon";

    try {
        mysqlx::Session session(mysqlx::SessionOption::HOST, host,
            mysqlx::SessionOption::PORT, port,
            mysqlx::SessionOption::USER, user,
            mysqlx::SessionOption::PWD, "wrong-password");
    }
    catch (mysqlx::Error& err) {
        std::string e = err.what();
        BOOST_CHECK_EQUAL(e.compare("CDK Error: Access denied for user 'horizon'@'localhost' (using password: YES)"), 0);
    }

    // Connect to MySQL Server on a network machine
    mysqlx::Session session(mysqlx::SessionOption::HOST, host,
        mysqlx::SessionOption::PORT, port,
        mysqlx::SessionOption::USER, user,
        mysqlx::SessionOption::PWD, pass);

    session.sql("CREATE DATABASE IF NOT EXISTS `horizon`").execute();

    try {
        session.sql("CREATE TABLE IF NOT EXISTS `horizon`.`test` ( \
            `idtest` INT NOT NULL, \
            `testint` INT NOT NULL, \
            `teststring` VARCHAR(45) NOT NULL, \
            `testbool` TINYINT NOT NULL, \
            `testdate` DATE NOT NULL, \
            `testdatetime` DATETIME NOT NULL, \
            PRIMARY KEY(`idtest`)); \
        ").execute();

        std::cout << "Created Table `horizon`.`test`..." << std::endl;

        session.sql("INSERT INTO `horizon`.`test` (`idtest`, `testint`, `teststring`, `testbool`, `testdate`, `testdatetime`) VALUES (?, ?, ?, ?, ?, ?);")
            .bind(1, 100, "test string", true, "1990-10-01", "1990-11-01 01:01:01")
            .execute();

        std::cout << "Inserted 1 column into `horizon`.`test`..." << std::endl;
    }
    catch (mysqlx::Error& error) {
        std::cout << "error:" << error.what() << std::endl;
    }

    try {
        std::cout << "Fetching 1 column from `horizon`.`test`..." << std::endl;
        mysqlx::RowResult res = session.sql("SELECT `idtest`, `testint`, `teststring`, `testbool`, date_format(`testdate`, '%Y-%m-%d'), date_format(`testdatetime`, '%Y-%m-%d %H:%i:%s') FROM `horizon`.`test` WHERE `idtest` = ?")
            .bind(1)
            .execute();

        mysqlx::Row row = res.fetchOne();

        BOOST_CHECK_EQUAL(row[0].get<int>(), 1);
        BOOST_CHECK_EQUAL(row[1].get<int>(), 100);
        BOOST_CHECK_EQUAL(row[2].get<std::string>().compare("test string"), 0);
        BOOST_CHECK_EQUAL(row[3].get<bool>(), true);
        BOOST_CHECK_EQUAL(row[4].get<std::string>().compare("1990-10-01"), 0);//654719400);
        BOOST_CHECK_EQUAL(row[5].get<std::string>().compare("1990-11-01 01:01:01"), 0); // 657401461);

        std::cout << "Dropping table `horizon`.`test`..." << std::endl;
        session.sql("DROP TABLE IF EXISTS `horizon`.`test`;").execute();
        session.sql("DROP TABLE IF EXISTS `horizon`.`character_inventory`;").execute();
        session.sql("DROP TABLE IF EXISTS `horizon`.`character_status`;").execute();
        session.sql("DROP TABLE IF EXISTS `horizon`.`characters`;").execute();
        session.sql("DROP TABLE IF EXISTS `horizon`.`game_accounts`;").execute();

        session.sql("CREATE TABLE IF NOT EXISTS `horizon`.`game_accounts` ("
            "`id` int(11) unsigned NOT NULL AUTO_INCREMENT,"
            "`username` varchar(23) NOT NULL DEFAULT '',"
            "`hash` varchar(128) NOT NULL DEFAULT '',"
            "`salt` varchar(16) NOT NULL DEFAULT '',"
            "`gender` enum('M', 'F', 'NA') NOT NULL DEFAULT 'M',"
            "`email` varchar(39) NOT NULL DEFAULT '',"
            "`group_id` tinyint(3) NOT NULL DEFAULT 0,"
            "`state` int(11) unsigned NOT NULL DEFAULT 0,"
            "`unban_time` int(11) unsigned NOT NULL DEFAULT 0,"
            "`expiration_time` int(11) unsigned NOT NULL DEFAULT 0,"
            "`login_count` mediumint(9) unsigned NOT NULL DEFAULT 0,"
            "`last_login` datetime DEFAULT NULL,"
            "`last_ip` varchar(100) NOT NULL DEFAULT '',"
            "`birth_date` varchar(10) DEFAULT NULL,"
            "`character_slots` tinyint(3) unsigned NOT NULL DEFAULT 0,"
            "`pincode` varchar(4) NOT NULL DEFAULT '',"
            "`pincode_expiry` int(11) unsigned NOT NULL DEFAULT 0,"
            "PRIMARY KEY(`id`),"
            "KEY `name` (`username`),"
            "KEY `id` (`id`),"
            "KEY `email` (`email`),"
            "KEY `last_ip` (`last_ip`)"
            ") ENGINE = InnoDB AUTO_INCREMENT = 1 DEFAULT CHARSET = UTF8MB4;")
            .execute();
        
        session.sql("CREATE TABLE IF NOT EXISTS `horizon`.`characters` ("
            "`id` int(11) unsigned NOT NULL AUTO_INCREMENT,"
            "`account_id` int(11) unsigned NOT NULL DEFAULT 0,"
            "`slot` tinyint(1) NOT NULL DEFAULT 0,"
            "`name` varchar(30) NOT NULL DEFAULT '',"
            "`online` tinyint(2) NOT NULL DEFAULT 0,"
            "`gender` enum('M', 'F', 'U') NOT NULL DEFAULT 'U',"
            "`delete_reserved_at` datetime DEFAULT NULL,"
            "`deleted_at` int(11) DEFAULT 0,"
            "`unban_time` int(11) unsigned NOT NULL DEFAULT 0,"
            "`rename_count` tinyint(2) unsigned NOT NULL DEFAULT 0,"
            "`last_unique_id` bigint(20) unsigned NOT NULL DEFAULT 0,"
            "`hotkey_row_index` tinyint(1) unsigned NOT NULL DEFAULT 0,"
            "`change_slot_count` tinyint(2) unsigned NOT NULL DEFAULT 0,"
            "`font` tinyint(1) unsigned NOT NULL DEFAULT 0,"
            "`show_equip` tinyint(1) unsigned NOT NULL DEFAULT 0,"
            "`allow_party` tinyint(1) unsigned NOT NULL DEFAULT 0,"
            "`partner_aid` int(11) unsigned NOT NULL DEFAULT 0,"
            "`father_aid` int(11) unsigned NOT NULL DEFAULT 0,"
            "`mother_aid` int(11) unsigned NOT NULL DEFAULT 0,"
            "`child_aid` int(11) unsigned NOT NULL DEFAULT 0,"
            "`party_id` int(11) unsigned NOT NULL DEFAULT 0,"
            "`guild_id` int(11) unsigned NOT NULL DEFAULT 0,"
            "`pet_id` int(11) unsigned NOT NULL DEFAULT 0,"
            "`homun_id` int(11) unsigned NOT NULL DEFAULT 0,"
            "`elemental_id` int(11) unsigned NOT NULL DEFAULT 0,"
            "`current_map` varchar(11) NOT NULL DEFAULT 'new_1-1',"
            "`current_x` smallint(4) unsigned NOT NULL DEFAULT 53,"
            "`current_y` smallint(4) unsigned NOT NULL DEFAULT 111,"
            "`saved_map` varchar(11) NOT NULL DEFAULT 'new_1-1',"
            "`saved_x` smallint(4) unsigned NOT NULL DEFAULT 53,"
            "`saved_y` smallint(4) unsigned NOT NULL DEFAULT 111,"
            "PRIMARY KEY(`id`),"
            "UNIQUE KEY `name_key` (`name`),"
            "CONSTRAINT FOREIGN KEY(account_id) REFERENCES game_accounts(id)"
            ") ENGINE = InnoDB DEFAULT CHARSET = UTF8MB4;")
            .execute();
        
        session.sql("CREATE TABLE IF NOT EXISTS `horizon`.`character_status` ("
            "`id` int(11) unsigned NOT NULL,"
            "`job_id` smallint(6) unsigned NOT NULL DEFAULT 0,"
            "`base_level` smallint(6) unsigned NOT NULL DEFAULT 1,"
            "`job_level` smallint(6) unsigned NOT NULL DEFAULT 1,"
            "`base_experience` bigint(20) unsigned NOT NULL DEFAULT 1,"
            "`job_experience` bigint(20) unsigned NOT NULL DEFAULT 1,"
            "`zeny` int(11) unsigned NOT NULL DEFAULT 0,"
            "`strength` smallint(6) unsigned NOT NULL DEFAULT 1,"
            "`agility` smallint(6) unsigned NOT NULL DEFAULT 1,"
            "`vitality` smallint(6) unsigned NOT NULL DEFAULT 1,"
            "`intelligence` smallint(6) unsigned NOT NULL DEFAULT 1,"
            "`dexterity` smallint(6) unsigned NOT NULL DEFAULT 1,"
            "`luck` smallint(6) unsigned NOT NULL DEFAULT 1,"
            "`maximum_hp` int(11) unsigned NOT NULL DEFAULT 40,"
            "`hp` int(11) unsigned NOT NULL DEFAULT 40,"
            "`maximum_sp` int(11) unsigned NOT NULL DEFAULT 40,"
            "`sp` int(11) unsigned NOT NULL DEFAULT 40,"
            "`status_points` int(11) unsigned NOT NULL DEFAULT 48,"
            "`skill_points` int(11) unsigned NOT NULL DEFAULT 0,"
            "`body_state` int(11) unsigned NOT NULL DEFAULT 0,"
            "`virtue` tinyint(3) NOT NULL DEFAULT 0,"
            "`honor` int(11) unsigned NOT NULL DEFAULT 0,"
            "`manner` smallint(6) NOT NULL DEFAULT 0,"
            "`hair_style_id` tinyint(4) unsigned NOT NULL DEFAULT 0,"
            "`hair_color_id` smallint(5) unsigned NOT NULL DEFAULT 0,"
            "`cloth_color_id` smallint(5) unsigned NOT NULL DEFAULT 0,"
            "`body_id` smallint(5) unsigned NOT NULL DEFAULT 0,"
            "`weapon_id` smallint(6) unsigned NOT NULL DEFAULT 0,"
            "`shield_id` smallint(6) unsigned NOT NULL DEFAULT 0,"
            "`head_top_view_id` smallint(6) unsigned NOT NULL DEFAULT 0,"
            "`head_mid_view_id` smallint(6) unsigned NOT NULL DEFAULT 0,"
            "`head_bottom_view_id` smallint(6) unsigned NOT NULL DEFAULT 0,"
            "`robe_view_id` smallint(6) unsigned NOT NULL DEFAULT 0,"
            "PRIMARY KEY(`id`),"
            "    CONSTRAINT FOREIGN KEY(id) REFERENCES characters(id)"
            ") ENGINE = InnoDB DEFAULT CHARSET = UTF8MB4;")
            .execute();

        session.sql("CREATE TABLE IF NOT EXISTS `horizon`.`character_inventory` ("
            "`id` int(11) unsigned NOT NULL AUTO_INCREMENT,"
            "`char_id` int(11) unsigned NOT NULL DEFAULT '0',"
            "`inventory_index` int(11) unsigned NOT NULL DEFAULT '2',"
            "`item_id` int(11) unsigned NOT NULL DEFAULT '0',"
            "`amount` int(11) unsigned NOT NULL DEFAULT '0',"
            "`equip_location_mask` int(11) unsigned NOT NULL DEFAULT '0',"
            "`is_identified` smallint(6) NOT NULL DEFAULT '0',"
            "`refine_level` tinyint(3) unsigned NOT NULL DEFAULT '0',"
            "`element_type` tinyint(4) unsigned NOT NULL DEFAULT '0',"
            "`slot_item_id_0` int(11) NOT NULL DEFAULT '0',"
            "`slot_item_id_1` int(11) NOT NULL DEFAULT '0',"
            "`slot_item_id_2` int(11) NOT NULL DEFAULT '0',"
            "`slot_item_id_3` int(11) NOT NULL DEFAULT '0',"
            "`opt_idx0` smallint(5) unsigned NOT NULL DEFAULT '0',"
            "`opt_val0` smallint(5) NOT NULL DEFAULT '0',"
            "`opt_idx1` smallint(5) unsigned NOT NULL DEFAULT '0',"
            "`opt_val1` smallint(5) NOT NULL DEFAULT '0',"
            "`opt_idx2` smallint(5) unsigned NOT NULL DEFAULT '0',"
            "`opt_val2` smallint(5) NOT NULL DEFAULT '0',"
            "`opt_idx3` smallint(5) unsigned NOT NULL DEFAULT '0',"
            "`opt_val3` smallint(5) NOT NULL DEFAULT '0',"
            "`opt_idx4` smallint(5) unsigned NOT NULL DEFAULT '0',"
            "`opt_val4` smallint(5) NOT NULL DEFAULT '0',"
            "`hire_expire_date` int(11) unsigned NOT NULL DEFAULT '0',"
            "`is_favorite` tinyint(3) unsigned NOT NULL DEFAULT '0',"
            "`bind_type` tinyint(1) unsigned NOT NULL DEFAULT '0',"
            "`unique_id` bigint(20) unsigned NOT NULL DEFAULT '0',"
            "PRIMARY KEY(`id`),"
            "KEY `char_id` (`char_id`),"
            "KEY `item_id` (`item_id`),"
            "CONSTRAINT FOREIGN KEY(`char_id`) REFERENCES characters(`id`)"
            ") ENGINE = InnoDB AUTO_INCREMENT = 0 DEFAULT CHARSET = UTF8MB4;")
            .execute();

        session.sql("INSERT INTO `horizon`.`game_accounts` (`id`, `username`, `hash`, `salt`, `gender`, `email`) VALUES (?, ?, ?, ?, ?, ?);")
            .bind(1, "test", "test", "test", "NA", "a@a.com")
            .execute();

        session.sql("INSERT INTO `horizon`.`characters` (`id`, `account_id`, `slot`, `name`, `online`, `gender`, `deleted_at`) VALUES (?, ?, ?, ?, ?, ?, ?);")
            .bind(1, 1, 0, "test", 0, "U", 0)
            .execute();

        session.sql("INSERT INTO `horizon`.`character_status` (`id`) VALUES (?);")
            .bind(1)
            .execute();

        mysqlx::Schema s = session.getSchema("horizon");
        mysqlx::Table t = s.getTable("character_inventory");
        mysqlx::TableInsert ti = t.insert("char_id", "inventory_index", "item_id");
        ti.values(1, 2, 2);
        ti.values(1, 2, 2);
        ti.execute();

        mysqlx::RowResult rr = session.sql("SELECT "
            "a.`id`, a.`account_id`, a.`slot`, a.`name`, a.`online`, a.`gender`, a.`delete_reserved_at`, a.`deleted_at`, a.`unban_time`, "
            "a.`rename_count`, a.`last_unique_id`, a.`hotkey_row_index`, a.`change_slot_count`, a.`font`, a.`show_equip`, a.`allow_party`, "
            "a.`partner_aid`, a.`father_aid`, a.`mother_aid`, a.`child_aid`, a.`party_id`, a.`guild_id`, a.`pet_id`, a.`homun_id`, "
            "a.`elemental_id`, a.`current_map`, a.`current_x`, a.`current_y`, a.`saved_map`, a.`saved_x`, a.`saved_y`, "
            "b.`job_id`, b.`base_level`, b.`job_level`, b.`base_experience`, b.`job_experience`, b.`zeny`, b.`strength`, "
            "b.`agility`, b.`vitality`, b.`intelligence`, b.`dexterity`, b.`luck`, b.`maximum_hp`, b.`hp`, b.`maximum_sp`, "
            "b.`sp`, b.`status_points`, b.`skill_points`, b.`body_state`, b.`virtue`, b.`honor`, b.`manner`, b.`hair_style_id`, "
            "b.`hair_color_id`, b.`cloth_color_id`, b.`body_id`, b.`weapon_id`, b.`shield_id`, b.`head_top_view_id`, b.`head_mid_view_id`, "
            "b.`head_bottom_view_id`, b.`robe_view_id` "
            "FROM `horizon`.`characters` as a LEFT JOIN `horizon`.`character_status` as b ON a.id = b.id WHERE a.account_id = ? AND a.deleted_at = ?")
            .bind(1, 0)
            .execute();


        session.sql("DELETE FROM `horizon`.`character_inventory` WHERE `char_id` = ?")
            .bind(1)
            .execute();

        session.sql("DELETE FROM `horizon`.`character_status` WHERE `id` = ?")
            .bind(1)
            .execute();

        session.sql("DELETE FROM `horizon`.`characters` WHERE `account_id` = ?")
            .bind(1)
            .execute();

        session.sql("DELETE FROM `horizon`.`game_accounts` WHERE `id` = ?")
            .bind(1)
            .execute();

        session.sql("DROP TABLE `horizon`.`character_inventory`;").execute();
        session.sql("DROP TABLE `horizon`.`character_status`;").execute();
        session.sql("DROP TABLE `horizon`.`characters`;").execute();
        session.sql("DROP TABLE `horizon`.`game_accounts`;").execute();

        std::list<mysqlx::Row> rs = rr.fetchAll();
        
        if (rs.size() == 0) {
            std::cerr << "error: Joined table could not return values." << std::endl;
        }

        for (mysqlx::Row r : rs) {
            BOOST_CHECK_EQUAL(r.colCount(), 63);
        }

    }
    catch (mysqlx::Error& error) {
        std::cout << "error:" << error.what() << std::endl;
    }
}
