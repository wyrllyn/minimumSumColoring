#include "Vertex.h"



Vertex::Vertex() {
}

Vertex::Vertex(int n) {
	num = n;
}

Vertex::Vertex(const Vertex& v):num(v.num) {
	for (int i = 0; i < v.edges.size(); i++) {
		addEdge(v.edges[i]);
	}
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