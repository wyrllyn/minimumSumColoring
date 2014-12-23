#include "Solution.h"

Solution::Solution(){

}

vector<Graph *> Solution::getSol() {
	return sol;
}

Solution::Solution(const Solution& s) {
	for (int i = 0; i < s.sol.size(); i++) {
		Graph * g = new Graph(*s.sol[i]);
		addGraph(g);
	}
}

Solution::~Solution() {
/*	for (int i = 0; i < sol.size(); i++) {
		cout << "i = " << i << endl;
		sol[i]->~Graph();
	}*/
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

void Solution::removeGraph(int g) {
	sol.erase(sol.begin()+g);
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
			//cout << "isInto num tested : " << num << endl;
			if (sol[i]->getGraph()[j]->getNum() == num) {
				return true;
			}
		}
	}
	return false;
}

// used to know if all vertices are in Solution and for the cardinality 
bool Solution::solutionOk(Graph g) {
	for (int i = 0; i < g.getSize(); i++) {
		if (!isInto(g.getGraph()[i]->getNum())){
			cerr << "F1: missing Node(s) : " << g.getGraph()[i]->getNum() <<endl;
			return false;
		}
	}
	for (int i = 0; i < sol.size() - 1 ; i++) {
		for (int j = i+1; j < sol.size() ; j++ ) {
			if (sol[i]->getSize() < sol[j]->getSize()) {
				cout << "F2: cardinality not respected" <<endl;
				return false;
			}
		}
	}
	cout << "TRUE" <<endl;
	return true;
}

void Solution::swapGraph(int index1, int index2) {
	Graph * g = new Graph(*sol[index1]);

	Graph * g2 = new Graph(*sol[index2]);
	sol[index1] = new Graph(*g2);

	sol[index2] = new Graph(*g);

}

void Solution::moveVertex(int numVertex) {

	cout<< "colors k = "  <<sol.size() << endl;
	cout<< "sum = " << cost() << endl;
	// remove from appropriate graph a
	int indexa= indexGraph(numVertex);
	int indexb = -1;
		//cout << index << endl;
	int tempIndex = sol[indexa]->getIndexVertex(numVertex);
	Vertex * toMove = new Vertex(*sol[indexa]->getGraph()[tempIndex]);
		//cout << toMove->getNum() << " = tomove " << endl;
	// remove
		/*cout << "verif sizes :" << endl;
		cout << sol[indexa]->getSize() << endl;*/
/*	cout << "A res is into 1 : " << isInto(1) << endl;
	cout << "index graph(1)" << indexGraph(1) << endl;
	cout << " temp index : " << tempIndex << endl;
	cout << "num to Move : " << toMove->getNum() << endl;*/
//	cout << "1 -size indexa : " << sol[indexa]->getSize() << endl;
	sol[indexa]->removeVertex(numVertex);
//	cout << "2- size indexa : " << sol[indexa]->getSize() << endl;

	// PROBLEM WITH REMOVE VERTEX OR TEMPINDEX 
	/////////////////////////////////////////
	/////////////////////////////////////////////
	////////////////////////////////////////////
	//////////////////////////////////////////
	// 5 must not be printed, should be 1

	for (int i = 0 ; i < sol[indexa]->getSize(); i++) {
		cout << "  " << sol[indexa]->getGraph()[i]->getNum()<< endl;
	}
	//iterative verification - find a correct graph b
	for (int i = 0; i < sol.size(); i++) {
		if (sol[i]->canBeAdded(numVertex) && i!=indexa) {
			indexb = i;
			break;
		}
	}
	if (indexb == -1) {
		cout << " WARNING : CHECK moveVertex method into Solution class" << endl;
	}

	cout << "graph a : " << indexa << endl;
	cout << "graph b : " << indexb << endl;
/*	cout << "index graph(1)" << indexGraph(1) << endl;
	cout << "A2 res is into 1 : " << isInto(1) << endl;*/
	// add into another graph b

	sol[indexb]->addVertex(toMove);
	//sol[indexb]->printGraph();
	// if graph a size = 0, remove it
	if (sol[indexa]->getSize() == 0) {
	//	cout << "REMOVE" << endl;
		removeGraph(indexa);
	}

	// verif of graph a size (same as below)	
	// verification of graph b size compare to his neighbors -> if not ok, find the right index and swap
	if (!rightPlace(indexb)) {
		cout << "MOVE IT B : " << indexPlace(indexb)  << endl;
		swapGraph(indexb, indexPlace(indexb));
	}
	if (!rightPlace(indexa)) {
		cout << "MOVE IT A : " << indexPlace(indexa) << endl;
		swapGraph(indexa, indexPlace(indexa));
	}
}

int Solution::indexGraph(int numVertex) {
	int index = -1;
	for (int i = 0 ; i < sol.size(); i++) {
		if (sol[i]->vertexIsInto(numVertex)) {
			return i;
		}
	}
	return index;
}

bool Solution::rightPlace(int index) {
	if(index == 0) {
		if(sol[index]->getSize() >= sol[index + 1]->getSize() ) {
			return true;
		}
	}
	else if (index == sol.size() - 1) {
		if (sol[index]->getSize()  <= sol[index-1]->getSize() ) {
			return true;
		}
	}
	else {
		if (sol[index]->getSize()  <= sol[index-1]->getSize() && sol[index]->getSize()  >= sol[index+1]->getSize() ) {
			return true;
		}
	}
	return false;
}

int Solution::indexPlace(int index) {
	int s = sol[index]->getSize();
	if(index == 0) {
		for (int i = 1; i < sol.size();i++) {
			if ( s >= sol[i]->getSize()) {
				return i;
			}
		}
	}
	else if (index == sol.size() - 1) {
		for (int i = index - 1; i >= 0 ;i--) {
			if ( s >= sol[i]->getSize()) {
				return i;
			}
		}
	}
	else {
		if(s < sol[index + 1]->getSize()) {
			for (int i = index + 1; i < sol.size();i++) {
				if ( s > sol[i]->getSize()) {
					return i;
				}
			}
			return sol.size()-1;
		}
		else if ( s > sol[index - 1]->getSize()) {
			for (int i = index - 1; i >= 0 ;i--) {
				if ( s > sol[i]->getSize()) {
					return i;
				}
			}
			return 0;
		}
	}

	return -1;
}

void Solution::printSizes() {
	for (int i = 0; i < sol.size(); i++) {
		cout << " " << sol[i]->getSize();
	}
	cout << endl;
}