#include "Solver.h"

int total_loop_nbrs = 20000000;

Solver::Solver(string f) {
	file = f;
	baseGraph = new Graph(f);
	solution = new Solution();
	//solution->initialisation_2(baseGraph);
}

Graph * Solver::getGraph() {
	return  baseGraph;
}

Solver::~Solver() {
	delete baseGraph;
	//delete solution;
}

void Solver::solve_1() {
	cout << "LOCAL SEARCH w DESCENT" << endl;
	int seed = time(NULL);
	srand(seed);
	solution->initialisation_3(baseGraph);
	Solution * newSol = new Solution(*solution);
	Solution * cSol = new Solution(*solution);
	float currentCost = solution->getCostSol();
	int newCost = 0;
	vector<int> checked;
	cout << "init cost : " << solution->cost() << " " << solution->colors() << " colors" << endl;

	while(checked.size() < baseGraph->getGraph().size()) {
	//	cout << "---- last cost into while " << cSol->getCostSol()<< " " << cSol->colors() << " colors" << endl;
		checked.clear();
		for (int i = baseGraph->getGraph().size(); i > 0 ; i-- ) {
			int tmp = newSol->moveVertex_2(i);
			if ( tmp == 1 ) {				
				delete cSol;
				cSol = new Solution(*newSol);
			}
			else if (tmp == -1) {
				delete newSol;
				newSol = new Solution(*cSol);
				checked.push_back(i);
			}
			else {
				checked.push_back(i);
			}
		}		
	//	cout << "not moved = " << checked.size() << endl;
	}
	cout << "seed was " << seed << endl;
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

	write_res(file, 1, newSol->getCostSol(), newSol->colors() );


	delete newSol;
	delete cSol;
}


void Solver::solve_2() {
	cout << "LOCAL SEARCH w SIMULATED ANNEALING"<< endl;
	int seed = time(NULL);
	//seed = 10;
	srand(seed);
	solution->initialisation_3(baseGraph);
	Solution * newSol = new Solution(*solution);
	Solution * currentSol = new Solution(*solution);
	Solution * bestSol = new Solution(*solution);
	float temperature = 1000000;
	float currentCost = solution->getCostSol();
	int newCost = 0;
	vector<int> checked;
	cout << "init cost : " << solution->cost() << " " << solution->colors() << " colors" << endl;
	float diff = 0;
	int foundAt= 0;

	if (baseGraph->getGraph().size() == 250) total_loop_nbrs = 500000;
	if (baseGraph->getGraph().size() == 500) total_loop_nbrs = 3000000;

	int i;
	for (int count = 0; count < total_loop_nbrs ; count++) {
		/*if (count % 10000 == 0)
			cout << count << endl;*/
		i = rand() % baseGraph->getGraph().size() + 1;
		int tmp = newSol->new_moveVertex_2(i);
		if (tmp == 1) {
			foundAt = count;
			delete bestSol;
			bestSol = new Solution(*newSol);
			delete currentSol;
			currentSol = new Solution(*newSol);
		}
		else if (tmp == -1) {
			diff = newSol->getCostSol() - currentSol->getCostSol();
			//cout << "new cost" << newSol->getCostSol() << endl;
			//cout << "current cost" << currentSol->getCostSol() << endl;
			if(recuit(temperature, diff) == true ) {
				delete currentSol;
				currentSol = new Solution(*newSol);
			}
			else {
				delete newSol;
				newSol = new Solution(*currentSol);
			}
			temperature*=0.97;
		}
	}

//	cout << "temperature is " << temperature << endl;
	cout << "seed was " << seed << endl;
	cout<< "CHECKING VALIDITY" << endl;
	solution->solutionOk(*baseGraph);
	solution->testGraphsValidity();

	cout << "BEST SOL - found at iteration : " << foundAt << " on " << total_loop_nbrs << endl;
	cout << "------last cost with get sol cost " << bestSol->getCostSol() << endl;
	cout << "------last cost with cost calculation : " << bestSol->cost()   << " " << bestSol->colors() << " colors" << endl;

	write_res(file, 2, bestSol->getCostSol(), bestSol->colors() );

	delete newSol;
	delete currentSol;
	delete bestSol;
}

void Solver::solve_3() {
	Solution * newSol = new Solution();
	newSol->initialisation(baseGraph);

	cout<< "CHECKING VALIDITY" << endl;
	solution->solutionOk(*baseGraph);
	solution->testGraphsValidity();
}

bool Solver::recuit(float T, float delta) {
	float temp = (rand() % 10 + 1) * 0.1;
//	cout << "delta " << delta << endl;
//	cout << "proba " << temp << endl;
//	cout << "exp " <<  exp(-delta/T) << endl;
	if (temp < exp(-delta/T) ) {
	//	cout << false << endl;
		return true;
	}
//	cout << true << endl;
	return false;
}

void Solver::write_res(string fileName, int method, float cost, int colors) {

	cout << "test" << endl;
	ofstream ofs;
	
  	ofs.open("results.txt", ios::out | ios::app);

  	if(ofs) {	
		ofs << fileName << " " << method << " " << cost << " " << colors << endl;
		ofs.close();
	}
}

/*
void Solver::solve_1_1() {
	cout << "LOCAL SEARCH w DESCENT" << endl;
	int seed = time(NULL);
	srand(seed);
	solution->initialisation_3(baseGraph);
	Solution * newSol = new Solution(*solution);
	Solution * cSol = new Solution(*solution);
	float currentCost = solution->getCostSol();
	int newCost = 0;
	vector<int> checked;
	cout << "init cost : " << solution->cost() << " " << solution->colors() << " colors" << endl;

	while(checked.size() < baseGraph->getGraph().size()) {
	//	cout << "---- last cost into while " << cSol->getCostSol()<< " " << cSol->colors() << " colors" << endl;
		checked.clear();
		for (int i = baseGraph->getGraph().size(); i > 0 ; i-- ) {
			int tmp = newSol->new_moveVertex_2(i)[0];
			if (tmp == 1) {
				// modify csol with vector
				delete cSol;
				cSol = new Solution(*newSol);
			}
			else if (tmp == -1) {
				delete newSol;
				newSol = new Solution(*cSol);
				checked.push_back(i);
			}
			else {
				checked.push_back(i);
			}
		}		
	//	cout << "not moved = " << checked.size() << endl;
	}
	cout << "seed was " << seed << endl;
	cout << "check stuff" << endl;
	solution->solutionOk(*baseGraph);
	cout<< "CHECKING VALIDITY" << endl;
	solution->testGraphsValidity();

	write_res(file, 1, newSol->getCostSol(), newSol->colors() );

	cout << "SOL " << endl;
	cout << "------last cost with get sol cost " << solution->getCostSol() << endl;
	cout << "------last cost with cost calculation : " << solution->cost()   << " " << solution->colors() << " colors" << endl;
	cout << "NEW " << endl;
	cout << "------last cost with get sol cost " << newSol->getCostSol() << endl;
	cout << "------last cost with cost calculation : " << newSol->getCostSol() << " " << newSol->colors() << " colors" << endl;

	


	delete newSol;
	delete cSol;
}*/