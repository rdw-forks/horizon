#!/bin/bash
###################################################
#       _   _            _                        #
#      | | | |          (_)                       #
#      | |_| | ___  _ __ _ _______  _ __          #
#      |  _  |/ _ \| '__| |_  / _ \| '_  \        #
#      | | | | (_) | |  | |/ / (_) | | | |        #
#      \_| |_/\___/|_|  |_/___\___/|_| |_|        #
###################################################
# This file is part of Horizon (c).
#
# Copyright (c) 2023 Sagun K. (sagunxp@gmail.com).
# Copyright (c) 2023 Horizon Dev Team.
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

MODE="$1"
shift

function header
{
    echo "                                                 "
    echo "       _   _            _                        "
    echo "      | | | |          (_)                       "
    echo "      | |_| | ___  _ __ _ _______  _ __          "
    echo "      |  _  |/ _ \| '__| |_  / _ \| '_  \        "
    echo "      | | | | (_) | |  | |/ / (_) | | | |        "
    echo "      \_| |_/\___/|_|  |_/___\___/|_| |_|        "
    echo "                                                 "
    echo "        A new dawn for ragnarok online.          "
    echo "                                                 "
    echo " Copyright (c) 2023 Sagun K. (sagunxp@gmail.com)."
    echo " Copyright (c) 2023 Horizon Dev Team.            "
    echo "                                                 "
}

function usage
{
    header
	echo "usage:"
	echo "    $0 start [directory] [args]"
	echo "    $0 stop"
	echo "    $0 build [build_directory] [vcpkg_install_dir] [vcpkg_triplet]"
    echo "    $0 install [install_directory]"
	echo "    $0 auth [install_directory] [args]"
	echo "    $0 char [install_directory] [args]"
	echo "    $0 zone [install_directory] [args]"
    echo "    $0 build-tests [install_directory]"
    echo "    $0 run-tests [install_directory]"
	echo "    $0 createdb [dbuser] [dbpassword] [dbhost] <dbname>"
	echo "    $0 importdb [dbuser] [dbpassword] [dbhost] <dbname>"
	echo "    $0 adduser [dbuser] [dbpassword] [dbhost] <dbname> <new_user> <new_user_password>"
    echo "    $0 dropdb [dbuser] [dbpassword] [dbhost] <dbname>"
}

function aborterror
{
	echo "Horizon: $@"
}

function console_log
{
    echo "Horizon: $@"
}

DBNAME=horizon
DBUSER=ragnarok
DBPASS=ragnarok
DBHOST=localhost

INSTALL_DIRECTORY=""
BUILD_DIRECTORY=""
case "$MODE" in
    build)
        if [ -z "$1" ]; then
            usage
        fi
        BUILD_DIRECTORY="$1"
        ;;
    adduser)
        if [ -z "$5" ] OR [ -z "$6" ]; then
            usage
        fi
        NEWUSER="$5"
        NEWPASS="$6"
        ;&
	createdb|importdb|dropdb|test)
		if [ -z "$1" ] || [ -z "$2" ] || [ -z "$3" ] || [ -z "$4" ]; then
			usage
		fi
        DBUSER=$1
        DBPASS=$2
        DBHOST=$3
        DBNAME=$4
		;;
    install|build-tests|run-tests)
        if [ -z "$1" ]; then
            usage
        fi
        INSTALL_DIRECTORY=$1
        ;;
    auth|char|zone|start)
        if [ -z "$1" ]; then
            usage
        fi
        INSTALL_DIRECTORY=$1
        ;;
esac

function build_horizon
{
    echo "Horizon build initiated, preparing build directory..."
    cmake -B build $@ || aborterror "Horizon Build has failed."
    echo "Initiating Build..."
    cmake --build build --config Release --target install || aborterror "Horizon Build has failed."
    echo "Build Complete."
}

