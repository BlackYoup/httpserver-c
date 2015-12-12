#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H

#include <map>
#include <vector>


enum HTTP_VERB{
  GET,
  POST,
  UPDATE,
  DELETE
};

struct HTTP_REQUEST{
  std::map<char*, char*> headers;
  std::map<char*, char*> queryString;
  HTTP_VERB verb;
  char *rawUrl;
  char *url;
  char *data;
  char *protocol;
  char *body;
};

class HTTPRequest{
  private:
    HTTP_REQUEST req;
    char* rawReq;

    std::map<char*, char*> parseHeaders(std::vector<char*>);
    std::map<char*, char*> parseRequest(char*);
    std::map<char*, char*> parseQueryString(char*);
    std::vector<char*> parseHTTPInfo(char*);
    HTTP_VERB getHTTPVerb(char*);
    char *extractPath(char*);
  public:
    HTTPRequest(char*);
};

#endif
