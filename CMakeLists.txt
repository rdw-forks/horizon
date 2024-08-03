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
####################################################

#################################
# Project Setup
#################################
cmake_minimum_required (VERSION 3.7 FATAL_ERROR)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(PROJECT_NAME "Horizon")

project (${PROJECT_NAME})
enable_language(CXX)
enable_language(C)

#################################
# CMAKE Module Path
#################################
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/macros")

#################################
# Find revision ID and hash of the sourcetree
#################################
if(NOT WITHOUT_GIT)
	find_package(Git)
endif()

#################################
# Binary Installation Directory
#################################
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#################################
# INCLUDE COMPONENTS
#################################
include(CheckCXXSourceRuns)
include(CheckIncludeFiles)
include(CheckPlatform)
include(GroupSources)
include(AutoCollect)

#################
# Generate version.hpp File
#################
include(cmake/genversion/genversion.cmake)

#################################
# print out the results before continuing
#################################
include(cmake/showoptions.cmake)

include (CheckCXXSourceCompiles)

check_cxx_source_compiles("
	#include <regex>
	int main() { std::wregex r(L\".*\"); }"
				STD_HAS_WORKING_WREGEX)


#################################
# Boost Library
#################################
set(BOOST_REQUIRED_VERSION 1.82.0)

set(BOOST_COMPONENTS locale filesystem log log_setup charconv)

if (WITH_TESTS)
	set(BOOST_COMPONENTS ${BOOST_COMPONENTS} unit_test_framework)
endif()

# Remove warnings for new versions of Boost
set(Boost_NO_WARN_NEW_VERSIONS 1)

find_package(Boost ${BOOST_REQUIRED_VERSION} REQUIRED COMPONENTS ${BOOST_COMPONENTS})

# Fix: error LNK2038: mismatch detected for 'boost_log_abi': value 'v2_mt_nt6' doesn't match value 'v2_mt_nt62'
if (WIN32)
    if (CMAKE_SYSTEM_VERSION VERSION_GREATER_EQUAL 10.0.2)
		message(STATUS "Hotfix: Target system is Windows 11. Setting OS specific instructions for Boost.Log library linkage...")
		add_definitions(-D_WIN32_WINNT=0x0602)
	elseif (CMAKE_SYSTEM_VERSION VERSION_GREATER_EQUAL 10.0.1)
		message(STATUS "Hotfix: Target system is Windows 10.  Setting OS specific instructions for for Boost.Log library linkage...")
		add_definitions(-D_WIN32_WINNT=0x0601)
    else()
        message(STATUS "Target system is older than Windows 10, it is unsupported.")
    endif()
endif()

message(STATUS "Hotfix: Enabling dynamic linkage for Boost.Log library...")
add_definitions(-DBOOST_LOG_DYN_LINK)
message(STATUS "Hotfix: Enabling dynamic linkage for Boost.Test library...")
add_definitions(-DBOOST_TEST_DYN_LINK)
#################
# OpenSSL Library
#################
find_package(OpenSSL REQUIRED)

#################
# Readline Library
#################
set(Readline_FIND_REQUIRED true)
include(FindReadline)

###############
# Lua
###############
find_package(Lua 5.0 REQUIRED)

###############
# Sol2
###############
if (WIN32)
find_package(sol2 3.3.0 REQUIRED)
elseif(UNIX)
include(FindSol2)
endif()

#################
# Find ZLIB
#################
find_package(ZLIB REQUIRED)

#################
# Horizon Project Source
#################
add_subdirectory(src)