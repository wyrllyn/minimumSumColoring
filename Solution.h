#ifndef SOLUTION_H
#define SOLUTION_H

#include "Graph.h"

class Solution {
	private:
		vector<Graph *> sol;
	public:
		Solution();
		vector<Graph *> getSol();
		int colors();
		int cost();
		void addGraph(Graph * g);
		void removeGraph(Graph* g);

		void initialisation();
};



#endif