#include "winClient.hpp"
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#include <stdio.h>
#include <windows.h>

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "libprotobuf.lib")

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

bool Client::connected(SOCKET sock)
{
    char buffer[2*msgSize];
    if (recv(sock, buffer, sizeof(buffer), 0) == SOCKET_ERROR)
        return false; // disconnected
    else
        return true;
}

SOCKET Client::Connect()
{
    WSAData wsa_data;
    struct addrinfo *result = NULL, *ptr = NULL, hints;

    std::cout << "Starting Client...\n";

    // Initialize Winsock
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsa_data);
    if (iResult != 0) {
        std::cout << "WSAStartup() failed with error: " << iResult << std::endl;
        return 1;
    }
 
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
 
    std::cout << "Connecting...\n";

    // Resolve the server address and port
    iResult = getaddrinfo(static_cast<LPCTSTR>(serverIp), std::to_string(this->port).c_str(), &hints, &result);
    if (iResult != 0) {
        std::cout << "getaddrinfo() failed with error: " << iResult << std::endl;
        WSACleanup();
        system("pause");
        return 1;
    }

    // Create a SOCKET for connecting to server
    SOCKET clientSd = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
    if (clientSd == INVALID_SOCKET) {
        std::cout << "socket() failed with error: " << WSAGetLastError() << std::endl;
        WSACleanup();
        system("pause");
        return 1;
    }

    // Connect to server.
    iResult = connect(clientSd, ptr->ai_addr, (int)ptr->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        closesocket(clientSd);
        clientSd = INVALID_SOCKET;
        return 1;
    }

    freeaddrinfo(result);
    
    if (clientSd == INVALID_SOCKET) {
        std::cout << "Unable to connect to server!" << std::endl;
        WSACleanup();
        system("pause");
        return 1;
    }
 
    std::cout << "Successfully Connected to the server!" << std::endl;

    return clientSd;
}

int Client::CloseConnection(SOCKET clientSd)
{
    closesocket(clientSd);
    WSACleanup();
    system("pause");
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