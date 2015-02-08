#include <iostream>

#include "Solver.h"

int main (int argc, char ** argv) {
	int method = 2;
	string file = "files/dsjc1000.9.col";
	if (argc > 1) {
			file = argv[1];
			if (argc > 2) {
				method = atoi(argv[2]);
			}
	}

	clock_t begin, end;
	double time_spent;
	begin = clock();

	Solver solve = Solver(file);
	if (method == 1)
		solve.solve_1();
	else 
		solve.solve_2();

	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	cout << "time : " << time_spent << endl;

	return 0;
}