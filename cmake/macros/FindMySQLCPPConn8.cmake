###################################################
#       _   _            _                        #
#      | | | |          (_)                       #
#      | |_| | ___  _ __ _ _______  _ __          #
#      |  _  |/ _ \| '__| |_  / _ \| '_  \        #
#      | | | | (_) | |  | |/ / (_) | | | |        #
#      \_| |_/\___/|_|  |_/___\___/|_| |_|        #
###################################################
# This file is part of Horizon (c).
# Copyright (c) 2018 Horizon Dev Team.
#
# Base Author - Sagun Khosla. (sagunxp@gmail.com)
#
# Under a proprietary license this file is not for use
# or viewing without permission.
###################################################

# - Find MySQL
# Find the MySQL includes and client library
# This module defines
#  MYSQLCPPCONN8_INCLUDE_DIR, where to find mysql.h
#  MYSQLCPPCONN8_LIBRARIES, the libraries needed to use MySQL.
#  MYSQLCPPCONN8_FOUND, If false, do not try to use MySQL.

find_path(MYSQLCPPCONN8_INCLUDE_DIR NAMES mysqlx/xdevapi.h
    PATHS
        /usr/include/mysql
        /usr/local/include/mysql
        /usr/include/mysql-cppconn-8
)

find_library(MYSQLCPPCONN8_LIBRARIES NAMES libmysqlcppconn8-static.a
        PATHS
        /usr/lib/mysql
        /usr/lib/x86_64-linux-gnu/
        /usr/local/lib/mysql
)

include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(libmysqlcppconn.so DEFAULT_MSG MYSQLCPPCONN8_INCLUDE_DIR MYSQLCPPCONN8_LIBRARIES)

if(MYSQLCPPCONN8_INCLUDE_DIR AND MYSQLCPPCONN8_LIBRARIES)
    set(MYSQL_FOUND TRUE)
    message(STATUS "Found MySQL Cpp Conn 8: ${MYSQLCPPCONN8_INCLUDE_DIR}, ${MYSQLCPPCONN8_LIBRARIES}")
else(MYSQLCPPCONN8_INCLUDE_DIR AND MYSQLCPPCONN8_LIBRARIES)
    set(MYSQL_FOUND FALSE)
    message(STATUS "MySQL Cpp Conn 8 not found.")
endif(MYSQLCPPCONN8_INCLUDE_DIR AND MYSQLCPPCONN8_LIBRARIES)

mark_as_advanced(MYSQLCPPCONN8_INCLUDE_DIR MYSQLCPPCONN8_LIBRARIES)