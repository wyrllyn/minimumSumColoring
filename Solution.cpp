#include "Solution.h"

Solution::Solution(){

}

vector<Graph *> Solution::getSol() {
	return sol;
}


int Solution::colors() {
	return sol.size();
}

int Solution::cost() {
	int toReturn = 0;
	for (int i = 0; i < sol.size(); i++) {
		toReturn += sol[i]->getSize() * (i+1);
	}
	return toReturn;
}

void Solution::addGraph(Graph * g) {
	sol.push_back(g);
}

void Solution::removeGraph(Graph* g) {

}

void Solution::initialisation() {

}