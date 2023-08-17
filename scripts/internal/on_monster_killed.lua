local player, monster, with_drops, with_exp = ...

local find_monster_by_id = require("scripts/modules/find_monster_by_id")

local m_config = find_monster_by_id(monster:entity():job_id())

print(player, monster, with_drops, with_exp)

print("Player " .. player:entity():name() .. " Gained EXP: " .. m_config["Exp"] .. " Job EXP: " .. m_config["JExp"])

player_status = player:entity():status()

local stage = player:entity():combat_registry():create_combat_stage(os.time())
stage:push_attribute_operation(player:entity(), monster:entity(), player_status:base_experience():attribute(), AttributeOperationType.AddToBase, m_config["Exp"])
stage:push_attribute_operation(player:entity(), monster:entity(), player_status:job_experience():attribute(), AttributeOperationType.AddToBase, m_config["JExp"])
player:entity():combat_registry():queue_combat_stage(stage)