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

#include "UserInterface.hpp"
#include "Server/Zone/Session/ZoneSession.hpp"


/**
 * Auction 
 */
Horizon::Zone::UI::Auction::Auction(std::shared_ptr <Horizon::Zone::ZoneSession> session)
: _session(session)
{

}

Horizon::Zone::UI::Auction::~Auction()
{

}

void Horizon::Zone::UI::Auction::add(int now_money, int max_money, int16_t delete_hour)
{
    
}

void Horizon::Zone::UI::Auction::add_cancel(int auction_id)
{
    
}

void Horizon::Zone::UI::Auction::add_item(int inventory_index, int amount)
{
    
}

void Horizon::Zone::UI::Auction::buy(int auction_id, int money)
{
    
}

void Horizon::Zone::UI::Auction::create(cz_auction_create_type type)
{

}

void Horizon::Zone::UI::Auction::search_item(cz_auction_search_type search_type, int auction_id, std::string search_text, int page_number)
{

}

void Horizon::Zone::UI::Auction::own_information(cz_auction_reqmyinfo_type type)
{

}

void Horizon::Zone::UI::Auction::stop(int auction_id)
{
    
}

bool Horizon::Zone::UI::Auction::notify_add_item(int inventory_index, zc_ack_auction_add_item_result_type result)
{
	ZC_ACK_AUCTION_ADD_ITEM pkt(get_session());
	pkt.deliver(inventory_index, result);
	return false;
}

/**
 * Chatroom 
 */
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

/**
 * Friend 
 */
Horizon::Zone::UI::Friend::Friend(std::shared_ptr<ZoneSession> session)
    : _session(session)
{

}

Horizon::Zone::UI::Friend::~Friend()
{

}

void Horizon::Zone::UI::Friend::request(int inviter_account_id, int inviter_char_id, cz_ack_req_add_friends_result_type result)
{

}

void Horizon::Zone::UI::Friend::add(std::string name)
{

}

void Horizon::Zone::UI::Friend::remove(int account_id, int char_id)
{

}

bool Horizon::Zone::UI::Friend::notify_add_friend_request(int inviter_account_id, int inviter_char_id, std::string name)
{
	ZC_REQ_ADD_FRIENDS pkt(nullptr);
	pkt.prepare(inviter_account_id, inviter_char_id, name);
	// @TODO
	return true;
}

/**
 * Guild 
 */
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


bool Horizon::Zone::UI::Guild::notify_expel_member(std::string char_name, std::string reason, std::string account_name)
{
	ZC_ACK_BAN_GUILD pkt(get_session());
	pkt.deliver(char_name, reason, account_name);
	return true;
}
bool Horizon::Zone::UI::Guild::notify_expel_member(std::string char_name, std::string reason)
{
	ZC_ACK_BAN_GUILD_SSO pkt(get_session());
	pkt.deliver(char_name, reason);
	return true;
}
/**
 * Clan 
 */
Horizon::Zone::UI::Clan::Clan(std::shared_ptr<ZoneSession> session)
: _session(session)
{

}

Horizon::Zone::UI::Clan::~Clan()
{

}

void Horizon::Zone::UI::Clan::message(std::string name)
{

}

bool Horizon::Zone::UI::Clan::notify_leave()
{
	ZC_ACK_CLAN_LEAVE pkt(get_session());
	pkt.deliver();
	return true;
}


/**
 * Mail
 */
Horizon::Zone::UI::Mail::Mail(std::shared_ptr<ZoneSession> session)
{

}

Horizon::Zone::UI::Mail::~Mail()
{

}

void Horizon::Zone::UI::Mail::check_receiver_name(std::string name)
{

}

void Horizon::Zone::UI::Mail::add_item(int inventory_index, int amount)
{

}

void Horizon::Zone::UI::Mail::delete_(int mail_id)
{

}

void Horizon::Zone::UI::Mail::retrieve_attachment(int mail_id)
{

}

