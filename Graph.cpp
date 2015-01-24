#include "Graph.h"


Graph::Graph() {
}



Graph::Graph(const Graph& g) : size(g.size), graph(g.graph.size()) {

    for(int i = 0; i < g.graph.size(); i++) {
            graph[i] = new Vertex(*g.graph[i]);
    }
}

Graph::Graph(string filename) {
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
        		for (int i = 1; i <= size; i++) {
        			addVertex(new Vertex(i));
        		}
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
        cout << "DONE : " << size << endl;
    }
    else {
   		cerr << "Could not open file" << endl;
    }
}

Graph::~Graph(){
   // cout << " calling graph destructor" << endl;
   /* for (int i = 0; i < graph.size(); i++) {
       delete graph[i]/*->~Vertex()*/;
    //}
    while(!graph.empty()) {
        if (graph.back() != NULL)
            delete graph.back();
        graph.pop_back();
    }
   // cout << "is the segfault there ?" << endl;
}

/////////////////////////
////// GETTERS //////////
/////////////////////////

vector<Vertex*> Graph::getGraph() {
	return graph;
}

int Graph::getSize() {
    return graph.size();
}

////////////////////////////////////////
// INSERT & REMOVE VERTEX METHODS //////
///////////////////////////////////////

void Graph::addVertex(Vertex * v) {
	graph.push_back(v);
}


// seems to work
// removes vertex num = v
void Graph::removeVertex(int v) {
	int index = 0;
	for (int i = 0; i < graph.size(); i++) {
		if (v == graph[i]->getNum()) {
			index = i;
			break;
		}
	}
    delete graph[index];
	graph.erase(graph.begin()+index);
	
}

/////////////////////////
//// CHECK METHODS ///////
/////////////////////////

bool Graph::vertexIsInto(int n) {
    for (int i = 0; i < graph.size() ; i++) {
        if (graph[i]->getNum() == n) {
            return true;
        }
    }
    return false;
}

//TODO: check method
bool Graph::canBeAdded(Vertex v) {
    for (int i = 0; i < graph.size(); i++) {
        if(v.isLinked(graph[i]->getNum()) || graph[i]->isLinked(v.getNum())) {
            return false;
        }
    }
    return true;
}

///////////////////
//////////////////

int Graph::getIndexVertex(int n) {
    for (int i = 0; i < graph.size(); i++) {
        if (graph[i]->getNum() == n) {
            return i;
        }
    }
    return -1;
}



/////////////////////////////
// PRINT A GRAPH ///////////
///////////////////////////

void Graph::printGraph() {
    for (int i = 0 ; i < graph.size(); i++) {
        cout << graph[i]->getNum() << " ";
    }
    cout << endl;
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