add_executable(lserver MACOSX_BUNDLE server.cpp linuxServer.hpp linuxServer.cpp)

target_link_libraries(lserver fssimplewindow ysclass proto ${PROTOBUF_LIBRARY})
#add_executable(winServer winServer.cpp)
#add_executable(unixServer unixServer.cpp)
