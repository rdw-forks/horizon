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

d:add(0x023b, 6, require('CZ_ACK_STORE_PASSWORD'))
d:add(0x0361, 2, require('CZ_CHANGE_DIRECTION2'))
d:add(0x022d, 2, require('CZ_COMMAND_MER'))
d:add(0x02f6, 7, require('CZ_IRMAIL_LIST'))
d:add(0x02f3, -1, require('CZ_IRMAIL_SEND'))
d:add(0x0362, 6, require('CZ_ITEM_PICKUP2'))
d:add(0x0363, 10, require('CZ_ITEM_THROW2'))
d:add(0x07ec, 2, require('CZ_JOIN_BATTLE_FIELD'))
d:add(0x0364, 90, require('CZ_MOVE_ITEM_FROM_BODY_TO_STORE2'))
d:add(0x0802, 2, require('CZ_PARTY_BOOKING_REQ_REGISTER'))
d:add(0x0368, 26, require('CZ_REQNAME2'))
d:add(0x0369, 2, require('CZ_REQNAME_BYGID2'))
d:add(0x0437, 19, require('CZ_REQUEST_ACT2'))
d:add(0x035f, 2, require('CZ_REQUEST_MOVE2'))
d:add(0x0360, 2, require('CZ_REQUEST_TIME2'))
d:add(0x0815, 2, require('CZ_REQ_CLOSE_BUYING_STORE'))
d:add(0x0811, 2, require('CZ_REQ_OPEN_BUYING_STORE'))
d:add(0x0819, 2, require('CZ_REQ_TRADE_BUYING_STORE'))
d:add(0x0835, 6, require('CZ_SEARCH_STORE_INFO'))
d:add(0x0838, 4, require('CZ_SEARCH_STORE_INFO_NEXT_PAGE'))
d:add(0x083c, 2, require('CZ_SSILIST_ITEM_CLICK'))
d:add(0x0438, -1, require('CZ_USE_SKILL2'))
d:add(0x0366, 2, require('CZ_USE_SKILL_TOGROUND2'))
d:add(0x0367, 2, require('CZ_USE_SKILL_TOGROUND_WITHTALKBOX2'))
d:add(0x02f5, 7, require('ZC_IRMAIL_NOTIFY'))
d:add(0x02f4, 3, require('ZC_IRMAIL_SEND_RES'))

return d