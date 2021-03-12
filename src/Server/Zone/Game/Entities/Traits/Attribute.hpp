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

#ifndef HORIZON_ZONE_GAME_TRAITS_ATTRIBUTES_HPP
#define HORIZON_ZONE_GAME_TRAITS_ATTRIBUTES_HPP

#include "Server/Common/Definitions/EntityDefinitions.hpp"
#include "Server/Zone/Game/Entities/Traits/ObservableStatus.hpp"

// Includes for Linux
#include <memory>
#include <algorithm>
#include <type_traits>

namespace Horizon
{
namespace Zone
{
class Entity;
namespace Entities
{
class Player;
namespace Traits
{	
	template <class T>
	class Attribute
	{
	public:
		Attribute(std::weak_ptr<Entity> entity, uint32_t base = 0, uint32_t equip = 0, uint32_t status = 0)
		: _base_val(base), _equip_val(equip), _status_val(status), _entity(entity)
		{
		}
		virtual ~Attribute() { }

		std::shared_ptr<Entity> get_entity() { return _entity.lock(); }
		void set_entity(std::shared_ptr<Entity> e) { _entity = e; }

		virtual void set_base(uint32_t val)
		{
			_base_val = val;
		}

		virtual void add_base(uint32_t val) { set_base(_base_val + val); }
		virtual void sub_base(uint32_t val) { set_base(_base_val - std::min(_base_val, val)); }
		virtual uint32_t get_base() const { return _base_val; }

		virtual void set_equip(uint32_t val)
		{
			_equip_val = val;
		}
		virtual void add_equip(uint32_t val) { set_equip(_equip_val + val); }
		virtual void sub_equip(uint32_t val) { set_equip(_equip_val - std::min(_base_val, val)); }
		virtual uint32_t get_equip() const { return _equip_val; }

		virtual void set_status(uint32_t str)
		{
			_status_val = str;
		}
		virtual void add_status(uint32_t val) { set_status(_status_val + val); }
		virtual void sub_status(uint32_t val) { set_status(_status_val - std::min(_base_val, val)); }
		virtual uint32_t get_status() const { return _status_val; }

		virtual uint32_t total() const { return _base_val + _equip_val + _status_val; }

		template <class TT>
		float operator + (Attribute<TT> const &right) const { return total() + right.total() ; }
		template <typename TT, typename std::enable_if<std::is_integral<TT>::value>::type* = nullptr>
		TT operator + (TT right) { return total() + right; }

		template <class TT>
		float operator / (Attribute<TT> const &right) { return right.total() / total(); }
		template <typename TT, typename std::enable_if<std::is_integral<TT>::value>::type* = nullptr>
		TT operator / (TT right) { return total() / right; }

		template <class TT>
		float operator * (Attribute<TT> const &right) { return right.total() * total(); }
		template <typename TT, typename std::enable_if<std::is_integral<TT>::value>::type* = nullptr>
		TT operator * (TT right) { return total() * right; }

		template <class TT>
		float operator - (Attribute<TT> const &right) { return right.total() - total(); }
		template <typename TT, typename std::enable_if<std::is_integral<TT>::value>::type* = nullptr>
		TT operator - (TT right) { return total() - right; }

		template <typename TT, typename std::enable_if<std::is_integral<TT>::value>::type* = nullptr>
		bool operator == (TT right) { return total() == right; }
		template <typename TT, typename std::enable_if<std::is_integral<TT>::value>::type* = nullptr>
		bool operator != (TT right) { return total() != right; }
		template <typename TT, typename std::enable_if<std::is_integral<TT>::value>::type* = nullptr>
		bool operator > (TT right) { return total() > right; }
		template <typename TT, typename std::enable_if<std::is_integral<TT>::value>::type* = nullptr>
		bool operator >= (TT right) { return total() >= right; }
		template <typename TT, typename std::enable_if<std::is_integral<TT>::value>::type* = nullptr>
		bool operator < (TT right) { return total() < right; }
		template <typename TT, typename std::enable_if<std::is_integral<TT>::value>::type* = nullptr>
		bool operator <= (TT right) { return total() <= right; }

		Attribute<T> operator = (Attribute<T> const &right)
		{
			set_entity(right.get_entity());
			set_base(right.get_base(), false);
			set_equip(right.get_equip(), false);
			set_status(right.get_status(), false);

			return *this;
		}

	protected:
		uint32_t _base_val{0};
		uint32_t _equip_val{0};
		uint32_t _status_val{0};
	private:
		std::weak_ptr<Entity> _entity;
	};
}
}
}
}

#endif /* HORIZON_ZONE_GAME_STATUS_ATTRIBUTES_HPP */
