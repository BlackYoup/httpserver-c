#include <string.h>
#include <cstring>
#include <stdlib.h>
#include <stdio.h>

#include "utils.h"

using std::vector;

vector<char *> Utils::split(char *str, char del){
  vector<char *> splittedStr;

  const size_t length = strlen(str);
  size_t count = 0;

  char buffer[length] = {'\0'};
  int bufferEntry = 0;
  size_t lastElement = length - 1;

  for(; count < length; count++, bufferEntry++){
    if(str[count] == del || count == lastElement){
      if(count == lastElement){
        buffer[bufferEntry] = str[count];
      }

      strcat(buffer, "\0");
      // TODO: need to free these buffers
      char *x = (char*)malloc(strlen(buffer) + 1);
      std::strcpy(x, buffer);

      splittedStr.push_back(x);

      bufferEntry = -1;
      memset(buffer, '\0', length);
    } else{
      buffer[bufferEntry] = str[count];
    }
  }

  return splittedStr;
};

char *Utils::strcpy(char *dest, char *source, int sourceStart, int sourceEnd){
  if(sourceEnd <= 0 || sourceStart > sourceEnd){
    sourceEnd = strlen(source);
  }

  char buffer[sourceEnd - sourceStart + 1];

  for(int i = 0; sourceStart < sourceEnd; i++, sourceStart++){
    buffer[i] = source[sourceStart];
  }

  buffer[sourceEnd] = '\0';

  return std::strcpy(dest, buffer);
};
