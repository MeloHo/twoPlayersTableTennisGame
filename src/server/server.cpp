//server
#include "linuxServer.hpp"
#include <iostream>
#include <string>
#include <stdio.h>

int main(int argc, char *argv[])
{
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


    struct timeval start1, end1;
    gettimeofday(&start1, NULL);
    int bytesRead, bytesWritten = 0;

    //buffer to send and receive messages with
    char msg1[msgSize];
    char msg2[msgSize];

    while(1)
    {
        if (!server.connected(server.client1Sd) || !server.connected(server.client1Sd)) break;
        std::cout << "Awaiting client1 response..." << std::endl;
        memset(&msg1, 0, sizeof(msg1));
        bytesRead += recv(server.client1Sd, (char*)&msg1, sizeof(msg1), 0);
        if(!strcmp(msg1, "exit"))
        {
            std::cout << "Client1 has quit the session" << std::endl;
            break;
        }
        std::cout << "Client1: " << msg1 << std::endl;

        std::cout << "Awaiting client2 response..." << std::endl;
        memset(&msg2, 0, sizeof(msg2));
        bytesRead += recv(server.client2Sd, (char*)&msg2, sizeof(msg2), 0);
        if(!strcmp(msg2, "exit"))
        {
            std::cout << "Client2 has quit the session" << std::endl;
            break;
        }
        std::cout << "Client2: " << msg2 << std::endl;

        std::cout << ">";
        std::string data = server.msgToSend(msg1, msg2);
        memset(&msg1, 0, sizeof(msg1)); 

        strcpy(msg1, data.c_str());
        std::cout << "Message Sent:" << data << std::endl;
        bytesWritten += send(server.client1Sd, (char*)&msg1, strlen(msg1), 0);
        bytesWritten += send(server.client2Sd, (char*)&msg1, strlen(msg1), 0);
    }
    
    gettimeofday(&end1, NULL);
    close(server.client1Sd);
    close(server.client2Sd);


    close(serverSd);
    std::cout << "********Session********" << std::endl;
    std::cout << "Bytes written: " << bytesWritten << " Bytes read: " << bytesRead << std::endl;
    std::cout << "Elapsed time: " << (end1.tv_sec - start1.tv_sec) 
        << " secs" << std::endl;
    std::cout << "Connection closed..." << std::endl;   

	printf("session ended\n");
	
	return 0;
}

