//server
#include "linuxServer.hpp"
#include <iostream>
#include <string>
#include <stdio.h>
using namespace std;

int main(int argc, char *argv[])
{
	if(argc != 2)
    {
        cerr << "Usage: port" << endl;
        exit(0);
    }

    int port = atoi(argv[1]);

	Server server(port);

	printf("server created \n");

	int ret = server.StartServer();

	printf("session ended\n");
	return 0;
}