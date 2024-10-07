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

#include "ByteBuffer.hpp"

#include <iostream>
#include <sstream>

ByteBufferPositionException::ByteBufferPositionException(bool add, size_t pos,
														 size_t size, size_t valueSize)
{
	std::ostringstream ss;

	ss << "Attempted to " << (add ? "put" : "get") << " value with size: "
	<< valueSize << " in ByteBuffer (pos: " << pos << " size: " << size
	<< ")";

	message().assign(ss.str());
}

ByteBufferSourceException::ByteBufferSourceException(size_t pos, size_t size,
													 size_t valueSize)
{
	std::ostringstream ss;

	ss << "Attempted to put a "
	<< (valueSize > 0 ? "NULL-pointer" : "zero-sized value")
	<< " in ByteBuffer (pos: " << pos << " size: " << size << ")";

	message().assign(ss.str());
}

void ByteBuffer::print_storage() const
{
	std::ostringstream o;
	o << "STORAGE_SIZE: " << _storage.size();
	for (uint32_t i = 0; i < _storage.size(); ++i)
		o << read<uint8_t>(i) << " - ";
	o << " ";

	std::cout << o.str() << std::endl;
	//TC_LOG_TRACE("network", "%s", o.str().c_str());
}

void ByteBuffer::textlike() const
{
	std::ostringstream o;
	o << "STORAGE_SIZE: " << active_length();
	for (uint32_t i = 0; i < active_length(); ++i)
	{
		char buf[2];
		snprintf(buf, 2, "%c", read<uint8_t>(i));
		o << buf;
	}
	o << " ";
	std::cout << o.str() << std::endl;
	//TC_LOG_TRACE("network", "%s", o.str().c_str());
}

void ByteBuffer::hexlike() const
{
	uint32_t j = 1, k = 1;

	std::ostringstream o;
	o << "STORAGE_SIZE: " << active_length();

	for (uint32_t i = 0; i < active_length(); ++i)
	{
		char buf[3];
		snprintf(buf, 3, "%2X ", read<uint8_t>(i));
		if ((i == (j * 8)) && ((i != (k * 16))))
		{
			o << "| ";
			++j;
		}
		else if (i == (k * 16))
		{
			o << "\n";
			++k;
			++j;
		}

		o << buf;
	}
	o << " ";

	std::cout << o.str() << std::endl;

	//TC_LOG_TRACE("network", "%s", o.str().c_str());
}
