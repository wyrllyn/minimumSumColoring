program: main.o solver.o solution.o graph.o vertex.o
	g++ main.o solver.o solution.o graph.o vertex.o -O3 -o program

main.o: main.cpp Solver.h
	g++ -c main.cpp -O3 -o main.o 

solver.o: Solver.cpp Solution.h
	g++ -c Solver.cpp -O3 -o solver.o

solution.o: Solution.cpp Graph.h
	g++ -c Solution.cpp -O3 -o solution.o

graph.o: Graph.cpp Vertex.h
	g++ -c Graph.cpp -O3 -o graph.o

vertex.o: Vertex.cpp
	g++ -c Vertex.cpp -O3 -o vertex.o

clean:
	rm -rf *.o program