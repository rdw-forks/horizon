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

#ifndef HORIZON_ZONE_COMMON_STATUS_DEFINITIONS
#define HORIZON_ZONE_COMMON_STATUS_DEFINITIONS

enum status_effect_behavior_type {
	SEBHVR_NO_REM_DEATH  = 0x001,
	SEBHVR_NO_SAVE       = 0x002,
	SEBHVR_NO_DISPELL    = 0x004,
	SEBHVR_NO_CLEARANCE  = 0x008,
	SEBHVR_BUFF          = 0x010,
	SEBHVR_DEBUFF        = 0x020,
	SEBHVR_MADO_NO_RESET = 0x040,
	SEBHVR_NO_CLEAR      = 0x080,
	SEBHVR_VISIBLE       = 0x100,
	SEBHVR_NO_BOSS       = 0x200
};

#endif /* HORIZON_ZONE_COMMON_STATUS_DEFINITIONS */