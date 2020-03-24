#ifndef LINUXSERVER_H
#define LINUXSERVER_H

#define msgSize 50
#include <iostream>
#include <string>
#include <stdio.h>

class Server
{
private:
	int port;

public:
	int client1Sd;
	int client2Sd;

	Server(int p);
	int StartServer();
	std::string msgToSend(char msg1[], char msg2[]);
	std::string msgReceived();
	bool connected(int sock);
	void decode(); 
};

#endif