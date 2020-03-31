# twoPlayersTableTennisGame

This is a team project for 24783-Advanced Engineering Computation, Spring 2020

# Install Boost
Ubuntu:

	sudo apt install libboost-dev
	sudo apt install libboost-all-dev
	dpkg -s libboost-dev | grep Version

# Install Protobuf
	sudo apt-get install autoconf automake libtool curl make g++ unzip

# Compile with protobuf
	protoc --cpp_out=. msg.proto
	c++ my_program.cc my_proto.pb.cc `pkg-config --cflags --libs protobuf`


# Build
	mkdir build
	cd build
	cmake ../
	make all

executables are in the bin folder
