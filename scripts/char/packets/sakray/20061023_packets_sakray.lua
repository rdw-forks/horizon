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

local d = require('default_packets_sakray')

d:add(0x028f, 6, require('CH_REQ_CHANGE_CHARNAME'))
d:add(0x028d, 34, require('CH_REQ_IS_VALID_CHARNAME'))
d:add(0x028c, 46, require('CH_SELECT_CHAR_GOINGTOBEUSED'))
d:add(0x006d, 110, require('HC_ACCEPT_MAKECHAR'))
d:add(0x0290, 4, require('HC_ACK_CHANGE_CHARNAME'))
d:add(0x028e, 4, require('HC_ACK_IS_VALID_CHARNAME'))
d:add(0x028b, -1, require('HC_CHARNOTBEENSELECTED'))

return d