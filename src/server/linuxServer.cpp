#include "linuxServer.hpp"
#include <iostream>
#include <string>
#include <stdio.h>

Server::Server(int p)
{
    this->port = p;
}

std::string Server::msgToSend(char msg1[], char msg2[])
{
    std::string s_msg1 = std::string(msg1);
    std::string s_msg2 = std::string(msg2);
    std::string ret = s_msg1+s_msg2;
    std::cout << ret.size() << std::endl;
    return ret;
}

std::string Server::msgReceived()
{
    return "s";
}

bool Server::connected(int sock)
{
    char buffer[2*msgSize];
    if (recv(sock, buffer, sizeof(buffer), MSG_PEEK | MSG_DONTWAIT) == 0)
        return false;
    else
        return true;
}

void decode(){
    return;
}

int Server::StartServer()
{
    //setup a socket and connection tools
    sockaddr_in servAddr;
    bzero((char*)&servAddr, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(this->port);
 
    //open stream oriented socket with internet address
    //also keep track of the socket descriptor
    int serverSd = socket(AF_INET, SOCK_STREAM, 0);
    if(serverSd < 0)
    {
        std::cerr << "Error establishing the server socket" << std::endl;
        exit(0);
    }
    //bind the socket to its local address
    int bindStatus = ::bind(serverSd, (struct sockaddr*) &servAddr, sizeof(servAddr));
    if(bindStatus < 0)
    {
        std::cerr << "Error binding socket to local address" << std::endl;
        exit(0);
    }

    std::cout << "Waiting for a client to connect..." << std::endl;
    //listen for up to 5 requests at a time
    int listenStatus = listen(serverSd, 5);
    if (listenStatus < 0)
    {
        std::cerr << "Error listening to server" << std::endl;
    }

    //connect to client1 
    sockaddr_in newSockAddr1;
    socklen_t newSockAddrSize1 = sizeof(newSockAddr1);
    this->client1Sd = accept(serverSd, (sockaddr *)&newSockAddr1, &newSockAddrSize1);
    if(this->client1Sd < 0)
    {
        std::cerr << "Error accepting request from client 1!" << std::endl;
        exit(1);
    }
    std::cout << "Connected with client 1!" << std::endl;

    // assign player 1
    char msg[msgSize];
    memset(&msg, 0, sizeof(msg)); 
    msg[0] = '0';
    std::cout << "Player 1 assigned"<< std::endl;
    send(client1Sd, (char*)&msg, sizeof(msg), 0);
    sleep(2);

    //connext to client 2
    sockaddr_in newSockAddr2;
    socklen_t newSockAddrSize2 = sizeof(newSockAddr2);
    this->client2Sd = accept(serverSd, (sockaddr *)&newSockAddr2, &newSockAddrSize2);
    if(this->client2Sd < 0)
    {
        std::cerr << "Error accepting request from client 2!" << std::endl;
        exit(1);
    }
    std::cout << "Connected with client 2!" << std::endl;

    // assign player 2
    memset(&msg, 0, sizeof(msg)); 
    msg[0] = '1';
    std::cout << "Player 2 assigned"<< std::endl;
    send(client2Sd, (char*)&msg, sizeof(msg), 0);
    sleep(2);

    return serverSd;
}