#ifndef VERTEX_H
#define VERTEX_H

#include <vector>

using namespace std;

class Vertex {
	
	private:
		int num;
		vector<int> edges;
	public:
		Vertex();
		Vertex(int n);
		int getNum();
		vector<int> getEdges();
		void addEdge(int e);

};


#endif