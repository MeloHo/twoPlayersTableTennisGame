cmake_minimum_required(VERSION 3.1)

if($(CMAKE_VERSION) VERSION_LESS 3.15)
	cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
else()
	cmake_policy(VERSION 3.15)
endif()

project(TennisGame VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# add subdirectory here

add_subdirectory(src/server) # All source files goes into src
add_subdirectory(src/client)


add_subdirectory(utils) # All external libs goes here