#ifndef HTTP_SOCKET_H
#define HTTP_SOCKET_H

#include <sys/socket.h>
#include <cstring>
#include <netdb.h>
#include "debug.h"
#include "server.h"
#include "HTTPRequest.h"

class Socket{
  private:
    int socketfd;
    struct addrinfo host_info;
    struct addrinfo *host_info_list;
    Debug d;

    Socket* bindSocket();
    Socket* createSocket(char const*);
    Socket* listenConnections();
    Socket* acceptClients();
    HTTPRequest receiveDataFromClient(int);
    Socket* sendBackResponse(int, char*);
    Socket* disconnectClient(int);
    Socket* error();
    void onClient(int);

    int errorCode = 0;
    char strError[128];
    char response[2048];

  public:
    void init(char const *);
};

#endif
