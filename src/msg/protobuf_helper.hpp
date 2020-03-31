#ifndef PROTOBUF_HELPER
#define PROTOBUF_HELPER


class Protobuf_helper
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