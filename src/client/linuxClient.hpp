#ifndef LINUXCLIENT_H
#define LINUXCLIENT_H

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