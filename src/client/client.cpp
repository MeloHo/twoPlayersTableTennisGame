//client
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

#include "ball.h"
#include "player.h"
#include "table.h"
#include "fssimplewindow.h" // For graphics
#include "ysclass.h"


#include "linuxClient.hpp"
#include "../msg/state.h"
#include "../msg/msg.pb.h"

// protobuf inlcudes
#include <google/protobuf/message.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include <google/protobuf/io/coded_stream.h>

using namespace google::protobuf::io;

google::protobuf::uint32 readHdr(char *buf)
{
    google::protobuf::uint32 size;
    google::protobuf::io::ArrayInputStream ais(buf,4);
    CodedInputStream coded_input(&ais);
    coded_input.ReadVarint32(&size);
    std::cout<<"size of payload is "<<size<<std::endl;
    return size;
}

void readBody(int csock, google::protobuf::uint32 siz, State &state)
{
    int bytecount;
    Msg payload;
    char buffer [siz+4];

    if((bytecount = recv(csock, (void *)buffer, 4+siz, MSG_WAITALL))== -1)
    {
        fprintf(stderr, "Error receiving data %d\n", errno);
    }

    //std::cout<<"Second read byte count is "<<bytecount<<std::endl;

    google::protobuf::io::ArrayInputStream ais(buffer,siz+4);
    CodedInputStream coded_input(&ais);

    coded_input.ReadVarint32(&siz);

    google::protobuf::io::CodedInputStream::Limit msgLimit = coded_input.PushLimit(siz);

    payload.ParseFromCodedStream(&coded_input);

    coded_input.PopLimit(msgLimit);

    std::cout<<"Message is \n"<<payload.DebugString();

    std::cout<<"--------------Updating---------------"<<std::endl;
    //update game state for drawing
    state.isHitting = payload.ishitting();
    state.player1Score = payload.player1score();
    state.player2Score = payload.player2score();

    state.ballX = payload.ballx();
    state.ballY = payload.bally();
    state.ballZ = payload.ballz();

    state.player1X = payload.player1x();
    state.player1Y = payload.player1y();
    state.player1Z = payload.player1z();

    state.player2X = payload.player2x();
    state.player2Y = payload.player2y();
    state.player2Z = payload.player2z();

    std::cout<<"------------Update Finished!-------------"<<std::endl;

}

void recv_msg(int csock, State &state)
{
    char buffer[4];
    int bytecount=0;
    Msg logp;

    memset(buffer, '\0', 4);

    if((bytecount = recv(csock, buffer,4, MSG_PEEK))== -1){
        fprintf(stderr, "Error receiving data %d\n", errno);
    }else if (bytecount == 0)
        printf(" Byte read 0\n");

    //std::cout<<"First read byte count is "<<bytecount<<std::endl;
    readBody(csock, readHdr(buffer), state);
}

Msg encodeMessage(State state)
{
    Msg message;
    message.set_ishitting(state.isHitting);
    message.set_playerid(state.playerId);
    message.set_player1score(state.player1Score);
    message.set_player2score(state.player2Score);

    message.set_ballx(state.ballX);
    message.set_bally(state.ballY);
    message.set_ballz(state.ballZ);

    message.set_player1x(state.player1X);
    message.set_player1y(state.player1Y);
    message.set_player1z(state.player1Z);

    message.set_player2x(state.player2X);
    message.set_player2y(state.player2Y);
    message.set_player2z(state.player2Z);
    return message;
}

void updateStates(const char* msg, bool& isStarter, Ball& ball, Player& component)
{
    return;
}





