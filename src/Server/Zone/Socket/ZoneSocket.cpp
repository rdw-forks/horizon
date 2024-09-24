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

#include "ZoneSocket.hpp"


#include "Server/Zone/Session/ZoneSession.hpp"

using namespace Horizon::Zone;

ZoneSocket::ZoneSocket(uint64_t uid, std::shared_ptr<tcp::socket> socket)
: Socket(uid, socket)
{
	//
}

/**
 * Session dependency.
 * @note required atomic setting/loading.
 * @thread set by network thread, retrieved by main thread.
 */
std::shared_ptr<ZoneSession> ZoneSocket::get_session() { return std::atomic_load(&_session); }
void ZoneSocket::set_session(std::shared_ptr<ZoneSession> session) { std::atomic_store(&_session, session); }

/**
 * @brief Initial method invoked once from the network thread that handles the ZoneSocket.
 */
void ZoneSocket::start()
{
	auto session = std::make_shared<ZoneSession>(get_socket_id());
	session->set_socket(shared_from_this());

	set_session(session);

	// Session initialized in network thread to initiate the packet length table and packet handling procedure.
	session->initialize();

	HLog(info) << "Established connection from '" << remote_ip_address() << "'.";

	// Start async_read loop.
	async_read();
}

/**
 * @brief Socket cleanup method on connection closure.
 * @note This method is invoked from the network thread.
 */
void ZoneSocket::on_close()
{
	HLog(info) << "Closed connection from '" << remote_ip_address() << "'.";

	if (get_session()->player() != nullptr) {
		// Remove player from map (if any)
		get_session()->perform_cleanup();
	}
}

/**
 * @brief Socket error handler.
 * @note This method is invoked from the network thread.
 */
void ZoneSocket::on_error()
{
	if (get_session()->player() != nullptr) {
		// Remove player from map (if any)
		get_session()->perform_cleanup();
	}
}

/**
 * @brief Asynchronous update method periodically called from network threads.
 * @thread NetworkThread
 * @return true on successful update, false on failure.
 */
bool ZoneSocket::update()
{
	return BaseSocket::update();
}

/**
 * Incoming buffer read handler.
 */
void ZoneSocket::read_handler()
{
	while (get_read_buffer().active_length()) {
		uint16_t packet_id = 0x0;
		memcpy(&packet_id, get_read_buffer().get_read_pointer(), sizeof(uint16_t));
		
		HPacketTablePairType p = get_session()->pkt_tbl()->get_hpacket_info(packet_id);
		
		int16_t packet_length = p.first;
		
		HLog(debug) << "Received packet 0x" << std::hex << packet_id << " of length " << std::dec << packet_length << " from client.";
		
		if (packet_length == -1) {
			memcpy(&packet_length, get_read_buffer().get_read_pointer() + 2, sizeof(int16_t));
			if (get_read_buffer().active_length() < packet_length) {
				HLog(debug) << "Received packet 0x" << std::hex << packet_id << " has expected length " << std::dec << packet_length << " but buffer only supplied " << get_read_buffer().active_length() << " from client.";
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
