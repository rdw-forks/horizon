local item_db = require("db/item_db")

local function find_item_by_name(item_name)
	for k, v in pairs(item_db) do
		if k == item_name then
			return v
		end
	end
	return nil
end

return find_item_by_name