#include "Solution.h"

///////////////////////////////////////////////////
///// CONSTRUCTORS & DESTRUCTORS////////////////////
///////////////////////////////////////////////////

Solution::Solution(){
}

Solution::Solution(const Solution& s) : sol(s.sol.size()) {		
	for (int i = 0; i < s.sol.size(); i++) {
			sol[i] = new Graph(*s.sol[i]);
	}
	costSol = s.costSol;
}

Solution::~Solution() {
	while(!sol.empty()) {
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
	delete sol[g];
	sol.erase(sol.begin()+g);
}

/////////////////////////////
///////// SWAP GRAPH ////////
/////////////////////////////

//TODO check
void Solution::swapGraph(int index1, int index2) {
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
	//cout << "init" << endl;
	for (int i = 0; i < g->getSize(); i++) {
		Graph* tempGraph = new Graph();
		tempGraph->addVertex(g->getGraph()[i]);
		addGraph(tempGraph);
	}
	costSol = cost();
}

void Solution::initialisation_3(Graph * g) {
	cout << "init" << endl;
	vector<int> numbers;
	int indRand = 0;
	int count = 0;
	while( numbers.size() < g->getGraph().size() ) {
		indRand = rand() % g->getGraph().size() + 1;
		if(!isIntoNumber(indRand, numbers)) {
			count ++;
			Graph* tempGraph = new Graph();
			int tempIndex = g->getIndexVertex(indRand);
			tempGraph->addVertex(g->getGraph()[tempIndex]);
			addGraph(tempGraph);
			numbers.push_back(indRand);
		}
	}
	costSol = cost();
	cout << costSol << " is the cost" << endl;
	cout << sol.size() << " is the size" << endl;
}

void Solution::initialisation_2(Graph * g) {
	//cout << "init " << endl;
	vector<int> numbers;
	int indRand = 0;
	int graph_index;
	bool ok = false;
	Vertex * temp_v /*= new Vertex()*/;
	while( numbers.size() < g->getGraph().size() ) {
	//	cout << numbers.size() << endl;
		ok = false;
		indRand = rand() % g->getGraph().size() + 1;
		// if numbers contains indRand => do nothing
		//else
		if(!isIntoNumber(indRand, numbers)) {
			int tempIndex = g->getIndexVertex(indRand);
			temp_v = new Vertex(*g->getGraph()[tempIndex]);
			for (int i = 0; i < sol.size(); i++) {
				if (sol[i]->canBeAdded(*temp_v)){
					// add vertex into graph
					sol[i]->addVertex(temp_v);
					graph_index = i;
					ok = true;
					break;
				}
			}
			if (!ok) {
				// new graph to add
				Graph* tempGraph = new Graph();
				tempGraph->addVertex(temp_v);
				addGraph(tempGraph);
				graph_index = sol.size() - 1;
			}
			// order
			// maybe something else
			if (!rightPlace(graph_index)) {
				order();
			}
			numbers.push_back(indRand);
		}
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
	if(index == 0) {

		//	cout << "here 1" << endl;
		if(sol[index]->getSize() >= sol[index + 1]->getSize() ) {
			return true;
		}
	}
	else if (index == sol.size() - 1 || index == sol.size() ) {
		if (sol[sol.size() - 1]->getSize()  <= sol[sol.size() - 2]->getSize() ) {
			return true;
		}
	}
	else {
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

	int tempIndex = sol[indexa]->getIndexVertex(numVertex);
	Vertex * toMove = new Vertex(*sol[indexa]->getGraph()[tempIndex]);


	sol[indexa]->removeVertex(numVertex);

	//iterative verification - find a correct graph b
	for (int i = 0; i < sol.size(); i++) {
		if (sol[i]->canBeAdded(numVertex) && i!=indexa) {
			indexb = i;
			break;
		}
	}


	if (indexb == -1) {
		sol[indexa]->addVertex(toMove);
		return 0;
	}	

	sol[indexb]->addVertex(toMove);



	// if graph a size = 0, remove it
	if (sol[indexa]->getSize() == 0) {
		removeGraph(indexa);		
	};

	// verif of graph a size (same as below)	
	// verification of graph b size compare to his neighbors -> if not ok, find the right index and swap
	if (!rightPlace(indexb) || !rightPlace(indexa)) {
		order();
	}

	costSol = cost();

	if (costSol >= oldCost) {
		return -1;
	}

	return 1;
}

int Solution::moveVertex_2(int numVertex) {
	float oldCost = costSol;
	// remove from appropriate graph a
	int indexa = indexGraph(numVertex);
	int indexb = -1;

	bool found = false;
	vector<int> numbers;

	int tempIndex = sol[indexa]->getIndexVertex(numVertex);
	Vertex * toMove = new Vertex(*sol[indexa]->getGraph()[tempIndex]);


	sol[indexa]->removeVertex(numVertex);

	// set indexb, with random and verification
	while(!found && !isIntoNumber(indexb, numbers) && (numbers.size() < sol.size())) {
		indexb = rand() % sol.size();
		if (indexb != indexa && sol[indexb]->canBeAdded(numVertex)) {
			found = true;
			break;
		}
		numbers.push_back(indexb);
	}
	if (!found) {
		sol[indexa]->addVertex(toMove);
		return 0;
	}	
	sol[indexb]->addVertex(toMove);

	// if graph a size = 0, remove it
	if (sol[indexa]->getSize() == 0) {
		removeGraph(indexa);		
	};

	// verif of graph a size (same as below)	
	// verification of graph b size compare to his neighbors -> if not ok, find the right index and swap
	if (!rightPlace(indexb) || !rightPlace(indexa)) {
		order();
	}

	costSol = cost();

	if (costSol >= oldCost) {
		return -1;
	}

	return 1;
}

int Solution::new_moveVertex_2(int numVertex){
	float oldCost = costSol;
	// remove from appropriate graph a
	int indexa = indexGraph(numVertex);
	int indexb = -1;

	bool wasNotAlone = true;

	bool found = false;
	vector<int> numbers;

	int tempIndex = sol[indexa]->getIndexVertex(numVertex);
	Vertex * toMove = new Vertex(*sol[indexa]->getGraph()[tempIndex]);

	if (sol[indexa]->getGraph().size() < 2) wasNotAlone == false;
	sol[indexa]->removeVertex(numVertex);

	// set indexb, with random and verification
	while(!found && !isIntoNumber(indexb, numbers) && (numbers.size() < sol.size())) {
		// if wasNotAlone => value_rand + 1
		// if indexb = max_value_rand + 1
			// create new graph at indexb + found = true
		if (wasNotAlone) {
			indexb = rand() % (sol.size() + 1);
		} else {
			indexb = rand() % sol.size();
		}
		if (indexb == sol.size()) {
			Graph* tempGraph = new Graph();
				//tempGraph->addVertex(temp_v);
			addGraph(tempGraph);

			found = true;
			break;

		} else if (indexb != indexa && sol[indexb]->canBeAdded(numVertex)) {
			found = true;
			break;
		}
		numbers.push_back(indexb);
	}
	if (!found) {
		sol[indexa]->addVertex(toMove);
		return 0;
	}	
	sol[indexb]->addVertex(toMove);

	// if graph a size = 0, remove it
	if (sol[indexa]->getSize() == 0) {
		removeGraph(indexa);		
	};

	// verif of graph a size (same as below)	
	// verification of graph b size compare to his neighbors -> if not ok, find the right index and swap
	if (!rightPlace(indexb) || !rightPlace(indexa)) {
		order();
	}

	costSol = cost();

	if (costSol >= oldCost) {
		return -1;
	}

	return 1;
}

bool Solution::isIntoNumber(int num, vector<int> numbers) {
	for (int i = 0; i < numbers.size(); i++ ) {
		if (numbers[i] == num)
			return true;
	}
	return false;
}
