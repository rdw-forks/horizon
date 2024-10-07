/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
       \_| |_/\___/|_|  |_/___\___/|_| |_|        *
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

#include "Mob.hpp"

#include "Server/Zone/Game/Map/Map.hpp"
#include "Server/Zone/Game/Units/Traits/Status.hpp"
#include "Server/Zone/Game/Units/Mob/Mob.hpp"
#include "Server/Zone/Game/Units/Player/Player.hpp"
#include "Server/Zone/Definitions/MonsterDefinitions.hpp"
#include "Server/Zone/Definitions/UnitDefinitions.hpp"
using namespace Horizon::Zone::Units;

Mob::Mob(uint64_t uuid, unit_type type, unit_type_mask type_mask, std::shared_ptr<Map> map, MapCoords mcoords)
: Unit(uuid, type, type_mask, map, mcoords)
{
	//
}

Mob::~Mob()
{
}

bool Mob::initialize(std::shared_ptr<const monster_config_data> md)
{
	if (Unit::initialize() == false)
		return false;

	if (status()->initialize(shared_from_this()->downcast<Mob>(), md) == false) {
		HLog(error) << "Status::initialize: failed to initialize status for creature with monster id " << md->monster_id << ".";
		return false;
	}

	return true;
}

bool Mob::finalize()
{
	if (!Unit::finalize())
		return false;

	return true;
}

void Mob::on_damage_received(std::shared_ptr<Unit> damage_dealer, int damage)
{
	Unit::on_damage_received(damage_dealer, damage);
}

void Mob::on_killed(std::shared_ptr<Unit> killer, bool with_drops, bool with_exp)
{
	Unit::on_killed(killer, with_drops, with_exp);

	if (killer->type() == UNIT_PLAYER) {
		killer->downcast<Player>()->remove_unit_from_viewport(shared_from_this(), EVP_NOTIFY_DEAD);
	}
}