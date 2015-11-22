#include <iostream>
#include <stdio.h>
#include <string.h>
#include "debug.h"

void Debug::print(std::string message, DEBUG_LEVEL level){
  std::string level_str;

  switch(level){
    case ERROR:
      level_str = "\033[1;31m[ERROR]\033[0m ";
    break;
    case INFO:
      level_str = "\033[1;32m[INFO]\033[0m ";
    break;
    case DEBUG:
      level_str = "\033[1;36m[DEBUG]\033[0m ";
    break;
    default:
      level_str = "";
    break;
  }

  std::cout
    << "\033[1;33m["
    << getTime()
    << "]\033[0m"
    << level_str
    << message
    << std::endl;
};

char* Debug::getTime(){
  time_t now;
  time(&now);

  int sizeOfStr = sizeof "00:00:00";

  char *tempDate = new char[sizeOfStr];
  char date[sizeOfStr];

  strftime(date, sizeOfStr, "%H:%M:%S", gmtime(&now));
  strcpy(tempDate, date);

  return tempDate;
};
