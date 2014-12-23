#ifndef SOLVER_H
#define SOLVER_H

#include "Solution.h"

class Solver {
	private:
		Graph completeGraph;
		Solution solu;
		string fileN;
	public:
		Solver(string filename);
		Graph getCompleteGraph();
		Solution getSolu();
		void test();

};

#endif