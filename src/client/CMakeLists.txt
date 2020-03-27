add_executable(lclient MACOSX_BUNDLE client.cpp linuxClient.cpp linuxClient.hpp)

target_link_libraries(lclient fssimplewindow)
#add_executable(winClient winClient.cpp)
#add_executable(unixClient unixClient.cpp)