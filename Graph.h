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

		// Constructors & destructor
		Graph();
		Graph(string filename);
		Graph(const Graph& g);
		~Graph();
		bool operator !=(const Graph &b) const ;
		void copy(const Graph& g) ;
	//	Graph operator =(const Graph & other);

		//getters
		int getSize();
		vector<Vertex*> getGraph();

		//insert or remove Vertex
		void addVertex(Vertex * v);
		void removeVertex(int v);
		

		bool vertexIsInto(int n) ;
		int getIndexVertex(int n);
		//bool canBeAdded(int n);
		bool canBeAdded(Vertex v);

		// just a print method
		void printGraph();

		//utils to parse // no need to be in class, check when refactor
		vector<string> tokenize(string toSplit, string token);
};

#endif