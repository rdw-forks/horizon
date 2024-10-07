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

#ifndef HORIZON_ZONE_GAME_TRAITS_APPEARANCE_HPP
#define HORIZON_ZONE_GAME_TRAITS_APPEARANCE_HPP

#include "Server/Zone/Definitions/UnitDefinitions.hpp" // Linux
#include <memory>
namespace Horizon
{
namespace Zone
{
class Unit;
namespace Units
{
	class Player;
}
namespace Traits
{
	class Appearance
	{
	public:
		Appearance(std::weak_ptr<Unit> unit, unit_appearance_type type, uint32_t id = 0, uint32_t id_left = 0)
		: _unit(unit), _type(type), _id(id), _id_left(id_left)
		{ }
		~Appearance() { }

		void set(uint32_t id) { _id = id; notify_update(); }
		uint32_t get() { return _id; }

		void set_left(uint32_t id) { _id_left = id; notify_update(); }
		uint32_t get_left() { return _id_left; }

		virtual void notify_update();

		unit_appearance_type get_type() { return _type; }

	protected:
		std::shared_ptr<Unit> get_unit() { return _unit.lock(); }

	private:
		std::weak_ptr<Unit> _unit;
		unit_appearance_type _type;
		uint32_t _id{0};
		uint32_t _id_left{0};
	};

	class BaseAppearance : public Appearance
	{
	public:
		BaseAppearance(std::weak_ptr<Unit> unit, uint32_t id = 0)
		: Appearance(unit, UAT_BASE, id)
		{ }
		~BaseAppearance() { }
	};

	class HairColor : public Appearance
	{
	public:
		HairColor(std::weak_ptr<Unit> unit, uint32_t id = 0)
		: Appearance(unit, UAT_HAIR_COLOR, id)
		{ }
		~HairColor() { }
	};

	class ClothColor : public Appearance
	{
	public:
		ClothColor(std::weak_ptr<Unit> unit, uint32_t id = 0)
		: Appearance(unit, UAT_CLOTH_COLOR, id)
		{ }
		~ClothColor() { }
	};

	class WeaponSprite : public Appearance
	{
	public:
		WeaponSprite(std::weak_ptr<Unit> unit, uint32_t id = 0, uint32_t id_left = 0)
		: Appearance(unit, UAT_WEAPON_SPRITE, id, id_left)
		{ }
		~WeaponSprite() { }
	};

	class ShieldSprite : public Appearance
	{
	public:
		ShieldSprite(std::weak_ptr<Unit> unit, uint32_t id = 0)
		: Appearance(unit, UAT_SHIELD_SPRITE, id)
		{ }
		~ShieldSprite() { }
	};

	class RobeSprite : public Appearance
	{
	public:
		RobeSprite(std::weak_ptr<Unit> unit, uint32_t id = 0)
		: Appearance(unit, UAT_ROBE_SPRITE, id)
		{ }
		~RobeSprite() { }
	};

	class HeadTopSprite : public Appearance
	{
	public:
		HeadTopSprite(std::weak_ptr<Unit> unit, uint32_t id = 0)
		: Appearance(unit, UAT_HEAD_TOP_SPRITE, id)
		{ }
		~HeadTopSprite() { }
	};

	class HeadMidSprite : public Appearance
	{
	public:
		HeadMidSprite(std::weak_ptr<Unit> unit, uint32_t id = 0)
		: Appearance(unit, UAT_HEAD_MID_SPRITE, id)
		{ }
		~HeadMidSprite() { }
	};

	class HeadBottomSprite : public Appearance
	{
	public:
		HeadBottomSprite(std::weak_ptr<Unit> unit, uint32_t id = 0)
		: Appearance(unit, UAT_HEAD_BOTTOM_SPRITE, id)
		{ }
		~HeadBottomSprite() { }
	};

	class HairStyle : public Appearance
	{
	public:
		HairStyle(std::weak_ptr<Unit> unit, uint32_t id = 0)
		: Appearance(unit, UAT_HAIR_STYLE, id)
		{ }
		~HairStyle() { }
	};

	class BodyStyle : public Appearance
	{
	public:
		BodyStyle(std::weak_ptr<Unit> unit, uint32_t id = 0)
		: Appearance(unit, UAT_BODY_STYLE, id)
		{ }
		~BodyStyle() { }
	};
}
}
}

#endif /* HORIZON_ZONE_GAME_TRAITS_APPEARANCE_HPP */
