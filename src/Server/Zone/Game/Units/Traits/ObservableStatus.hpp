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

#ifndef HORIZON_ZONE_GAME_TRAITS_OBSERVABLESTATUS_HPP
#define HORIZON_ZONE_GAME_TRAITS_OBSERVABLESTATUS_HPP

#include <type_traits>
#include <tuple>
template <typename OBSERVABLE, typename ... HAS_OBSERVERS>
class ObservableStatus
{
public:
	explicit ObservableStatus(HAS_OBSERVERS ... args)
	: _observers(args...)
	{
	}
	~ObservableStatus() { }

	template<std::size_t I = 0, typename... Tp>
	inline typename std::enable_if<I == sizeof...(Tp), void>::type
	notify(std::tuple<Tp...>& /*t*/)
	{ }

	template<std::size_t I = 0, typename... Tp>
	inline typename std::enable_if<I < sizeof...(Tp), void>::type
	notify(std::tuple<Tp...>& t)
	{	
		if (std::get<I>(_observers) != nullptr)
			std::get<I>(_observers)->on_observable_changed(_observable);
		notify<I + 1, Tp...>(t);
	}

	inline void notify_observers() { notify<0, HAS_OBSERVERS...>(_observers); }

	void register_observable(OBSERVABLE obs) { _observable = obs; }
	void register_observers(HAS_OBSERVERS... obs) { _observers = std::make_tuple(obs...); }

	OBSERVABLE _observable;
	std::tuple<HAS_OBSERVERS...> _observers;
};

#endif /* HORIZON_ZONE_GAME_STATUS_OBSERVABLESTATUS_HPP */
