###################################################
#       _   _            _                        #
#      | | | |          (_)                       #
#      | |_| | ___  _ __ _ _______  _ __          #
#      |  _  |/ _ \| '__| |_  / _ \| '_  \        #
#      | | | | (_) | |  | |/ / (_) | | | |        #
#      \_| |_/\___/|_|  |_/___\___/|_| |_|        #
###################################################
# This file is part of Horizon (c).
# Copyright (c) 2019 Sagun K. (sagunxp@gmail.com).
# Copyright (c) 2019 Horizon Dev Team.
#
# Base Author - Sagun K. (sagunxp@gmail.com)
#
# This library is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this library.  If not, see <http://www.gnu.org/licenses/>.
###################################################

add_library(grf
	STATIC
	${CMAKE_CURRENT_SOURCE_DIR}/GRF.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/GRF.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/DES.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/DES.hpp)

target_link_libraries(grf
	PUBLIC
	${Boost_LIBRARIES})

target_include_directories(grf
	PUBLIC
		${PROJECT_SOURCE_DIR}/src
		${Boost_INCLUDE_DIRS})

#Enable policy CMP0091 for MSVC builds
if (MSVC)
	set_property(TARGET grf PROPERTY
		MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif(MSVC)

set_target_properties(grf
	PROPERTIES
	LINKER_LANGUAGE CXX
        FOLDER
        "GRF"
    DISABLE_PRECOMPILE_HEADER ON)

