#ifndef LINUXCLIENT_H
#define LINUXCLIENT_H

#define msgSize 50
#include <iostream>
#include <string>
#include <stdio.h>

class Client
{
private:
	int port;
	char *serverIp;

public:
	Client(int p, char * ip);
	int Connect();
	std::string msgToSend();
	std::string msgReceived();
	bool connected(int sock);
	int CloseConnection(int clientSd);
	std::string getState();
	std::string encode();

};

#endif