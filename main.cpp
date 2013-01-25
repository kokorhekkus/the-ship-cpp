#include "engine.h"
#include "object.h"
#include "map.h"
#include "base.h"
#include "player.h"
#include "screens.h"
#include "monster.h"
#include "log.h"

#include <ncurses.h>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

// prints out the main game screen
void print_all(LevelMap lm, Player pc) {
  main_screen();
  lm.print();
  pc.printMainScreenInfo();
  pc.print();
}

//----------------------------------------------------------------------
//                              MAIN
//----------------------------------------------------------------------
int main(int argc, char *argv[]) {
  srand(time(0));      // init random seed
  
  string s = "Initialising";
  shiplog(s, 1);
  // init, and enter game loop checking for keyboard input
  init_for_draw();
  init_objects();
  init_monsters();
  initMapDrawingChars();
  
  s = "Going to title screen"; 
  shiplog(s, 1);
  vis_cursor(0);
  title_screen();
  clear();
  
  s = "Getting name";
  shiplog(s, 1);
  vis_cursor(1);
  string iname = get_pcname();
  char* name = (char*)iname.c_str(); // convert to character array
  clear();
  vis_cursor(0);
  
  s = "Getting origin world";
  shiplog(s, 1);
  playerWorld w_choice = world_choice();
  clear();
  s = "Getting regiment choice";
  shiplog(s, 1);
  playerCareer c_choice = career_choice();
  s = "Creating PC";
  shiplog(s, 1);
  Player pc(name, w_choice, c_choice, 0, 0, WHITE, '@');
  clear();
  
  s = "Generating starting level";
  shiplog(s, 1);
  LevelMap currentLevel;
  currentLevel.generate(1, CORRIDORS);
  pc.setLocation(11,11); // just an initial test
  print_all(currentLevel, pc);
  print_msg("You're inside.");
  
  s = "Entering main game loop";
  shiplog(s, 1);
  while (1) {
	// get keyb input
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
	
	// Rogue-like movement keys & cursor keys
	//
	// TODO: Handle more failures to mvoe than just hitting
	//       a wall
	// TODO: make code generic so we don't repeat all these lines
	if (c == 'h')  {
	  if (pc.setLocation(WEST, currentLevel) == 0) {
		print_msg("Bonk.");
	  }
	}
	if (c == 'j') {
	  if (pc.setLocation(SOUTH, currentLevel) == 0) {
		print_msg("Bonk.");
	  }
	}
	if (c == 'k') {
	  if (pc.setLocation(NORTH, currentLevel) == 0) {
		print_msg("Bonk.");
	  }
	}
	if (c == 'l') {
	  if (pc.setLocation(EAST, currentLevel) == 0) {
		print_msg("Bonk.");
	  }
	}
	if (c == 'y') {
	  if (pc.setLocation(NORTHWEST, currentLevel) == 0) {
		print_msg("Bonk.");
	  }
	}
	if (c == 'u') {
	  if (pc.setLocation(NORTHEAST, currentLevel) == 0) {
		print_msg("Bonk.");
	  }
	}
	if (c == 'b') {
	  if (pc.setLocation(SOUTHWEST, currentLevel) == 0) {
		print_msg("Bonk.");
	  }
	}
	if (c == 'n') {
	  if (pc.setLocation(SOUTHEAST, currentLevel) == 0) {
		print_msg("Bonk.");
	  }
	}
	
	// pick up objects from the floor
	if (c == ',') {
	  
	}
	
	// Inventory screen
	if (c == 'i') {
	  show_inventory(pc);
	}
	
	// Quit
	if (c == 'Q') { break; }
  }
  finish(0);
  
  return 1;
}
