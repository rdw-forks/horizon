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

#include "AuthSocket.hpp"

#include "Server/Auth/Session/AuthSession.hpp"
#include "Server/Auth/SocketMgr/ClientSocketMgr.hpp"
#include "Server/Auth/Auth.hpp"

using namespace Horizon::Auth;

AuthSocket::AuthSocket(uint64_t uid)
: Socket(uid)
{
}

AuthSocket::AuthSocket(uint64_t uid, std::shared_ptr<tcp::socket> socket)
: Socket(uid, socket)
{
}

AuthSocket::~AuthSocket()
{

}

/**
 * @thread created by network thread and called from main thread / client-sockt-mgr for update().
 */
std::shared_ptr<AuthSession> AuthSocket::get_session() { return std::atomic_load(&_session); }
void AuthSocket::set_session(std::shared_ptr<AuthSession> session) { std::atomic_store(&_session, session); }

/**
 * @brief Initial method invoked once from the network thread that handles the AuthSocket.
 * @thread NetworkThread
 */
void AuthSocket::start()
{
	auto session = std::make_shared<AuthSession>(get_socket_id());
    session->set_socket(shared_from_this());
	set_session(session);

    session->initialize();

	HLog(info) << "Established connection from " << remote_ip_address();

	// Starts the async_read loop.
	async_read();
}

/**
 * @brief Socket cleanup method on connection closure. Called from close_socket() in parent class.
 * @thread NetworkThread
 */
void AuthSocket::on_close()
{
	HLog(info) << "Closed connection from " << remote_ip_address();

	/* Perform socket manager cleanup. */
	sClientSocketMgr->set_socket_for_removal(shared_from_this());
}

/**
 * @brief Method invoked when an error occured during a read operation on the socket.
 * @thread NetworkThread
 */
void AuthSocket::on_error()
{

}

/**
 * @brief Asynchronous update method periodically called from network threads.
 * @return true on successful update, false on failure.
 * @thread NetworkThread
 */
bool AuthSocket::update()
{
	if (get_shutdown_stage() >= SHUTDOWN_INITIATED)
		sClientSocketMgr->set_socket_for_removal(shared_from_this());

	return BaseSocket::update();
}
/**
 * @brief Read handler for when a message is read from the network and
 * placed within this socket's message buffer. The packet length is checked
 * before the packet is processed and its corresponding handler is called.
 * @thread NetworkThread
 */
void AuthSocket::read_handler()
{
	while (get_read_buffer().active_length()) {
		uint16_t packet_id = 0x0;
		memcpy(&packet_id, get_read_buffer().get_read_pointer(), sizeof(uint16_t));
		
		std::pair<uint16_t, std::shared_ptr<Base::NetworkPacket<AuthSession>>> p;
		p = get_session()->pkt_tbl()->get_hpacket_info(packet_id);

		if (p.first == 0) { // 
			p = get_session()->pkt_tbl()->get_tpacket_info(packet_id);
		}
		
		int16_t packet_length = p.first;
		
		if (packet_length == -1) {
			memcpy(&packet_length, get_read_buffer().get_read_pointer() + 2, sizeof(int16_t));
			if (get_read_buffer().active_length() < packet_length) {
				HLog(debug) << "Received packet 0x" << packet_id << " has expected length " << packet_length << " but buffer only supplied " << get_read_buffer().active_length() << " from client.";
				break;
			}
		} else if (packet_length == 0) {
			HLog(warning) << "Received non-existent packet id 0x" << std::hex << packet_id << ", disconnecting session..." << std::endl;
			get_read_buffer().read_completed(get_read_buffer().active_length());
			close_socket();
			break;
		}
		
		ByteBuffer b;
		b.append(get_read_buffer().get_read_pointer(), packet_length);
		get_session()->get_recv_queue().push(std::move(b));
		get_read_buffer().read_completed(packet_length);
	}
}

/**
 * @brief Packets are processed within the session associated with this socket.
 * Packets lengths are checked in the NetworkThread before being processed here in the main thread.
 * @thread Main or Other Thread (Not Network Thread)
 */
void AuthSocket::update_session(uint32_t diff)
{	
	get_session()->update(diff);
}
