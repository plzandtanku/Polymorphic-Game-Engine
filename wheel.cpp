#include <iostream>
#include "config.h"
#include "WheelConfig.h"
#include "solver.h"
using namespace std;

//Kenneth Liu kkl4549
//the main program for solving
// Right now, we are running the wheel solver only
// so just handle args for that case
int main(int argc, char* argv[]) {
	// one arg optional must be path to print path
	// else just solution (or no solution)
	if (argc > 2){
		cerr << "Usage: wheel {path}"<< endl;
		return 0;
	}
	Config * c = new Wheel();
	Solver solver;
	// catch no solution configs first (incase for large sets)
	if (!c->noSol()){
		solver.printPath(0);
		delete c;
		return 0;
	}
	Config * test = solver.solve(c);
	if (argc > 1){
		string s(argv[1]);
		if (s.compare("path") != 0){
			cerr << "Usage: wheel {path}"<< endl;
			delete c;
			return 0;
		}
		solver.printPath(0);
	}else{
		solver.printPath(1);
	}
	delete c;
	return 0;
}


