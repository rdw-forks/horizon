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

#ifndef HORIZON_ZONE_CLIENT_DEFINITIONS_HPP
#define HORIZON_ZONE_CLIENT_DEFINITIONS_HPP

enum grid_notifier_type
{
    GRID_NOTIFY_AREA,               // area
    GRID_NOTIFY_AREA_WOS,           // area, without self
    GRID_NOTIFY_AREA_WOC,           // area, without chatrooms
    GRID_NOTIFY_AREA_WOSC,          // area, without own chatrooms
    GRID_NOTIFY_AREA_CHAT_WOC,      // hearable area, without chatrooms
    GRID_NOTIFY_AREA_DEAD,          // area, for clear unit (monster death)
    GRID_NOTIFY_CHAT,               // current chatroom
    GRID_NOTIFY_CHAT_WOS,           // current chatroom, without self
    GRID_NOTIFY_PARTY,
    GRID_NOTIFY_PARTY_WOS,
    GRID_NOTIFY_PARTY_AREA,
    GRID_NOTIFY_PARTY_AREA_WOS,
    GRID_NOTIFY_GUILD,
    GRID_NOTIFY_GUILD_WOS,
    GRID_NOTIFY_GUILD_AREA,
    GRID_NOTIFY_GUILD_AREA_WOS,
    GRID_NOTIFY_GUILD_NOBG,
    GRID_NOTIFY_DUEL,
    GRID_NOTIFY_DUEL_WOS,
    GRID_NOTIFY_SELF
};


/**   0 = damage [ damage: total damage, div: amount of hits, damage2: assassin dual-wield damage ]
 *   1 = pick up item
 *   2 = sit down
 *   3 = stand up
 *   4 = damage (endure)
 *   5 = (splash?)
 *   6 = (skill?)
 *   7 = (repeat damage?)
 *   8 = multi-hit damage
 *   9 = multi-hit damage (endure)
 *   10 = critical hit
 *   11 = lucky dodge
 *   12 = (touch skill?)
 *   13 = multi-hit critical
 */
enum zc_notify_act_3_action_types
{
    ZCNA3_DAMAGE = 0,
    ZCNA3_PICKUP_ITEM = 1,
    ZCNA3_SIT    = 2,
    ZCNA3_STAND  = 3,
    ZCNA3_ENDURE_DAMAGE = 4,
    ZCNA3_SPLASH = 5,
    ZCNA3_SKILL  = 6,
    ZCNA3_REPEAT_DAMAGE = 7,
    ZCNA3_MULTI_HIT_DAMAGE = 8,
    ZCNA3_MULTI_HIT_ENDURE_DAMAGE = 9,
    ZCNA3_CRITICAL_HIT = 10,
    ZCNA3_LUCKY_DODGE = 11,
    ZCNA3_TOUCH_SKILL = 12,
    ZCNA3_MULTI_HIT_CRITICAL = 13
};

#endif /* HORIZON_ZONE_CLIENT_DEFINITIONS_HPP */