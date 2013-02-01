#include "engine.h"
#include "object.h"
#include "map.h"
#include "base.h"
#include "player.h"
#include "screens.h"
#include "monster.h"
#include "log.h"
#include "level.h"

#include <ncurses.h>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

// use this to assign a unique serial number to game objects
unsigned int objectSerial = 0;
unsigned int getSerial() {
  objectSerial++;
  return objectSerial;
}

// prints out the main game screen
void printAll(const Level& level, const Player& pc) {
  main_screen();
  level.print();
  pc.printMainScreenInfo();
  pc.print();
}

// just print the map area
// TODO: add monster movement and LOS
void printMap(const Level& level, const Player& pc) {
  level.print();
  pc.print();
}

//----------------------------------------------------------------------
//                              MAIN
//----------------------------------------------------------------------
int main(int argc, char *argv[]) {
  srand(time(0));      // init random seed
  
  shiplog("Initialising", 1);
  // init, and enter game loop checking for keyboard input
  init_for_draw();
  init_objects();
  init_monsters();
  initMapDrawingChars();
  
  shiplog("Going to title screen", 1);
  vis_cursor(0);
  title_screen();
  clear();
  
  shiplog("Getting name", 1);
  vis_cursor(1);
  string iname = get_pcname();
  char* name = (char*)iname.c_str(); // convert to character array
  clear();
  vis_cursor(0);
  
  shiplog("Getting origin world", 1);
  playerWorld w_choice = world_choice();
  clear();
  shiplog("Getting regiment choice", 1);
  playerCareer c_choice = career_choice();
  shiplog("Creating PC", 1);
  Player pc(name, w_choice, c_choice, 11, 11, WHITE, '@'); //TODO: set player's location in a random empty bit of map
  clear();
  
  shiplog("Generating starting level", 1);
  LevelMap currentLevelMap(1, MAIN);
  currentLevelMap.generate(1, CORRIDORS);
  Level currentLevel(&currentLevelMap);

  // TEST: generate an object on the level to test picking up and inventory
  string gunName = "sharplight projector";
  Gun sharpie(getSerial(),gunName,1,11,12,BLUE,'/',5,5,1,6);
  currentLevel.addObject(sharpie);
  
  printAll(currentLevel, pc);

  print_msg("You're inside.");
  
  shiplog("Entering main game loop", 1);
  while (1) {
	// get curses terminal keyboard input
	char c = getch();
	
	// color test
	if (c == 'c') {
	  save_screen("scrtocol.tdd");
	  clear();
	  write_line(4,30,1,20,'r',RED);
	  write_line(5,30,1,20,'g',GREEN);
	  write_line(6,30,1,20,'c',CYAN);
	  write_line(7,30,1,20,'g',L_GREY);
	  write_line(8,30,1,20,'b',BROWN);
	  write_line(9,30,1,20,'b',BLUE);
	  write_line(10,30,1,20,'m',MAGENTA);
	  write_line(11,30,1,20,'b',BLACK);
	  write_line(12,30,1,20,'o',ORANGE);
	  write_line(13,30,1,20,'g',L_GREEN);
	  write_line(14,30,1,20,'c',L_CYAN);
	  write_line(15,30,1,20,'w',WHITE);
	  write_line(16,30,1,20,'y',YELLOW);
	  write_line(17,30,1,20,'b',L_BLUE);
	  write_line(18,30,1,20,'p',PINK);
	  write_line(19,30,1,20,'g',D_GREY);
	}
	if (c == 'C') {
	  clear();
	  restore_screen("scrtocol.tdd");
	}
	
	// vi-like movement keys
	//
	// TODO: Sort out numpad & cursor keys
	// TODO: Handle more failures to move than just hitting
	//       a wall
	// TODO: make code generic so we don't repeat all these lines
	if (c == 'h')  {
	  if (pc.setLocation(WEST, currentLevelMap) == 0) {
		print_msg("Bonk.");
	  } else {
		printMap(currentLevel, pc);
	  }
	}
	if (c == 'j') {
	  if (pc.setLocation(SOUTH, currentLevelMap) == 0) {
		print_msg("Bonk.");
	  } else {
		printMap(currentLevel, pc);
	  }
	}
	if (c == 'k') {
	  if (pc.setLocation(NORTH, currentLevelMap) == 0) {
		print_msg("Bonk.");
	  } else {
		printMap(currentLevel, pc);
	  }
	}
	if (c == 'l') {
	  if (pc.setLocation(EAST, currentLevelMap) == 0) {
		print_msg("Bonk.");
	  } else {
		printMap(currentLevel, pc);
	  }
	}
	if (c == 'y') {
	  if (pc.setLocation(NORTHWEST, currentLevelMap) == 0) {
		print_msg("Bonk.");
	  } else {
		printMap(currentLevel, pc);
	  }
	}
	if (c == 'u') {
	  if (pc.setLocation(NORTHEAST, currentLevelMap) == 0) {
		print_msg("Bonk.");
	  } else {
		printMap(currentLevel, pc);
	  }
	}
	if (c == 'b') {
	  if (pc.setLocation(SOUTHWEST, currentLevelMap) == 0) {
		print_msg("Bonk.");
	  } else {
		printMap(currentLevel, pc);
	  }
	}
	if (c == 'n') {
	  if (pc.setLocation(SOUTHEAST, currentLevelMap) == 0) {
		print_msg("Bonk.");
	  } else {
		printMap(currentLevel, pc);
	  }
	}
	
	// pick up objects from the floor
	if (c == ',') {
	  
	}
	
	// inventory screen
	if (c == 'i') {
	  show_inventory(pc);
	}
	
	// Quit
	if (c == 'Q') { break; }
  }
  finish(0);
  
  return 1;
}
