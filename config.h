#ifndef SHIP_CONFIG
#define SHIP_CONFIG 1

// The area we will be writing to; in essence, the minimum terminal size
const int xTerminalSize = 80;
const int yTerminalSize = 24;

// the area we can write the level map to, so the terminal size minus all
// the screen furniture around it
const int xMinMapSize = 0;
const int xMaxMapSize = 73;
const int yMinMapSize = 2;
const int yMaxMapSize = 22;

// max level of log lines to print
const int logLevel = 100;

#endif
