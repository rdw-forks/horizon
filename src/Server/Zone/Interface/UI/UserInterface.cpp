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

#include "UserInterface.hpp"
#include "Server/Zone/Session/ZoneSession.hpp"


Horizon::Zone::UI::Chatroom::Chatroom(std::shared_ptr <Horizon::Zone::ZoneSession> session)
    : _session(session)
{

}

Horizon::Zone::UI::Chatroom::~Chatroom()
{

}

void Horizon::Zone::UI::Chatroom::create_chatroom(int limit, int _public, std::string password, std::string title)
{

}

void Horizon::Zone::UI::Chatroom::role_change(int role, std::string name)
{

}

void Horizon::Zone::UI::Chatroom::add_member(int chat_id, std::string password)
{

}

void Horizon::Zone::UI::Chatroom::expel_member(std::string name)
{

}

void Horizon::Zone::UI::Chatroom::leave()
{

}

void Horizon::Zone::UI::Chatroom::change_properties(int limit, int type, std::string password, std::string title)
{

}

Horizon::Zone::UI::Friend::Friend(std::shared_ptr<ZoneSession> session)
    : _session(session)
{

}

Horizon::Zone::UI::Friend::~Friend()
{

}

void Horizon::Zone::UI::Friend::request(int inviter_account_id, int inviter_char_id, int response)
{
    
}

Horizon::Zone::UI::Guild::Guild(std::shared_ptr<ZoneSession> session)
    : _session(session)
{

}

Horizon::Zone::UI::Guild::~Guild()
{

}

void Horizon::Zone::UI::Guild::create(int master_id, std::string name)
{
    
}

void Horizon::Zone::UI::Guild::request_guild_information(int type)
{

}

void Horizon::Zone::UI::Guild::notify_menu_interface()
{

}

void Horizon::Zone::UI::Guild::change_position_info(std::vector<s_cz_reg_change_guild_positioninfo> info)
{

}

void Horizon::Zone::UI::Guild::change_member_positions(std::vector<s_cz_req_change_memberpos> members)
{

}

void Horizon::Zone::UI::Guild::change_emblem(std::string emblem)
{

}

void Horizon::Zone::UI::Guild::change_notice(int guild_id, std::string subject, std::string notice)
{

}


void Horizon::Zone::UI::Guild::invite(int account_id, int inviter_account_id, int inviter_char_id)
{

}

void Horizon::Zone::UI::Guild::invite(std::string name)
{

}

void Horizon::Zone::UI::Guild::invite_response(int guild_id, cz_join_guild_response_type response)
{

}

void Horizon::Zone::UI::Guild::leave(int guild_id, int account_id, int char_id, std::string reason)
{

}

void Horizon::Zone::UI::Guild::expel(int guild_id, int account_id, int char_id, std::string reason)
{

}

void Horizon::Zone::UI::Guild::send_message(std::string message)
{

}

void Horizon::Zone::UI::Guild::invite_ally(int account_id, int inviter_account_id, int inviter_char_id)
{

}

void Horizon::Zone::UI::Guild::invite_ally_response(int inviter_account_id, cz_ally_guild_response_type response)
{

}

void Horizon::Zone::UI::Guild::remove_related_guild(int guild_id, cz_req_delete_related_guild_relation_type relation)
{

}

void Horizon::Zone::UI::Guild::add_opposition(int account_id)
{

}

void Horizon::Zone::UI::Guild::disband(std::string key)
{

}

Horizon::Zone::UI::Party::Party(std::shared_ptr<Horizon::Zone::ZoneSession> session)
{

}

Horizon::Zone::UI::Party::~Party()
{

}

void Horizon::Zone::UI::Party::create(std::string name, int item_share_rule, int item_pickup_rule)
{

}

void Horizon::Zone::UI::Party::invite(int account_id)
{

}

void Horizon::Zone::UI::Party::invite(std::string name)
{

}

void Horizon::Zone::UI::Party::invite_response(int party_id, enum party_invite_response_type response)
{

}

void Horizon::Zone::UI::Party::leave()
{

}

void Horizon::Zone::UI::Party::expel_member(int account_id, std::string name)
{

}

void Horizon::Zone::UI::Party::change_properties(int exp_share_rule, int item_pickup_rule, int item_share_rule)
{

}

void Horizon::Zone::UI::Party::send_message(int packet_length, std::string message)
{

}

void Horizon::Zone::UI::Party::change_leader(int account_id)
{

}

/* Notify */
void Horizon::Zone::UI::Party::notify_created(zcack_makegroup_result_type result)
{

}

Horizon::Zone::UI::Trade::Trade(std::shared_ptr<ZoneSession> s)
	: _session(s)
{

}

Horizon::Zone::UI::Trade::~Trade()
{

}

void Horizon::Zone::UI::Trade::request(int account_id)
{

}

void Horizon::Zone::UI::Trade::response(int result)
{
	switch (result)
	{
	case 3: // accepted
	case 4: // rejected
	default:
		break;
	}
}

void Horizon::Zone::UI::Trade::add_zeny(int zeny)
{

}

void Horizon::Zone::UI::Trade::add_item(int inventory_index, int amount)
{

}

void Horizon::Zone::UI::Trade::lock()
{

}

void Horizon::Zone::UI::Trade::cancel()
{

}

void Horizon::Zone::UI::Trade::commit()
{

}