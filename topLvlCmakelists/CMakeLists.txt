cmake_minimum_required(VERSION 3.5)

project(TableTennisGame)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if("${CMAKE_SYSTEM_NAME}" STREQUAL "WindowsStore")
	message(FATAL_ERROR "This framework not supported for UWP")
elseif(MSVC)
	set(CMAKE_PREFIX_PATH
	"C:/Program Files (x86)/protobuf"
	"${CMAKE_PREFIX_PATH}"
	)
	set(Protobuf_USE_STATIC_LIBS ON)
	find_package(Protobuf CONFIG REQUIRED)
	include_directories(${PROTOBUF_DIRECTORIES})
	IF (${Protobuf_FOUND})
		include_directories(${PROTOBUF_LIBRARIES})
	ELSE (${Protobuf_FOUND})
		message(STATUS "Could not locate protobuf.")
	ENDIF (${Protobuf_FOUND})
else()
	set(CMAKE_C_COMPILER "/Library/Developer/CommandLineTools/usr/bin/clang")
	set(CMAKE_CXX_COMPILER "/Library/Developer/CommandLineTools/usr/bin/clang++")
	include_directories(/usr/local/include)
	include_directories(/usr/local/lib)
	IF (${Protobuf_FOUND})
		message(STATUS "protobuf version: " ${Protobuf_VERSION}) 
		message(STATUS "protobuf path: " ${PROTOBUF_INCLUDE_DIR}) 
	ELSE (${Protobuf_FOUND})
		MESSAGE(STATUS "Could not locate Protobuf.")
	ENDIF (${Protobuf_FOUND})
	find_package(Protobuf REQUIRED)
endif()


#set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)


#############################
#Build Executable
#############################

add_subdirectory(public/src)
add_subdirectory(twoPlayersTableTennisGame/src/msg)
add_subdirectory(twoPlayersTableTennisGame/src/client)
add_subdirectory(twoPlayersTableTennisGame/src/server)
add_subdirectory(twoPlayersTableTennisGame/utils)
