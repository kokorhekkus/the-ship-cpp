// The Player Character

#include "player.h"
#include "log.h"
#include "engine.h"
#include "random.h"

#include <ncurses.h>

#include <sstream>
#include <iostream>
#include <cmath>

using namespace std;

//----------------------------------------------------------------------
// Player class implementation
//----------------------------------------------------------------------

// Constructor that sets all Player variables
Player::Player(char* a_name, playerWorld a_world, playerCareer a_career,
			   int xloc, int yloc, 
			   mapColor color, char look) :
  name(a_name), world(a_world), career(a_career),
  ScreenObject(xloc, yloc, color, look) {

  shiplog("Creating new Player object", 10);

  // set up XP calculation array
  for (int i=1; i<100; i++) {
	if (i<=10) {
	  xpCalcArray[i] = i*100;
	}
	if (i>10 || i<=50) {
	  xpCalcArray[i] = i*1000;
	}
	if (i>50 || i<=99) {
	  xpCalcArray[i] = i*5000;
	}
  }
  
  genPrimaryStats();
  // TODO: generate starting inventory
  calcSecondaryStats();
  // set starting HP here
  hp = max_hp;
}
Player::~Player() {
  shiplog("Destroying Player object", 10);
}

// Getters
char* Player::getName() const { return name; }
playerWorld Player::getWorld() const { return world; }
playerCareer Player::getCareer() const { return career; }
int Player::getStrength() const { return strength; }
int Player::getIntelligence() const { return intelligence; }
int Player::getConstitution() const { return constitution; }
int Player::getDexterity() const { return dexterity; }
int Player::getLuck() const { return luck; }
int Player::getXP() const { return xp; }
int Player::getHP() const { return hp; }
int Player::getMaxHP() const { return max_hp; }
int Player::getArmour() const { return armour; }
int Player::getSpeed() const { return speed; }
int Player::getDodge() const { return dodge; }

// Setters
void Player::setStrength(int new_strength) {
  if (checkStatRange(new_strength,1,50)) {
	strength = new_strength;
	calcSecondaryStats();
  } else {
	ostringstream os;
	os << "STR not in range 1-50, is " << new_strength << ", not setting";
	string msg = os.str();
	shiplog(msg,5);
  }
}
void Player::setIntelligence(int new_intelligence) {
  if (checkStatRange(new_intelligence,1,50)) {
	intelligence = new_intelligence;
	calcSecondaryStats();
  } else {
	ostringstream os;
	os << "INT not in range 1-50, is " << new_intelligence << ", not setting";
	string msg = os.str();
	shiplog(msg,5);
  }
}
void Player::setConstitution(int new_constitution) {
  if (checkStatRange(new_constitution,1,50)) {
	constitution = new_constitution;
	calcSecondaryStats();
  } else {
	ostringstream os;
	os << "CON not in range 1-50, is " << new_constitution << ", not setting";
	string msg = os.str();
	shiplog(msg,5);
  }
}
void Player::setDexterity(int new_dexterity) {
  if (checkStatRange(new_dexterity,1,50)) {
	dexterity = new_dexterity;
	calcSecondaryStats();
  } else {
	ostringstream os;
	os << "DEX not in range 1-50, is " << new_dexterity << ", not setting";
	string msg = os.str();
	shiplog(msg,5);
  }
}
void Player::setLuck(int new_luck) {
  if (checkStatRange(new_luck,1,50)) {
	luck = new_luck;
	calcSecondaryStats();
  } else {
	ostringstream os;
	os << "LCK not in range 1-50, is " << new_luck << ", not setting";
	string msg = os.str();
	shiplog(msg,5);
  }
}
void Player::addXP(int add_xp) {
  int new_xp = xp + add_xp;
  if (checkStatRange(new_xp,1,495000)) {
	xp = new_xp;
	calcSecondaryStats();
  } else {
	ostringstream os;
	os << "XP not in range 1 - 495000, is " << new_xp << ", not setting";
	string msg = os.str();
	shiplog(msg,5);
  }
}
void Player::setHP(int new_hp) {
  if (checkStatRange(new_hp,1,max_hp)) {
	hp = new_hp;
  } else {
	// TODO: handle death when hp goes below 1
  }
}
void Player::setMaxHP(int new_max_hp) {
  if (checkStatRange(new_max_hp,1,999)) {
	max_hp = new_max_hp;
  } else {
	ostringstream os;
	os << "Max HP not in range 1-999, is " << new_max_hp << ", not setting";
	string msg = os.str();
	shiplog(msg,5);
  }
}
void Player::setArmour(int new_armour) {
  if (checkStatRange(new_armour,0,99)) {
	armour = new_armour;
  } else {
	ostringstream os;
	os << "Armour not in range 1-99, is " << new_armour << ", not setting";
	string msg = os.str();
	shiplog(msg,5);
  }
}
void Player::setSpeed(int new_speed) {
  if (checkStatRange(new_speed,0,99)) {
	speed = new_speed;
  } else {
	ostringstream os;
	os << "Speed not in range 1-99, is " << new_speed << ", not setting";
	string msg = os.str();
	shiplog(msg,5);
  }
}
void Player::setDodge(int new_dodge) {
  if (checkStatRange(new_dodge,0,99)) {
	dodge = new_dodge;
  } else {
	ostringstream os;
	os << "Dodge not in range 1-99, is " << new_dodge << ", not setting";
	string msg = os.str();
	shiplog(msg,5);
  }
}
 
