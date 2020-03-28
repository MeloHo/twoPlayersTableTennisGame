//client
#include "linuxClient.hpp"
#include <iostream>
#include <string>
#include <stdio.h>

#include "ball.h"
#include "player.h"
#include "table.h"
#include "fssimplewindow.h" // For graphics
#include <ysclass.h>

// std::string encodeMessage(const bool& isStarter, const bool& isHiting, const Ball& ball, const Player& player)
// {
//
// }
//
// void updateStates(const char* msg, bool& isStarter, Ball& ball, Player& component)
// {
//
// }

int main(int argc, char *argv[])
{
    FsOpenWindow(0,0,1200,800,1);
//    Ball ball;
    Player player;
    int wid, hei;
    FsGetWindowSize(wid,hei);
    player.updateWinSize(wid, hei);
//    Player opponent;
//    Table table;

    bool isStarter = true;
    bool terminate = false;

    YsMatrix4x4 Rc;
    double d = 1.0;
    YsVec3 t = YsVec3::Origin() + YsVec3 (7.5, 0.0, 1.0);
    Rc.RotateYZ(YsPi/2.0);

    // Connect to the server
// 	if(argc != 3)
//     {
//         std::cerr << "Usage: ip_address port" << std::endl;
//         exit(0);
//     }
//
//     char *serverIp = argv[1];
//     int port = atoi(argv[2]);
//
// 	Client client(port, serverIp);
//
// 	printf("client created \n");
//
// 	int clientSd = client.Connect();
//
// 	if (clientSd == -1) return -1;
//
// 	printf("client connected\n");
//
//     char msg[msgSize];

    while(!terminate) {
        FsPollDevice();
        // Get mouse event
        bool isHiting = false;
        int key = FsInkey();
        int leftButton, middleButton, rightButton, locX, locY;
        int mouseEvent = FsGetMouseEvent(leftButton, middleButton, rightButton, locX, locY);

        if (key == FSKEY_ESC) {
            terminate = true;
        }

        if(isStarter) {
            player.update(locX, locY);
            // ball.update(locX, locY);
            if(mouseEvent == FSMOUSEEVENT_LBUTTONDOWN) {
                float vx = 0.0;
                float vy = 1.0;
                float vz = 0.0;
                // ball.update(vx, vy, vz);

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
        // std::stirng message = encodeMessage(isStarter, isHiting, ball, player);


        // ----------------------------------------------------------------------
        // Send the message to the server and receive the message from the server
        // if (!client.connected(clientSd)){
        //     std::cout << "Connection Lost." << std::endl;
        //     break;
        // }
        // Send
        // memset(&msg, 0, sizeof(msg));
        // strcpy(msg, message.c_str());

        // Receive
        // std::cout << "Message Sent:" << msg <<"\nAwaiting server response..." << std::endl;
        // memset(&msg, 0, sizeof(msg));

        // ----------------------------------------------------------------------

        // updateStates(msg, isStarter, ball, opponent);

        // Draw
        glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
        auto aspect=(double)wid/(double)hei;
        glViewport(0,0,wid,hei);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(45.0,aspect,d/10.0,d*2.0);

        YsMatrix4x4 globalToCamera=Rc;
        globalToCamera.Invert();

        YsMatrix4x4 modelView;  // need #include ysclass.h
        modelView.Translate(0,0,-d);
        modelView*=globalToCamera;
        modelView.Translate(-t);

        GLfloat modelViewGl[16];
        modelView.GetOpenGlCompatibleMatrix(modelViewGl);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glMultMatrixf(modelViewGl);

        // ball.draw();
        player.draw();
        // opponent.draw();
        // table.draw();
        FsSwapBuffers();
        FsSleep(25);
        // Reset
        isHiting = false;

    }
    // close(clientSd);
    std::cout << "End of Game." << std::endl;
}
