#ifndef SHIP_MESSAGE
#define SHIP_MESSAGE 1

#include <string>
#include <list>

class MessageLog {
private:
  std::list<std::string> messages;

public:
  MessageLog();
  ~MessageLog();

  void print(const char* msg);
  void print(std::string& msg);
};

#endif
