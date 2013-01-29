#ifndef SHIP_LOG
#define SHIP_LOG

#include <string>

void shiplog(std::string& message, int level);
void shiplog(const char* message, int level);
std::string dateString();

#endif
