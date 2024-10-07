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
 * This is proprietary software. Unauthorized copying,
 * distribution, or modification of this file, via any
 * medium, is strictly prohibited. All rights reserved.
 **************************************************/

#ifndef HORIZON_ZONE_STATUS_DEFINITIONS
#define HORIZON_ZONE_STATUS_DEFINITIONS

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

struct status_change_entry {
    int type{0};
    int current_time{0};
    int total_time{0};
    int val1{0}, val2{0}, val3{0}, val4{0};
    bool infinite_duration{false};
};

#endif /* HORIZON_ZONE_STATUS_DEFINITIONS */