// Functionality to print messages to the player in the top two lines of the scren

// TODO: -rolling message bar, there is currently no point
//       to having 2 lines.
//       -limit message to 48 chars, and scroll anything over
//        24 to the second line
//       -implement a message memory so you can switch between screens, and look at history

#include "message.h"
#include "engine.h"

using namespace std;

// print a message to the 2-line message bar at top of screen
void print_msg(const char* msg) {
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
void print_msg(string msg) {
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
