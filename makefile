program: main.o solver.o solution.o graph.o vertex.o
	g++ main.o solver.o solution.o graph.o vertex.o -o program

main.o: main.cpp Solver.h
	g++ -c main.cpp -o main.o 

solver.o: Solver.cpp Solution.h
	g++ -c Solver.cpp -o solver.o

solution.o: Solution.cpp Graph.h
	g++ -c Solution.cpp -o solution.o

graph.o: Graph.cpp Vertex.h
	g++ -c Graph.cpp -o graph.o

vertex.o: Vertex.cpp
	g++ -c Vertex.cpp -o vertex.o

clean:
	rm -rf *.o program