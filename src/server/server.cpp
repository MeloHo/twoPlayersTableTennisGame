//server
#include "linuxServer.hpp"
#include <iostream>
#include <string>
#include <stdio.h>

void updateMessage(const char* msg1, const char* msg2, std::string& msg1_reply, std::string& msg2_reply)
{
    
}


int main(int argc, char *argv[])
{
    // Create Server 
	if(argc != 2)
    {
        std::cerr << "Usage: port" << std::endl;
        exit(0);
    }

    int port = atoi(argv[1]);

	Server server(port);

	printf("server created \n");

	int serverSd = server.StartServer();

	printf("server connected to clients\n");

    //buffer to send and receive messages with
    char msg1[msgSize];
    char msg2[msgSize];

    while(1)
    {
        if (!server.connected(server.client1Sd) || !server.connected(server.client2Sd)) break;
        std::cout << "Awaiting client1 response..." << std::endl;
        memset(&msg1, 0, sizeof(msg1));
        recv(server.client1Sd, (char*)&msg1, sizeof(msg1), 0);
        if(!strcmp(msg1, "exit"))
        {
            std::cout << "Client1 has quit the session" << std::endl;
            break;
        }
        std::cout << "Client1: " << msg1 << std::endl;

        std::cout << "Awaiting client2 response..." << std::endl;
        memset(&msg2, 0, sizeof(msg2));
        recv(server.client2Sd, (char*)&msg2, sizeof(msg2), 0);
        if(!strcmp(msg2, "exit"))
        {
            std::cout << "Client2 has quit the session" << std::endl;
            break;
        }
        std::cout << "Client2: " << msg2 << std::endl;

        std::string msg1_reply;
        std::string msg2_reply;

        updateMessage(msg1, msg2, msg1_reply, msg2_reply);

        send(server.client1Sd, (char*)msg1_reply.c_str(), strlen(msg1_reply.c_str()), 0);
        send(server.client2Sd, (char*)msg2_reply.c_str(), strlen(msg1_reply.c_str()), 0);
        
    }

    close(serverSd);

	printf("session ended\n");
	
	return 0;
}

