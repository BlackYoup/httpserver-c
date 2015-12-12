#include <stdio.h>
#include <vector>
#include <cstring>

#include "tests.h"
#include "utils.h"

int main(){
  testOwnMethods();
  testUtilsMethods();
};

void testOwnMethods(){
  printf("Testing own methods..\n");
  Test::assert(Test::assert(true, true), true);
  Test::assert("equal", "equal");
  Test::assert(true, false);
};

void testUtilsMethods(){
  printf("Testing Utils methods...\n");

  std::vector<char *> x = Utils::split((char*)"Some spaces needed", ' ');
  Test::assert(x.size(), (std::vector<char *>::size_type)3);

  char destination[10];
  char source[13] = "yoloswag2014";
  Utils::strcpy(destination, source, 0, 8);
  Test::assert(destination, (char*)"yoloswag");
};
