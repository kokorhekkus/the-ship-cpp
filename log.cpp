// Logging functionality

#include "log.h"

#include <fstream>

using namespace std;

string dateString() { 
  time_t now = time(0);    // current date/time based on current system
  string dt = ctime(&now); // convert to string
  dt.erase(dt.length()-1); // remove newline
  dt.append(":");
  return dt;
}

void shiplog(string& message, short int level) {
  std::ofstream logfile;
  logfile.open("TheShip.log", fstream::out | fstream::app);
  logfile << dateString() << level << ":" << message << endl;
  logfile.close();  
}
