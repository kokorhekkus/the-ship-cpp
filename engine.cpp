/*
 * Engine function definitions
 * -these are the platform-dependent functions
 */

#include "engine.h"
#include "log.h"
#include <ncurses.h>
#include <string>
#include <cstdlib>
#include <csignal>
#include <iostream>
using namespace std;

// initialise ncurses and colors, for drawing the game screen
// -includes signal processing
void init_for_draw(void) {
  shiplog("Initialising ncurses...",1);
  signal(SIGINT, finish); // init for finish()
  
  // check for and make the neccesary files and folders
  
  // ncurses init stuff */
  initscr();
  // TODO: CHECK FOR STDSCR !< 80x24 (int LINES,COLS)
  cbreak();
  nonl();
  noecho();
  intrflush(stdscr, FALSE);
  keypad(stdscr, TRUE);

  if (has_colors()) {
	start_color();
	
	// Set up 8 colors (16 with BOLDing) 
	init_pair(1, COLOR_RED,     COLOR_BLACK);
	init_pair(2, COLOR_GREEN,   COLOR_BLACK);
	init_pair(3, COLOR_CYAN,    COLOR_BLACK);
	init_pair(4, COLOR_WHITE,   COLOR_BLACK);
	init_pair(5, COLOR_YELLOW,  COLOR_BLACK);
	init_pair(6, COLOR_BLUE,    COLOR_BLACK);
	init_pair(7, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(8, COLOR_BLACK,   COLOR_BLACK);
  }
}

// write a character, 'c', to the co-ords (x,y) with color 'color' 
void write_char(int x, int y, char c, mapColor color) {
	chtype ch = c;
	
	set_term_color(color);
	mvaddch(y,x,ch);
}

// write a string, 's', to the co-ords (x,y) with color 'color'
void write_string(int x, int y, const char* s, mapColor color) {
  set_term_color(color);
  string ss = s;
  int s_len = ss.length();
  
  for (int i=0; i < s_len; i++) {
	chtype ch = s[i];
	mvaddch(y,x+i,ch);
  }
}

// write a line of color 'color' and length 'length' starting at (x,y)
// 'type' is 1 - horizontal, 2 - vertical
void write_line(int x, int y, int type, int length, char c, mapColor color) {
  int i;
  chtype ch = c;
  
  set_term_color(color);

  for (i=0;i<length;i++) {
	 if (type == 1) {
	   mvaddch(y,x+i,ch);
	 }
	 if (type == 2) {
	   mvaddch(y+i,x,ch);
	 }
  }
}

// finish up, get rid of 'stdscr'
void finish(int sig) {
  endwin();
  cout << endl << "Terminated with signal " << sig << endl << endl;
  cout << "The Ship Version 0.1" << endl;
  cout << "(C) Copyright 2013 Karim Rashad" << endl;
  cout << "All Rights Reserved" << endl << endl;
  exit(0);
}

// makes cursor appear or disappear: 1 - visible, 0 - not visible
void vis_cursor(int visibility) {
  int v;
  
  if (visibility) {
	v = curs_set(1);
  } else {
	v = curs_set(0);
  }
}

// set the video color attribute of a terminal once
void set_term_color(mapColor color) {

  if (color == RED) {
	attrset(COLOR_PAIR(1));
  }
  if (color == GREEN) {
	attrset(COLOR_PAIR(2));
  }
  if (color == CYAN) {
	attrset(COLOR_PAIR(3));
  }
  if (color == L_GREY) {
	attrset(COLOR_PAIR(4));
  }
  if (color == BROWN) {
	attrset(COLOR_PAIR(5));
  }
  if (color == BLUE) {
	attrset(COLOR_PAIR(6));
  }
  if (color == MAGENTA) {
	attrset(COLOR_PAIR(7));
  }
  if (color == BLACK) {
	attrset(COLOR_PAIR(8));
  }
  if (color == ORANGE) {
	attrset(COLOR_PAIR(1) | A_BOLD);
  }
  if (color == L_GREEN) {
	attrset(COLOR_PAIR(2) | A_BOLD);
  }
  if (color == L_CYAN) {
	attrset(COLOR_PAIR(3) | A_BOLD);
  }
  if (color == WHITE) {
	attrset(COLOR_PAIR(4) | A_BOLD);
  }
  if (color == YELLOW) {
	attrset(COLOR_PAIR(5) | A_BOLD);
  }
  if (color == L_BLUE) {
	attrset(COLOR_PAIR(6) | A_BOLD);
  }
  if (color == PINK) {
	attrset(COLOR_PAIR(7) | A_BOLD);
  }
  if (color == D_GREY) {
	attrset(COLOR_PAIR(8) | A_BOLD);
  }
}


// exit program and print an error message 
void error_exit(string& msg) {
  endwin();
  cout << "*******************************************************************************" << endl;
  cout << "* THE_SHIP ERROR:" << endl << msg << endl;
  cout << "*******************************************************************************" << endl;
  exit(0);
}
void error_exit(const char* msg) {
  endwin();
  cout << "*******************************************************************************" << endl;
  cout << "* THE_SHIP ERROR:" << endl << msg << endl;
  cout << "*******************************************************************************" << endl;
  exit(0);
}
