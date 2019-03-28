all: maze_test.cpp
.PHONY: maze_test.cpp
clean:
	rm *.o maze_test

maze_test.cpp: MazeLocation.hpp OpenSpace.o Wall.o Explorer.o Maze.o
	g++ -std=c++11 -g OpenSpace.o Wall.o Explorer.o Maze.o maze_test.cpp -o maze_test

OpenSpace.o: OpenSpace.cpp OpenSpace.hpp
	g++ -std=c++11 -g OpenSpace.cpp -c

Wall.o: Wall.cpp Wall.hpp
	g++ -std=c++11 -g Wall.cpp -c

Explorer.o: Explorer.cpp Explorer.hpp
	g++ -std=c++11 -g Explorer.cpp -c

Maze.o: Maze.cpp Maze.hpp
	g++ -std=c++11 -g Maze.cpp -c
