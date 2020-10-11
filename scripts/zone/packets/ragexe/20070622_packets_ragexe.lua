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

local d = require('default_packets_ragexe')

d:add(0x02b6, 7, require('CZ_ACTIVE_QUEST'))
d:add(0x02b7, 10, require('ZC_ACTIVE_QUEST'))
d:add(0x02b3, 26, require('ZC_ADD_QUEST'))
d:add(0x02b4, 6, require('ZC_DEL_QUEST'))
d:add(0x02bb, 8, require('ZC_EQUIPITEM_DAMAGED'))
d:add(0x02bc, 6, require('ZC_NOTIFY_PCBANG_PLAYING_TIME'))
d:add(0x02b5, 18, require('ZC_UPDATE_MISSION_HUNT'))

return d