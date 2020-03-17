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
using namespace std;

Client::Client(int p, char * ip)
{
	this->port = p;
	this->serverIp = ip;
}

string Client::msgToSend()
{
    string data;
    getline(cin, data);
    return data;
}

//decode message
string Client::msgReceived()
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
	char msg[msgSize]; 

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
        cout<<"Error connecting to socket!"<<endl;
        return -1;
    }
    cout << "Connected to the server!" << endl;

    int bytesRead, bytesWritten = 0;

    struct timeval start1, end1;
    gettimeofday(&start1, NULL);

    while(1)
    {
        if (!connected(clientSd)) break;

        cout << ">";
        string data = msgToSend();
        
        memset(&msg, 0, sizeof(msg));
        strcpy(msg, data.c_str());

        if(data == "exit")
        {
            send(clientSd, (char*)&msg, strlen(msg), 0);
            break;
        }

        bytesWritten += send(clientSd, (char*)&msg, strlen(msg), 0);
        cout << "Message Sent:" << msg <<"\nAwaiting server response..." << endl;

        memset(&msg, 0, sizeof(msg));

        bytesRead += recv(clientSd, (char*)&msg, sizeof(msg), 0);

        if(!strcmp(msg, "exit"))
        {
            cout << "Server has quit the session" << endl;
            break;
        }

        cout << "Server: " << msg << endl;
    }

    gettimeofday(&end1, NULL);
    close(clientSd);
    cout << "********Session********" << endl;
    cout << "Bytes written: " << bytesWritten << 
    " Bytes read: " << bytesRead << endl;
    cout << "Elapsed time: " << (end1.tv_sec- start1.tv_sec) 
      << " secs" << endl;
    cout << "Connection closed" << endl;
    return 0;    
}