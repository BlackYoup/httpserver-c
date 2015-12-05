#include "server.h"

void Server::start(){
  Socket serverSocket;
  serverSocket.init("8080");
};
