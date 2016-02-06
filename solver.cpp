#include <iostream>
#include "solver.h"
using namespace std;

// Kenneth Liu kkl4549
// Run the recursive solve algo
// uses Config polymorphic functions
Config* Solver::solve(Config *c){
	if (c->isGoal()){
		c->none = 2;
		solution = c;
		return c;
	}else{
		vector<Config*> children = c->getSuccessors();
		for (auto child:children){
			ptrs.push_back(child);
		}
		for (auto child:children){
				Config *solution = solve(child);
				if (solution->none > 1){
					path.push_back(child);
					return solution;
				}
		}
		c->none = 1;
		return c;
	}
}

//destruct your ptrs
Solver::~Solver(){
	for (auto a:ptrs){
		delete a;
	}
}

//printPath
//print the output
//option 1-print solution only
//else print path (or no solution)
void Solver::printPath(int option){
	if (path.size()<1 && solution==nullptr){
		cout << "No solution!" << endl;
		return;
	}
	if (option !=1){
		for (int i=path.size()-1;i>0;i--){
			vector<int> config = path[i]->getConfig();
			for (int j=0;j<config.size();j++){
				if (j!=0 && j%3==0){
					cout <<" - ";
				}
				cout <<config[j];
				if ((j+1)%3!=0){
					cout <<".";
				}
			}
			cout << endl;
		}
	}
	vector<int> config = solution->getConfig();
	for (int j=0;j<config.size();j++){
		if (j!=0 && j%3==0){
			cout <<" - ";
		}
		cout <<config[j];
		if ((j+1)%3!=0){
			cout <<".";
		}
	}
	cout << endl;
	return;
}
