//server
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
#include <cmath>

#include "linuxServer.hpp"
#include "../msg/state.h"
#include "../msg/msg.pb.h"

// protobuf
#include <google/protobuf/message.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include <google/protobuf/io/coded_stream.h>

using namespace google::protobuf::io;

const double TIME_INTERVAL = 0.001; // 0.01s
const double GRAVITY = 9.8; // g = 9.8

struct ball
{
  float x, y, z;
  float vx, vy, vz;
};

google::protobuf::uint32 readHdr(char *buf)
{
    google::protobuf::uint32 size;
    google::protobuf::io::ArrayInputStream ais(buf,4);
    CodedInputStream coded_input(&ais);
    coded_input.ReadVarint32(&size);
    std::cout<<"size of payload is "<<size<<std::endl;
    return size;
}

void readBody(int csock,google::protobuf::uint32 siz, State &state)
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

    std::cout<<"Message is "<<payload.DebugString();

    std::cout<<"--------------Updating---------------"<<std::endl;
    // update game state for calculating 

    state.isHitting = payload.ishitting();
    state.player1X = payload.player1x();
    state.player1Y = payload.player1y();
    state.player1Z = payload.player1z();

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

    readBody(csock, readHdr(buffer), state);
}

void updateBall(ball& Ball,State& player1State,State& player2State)
{
  // If Ball hits the table, bounce the ball
  if(Ball.x >= 0 && Ball.x <= 1.5 && Ball.y >= 0.5 && Ball.y <= 3.24 && Ball.z <= 0.76)
  {
    Ball.z = -Ball.z;
  }
  else if(player1State.isHitting && player2State.isHitting){
    // Player1 hit the ball
    if(sqrt(pow(Ball.x - player1State.player1X, 2) + pow(Ball.y - player1State.player1Y, 2) + pow(Ball.z - player1State.player1Z, 2)) < 0.1)
    {
      Ball.y = -Ball.y;
    }
    // Player2 hit the ball
    else if(sqrt(pow(Ball.x - player2State.player1X, 2) + pow(Ball.y - player2State.player1Y, 2) + pow(Ball.z - player2State.player1Z, 2)) < 0.1)
    {
      Ball.y = -Ball.y;
    }
  }

  //Update the postion of Ball based on its velocity
  Ball.x += TIME_INTERVAL * Ball.vx;
  Ball.y += TIME_INTERVAL * Ball.vy;
  Ball.vz -= TIME_INTERVAL * GRAVITY;
  Ball.z += TIME_INTERVAL * Ball.vz;

}

void judgeWinner(ball& Ball, bool& isPlayer1Starter, bool& isPlayer2Starter, int& score1, int& score2)
{
  // The Ball hit the net
  if(Ball.x >=0 && Ball.x <= 1.5 && Ball.z >= 0.76 && Ball.z <= 0.91 && Ball.y >= 1.86 && Ball.y <= 1.88){
    if(Ball.vy > 0){
      score2++;
      isPlayer2Starter = true;
    }
    else{
      score1++;
      isPlayer1Starter = true;
    }
    return;
  }
  // The ball hits outsize of the table
  else if(!(Ball.x >= 0 && Ball.x <= 1.5 && Ball.y >= 0.5 && Ball.y <= 3.24) && Ball.z <= 0.76)
  {
    if(Ball.vy > 0){
      score2++;
      isPlayer2Starter = true;
    }
    else{
      score1++;
      isPlayer1Starter = true;
    }
    return;
  }
}


