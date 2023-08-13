local MG_FIREBOLT = require("scripts/skills/base_skill")

function MG_FIREBOLT.cast_skill(scd, skd)
	scd.cast_time = 2000
  
	local notifier_config = s_entity_skill_use_notifier_config.new()
	notifier_config.skill_id = scd.skill_id
	notifier_config.cast_time = scd.cast_time
	notifier_config.element = Element.Fire
	notifier_config.source_guid = scd.source:guid()
	notifier_config.target_guid = scd.target:guid()
	notifier_config.target_x = scd.target:map_coords():x()
	notifier_config.target_y = scd.target:map_coords():y()

	scd.source:notify_nearby_players_of_skill_use(grid_entity_skill_use_notification_type.GRID_ENTITY_SKILL_USE_NOTIFY_CASTTIME, notifier_config)
	print("Casting skill for skill " .. scd.skill_id .. " Cast Time of	" .. scd.cast_time .. " milliseconds")
end

function MG_FIREBOLT.perform_skill(scd, skd)
	if scd.target_type == SkillTargetType.Single then
		local int = scd.source:status():intelligence():get()
		local min_matk = int + math.floor(int / 7) ^ 2
		local max_matk = int + math.floor(int / 5) ^ 2

		local damage = math.random(min_matk, max_matk) * scd.skill_lv

		scd.target:status():current_hp():sub(damage)

		local attack_motion = 3050
		local attacked_motion = 500
	
		local config = s_skill_result_operation_config.new()
		config.skill_id = scd.skill_id
		config.skill_lv = scd.skill_lv
		local combat_dmg = combat_damage.new()
		
		combat_dmg.skill_cast_data = scd
		combat_dmg.amotion = attack_motion
		combat_dmg.dmotion = attacked_motion
		combat_dmg.left_damage = damage 
		combat_dmg.right_damage = 0
		combat_dmg.skill_lv = scd.skill_lv
		combat_dmg.number_of_hits = 1
		
		local stage = scd.source:combat_registry():create_combat_stage(os.time())
		stage:push_skill_result_damage_operation(scd.source, scd.target, config, combat_dmg)
		scd.source:combat_registry():queue_combat_stage(stage)
		print("queued combat result damage for skill " .. scd.skill_id)
	end
	return true
end

return MG_FIREBOLT