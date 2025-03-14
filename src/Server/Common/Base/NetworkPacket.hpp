/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
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

#ifndef HORIZON_BASE_NETWORKPACKET_HPP
#define HORIZON_BASE_NETWORKPACKET_HPP

#include "Core/Logging/Logger.hpp"
#include "Libraries/Networking/Buffer/ByteBuffer.hpp"

#include <memory>

namespace Horizon
{
namespace Base
{
template <class SessionType>
class NetworkPacket
{
public:
	explicit NetworkPacket(uint16_t packet_id, std::shared_ptr<SessionType> s)
	: _packet_id(packet_id), _session(s)
	{
		//
	}

	virtual ~NetworkPacket()
	{
		//
	}

    void set_packet_id(uint16_t id) { _packet_id = id; }
    uint16_t get_packet_id() { return _packet_id; }
    
    ByteBuffer &buf() { return _buffer; }
	
	/**
	 * @brief Retrieves the session from this handler instance.
	 * @return shared_ptr to an object of the session type.
	 */
	std::shared_ptr<SessionType> get_session() { return _session.lock(); }
    
	virtual void handle(ByteBuffer &&buf) {}
	virtual void deserialize(ByteBuffer &buf) {}
	
	/**
	 * @brief Send an Asynchronous packet by queueing
	 *        a buffer of a particular size to the
	 *        connected session.
	 * @param[in|out] buf    packet buffer to be queued.
	 */
	void transmit();
	
	/**
	 * @brief Send an Asynchronous packet by queueing
	 *        a buffer of a particular size to the
	 *        connected session.
	 * @param[in]     size   size of the buffer to be queued (default sizeof type T)
	 */
	void transmit(std::size_t size);
protected:
    ByteBuffer _buffer;                    ///< Buffer storage facility for the packet stream.
    uint16_t _packet_id;                   ///< ID of the network packet.
    
private:
	std::weak_ptr<SessionType> _session;   ///< Pointer to the instantiated session object.
};

template <class SessionType>
void NetworkPacket<SessionType>::transmit()
{
	transmit(this->_buffer.active_length());
}

/**
 * @brief Send an Asynchronous packet by queueing
 *        a buffer of a particular size to the
 *        connected session.
 * @param[in]     size   size of the buffer to be queued (default sizeof type T)
 */
template <class SessionType>
void NetworkPacket<SessionType>::transmit(std::size_t size)
{
	std::shared_ptr<SessionType> s = this->get_session();
	if (s == nullptr) {
		HLog(debug) << "NetworkPacket::transmit: Session was null.";
		return;
	}
	
	if (this->_buffer.is_empty()) {
		HLog(debug) << "Attempted to transmit empty buffer.";
		return;
	}
	
	s->transmit_buffer(std::move(this->_buffer), size);
}

}
}

#endif /* HORIZON_BASE_NETWORKPACKET_HPP */
