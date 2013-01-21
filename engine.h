#ifndef SHIP_ENGINE
#define SHIP_ENGINE 1

#include "enums.h"

#include <string>

void init_for_draw(void);

void finish(int);

void write_char(int x, int y, char c, mapColor color);

void write_string(int x, int y, const char* s, mapColor color);

void write_line(int x, int y, int type, int length, char c, mapColor color);

void save_screen(const char *filepath);

void restore_screen(const char *filepath);

void vis_cursor(int visibility);

void set_term_color(mapColor color);

void error_exit(std::string& msg);

#endif
