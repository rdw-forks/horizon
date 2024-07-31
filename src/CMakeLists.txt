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
	set(AUTH_TESTING_SOURCES
		${CMAKE_SOURCE_DIR}/src/Server/Auth/Auth.hpp
		${CMAKE_SOURCE_DIR}/src/Server/Auth/Auth.cpp
		${CMAKE_SOURCE_DIR}/src/Server/Auth/Interface/AuthClientInterface.cpp
		${CMAKE_SOURCE_DIR}/src/Server/Auth/Interface/AuthClientInterface.hpp
		${CMAKE_SOURCE_DIR}/src/Server/Auth/Session/AuthSession.cpp
		${CMAKE_SOURCE_DIR}/src/Server/Auth/Session/AuthSession.hpp
		${CMAKE_SOURCE_DIR}/src/Server/Auth/Socket/AuthSocket.cpp
		${CMAKE_SOURCE_DIR}/src/Server/Auth/Socket/AuthSocket.hpp
		${CMAKE_SOURCE_DIR}/src/Server/Auth/SocketMgr/ClientSocketMgr.hpp
		${CMAKE_SOURCE_DIR}/src/Server/Auth/SocketMgr/ClientSocketMgr.cpp
	)
	set(CHAR_TESTING_SOURCES
		${CMAKE_SOURCE_DIR}/src/Server/Char/Char.hpp
		${CMAKE_SOURCE_DIR}/src/Server/Char/Char.cpp
		${CMAKE_SOURCE_DIR}/src/Server/Char/Interface/CharClientInterface.cpp
		${CMAKE_SOURCE_DIR}/src/Server/Char/Interface/CharClientInterface.hpp
		${CMAKE_SOURCE_DIR}/src/Server/Char/Session/CharSession.cpp
		${CMAKE_SOURCE_DIR}/src/Server/Char/Session/CharSession.hpp
		${CMAKE_SOURCE_DIR}/src/Server/Char/Socket/CharSocket.cpp
		${CMAKE_SOURCE_DIR}/src/Server/Char/Socket/CharSocket.hpp
		${CMAKE_SOURCE_DIR}/src/Server/Char/SocketMgr/ClientSocketMgr.hpp
		${CMAKE_SOURCE_DIR}/src/Server/Char/SocketMgr/ClientSocketMgr.cpp
	)
	set(ZONE_TESTING_SOURCES
		${CMAKE_SOURCE_DIR}/src/Server/Zone/Zone.hpp
		${CMAKE_SOURCE_DIR}/src/Server/Zone/Zone.cpp
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