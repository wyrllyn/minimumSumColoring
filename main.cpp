#include <iostream>

#include "Solver.h"

int main (int argc, char ** argv) {
	string file = "files/dsjc1000.9.col";
	if (argc > 1) {
			file = argv[1];
	}

	clock_t begin, end;
	double time_spent;
	begin = clock();

	Solver solve = Solver(file);
	solve.solve_2();
	//cout << solve.getGraph()->getIndexVertex(5) << endl;
//	solve.getGraph()->removeVertex(5);
	//cout << "can be added 5" << solve.getGraph()->canBeAdded(5);
//	cout << solve.getGraph()->getIndexVertex(5) << endl;
	//solve.getGraph()->printGraph();

	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	cout << "time : " << time_spent << endl;

	return 0;
}