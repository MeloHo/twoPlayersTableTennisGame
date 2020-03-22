#include "linuxClient.hpp"
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

Client::Client(int p, char * ip)
{
	this->port = p;
	this->serverIp = ip;
}

std::string Client::msgToSend()
{
    std::string data;
    getline(std::cin, data);
    return data;
}

//decode message
std::string Client::msgReceived()
{
    return "s";
}

bool Client::connected(int sock)
{
    char buffer[2*msgSize];
    if (recv(sock, buffer, sizeof(buffer), MSG_PEEK | MSG_DONTWAIT) == 0)
        return false;
    else
        return true;
}

int Client::Connect()
{
    struct hostent* host = gethostbyname(serverIp); 
    sockaddr_in sendSockAddr;   
    bzero((char*)&sendSockAddr, sizeof(sendSockAddr)); 
    sendSockAddr.sin_family = AF_INET; 
    sendSockAddr.sin_addr.s_addr = inet_addr(inet_ntoa(*(struct in_addr*)*host->h_addr_list));
    sendSockAddr.sin_port = htons(port);

    int clientSd = socket(AF_INET, SOCK_STREAM, 0);

    int status = connect(clientSd, (sockaddr*) &sendSockAddr, sizeof(sendSockAddr));

    if(status < 0)
    {
        std::cout<<"Error connecting to server!"<< std::endl;
        return -1;
    }
    std::cout << "Connected to the server!" << std::endl;

    return clientSd;
}

int Client::CloseConnection(int clientSd)
{
    close(clientSd);

    return 0;
}

std::string Client::getState()
{
    return "";
}

std::string Client::encode()
{
    return "1";
}