CC=g++
EXE_FILE=go_fish
INTERFACE=go_fish

all: $(EXE_FILE)

$(EXE_FILE): libhelp.so $(INTERFACE).cpp Card.o Hand.o Deck.o Game.o Player.o
	$(CC) -std=c++11 -g -Wl,-z,origin,-rpath=\$$ORIGIN -I. -L. -lhelp Card.o Hand.o Deck.o Game.o Player.o $(INTERFACE).cpp -o $(EXE_FILE)

Game.o: Game.hpp Game.cpp libhelp.so
	$(CC) -std=c++11 -g -c Game.cpp

Player.o: Player.hpp Player.cpp
	$(CC) -std=c++11 -g -c Player.cpp

Hand.o: Hand.hpp Hand.cpp
	$(CC) -std=c++11 -g -c Hand.cpp

Deck.o: Deck.hpp Deck.cpp
	$(CC) -std=c++11 -g -c Deck.cpp

Card.o: Card.hpp Card.cpp
	$(CC) -std=c++11 -g -c Card.cpp

libhelp.so: help.cpp help.hpp help.o
	$(CC) -std=c++11 -g -fPIC -shared help.o -o libhelp.so

help.o: help.cpp help.hpp
	$(CC) -std=c++11 -g -fPIC -c help.cpp

clean:
	rm -f *.o *.so $(EXE_FILE)
