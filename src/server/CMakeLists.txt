find_package(Protobuf REQUIRED)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

add_executable(lserver MACOSX_BUNDLE server.cpp linuxServer.hpp linuxServer.cpp)


target_link_libraries(lserver fssimplewindow ysclass msg ${PROTOBUF_LIBRARY})
#add_executable(winServer winServer.cpp)
#add_executable(unixServer unixServer.cpp)

target_include_directories(lserver
    PUBLIC
    ${PROTOBUF_INCLUDE_DIRS}
    ${CMAKE_CURRENT_BINARY_DIR}
)


