#include "linuxServer.hpp"
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
using namespace std;

Server::Server(int p)
{
	this->port = p;
}

string Server::msgToSend(char msg1[], char msg2[])
{
    string s_msg1 = string(msg1);
    string s_msg2 = string(msg2);
    string ret = s_msg1+s_msg2;
    cout << ret.size() << endl;
    return ret;
}

string Server::msgReceived()
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

int Server::StartServer()
{
    //buffer to send and receive messages with
    char msg1[msgSize];
    char msg2[msgSize];
     
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
        std::cerr << "Error establishing the server socket" << endl;
        exit(0);
    }
    //bind the socket to its local address
    int bindStatus = ::bind(serverSd, (struct sockaddr*) &servAddr, sizeof(servAddr));
    if(bindStatus < 0)
    {
        std::cerr << "Error binding socket to local address" << endl;
        exit(0);
    }

    cout << "Waiting for a client to connect..." << endl;
    //listen for up to 5 requests at a time
    int listenStatus = listen(serverSd, 5);
    if (listenStatus < 0)
    {
        cerr << "Error listening to server" << endl;
    }

    //connect to client1 
    sockaddr_in newSockAddr1;
    socklen_t newSockAddrSize1 = sizeof(newSockAddr1);
    int newSd1 = accept(serverSd, (sockaddr *)&newSockAddr1, &newSockAddrSize1);
    if(newSd1 < 0)
    {
        cerr << "Error accepting request from client 1!" << endl;
        exit(1);
    }
    cout << "Connected with client 1!" << endl;

    //connext to client 2
    sockaddr_in newSockAddr2;
    socklen_t newSockAddrSize2 = sizeof(newSockAddr2);
    int newSd2 = accept(serverSd, (sockaddr *)&newSockAddr2, &newSockAddrSize2);
    if(newSd2 < 0)
    {
        cerr << "Error accepting request from client 2!" << endl;
        exit(1);
    }
    cout << "Connected with client 2!" << endl;

    struct timeval start1, end1;
    gettimeofday(&start1, NULL);
    int bytesRead, bytesWritten = 0;

    while(1)
    {
        if (!connected(newSd1) || !connected(newSd2)) break;
        cout << "Awaiting client1 response..." << endl;
        memset(&msg1, 0, sizeof(msg1));
        bytesRead += recv(newSd1, (char*)&msg1, sizeof(msg1), 0);
        if(!strcmp(msg1, "exit"))
        {
            cout << "Client1 has quit the session" << endl;
            break;
        }
        cout << "Client1: " << msg1 << endl;

        cout << "Awaiting client2 response..." << endl;
        memset(&msg2, 0, sizeof(msg2));
        bytesRead += recv(newSd2, (char*)&msg2, sizeof(msg2), 0);
        if(!strcmp(msg2, "exit"))
        {
            cout << "Client1 has quit the session" << endl;
            break;
        }
        cout << "Client2: " << msg2 << endl;

        cout << ">";
        string data = msgToSend(msg1, msg2);
        memset(&msg1, 0, sizeof(msg1)); 
        strcpy(msg1, data.c_str());
        cout << "Message Sent:" << data << endl;
        bytesWritten += send(newSd1, (char*)&msg1, strlen(msg1), 0);
        bytesWritten += send(newSd2, (char*)&msg1, strlen(msg1), 0);
    }
    
    gettimeofday(&end1, NULL);
    close(newSd1);
    close(newSd2);
    close(serverSd);
    cout << "********Session********" << endl;
    cout << "Bytes written: " << bytesWritten << " Bytes read: " << bytesRead << endl;
    cout << "Elapsed time: " << (end1.tv_sec - start1.tv_sec) 
        << " secs" << endl;
    cout << "Connection closed..." << endl;
    return 0;   
}