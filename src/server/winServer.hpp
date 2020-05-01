#ifndef WINSERVER_H
#define WINSERVER_H

#define msgSize 50
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <fstream>

#define IP_ADDRESS "127.0.0.1"

class Server
{
private:
	int port;

public:
	SOCKET client1Sd;
	SOCKET client2Sd;

	Server(int p);
	SOCKET StartServer();
	std::string msgToSend(char msg1[], char msg2[]);
	std::string msgReceived();
	bool connected(SOCKET sock);
	void decode(); 
};

#endif