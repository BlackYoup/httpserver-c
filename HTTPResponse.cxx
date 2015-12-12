#include <cstring>
#include <stdlib.h>

#include "HTTPResponse.h"
#include "debug.h"

using std::map;
using std::pair;

const int LF = 0x0A;
const int CR = 0x0D;
const int SP = 0x20;

HTTPResponse::HTTPResponse(HTTPRequest *request){
  // TODO: berk
  memset(this->response, '\0', 2048);

  this->req = request;

  this->res.statusLine = this->makeStatusLine();
  this->res.headers = this->makeHeaders();
  this->res.body = this->makeBody();

  this->makeResponse();
};

char *HTTPResponse::getResponse(){
  return this->response;
};

void HTTPResponse::makeResponse(){
  char textHeaders[1024] = {'\0'};
  map<char*, char*>::iterator header;

  Debug d;

  for(header = this->res.headers.begin(); header != this->res.headers.end(); ++header){
    strcat(textHeaders, header->first);
    strcat(textHeaders, ": ");
    strcat(textHeaders, header->second);
    size_t tmp = strlen(textHeaders);
    textHeaders[tmp] = CR;
    textHeaders[tmp + 1] = LF;
  };

  size_t head = strlen(this->res.statusLine) + strlen(textHeaders);

  strcat(this->response, this->res.statusLine);
  strcat(this->response, textHeaders);

  this->response[head] = CR;
  this->response[head + 1] = LF;
  this->response[head + 2] = '\0';

  strcat(this->response, this->res.body);
  this->response[strlen(this->response) - 1] = '\0';
};

char *HTTPResponse::makeStatusLine(){
  HTTP_REQUEST req = this->req->getRequest();
  size_t protocolLength = strlen(req.protocol);
  size_t totalLength = protocolLength + 1 + 3 + 1 + 2 + 1 + 1;

  char *statusLine = (char*)calloc(totalLength, sizeof(char));

  strcat(statusLine, req.protocol);
  statusLine[protocolLength - 1] = SP;

  strcat(statusLine, "200");
  statusLine[protocolLength + 3] = SP;

  strcat(statusLine, "OK");

  statusLine[totalLength - 3] = CR;
  statusLine[totalLength - 2] = LF;

  return statusLine;
};

map<char*, char*> HTTPResponse::makeHeaders(){
  map<char*, char*> ret;

  ret.insert(pair<char*, char*>((char*)"Server", (char*)"YSS"));
  ret.insert(pair<char*, char*>((char*)"Content-Type", (char*)"text/html"));

  return ret;
};

char *HTTPResponse::makeBody(){
  return (char*)"Hello, welcome onto YSS (YoloSwagServer).\n";
};
