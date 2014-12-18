#include "Solver.h"

// TODO: init solu
Solver::Solver(string filename) : completeGraph(filename){
	fileN = filename;
	solu = Solution();
	solu.initialisation(completeGraph);
	cout<< solu.getSol().size() << endl;
	cout << solu.cost() << endl;
}


Graph Solver::getCompleteGraph() {
	return completeGraph;
}

Solution Solver::getSolu() {
	return solu;
}