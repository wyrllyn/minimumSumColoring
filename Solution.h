#ifndef SOLUTION_H
#define SOLUTION_H

#include "Graph.h"
#include <cstdlib>


class Solution {
	private:
		vector<Graph *> sol;
	public:
		Solution();
		Solution(const Solution& s);
		~Solution();

		vector<Graph *> getSol();

		int colors();

		float cost();

		void addGraph(Graph * g);

		void removeGraph(int g);

		void initialisation(Graph g);

		bool isInto(int num);

		bool solutionOk(Graph g);

		void swapGraph(int index1, int index2);

		int moveVertex(int numVertex);

		int indexGraph(int numVertex);

		bool rightPlace(int index);

		int indexPlace(int index);

		void printSizes();

		void order();
};



#endif