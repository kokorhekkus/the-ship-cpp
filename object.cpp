// Objects

#include "object.h"
#include "log.h"
#include "engine.h"
#include "random.h"

#include <sstream>
#include <algorithm>
#include <cstdlib>

using namespace std;

//----------------------------------------------------------------------
// Thing class implementation
//----------------------------------------------------------------------
const string Thing::invIDs =    "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
string Thing::invIDsAvailable = "0000000000000000000000000000000000000000000000000000";

Thing::Thing(unsigned int a_id, string& a_name, int a_weight, inventoryType a_type,
			 int xloc, int yloc,
			 mapColor color, char look) :
  ScreenObject(xloc, yloc, color, look),
  id(a_id), name(a_name), weight(a_weight), type(a_type) {
  
  ostringstream oss;
  oss << "Creating new Thing object with id " << id;
  string s = oss.str();
  shiplog(s, 10);
}

Thing::~Thing() {
  ostringstream oss;
  oss << "Destroying Thing object with id " << id;
  string s = oss.str();
  shiplog(s, 10);
}

// Getters
unsigned int Thing::getId() const { return id; }
string Thing::getName() const { return name; }
int Thing::getWeight() const { return weight; }
inventoryType Thing::getType() const { return type; }
char Thing::getInvID() const { return invID; }

// get an available letter to identify an object in the player's inventory
char Thing::getNextInvID() {
  string::iterator it;
  for (it = invIDsAvailable.begin(); it < invIDsAvailable.end(); ++it) {
	if (*it == '0') {
	  int index = distance(invIDsAvailable.begin(), it);
	  invIDsAvailable[index] = '1';
	  return invIDs[index];
	}
  }
  // no more characters to assign, should never happen due to inventory size limit
  shiplog("Run out of inventory letters to assign!",1);
  error_exit("Run out of inventory letters to assign!");
}

// used when an object is added to the inventory
void Thing::setInventoryLetter() {
  shiplog("Setting an inventory letter",60);
  invID = getNextInvID();
}
// used when an object is removed from the inventory
void Thing::delInventoryLetter() {
  shiplog("Deleting an inventory letter",60);
  string::const_iterator it;
  for (it = invIDs.begin(); it < invIDs.end(); ++it) {
	if (*it == invID) {
	  int index = distance(invIDs.begin(), it);
	  invIDsAvailable[index] = '0';
	} 
  }
  invID = '\0';
}

//----------------------------------------------------------------------
// Weapon class implementation
//----------------------------------------------------------------------
Weapon::Weapon(unsigned int id, string& name, int weight, inventoryType type,
			   int xloc, int yloc,
			   mapColor color, char look,
			   int a_range, int a_to_hit,
			   int a_dmgdice_num, int a_dmgdice_sides, int a_dmg_extra) :
  Thing(id, name, weight, type, xloc, yloc, color, look),
  range(a_range), to_hit(a_to_hit), dmgdice_num(a_dmgdice_num),
  dmgdice_sides(a_dmgdice_sides), dmg_extra(a_dmg_extra) {

  ostringstream oss;
  oss << "Creating new Weapon object with id " << getId();
  string s = oss.str();
  shiplog(s, 10);
}
Weapon::~Weapon() {
  ostringstream oss;
  oss << "Destroying Weapon object with id " << getId();
  string s = oss.str();
  shiplog(s, 10);
}

//----------------------------------------------------------------------
// Armour class implementation
//----------------------------------------------------------------------
Armour::Armour(unsigned int id, string& name, int weight, inventoryType type,
			   int xloc, int yloc,
			   mapColor color, char look,
			   int a_modArmour, int a_modDodge) :
  Thing(id, name, weight, type, xloc, yloc, color, look),
  modArmour(a_modArmour), modDodge(a_modDodge) {

  ostringstream oss;
  oss << "Creating new Armour object with id " << getId();
  string s = oss.str();
  shiplog(s, 10);
}
Armour::~Armour() {
  ostringstream oss;
  oss << "Destroying Armour object with id " << getId();
  string s = oss.str();
  shiplog(s, 10);
}


//----------------------------------------------------------------------
// ThingMaker class implementation
//----------------------------------------------------------------------
ThingMaker::ThingMaker() {
  shiplog("Creating ThingMaker object",5);
  objectSerial = 0;
}
ThingMaker::~ThingMaker() {
  shiplog("Destroying ThingMaker object",5);
}

// use this to assign a unique serial number to game objects
unsigned int ThingMaker::getSerial() {
  objectSerial++;
  return objectSerial;
}

// convert an integer to a mapColor enum
mapColor ThingMaker::getMapColor(int i) {
  switch (i) {
  case 0:
	return RED;
	break;
  case 1:
	return GREEN;
	break;
  case 2:
	return CYAN;
	break;
  case 3:
	return L_GREY;
	break;
  case 4:
	return BROWN;
	break;
  case 5:
	return BLUE;
	break;
  case 6:
	return MAGENTA;
	break;
  case 7:
	return BLACK;
	break;
  case 8:
	return ORANGE;
	break;
  case 9:
	return L_GREEN;
	break;
  case 10:
	return L_CYAN;
	break;
  case 11:
	return WHITE;
	break;
  case 12:
	return YELLOW;
	break;
  case 13:
	return L_BLUE;
	break;
  case 14:
	return PINK;
	break;
  case 15:
	return D_GREY;
	break;
  default:
	ostringstream oss;
	oss << "Bad color int supplied: " << i << ", returning L_GREY as default";
	string s = oss.str();
	shiplog(s,1);
	return L_GREY;
  }
}

