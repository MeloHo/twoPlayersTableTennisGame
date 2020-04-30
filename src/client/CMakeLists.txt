find_package(Protobuf REQUIRED)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

add_executable(lclient MACOSX_BUNDLE client.cpp linuxClient.cpp linuxClient.hpp player.h player.cpp table.h table.cpp ball.h ball.cpp pngRenderer.h pngRenderer.cpp)

target_include_directories(lclient
	PUBLIC
	${PROTOBUF_INCLUDE_DIRS}
	${CMAKE_CURRENT_BINARY_DIR}
)

message("dir:" ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(lclient fssimplewindow ysclass ysbitmap ysbitmapfont msg ${PROTOBUF_LIBRARIES})


#add_executable(winClient winClient.cpp)
#add_executable(unixClient unixClient.cpp)
