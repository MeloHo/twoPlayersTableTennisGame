#ifndef LINUXSERVER_H
#define LINUXSERVER_H

#define msgSize 50
#include <string>

class Server
{
private:
	int port;

public:
	Server(int p);
	int StartServer();
	string msgToSend(char msg1[], char msg2[]);
	string msgReceived();
	bool connected(int sock);
}

#endif