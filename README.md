

# The Horizon Project
Horizon is a free software project (authored by [@sagunkho](https://gitlab.com/sagunkho) aka [@Smokexyz](https://gitlab.com/Smokexyz)), a Massively Multiplayer Online Role-Playing Game (MMORPG) server package. Certain static database files and client packet information were converted from [HerculesWS](https://github.com/HerculesWS/Hercules) into a suitable format for our project.

Table of Contents
---------
1. What is Horizon?
2. Prerequisites
3. Installation
4. Troubleshooting

Prerequisites
-------------
Before installing Horizon, you will need to install certain tools and applications.

#### Supported Operating Systems
- Linux
- Unix / MacOS
- Windows

#### Pre-requisites
  - git
  - g++ or clang (version 4.5 or newer, recommended 5.0 or newer)
  - [CMake 3.7+](https://cmake.org/)
  - [Boost v1.60+](https://www.boost.org/)
  - [Readline](https://tiswww.case.edu/php/chet/readline/rltop.html)
  - [Sol2](https://github.com/ThePhD/sol2)
  - [Argon2](https://github.com/P-H-C/phc-winner-argon2)
  - [SQLPP11](https://github.com/rbock/sqlpp11) 
  - [SQLPP11-MYSQL](https://github.com/rbock/sqlpp11-connector-mysql)

#### Optional, useful tools
  - MySQL GUI clients
    - [MySQL Workbench](http://www.mysql.com/downloads/workbench/) (cross-platform)
    - [HeidiSQL](http://www.heidisql.com/) (Windows)
    - [Sequel Pro](http://www.sequelpro.com/) (Mac OS X)
  - GUI Git clients
    - [Atlassian SourceTree](https://www.sourcetreeapp.com/) (Windows, Mac OS X)
    - [TortoiseGit](https://tortoisegit.org/) (Windows)

#### Install on Windows
1. `vcpkg install cmake:x64-windows readline:x64-windows sqlpp11:x64-windows lua:x64-windows zlib:x64-windows sol2:x64-windows mysql:x64-windows`
2. `vcpkg install boost-log:x64-windows boost-filesystem:x64-windows boost-system:x64-windows boost-test:x64-windows boost-locale:x64-windows boost-crc:x64-windows boost-multi-array:x64-windows`
3. `git clone https://github.com/horizonxyz/horizon.git horizon`
4. `cd horizon; mkdir build; cd build;`
5. `cmake .. -DCMAKE_TOOLCHAIN_FILE="C:/vcpkg/scripts/buildsystems/vcpkg.cmake" -DVCPKG_TARGET_TRIPLET=x64-windows -DWITH_SOURCE_TREE=hierarchical-folders -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=<path-to-installation-dir>"`
