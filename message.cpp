// Functionality to print messages to the player in the top two lines of the scren

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

// TODO: ensure message not too long for screen (80 chars per line,

// print a message to the 2-line message bar at top of screen
void MessageLog::print(const char* msg) {
  shiplog("->MessageLog::print (char*)",50);
  string s = msg;
  messages.push_back(s);
  if (messages.size() > numPlayerMsgs) {
	shiplog("deleting player message",70);
	messages.pop_front();
  }

  // blank message area
  write_string(0, 0, "                                                                                ", L_GREY);
  write_string(0, 1, "                                                                                ", L_GREY);

  // print this message on the bottom line
  write_string(0, 1, msg, L_GREY);
  // print last message at the top
  if (messages.size() > 1) {
	list<string>::iterator it = messages.end();
	it--; it--; // end() returns a past-of-end iterator,
	            // so decrement twice to get last message
	string msg2 = *it;
	const char* cmsg2 = msg2.c_str();
	write_string(0, 0, cmsg2, L_GREY);
  }
}
void MessageLog::print(string& msg) {
  shiplog("->MessageLog::print (string)",50);
  messages.push_back(msg);
  if (messages.size() > numPlayerMsgs) {
	shiplog("deleting player message",70);
	messages.pop_front();
  }

  // blank message area
  write_string(0, 0, "                                                                                ", L_GREY);
  write_string(0, 1, "                                                                                ", L_GREY);

  const char* cmsg = msg.c_str();
  // print this message on the bottom line
  write_string(0, 1, cmsg, L_GREY);
  // print last message at the top
  if (messages.size() > 1) {
	list<string>::iterator it = messages.end();
	it--; it--; // end() returns a past-of-end iterator,
	            // so decrement twice to get last message
	string msg2 = *it;
	const char* cmsg2 = msg2.c_str();
	write_string(0, 0, cmsg2, L_GREY);
  }
}
