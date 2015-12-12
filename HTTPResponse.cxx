#include "HTTPResponse.h"

HTTPResponse::HTTPResponse(HTTPRequest *request){
  this->req = request;
};

char *HTTPResponse::getResponse(){
  return this->response;
};
