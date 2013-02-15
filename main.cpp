#include "engine.h"
#include "object.h"
#include "map.h"
#include "screenobject.h"
#include "player.h"
#include "screens.h"
#include "monster.h"
#include "log.h"
#include "level.h"
#include "message.h"

#include <ncurses.h>
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>

using namespace std;

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
  ThingMaker tm;
  tm.initThings();
  init_monsters();
  initMapDrawingChars();
  
  shiplog("Going to title screen", 1);
  vis_cursor(0);
  title_screen();
  clear();
  
  shiplog("Getting name", 1);
  vis_cursor(1);
  string iname = get_pcname();
  clear();
  vis_cursor(0);
  
  shiplog("Getting origin world", 1);
  playerWorld w_choice = world_choice();
  clear();
  shiplog("Getting regiment choice", 1);
  playerCareer c_choice = career_choice();
  shiplog("Creating PC", 1);
  Player pc(iname, w_choice, c_choice, 11, 11, WHITE, '@'); //TODO: set player's location in a random empty bit of map
  clear();
  
  shiplog("Generating starting level", 1);
  LevelMap currentLevelMap(1, MAIN);
  currentLevelMap.generate(1, CORRIDORS);
  Level currentLevel(&currentLevelMap);

  // TEST OBJECTS
  Thing* lrw = tm.instantiate(LRW,10,12);
  Thing* srw = tm.instantiate(SRW,11,12);
  Thing* body = tm.instantiate(BODY,12,12);
  Thing* head = tm.instantiate(HEAD,13,12);
  Thing* leg = tm.instantiate(LEG,10,13);
  Thing* foot = tm.instantiate(FOOT,11,13);
  currentLevel.addObject(*lrw);
  currentLevel.addObject(*srw);
  currentLevel.addObject(*body);
  currentLevel.addObject(*head);
  currentLevel.addObject(*leg);
  currentLevel.addObject(*foot);
  
  printAll(currentLevel, pc);

  MessageLog msg;
  msg.print("You're inside.");
  
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
	if (c == 'h' || c == 'j' || c == 'k' || c == 'l' ||
		c == 'y' || c == 'u' || c == 'b' || c == 'n') {
	  direction dir;
	  switch (c) {
	  case 'h':
		dir = WEST; break;
	  case 'j':
		dir = SOUTH; break;
	  case 'k':
		dir = NORTH; break;
	  case 'l':
		dir = EAST; break;
	  case 'y':
		dir = NORTHWEST; break;
	  case 'u':
		dir = NORTHEAST; break;
	  case 'b':
		dir = SOUTHWEST; break;
	  case 'n':
		dir = SOUTHEAST; break;
	  }

	  if (pc.setLocation(dir, currentLevelMap) == 0) {
		msg.print("Bonk.");
	  } else {
		printMap(currentLevel, pc);
		int x = pc.getX();
		int y = pc.getY();
		unsigned int objectId = currentLevel.objectAt(x,y);
		if (objectId != 0) {
		  Thing t = currentLevel.getObject(objectId);
		  string s = "You see a ";
		  s.append(t.getName());
		  s.append(".");
		  msg.print(s);
		}
	  }
	}
	
	// pick up objects from the floor
	if (c == 'g') {
	  shiplog("Trying to pick up an object",50);
	  int* loc = pc.getLocation();
	  int x = *(loc);
	  int y = *(loc+1);

	  unsigned int id = currentLevel.objectAt(x, y); 
	  if (id != 0) {
		Thing& t = currentLevel.getObject(id);
		ostringstream oss;
		oss << "in main(), object id is " << t.getId();
		string s = oss.str();
		shiplog(s,50);
		pc.addToInv(t);
		currentLevel.delObject(id);
	  } else {
		msg.print("There's nothing here.");
	  }
	}
	
	// inventory screen
	if (c == 'i') {
	  if(pc.printInventory()) {
		msg.printCurrent();
		printAll(currentLevel, pc);
	  }
	}
	
	// Quit
	if (c == 'Q') { break; }
  }
  finish(0);
  
  return 1;
}
