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
  RED,
  GREEN,
  CYAN,
  L_GREY,
  BROWN,
  BLUE,
  MAGENTA,
  BLACK,
  ORANGE,
  L_GREEN,
  L_CYAN,
  WHITE,
  YELLOW,
  L_BLUE,
  PINK,
  D_GREY
};

enum inventoryType {
  LRW,  // ranged weapons
  SRW,  // melee weapons
  BODY, // body armour
  HEAD, // headwear
  LEG,  // legwear
  FOOT, // footwear
  AMMO, // ammunition
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
