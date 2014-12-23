#include "Solver.h"

// TODO: init solu
Solver::Solver(string filename) : completeGraph(filename){
	fileN = filename;
	solu = Solution();
	solu.initialisation(completeGraph);
	
}

Solver::~Solver() {
	/*solu.~Solution();
	completeGraph.~Graph();*/
}


Graph Solver::getCompleteGraph() {
	return completeGraph;
}

Solution Solver::getSolu() {
	return solu;
}

void Solver::test() {
	/*
	//// Graph copy
	Graph * g = new Graph(completeGraph);
	if (g->getSize() != completeGraph.getSize()) {
		cout << "error 1 " << endl;
	}
	for (int i = 0; i < completeGraph.getSize(); i++) {
		if (g->getGraph()[i]->getEdges().size() != completeGraph.getGraph()[i]->getEdges().size()) {
			cout << "error 2 " << endl;
		}
		if (g->getGraph()[i]->getNum() != completeGraph.getGraph()[i]->getNum()) {
				cout << "error 3 " << endl;
		}
		for (int j = 0; j < completeGraph.getGraph()[i]->getEdges().size(); j++) {
			if (completeGraph.getGraph()[i]->getEdges()[j] != g->getGraph()[i]->getEdges()[j]) {
				cout << "error 4 " << endl;
			}			

		}
	}
	//// Solution copy
	Solution * s = new Solution(solu);
	if (s->getSol().size() != solu.getSol().size()) {
		cout << "error" << endl;
	}
	*/
	//cout << solu.solutionOk(completeGraph) << endl;
	//completeGraph.printGraph();

	for (int i = 0; i < 10 ; i++) {
		int random = rand() % completeGraph.getSize() ;
		solu.moveVertex(random);
		solu.printSizes();
	}

	solu.solutionOk(completeGraph);

}