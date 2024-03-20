---------------------------------------------------------------------------
--       _   _            _                        --
--      | | | |          (_)                       --
--      | |_| | ___  _ __ _ _______  _ __          --
--      |  _  |/ _ \| '__| |_  / _ \| '_  \        --
--      | | | | (_) | |  | |/ / (_) | | | |        --
--      \_| |_/\___/|_|  |_/___\___/|_| |_|        --
---------------------------------------------------------------------------
-- This file is part of Horizon (c).
-- Copyright (c) 2018 Horizon Dev Team.
--
-- Base Author - Sagun K. (sagunxp@gmail.com)
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
---------------------------------------------------------------------------
--- Storage Configuration
---------------------------------------------------------------------------
--- @Format Notes:
--- - There can be an unlimited amount of storages and limits.
--- - All setting names are case-sensitive and must be keyed accurately.
--- - It is not recommended to set the maximum storage capacity over 1000 items.

storage_db = {
---------------------------------------------------------------------------
------------------------------- Entry Structure ---------------------------
---------------------------------------------------------------------------
-- [ Id ] = {                              (required|unique) Unique Identifier
--	Name: (string)                         (required) Name of the storage sent to the client.
--	Capacity: (int)                        (required) Maximum capacity of the storage.
--}
---------------------------------------------------------------------------
    [1] = {
    -- DO NOT EDIT THIS ENTRY!
	-- This is the default (official) storage for an account.
	    Name = "Storage",
	    Capacity = 600
	},
    [2] = {
    -- DO NOT EDIT THIS ENTRY!
	-- This is the default (official) storage for an account.
	    Name = "Premium Storage",
	    Capacity = 600
	}
}