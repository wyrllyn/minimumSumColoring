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
		vector<Vertex*> getGraph();
		void addVertex(Vertex * v);
		void removeVertex(Vertex v);
		int getSize();
		vector<string> tokenize(string toSplit, string token);
};

#endif