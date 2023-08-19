local monster_id = ...

local monster_db = require("db/monster_db")

local function find_monster_by_id(monster_id)
	for k, v in pairs(monster_db) do
		if v["Id"] == monster_id then
			return v
		end
	end
	return nil
end

return find_monster_by_id