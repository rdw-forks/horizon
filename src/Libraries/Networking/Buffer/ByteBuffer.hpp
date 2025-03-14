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

#ifndef HORIZON_NETWORKING_BYTEBUFFER_HPP
#define HORIZON_NETWORKING_BYTEBUFFER_HPP

#include "ByteConverter.hpp"

#include <type_traits>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <vector>
#include <cmath>
#include <assert.h>
#include <list>
#include <map>
#include <cstdio>

// Root of ByteBuffer exception hierarchy
class ByteBufferException : public std::exception
{
public:
	~ByteBufferException() throw() { }

	char const* what() const throw() override { return msg_.c_str(); }

protected:
	std::string & message() throw() { return msg_; }

private:
	std::string msg_;
};

class ByteBufferPositionException : public ByteBufferException
{
public:
	ByteBufferPositionException(bool add, size_t pos, size_t size, size_t valueSize);

	~ByteBufferPositionException() throw() { }
};

class ByteBufferSourceException : public ByteBufferException
{
public:
	ByteBufferSourceException(size_t pos, size_t size, size_t valueSize);

	~ByteBufferSourceException() throw() { }
};

class ByteBuffer
{
public:
	const static size_t DEFAULT_SIZE = 0x1000; // Reserve 4096 bytes.

	// constructor
	ByteBuffer()
    : _rpos(0), _wpos(0)
	{
		_storage.reserve(DEFAULT_SIZE);
	}

	ByteBuffer(size_t reserve)
    : _rpos(0), _wpos(0)
	{
		_storage.reserve(reserve);
	}

	ByteBuffer(ByteBuffer&& buf)
    : _rpos(buf._rpos), _wpos(buf._wpos), _storage(std::move(buf._storage))
    { }
	
	ByteBuffer(ByteBuffer& buf, size_t len)
    : _rpos(0)
    {	
		_storage.resize(len);
		// copy len bytes from buf
		std::memcpy(&_storage[_wpos], buf.contents(), len);
		_wpos = len;
		buf._rpos += len;
	}

	ByteBuffer(ByteBuffer const& right)
    : _rpos(right._rpos), _wpos(right._wpos), _storage(right._storage)
    { }

	ByteBuffer& operator=(ByteBuffer const& right)
	{
		if (this != &right)
		{
			_rpos = right._rpos;
			_wpos = right._wpos;
			_storage = right._storage;
		}

		return *this;
	}

	virtual ~ByteBuffer()
    { }

	void clear()
	{
		_storage.clear();
        reset();
	}
    
    void reset()
    {
        _wpos = 0;
        _rpos = 0;
    }

	template <typename T> void append(T value)
	{
		append((uint8_t *)&value, sizeof(value));
	}

	template <typename T> void put(size_t pos, T value)
	{
		static_assert(std::is_fundamental<T>::value, "append(compound)");
		put(pos, (uint8_t *)&value, sizeof(value));
	}

	ByteBuffer &operator<<(uint8_t value)
	{
		append<uint8_t>(value);
		return *this;
	}

	ByteBuffer &operator<<(uint16_t value)
	{
		append<uint16_t>(value);
		return *this;
	}

	ByteBuffer &operator<<(uint32_t value)
	{
		append<uint32_t>(value);
		return *this;
	}

	ByteBuffer &operator<<(uint64_t value)
	{
		append<uint64_t>(value);
		return *this;
	}

	// signed as in 2e complement
	ByteBuffer &operator<<(int8_t value)
	{
		append<int8_t>(value);
		return *this;
	}

	ByteBuffer &operator<<(int16_t value)
	{
		append<int16_t>(value);
		return *this;
	}

	ByteBuffer &operator<<(int32_t value)
	{
		append<int32_t>(value);
		return *this;
	}

	ByteBuffer &operator<<(int64_t value)
	{
		append<int64_t>(value);
		return *this;
	}