string Player::itos(int i) const {
   stringstream ss;
   ss << i;
   return ss.str();
}

void Player::printMainScreenInfo() const {

  // Primary stats
  string s = itos(strength);
  char* sc = (char*)s.c_str(); 
  write_string(77, 3, sc, L_BLUE);

  s = itos(intelligence);
  sc = (char*)s.c_str(); 
  write_string(77, 5, sc, L_BLUE);

  s = itos(constitution);
  sc = (char*)s.c_str(); 
  write_string(77, 7, sc, L_BLUE);

  s = itos(dexterity);
  sc = (char*)s.c_str(); 
  write_string(77, 9, sc, L_BLUE);

  s = itos(luck);
  sc = (char*)s.c_str(); 
  write_string(77, 11, sc, L_BLUE);

  // Secondary stats
  s = itos(hp);
  sc = (char*)s.c_str(); 
  write_string(29, 23, sc, L_BLUE);

  s = itos(max_hp);
  sc = (char*)s.c_str(); 
  write_string(33, 23, sc, L_BLUE);

  s = itos(xp_level);
  sc = (char*)s.c_str(); 
  write_string(43, 23, sc, L_BLUE);

  s = itos(speed);
  sc = (char*)s.c_str(); 
  write_string(52, 23, sc, L_BLUE);

  s = itos(armour);
  sc = (char*)s.c_str(); 
  write_string(62, 23, sc, L_BLUE);

  s = itos(dodge);
  sc = (char*)s.c_str(); 
  write_string(71, 23, sc, L_BLUE);

  // Print name
  write_string(0, 22, name, MAGENTA);
  
  s = title();
  sc = (char*)s.c_str();
  write_string(0, 23, sc, MAGENTA);
}

// TODO: -Change title based on experience
//       -Ensure a limit of 28 characters
string Player::title() const {
  string title;
  
  switch(world) {
  case EARTH:
	title.append("Terran ");
	break;
  case NEWBEIJING:
	title.append("Beijinger ");
	break;
  case SPARTA:
	title.append("Spartan ");
	break;
  }

  switch(career) {
  case COMMANDO:
	title.append("Commando");
	break;
  case MEDIC:
	title.append("Medic");
	break;
  case SAPPER:
	title.append("Sapper");
	break;
  case SCOUT:
	title.append("Scout");
	break;
  case TECHNICIAN:
	title.append("Technician");
	break;
  case HIGHCOMMAND:
	title.append("General");
	break;
  }

  return title;
} 

