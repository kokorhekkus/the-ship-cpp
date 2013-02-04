#ifndef SHIP_SCREENS
#define SHIP_SCREENS 1

#include "player.h"

#include <string>

void title_screen();

playerWorld world_choice();

playerCareer career_choice();

void main_screen();

std::string get_pcname();

// returns true on player wanting to return to main game screen
bool show_inventory(const Player& pc);

#endif
