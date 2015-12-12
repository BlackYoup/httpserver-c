#ifndef TESTS_H
#define TESTS_H

#include <typeinfo>
#include <stdio.h>
#include <cstring>

void testOwnMethods();
void testUtilsMethods();

enum TEST_ERRORS{
  NOT_SAME_TYPE,
  NOT_SAME_VALUE
};

class Test{
  private:
    static void testSuccess();
    static void testFailed(TEST_ERRORS);
  public:
    template <typename T> static bool assert(T, T);
};

template <typename T>
bool Test::assert(T obj, T obj2){
  const char *objName = typeid(obj).name();
  const char *objName2 = typeid(obj2).name();
  bool isSameType = strcmp(objName, objName2) == 0;
  bool isSameValue;

  if(!isSameType){
    testFailed(NOT_SAME_TYPE);
    return isSameType;
  } else{
    if(strcmp(typeid(obj).name(), typeid(char *).name()) == 0){
      isSameValue = strcmp((char*)obj, (char*)obj2) == 0;
    } else{
      isSameValue = obj == obj2;
    }

    if(isSameValue){
      testSuccess();
    } else{
      testFailed(NOT_SAME_VALUE);
    }

    return isSameValue;
  }
};

void Test::testSuccess(){
  printf("Test successful\n");
};

void Test::testFailed(TEST_ERRORS err){
  printf("Test failed");
  if(err == NOT_SAME_TYPE){
    printf(" Not same type\n");
  } else if(err == NOT_SAME_VALUE){
    printf(" Not same value\n");
  }
};

#endif
