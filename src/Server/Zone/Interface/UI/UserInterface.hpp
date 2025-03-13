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
 *  (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 **************************************************/

#ifndef HORIZON_ZONE_USER_INTERFACE_HPP
#define HORIZON_ZONE_USER_INTERFACE_HPP

#include "Server/Zone/Definitions/ClientDefinitions.hpp"

namespace Horizon
{
namespace Zone
{
class ZoneSession;
namespace UI
{
class Auction
{
public:
    Auction(std::shared_ptr<ZoneSession> session);
    ~Auction();

	std::shared_ptr<ZoneSession> get_session() { return _session.lock(); }

    void add(int now_money, int max_money, int16_t delete_hour);
    void add_cancel(int auction_id);
    void add_item(int inventory_index, int amount);
    void buy(int auction_id, int money);
    void create(cz_auction_create_type type);
    void search_item(cz_auction_search_type search_type, int auction_id, std::string search_text, int page_number);
    void own_information(cz_auction_reqmyinfo_type type);
    void stop(int auction_id);

	bool notify_add_item(int inventory_index, zc_ack_auction_add_item_result_type result);
	
private:
	std::weak_ptr<ZoneSession> _session;
};
class Chatroom
{
public:
	Chatroom(std::shared_ptr<ZoneSession> session);
	~Chatroom();

	std::shared_ptr<ZoneSession> get_session() { return _session.lock(); }

	void create_chatroom(int limit, int _public, std::string password, std::string title);
	void role_change(int role, std::string name);
	void add_member(int chat_id, std::string password);
	void expel_member(std::string name);
	void leave();
	void change_properties(int limit, int type, std::string password, std::string title);

private:
	std::weak_ptr<ZoneSession> _session;
};
class Friend
{
public:
	Friend(std::shared_ptr<ZoneSession> session);
	~Friend();

	std::shared_ptr<ZoneSession> get_session() { return _session.lock(); }

	void request(int inviter_account_id, int inviter_char_id, cz_ack_req_add_friends_result_type result);
    void add(std::string name);
	void remove(int account_id, int char_id);
	bool notify_add_friend_request(int inviter_account_id, int inviter_char_id, std::string inviter_name);

private:
	std::weak_ptr<ZoneSession> _session;
};
class Guild
{
public:
	Guild(std::shared_ptr<ZoneSession> session);
	~Guild();
	
	void create(int master_id, std::string name);
	std::shared_ptr<ZoneSession> get_session() { return _session.lock(); }
	void request_guild_information(int type);
	void notify_menu_interface();
	void change_position_info(std::vector<s_cz_reg_change_guild_positioninfo> info);
	void change_member_positions(std::vector<s_cz_req_change_memberpos> members);
	void change_emblem(std::string emblem);
	void change_notice(int guild_id, std::string subject, std::string notice);
	void invite(int account_id, int inviter_account_id, int inviter_char_id);
	void invite(std::string name);
	void invite_response(int guild_id, cz_join_guild_response_type response);
	void leave(int guild_id, int account_id, int char_id, std::string reason);
	void expel(int guild_id, int account_id, int char_id, std::string reason);
	void send_message(std::string message);
	void invite_ally(int account_id, int inviter_account_id, int inviter_char_id);
	void invite_ally_response(int inviter_account_id, cz_ally_guild_response_type response);
	void remove_related_guild(int guild_id, cz_req_delete_related_guild_relation_type relation);
	void add_opposition(int account_id);
	void disband(std::string key);

	bool notify_expel_member(std::string char_name, std::string reason, std::string account_name);
	bool notify_expel_member(std::string char_name, std::string reason);
private:
	std::weak_ptr<ZoneSession> _session;
};

class Clan
{
public:
	Clan(std::shared_ptr<ZoneSession> session);
	~Clan();

	std::shared_ptr<ZoneSession> get_session() { return _session.lock(); }
	
    void message(std::string message);
	bool notify_leave();
    
private:
	std::weak_ptr<ZoneSession> _session;
};

class Mail
{
public:
	Mail(std::shared_ptr<ZoneSession> session);
	~Mail();

	std::shared_ptr<ZoneSession> get_session() { return _session.lock(); }

	void check_receiver_name(std::string name);
	void add_item(int inventory_index, int amount);
	void delete_(int mail_id);
	void retrieve_attachment(int mail_id);
	void list();
	void open(int mail_id);
	void reset(cz_mail_reset_item_type reset);
	void send(std::string recipient, std::string title, std::string body);
	void return_(int mail_id, std::string receiver_name);

	bool notify_add_item(int inventory_index, zc_ack_mail_add_item_result_type result);
	bool notify_delete(int mail_id, zc_ack_mail_delete_result_type result);
	bool notify_return(int mail_id, zc_ack_mail_return_result_type result);
private:
	std::weak_ptr<ZoneSession> _session;
};
class Party
{
public:
	Party(std::shared_ptr<ZoneSession> session);
	~Party();

	std::shared_ptr<ZoneSession> get_session() { return _session.lock(); }

	void create(std::string name, int item_pickup_rule, int item_share_rule);
	void invite(int account_id);
	void invite(std::string name);
	void invite_response(int party_id, enum party_invite_response_type response);
	void leave();
	void expel_member(int account_id, std::string name);
	void change_properties(int exp_share_rule, int item_pickup_rule, int item_share_rule);
	void send_message(int packet_length, std::string message);
	void change_leader(int account_id);
	void refuse_invite(bool refuse);

	/* Notify */
	void notify_created(zcack_makegroup_result_type result);

private:
	std::weak_ptr<ZoneSession> _session;
};

class PartyBooking
{
public:
	PartyBooking(std::shared_ptr<ZoneSession> session);
	~PartyBooking();

	std::shared_ptr<ZoneSession> get_session() { return _session.lock(); }

	void delete_();
	void register_(int level, int map_id, std::vector<int> jobs);
	void search(int level, int map_id, int job, int last_index, int result_count);
	void update(std::vector<int> jobs);

private:
	std::weak_ptr<ZoneSession> _session;
};
class RODEx
{
public:
	RODEx(std::shared_ptr<ZoneSession> session);
	~RODEx();
	
	std::shared_ptr<ZoneSession> get_session() { return _session.lock(); }

	bool notify_add_item(s_zc_ack_add_item_rodex info);
	
private:
	std::weak_ptr<ZoneSession> _session;
};
class Roulette
{
public:
	Roulette(std::shared_ptr<ZoneSession> session);
	~Roulette();
	
	std::shared_ptr<ZoneSession> get_session() { return _session.lock(); }

	bool notify_close();
	
private:
	std::weak_ptr<ZoneSession> _session;
};
class Trade
{
public:
	Trade(std::shared_ptr<ZoneSession> session);
	~Trade();

	std::shared_ptr<ZoneSession> get_session() { return _session.lock(); }

	void request(int account_id);
	void response(int result);
	void add_zeny(int zeny);
	void add_item(int inventory_index, int amount);
	void lock();
	void cancel();
	void commit();

	bool notify_response(zc_ack_exchange_item_result_type result);
	bool notify_response(zc_ack_exchange_item_result_type result, int char_id, int base_level);

private:
	std::weak_ptr<ZoneSession> _session;
};
class Quest
{
public:
    Quest(std::shared_ptr<ZoneSession> session);
    ~Quest();

	std::shared_ptr<ZoneSession> get_session() { return _session.lock(); }

    void update_status(int quest_id, cz_active_quest_type type);
private:
	std::weak_ptr<ZoneSession> _session;
};
}
}
}

#endif /* HORIZON_ZONE_USER_INTERFACE_HPP */