#include <iostream>
#include "WheelConfig.h"

using namespace std;

//Kenneth Liu kkl4549
// Wheel class, inherits from Config class
// for now, we use the constructor to readinputs to keep main 'cleaner'
// also constructor will do some value sums for Wheel solving
Wheel::Wheel(){
	// Read the input (may extract later)
	cin >> triads;
	for (int i = 0;i<triads;i++){
		int connector;
	   	cin >> connector;	
		connectors.push_back(connector);
	}
	int value = 0;
	while (cin >> value){
		vals.push_back(value);
	}	
	// Keep track of the size
	size = 3 * triads;
	int sum = 0;
	sum = (size*(size+1))/2;

	// Generate sum to determine tradValue (use for validity checks)
	triadValue = sum/triads;
	config.resize(size);
   	if (value > 0){
		preset = true;
		setValues();
	}
	setUsed();
}

// Destructor
Wheel::~Wheel(){
}

// Separate construct for generating children nodes
Wheel::Wheel(vector<int> vals,vector<int> oldConn, int triad,bool set){
	preset = set;
	config = vals;
	connectors = oldConn;
	triadValue = triad;
	size = vals.size();
	setUsed();
}

//getConfig
// return the vecotr<int> that is the underlying config
vector<int> Wheel::getConfig(){
	return config;
}

// setValues
// From input, determine if we have existing values
void Wheel::setValues(){
	for (int i =0;i<vals.size();i++){
		config[vals[i]] = vals[i+1];
		i++;
	}
	return;
}

// setUsed
// when generating successors, would want to check used values
void Wheel::setUsed(){
	used.resize(size+1);
	for (auto i:config){
		if (i > 0){
			used[i] = 1;
		}
	}
	return;
}

// isGoal
// logic involves doing some math checks as well as basic checks
bool Wheel::isGoal(){
	int index = 0;
	int index2 = 0;
	for (int i=0;i<connectors.size();i++){
		if (config.size()>3 && config[2]+config[3] == connectors[i]){
			index2 = i;
			break;
		}
	}
	int triSum = 0;
	// Keep running indexes against the connectors and the config
	// match the right config value within the connectors (by index)
	while (index < config.size()){
		if (config[index] == 0){
			return false;
		}
		// build triad Sum 
		triSum = triSum + config[index];
		// Based on index, do a different check
		if (index == config.size() -1){
			// check wrap around triad connector
			if (config[index] + config[0] != connectors[index2]){
				return false;
			}
		}else{
			// check the other connectors
			if ((index + 1) % 3 == 0){
				if (triSum != triadValue){
					return false;
				}
				if (config[index]+config[index+1] != connectors[index2]){
					return false;
				}
				index2++;
				if (index2 >= connectors.size()){
					index2 = 0;
				}
				triSum = 0;
			}
		}
		index++;
	}
	return true;
}

// noSol
// Detect noSolution configs 
bool Wheel::noSol(){
	int sum = (size*(size+1))/2;
	int triadSum = 0;
	if (sum % triads !=0){
		return false;
	}
	for (auto a:connectors){
		triadSum = a + triadSum;
		if (a-size >=size){
			return false;
		}
		if (triadSum > sum){
			return false;
		}
	}
	return true;
}

// getSuccessors
// generate successors of Config/Wheels
// by inputting 1-(size of solution) in every instance of 0
// only include successors that are valid
vector<Config*> Wheel::getSuccessors(){
	int index = -1;
	// we know to only generate values 1-n
	for (int i=0;i<config.size();i++){
		// if the position, is 0, fill it
		if (config[i] == 0){
			for (int j =1;j<used.size();j++){
				vector<int> temp = config;
				if (used[j] != 1){
					temp[i]= j;
					// create the successor WATCH FOR MEMORY LEAKS
					Config *c1=new 	Wheel(temp,connectors,triadValue,preset);
					if (c1->isValid()){
						//add it to the successors if its valid
						suc.push_back(c1);
					}else{
						// not using it, delete
						delete c1;
					}
				}
			}
			return suc;
		}
	}
	return suc;
}

//checkConnect
//helper for isValid that sees if a pair matches a connector
bool Wheel::checkConnect(int val){
	if (val == connectors[connectorIndex]){
		connectorIndex++;
		if (connectorIndex >= connectors.size()){
			connectorIndex = 0;
		}
		return true;
	}
	return false;
}

// isValid
// determine valid configs/wheels
bool Wheel::isValid(){
	if (preset && config.size() > 3 && config[2] && config[3]){
		for (int i=0;i<connectors.size();i++){
			if (config[2]+config[3] == connectors[i]){
				connectorIndex = i;
				break;
			}
		}
	}
	for (int i=0;i<config.size();i++){
		// if its a 3rd index, check the triadSum with triadValue
		if (i%3 == 0){
			// check first if you are creating an impossible triad
			if (config[i] && config[i+1]){
				int triadSum =config[i] + config[i+1];
				if (triadValue - triadSum > size){
					return false;
				}
			}	
			// then check if the triad is a good sum
			if (config[i] && config[i+1] && config[i+2]){
				int triadSum =config[i] + config[i+1] + config[i+2];
				if (triadSum!=triadValue){
					return false;	
				}
			}
		}
		// now check connector values 
		if (i<config.size()-1 && (i+1)%3 == 0 && config[i] && config[i+1]){
			int val = config[i]+config[i+1];
			if (!checkConnect(val)){
				return false;
			}

		}
		// check the connector that wraps around
		if (i == config.size()-1 && config[0] !=0 && config[0] && config[i]){
			int val = config[0] + config[i];
			if (!checkConnect(val)){
				return false;
			}
		}
	}
	return true;
}

