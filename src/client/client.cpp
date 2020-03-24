//client
#include "linuxClient.hpp"
#include <iostream>
#include <string>
#include <stdio.h>

int main(int argc, char *argv[])
{
	if(argc != 3)
    {
        std::cerr << "Usage: ip_address port" << std::endl;
        exit(0);
    }

    char *serverIp = argv[1]; 
    int port = atoi(argv[2]); 

	Client client(port, serverIp);

	printf("client created \n");

	int clientSd = client.Connect();

	if (clientSd == -1) return -1;

	printf("client connected\n");


    int bytesRead, bytesWritten = 0;

    struct timeval start1, end1;

    gettimeofday(&start1, NULL);

    char msg[msgSize]; 

    while(1)
    {
        if (!client.connected(clientSd)) break;

        std::cout << ">";

        std::string data = client.msgToSend();
        
        memset(&msg, 0, sizeof(msg));
        strcpy(msg, data.c_str());

        if(data == "exit")
        {
            send(clientSd, (char*)&msg, strlen(msg), 0);
            break;
        }

        bytesWritten += send(clientSd, (char*)&msg, strlen(msg), 0);
        std::cout << "Message Sent:" << msg <<"\nAwaiting server response..." << std::endl;

        memset(&msg, 0, sizeof(msg));

        bytesRead += recv(clientSd, (char*)&msg, sizeof(msg), 0);

        if(!strcmp(msg, "exit"))
        {
            std::cout << "Server has quit the session" << std::endl;
            break;
        }

        std::cout << "Server: " << msg << std::endl;
    }

    gettimeofday(&end1, NULL);

	close(clientSd);
	std::cout << "********Session********" << std::endl;
    std::cout << "Bytes written: " << bytesWritten << 
    " Bytes read: " << bytesRead << std::endl;
    std::cout << "Elapsed time: " << (end1.tv_sec- start1.tv_sec) 
      << " secs" << std::endl;
    std::cout << "Connection closed" << std::endl;

	std::cout<< "Session ended\n" << std::endl;
    return 0;    
}
