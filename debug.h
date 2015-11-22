#include <string>

enum DEBUG_LEVEL{
  ERROR = 1,
  INFO  = 2,
  DEBUG = 3
};

class Debug{
  private:
    char* getTime();
  public:
    void print(std::string, DEBUG_LEVEL);
};
