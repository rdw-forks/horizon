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

#ifndef HORIZON_ZONE_GAME_TRAITS_ATTRIBUTES_HPP
#define HORIZON_ZONE_GAME_TRAITS_ATTRIBUTES_HPP

#include "Server/Zone/Definitions/UnitDefinitions.hpp"
#include "Server/Zone/Game/Units/Traits/ObservableStatus.hpp"
#include <memory>
#include <string>
#include <vector>
#include <chrono>
#include <functional>

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
		struct s_attribute_min_max : s_min_max
		{
			s_attribute_min_max(int32_t min, int32_t max) : s_min_max(min, max) {}
			s_attribute_min_max(int32_t min, Attribute *attr);
			// create constructor for min attribute value if required.
			s_attribute_min_max() = default;

			void update_with_live_attribute();

			bool is_valid() { return _attr != nullptr; }

		private:
			Attribute *_attr;
		};
		class ApplyLiveAttribute
		{
		public:
			ApplyLiveAttribute(Attribute *attr)
			: _attr(attr) {}

			void update_with_live_attribute(s_attribute_change_values *change);

			bool is_valid() { return _attr != nullptr; }

			Attribute *get_attribute() { return _attr; }

		private:
			Attribute *_attr;
		};

		int32_t base{ 0 };
		int32_t equip{ 0 };
		int32_t status{ 0 };
		s_attribute_min_max minmax{ 0, 0 };
		ApplyLiveAttribute apply_live_attribute{ nullptr };
		std::function<void(s_attribute_change_values &)> client_notify_function;

		s_attribute_change_values() = default;
		s_attribute_change_values(int32_t base, int32_t equip = 0, int32_t status = 0, s_attribute_min_max minmax = s_attribute_min_max(0, 0), std::function<void(s_attribute_change_values &)> client_notify_function = nullptr)
		: base(base), equip(equip), status(status), minmax(minmax), client_notify_function(client_notify_function) {}
		s_attribute_change_values(ApplyLiveAttribute apply_live_attribute, s_attribute_min_max minmax = s_attribute_min_max(0, 0), std::function<void(s_attribute_change_values &)> client_notify_function = nullptr)
		: apply_live_attribute(apply_live_attribute), minmax(minmax), client_notify_function(client_notify_function) {}
		s_attribute_change_values(Attribute *attr, s_attribute_min_max minmax = s_attribute_min_max(0, 0), std::function<void(s_attribute_change_values &)> client_notify_function = nullptr)
		: apply_live_attribute(ApplyLiveAttribute(attr)), minmax(minmax), client_notify_function(client_notify_function) {}
				
		int32_t get_base() const { return base; }
		void set_base(int32_t val) { base = val; }

		int32_t get_equip() const { return equip; }
		void set_equip(int32_t val) { equip = val; }

		int32_t get_status() const { return status; }
		void set_status(int32_t val) { status = val; }

		int32_t get_max() { return minmax.get_max(); }
		void set_max(int32_t val) { minmax.set_max(val); }

		int32_t get_min() { return minmax.get_min(); }
		void set_min(int32_t val) { minmax.set_min(val); }
		
		void update_with_live_attribute()
		{
			if (get_live_attribute().is_valid()) {
				get_live_attribute().update_with_live_attribute(this);
			}
			if (minmax.is_valid()) {
				minmax.update_with_live_attribute();
			}
		}

		ApplyLiveAttribute get_live_attribute() { return apply_live_attribute; }
		void set_live_attribute(Attribute *attr)
		{
			apply_live_attribute = ApplyLiveAttribute(attr);
		}

		std::function<void(s_attribute_change_values &)> get_client_notify_function() { return client_notify_function; }
		void set_client_notify_function(std::function<void(s_attribute_change_values &)> func) { client_notify_function = func; }
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

		virtual int32_t compute() { this->notify(); return total(); }

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
			// do not calculate until ready. Changes to stats (via permanent changes and temporary changes) 
			// will not be calculated until ready.
			_calculate_ready = false; 
			_permanent_changes.apply(notify);
			_temporary_changes.apply(notify);
			_apply_periodic_changes = true;
			_calculate_ready = true;
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

		bool is_compute_ready() const { return _calculate_ready; }
		
	protected:
		status_point_type _status_point_type{status_point_type::STATUS_POINT_INVALID};
		int32_t _base_val{0};
		int32_t _equip_val{0};
		int32_t _status_val{0};
		bool _apply_periodic_changes{false};
		bool _recalculate_flag{false};
		bool _calculate_ready{false};
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
