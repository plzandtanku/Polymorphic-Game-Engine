#ifndef SOLVER_H
#define SOLVER_H

#include <iostream>
#include "config.h"

// Kenneth Liu kkl4549
// The Solver class
// contains information for solving a Config
class Solver {
	private:
		// Keep track of a solution
		Config * solution = nullptr;
		// Keep track of all ptrs for mem mgmt
		std::vector<Config *> ptrs;
		// Keep track of the path
		std::vector<Config *> path;
	public:
		~Solver();
		Config* solve(Config *c);
		void printPath(int option);
};

#endif // SOLVER_H

