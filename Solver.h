#ifndef SOLVER_H
#define SOLVER_H

#include "Solution.h"

class Solver {
	private:
		Graph * baseGraph;
		string file;
		Solution * solution;
	public:
		Solver(string f);
		~Solver();

		Graph * getGraph();

		void solve_1();
		



};

#endif