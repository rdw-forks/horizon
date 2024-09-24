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

#include "AuthSession.hpp"

#include "Server/Auth/Interface/AuthClientInterface.hpp"
#include "Server/Auth/Socket/AuthSocket.hpp"
#include "Server/Auth/Auth.hpp"

using namespace Horizon::Auth;

AuthSession::AuthSession(uint64_t uid)
: Networking::Session<AuthSocket, AuthSession>(uid)
{
}

AuthSession::~AuthSession()
{
	//
}

void AuthSession::initialize()
{
	_pkt_tbl = std::make_unique<ClientPacketLengthTable>(shared_from_this());
	_clif = std::make_unique<AuthClientInterface>(shared_from_this());
	set_initialized(true);
}

void AuthSession::transmit_buffer(ByteBuffer _buffer, std::size_t size)
{
	if (get_socket() == nullptr || !get_socket()->is_open())
		return;
	
	if (!_buffer.is_empty()) {
		uint16_t packet_id = 0x0;
		int16_t packet_len = 0;
		
		memcpy(&packet_id, _buffer.get_read_pointer(), sizeof(int16_t));

		std::pair<int16_t, std::shared_ptr<Base::NetworkPacket<AuthSession>>> p;
		p = _pkt_tbl->get_tpacket_info(packet_id);

		if (p.first == 0) { // Check if packet sending is a handled packet.
			p = _pkt_tbl->get_hpacket_info(packet_id);
			if (p.first == 0) {
				HLog(warning) << "Trying to send packet 0x" << std::hex << packet_id << " which is unknown... ignoring.";
				return;
			}
		} 

		if (p.first == -1) {
			memcpy(&packet_len, _buffer.get_read_pointer() + 2, sizeof(int16_t));
		} else {
			packet_len = p.first;
		}

		if (packet_len != _buffer.active_length()) {
			HLog(warning) << "Packet 0x" << std::hex << packet_id << " has length len " << std::dec << packet_len << " but buffer has " << _buffer.active_length() << " bytes... ignoring.";
			return;
		}

		get_socket()->queue_buffer(std::move(_buffer));
	}
}

void AuthSession::update(uint32_t /*diff*/)
{
	std::shared_ptr<ByteBuffer> read_buf;
	while ((read_buf = get_recv_queue().try_pop())) {
		uint16_t packet_id = 0x0;
		memcpy(&packet_id, read_buf->get_read_pointer(), sizeof(uint16_t));
		HPacketTablePairType p = _pkt_tbl->get_hpacket_info(packet_id);
		p.second->handle(std::move(*read_buf));
	}
}
