# twoPlayersTableTennisGame

This is a team project for 24783-Advanced Engineering Computation, Spring 2020

# Install Protobuf
## Ubuntu:

	sudo apt-get install autoconf automake libtool curl make g++ unzip

## Mac:

Homebrew:

	brew install protobuf

or from source:
	
	sudo mv ~/Downloads/protobuf-3.6.1 /usr/local/bin
	cd /usr/local/bin/protobuf-3.6.1
	./configure CC=clang CXX="clang++ -std=c++11 -stdlib=libc++" CXXFLAGS="-O3" --disable-shared
	make
	sudo make install
	protoc --version

# Build
	mkdir build
	cd build
	cmake ../
	make all

executables are in the bin folder under src
