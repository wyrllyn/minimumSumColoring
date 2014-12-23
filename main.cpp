#include <iostream>

#include "Solver.h"

int main (int argc, char ** argv) {
	string file = "files/dsjc250.5.col";
	if (argc > 1) {
			file = argv[1];
	}
	Solver solve(file);
	solve.test();
	cout << "quitting main" << endl;
	return 0;
}