// set up the vector of condensed information on base objects in the game
// TODO: add a 'level' to define how rare/powerful objects are
//
// object definition string:
//
// OKNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNWWWRRnnSSEEHHAASSDDLLLssiiccddllrrr
//
//   Attribute         Position Length Notes
//--------------------------------------------------------------
// O Color             0-1      2      a number, as defined in enums.h
// K Look              2        1      a character 
// N Name              3-33     30
// W Weight            34-36    3
// R Range             37-38    2
// n Number (Dmg Dice) 39-40    2
// S Sides (Dmg Dice)  41-42    2
// E Extra Damage      43-44    2
// H To Hit            45-46    2
// A Armour Mod        47-48    2
// S Speed Mod         49-50    2
// D Dodge Mod         51-53    2
// L Hit Points Mod    54-56    3
// s Strength Mod      56-57    2 
// i Intelligence Mod  58-59    2 
// c Constitution Mod  60-61    2 
// d Dexterity Mod     62-63    2 
// l Luck Mod          64-65    2 
// r Rarity            65-67    3      Percent generation chance, lower is rarer
void ThingMaker::initThings() {
  // Ranged weapons (/)
  LRWDat.push_back( "5 /sharplight projector          1  3 1 6 0 0 0 0 0 0  0 0 0 0 0 10");
  LRWDat.push_back( "5 /maser                         3  6 3 100 0 0 0 0 0  0 0 0 0 0 40");

  // Melee weapons (\) (note escaped '\')
  SRWDat.push_back("14\\forceknife                    1  1 1 4 0 0 0 0 0 0  0 0 0 0 0 10");
  SRWDat.push_back("14\\monofilament loop             1  1 1 100 0 0 0 0 0  0 0 0 0 0 20");

  // Body armour (])
  BodyDat.push_back("13]tungsten weave vest           5            3 0 2 0  0 0 0 0 0 20");
  BodyDat.push_back("13]ceramic plate armour          10           100 0 0  0 0 0 0 0 30");

  // Headwear (^)
  HeadDat.push_back("15^carbon fibre headband         1            1 0 0 0  0 0 0 0 0 10");
  HeadDat.push_back("15^three-ply helmet              3            3 0 0 0  0 0 0 0 0 20");

  // Legwear (|)
  LegDat.push_back( "11|pair of Kevlar trousers       3            6 0 1 0  0 0 0 0 0 20");
  LegDat.push_back( "11|set of ceramic plate leggings 10           9 0 0 0  0 0 0 0 0 30");

  // Footwear (-)
  FootDat.push_back("4 -pair of combat boots          2            2 0 5 0  0 0 0 0 0 10");
  FootDat.push_back("4 -pair of tabi                  1            0 5 3 0  0 0 0 0 0 20");

  // set up adjectives
  adjectivesGun.push_back("big");             adjectivesGun.push_back("old");
  adjectivesGun.push_back("huge");            adjectivesGun.push_back("new");
  adjectivesGun.push_back("small");           adjectivesGun.push_back("well-balanced");
  adjectivesGun.push_back("tiny");            adjectivesGun.push_back("unusual");
  adjectivesGun.push_back("chrome-plated");   adjectivesGun.push_back("deadly-looking");
  adjectivesGun.push_back("matte black");     adjectivesGun.push_back("plastic");
  adjectivesGun.push_back("rusty");           adjectivesGun.push_back("ceramic");
  adjectivesGun.push_back("corroded");        adjectivesGun.push_back("metallic");
  adjectivesGun.push_back("sleek");           adjectivesGun.push_back("antique");
  adjectivesGun.push_back("glossy");          adjectivesGun.push_back("dull");
  adjectivesGun.push_back("black");           adjectivesGun.push_back("pitted");

  adjectivesArmour.push_back("red");          adjectivesArmour.push_back("old");
  adjectivesArmour.push_back("green");        adjectivesArmour.push_back("new");
  adjectivesArmour.push_back("blue");         adjectivesArmour.push_back("unusual");
  adjectivesArmour.push_back("yellow");       adjectivesArmour.push_back("antique");
  adjectivesArmour.push_back("indigo");       adjectivesArmour.push_back("fancy");
  adjectivesArmour.push_back("camoflage");    adjectivesArmour.push_back("faded");
  adjectivesArmour.push_back("dusty");        adjectivesArmour.push_back("badly fitting");
  adjectivesArmour.push_back("bulky");        adjectivesArmour.push_back("rotting");
  adjectivesArmour.push_back("well-fitting"); adjectivesArmour.push_back("brand-new");
  adjectivesArmour.push_back("ripped");       adjectivesArmour.push_back("teal");
  adjectivesArmour.push_back("decorated");    adjectivesArmour.push_back("pitted");
}

