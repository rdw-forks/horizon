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

#include "Server/Zone/Definitions/UnitDefinitions.hpp"
#include "Server/Zone/Game/Units/Traits/ObservableStatus.hpp"
#include <memory>

namespace Horizon
{
namespace Zone
{
class Unit;
class Player;
namespace Traits
{	
	class AttributeVariance
	{
	public:
		virtual void add_min(int32_t val) { set_min(_min + val); }
		virtual void sub_min(int32_t val) { set_min(_min - std::min(_min, val)); }
		virtual int32_t get_min() const { return _min; }
		
		virtual void set_min(int32_t val)
		{
			_min = val;
		}

		virtual void add_max(int32_t val) { set_max(_max + val); }
		virtual void sub_max(int32_t val) { set_max(_max - std::min(_max, val)); }
		virtual int32_t get_max() const { return _max; }

		virtual void set_max(int32_t val)
		{
			_max = val;
		}

	protected:
		int32_t _min{ 0 }, _max{ 0 };
	};

	class Attribute;
	
	struct s_attribute_change_values
	{
		int32_t base{ 0 };
		int32_t equip{ 0 };
		int32_t status{ 0 };
		s_attribute_change_values() = default;
		s_attribute_change_values(int32_t base, int32_t equip, int32_t status) : base(base), equip(equip), status(status) {}

		int32_t get_base() const { return base; }
		void set_base(int32_t val) { base = val; }

		int32_t get_equip() const { return equip; }
		void set_equip(int32_t val) { equip = val; }

		int32_t get_status() const { return status; }
		void set_status(int32_t val) { status = val; }
	};

	class PermanentChanges
	{
	public:
		PermanentChanges(Attribute *attr) : _attr(attr) {}

		struct s_permanent_change
		{
			s_attribute_change_values change;
			std::string source{ "" };
		};

		void add_change(s_attribute_change_values change, std::string source);

		void remove_change(std::string source);

		void apply(bool notify = true);

		private:
			std::vector<s_permanent_change> _changes;
			Attribute *_attr;
	};

	class TemporaryChanges
	{
	public:
		TemporaryChanges(Attribute *attr) : _attr(attr) {}

		struct s_temporary_change
		{
			s_attribute_change_values change;
			uint64_t duration{ 0 };
			std::string source{ "" };
			std::chrono::high_resolution_clock::time_point start_time{std::chrono::high_resolution_clock::now()};
		};

		void add_change(s_attribute_change_values change, uint64_t duration, std::string source);

		void remove_change(std::string source);

		void apply(bool notify = true);

		void update(uint64_t delta);

	private:
		std::vector<s_temporary_change> _changes;
		Attribute *_attr;
	};

	class PeriodicChanges
	{
	public:
		PeriodicChanges(Attribute *attr) : _attr(attr) {}

		struct s_periodic_change
		{
			s_attribute_change_values change;
			uint64_t duration{ 0 };
			uint64_t interval{ 0 };
			std::string source{ "" };
			std::chrono::high_resolution_clock::time_point last_update{std::chrono::high_resolution_clock::now()};
			std::chrono::high_resolution_clock::time_point start_time{std::chrono::high_resolution_clock::now()};
		};

		void add_change(s_attribute_change_values change, uint64_t duration, uint64_t interval, std::string source);

		void remove_change(std::string source);

		void update(uint64_t delta);

	private:
		std::vector<s_periodic_change> _changes;
		Attribute *_attr;
	};

	class Attribute
	{
	public:

		Attribute(std::weak_ptr<Unit> unit, status_point_type st_type, int32_t base = 0, int32_t equip = 0, int32_t status = 0)
		: _status_point_type(st_type), _unit(unit)
		{
			add_permanent_change({base, equip, status}, "initial");
		}

		std::shared_ptr<Unit> unit() { return _unit.lock(); }
		void unit(std::shared_ptr<Unit> e) { _unit = e; }

		virtual void set_base(int32_t val, bool notify = true)
		{
			_base_val = val;
			if (notify) this->notify();
		}
		virtual void add_base(int32_t val, bool notify = true);
		virtual void sub_base(int32_t val, bool notify = true);
		virtual int32_t get_base() const { return _base_val; }

