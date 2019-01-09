CC=g++
EXE_FILE=explore_econdata

all: $(EXE_FILE)

$(EXE_FILE): explore_econdata.cpp econdata.hpp econdata.o
	$(CC) -lhelp -L. -I. econdata.o explore_econdata.cpp -o $(EXE_FILE)

muldiv.o: econdata.hpp econdata.cpp
	$(CC) -c econdata.cpp

clean:
	rm -f *.o $(EXE_FILE)

