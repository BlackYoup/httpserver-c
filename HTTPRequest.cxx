#include "HTTPRequest.h"
#include "utils.h"
#include "debug.h"

using std::vector;
using std::map;
using std::pair;

// Empty line, Carriage Return symbol
const int CR = 0xD;

HTTPRequest::HTTPRequest(char*plainRequest){
  this->rawReq = plainRequest;
  map<char*, char*> parsedHTTPRequest = this->parseRequest(plainRequest);

  vector<char*> headers = this->parseHTTPInfo(parsedHTTPRequest[(char*)"http"]);
  this->req.headers = this->parseHeaders(headers);
  this->req.queryString = this->parseQueryString(this->req.rawUrl);

  this->req.body = parsedHTTPRequest[(char*)"body"];
};

map<char*, char*> HTTPRequest::parseRequest(char *req){
  size_t emptyLine = 0;
  size_t reqLength = strlen(req);
  size_t last = reqLength - 1;

  map<char*, char*> ret;

  Debug d;

  for(; emptyLine < reqLength; emptyLine++){
    if(req[emptyLine] == '\n' && emptyLine < last && (int)req[emptyLine + 1] == CR){
      break;
    }
  }

  if(emptyLine == 0){
    d.log(ERROR, "Couldn't find a separator, aborting...");
    return ret;
  }

  size_t bodyLength = reqLength - emptyLine;

  // TODO: clean these 2 buffers
  char *http = (char*)malloc(emptyLine);
  char *body = (char*)malloc(bodyLength);

  strncpy(http, req, emptyLine);
  Utils::strcpy(body, req, emptyLine + 3, -1); // +3 because chars are: LB(10) CR(13) LB(10)

  d.log("HTTP", http);

  ret.insert(pair<char*, char*>((char*)"http", http));
  ret.insert(pair<char*, char*>((char*)"body", body));

  return ret;
};

vector<char*> HTTPRequest::parseHTTPInfo(char *headers){
  Debug d;
  vector<char*> splitLB = Utils::split(headers, '\n');
  vector<char*> httpInfo = Utils::split(splitLB[0], ' ');

  this->req.verb = getHTTPVerb(httpInfo[0]);
  this->req.rawUrl = httpInfo[1];
  this->req.protocol = httpInfo[2];

  splitLB.erase(splitLB.begin());
  return splitLB;
};

HTTP_VERB HTTPRequest::getHTTPVerb(char *verb){
  // TODO: I'm sure I can do much better
  if(strcmp(verb, "GET") == 0){
    return GET;
  } else if(strcmp(verb, "POST") == 0){
    return POST;
  } else if(strcmp(verb, "DELETE") == 0){
    return DELETE;
  } else if(strcmp(verb, "UPDATE") == 0){
    return UPDATE;
  }
};

map<char*, char*> HTTPRequest::parseHeaders(vector<char*> headers){
  map<char*, char*> ret;
  vector<char*>::iterator header;

  Debug d;

  for(header = headers.begin(); header != headers.end(); ++header){
    vector<char*> tmp = Utils::split(*header, ':');
    ret.insert(pair<char*, char*>(tmp[0], tmp[1]));
  }

  return ret;
};

map<char*, char*> HTTPRequest::parseQueryString(char *url){
  map<char*, char*> ret;
  vector<char*> qs = Utils::split(url, '?');

  this->req.url = qs[0];

  Debug d;

  // If there is a QueryString
  if(qs.size() == 2){
    d.log("GOT QUERY STRING");
    vector<char*> params = Utils::split(qs[1], '&');
    vector<char*>::iterator param;
    for(param = params.begin(); param != params.end(); ++param){
      // TODO: handle multiple values for same key
      vector<char*> tmp = Utils::split(*param, '=');
      d.log("QS: PARAM:", tmp[0], "VALUE:", tmp[1]);
      ret.insert(pair<char*, char*>(tmp[0], tmp[1]));
    }
  } else{
    d.log("NO QUERY STRING");
    return ret;
  }
};
