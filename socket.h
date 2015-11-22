#include <string>
#include "debug.h"

class Socket{
  private:
    int socket;
    Debug d;

  public:
    int connect();
    int disconnect();
};
