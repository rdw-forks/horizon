local MG_COLDBOLT = require("scripts/skills/base_skill")

function MG_COLDBOLT.cast_skill(scd, skd)
  scd.cast_time = 2000

  --if scd.target:type() == 5 then
  --  schedule(scd.cast_time, function ()
  --      MG_COLDBOLT.perform_skill(scd, skd)
  --  end)
  --end

  scd.source:notify_nearby_players_of_skill_use(scd.target, scd.skill_id, scd.cast_time, Element.Water)
  print("Casting skill for skill BASE_SKILL. Cast Time of  " .. scd.cast_time .. " milliseconds")
end

function MG_COLDBOLT.perform_skill(scd, skd)
  if scd.target_type == SkillTargetType.Single then
    local int = scd.source:status():intelligence():get()
    local min_matk = int + math.floor(int / 7) ^ 2
    local max_matk = int + math.floor(int / 5) ^ 2

    local damage = math.random(min_matk, max_matk) * scd.skill_lv

    scd.target:status():current_hp():sub(damage)

    local attack_motion = 3050
    local attacked_motion = 500

    local monster = cast_entity_to_monster(scd.target)
    monster:on_damage_received(scd.source, damage)
    scd.source:notify_nearby_players_of_skill_damage(scd.target, scd.skill_id, scd.skill_lv, os.time(), attack_motion, attacked_motion, damage, scd.skill_lv, 8)
  
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
    print("queued combat result damage for skill MG_COLDBOLT")
  end
  return true
end

return MG_COLDBOLT