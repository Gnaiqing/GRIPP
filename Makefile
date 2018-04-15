#CFLAGS=-g
CFLAGS=-O2

all:run.exe
run.exe: Gripp.o  Graph.o main.cpp
	g++ $(CFLAGS) -std=c++11 Gripp.o Graph.o main.cpp -o run.exe
Gripp.o: Gripp.cpp Gripp.h Graph.h Util.h
	g++ $(CFLAGS) -c -std=c++11 Gripp.cpp -o Gripp.o
Graph.o: Graph.h Graph.cpp Util.h
	g++ $(CFLAGS) -c -std=c++11 Graph.cpp -o Graph.o

clean:
	rm *.o
dist: clean
	rm *.exe
tarball: 
	tar -czvf GRIPP.tar.gz data Graph.cpp Graph.h Gripp.cpp Gripp.h LICENSE main.cpp Makefile README.md Util.h