int main(int argc, char *argv[])
{
    FsOpenWindow(0,0,1200,800,1);

    //*********************************************


    //                  Ball


    //*********************************************
    Ball ball;


    /* player and opponent */
    Player player;
    Player opponent;
    int wid, hei;
    FsGetWindowSize(wid,hei);
    player.updateWinSize(wid, hei);
    opponent.updateWinSize(wid, hei);
    Table table(0.7625,1.37,0.5);

    YsMatrix4x4 Rc;
    double d = 1.0;
    YsVec3 t = YsVec3::Origin() + YsVec3 (0.75, 0.0, 1.0);
    Rc.RotateYZ(YsPi/2.0);

    /* some flags */
    bool isStarter = true;
    bool terminate = false;
    bool start = false; // flag for starting game/ both player connectted

    /* connecting to server */
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
    int bytecount;

    /* Receiving first message */
    // first message is the assigned number of player
    int Iam = -1;
    memset(&msg, 0, sizeof(msg));
    recv(clientSd, (char*)&msg, sizeof(msg), 0);
    sscanf(msg, "%d", &Iam);

    printf("I am %d Player\n", Iam+1);
    sleep(1);

    /* waiting for the other player to connect */
    while (true){
        printf("Waiting for the other client\n");

        memset(&msg, 0, sizeof(msg));
        recv(clientSd, (char*)&msg, sizeof(msg), 0);

        if(!strcmp(msg, "Start"))
        {
            cout << "Both players connected" << endl;
            break;
        }
        sleep(1);
    }

    /* client state for the purpose of drawing */
    // initialization
    State state = {
        0,
        Iam,
        1,
        3,
        0.0,
        0.0,
        0.0,
        0,
        0,
        0,
        0,
        0,
        0
    };

    /* start game loop */
    while(!terminate) {
        FsPollDevice();

        /* Get mouse event */
        bool isHiting = false;
        int key = FsInkey();
        int leftButton, middleButton, rightButton, locX, locY;
        int mouseEvent = FsGetMouseEvent(leftButton, middleButton, rightButton, locX, locY);

        if (key == FSKEY_ESC) {
            terminate = true;
        }

        /* set initial state/action */
        if(isStarter) {
            player.update(locX, locY);
            // ball.update(locX, locY);
            if(mouseEvent == FSMOUSEEVENT_LBUTTONDOWN) {
                float vx = 0.0;
                float vy = 1.0;
                float vz = 0.0;
                // ball.update(vx, vy, vz);

                isStarter = false;
            }else{
                player.update(locX, locY);
                if(mouseEvent == FSMOUSEEVENT_LBUTTONDOWN) {
                    isHiting = true;
                }
            }
        }

        // TODO: add is_hitting flag;

        /* update player state */
        if (Iam == 0){
            state.player1X = locX;
            state.player1Y = locY;
        }else{
            state.player2X = locX;
            state.player2Y = locY;
        }
        
        /* Communicating with server sending/receiving */
        // ----------------------------------------------------------------------
        // Send the message to the server and receive the message from the server
        if (!client.connected(clientSd)){
            std::cout << "Connection Lost." << std::endl;
            break;
        }

        // Encode the message here
        Msg message = encodeMessage(state);
        std::cout<<"size after serializing is "<<message.ByteSize()<<std::endl;
        int siz = message.ByteSize()+4;
        char *pkt = new char[siz];

        // serialize
        google::protobuf::io::ArrayOutputStream aos(pkt, siz);
        CodedOutputStream *coded_output = new CodedOutputStream(&aos);
        coded_output->WriteVarint32(message.ByteSize());
        message.SerializeToCodedStream(coded_output);

        // send the package
        if (bytecount = send(clientSd, (void*)pkt, siz, 0) == -1){
            printf("error sending data\n");
            break;
        }
        std::cout << "Bytes Sent:"<< bytecount <<"\nAwaiting server response..." << std::endl;
        delete pkt;

        /* Reciver */
        recv_msg(clientSd, state);
        // ----------------------------------------------------------------------

        /* draw self and oppenent */
        //int oppoX = wid/2, oppoY = hei/2; // decoded from response, this line is just for testing
        // update oppoent position
        int oppoX = Iam == 1 ? state.player1X: state.player2X;
        int oppoY = Iam == 1 ? state.player1Y: state.player2Y;
        opponent.updateOppo(oppoX, oppoY);

        // Draw
        glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
        auto aspect=(double)wid/(double)hei;
        glViewport(0,0,wid,hei);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(60.0,aspect,d/10.0,10.0);

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

        /* draw stuff */
        ball.draw();
        player.draw();
        opponent.draw();
        table.draw();
        FsSwapBuffers();
        FsSleep(10);
        // Reset
        isHiting = false;

        /* sleep for 0.2 s */
        //usleep(200000); 

    }

    /* game over & close socket */
    close(clientSd);
    std::cout << "End of Game." << std::endl;
}
