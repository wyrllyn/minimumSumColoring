#include "Solver.h"


Solver::Solver(string f) {
	file = f;
	baseGraph = new Graph(f);
	solution = new Solution();
	solution->initialisation(baseGraph);
}

Graph * Solver::getGraph() {
	return  baseGraph;
}

Solver::~Solver() {
	delete baseGraph;
	//delete solution;
}

void Solver::solve_1() {
	Solution * newSol = new Solution(*solution);
	float currentCost = solution->getCostSol();
	int newCost = 0;
	vector<int> checked;
	cout << "init cost : " << solution->cost() << " " << solution->colors() << " colors" << endl;

	while(checked.size() < newSol->getSol().size()) {
		cout << checked.size() << endl;
		cout << "last cost " << solution->getCostSol()<< " " << solution->colors() << " colors" << endl;
		checked.clear();
		for (int i = newSol->getSol().size(); i > 0 ; i-- ) {
			//cout << "LOOP " << i << endl;
			int tmp = newSol->moveVertex(i);
			//cout << " tmp = " << tmp << endl;
			if ( tmp == 1) {
				//cout << "test" << endl;
				solution = new Solution(*newSol);
				currentCost = newCost;
			}
			else if (tmp == -1) {
				newSol = new Solution(*solution);
				checked.push_back(i);
			}
			else {
				checked.push_back(i);
			}
			//cout << "------- end i " << endl;
		}

	}


//	solution->~Solution();
//	cout << "last cost : " << solution->cost() << " " << solution->colors() << " colors" << endl;
//	cout << " new cost " << newSol->cost() << endl;
	

	solution->solutionOk(*baseGraph);
	solution->testGraphsValidity();

	cout << "last cost " << solution->getCostSol() << endl;
	cout << "last cost : " << solution->cost()   << " " << solution->colors() << " colors" << endl;
/*	 for (int i = 0; i < newSol->getSol().size() ; i++ ) {
	 	cout << i << endl;
	 	cout << "loop : "<< i << " size = " << newSol->getSol()[i]->getGraph()[0]->getEdges().size() << endl;
	 	cout << "vertex is " << newSol->getSol()[i]->getGraph()[0]->getNum() << endl;
	 	cout << "vertex is " << solution->getSol()[i]->getGraph()[0]->getNum() << endl;
	 } */


	delete newSol;
}