Msg encodeMessage(State state)
{
    Msg message;

    //message.set_gamestate(state.gameState);
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




int main(int argc, char *argv[])
{

  // Create Server 
  if(argc != 2)
  {
      std::cerr << "Usage: port" << std::endl;
      exit(0);
  }
  int port = atoi(argv[1]);

  Server server(port);
  printf("server created \n");
  int serverSd = server.StartServer();
  printf("server connected to both clients\n");

  //buffer to send and receive messages with
  char msg1[msgSize];
  char msg2[msgSize];
  int bytecount;

  // send signal to start game
  std::string s = "Start";
  send(server.client1Sd, (char*)s.c_str(), strlen(s.c_str()), 0);
  send(server.client2Sd, (char*)s.c_str(), strlen(s.c_str()), 0);
  sleep(1);

  // server state for calculating
  // initialization

  bool isPlayer1Starter = true;
  bool isPlayer2Starter = false;
  int score1 = 0, score2 = 0;
  ball Ball;
  Ball.x = 0.0;
  Ball.y = 0.0;
  Ball.z = 0.0;
  Ball.vx = 0.0;
  Ball.vy = 0.0;
  Ball.vz = 0.0;

  State player1State = {
      false,
      0,
      0,
      0,
      0.0,
      0.0,
      0.0,
      0.0,
      0.0,
      0.0,
      0.0,
      0.0,
      0.0
  };

  State player2State = {
      false,
      0,
      0,
      0,
      0.0,
      0.0,
      0.0,
      0.0,
      0.0,
      0.0,
      0.0,
      0.0,
      0.0
  };


  while(true)
  {
      if (!server.connected(server.client1Sd) || !server.connected(server.client2Sd)) break;

      // get both clients response
      std::cout << "Awaiting client1 response..." << std::endl;
      recv_msg(server.client1Sd, player1State);
      std::cout << "Awaiting client2 response..." << std::endl;
      recv_msg(server.client2Sd, player2State);

      // some processing 
      //+++++++++++++++++++++++++++++

      if(isPlayer1Starter && !isPlayer2Starter)
      {
        Ball.x = player1State.player1X;
        Ball.y = player1State.player1Y;
        Ball.z = player1State.player1Z;

        if(player1State.isHitting) {
          Ball.vx = 0;
          Ball.vy = 1.0;
          Ball.vz = 0;

          isPlayer1Starter = false;
        }
      }
      else if(isPlayer2Starter && !isPlayer1Starter)
      {
        Ball.x = player2State.player1X;
        Ball.y = player2State.player1Y;
        Ball.z = player2State.player1Z;

        if(player2State.isHitting) {
          Ball.vx = 0;
          Ball.vy = 1.0;
          Ball.vz = 0;

          isPlayer2Starter = false;
        }
      }
      else{
        updateBall(Ball, player1State, player2State);
        judgeWinner(Ball, isPlayer1Starter, isPlayer2Starter, score1, score2);
      }

      //+++++++++++++++++++++++++++++

      // encode message

      // update player1State
      player1State.player1Score = score1;
      player1State.player2Score = score2;
      player1State.player2X = player2State.player1X;
      player1State.player2Y = player2State.player1Y;
      player1State.player2Z = player2State.player1Z;
      player1State.ballX = Ball.x;
      player1State.ballY = Ball.y;
      player1State.ballZ = Ball.z;      
      Msg message1 = encodeMessage(player1State);

      // update player2State
      player2State.player1Score = score2;
      player2State.player2Score = score1;
      player2State.player2X = player1State.player1X;
      player2State.player2Y = player1State.player1Y;
      player2State.player2Z = player1State.player1Z;
      player2State.ballX = Ball.x;
      player2State.ballY = Ball.y;
      player2State.ballZ = Ball.z;      
      Msg message2 = encodeMessage(player2State);

      // Send message1
      int siz1 = message1.ByteSize()+4;
      char *pkt1 = new char[siz1];

      google::protobuf::io::ArrayOutputStream aos1(pkt1, siz1);
      CodedOutputStream *coded_output1 = new CodedOutputStream(&aos1);
      coded_output1->WriteVarint32(message1.ByteSize());
      message1.SerializeToCodedStream(coded_output1);

      if (bytecount = send(server.client1Sd, (void*)pkt1, siz1, 0) == -1){
          printf("error sending data to client1\n");
          break;
      }

      // Send message2
      int siz2 = message2.ByteSize()+4;
      char *pkt2 = new char[siz2];

      google::protobuf::io::ArrayOutputStream aos2(pkt2, siz2);
      CodedOutputStream *coded_output2 = new CodedOutputStream(&aos2);
      coded_output2->WriteVarint32(message2.ByteSize());
      message2.SerializeToCodedStream(coded_output2);

      if (bytecount = send(server.client2Sd, (void*)pkt2, siz2, 0) == -1){
          printf("error sending data to client2\n");
          break;
      }

      delete[] pkt1;
      delete[] pkt2;
      std::cout << "Message Sent!" << std::endl;

  }

  close(serverSd);

  printf("session ended\n");
    
  return 0;
}