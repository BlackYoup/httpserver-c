#ifndef UTILS_H
#define UTILS_H

#include <vector>

class Utils{
  public:
    static std::vector<char*> split(char*, char, int);
    static char *strcpy(char*, char*, int, int);
};

#endif
