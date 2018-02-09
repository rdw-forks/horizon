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

FIND_PATH(MYSQL_CONNECTOR_INCLUDE_DIR mysql_driver.h)

IF(WIN32)
    SET(CMAKE_FIND_LIBRARY_PREFIXES "lib" "")
ENDIF()

FIND_LIBRARY(MYSQL_CONNECTOR_LIBRARY NAMES mysqlcppconn
        DOC "The Mysql Connector Library"
        )

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(MYSQL_CONNECTOR DEFAULT_MSG MYSQL_CONNECTOR_INCLUDE_DIR MYSQL_CONNECTOR_LIBRARY)

IF(MYSQL_CONNECTOR_FOUND)
    SET(MYSQL_CONNECTOR_INCLUDE_DIRS ${MYSQL_CONNECTOR_INCLUDE_DIR})
    SET(MYSQL_CONNECTOR_LIBRARIES    ${MYSQL_CONNECTOR_LIBRARY})
ENDIF()

MARK_AS_ADVANCED(MYSQL_CONNECTOR_INCLUDE_DIR MYSQL_CONNECTOR_LIBRARY)
