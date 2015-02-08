#ifndef SOLVER_H
#define SOLVER_H

#include "Solution.h"
#include <cmath>
#include <fstream>

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
		void solve_1_1();

		void solve_2();

		void solve_3();

		bool recuit(float T, float delta);

		void write_res(string fileName, int method, float cost, int colors);
		



};



#endif