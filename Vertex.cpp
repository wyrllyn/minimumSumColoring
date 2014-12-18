#include "Vertex.h"



Vertex::Vertex() {
}

Vertex::Vertex(int n) {
	num = n;
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