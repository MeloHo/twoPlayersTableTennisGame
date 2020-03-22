//client

#include "linuxClient.hpp"
#include <iostream>
#include <string>
#include <stdio.h>
using namespace std;

int main(int argc, char *argv[])
{
	if(argc != 3)
    {
        cerr << "Usage: ip_address port" << endl;
        exit(0);
    }

    char *serverIp = argv[1]; 
    int port = atoi(argv[2]); 

	Client client(port, serverIp);

	printf("client created \n");

	int ret = client.Connect();

	printf("session end\n");

	return 0;
}
