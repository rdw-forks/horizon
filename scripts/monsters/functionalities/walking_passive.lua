local entity = ...

monster = cast_entity_to_monster(entity)

if (monster == nil) then
	print("Monster (" .. entity:guid() .. ") " .. entity:name() .. " could not be casted from Entity.")
	return
end

math.randomseed(os.time())

mc = entity:map():get_random_coordinates_in_walkable_range(entity:map_coords():x(), entity:map_coords():y(), 5, 7)
monster:set_next_walk_time(os.time() + math.random(0, 4) + 1)

if mc:x() == 0 and mc:y() == 0 then
	print("Monster (" .. entity:guid() .. ") " .. entity:name() .. " could not move, coordinates not found.")
	return
end

if entity:move_to_coordinates(mc:x(), mc:y()) == false then
	print("Monster (" .. entity:guid() .. ") ".. entity:name() .. " could not move to coordinates.")
	return
end

wp = entity:get_walk_path()

total_move_cost = 0
for i = 0, #wp, 1 do
	if wp[i] ~= nil then
		total_move_cost = total_move_cost + wp[i]:move_cost()
	end
end

print("Monster (" .. entity:guid() .. ") " .. entity:name() .. " is set to travel from (" .. entity:map_coords():x() .. "," .. entity:map_coords():y() .. ") to (" .. mc:x() .. ", " .. mc:y() ..") cost (" .. total_move_cost ..").")

monster:set_next_walk_time(monster:next_walk_time() + math.floor(total_move_cost / 10))