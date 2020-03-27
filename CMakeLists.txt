project(TableTennisGame)

set(CMAKE_CXX_STANDARD 11)
cmake_minimum_required(VERSION 3.5)

#set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

#############################
#Dependencies
#############################

#find_package(Eigen3 REQUIRED)

#include_directories(${EIGEN3_INCLUDE_DIR})

#############################
#Build Executable
#############################

add_executable(lclient src/client/client.cpp src/client/linuxClient.cpp src/client/linuxClient.hpp)
add_executable(lserver src/server/server.cpp src/server/linuxServer.hpp src/server/linuxServer.cpp)