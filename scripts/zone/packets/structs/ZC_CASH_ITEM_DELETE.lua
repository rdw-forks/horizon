-----------------------------------------------------
--       _   _            _                        --
--      | | | |          (_)                       --
--      | |_| | ___  _ __ _ _______  _ __          --
--      |  _  |/ _ \| '__| |_  / _ \| '_  \        --
--      | | | | (_) | |  | |/ / (_) | | | |        --
--      \_| |_/\___/|_|  |_/___\___/|_| |_|        --
-----------------------------------------------------
-- This file is part of Horizon (c).
-- Copyright (c) 2019 Horizon Dev Team.
--
-- Base Author - Sagun Khosla. (sagunxp@gmail.com)
--
-- This library is free software; you can redistribute it and/or modify
-- it under the terms of the GNU General Public License as published by
-- the Free Software Foundation, either version 3 of the License, or
-- (at your option) any later version.
--
-- This library is distributed in the hope that it will be useful,
-- but WITHOUT ANY WARRANTY; without even the implied warranty of
-- MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
-- GNU General Public License for more details.
--
-- You should have received a copy of the GNU General Public License
-- along with this library.  If not, see <http://www.gnu.org/licenses/>.
-----------------------------------------------------

if RAGNA_ROOT == nil then print('Error: Running outside of project directory') os.exit() end

if packet_version >= 20181121 then
	local pid = 0x0299
elseif packet_version >= 20181114 then
	local pid = 0x0299
elseif packet_version >= 20180704 then
	local pid = 0x0299
elseif packet_version >= 20180103 then
	local pid = 0x0299
elseif packet_version >= 20061211 then
	local pid = 0x0299
elseif packet_version >= 0 then
	local pid = 0x0299
end

local ZC_CASH_ITEM_DELETE = {
	_id = pid,
	_length = 0,
	_buffer = nil
}


function ZC_CASH_ITEM_DELETE.new(o)
	o = o or ZC_CASH_ITEM_DELETE
	setmetatable(o, self)
	self.__index = self
	return o
end

function ZC_CASH_ITEM_DELETE.serialize()

end

return ZC_CASH_ITEM_DELETE
