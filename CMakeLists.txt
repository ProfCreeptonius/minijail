cmake_minimum_required(VERSION 3.31)
project(MiniJail)

file(GLOB_RECURSE source CONFIGURE_DEPENDS "./src/*.cpp" "./src/*.hpp")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # For the language server.
set(CMAKE_CXX_STANDARD 23)

if(UNIX)
	set(CMAKE_CXX_FLAGS "-Wall -Wextra")
endif()

add_executable(main ${source})

if(${CMAKE_SYSTEM_NAME} STREQUAL FreeBSD)
  target_link_libraries(main "pthread")
endif()

add_subdirectory(test)
