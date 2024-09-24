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
 * This is proprietary software. Unauthorized copying,
 * distribution, or modification of this file, via any
 * medium, is strictly prohibited. All rights reserved.
 **************************************************/

#include "Appearance.hpp"

#include "Server/Zone/Game/Units/Unit.hpp"
#include "Server/Zone/Game/Units/Player/Player.hpp"
#include "Server/Zone/Session/ZoneSession.hpp"

using namespace Horizon::Zone::Traits;

void Appearance::notify_update()
{
	if (get_unit() != nullptr && get_unit()->type() == UNIT_PLAYER)
		get_unit()->template downcast<Horizon::Zone::Units::Player>()->get_session()->clif()->notify_appearance_update(_type, get(), get_left());
}
