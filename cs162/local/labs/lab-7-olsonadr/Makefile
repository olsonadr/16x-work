CC=g++

all: debugging-demo debugging-1 debugging-2 debugging-3

debugging-demo: debugging-demo.cpp
	$(CC) -g debugging-demo.cpp -o debugging-demo

debugging-1: debugging-1.cpp
	$(CC) -g debugging-1.cpp -o debugging-1

debugging-2: debugging-2.cpp dynarray.o dynarray.hpp
	$(CC) -g debugging-2.cpp dynarray.o -o debugging-2

debugging-3: debugging-3.cpp
	$(CC) -g debugging-3.cpp -o debugging-3

dynarray.o: dynarray.cpp dynarray.hpp
	$(CC) -g -c dynarray.cpp -o dynarray.o

clean:
	rm -f *.o debugging-demo debugging-1 debugging-2 debugging-3
