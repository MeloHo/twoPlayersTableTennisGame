project(TableTennisGame)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

cmake_minimum_required(VERSION 3.5)


#############################
#Dependencies
#############################

#find_package(Eigen3 REQUIRED)

#include_directories(${EIGEN3_INCLUDE_DIR})

#############################
#Build Executable
#############################

add_subdirectory(public/src)
add_subdirectory(src/client)
add_subdirectory(src/server)
add_subdirectory(utils)