// Objects

#include "object.h"
#include "log.h"

#include <sstream>
#include <algorithm>
#include <cstdlib>

using namespace std;

//----------------------------------------------------------------------
// Thing class implementation
//----------------------------------------------------------------------
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


//----------------------------------------------------------------------
// Weapon class implementation
//----------------------------------------------------------------------
Weapon::Weapon(unsigned int id, string& name, int weight, inventoryType type,
		 int xloc, int yloc,
		 mapColor color, char look,
		 int a_range, int a_to_hit,
		 int a_dmgdice_num, int a_dmgdice_sides) :
  Thing(id, name, weight, type, xloc, yloc, color, look),
  range(a_range), dmgdice_num(a_dmgdice_num),
  dmgdice_sides(a_dmgdice_sides), to_hit(a_to_hit) {

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
//
// object definition string:
//
// OKNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNWWWRRnnSSHHAASSDDLLLssiiccddll
//
//   Attribute         Position Length Notes
//--------------------------------------------------------------
// O Color             0        1      a number, as defined in enums.h
// K Look              1        1      a character 
// N Name              2-32     30
// W Weight            33-35    3
// R Range             36-37    2
// n Number (Dmg Dice) 38-39    2
// S Sides (Dmg Dice)  40-41    2
// H To Hit            42-43    2
// A Armour Mod        44-45    2
// S Speed Mod         46-47    2
// D Dodge Mod         48-49    2
// L Hit Points Mod    50-52    3
// s Strength Mod      53-54    2 
// i Intelligence Mod  55-56    2 
// c Constitution Mod  57-58    2 
// d Dexterity Mod     59-60    2 
// l Luck Mod          61-62    2 
void ThingMaker::initThings() {
  // Short range weapons
  SRWDat.push_back("5/sharplightprojector           1  1 1 6 0 0 0 0 0  0 0 0 0 0 ");
}

// TODO: randomise the object and its properties
Thing* ThingMaker::instantiate(inventoryType type, int xloc, int yloc) {
  switch (type) {
  case SRW:
	string dat = SRWDat[0];
	
	int icolor = dat[0] - '0';
	mapColor color = getMapColor(icolor);
	char look = dat[1];
	string name = dat.substr(2,30);
	name.erase(name.find_last_not_of(' ')+1); // right-trim whitespace
	string s = dat.substr(33,3);
	int weight = atoi(s.c_str());
	s = dat.substr(36,2);
	int range = atoi(s.c_str());
	s = dat.substr(38,2);
	int dmgdice_num = atoi(s.c_str());
	s = dat.substr(40,2);
	int dmgdice_sides = atoi(s.c_str());
	s = dat.substr(42,2);
	int to_hit = atoi(s.c_str());
	s = dat.substr(44,2);
	int  armour= atoi(s.c_str());
	s = dat.substr(46,2);
	int  speed = atoi(s.c_str());
	s = dat.substr(48,2);
	int  dodge = atoi(s.c_str());
	s = dat.substr(50,3);
	int  life = atoi(s.c_str());
	s = dat.substr(53,2);
	int  strength = atoi(s.c_str());
	s = dat.substr(55,2);
	int  intelligence = atoi(s.c_str());
	s = dat.substr(57,2);
	int  constitution = atoi(s.c_str());
	s = dat.substr(59,2);
	int  dexterity = atoi(s.c_str());
	s = dat.substr(61,2);
	int  luck = atoi(s.c_str());

	Weapon* w = new Weapon(getSerial(),name,weight,SRW,xloc,yloc,color,look,range,to_hit,dmgdice_num,dmgdice_sides);
	return w;
	break;
  }
  
}
