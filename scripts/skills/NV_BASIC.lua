local entity, skill_id, skill_lv = ...

player = nil

if entity:type() == UnitType.Player then
	player = cast_entity_to_player(entity)
else
	print("skill:NV_BASIC: Unit Type was not Player.")
	return false
end

if player == nil then
	print("skill:NV_BASIC: Player was nil")
	return false
end

learnt = player:get_learnt_skill(skill_id)
if skill_lv == 3 and learnt ~= nil and learnt.level >= 3 then
	find_skill_by_id = require("scripts/modules/find_skill_by_id")
	find_status_effect_by_name = require("scripts/modules/find_status_effect_by_name")
	skill = find_skill_by_id(skill_id)
	se = find_status_effect_by_name("SC_SIT")
	if entity:posture() == Posture.Standing then
		entity:set_posture(Posture.Sitting)
		entity:status_effect_start(se["Id"], 9999, 0, 0, 0, 0)
		return player:perform_action(PlayerActionType.Sit)
	elseif entity:posture() == Posture.Sitting then
		entity:set_posture(Posture.Standing)
		entity:status_effect_end(se["Id"])
		return player:perform_action(PlayerActionType.Stand)
	else
		return false
	end
else
	player:on_skill_failure(skill_id, 0, 0, SkillUseFailCauseType.Level);
end