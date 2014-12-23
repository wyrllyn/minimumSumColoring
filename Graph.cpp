#include "Graph.h"


Graph::Graph() {
	size = 0;
}

Graph::Graph(const Graph& g) : size(g.size) {
    for(int i = 0; i < g.graph.size(); i++) {
            Vertex * v = new Vertex(*g.graph[i]);
            addVertex(v);
    }
}

Graph::Graph(string filename) {
	//TODO: implement it
	ifstream file(filename.c_str(), ios::in); 
 
    if(file)
    {     
    	string line;
    	//string tempLine;
    	vector<string> tempVect;
    	int first;
    	int second;
        while(getline(file, line)) {
        	
        	if(line[0] == 'p') {
        		tempVect = tokenize(line, " ");
        		size = atoi(tempVect[2].c_str());
        		//cout << size << endl;
        		for (int i = 1; i <= size; i++) {
        			Vertex * v = new Vertex(i);
        			addVertex(v);
        		}
        		/*for (int i = 0; i < graph.size(); i++) {
        			cout << graph[i]->getNum() <<endl;
        		}*/
        	}
        	else if (line[0] == 'e') {
        		tempVect = tokenize(line, " ");
        		first = atoi(tempVect[1].c_str());
        		second= atoi(tempVect[2].c_str());
        		//cout << "first + second "<< first << " " << second << endl;
        		graph[first - 1]->addEdge(second);
        		graph[second - 1]->addEdge(first);
        	}
        }       
        file.close();
       /* cout <<" vertex number " << graph[0]->getNum() << endl;
        for (int i = 0; i < graph[0]->getEdges().size(); i++) {
        	cout << graph[0]->getEdges()[i] << endl;
        }*/
    }
    else {
   		cerr << "Could not open file" << endl;
    }
}

vector<string> Graph::tokenize(string toSplit, string token) {
	int pos;
	vector<string> result;
	while ((pos = toSplit.find(token)) != string::npos) {
		string nuString = toSplit.substr(0, pos);
	if (!nuString.empty()) {
		result.push_back(nuString);
	}
		toSplit = toSplit.substr(pos + 1);
	}
	result.push_back(toSplit);
	return result;
}

vector<Vertex*> Graph::getGraph() {
	return graph;
}

void Graph::addVertex(Vertex * v) {
	graph.push_back(v);
}


//TODO: test
void Graph::removeVertex(Vertex v) {
	int index = 0;
	for (int i = 0; i < graph.size(); i++) {
		if (v.getNum() == graph[i]->getNum()) {
			index = i;
			break;
		}
	}
	graph.erase(graph.begin()+index);
	
}

int Graph::getSize() {
	return graph.size();
}