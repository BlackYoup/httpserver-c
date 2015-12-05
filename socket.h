#include <sys/socket.h>
#include <cstring>
#include <netdb.h>
#include "debug.h"

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
    Socket* receiveDataFromClient();
    Socket* sendBackResponse();
    Socket* disconnectClient();
    Socket* error();

    int errorCode = 0;
    char strError[128];
    int client;

  public:
    void init(char const *);
};
