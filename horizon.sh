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
	echo "    $0 build [build_directory] [args]"
	echo "    $0 auth [args]"
	echo "    $0 char [args]"
	echo "    $0 zone [args]"
    echo "    $0 build-tests [install_directory]"
    echo "    $0 run-tests [install_directory]"
	echo "    $0 inter [directory] [args]"
	echo "    $0 createdb <dbname> [dbuser] [dbpassword] [dbhost]"
	echo "    $0 importdb <dbname> [dbuser] [dbpassword] [dbhost]"
	echo "    $0 adduser <dbname> <new_user> <new_user_password> [dbuser] [dbpassword] [dbhost]"
    echo "    $0 dropdb <dbname> [dbuser] [dbpassword] [dbhost]"
	exit 1
}

function build_horizon
{
    echo "Horizon build initiated, preparing build directory..."
    cmake -B "$PWD/build" $@ || aborterror "Horizon Build has failed."
    echo "Initiating Build..."
    cmake -B "$PWD/build" --config Release || aborterror "Horizon Build has failed."
    echo "Build Complete."
}

function aborterror
{
	echo "Horizon: $@"
	exit 1
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
case "$MODE" in
	createdb|importdb|dropdb|test)
		if [ -z "$1" ]; then
			usage
		fi
		DBNAME="$1"
		if [ -n "$2" ]; then
			DBUSER_ARG="--user=$2"
			DBUSER="$2"
		fi
		if [ -n "$3" ]; then
			DBPASS_ARG="--password=$3"
			DBPASS="$3"
		fi
		if [ -n "$4" ]; then
			DBHOST_ARG="--host=$4"
			DBHOST="$4"
		fi
		;;
	adduser)
		if [ -z "$1" ] OR [ -z "$2" ]; then
			usage
		fi
		DBNAME="$1"
		NEWUSER="$2"
		NEWPASS="$3"
		if [ -n "$4" ]; then
			DBUSER_ARG="--user=$4"
			DBUSER="$4"
		fi
		if [ -n "$5" ]; then
			DBPASS_ARG="--password=$5"
			DBPASS="$5"
		fi
		if [ -n "$6" ]; then
			DBHOST_ARG="--host=$6"
			DBHOST="$6"
		fi
		;;
    auth|char|zone|start)
        if [ -z "$1" ]; then
            usage
        fi
        INSTALL_DIRECTORY=$1
esac

SERVERS=(auth char zone)

function check_compile
{
    if [ ! -f ./$1/$2 ]; then
        aborterror "$2 is not compiled... aborting."
    fi
}

function start_server
{
    exe=$1
    name=$2
    dir=$3
    args_str="$4 $5 $6 $7 $8 $9"
    ###########
    # Start Server
    ###########
    check_compile ${dir} ${exe}
    serv="${exe} ${args_str}"
    cd $dir
    exec ./${serv}
    echo "${name} Server has started."
    cd ..
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
    inter)
        start_server $MODE "Inter" $@
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
		mysql $DBUSER_ARG $DBPASS_ARG $DBHOST_ARG --execute="CREATE DATABASE $DBNAME;" || aborterror "Unable to create database."
		;;
	importdb)
        console_log "Importing Horizon MySQL Tables into $DBNAME as $DBUSER..."
		mysql $DBUSER_ARG $DBPASS_ARG $DBHOST_ARG --database=$DBNAME < sql-files/horizon.sql || aborterror "Unable to import horizon database."
		;;
	adduser)
		console_log "Adding user $NEWUSER as $DBUSER, with access to database $DBNAME..."
		mysql $DBUSER_ARG $DBPASS_ARG $DBHOST_ARG --execute="GRANT SELECT, INSERT, UPDATE, DELETE ON $DBNAME.* TO '$NEWUSER'@'$DBHOST' IDENTIFIED BY '$NEWPASS';"
		;;
	build)
	    build_horizon $@
	    ;;
	*)
	usage
	;;
esac