	// floating points
	ByteBuffer &operator<<(float value)
	{
		append<float>(value);
		return *this;
	}

	ByteBuffer &operator<<(double value)
	{
		append<double>(value);
		return *this;
	}

	ByteBuffer &operator>>(bool &value)
	{
		value = read<char>() > 0 ? true : false;
		return *this;
	}

	ByteBuffer &operator>>(uint8_t &value)
	{
		value = static_cast<int>(read<unsigned char>());
		return *this;
	}

	ByteBuffer &operator>>(uint16_t &value)
	{
		value = read<unsigned short>();
		return *this;
	}

	ByteBuffer &operator>>(uint32_t &value)
	{
		value = read<unsigned int>();
		return *this;
	}

	ByteBuffer &operator>>(uint64_t &value)
	{
		value = read<unsigned long>();
		return *this;
	}

	//signed as in 2e complement
	ByteBuffer &operator>>(int8_t &value)
	{
		value = static_cast<int>(read<signed char>());
		return *this;
	}

	ByteBuffer &operator>>(int16_t &value)
	{
		value = read<short>();
		return *this;
	}

	ByteBuffer &operator>>(int32_t &value)
	{
		value = read<int>();
		return *this;
	}

	ByteBuffer &operator>>(int64_t &value)
	{
		value = read<long>();
		return *this;
	}

	ByteBuffer &operator>>(float &value)
	{
		value = read<float>();
		if (!std::isfinite(value))
			throw ByteBufferException();
		return *this;
	}

	ByteBuffer &operator>>(double &value)
	{
		value = read<double>();
		if (!std::isfinite(value))
			throw ByteBufferException();
		return *this;
	}

	uint8_t& operator[](size_t const pos)
	{
		if (pos >= maximum_length())
			throw ByteBufferPositionException(false, pos, 1, maximum_length());
		return _storage[pos];
	}

	uint8_t const& operator[](size_t const pos) const
	{
		if (pos >= maximum_length())
			throw ByteBufferPositionException(false, pos, 1, maximum_length());
		return _storage[pos];
	}

	size_t rpos() const { return _rpos; }

	size_t rpos(size_t rpos_)
	{
		_rpos = rpos_;
		return _rpos;
	}

    uint8_t* contents()
    {
        if (_storage.empty())
            throw ByteBufferException();
        return _storage.data();
    }

    uint8_t const* contents() const
    {
        if (_storage.empty())
            throw ByteBufferException();
        return _storage.data();
    }

    void finish_reading() { _rpos = wpos(); }
    void read_completed(size_t bytes) { _rpos += bytes; }
    void write_completed(size_t bytes) { _wpos += bytes; }

    size_t wpos() const { return _wpos; }
    
    uint8_t *get_base_pointer() { return _storage.data(); }
    uint8_t *get_read_pointer() { return get_base_pointer() + _rpos; }
    uint8_t *get_write_pointer() { return get_base_pointer() + _wpos; }

    std::string to_string() { return std::string(get_read_pointer(), get_write_pointer()); }

    size_t maximum_length() const { return _storage.size(); }
    size_t active_length() const { return _wpos - _rpos; }
    size_t remaining_space() const { return _storage.size() - _wpos; }
    
    bool is_empty() const { return _storage.empty(); }
    
    // Discards inactive data
    void flush()
    {
        if (_rpos) {
            if (_rpos != _wpos)
                memmove(get_base_pointer(), get_read_pointer(), active_length());
            _wpos -= _rpos;
            _rpos = 0;
        }
    }
    
    // Ensures there's "some" free space, make sure to call normalize() before this
    void ensure_free_space()
    {
        // resize buffer if it's already full
        if (remaining_space() == 0)
            _storage.resize(_storage.size() * 3 / 2);
    }
    
    void resize(size_t new_size)
    {
        _storage.resize(new_size);
    }

    void reserve(size_t ressize)
    {
        if (ressize > maximum_length())
            _storage.reserve(ressize);
    }

