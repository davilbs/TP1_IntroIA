algo.o: algo.cpp
	gcc -c algo.cpp -o algo.o

bfs.o: bfs.cpp
	gcc -c bfs.cpp -o bfs.o

ucs.o: ucs.cpp
	gcc -c ucs.cpp -o ucs.o

ids.o: ids.cpp
	gcc -c ids.cpp -o ids.o

astar.o: astar.cpp
	gcc -c astar.cpp -o astar.o

build: algo.o bfs.o ucs.o ids.o astar.o
	g++ -o TP1 main.cpp algo.o bfs.o ucs.o ids.o astar.o

clean:
	rm TP1 *.o