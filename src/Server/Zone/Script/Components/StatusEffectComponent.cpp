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

#include "StatusEffectComponent.hpp"

#include "Server/Common/Configuration/Horizon.hpp"
#include "StatusEffectDefinitions.hpp"

using namespace Horizon::Zone;

void StatusEffectComponent::sync_definitions(std::shared_ptr<sol::state> state)
{
	state->create_named_table("StatusEffectBehavior",
		"NoDeathReset", SEBHVR_NO_REM_DEATH,
		"NoSave", SEBHVR_NO_SAVE,
		"CantDispell", SEBHVR_NO_DISPELL,
		"CantClearance", SEBHVR_NO_CLEARANCE,
		"IsBuff", SEBHVR_BUFF,
		"IsDebuff", SEBHVR_DEBUFF,
		"MadoNoReset", SEBHVR_MADO_NO_RESET,
		"NoClear", SEBHVR_NO_CLEAR,
		"NoBoss", SEBHVR_NO_BOSS
	);
}

void StatusEffectComponent::sync_data_types(std::shared_ptr<sol::state> state)
{
}

void StatusEffectComponent::sync_functions(std::shared_ptr<sol::state> state)
{
}