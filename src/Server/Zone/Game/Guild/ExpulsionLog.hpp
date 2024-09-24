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

#ifndef HORIZON_MODELS_GUILD_HLog_HPP
#define HORIZON_MODELS_GUILD_HLog_HPP

namespace Horizon
{
namespace Models
{
namespace Guild
{
class HLog
{
public:
	HLog() { }
	~HLog() { }

	/* Guild ID */
	uint32_t get_guild_id() { return _guild_id; }
	void set_guild_id(uint32_t guild_id) { _guild_id = guild_id; }
	/* Expellee Name */
	std::string &getExpelleeName() { return _expellee_name; }
	void setExpelleeName(std::string const &name) { _expelle_name = name; }
	/* Reason */
	std::string &getReason() { return _reason; }
	void setReason(std::string const &reason) { _reason = reason; }

private:
	uint32_t _guild_id;
	std::string _expellee_name;
	std::string _reason;
}
}
}
}

#endif /* HORIZON_MODELS_GUILD_HLog_HPP */
