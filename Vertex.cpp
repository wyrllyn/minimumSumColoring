#include "Vertex.h"
#include <iostream>



Vertex::Vertex() {
}

Vertex::Vertex(int n) {
	num = n;
}

Vertex::Vertex(const Vertex& v):num(v.num) {
	// PROBLEM IN LAST CASE OF SOLUTION : CORRUPTED 
	
	for (int i = 0; i < v.edges.size(); i++) {
		//cout << "vertex const " << i <<  " on vertex num " << v.num << endl;
		addEdge(v.edges[i]);
	}
	//cout << "size is : " << v.edges.size() << endl;
}


int Vertex::getNum() {
	return num;
}

vector<int> Vertex::getEdges() {
	return edges;
}

void Vertex::addEdge(int e) {
	edges.push_back(e);
}

bool Vertex::isLinked(int n) {
	for (int i = 0; i < edges.size(); i++) {
		if (n == edges[i]) {
			return true;
		}
	}
	return false;
}

Vertex::~Vertex() {
	//std::cout << "bye vertex" << std::endl;
	while(!edges.empty()) {
		edges.pop_back();
	}
}