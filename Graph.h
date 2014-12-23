#ifndef GRAPH_H
#define GRAPH_H

#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>

#include "Vertex.h"

class Graph {
	private:
		vector<Vertex*> graph;
		int size;
	public:
		Graph();
		Graph(string filename);
		Graph(const Graph& g);
		~Graph();
		vector<Vertex*> getGraph();
		void addVertex(Vertex * v);
		void removeVertex(int v);
		int getSize();
		vector<string> tokenize(string toSplit, string token);
		void printGraph();
		bool vertexIsInto(int n) ;
		int getIndexVertex(int n);
		bool canBeAdded(int n);
};

#endif