// TODO: randomise the object and its properties: all objects in The Ship are unique
// TODO: pick which object to instantiate based on level and rarity
Thing* ThingMaker::instantiate(inventoryType type, int xloc, int yloc) {
  shiplog("->ThingMaker::instantiate",50);
  switch (type) {
  case LRW:
  case SRW: {
	shiplog("LRW/SRW",80);
	int datIdx;
	string dat;
	if (type == SRW) {
	  datIdx = inRange(0,SRWDat.size()-1);
	  dat = SRWDat[datIdx];
	} else {
	  datIdx = inRange(0,LRWDat.size()-1);
	  dat = LRWDat[datIdx];
	}
	
	// item colour & look
	string s = dat.substr(0,2);
	s.erase(s.find_last_not_of(' ')+1); // right-trim whitespace
	int icolor = atoi(s.c_str());
	mapColor color = getMapColor(icolor);

	char look = dat[2];

	// name the item
	string name = dat.substr(3,30);
	name.erase(name.find_last_not_of(' ')+1); // right-trim whitespace
	// append adjective
	int adjIdx = inRange(0,adjectivesGun.size()-1);
	string adj = adjectivesGun[adjIdx];
	adj.append(" ");
	name = adj + name;

	// item attributes
	s = dat.substr(34,3);
	int weight = atoi(s.c_str());
	s = dat.substr(37,2);
	int range = atoi(s.c_str());
	s = dat.substr(39,2);
	int dmgdice_num = atoi(s.c_str());
	s = dat.substr(41,2);
	int dmgdice_sides = atoi(s.c_str());
	s = dat.substr(43,2);
	int dmg_extra = atoi(s.c_str());
	s = dat.substr(45,2);
	int to_hit = atoi(s.c_str());
	s = dat.substr(47,2);
	int armour= atoi(s.c_str());
	s = dat.substr(49,2);
	int speed = atoi(s.c_str());
	s = dat.substr(51,2);
	int dodge = atoi(s.c_str());
	s = dat.substr(54,3);
	int life = atoi(s.c_str());
	s = dat.substr(56,2);
	int strength = atoi(s.c_str());
	s = dat.substr(58,2);
	int intelligence = atoi(s.c_str());
	s = dat.substr(60,2);
	int constitution = atoi(s.c_str());
	s = dat.substr(62,2);
	int dexterity = atoi(s.c_str());
	s = dat.substr(64,2);
	int luck = atoi(s.c_str());

	Weapon* w = new Weapon(getSerial(),name,weight,type,xloc,yloc,color,look,range,to_hit,dmgdice_num,dmgdice_sides,dmg_extra);	return w;
	break;
  }
  case BODY:
  case HEAD:
  case LEG:
  case FOOT: {
	shiplog("BODY/HEAD/LEG/FOOT",80);
	int datIdx;
	string dat;
	switch (type) {
	case BODY:
	  datIdx = inRange(0,BodyDat.size()-1);
	  dat = BodyDat[datIdx]; break;
	case HEAD:
	  datIdx = inRange(0,HeadDat.size()-1);
	  dat = HeadDat[datIdx]; break;
	case LEG:
	  datIdx = inRange(0,LegDat.size()-1);
	  dat = LegDat[datIdx]; break;
	case FOOT:
	  datIdx = inRange(0,FootDat.size()-1);
	  dat = FootDat[datIdx]; break;
	}
	
	// item colour & look
	string s = dat.substr(0,2);
	s.erase(s.find_last_not_of(' ')+1); // right-trim whitespace
	int icolor = atoi(s.c_str());
	mapColor color = getMapColor(icolor);

	char look = dat[2];

	// name the item
	string name = dat.substr(3,30);
	name.erase(name.find_last_not_of(' ')+1); // right-trim whitespace
	// append adjective
	int adjIdx = inRange(0,adjectivesGun.size()-1);
	string adj = adjectivesArmour[adjIdx];
	adj.append(" ");
	name = adj + name;

	// item attributes
	s = dat.substr(34,3);
	int weight = atoi(s.c_str());
	s = dat.substr(47,2);
	int  armour= atoi(s.c_str());
	s = dat.substr(49,2);
	int  speed = atoi(s.c_str());
	s = dat.substr(51,2);
	int  dodge = atoi(s.c_str());
	s = dat.substr(54,3);
	int  life = atoi(s.c_str());
	s = dat.substr(56,2);
	int  strength = atoi(s.c_str());
	s = dat.substr(58,2);
	int  intelligence = atoi(s.c_str());
	s = dat.substr(60,2);
	int  constitution = atoi(s.c_str());
	s = dat.substr(62,2);
	int  dexterity = atoi(s.c_str());
	s = dat.substr(64,2);
	int  luck = atoi(s.c_str());

	Armour* a = new Armour(getSerial(),name,weight,type,xloc,yloc,color,look,armour,dodge); 
	return a;
	break;
  }
  }
}
