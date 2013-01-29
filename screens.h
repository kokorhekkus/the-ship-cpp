#ifndef SHIP_SCREENS
#define SHIP_SCREENS 1

#include "player.h"

#include <string>

void title_screen();

playerWorld world_choice();

playerCareer career_choice();

void main_screen();

void print_msg(const char* msg);

std::string get_pcname();

void show_inventory(const Player& pc);

#endif
