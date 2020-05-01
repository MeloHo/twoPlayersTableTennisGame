#ifndef WINCLIENT_H
#define WINCLIENT_H

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

class Client
{
private:
	int port;
	char *serverIp;

public:
	Client(int p, char * ip);
	SOCKET Connect();
	std::string msgToSend();
	std::string msgReceived();
	bool connected(SOCKET sock);
	int CloseConnection(SOCKET clientSd);
	std::string getState();
	std::string encode();

};

#endif