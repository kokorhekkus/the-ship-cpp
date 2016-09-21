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

// print the screen
//   print_all: if TRUE, print whole screen, if FALSE only print map area
void printScreen(const Level& level, const Player& pc, bool print_all) {
	level.print();
	pc.print();

	if (print_all) {
		main_screen();
		pc.printMainScreenInfo();
	}
}

//----------------------------------------------------------------------
//                              MAIN
//----------------------------------------------------------------------
int main(int argc, char *argv[]) {
	shiplog("Initialising", 1);
	// init, and enter game loop checking for keyboard input
	init_for_draw();
	init_monsters();
	initMapDrawingChars();

	shiplog("Going to title screen", 1);
	vis_cursor(0);
	title_screen();
	clear();

	// TODO: check for savegame

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

	shiplog("Generating starting level", 1);
	LevelMap currentLevelMap(1, MAIN);
	currentLevelMap.generate(1, CAVERN);
	Level currentLevel(&currentLevelMap);
  currentLevel.addFloorItems(2);
  currentLevel.addLevelMonsters();

	shiplog("Creating PC", 1);
	Location startLoc = currentLevel.findEmptyLocation();
	Player pc(iname, w_choice, c_choice, startLoc.x, startLoc.y, WHITE, '@');

	clear();
	printScreen(currentLevel, pc, TRUE);

	MessageLog msg;
	msg.print("You're inside.");
  
	shiplog("Entering main game loop", 1);
	while (1) {
	// get curses terminal keyboard input
  	char c = getch();

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
  		printScreen(currentLevel, pc, FALSE);
      Location loc = pc.getLocation();
  		unsigned int objectId = currentLevel.objectAt(loc.x,loc.y);
  		if (objectId != 0) {
  			Thing t = currentLevel.getObject(objectId);
  			string s = "You see ";
  			string name = t.getName();
  			if (name[0] == 'a' || name[0] == 'e' || name[0] == 'i' || name[0] == 'o' || name[0] == 'u') {
  				s.append("an ");
  			} else {
  				s.append("a ");
  			}
  			s.append(name);
  			s.append(".");
  			msg.print(s);
  		}
  	}
  }

	// pick up objects from the floor
  if (c == 'g') {
  	shiplog("Trying to pick up an object",50);
  	Location loc = pc.getLocation();

  	unsigned int id = currentLevel.objectAt(loc.x, loc.y); 
  	if (id != 0) {
  		Thing& t = currentLevel.getObject(id);
  		ostringstream oss;
  		oss << "in main(), object id is " << t.getId();
  		string s = oss.str();
  		shiplog(s,50);
  		if (pc.addToInv(t)) {
  			currentLevel.delObject(id);
  		} else {
  			msg.print("Your inventory is full- drop something.");
  		}
  	} else {
  		msg.print("There's nothing here.");
  	}
  }

	// inventory screen
  if (c == 'i') {
  	if (pc.printInventory()) {
  		msg.printCurrent();
  		printScreen(currentLevel, pc, TRUE);
  	} else {
		// currently only return is 0 for no items
  		msg.print("You have no items in your inventory.");
  	}
  }

	// Quit
	// TODO: Confirmation dialog
  if (c == 'Q') { break; }
}
finish(0);

return 1;
}