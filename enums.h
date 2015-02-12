// enums
#ifndef SHIP_ENUMS
#define SHIP_ENUMS

enum levelFeature {
  BLANK,
  WALL,
  FLOOR,
  GRASS,
  USTAIR,
  DSTAIR,
  CDOOR,
  ODOOR
};

enum direction {
  NORTH,
  NORTHEAST,
  EAST,
  SOUTHEAST,
  SOUTH,
  SOUTHWEST,
  WEST,
  NORTHWEST
};

enum roomType {
  SQUARE,
  ROUND
};

enum levelType {
  CORRIDORS,
  FUEL_SEA,
  FOREST,
  CAVERN
};

enum mapColor { 
  RED = 0,
  GREEN = 1,
  CYAN = 2,
  L_GREY = 3,
  BROWN = 4,
  BLUE = 5,
  MAGENTA = 6,
  BLACK = 7,
  ORANGE = 8,
  L_GREEN = 9,
  L_CYAN = 10,
  WHITE = 11,
  YELLOW = 12,
  L_BLUE = 13,
  PINK = 14,
  D_GREY = 15
};

enum inventoryType {
  LRW = 0,  // ranged weapons
  SRW = 1,  // melee weapons
  BODY = 2, // body armour
  HEAD = 3, // headwear
  LEG = 4,  // legwear
  FOOT = 5  // footwear
};

enum playerWorld {
  EARTH,
  NEWBEIJING,
  SPARTA
};

enum playerCareer {
  COMMANDO,
  MEDIC,
  SAPPER,
  SCOUT,
  TECHNICIAN,
  HIGHCOMMAND
};

enum mapBranch {
  MAIN,
  REACTOR
};

#endif
