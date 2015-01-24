#ifndef SOLUTION_H
#define SOLUTION_H

#include "Graph.h"
#include <cstdlib>


class Solution {
	private:
		vector<Graph *> sol;
		float costSol;
	
	public:
		// constructors & destructor
		Solution();
		Solution(const Solution& s);
		~Solution();

		// getter
		vector<Graph *> getSol();
		float getCostSol();

		void updatesCost();

		// adds & removes elements
		void addGraph(Graph * g);
		void removeGraph(int g);

		// swap elements
		void swapGraph(int index1, int index2);
		int indexGraph(int numVertex);

		// initialisation method
		void initialisation(Graph * g);

		// orders graph for better eval
		void order();

		// evaluation
		int colors();
		float cost();
		
		//  ??
		bool isInto(int num);

		// verif is sol is ok
		bool solutionOk(Graph g);
		bool testGraphsValidity();

		
		// move a vertex
		int moveVertex(int numVertex);		
		bool rightPlace(int index);
		int indexPlace(int index);

		// print method
		void printSizes();

		

		

};



#endif