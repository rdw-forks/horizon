
local MG_FROSTDIVER = require("scripts/skills/base_skill")

function MG_FROSTDIVER.cast_skill(scd, skd)
	scd.cast_time = skd:get_cast_time(scd.skill_lv)
	
	local config = s_skill_execution_operation_config.new()
	config.skill_id = scd.skill_id
	config.element = skd:get_element(scd.skill_lv)
	config.cast_time = scd.cast_time
	config.skill_cast_data = scd
	config.skd = skd

	config.cast_end_function = function(scd, skd)
		if MG_FROSTDIVER.validate_after_casting(scd, skd) == false then return end
		if MG_FROSTDIVER.perform_skill(scd, skd) == false then return end
	end
	
	local stage = scd.source:combat_registry():create_combat_stage(os.time())
	stage:push_skill_execution_operation(scd.source, scd.target, config, SkillExecutionOperationType.Cast)
	scd.source:combat_registry():queue_combat_stage(stage)

	print("Casting skill for skill " .. scd.skill_id .. " Cast Time of	" .. scd.cast_time .. " milliseconds")
end

function MG_FROSTDIVER.perform_skill(scd, skd)
	if scd.target_type == SkillTargetType.Single then
		local int = scd.source:status():intelligence():get()
		local min_matk = int + math.floor(int / 7) ^ 2
		local max_matk = int + math.floor(int / 5) ^ 2
		local find_skill_by_name = require("scripts/modules/find_skill_by_name")
		local sk_config = find_skill_by_name("MG_FROSTDIVER")
		local damage = math.random(min_matk, max_matk) * scd.skill_lv

		local attack_motion = 3050
		local attacked_motion = 500
	
		local config = s_skill_result_operation_config.new()
		config.skill_id = scd.skill_id
		config.skill_lv = scd.skill_lv
		config.action_type = zc_notify_act_3_action_types.MultiHitDamage
		local combat_dmg = combat_damage.new()
		
		combat_dmg.skill_cast_data = scd
		combat_dmg.amotion = attack_motion
		combat_dmg.dmotion = attacked_motion
		combat_dmg.left_damage = damage 
		combat_dmg.right_damage = 0
		combat_dmg.skill_lv = scd.skill_lv
		combat_dmg.number_of_hits = 1
		local stage = scd.source:combat_registry():create_combat_stage(os.time())
		stage:push_attribute_operation(scd.source, scd.target, scd.target:status():current_hp():attribute(), AttributeOperationType.SubFromBase, damage)
		stage:push_skill_result_damage_operation(scd.source, scd.target, config, combat_dmg)
		scd.source:combat_registry():queue_combat_stage(stage)
		print("queued combat result damage for skill " .. scd.skill_id)
	end
	return true
end

return MG_FROSTDIVER