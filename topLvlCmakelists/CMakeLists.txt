cmake_minimum_required(VERSION 3.5)

project(TableTennisGame)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# uncomment if on mac
#set(CMAKE_C_COMPILER "/Library/Developer/CommandLineTools/usr/bin/clang")
#set(CMAKE_CXX_COMPILER "/Library/Developer/CommandLineTools/usr/bin/clang++")

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

#############################
#Dependencies
#############################

find_package(Protobuf REQUIRED)

IF (${Protobuf_FOUND})
	include_directories(~/usr/local/lib)
	message(STATUS "protobuf version: "${Protobuf_VERSION}) 
	message(STATUS "protobuf path: "${PROTOBUF_INCLUDE_DIR}) 
ELSE (${Protobuf_FOUND})
   MESSAGE(STATUS "Could not locate Protobuf.")
ENDIF (${Protobuf_FOUND})

#############################
#Build Executable
#############################

add_subdirectory(public/src)
add_subdirectory(twoPlayersTableTennisGame/src/msg)
add_subdirectory(twoPlayersTableTennisGame/src/client)
add_subdirectory(twoPlayersTableTennisGame/src/server)
add_subdirectory(twoPlayersTableTennisGame/utils)
