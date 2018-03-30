# -O2 -g
all:run.exe
run.exe: Gripp.o  Graph.o main.cpp
	g++ -g -std=c++11 Gripp.o Graph.o main.cpp -o run.exe
Gripp.o: Gripp.cpp Gripp.h Graph.h Util.h
	g++ -g -c -std=c++11 Gripp.cpp -o Gripp.o
Graph.o: Graph.h Graph.cpp Util.h
	g++ -g -c -std=c++11 Graph.cpp -o Graph.o

clean:
	rm *.o
dist: clean
	rm *.exe