function build_tests
{
    echo "Horizon tests build initiated, preparing..."
    cmake -B build -DWITHOUT_SERVERS=1 -DWITH_TESTS=1 $@ || aborterror "Horizon tests build has failed."
    echo "Initiating build..."
    cmake --build build --config Release
}

function run_tests
{
    files=$(find src/Tests -type f -iname "*Test.cpp");
    for f in ${files[@]};
    do
        t=$(basename ${f::-4});
        ./"$INSTALL_DIRECTORY/${t}.exe";
    done
}

function install_horizon
{
    echo "Horizon installation will copy all required folders to the destination installation path."
    cp db $1 -r
    cp scripts $1 -r 
    cp config $1 -r
    mv $INSTALL_DIRECTORY/config/auth-server.lua.dist $INSTALL_DIRECTORY/config/auth-server.lua
    mv $INSTALL_DIRECTORY/config/char-server.lua.dist $INSTALL_DIRECTORY/config/char-server.lua
    mv $INSTALL_DIRECTORY/config/zone-server.lua.dist $INSTALL_DIRECTORY/config/zone-server.lua
}

function check_compile
{
    if [ ! -f ./"$1/$2.exe" ]; then
        aborterror "$2 is not compiled... aborting."
    fi
}

SERVERS=(auth char zone)

function start_server
{
    exe=$1
    name=$2
    dir=$3
    args_str="$4 $5 $6 $7 $8 $9"
    ###########
    # Start Server
    ###########
    exec 2>> "$1.log"
    check_compile ${dir} ${exe}
    exec "$3"/$1.exe ${args_str}
    echo "${name} Server has started."

}

case "$MODE" in
    start)
        ###########
        # Get Directory
        ###########
        dir=$1
        if [ -z "$1" ]
        then
            dir="bin"
        fi

        shift

        ###########
        # Start Servers
        ###########
        for i in ${SERVERS[@]};
        do
            check_compile ${dir} $i
            cd $dir
            serv="${i} $@"
            exec ./${serv}&
            echo $! > .${i}.pid;
            cd ..
        done
        ;;
    stop)
        cd bin
        for i in ${SERVERS[@]};
        do
            if [ -e ./.${i}.pid ]; then
                kill $(cat .${i}.pid)
                rm .${i}.pid
            fi
        done
        cd ..
        ;;
    auth)
        start_server $MODE "Authentication" $@
        ;;
    char)
        start_server $MODE "Character" $@
        ;;
    zone)
        start_server $MODE "Zone" $@
        ;;
	createdb)
		console_log "Creating Horizon MySQL Database $DBNAME as $DBUSER..."
		mysql -u $DBUSER -p$DBPASS -h $DBHOST --execute="CREATE DATABASE $DBNAME;" || aborterror "Unable to create database."
		;;
	importdb)
        console_log "Importing Horizon MySQL Tables into $DBNAME as $DBUSER..."
		mysql -u $DBUSER -p$DBPASS -h $DBHOST --database=$DBNAME < sql-files/horizon.sql || aborterror "Unable to import horizon database."
		;;
	adduser)
		console_log "Adding user $NEWUSER with access to database $DBNAME..."
        mysql -u $DBUSER -p$DBPASS -h $DBHOST --execute="CREATE USER '$NEWUSER'@'$DBHOST' IDENTIFIED BY '$NEWPASS';"
		mysql -u $DBUSER -p$DBPASS -h $DBHOST --execute="GRANT ALL ON $DBNAME.* TO '$NEWUSER'@'$DBHOST' WITH GRANT OPTION;"
		;;
    dropdb)
        console_log "Dropping database $DBNAME..."
        mysql -u $DBUSER -p$DBPASS -h $DBHOST --execute="DROP DATABASE IF EXISTS `$DBNAME`;"
        ;;
	build)
	    build_horizon $@
	    ;;
    install)
        install_horizon $@
        ;;
    build-tests)
        build_tests $@
        ;;
    run-tests)
        run_tests $@
        ;;
	*)
	usage
	;;
esac