#ifndef SOLUTION_H
#define SOLUTION_H

#include "Graph.h"

class Solution {
	private:
		vector<Graph *> sol;
	public:
		Solution();
		Solution(const Solution& s);
		vector<Graph *> getSol();
		int colors();
		float cost();
		void addGraph(Graph * g);
		void removeGraph(Graph* g);

		void initialisation(Graph g);

		bool isInto(int num);

		bool solutionOk(Graph g);
};



#endif