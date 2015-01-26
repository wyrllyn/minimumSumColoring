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
	Solution * cSol = new Solution(*solution);
	float currentCost = solution->getCostSol();
	int newCost = 0;
	vector<int> checked;
	cout << "init cost : " << solution->cost() << " " << solution->colors() << " colors" << endl;

	while(checked.size() < newSol->getSol().size()) {
	//	cout << "begin while" << endl;
		cout << checked.size() << endl;
		cout << "---- last cost into while " << cSol->getCostSol()<< " " << cSol->colors() << " colors" << endl;
		checked.clear();
		for (int i = newSol->getSol().size(); i > 0 ; i-- ) {
		//	cout << "LOOP " << i << endl;
		//	
			int tmp = newSol->moveVertex(i);
		//	cout << "tmp " << tmp << endl;
		//	cout << "end" << endl;
			if ( tmp == 1 ) {
				
				delete cSol;
				cSol = new Solution(*newSol);
				
				//solution->moveVertex(i);
				
			}
			else if (tmp == -1) {
			//	cout << "here" << endl;
				delete newSol;
				newSol = new Solution(*cSol);
			//	cout << "yay" << endl;
				checked.push_back(i);
			}
			else {
				checked.push_back(i);
			}
		//	cout << "end for" << endl;
		}
		cout << "end while" << endl;

	}
	cout << "check stuff" << endl;
	solution->solutionOk(*baseGraph);
	cout<< "CHECKING VALIDITY" << endl;
	solution->testGraphsValidity();

	cout << "SOL " << endl;
	cout << "------last cost with get sol cost " << solution->getCostSol() << endl;
	cout << "------last cost with cost calculation : " << solution->cost()   << " " << solution->colors() << " colors" << endl;
	cout << "NEW " << endl;
	cout << "------last cost with get sol cost " << newSol->getCostSol() << endl;
	cout << "------last cost with cost calculation : " << newSol->getCostSol() << " " << newSol->colors() << " colors" << endl;


	delete newSol;
	delete cSol;
}


void Solver::solve_2() {
	Solution * newSol = new Solution(*solution);
	Solution * currentSol = new Solution(*solution);
	Solution * bestSol = new Solution(*solution);
	int temperature = 45;
	float currentCost = solution->getCostSol();
	int newCost = 0;
	vector<int> checked;
	cout << "init cost : " << solution->cost() << " " << solution->colors() << " colors" << endl;
	float diff = 0;
	int foundAt= 0;

	srand(time(NULL));

	int i;
	for (int count = 0; count < 5000; count++) {
		//if (count % 10 == 0)
	//	cout << count << endl;
		i = rand() % baseGraph->getGraph().size() + 1;
	//	cout << i << endl;
		int tmp = newSol->moveVertex(i);
		if (tmp == 1) {
		//	currentSol
			foundAt = count;
			delete bestSol;
			bestSol = new Solution(*newSol);
			delete currentSol;
			currentSol = new Solution(*newSol);
		}
		else {
			diff = newSol->getCostSol() - currentSol->getCostSol();
			if(recuit(temperature, diff) == true ) {
				delete currentSol;
				currentSol = new Solution(*newSol);
			}
			else {
				delete newSol;
				newSol = new Solution(*currentSol);
			}
		}
	}

	
	cout<< "CHECKING VALIDITY" << endl;
	solution->solutionOk(*baseGraph);
	solution->testGraphsValidity();

	cout << "BEST SOL - found at iteration : " << foundAt << endl;
	cout << "------last cost with get sol cost " << bestSol->getCostSol() << endl;
	cout << "------last cost with cost calculation : " << bestSol->cost()   << " " << bestSol->colors() << " colors" << endl;
	cout << "CURRENT " << endl;
	cout << "------last cost with get sol cost " << currentSol->getCostSol() << endl;
	cout << "------last cost with cost calculation : " << currentSol->cost() << " " << currentSol->colors() << " colors" << endl;


	delete newSol;
	delete currentSol;
	delete bestSol;
}


bool Solver::recuit(int T, float delta) {
	float temp = (rand() % 10 + 1) * 0.1;
//	cout << "proba " << temp << endl;
//	cout << "exp " <<  exp(-delta/T) << endl;
	if (temp < exp(-delta/T) ) {
	//	cout << false << endl;
		return false;
	}
//	cout << true << endl;
	return true;
}