#ifndef VERTEX_H
#define VERTEX_H

#include <vector>

using namespace std;

class Vertex {
	
	private:
		int num;
		vector<int> edges;
	public:
		// constructers + getters
		Vertex();
		Vertex(int n);
		~Vertex();
		Vertex(const Vertex& v);
		int getNum();
		vector<int> getEdges();
		void addEdge(int e);

		// used to know if a Vertex with num = n is into edges
		bool isLinked(int n);

};


#endif