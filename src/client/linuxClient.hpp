#ifndef LINUXCLIENT_H
#define LINUXCLIENT_H

#define msgSize 50
#include <string>

class Client
{
private:
	int port;
	char *serverIp;

public:
	Client(int p, char * ip);
	int Connect();
	string msgToSend();
	string msgReceived();
	bool connected(int sock);
}

#endif