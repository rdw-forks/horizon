# Set build-directive (used in core to tell which buildtype we used)
add_definitions(-D_BUILD_DIRECTIVE='"${CMAKE_BUILD_TYPE}"')

set (CLANG_EXPECTED_VERSION 3.4.0)

if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS CLANG_EXPECTED_VERSION)
	message(FATAL_ERROR "Clang: Horizon requires version ${CLANG_EXPECTED_VERSION} to build but found ${CMAKE_CXX_COMPILER_VERSION}")
endif()

if(WITH_WARNINGS)
  set(WARNING_FLAGS "-W -Wall -Wextra -Winit-self -Wfatal-errors -Wno-mismatched-tags")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${WARNING_FLAGS}")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${WARNING_FLAGS} -Woverloaded-virtual")
  message(STATUS "Clang: All warnings enabled")
endif()

if(WITH_CORE_DEBUG)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g3")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g3")
  message(STATUS "Clang: Debug-flags set (-g3)")
endif()

if (WITH_COVERAGE)
	set(COVERAGE_FLAGS "-fprofile-arcs -ftest-coverage")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${COVERAGE_FLAGS}")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COVERAGE_FLAGS}")
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${COVERAGE_FLAGS}")
	message(STATUS "Clang: Coverage flags set (${COVERAGE_FLAGS})")
endif()

set(SANITIZERS "")
if (WITH_TSAN)
	if (WITH_ASAN OR WITH_LSAN)
		message(WARNING "GCC: Thread Sanitizer cannot be used with Address and Leak sanitizers.")
	endif()
	set(SANITIZERS "${SANITIZERS} -fsanitize=thread")
elseif (WITH_ASAN)
	set(SANITIZERS "${SANITIZERS} -fsanitize=address")
elseif (WITH_LSAN)
	set(SANITIZERS "${SANITIZERS} -fsanitize=leak")
elseif (WITH_ESAN)
	set(SANITIZERS "${SANITIZERS} -fsanitize=efficiency-cache-frag,efficiency-working-set")
endif()

if (SANITIZERS)
	message(STATUS "Clang: Sanitization enabled (${SANITIZERS} ).")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${SANITIZERS}")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SANITIZERS}")
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${SANITIZERS}")
endif()
