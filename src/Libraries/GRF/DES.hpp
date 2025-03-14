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

#ifndef HORIZON_LIBRARIES_GRF_DES_HPP
#define HORIZON_LIBRARIES_GRF_DES_HPP

#include <cstdint>
#include <cstddef>

#define USE_OPENSSL_DES 0

#if USE_OPENSSL_DES
#include <openssl/des.h>
#else

/// One 64-bit block.
typedef struct BIT64 { uint8_t b[8]; } BIT64;
#endif

class DES
{
public:
#if USE_OPENSSL_DES
	DES(const unsigned char *key);

	void decryptBlock(DES_cblock *block);
	void decrypt(unsigned char *data, size_t size);

#else
	void decryptBlock(BIT64 *block);
	void decrypt(unsigned char *data, size_t size);
	void roundFunction(BIT64 *src);
	void SBOX(BIT64 *src);
	void E(BIT64* src);
	void TP(BIT64 *src);
	void IP(BIT64 *src);
	void FP(BIT64 *src);
#endif
#if USE_OPENSSL_DES
	DES_key_schedule _schedule;
#endif
};


#endif // HORIZON_LIBRARIES_GRF_DES_HPP
