#include <iostream>

#include "Solver.h"

int main (int argc, char ** argv) {
	string file = "files/dsjc500.1.col";
	if (argc > 1) {
			file = argv[1];
	}

	clock_t begin, end;
	double time_spent;
	begin = clock();

	Solver solve(file);
	solve.test();

	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	cout << "time : " << time_spent << endl;
	return 0;
}