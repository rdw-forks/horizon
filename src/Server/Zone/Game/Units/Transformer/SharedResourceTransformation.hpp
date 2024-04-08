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

#ifndef HORIZON_ZONE_GAME_SHARED_RESOURCE_TRANSFORMATION_HPP
#define HORIZON_ZONE_GAME_SHARED_RESOURCE_TRANSFORMATION_HPP

namespace Horizon
{
namespace Zone
{
    namespace Units 
    {
        class Skill;
        class Player;
        class NPC;
        class Item;
        class Mob;
        class Monster;
        class Homunculus;
        class Elemental;
        class Mercenary;
        class Pet;
    };
    class Unit;

namespace Game
{
template <typename UnitType>
class SharedResourceTransformation
{
public:
    SharedResourceTransformation(std::shared_ptr<UnitType> before_resource, std::shared_ptr<UnitType> after_resource);
    SharedResourceTransformation(std::shared_ptr<UnitType> before_resource);

    void set_after_resource(std::shared_ptr<UnitType> after_resource) { _after_resource = after_resource; }
    
    virtual bool prepare() { HLog(error) << "Nothing to prepare."; return true; }
    virtual bool validate() { HLog(error) << "Nothing to validate."; return true; }
    virtual bool transform() { HLog(error) << "Nothing to transform."; return true; }
    virtual bool response() { HLog(error) << "Nothing to respond."; return true; };

private:
    std::weak_ptr<UnitType> _before_resource;
    std::weak_ptr<UnitType> _after_resource;
};

template<typename UnitType>
class PreparatoryTo : public SharedResourceTransformation<UnitType>
{
public:
    PreparatoryTo(std::shared_ptr<UnitType> before_resource);

    virtual bool prepare() override { HLog(error) << "Nothing to prepare"; return true; }
    virtual bool validate() override { HLog(error) << "Nothing to validate."; return true; }
    virtual bool transform() override { HLog(error) << "Nothing to transform."; return true; }
};

template<typename UnitType>
class SubsequentTo : public SharedResourceTransformation<UnitType>
{
public:
    SubsequentTo(std::shared_ptr<UnitType> before_resource, std::shared_ptr<UnitType> after_resource);
    
    virtual bool prepare() override { HLog(error) << "Nothing to prepare"; return true; }
    virtual bool validate() override { HLog(error) << "Nothing to validate."; return true; }
    virtual bool response() override { HLog(error) << "Nothing to respond."; return true; }
};

template<typename UnitType>
class TransformResource
{
public:
    TransformResource(PreparatoryTo<UnitType> prep_to, SubsequentTo<UnitType> sub_to);
    
    virtual bool prepare() { HLog(error) << "Nothing to prepare."; return true; }
    virtual bool validate() { HLog(error) << "Nothing to Validate."; return true; }
    virtual bool transform() { HLog(error) << "Nothing to transform."; return true; }

private: 
    PreparatoryTo<UnitType> _prep_to;
    SubsequentTo<UnitType> _sub_to;
};

class PreparatoryToTransformUnit : public PreparatoryTo<Unit>
{
public:
    PreparatoryToTransformUnit(std::shared_ptr<Unit> unit);
    
    bool prepare() override;
    bool validate() override;
    bool transform() override;
};

class SubsequentToTransformUnit : public SubsequentTo<Unit>
{
public:
    SubsequentToTransformUnit(std::shared_ptr<Unit> unit);

    bool prepare() override;
    bool validate() override;
    bool response() override;
};

class TransformUnit : public TransformResource<Unit>
{
public:
    TransformUnit(PreparatoryToTransformUnit prep_to, SubsequentToTransformUnit sub_to);

    virtual bool prepare() override;
    virtual bool validate() override;
    virtual bool transform() override;
};

class PreparatoryToTransformPlayer : public PreparatoryToTransformUnit
{
public:
    PreparatoryToTransformPlayer(std::shared_ptr<Units::Player> player);

