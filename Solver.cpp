#include "Solver.h"

// TODO: init solu
Solver::Solver(string filename) : completeGraph(filename){
	fileN = filename;

}


Graph Solver::getCompleteGraph() {
	return completeGraph;
}

Solution Solver::getSolu() {
	return solu;
}