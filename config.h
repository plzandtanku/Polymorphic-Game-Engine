#ifndef CONFIG_H
#define CONFIG_H

#include <iostream>
#include <vector>

// The definition of a single configuration
// by Kenneth Liu kkl4549
// specific documentation can be found by the child classes
// that use them
class Config {

private:
	std::vector<int> vals;
	std::vector<int> connectors;
	std::vector<int> used;
	int size;
	int triadValue;
	int connectorIndex = 0;
	std::vector<int> config;
	bool valid = true;

public:
	Config();
	virtual ~Config()=0;
	int none = 0;
	virtual std::vector<int> getConfig() =0;
	virtual bool isGoal() =0;
	virtual std::vector<Config*> getSuccessors() =0;
	virtual bool isValid() =0;
	virtual bool noSol() =0;
	friend std::ostream& operator<<(std::ostream& os, Config *c);

};

#endif // CONFIG_H

