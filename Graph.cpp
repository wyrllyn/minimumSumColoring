#include "Graph.h"


Graph::Graph() {
}



Graph::Graph(const Graph& g) : size(g.size), graph(g.graph.size()) {
/*    if ((g.graph == graph)) {
      //  cout << "same" << endl;
    }
    else {
     //   cout << "hey" << endl;
        while(!graph.empty()) {
            delete graph.back();
            graph.pop_back();
        }
       // graph.reserve(g.graph.size());
        for (int i = 0; i < g.graph.size(); i++) {
       //     cout << "test" << endl;
            graph.push_back(g.graph[i]);
        }
     //   for(int i = 0; i < g.graph.size(); i++) {
         //   if (graph[i] == NULL) {
     //           graph[i] = new Vertex(*g.graph[i]);
           /* }
            else {*/
               // cout << "hey null" << endl;
           //     graph[i] = g.graph[i];
          //  }
               
      //  }
  //  graph.reserve(g.graph.size());
    for (int i = 0; i < g.graph.size(); i++) {
    //    cout << "graph --------" << i << " on " << g.graph.size() << endl;
     //   cout << g.graph[i]->getNum() << endl;
        graph[i] = new Vertex(*g.graph[i]);
     //   cout << "done in graph const" << endl;
    }
 //   cout << "DONE" << endl;
}

void Graph::copy(const Graph& g) {
    if (g.graph != graph) {
        if (g.graph.size() < graph.size() ) {
            for (int i = graph.size() ; i >= g.graph.size() ; i-- ) {
                delete graph.back();
                graph.pop_back();
            }
            for (int i = g.graph.size() - 1 ; i >= 0 ; i--) {
                 delete graph.back();
                graph.pop_back();
                graph.push_back(new Vertex(*g.graph[i]));
            }
        }
        else {
            while(!graph.empty()) {
                delete graph.back();
                graph.pop_back();
            }
            for (int i = 0; i < g.graph.size(); i++) {
                graph[i] = new Vertex(*g.graph[i]);
            }
        }
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
        delete graph.back();
        graph.pop_back();
    }
   // cout << "is the segfault there ?" << endl;
}

bool Graph::operator !=(const Graph &b) const {
    if (graph.size() != b.graph.size())
        return true;
    else {
        for (int i = 0; i < graph.size(); i++) {
            if(graph[i]->getNum() != b.graph[i]->getNum()) {
                return true;
            }
        }

    }
    return false;
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
  //  cout << "into get getIndexVertex" << endl;
   // cout << "graph size " << graph.size() << endl;
    for (int i = 0; i < graph.size(); i++) {
      //  cout << "------------------- i = " << i << endl;
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