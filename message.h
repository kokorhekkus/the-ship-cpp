#ifndef SHIP_MESSAGE
#define SHIP_MESSAGE 1

#include <string>
#include <list>

class MessageLog {
private:
  std::list<std::string> messages;
  void blankDisplay();

public:
  MessageLog();
  ~MessageLog();

  // print new player messages
  void print(const char* msg);
  void print(std::string& msg);

  // print the current state (e.g. last two messages)
  void printCurrent();
};

#endif
