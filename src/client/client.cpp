//client
#include "linuxClient.hpp"
#include <iostream>
#include <string>
#include <stdio.h>

#include "ball.h"
#include "player.h"
#include "table.h"
#include "fssimplewindow.h" // For graphics

std::string encodeMessage(const bool& isStarter, const bool& isHiting, const Ball& ball, const Player& player)
{

}

void updateStates(const char* msg, bool& isStarter, Ball& ball, Player& component)
{

}

int main(int argc, char *argv[])
{
    Ball ball;
    Player player;
    Player opponent;
    Table table;

    bool isStarter = true;
    bool terminate = false;

    // Connect to the server
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

    char msg[msgSize];

    while(!terminate) {
        // Get mouse event
        int key = FsInkey();
        int leftButton, middleButton, rightButton, locX, locY;
        int mouseEvent = FsGetMouseEvent(leftButton, middleButton, rightButton, locX, locY);

        bool isHiting = false;

        if (key == FSKEY_ESC) {
            terminate = true;
        }

        if(isStarter) {
            player.update(locX, locY);
            ball.update(locX, locY);
            if(mouseEvent == FSMOUSEEVENT_LBUTTONDOWN) {
                float vx = 0.0;
                float vy = 1.0;
                float vz = 0.0;
                ball.update(vx, vy, vz);

                isStarter = false;
            }
        }
        else{
            player.update(locX, locY);
            if(mouseEvent == FSMOUSEEVENT_LBUTTONDOWN) {
                isHiting = true;
            }
        }
        // Encode the message here
        std::stirng message = encodeMessage(isStarter, isHiting, ball, player);


        // ----------------------------------------------------------------------
        // Send the message to the server and receive the message from the server
        if (!client.connected(clientSd)){
            std::cout << "Connection Lost." << std::endl;
            break;
        }
        // Send
        memset(&msg, 0, sizeof(msg));
        strcpy(msg, message.c_str());

        // Receive
        std::cout << "Message Sent:" << msg <<"\nAwaiting server response..." << std::endl;
        memset(&msg, 0, sizeof(msg));

        // ----------------------------------------------------------------------

        updateStates(msg, isStarter, ball, opponent);

        // Draw
        

        ball.draw();
        player.draw();
        opponent.draw();
        table.draw();

        // Reset
        isHiting = false;

    }
    close(clientSd);
    std::cout << "End of Game." << std::endl;  
}
