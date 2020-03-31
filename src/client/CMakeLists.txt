add_executable(lclient MACOSX_BUNDLE client.cpp linuxClient.cpp linuxClient.hpp player.h player.cpp table.h table.cpp)

target_link_libraries(lclient fssimplewindow ysclass)
#add_executable(winClient winClient.cpp)
#add_executable(unixClient unixClient.cpp)
