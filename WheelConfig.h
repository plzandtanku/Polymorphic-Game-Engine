#ifndef WHEEL_H
#define WHEEL_H

#include "config.h"

// Kenneth Liu kkl4549
// Wheel class header file
class Wheel: public Config {
private:
	// number of triads
	int triads;
	// values of the config (if any)
	std::vector<int> vals;
	// connector values
	std::vector<int> connectors;
	// list of used values (for generating successors
	std::vector<int> used;
	// size of config
	int size;
	// the expected triad value
	int triadValue;
	// in order to maintain ordering of the connector, use index
	int connectorIndex = 0;
	// the config to build
	std::vector<int> config;
	// the successors for an instance of a Wheel
	std::vector<Config*> suc;
	// indicates a present
	bool preset = false;

public:
	// see the cpp for documentation
	Wheel();
	~Wheel();
	Wheel(std::vector<int> vals, std::vector<int> oldConn,int triadValue,bool preset);
	std::vector<int> getConfig();
	std::vector<int> updateConnect();
	bool noSol();
	// indicates noSol config
	int none = 0;
	bool checkConnect(int val);
	void setValues();
	void setUsed();
	bool isGoal();
	std::vector<Config*> getSuccessors();
	bool isValid();
};

#endif // WHEEL_H
