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

#include "CombatComponent.hpp"

#include "Server/Common/Configuration/Horizon.hpp"
#include "BattleDefinitions.hpp"

using namespace Horizon::Zone;

void CombatComponent::sync_definitions(std::shared_ptr<sol::state> state)
{
	state->create_named_table("TargetCheckType",
		"Noone", (int) BTC_NONE,
		"Self", (int) BTC_SELF,
		"Enemy", (int) BTC_ENEMY,
		"Party", (int) BTC_PARTY,
		"AllianceOnly", (int) BTC_GUILD_ALLY,
		"Neutral", (int) BTC_NEUTRAL,
		"Guild", (int) BTC_GUILD,
		"GuildAndAlliance", (int) BTC_GUILD_AND_ALLY,
		"AllExceptGuild", (int) BTC_ALL_EXCEPT_GUILD,
		"AllExceptParty", (int) BTC_ALL_EXCEPT_PARTY,
		"AllExceptEnemy", (int) BTC_ALL_EXCEPT_ENEMY,
		"All", (int) BTC_ALL
	);

	state->create_named_table("AttackType",
		"None", (int) BAT_NONE,
		"Weapon", (int) BAT_WEAPON,
		"Magic", (int) BAT_MAGIC,
		"Misc", (int) BAT_MISC
	);

	state->create_named_table("DamageBehavior",
		"NoDamage", (int) DMG_BHVR_NONE,
		"NonOffensive", (int) DMG_BHVR_NON_OFFENSIVE,
		"SplashArea", (int) DMG_BHVR_SPLASH,
		"SplitBetweenTargets", (int) DMG_BHVR_SPLIT_BW_TARGETS,
		"IgnoreEquipATK", (int) DMG_BHVR_IGNORE_EQUIP_ATK,
		"IgnoreDefElement", (int) DMG_BHVR_IGNORE_DEF_ELE,
		"IgnoreSoftDef", (int) DMG_BHVR_IGNORE_SOFT_DEF,
		"IgnoreFLEE", (int) DMG_BHVR_IGNORE_FLEE,
		"IgnoreEquipDef", (int) DMG_BHVR_IGNORE_EQUIP_DEF
	);
}

void CombatComponent::sync_data_types(std::shared_ptr<sol::state> state)
{
}

void CombatComponent::sync_functions(std::shared_ptr<sol::state> state)
{
}