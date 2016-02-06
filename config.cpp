#include <iostream>
#include "config.h"

using namespace std;

//Kenneth Liu kkl4549
// Config cpp file for config.h (abstract class)
// We need to define a destructor and ostream<< for now

// possibly need constructor in future?
Config::Config(){}
// destruct for mem mgmt
Config::~Config(){}

// print out the contents of the config
ostream& operator<<(std::ostream& os, Config *c){
	for (auto a:c->getConfig()){
		os << a << " ";
	}
	return os;
}	

