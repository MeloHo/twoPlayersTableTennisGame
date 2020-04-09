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
    if (payload.playerid() == 0)
    {
      state.player1X = payload.player1x();
      state.player1Y = payload.player1y();
      state.player1Z = payload.player1z();
    }else{
      state.player2X = payload.player2x();
      state.player2Y = payload.player2y();
      state.player2Z = payload.player2z();
    }

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
  State state = {
      0,
      -1,
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

  while(true)
  {
      if (!server.connected(server.client1Sd) || !server.connected(server.client2Sd)) break;

      // get both clients response
      std::cout << "Awaiting client1 response..." << std::endl;
      recv_msg(server.client1Sd, state);
      std::cout << "Awaiting client2 response..." << std::endl;
      recv_msg(server.client2Sd, state);

      // some processing 
      //+++++++++++++++++++++++++++++




      //+++++++++++++++++++++++++++++

      // encode message
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
      if (bytecount = send(server.client1Sd, (void*)pkt, siz, 0) == -1){
          printf("error sending data to client1\n");
          break;
      }
      if (bytecount = send(server.client2Sd, (void*)pkt, siz, 0) == -1){
          printf("error sending data to client1\n");
          break;
      }
      std::cout << "Bytes Sent: %d"<< bytecount <<"\nAwaiting server response..." << std::endl;
      delete[] pkt;
      std::cout << "Message Sent!" << std::endl;

  }

  close(serverSd);

    printf("session ended\n");
    
    return 0;
}