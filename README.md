# twoPlayersTableTennisGame

This is a team project for 24783-Advanced Engineering Computation, Spring 2020

![alt text](https://github.com/MeloHo/twoPlayersTableTennisGame/tree/master/images/Overview.png)

We use [Proto Buffers by Google](https://developers.google.com/protocol-buffers) and Socket for network programming. Best tutorial is [here](https://beej.us/guide/bgnet/html/#client-server-background). 

# Dependencies

## Protobuf

To install Protobuf

### On Ubuntu

```
sudo apt-get install autoconf automake libtool curl make g++ unzip
```

### On Mac
1. Build from source
```
sudo mv ~/Downloads/protobuf-3.6.1 /usr/local/bin
	cd /usr/local/bin/protobuf-3.6.1
	./configure CC=clang CXX="clang++ -std=c++11 -stdlib=libc++" CXXFLAGS="-O3" --disable-shared
	make
	sudo make install
	protoc --version
```

2. Use homebrew:

	brew install protobuf

or from source:
	
	sudo mv ~/Downloads/protobuf-3.6.1 /usr/local/bin
	cd /usr/local/bin/protobuf-3.6.1
	./configure CC=clang CXX="clang++ -std=c++11 -stdlib=libc++" CXXFLAGS="-O3" --disable-shared
	make
	sudo make install
	protoc --version

## OpenGL Graphics.
From [Soji](https://github.com/captainys/public). 

# Build
	mkdir build
	cd build
	cmake ../
	make all


executables are in the bin folder under src

# Run
Run a server and two clients. For example, if using a port number 8899 and run it under local loopback.

for server: ./lserver.app/Contents/MacOS/lserver 8899

for client1: ./lclient.app/Contents/MacOS/lclient 127.0.0.1 8899

for client2: ./lclient.app/Contents/MacOS/lclient 127.0.0.1 8899