void Horizon::Zone::UI::Mail::list()
{

}

void Horizon::Zone::UI::Mail::open(int mail_id)
{

}

void Horizon::Zone::UI::Mail::reset(cz_mail_reset_item_type reset)
{

}

void Horizon::Zone::UI::Mail::send(std::string recipient, std::string title, std::string body)
{

}

void Horizon::Zone::UI::Mail::return_(int mail_id, std::string receiver_name)
{

}

bool Horizon::Zone::UI::Mail::notify_add_item(int inventory_index, zc_ack_mail_add_item_result_type result)
{
	ZC_ACK_MAIL_ADD_ITEM pkt(get_session());
	pkt.deliver(inventory_index, result);
	return true;
}
bool Horizon::Zone::UI::Mail::notify_delete(int mail_id, zc_ack_mail_delete_result_type result)
{
	ZC_ACK_MAIL_DELETE pkt(get_session());
	pkt.deliver(mail_id, result);
	return true;
}
bool Horizon::Zone::UI::Mail::notify_return(int mail_id, zc_ack_mail_return_result_type result)
{
	ZC_ACK_MAIL_RETURN pkt(get_session());
	pkt.deliver(mail_id, result);
	return true;
}
/**
 * Party
 */
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

void Horizon::Zone::UI::Party::refuse_invite(bool refuse)
{
	
}

/* Notify */
void Horizon::Zone::UI::Party::notify_created(zcack_makegroup_result_type result)
{

}

/**
 * PartyBooking
 */
Horizon::Zone::UI::PartyBooking::PartyBooking(std::shared_ptr<Horizon::Zone::ZoneSession> session)
{

}

Horizon::Zone::UI::PartyBooking::~PartyBooking()
{

}

void Horizon::Zone::UI::PartyBooking::delete_()
{

}

void Horizon::Zone::UI::PartyBooking::search(int level, int map_id, int job, int last_index, int result_count)
{

}

void Horizon::Zone::UI::PartyBooking::register_(int level, int map_id, std::vector<int> jobs)
{

}

void Horizon::Zone::UI::PartyBooking::update(std::vector<int> jobs)
{

}

/**
 * RODEx
 */
Horizon::Zone::UI::RODEx::RODEx(std::shared_ptr<ZoneSession> s)
	: _session(s)
{

}

Horizon::Zone::UI::RODEx::~RODEx()
{

}

bool Horizon::Zone::UI::RODEx::notify_add_item(s_zc_ack_add_item_rodex info)
{
	ZC_ACK_ADD_ITEM_RODEX pkt(get_session());
	pkt.deliver(info);
	return true;
}

/**
 * Roulette
 */
Horizon::Zone::UI::Roulette::Roulette(std::shared_ptr<ZoneSession> s)
	: _session(s)
{

}

Horizon::Zone::UI::Roulette::~Roulette()
{

}

bool Horizon::Zone::UI::Roulette::notify_close()
{
	ZC_ACK_CLOSE_ROULETTE pkt(get_session());
	pkt.deliver(0);
	return true;
}

/**
 * Trade
 */
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

bool Horizon::Zone::UI::Trade::notify_response(zc_ack_exchange_item_result_type result)
{
	ZC_ACK_EXCHANGE_ITEM pkt(get_session());
	pkt.deliver(result);
	return true;
}

bool Horizon::Zone::UI::Trade::notify_response(zc_ack_exchange_item_result_type result, int char_id, int base_level)
{
	ZC_ACK_EXCHANGE_ITEM2 pkt(get_session());
	pkt.deliver(result, char_id, base_level);
	return true;
}

/**
 * Quest
 */
Horizon::Zone::UI::Quest::Quest(std::shared_ptr<ZoneSession> session)
{

}
Horizon::Zone::UI::Quest::~Quest()
{

}

void Horizon::Zone::UI::Quest::update_status(int quest_id, cz_active_quest_type type)
{

}