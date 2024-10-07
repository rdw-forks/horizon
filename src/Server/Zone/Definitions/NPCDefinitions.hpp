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

#ifndef HORIZON_ZONE_NPC_DEFINITIONS_HPP
#define HORIZON_ZONE_NPC_DEFINITIONS_HPP

#include "UnitDefinitions.hpp"
#include "Server/Zone/Game/Map/Grid/GridDefinitions.hpp"
#include <memory>
#include <string>

#define NPC_START_GUID 5000000

enum npc_type
{
	FAKE_NPC               =    -1,
	NPC_TYPE_PORTAL        =    45,
	NPC_TYPE_PORTAL_HIDDEN =   139,
	NPC_TYPE_MOB_TOMB      =   565,
	NPC_TYPE_PORTAL_DBG    =   722,
	NPC_TYPE_FLAG          =   722,
	NPC_TYPE_INVISIBLE     = 32767
};

namespace Horizon
{
	namespace Zone
	{
		namespace Game
		{
			namespace Units
			{
				class NPC;
			}
		}
	}
}

struct npc_db_data
{
	std::string npc_name{""};
	std::string map_name{""};
	MapCoords coords;
	directions direction{DIR_SOUTH};
	uint16_t sprite_id{0};
	std::string script{""};
	bool script_is_file{true};
	uint16_t trigger_range{1};
	std::shared_ptr<Horizon::Zone::Units::NPC> _npc;
};

#endif /* HORIZON_ZONE_NPC_DEFINITIONS_HPP */
