#include "Solution.h"

///////////////////////////////////////////////////
///// CONSTRUCTORS & DESTRUCTORS////////////////////
///////////////////////////////////////////////////

Solution::Solution(){
	cout << " new sol" << endl;
}

// TODO : verif
Solution::Solution(const Solution& s) : sol(s.sol.size()) {

		
	for (int i = 0; i < s.sol.size(); i++) {
		//cout << "SOL " << i << " graph size = " << s.sol[i].size() << endl;
		//for (std::size_t i = 0; i < s.sol.size() ; i++ ) {
			sol[i] = new Graph(*s.sol[i]);
		//	cout << "SOL " << i << " graph size = " << s.sol[i]->getGraph().size() << endl;
		//}
	}
	costSol = s.costSol;
}

//for (std::size_t i = 0; i < orig.data.size(); ++i)
        //data[i] = new A(*orig.data[i]);
//


Solution::~Solution() {
	while(!sol.empty()) {
		if(sol.back() != NULL)
			delete sol.back();
		sol.pop_back();
	}
}

//////////////////////////////////
//// GETTER /////////////////////
////////////////////////////////

vector<Graph *> Solution::getSol() {
	return sol;
}

float Solution::getCostSol() {
	return costSol;
}

///////////////////////////////
///// ADD & REMOVE GRAPH //////
///////////////////////////////

void Solution::addGraph(Graph * g) {
	sol.push_back(g);
}

//uses an index
void Solution::removeGraph(int g) {
	//delete sol[g];
	//sol[g]->~Graph();
	delete sol[g];
	sol.erase(sol.begin()+g);
}

/////////////////////////////
///////// SWAP GRAPH ////////
/////////////////////////////

//TODO check
void Solution::swapGraph(int index1, int index2) {
/*	Graph * g = new Graph(*sol[index1]);

	Graph * g2 = new Graph(*sol[index2]);
	sol[index1] = g2;

	sol[index2] = g;
*/

	swap(sol[index1], sol[index2]);

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

void Solution::initialisation(Graph * g) {
	cout << "init" << endl;
	for (int i = 0; i < g->getSize(); i++) {
		Graph* tempGraph = new Graph();
		tempGraph->addVertex(g->getGraph()[i]);
		addGraph(tempGraph);
	}
	costSol = cost();
}

////////////////////////////////////////////////////
////// ORDER ////////////////////////////////////
////////////////////////////////////////////////////

void Solution::order() {
	for (int i = 0; i < sol.size() - 1; i++) {
		for (int j = i+1 ; j < sol.size(); j++) {
			if(sol[i]->getSize() < sol[j]->getSize()) {
				swapGraph(i,j);
			}
		}
	}
}


////////////////////////////////////////////////////////
//// EVAL ///////////////////////////////////////////
/////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////
////////////////////////////////////////////////////

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


////////////////////////////////////////////////////////////
// VALIDITY /////////////////////////////////////////
///////////////////////////////////////////////////////////

bool Solution::solutionOk(Graph g) {
	bool toReturn = true;
	for (int i = 0; i < g.getSize(); i++) {
		if (!isInto(g.getGraph()[i]->getNum())){
			cerr << "F1: missing Node(s) : " << g.getGraph()[i]->getNum() <<endl;
			toReturn = false;
		}
	}
	for (int i = 0; i < sol.size() - 1 ; i++) {
		for (int j = i+1; j < sol.size() ; j++ ) {
			if (sol[i]->getSize() < sol[j]->getSize()) {
				cout << "F2: cardinality not respected" <<endl;
				toReturn =  false;
			}
		}
	}

	return toReturn;
}

bool Solution::testGraphsValidity() {
	for (int i = 0; i < sol.size(); i++) {
		for (int j = 0; j < sol[i]->getGraph().size(); j++) {
			for (int k = 0; k < sol[i]->getGraph().size(); k++) {
				if ( sol[i]->getGraph()[j]->isLinked(sol[i]->getGraph()[k]->getNum()) && (j != k)) {
					cout << "TEST GRAPHS VALIDITY = FALSE" << endl;
					cout << sol[i]->getGraph()[k]->getNum() << " and " << sol[i]->getGraph()[j]->getNum() << endl;
					return false;
				}
			}
		}
	}
	cout << "TEST GRAPHS VALIDITY = TRUE" << endl;
	return true;
}

/////////////////////////////////////////////////////////////
////                     MOVES                 /////////////
///////////////////////////////////////////////////////////


bool Solution::rightPlace(int index) {

//	cout << "calling right place" << endl;
//	cout << "--------- index = " << index<< "sol size is of " << sol.size()  << endl;
//	cout << "sol size is of " << sol.size() << endl;
	if(index == 0) {

		//	cout << "here 1" << endl;
		if(sol[index]->getSize() >= sol[index + 1]->getSize() ) {
			return true;
		}
	}
	else if (index == sol.size() - 1 || index == sol.size() ) {

	//		cout << "here 2" << endl;
		if (sol[sol.size() - 1]->getSize()  <= sol[sol.size() - 2]->getSize() ) {
			return true;
		}
	}
	else {
	//	cout << "here 3" << endl;
	//	cout << sol[index]->getSize() <<" <= " << sol[index-1]->getSize() << endl;
		if (sol[index]->getSize() <= sol[index-1]->getSize() && sol[index]->getSize() >= sol[index+1]->getSize() ) {
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


int Solution::moveVertex(int numVertex) {
	float oldCost = costSol;
	// remove from appropriate graph a
	int indexa = indexGraph(numVertex);
	int indexb = -1;

//	cout << "sol size at the beggining of move vertex " << sol.size() << endl;

	int tempIndex = sol[indexa]->getIndexVertex(numVertex);
	Vertex * toMove = new Vertex(*sol[indexa]->getGraph()[tempIndex]);


	sol[indexa]->removeVertex(numVertex);

	//iterative verification - find a correct graph b
	for (int i = 0; i < sol.size(); i++) {
		if (sol[i]->canBeAdded(numVertex) && i!=indexa) {
			indexb = i;
			break;
		}
	/*	if (sol[i]->canBeAdded(*toMove) && sol[i]->canBeAdded(numVertex)  && i!=indexa) {
			indexb = i;
			break;
		} */
	}


	if (indexb == -1) {
		//cout << " WARNING : CHECK moveVertex method into Solution class" << endl;
		sol[indexa]->addVertex(toMove);
		return 0;
	}

	

	sol[indexb]->addVertex(toMove);



	// if graph a size = 0, remove it
	if (sol[indexa]->getSize() == 0) {
		removeGraph(indexa);		
	}

//	cout << "INTO MOVE" << endl;
//	cout << indexa << " " << indexb << endl;
//	cout << indexb << " " << indexa << " size sol is " << sol.size() << endl;

	// verif of graph a size (same as below)	
	// verification of graph b size compare to his neighbors -> if not ok, find the right index and swap
	if (!rightPlace(indexb) || !rightPlace(indexa)) {
	//	cout << "before order calls" << endl;
		order();
	}

	//cout << "INTO MOVE 2" << endl;

	costSol = cost();

	if (costSol >= oldCost) {
		return -1;
	}

	return 1;
}