    bool prepare() override;
    bool validate() override;
    bool transform() override;
};

class SubsequentToTransformPlayer : public SubsequentToTransformUnit
{
public:
    SubsequentToTransformPlayer(std::shared_ptr<Units::Player> unit);

    bool prepare() override;
    bool validate() override;
    bool response() override;
};

class TransformPlayer : public TransformUnit
{
public:
    TransformPlayer(PreparatoryToTransformPlayer prep_to, SubsequentToTransformPlayer sub_to);
    ~TransformPlayer() { }

    virtual bool prepare() override;
    virtual bool validate() override;
    virtual bool transform() override;
};

class PreparatoryToTransformNPC : public PreparatoryToTransformUnit
{
public:
    PreparatoryToTransformNPC(std::shared_ptr<Units::NPC> npc);

    bool prepare() override;
    bool validate() override;
    bool transform() override;
};

class SubsequentToTransformNPC : public SubsequentToTransformUnit
{
public:
    SubsequentToTransformNPC(std::shared_ptr<Units::NPC> npc);

    bool prepare() override;
    bool validate() override;
    bool response() override;
};

class TransformNPC : public TransformUnit
{
public:
    TransformNPC(PreparatoryToTransformNPC prep_to, SubsequentToTransformNPC sub_to);
    ~TransformNPC() { }

    virtual bool prepare() override;
    virtual bool validate() override;
    virtual bool transform() override;
};

class PreparatoryToTransformItem : public PreparatoryToTransformUnit
{
public:
    PreparatoryToTransformItem(std::shared_ptr<Units::Item> item);

    bool prepare() override;
    bool validate() override;
    bool transform() override;
};

class SubsequentToTransformItem : public SubsequentToTransformUnit
{
public:
    SubsequentToTransformItem(std::shared_ptr<Units::Item> item);

    bool prepare() override;
    bool validate() override;
    bool response() override;
};

class TransformItem : public TransformUnit
{
public:
    TransformItem(PreparatoryToTransformItem prep_to, SubsequentToTransformItem sub_to);
    ~TransformItem() { }

    virtual bool prepare() override;
    virtual bool validate() override;
    virtual bool transform() override;
};

class PreparatoryToTransformSkill : public PreparatoryToTransformUnit
{
public:
    PreparatoryToTransformSkill(std::shared_ptr<Units::Skill> skill);

    bool prepare() override;
    bool validate() override;
    bool transform() override;
};

class SubsequentToTransformSkill : public SubsequentToTransformUnit
{
public:
    SubsequentToTransformSkill(std::shared_ptr<Units::Skill> skill);

    bool prepare() override;
    bool validate() override;
    bool response() override;
};

class TransformSkill : public TransformUnit
{
public:
    TransformSkill(PreparatoryToTransformSkill prep_to, SubsequentToTransformSkill sub_to);
    ~TransformSkill() { }

    virtual bool prepare() override;
    virtual bool validate() override;
    virtual bool transform() override;
};

class PreparatoryToTransformMob : public PreparatoryToTransformUnit
{
public:
    PreparatoryToTransformMob(std::shared_ptr<Units::Mob> mob);

    bool prepare() override;
    bool validate() override;
    bool transform() override;
};

class SubsequentToTransformMob : public SubsequentToTransformUnit
{
public:
    SubsequentToTransformMob(std::shared_ptr<Units::Mob> mob);

    bool prepare() override;
    bool validate() override;
    bool response() override;
};

class TransformMob : public TransformUnit
{
public:
    TransformMob(PreparatoryToTransformMob prep_to, SubsequentToTransformMob sub_to);
    ~TransformMob() { }

    virtual bool prepare() override;
    virtual bool validate() override;
    virtual bool transform() override;
};


class PreparatoryToTransformMonster : public PreparatoryToTransformMob
{
public:
    PreparatoryToTransformMonster(std::shared_ptr<Units::Monster> monster);

