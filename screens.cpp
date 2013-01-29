// Print out various screens available in the game

#include "engine.h"
#include "screens.h"
#include "enums.h"
#include "player.h" 

#include <ncurses.h>

using namespace std;

// title screen 
void title_screen() {
  write_string(36, 4, "The", L_BLUE);
  write_string(40, 4, "Ship", BLUE);
  
  write_string(27,6, "Press  Space  to continue", RED);
  write_char(33, 6, '[', BLUE);
  write_char(39, 6, ']', BLUE);
  
  char c = '\0';
  while (c != ' ') {
	c = getch();
  }
}

// character choice menu
playerWorld world_choice() {
  write_string(2, 2, "Choose your homeworld:", CYAN);
  
  write_char(5, 4, 'E', CYAN);
  write_string(7, 4, "arth (1.00G)", BLUE);
  write_char(5, 5, 'N', CYAN);
  write_string(7, 5, "ew Beijing (0.87G)", BLUE);
  write_char(5, 6, 'S', CYAN);
  write_string(7, 6, "parta (1.31G)", BLUE);
  
  for (int i=4; i<7; i++) {
	write_char(4, i, '[', RED);
	write_char(6, i, ']', RED);
  }
  
  char c = '\0';
  while (c != 'e' && c != 'E' && c != 'n' && c != 'N' && c != 's' && c != 'S') { 
	c = getch();
  }
	
  playerWorld pw;
  if (c == 'e' || c == 'E') {
	pw = EARTH;
  }
  if (c == 'n' || c == 'N') {
	pw = NEWBEIJING;
  }
  if (c == 's' || c == 'S') {
	pw = SPARTA;
  }
  return pw;
}

// career choice menu
playerCareer career_choice() {
  write_string(2, 2, "Choose your career:", CYAN);
  
  write_char(5, 4, 'C', CYAN);
  write_string(7, 4, "ommando", BLUE);
  write_char(5, 5, 'M', CYAN);
  write_string(7, 5, "edic", BLUE);
  write_char(5, 6, 'S', CYAN);
  write_string(7, 6, "apper", BLUE);
  write_string(4, 7, "Sc ", BLUE);
  write_char(7, 7, 'o', CYAN);
  write_string(9, 7, "ut", BLUE);
  write_char(5, 8, 'T', CYAN);
  write_string(7, 8, "echnician", BLUE);
  write_char(5, 9, 'H', CYAN);
  write_string(7, 9, "igh Command", BLUE);
  
  for (int i=4; i<7; i++) {
	write_char(4, i, '[', RED);
	write_char(6, i, ']', RED);
  }
  write_char(6, 7, '[', RED);
  write_char(8, 7, ']', RED);
  for (int i=8; i<10; i++) {
	write_char(4, i, '[', RED);
	write_char(6, i, ']', RED);
  }
  
  char c = '\0';
  while (c != 'c' && c != 'C' && c != 'm' && c != 'M'
		 && c != 's' && c != 'S' && c != 'o' && c != 'O'
		 && c != 't' && c != 'T' && c != 'h' && c != 'H') {
	c = getch();
  }

  playerCareer pc;
  if (c == 'C' || c == 'c') {
	pc = COMMANDO;
  }
  if (c == 'M' || c == 'm') {
	pc = MEDIC;
  }
  if (c == 'S' || c == 's') {
	pc = SAPPER;
  }
  if (c == 'O' || c == 'o') {
	pc =  SCOUT;
  }
  if (c == 'T' || c == 't') {
	pc = TECHNICIAN;
  }
  if (c == 'H' || c == 'h') {
	pc = HIGHCOMMAND;
  }
  return pc;
}

// create main game screen furniture;
// i.e. the stuff that doesn't ever change
void main_screen() {
  
  // Primary stats
  write_string(73, 3, "STR:", L_GREY);
  write_string(73, 5, "INT:", L_GREY);
  write_string(73, 7, "CON:", L_GREY);
  write_string(73, 9, "DEX:", L_GREY);
  write_string(73, 11, "LCK:", L_GREY);
  
  // bottom status line
  write_string(24, 23, "Life:   /", L_GREY);
  write_string(37, 23, "Level:", L_GREY);
  write_string(46, 23, "Speed:", L_GREY);
  write_string(55, 23, "Armour:", L_GREY);
  write_string(65, 23, "Dodge:", L_GREY);
  
  // top status line
  write_string(24, 22, "SRW:", L_GREY);
  write_string(53, 22, "LRW:", L_GREY);
}

// print a message to the 2-line message bar at top of screen
void print_msg(const char* msg) {
  // TODO: -rolling message bar, there is currently no point
  //       to having 2 lines.
  //       -limit message to 48 chars, and scroll anything over
  //        24 to the second line

  // blank message display
  write_string(0, 0, "                                   "
			   "                                   "
			   "         ", L_GREY);
  write_string(0, 1, "                                   "
			   "                                   "
			   "         ", L_GREY);
  // write new message
  write_string(0, 0, msg, L_GREY);
}

// screen to get player's name
string get_pcname() {
  write_string(8, 4, "Name yourself", CYAN);
  write_char(21, 4, ':', L_BLUE);
  write_char(22, 4, ' ', L_GREY);
  
  echo();

  char pc_name[23]   = {'\0'};
  if (getnstr(pc_name, 23) == ERR) {
	// TODO: terminate and print error message, don't allow it in the first place
  }
  noecho();
  
  return pc_name;
}

// show inventory screen; return to main screen
void show_inventory(const Player& pc) {
	clear();
	write_string(0,0,">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>",BLUE);
	write_string(35,0,"INVENTORY",RED);
	write_string(44,0,"<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<",BLUE);

	// TODO: actually print what's in the player inventory

	for (;;) {
		int c = getch();
		if (c == 'b') { break; }
	}
	clear();
	main_screen();
}
