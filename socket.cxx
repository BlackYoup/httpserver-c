#include "socket.h"
#include <unistd.h>

#include "HTTPResponse.h"

void Socket::init(char const *port){
  HTTPRequest req = createSocket(port)
  ->bindSocket()
  ->listenConnections()
  ->acceptClients()
  ->receiveDataFromClient();

  HTTPResponse res(&req);

  this
    ->sendBackResponse(res.getResponse())
    ->disconnectClient()
    ->error();
};

Socket* Socket::createSocket(char const *port){
  if(this->errorCode != 0){
    return this;
  }

  memset(&host_info, 0, sizeof host_info);

  host_info.ai_family   = AF_UNSPEC;
  host_info.ai_socktype = SOCK_STREAM;
  host_info.ai_flags    = AI_PASSIVE;

  int status = getaddrinfo(
    NULL,
    port,
    &host_info,
    &host_info_list
  );

  if(status != 0){
    std::sprintf(this->strError, "getaddrinfo error: %s", gai_strerror(status));
    this->errorCode = status;

  }

  d.log(DEBUG, "Creating socket...");

  socketfd = socket(
    host_info_list->ai_family,
    host_info_list->ai_socktype,
    host_info_list->ai_protocol
  );

  if(socketfd == -1){
    std::sprintf(this->strError, "Error creating socket: %s", strerror(errno));
    this->errorCode = socketfd;
  }

  d.log(DEBUG, "Socket created");

  return this;
};

Socket* Socket::bindSocket(){
  if(this->errorCode != 0){
    return this;
  }

  d.log(DEBUG, "Binding socket...");

  // we make use of the setsockopt() function to make sure the port is not in use.
  // by a previous execution of our code. (see man page for more information)

  int yes = 1;
  int statusSetSockOpt = setsockopt(
    socketfd,
    SOL_SOCKET,
    SO_REUSEADDR,
    &yes,
    sizeof(int)
  );

  if (statusSetSockOpt == -1){
    std::sprintf(this->strError, "Error setting socket options: %s", strerror(errno));
    this->errorCode = statusSetSockOpt;
    return this;
  }

  int statusBind = bind(
    socketfd,
    host_info_list->ai_addr,
    host_info_list->ai_addrlen
  );

  if(statusBind == -1){
    std::sprintf(this->strError, "Error binding socket: %s", strerror(errno));
    this->errorCode = statusBind;
    return this;
  }

  d.log(DEBUG, "Socket successfuly binded");

  return this;
};

Socket* Socket::listenConnections(){
  if(this->errorCode != 0){
    return this;
  }

  int listenStatus = listen(socketfd, 5);

  if(listenStatus == -1){
    std::sprintf(this->strError, "Error while listening to connections: %s", strerror(errno));
    this->errorCode = listenStatus;
    return this;
  }

  d.log(DEBUG, "Awaiting connections...");

  return this;
};

Socket* Socket::acceptClients(){
  if(this->errorCode != 0){
    return this;
  }

  struct sockaddr_storage client_info;
  socklen_t client_info_size = sizeof(client_info);

  this->client = accept(Socket::socketfd,
      (struct sockaddr *) &client_info,
      &client_info_size);

  d.log(DEBUG, "Accepting client...");

  if(this->client == -1){
    std::sprintf(this->strError, "Error connecting to client: %s", strerror(errno));
    this->errorCode = this->client;
    return this;
  }

  d.log(DEBUG, "Client connected !");

  return this;
};

HTTPRequest Socket::receiveDataFromClient(){
  if(this->errorCode != 0){
    //return this;
  }

  d.log(DEBUG, "Starting to receive data from client...");

  const int data_length = 2048;
  char data[data_length];

  ssize_t received_bytes = recv(this->client, data, data_length, 0);

  if(received_bytes == 0){
    std::sprintf(this->strError, "Seems like client closed the connection or didn't send any data");
    this->errorCode = -1;
    //TODO handle errors;
    //return this;
  } else if(received_bytes == -1){
    std::sprintf(this->strError, "Error receiving data from client: %s", strerror(errno));
    this->errorCode = received_bytes;
    //TODO handle errors;
    //return this;
  }

  for(size_t i = 0; i < strlen(data); i++){
    d.log(data[i], (int)data[i]);
  }

  HTTPRequest req(data);
  return req;
};

Socket* Socket::sendBackResponse(char *data){
  if(this->errorCode != 0){
    return this;
  }

  int sendStatus = send(this->client, data, strlen(data) + 1, 0);

  if(sendStatus == -1){
    d.log(ERROR, "Can't send back data to client", strerror(errno));
  }

  d.log(DEBUG, "Sent response to client:", "\n", data);

  return this;
};

Socket* Socket::disconnectClient(){
  if(this->errorCode != 0){
    return this;
  }

  close(this->client);
  d.log(DEBUG, "Client deconnected by server");

  return this;
};

Socket* Socket::error(){
  if(this->errorCode != 0){
    Debug d;
    d.log(ERROR, this->strError);
  }
  return this;
};
