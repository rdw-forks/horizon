local se_id = ...

-- if package.loaded["db/status_effect_db"] then
-- 	package.loaded["db/status_effect_db"] = nil
-- end

local se_db = require("db/status_effect_db")

local function find_status_effect_by_name(name)
	return se_db[name]
end

return find_status_effect_by_name