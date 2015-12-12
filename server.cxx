#include "server.h"
#include "socket.h"

void Server::start(){
  Socket serverSocket;
  serverSocket.init("8080");
};
