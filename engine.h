#ifndef SHIP_ENGINE
#define SHIP_ENGINE 1

#include "enums.h"

#include <string>


// The [x,y] location for an example 80x24 terminal work like this:
//
// Top leftmost location is [0,0]
// Top rightmost location is [79,0]
// Bottom leftmost location is [0,23]
// Bottom rightmost location is [79,23]

void init_for_draw(void);

void finish(int);

void write_char(int x, int y, char c, mapColor color);

void write_string(int x, int y, const char* s, mapColor color);

void write_line(int x, int y, int type, int length, char c, mapColor color);

void vis_cursor(int visibility);

void set_term_color(mapColor color);

void error_exit(std::string& msg);
void error_exit(const char* msg);

#endif
