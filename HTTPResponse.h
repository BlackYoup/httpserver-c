#ifndef HTTP_RESPONSE_H
#define HTTP_RESPONSE_H

#include "HTTPRequest.h"

class HTTPResponse{
  private:
    HTTPRequest *req;
    char response[14] = "HELLO BACK :)";

  public:
    HTTPResponse(HTTPRequest*);
    char *getResponse();
};

#endif
