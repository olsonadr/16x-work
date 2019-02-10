CC=g++
EXE_FILE=zoo_tycoon
INTERFACE=zoo_tycoon

all: $(EXE_FILE)

$(EXE_FILE): $(INTERFACE).cpp Animal.o Monkey.o Zoo.o
	$(CC) -std=c++11 -g -Wl,-z,origin,-rpath=\$$ORIGIN -I. -L. Animal.o Monkey.o Zoo.o $(INTERFACE).cpp -o $(EXE_FILE)

Zoo.o: Zoo.hpp Zoo.cpp #libhelp.so
	$(CC) -std=c++11 -g -c Zoo.cpp

Monkey.o: Monkey.hpp Monkey.cpp Animal.o
	$(CC) -std=c++11 -g -c Monkey.cpp

Animal.o: Animal.hpp Animal.cpp
	$(CC) -std=c++11 -g -c Animal.cpp

clean:
	rm -f *.o *.so $(EXE_FILE)
