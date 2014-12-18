#include "Solution.h"

Solution::Solution(){

}

vector<Graph *> Solution::getSol() {
	return sol;
}


int Solution::colors() {
	return sol.size();
}

// PROBLEM
float Solution::cost() {
	float toReturn = 0;
	for (int i = 0; i < sol.size(); i++) {
		//cout << sol[i]->getSize() << endl;
		toReturn += sol[i]->getSize() * (i+1);
	}
	return toReturn;
}

void Solution::addGraph(Graph * g) {
	sol.push_back(g);
}

void Solution::removeGraph(Graph* g) {

}

// CHECK
void Solution::initialisation(Graph g) {
	for (int i = 0; i < g.getSize(); i++) {

		Graph* tempGraph = new Graph();
		tempGraph->addVertex(g.getGraph()[i]);
		addGraph(tempGraph);
	}
}

//TODO: test
// used to know if a vertex (num) is into sol
bool Solution::isInto(int num) {
	for (int i = 0; i < sol.size(); i++) {
		for (int j = 0; j < sol[i]->getSize(); j++) {
			if (sol[i]->getGraph()[j]->getNum() == num) {
				return true;
			}
		}
	}
	return false;
}

// used to know if all vertices are in Solution
bool Solution::solutionOk(Graph* g) {
	for (int i = 0; i < g->getSize(); i++) {
		if (!isInto(g->getGraph()[i]->getNum())){
			return false;
		}
	}
	return true;
}