/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 * Copyright (c) 2020- Horizon Dev Team.
 *
 * Base Author - Sagun Khosla. (sagunxp@gmail.com)
 *
 * This is proprietary software. Unauthorized copying,
 * distribution, or modification of this file, via any
 * medium, is strictly prohibited. All rights reserved.
 **************************************************/

#ifndef HORIZON_CHARCLIENTINTERFACE_HPP
#define HORIZON_CHARCLIENTINTERFACE_HPP

#include "Server/Common/Configuration/Horizon.hpp"
#include "Server/Common/Interfaces/ClientInterface.hpp"
#include "Server/Common/Base/NetworkPacket.hpp"

namespace Horizon
{
namespace Char
{
class CharSession;
class CharClientInterface : public ClientInterface<CharSession>
{
public:
	CharClientInterface(std::shared_ptr<CharSession> s);
	~CharClientInterface();
	
	bool authorize_new_connection(uint32_t account_id, uint32_t auth_code, uint32_t account_level, uint8_t gender);
	
	bool make_new_character(std::string name, uint8_t slot, uint32_t hair_color, uint32_t hair_style, uint32_t job_class, uint8_t gender);
	bool make_new_character(std::string name, uint8_t slot, uint8_t hair_color, uint8_t hair_style);
	
	character_delete_result character_delete_soft(uint32_t character_id);
	bool character_delete_reserve(uint32_t character_id);
	bool character_delete_email(uint32_t character_id, std::string email);
	bool character_delete_birthdate(uint32_t character_id, std::string birthdate);
	bool character_delete_cancel(uint32_t character_id);
	
	bool pincode_create(uint32_t account_id, char *new_pin);
	bool pincode_change(uint32_t account_id, char *old_pin, char *new_pin);
	bool pincode_verify(uint32_t account_id, char *pincode);
	void pincode_decrypt(uint32_t seed, char *input, char *output);
	
	bool select_character(int slot);

	bool update_session(int32_t account_id);
	
protected:
	char _pincode_confirm[MAX_PINCODE_STRING_LENGTH];
};
}
}

#endif /* HORIZON_CHARCLIENTINTERFACE_HPP */