    bool prepare() override;
    bool validate() override;
    bool transform() override;
};

class SubsequentToTransformMonster : public SubsequentToTransformMob
{
public:
    SubsequentToTransformMonster(std::shared_ptr<Units::Monster> monster);

    bool prepare() override;
    bool validate() override;
    bool response() override;
};

class TransformMonster : public TransformMob
{
public:
    TransformMonster(PreparatoryToTransformMonster prep_to, SubsequentToTransformMonster sub_to);
    ~TransformMonster() { }

    virtual bool prepare() override;
    virtual bool validate() override;
    virtual bool transform() override;
};

class PreparatoryToTransformElemental : public PreparatoryToTransformMob
{
public:
    PreparatoryToTransformElemental(std::shared_ptr<Units::Elemental> elemental);

    bool prepare() override;
    bool validate() override;
    bool transform() override;
};

class SubsequentToTransformElemental : public SubsequentToTransformMob
{
public:
    SubsequentToTransformElemental(std::shared_ptr<Units::Elemental> elemental);

    bool prepare() override;
    bool validate() override;
    bool response() override;
};

class TransformElemental : public TransformMob
{
public:
    TransformElemental(PreparatoryToTransformElemental prep_to, SubsequentToTransformElemental sub_to);

    virtual bool prepare() override;
    virtual bool validate() override;
    virtual bool transform() override;
};

class PreparatoryToTransformHomunculus : public PreparatoryToTransformMob
{
public:
    PreparatoryToTransformHomunculus(std::shared_ptr<Units::Homunculus> homunculus);

    bool prepare() override;
    bool validate() override;
    bool transform() override;
};

class SubsequentToTransformHomunculus : public SubsequentToTransformMob
{
public:
    SubsequentToTransformHomunculus(std::shared_ptr<Units::Homunculus> homunculus);

    bool prepare() override;
    bool validate() override;
    bool response() override;
};

class TransformHomunculus : public TransformMob
{
public:
    TransformHomunculus(PreparatoryToTransformHomunculus prep_to, SubsequentToTransformHomunculus sub_to);

    virtual bool prepare() override;
    virtual bool validate() override;
    virtual bool transform() override;
};

class PreparatoryToTransformMercenary : public PreparatoryToTransformMob
{
public:
    PreparatoryToTransformMercenary(std::shared_ptr<Units::Mercenary> mercenary);

    bool prepare() override;
    bool validate() override;
    bool transform() override;
};

class SubsequentToTransformMercenary : public SubsequentToTransformMob
{
public:
    SubsequentToTransformMercenary(std::shared_ptr<Units::Mercenary> mercenary);

    bool prepare() override;
    bool validate() override;
    bool response() override;
};

class TransformMercenary : public TransformMob
{
public:
    TransformMercenary(PreparatoryToTransformMercenary prep_to, SubsequentToTransformMercenary sub_to);

    virtual bool prepare() override;
    virtual bool validate() override;
    virtual bool transform() override;
};

class PreparatoryToTransformPet : public PreparatoryToTransformMob
{
public:
    PreparatoryToTransformPet(std::shared_ptr<Units::Pet> pet);

    bool prepare() override;
    bool validate() override;
    bool transform() override;
};

class SubsequentToTransformPet : public SubsequentToTransformMob
{
public:
    SubsequentToTransformPet(std::shared_ptr<Units::Pet> pet);

    bool prepare() override;
    bool validate() override;
    bool response() override;
};

class TransformPet : public TransformMob
{
public:
    TransformPet(PreparatoryToTransformPet prep_to, SubsequentToTransformPet sub_to);

    virtual bool prepare() override;
    virtual bool validate() override;
    virtual bool transform() override;
};
}
}
}

#endif /* HORIZON_ZONE_GAME_SHARED_RESOURCE_TRANSFORMATION_HPP */