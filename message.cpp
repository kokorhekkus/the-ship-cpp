// Functionality to print messages to the player in the top two lines of the scren

// TODO: -rolling message bar, there is currently no point
//       to having 2 lines.
//       -limit message to 48 chars, and scroll anything over
//        24 to the second line
//       -implement a message memory so you can switch between screens, and look at history

#include "message.h"
#include "engine.h"
#include "log.h"
#include "config.h"

using namespace std;

MessageLog::MessageLog() {
  shiplog("Creating a MessageLog object",5);
}
MessageLog::~MessageLog() {
  shiplog("Destroying a MessageLog object",5);
}

// print a message to the 2-line message bar at top of screen
void MessageLog::print(const char* msg) {
  string s = msg;
  messages.push_back(s);
  if (messages.size() > numPlayerMsgs) {
	messages.pop_front();
  }

  // blank message display
  write_string(0, 0, "                                   "
			   "                                   "
			   "         ", L_GREY);
  write_string(0, 1, "                                   "
			   "                                   "
			   "         ", L_GREY);
  // write new message
  write_string(0, 0, msg, L_GREY);
}
void MessageLog::print(string& msg) {
  messages.push_back(msg);
  if (messages.size() > numPlayerMsgs) {
	messages.pop_front();
  }

  const char* cmsg = msg.c_str();
  // blank message display
  write_string(0, 0, "                                   "
			   "                                   "
			   "         ", L_GREY);
  write_string(0, 1, "                                   "
			   "                                   "
			   "         ", L_GREY);
  // write new message
  write_string(0, 0, cmsg, L_GREY);
}