	template<typename T>
	void read_skip() { read_skip(sizeof(T)); }

	void read_skip(size_t skip)
	{
		if (_rpos + skip > maximum_length())
			throw ByteBufferPositionException(false, _rpos, skip, maximum_length());
		_rpos += skip;
	}

	template <typename T> 
	T read()
	{
		T r = read<T>(_rpos);
		_rpos += sizeof(T);
		return r;
	}

	template <typename T> T read(size_t pos) const
	{
		if (pos + sizeof(T) > maximum_length())
			throw ByteBufferPositionException(false, pos, sizeof(T), maximum_length());
		T val = *(reinterpret_cast<T const*>(& _storage[pos]));
		return val;
	}

	void read(char *dest, size_t len)
	{
		if (_rpos  + len > maximum_length())
			throw ByteBufferPositionException(false, _rpos, len, maximum_length());
		std::memcpy((void *) dest, &_storage[_rpos], len);
		_rpos += len;
	}

	void read(ByteBuffer &buf, size_t len)
	{
		std::memcpy(&buf._storage[buf._wpos], &_storage[_rpos], len);
		buf._wpos += len;
		_rpos += len;
	}

	void append(const char *src, size_t size)
	{
        append((const uint8_t *)src, size);
	}

	void append(std::string string)
	{
		append(string.c_str(), string.size());
	}

	template<class T>
	void append(const T *src, size_t size)
	{
		append((const uint8_t *) src, size);
	}

	template<class T, class SubT>
	void append(const T *t, size_t t_size, const SubT *sub_t, int count)
	{
		append((const uint8_t *) t, t_size);
		append((const uint8_t *) sub_t, sizeof(SubT) * count);
	}

	void append(const uint8_t *src, size_t cnt)
	{
		if (!cnt)
			throw ByteBufferSourceException(_wpos, maximum_length(), cnt);

		if (!src)
			throw ByteBufferSourceException(_wpos, maximum_length(), cnt);

		assert(maximum_length() < 10000000);

		size_t const newSize = _wpos + cnt;
		if (_storage.capacity() < newSize) // custom memory allocation rules
		{
			if (newSize < 100)
				_storage.reserve(300);
			else if (newSize < 750)
				_storage.reserve(2500);
			else if (newSize < 6000)
				_storage.reserve(10000);
			else
				_storage.reserve(400000);
		}

		if (_storage.size() < newSize)
			_storage.resize(newSize);
		std::memcpy(&_storage[_wpos], src, cnt);
		_wpos = newSize;
	}

	void append(const ByteBuffer& buffer)
	{
		if (buffer.wpos())
			append(buffer.contents(), buffer.wpos());
	}

	void put(size_t pos, const uint8_t *src, size_t cnt)
	{
		if (pos + cnt > maximum_length())
			throw ByteBufferPositionException(true, pos, cnt, maximum_length());

		if (!src)
			throw ByteBufferSourceException(_wpos, maximum_length(), cnt);

		std::memcpy(&_storage[pos], src, cnt);
	}

	void print_storage() const;

	void textlike() const;

	void hexlike() const;

	template<typename SizeT = uint16_t, typename std::enable_if<std::is_integral<SizeT>::value>::type* = nullptr>
	void emplace_size(std::size_t pos = 2)
	{
		_storage.emplace(_storage.begin() + pos, 0);
		_storage.emplace(_storage.begin() + pos + 1, 0);
		_wpos += 2;
		put(pos, (uint8_t *) &_wpos, sizeof(SizeT));
	}

protected:
	size_t _rpos{0}, _wpos{0};
	std::vector<uint8_t> _storage;
};

template<>
inline void ByteBuffer::read_skip<char const*>()
{
	read_skip<char*>();
}

template<>
inline void ByteBuffer::read_skip<std::string>()
{
	read_skip<char*>();
}

#endif /* HORIZON_NETWORKING_BYTEBUFFER_HPP */
