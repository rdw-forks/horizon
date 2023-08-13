local MG_LIGHTNINGBOLT = require("scripts/skills/base_skill")

function MG_LIGHTNINGBOLT.cast_skill(scd, skd)
  scd.cast_time = 2000

  if scd.target:type() == 5 then
    schedule(scd.cast_time, function ()
        MG_LIGHTNINGBOLT.perform_skill(scd, skd)
    end)
  end

  scd.source:notify_nearby_players_of_skill_use(scd.target, scd.skill_id, scd.cast_time, Element.Water)
  print("Casting skill for skill BASE_SKILL. Cast Time of  " .. scd.cast_time .. " milliseconds")
end

function MG_LIGHTNINGBOLT.perform_skill(scd, skd)
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
  end
  return true
end

return MG_LIGHTNINGBOLT