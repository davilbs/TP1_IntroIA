CXXFLAGS=-Isrc
VPATH=src
objects = algo.o bfs.o ucs.o ids.o astar.o greedy.o

all: $(objects)

$(objects): %.o: %.cpp

build: $(objects)
	g++ -o TP1 main.cpp $(objects)

clean:
	rm TP1 *.o