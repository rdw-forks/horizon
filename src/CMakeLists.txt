add_subdirectory(Utility)
add_subdirectory(Core)
add_subdirectory(Libraries)

#################
# Horizon Project Servers
#################
if (NOT WITHOUT_SERVERS)
	add_subdirectory(Server)
endif (NOT WITHOUT_SERVERS)

#################
# Horizon Project Tests
#################
if (WITH_TESTS)
	add_subdirectory(Server/Common)
	add_subdirectory(Server/Zone/Packets)
	add_subdirectory(Server/Zone/Game)
	add_subdirectory(Server/Zone/Persistence)
	add_subdirectory(Server/Zone/Script)
	add_subdirectory(Server/Zone/Interface)
	set(ZONE_TESTING_SOURCES
		${CMAKE_SOURCE_DIR}/src/Server/Zone/Zone.hpp
		${CMAKE_SOURCE_DIR}/src/Server/Zone/Zone.cpp
		${CMAKE_SOURCE_DIR}/src/Server/Zone/ZoneRuntime.cpp
		${CMAKE_SOURCE_DIR}/src/Server/Zone/ZoneRuntime.hpp
		${CMAKE_SOURCE_DIR}/src/Server/Zone/ZoneSystem.cpp
		${CMAKE_SOURCE_DIR}/src/Server/Zone/ZoneSystem.hpp
		${CMAKE_SOURCE_DIR}/src/Server/Zone/Interface/ZoneClientInterface.cpp
		${CMAKE_SOURCE_DIR}/src/Server/Zone/Interface/ZoneClientInterface.hpp
		${CMAKE_SOURCE_DIR}/src/Server/Zone/Session/ZoneSession.cpp
		${CMAKE_SOURCE_DIR}/src/Server/Zone/Session/ZoneSession.hpp
		${CMAKE_SOURCE_DIR}/src/Server/Zone/Socket/ZoneSocket.cpp
		${CMAKE_SOURCE_DIR}/src/Server/Zone/Socket/ZoneSocket.hpp
		${CMAKE_SOURCE_DIR}/src/Server/Zone/SocketMgr/ClientSocketMgr.hpp
		${CMAKE_SOURCE_DIR}/src/Server/Zone/SocketMgr/ClientSocketMgr.cpp
	)
	add_subdirectory(Tests)
endif (WITH_TESTS)

#################
# Horizon Project Tools
#################
if (WITH_TOOLS)
    add_subdirectory(Tools)
endif (WITH_TOOLS)