		virtual void set_equip(int32_t val, bool notify = true)
		{
			_equip_val = val;
			if (notify) this->notify();
		}
		virtual void add_equip(int32_t val, bool notify = true);
		virtual void sub_equip(int32_t val, bool notify = true);
		virtual int32_t get_equip() const { return _equip_val; }

		virtual void set_status(int32_t val, bool notify = true)
		{
			_status_val = val;
			if (notify) this->notify();
		}
		virtual void add_status(int32_t val, bool notify = true);
		virtual void sub_status(int32_t val, bool notify = true);
		virtual int32_t get_status() const { return _status_val; }

		virtual int32_t total() const { return _base_val + _equip_val + _status_val; }

		virtual int32_t compute() { return total(); }

		template <typename TT, typename std::enable_if<std::is_integral<TT>::value>::type* = nullptr>
		TT operator + (TT right) { return total() + right; }
		template <typename TT, typename std::enable_if<std::is_integral<TT>::value>::type* = nullptr>
		TT operator / (TT right) { return total() / right; }
		template <typename TT, typename std::enable_if<std::is_integral<TT>::value>::type* = nullptr>
		TT operator * (TT right) { return total() * right; }
		template <typename TT, typename std::enable_if<std::is_integral<TT>::value>::type* = nullptr>
		TT operator - (TT right) { return total() - right; }

		int operator + (Attribute const &right) const { return total() + right.total() ; }
		double operator / (Attribute const &right) { return right.total() / total(); }
		double operator * (Attribute const &right) { return right.total() * total(); }
		int operator - (Attribute const &right) { return right.total() - total(); }
		
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

		bool operator == (Attribute const &right) { return total() == right.total(); }
		bool operator != (Attribute const &right) { return total() != right.total(); }
		bool operator > (Attribute const &right) { return total() > right.total(); }
		bool operator >= (Attribute const &right) { return total() >= right.total(); }
		bool operator < (Attribute const &right) { return total() < right.total(); }
		bool operator <= (Attribute const &right) { return total() <= right.total(); }

		Attribute operator = (Attribute &right)
		{
			unit(right.unit());
			set_base(right.get_base());
			set_equip(right.get_equip());
			set_status(right.get_status());

			return *this;
		}
		
		void add_permanent_change(s_attribute_change_values change, std::string source)
		{
			_permanent_changes.add_change(change, source);
		}

		void remove_permanent_change(std::string source)
		{
			_permanent_changes.remove_change(source);
		}

		void add_temporary_change(s_attribute_change_values change, uint64_t duration, std::string source)
		{
			_temporary_changes.add_change(change, duration, source);
		}

		void remove_temporary_change(std::string source)
		{
			_temporary_changes.remove_change(source);
		}

		void add_periodic_change(s_attribute_change_values change, uint64_t duration, uint64_t interval, std::string source)
		{
			_periodic_changes.add_change(change, duration, interval, source);
		}

		void remove_periodic_change(std::string source)
		{
			_periodic_changes.remove_change(source);
		}

		void update(uint64_t delta)
		{
			_temporary_changes.update(delta);
			if (_apply_periodic_changes == true) {
				_periodic_changes.update(delta);
			}
		}

		void apply(bool notify = true)
		{
			_permanent_changes.apply(notify);
			_temporary_changes.apply(notify);
			_apply_periodic_changes = true;
			compute();
		}

		void reset()
		{
			_apply_periodic_changes = false;
			_base_val = 0;
			_equip_val = 0;
			_status_val = 0;
		}

		void notify();

		status_point_type get_type() const { return _status_point_type; }

		bool needs_recalculation() const { return _recalculate_flag; }
		void recalculate(bool flag) { _recalculate_flag = flag; }
		
	protected:
		status_point_type _status_point_type{status_point_type::STATUS_POINT_INVALID};
		int32_t _base_val{0};
		int32_t _equip_val{0};
		int32_t _status_val{0};
		bool _apply_periodic_changes{false};
		bool _recalculate_flag{false};
	private:
		std::weak_ptr<Unit> _unit;
		PermanentChanges _permanent_changes{this};
		TemporaryChanges _temporary_changes{this};
		PeriodicChanges _periodic_changes{this};
	};
	
}
}
}

#endif /* HORIZON_ZONE_GAME_STATUS_ATTRIBUTES_HPP */