void Player::genPrimaryStats() {
  // called once in constructor, so set initial XP
  xp = 0;
  // set base stats

  // -an initial 50 points allocated
  // -intelligence and luck always start off as 10
  switch(world) {
  case EARTH:
	setStrength(10);
	setIntelligence(10);
	setConstitution(10);
	setDexterity(10);
	setLuck(10);
	break;
  case NEWBEIJING:
	setStrength(8);
	setIntelligence(10);
	setConstitution(8);
	setDexterity(14);
	setLuck(10);
	break;
  case SPARTA:
	setStrength(12);
	setIntelligence(10);
	setConstitution(12);
	setDexterity(6);
	setLuck(10);
	break;
  }
  
  // the modifiers for career end up adding 2 points
  switch(career) {
  case COMMANDO:
	setStrength(strength+1);
	setIntelligence(intelligence-2);
	setConstitution(constitution+3);
	setDexterity(dexterity);
	setLuck(luck);
	break;
  case MEDIC:
	setStrength(strength-1);
	setIntelligence(intelligence+3);
	setConstitution(constitution-1);
	setDexterity(dexterity+1);
	setLuck(luck);
	break;
  case SAPPER:
	setStrength(strength+2);
	setIntelligence(intelligence-1);
	setConstitution(constitution+1);
	setDexterity(dexterity);
	setLuck(luck-1);
	break;
  case SCOUT:
	setStrength(strength-2);
	setIntelligence(intelligence);
	setConstitution(constitution-1);
	setDexterity(dexterity+2);
	setLuck(luck+3);
	break;
  case TECHNICIAN:
	setStrength(strength-3);
	setIntelligence(intelligence+3);
	setConstitution(constitution-1);
	setDexterity(dexterity+3);
	setLuck(luck);
	break;
  case HIGHCOMMAND:
	setStrength(strength-1);
	setIntelligence(intelligence+2);
	setConstitution(constitution-1);
	setDexterity(dexterity-1);
	setLuck(luck+3);
	break;
  }

  // do some very minimal randomising:
  // small chance of adding or subtracting 1 to each stat
    if (percentChance(10)) {
	if (percentChance(50)) {
	  setStrength(strength+1);
	} else {
	  setStrength(strength-1);
	}
  }
  if (percentChance(10)) {
	if (percentChance(50)) {
	  setIntelligence(intelligence+1);
	} else {
	  setIntelligence(intelligence-1);
	}
  }
  if (percentChance(10)) {
	if (percentChance(50)) {
	  setConstitution(constitution+1);
	} else {
	  setConstitution(constitution-1);
	}
  }
  if (percentChance(10)) {
	if (percentChance(50)) {
	  setDexterity(dexterity+1);
	} else {
	  setDexterity(dexterity-1);
	}
  }
  if (percentChance(10)) {
	if (percentChance(50)) {
	  setLuck(luck+1);
	} else {
	  setLuck(luck-1);
	}
  }
}

void Player::calcSecondaryStats() {
  // set level based on XP
  for (int i=1; i<100; i++) {
	ostringstream os;
	os << "Calculating xp_level for xp value " << xp << ". On iterator " << i << ". xpCalcArray is " <<  xpCalcArray[i];
	string s = os.str();
	shiplog(s,50);

	if (xp <= xpCalcArray[i]) {
	  xp_level = i;
	  break;
	}
  }
  // TODO: Need to modify the following stats based on worn inventory items
  
  // calculate max hit points
  setMaxHP((constitution*2) + (floor(xp_level*1.5) + 0.5));
  
  // set to value for nothing on initially
  setArmour(3);

  setDodge(floor(dexterity*1.3) + 0.5);
  setSpeed(dodge + (floor(strength*0.3) + 0.5));
}

// add an object to the inventory
void Player::addToInv(const Thing& t) {
  inventory.push_back(t);
}

// remove an object from the inventory
void Player::delFromInv(unsigned int id) {
  for(vector<Thing>::iterator it = inventory.begin(); it != inventory.end(); ++it) {
	if (it->getId() == id) {
	  inventory.erase(it);
	}
  }
}

bool Player::checkStatRange(int i, int min, int max) {
  if (i > max || i < min) {
	return false;
  } else {
	return true;
  }
}
