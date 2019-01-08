CC=g++
EXE_FILE=muldiv_print

all: $(EXE_FILE)

$(EXE_FILE): muldiv.o muldiv.hpp muldiv_print.cpp
	$(CC) muldiv.o muldiv_print.cpp -o $(EXE_FILE)

muldiv.o: muldiv.hpp muldiv.cpp
	$(CC) -c muldiv.cpp

clean:
	rm -f *.o $(EXE_FILE)
