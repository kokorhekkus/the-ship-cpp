// Print out various screens available in the game

#include "engine.h"
#include "screens.h"
#include "enums.h"
#include "player.h" 

#include <ncurses.h>

using namespace std;

// title screen 
void title_screen() {
  write_string(4, 36, "The", L_BLUE);
  write_string(4, 40, "Ship", BLUE);
  
  write_string(6, 27, "Press  Space  to continue", RED);
  write_char(6, 33, '[', BLUE);
  write_char(6, 39, ']', BLUE);
  
  char c = '\0';
  while (c != ' ') {
	c = getch();
  }
}

// character choice menu
playerWorld world_choice() {
  write_string(2, 2, "Choose your homeworld:", CYAN);
  
  write_char(4, 5, 'E', CYAN);
  write_string(4, 7, "arth (1.00G)", BLUE);
  write_char(5, 5, 'N', CYAN);
  write_string(5, 7, "ew Beijing (0.87G)", BLUE);
  write_char(6, 5, 'S', CYAN);
  write_string(6, 7, "parta (1.31G)", BLUE);
  
  for (int i=4; i<7; i++) {
	write_char(i, 4, '[', RED);
	write_char(i, 6, ']', RED);
  }
  
  for (;;) {
	char c = getch();
	
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
}

// career choice menu
playerCareer career_choice() {
  write_string(2, 2, "Choose your career:", CYAN);
  
  write_char(4, 5, 'C', CYAN);
  write_string(4, 7, "ommando", BLUE);
  write_char(5, 5, 'M', CYAN);
  write_string(5, 7, "edic", BLUE);
  write_char(6, 5, 'S', CYAN);
  write_string(6, 7, "apper", BLUE);
  write_string(7, 4, "Sc ", BLUE);
  write_char(7, 7, 'o', CYAN);
  write_string(7, 9, "ut", BLUE);
  write_char(8, 5, 'T', CYAN);
  write_string(8, 7, "echnician", BLUE);
  write_char(9, 5, 'H', CYAN);
  write_string(9, 7, "igh Command", BLUE);
  write_char(10, 5, 'E', CYAN);
  write_string(10, 7, "ngineer", BLUE);
  
  for (int i=4; i<7; i++) {
	write_char(i, 4, '[', RED);
	write_char(i, 6, ']', RED);
  }
  write_char(7, 6, '[', RED);
  write_char(7, 8, ']', RED);
  for (int i=8; i<11; i++) {
	write_char(i, 4, '[', RED);
	write_char(i, 6, ']', RED);
  }
  
  for (;;) {
	char c = getch();
	
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
	if (c == 'E' || c == 'e') {
	  pc = ENGINEER;
	}
	return pc;
  }
}

// create main game screen
void main_screen() {
   // Stuff that doesn't ever change
  
  // Primary stats
  write_string(3, 72, "Str:", L_GREY);
  write_string(5, 72, "Int:", L_GREY);
  write_string(7, 72, "Con:", L_GREY);
  write_string(9, 72, "Dex:", L_GREY);
  write_string(11, 72, "Luc:", L_GREY);
  
  // bottom status line
  write_string(24, 24, "L:   /", L_GREY);
  write_string(24, 34, "C:   /", L_GREY);
  write_string(24, 44, "Spd:", L_GREY);
  write_string(24, 53, "Dmg:", L_GREY);
  write_string(24, 60, "A:  /", L_GREY);
  
  // top status line
  write_string(23, 24, "SRW:", L_GREY);
  write_string(23, 53, "LRW:", L_GREY);
  
  // TODO: print stuff that changes
  //print_stats();   print_2stats();
  //print_weapons(); print_name();
  //print_status();
  //print_map();
  //print_pc();
}

// print a message to the 2-line message bar at top of screen
void print_msg(const char* msg) {
  // blank message display
  write_string(0, 0, "                                   "
			   "                                   "
			   "         ", L_GREY);
  write_string(1, 0, "                                   "
			   "                                   "
			   "         ", L_GREY);
  // write new message
  write_string(0, 0, msg, L_GREY);
}

// screen to get player's name
string get_pcname() {
  write_string(4, 8, "Name yourself", CYAN);
  write_char(4, 21, ':', L_BLUE);
  write_char(4, 22, ' ', L_GREY);
  
  echo();

  char pc_name[23]   = {'\0'};
  if (getnstr(pc_name, 23) == ERR) {
	// TODO: terminate and print error message, don't allow it in the first place
  }
  noecho();
  
  return pc_name;
}

// show inventory screen; return to main screen
void show_inventory(Player pc) {
	clear();
	write_string(0,0,">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>",BLUE);
	write_string(0,35,"INVENTORY",RED);
	write_string(0,44,"<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<",BLUE);

	// TODO: actually print what's in the player inventory

	for (;;) {
		int c = getch();
		if (c == 'b') { break; }
	}
	clear();
	main_screen();
}
