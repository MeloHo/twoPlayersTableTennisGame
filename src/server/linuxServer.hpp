#ifndef LINUXSERVER_H
#define LINUXSERVER_H

#define msgSize 50
#include <iostream>
#include <string>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <sys/uio.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <fstream>

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