#include "winServer.hpp"
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#include <stdio.h>
#include <windows.h>

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "libprotobuf.lib")

const char OPTION_VALUE = 1;

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

bool Server::connected(SOCKET sock)
{
    char buffer[2*msgSize];
    if (recv(sock, buffer, sizeof(buffer), 0) == SOCKET_ERROR)
        return false; // disconnected
    else
        return true;
}

SOCKET Server::StartServer()
{

    WSADATA wsaData;
    struct addrinfo hints;
    struct addrinfo *server = NULL;
    SOCKET server_socket = INVALID_SOCKET;

    //Initialize Winsock
    std::cout << "Intializing Winsock..." << std::endl;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    //Setup hints
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    //Setup Server
    std::cout << "Setting up server..." << std::endl;
    getaddrinfo(static_cast<LPCTSTR>(IP_ADDRESS), std::to_string(this->port).c_str(), &hints, &server);

    //Create a listening socket for connecting to server
    std::cout << "Creating server socket..." << std::endl;
    server_socket = socket(server->ai_family, server->ai_socktype, server->ai_protocol);

    //Setup socket options
    //setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &OPTION_VALUE, sizeof(int)); //Make it possible to re-bind to a port that was used within the last 2 minutes
    setsockopt(server_socket, IPPROTO_TCP, TCP_NODELAY, &OPTION_VALUE, sizeof(int)); //Used for interactive programs

    //Assign an address to the server socket.
    std::cout << "Binding socket..." << std::endl;
    bind(server_socket, server->ai_addr, (int)server->ai_addrlen);
 
     //Listen for incoming connections.
    std::cout << "Listening..." << std::endl;
    listen(server_socket, SOMAXCONN);

    // connect to client1
    this->client1Sd = accept(server_socket, NULL, NULL);
    if (this->client1Sd == INVALID_SOCKET)
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
    Sleep(1000);

    // connect to client2
    this->client2Sd = accept(server_socket, NULL, NULL);
    if (this->client2Sd == INVALID_SOCKET)
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
    Sleep(1000);

    return server_socket;
}