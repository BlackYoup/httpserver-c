#ifndef HTTP_RESPONSE_H
#define HTTP_RESPONSE_H

#include "HTTPRequest.h"
#include <map>


enum HTTP_RESPONSE_CODES{
  OK = 200
};

struct HTTP_RESPONSE{
  std::map<char*, char*> headers;
  char *statusLine;
  char *body;
  HTTP_RESPONSE_CODES responseCode;
};

class HTTPResponse{
  private:
    HTTPRequest *req;
    HTTP_RESPONSE res;
    char response[2048];

    void makeResponse();
    char *makeStatusLine();
    std::map<char*, char*> makeHeaders();
    char *makeBody();

  public:
    HTTPResponse(HTTPRequest*);
    char *getResponse();
};

#endif
