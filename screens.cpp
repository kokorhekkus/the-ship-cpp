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
  write_char(5, 10, 'E', CYAN);
  write_string(7, 10, "ngineer", BLUE);
  
  for (int i=4; i<7; i++) {
	write_char(4, i, '[', RED);
	write_char(6, i, ']', RED);
  }
  write_char(6, 7, '[', RED);
  write_char(8, 7, ']', RED);
  for (int i=8; i<11; i++) {
	write_char(4, i, '[', RED);
	write_char(6, i, ']', RED);
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
  write_string(72, 3, "Str:", L_GREY);
  write_string(72, 5, "Int:", L_GREY);
  write_string(72, 7, "Con:", L_GREY);
  write_string(72, 9, "Dex:", L_GREY);
  write_string(72, 11, "Luc:", L_GREY);
  
  // bottom status line
  write_string(24, 23, "L:   /", L_GREY);
  write_string(34, 23, "C:   /", L_GREY);
  write_string(44, 23, "Spd:", L_GREY);
  write_string(53, 23, "Dmg:", L_GREY);
  write_string(60, 23, "A:  /", L_GREY);
  
  // top status line
  write_string(24, 22, "SRW:", L_GREY);
  write_string(53, 22, "LRW:", L_GREY);
  
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
void show_inventory(Player pc) {
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
