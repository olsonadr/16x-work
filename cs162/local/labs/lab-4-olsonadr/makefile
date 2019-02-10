CC=g++
EXE_FILE=deal_hand
INTERFACE=deal_hand

all: $(EXE_FILE)

$(EXE_FILE): $(INTERFACE).cpp Hand.o Deck.o Card.o
	$(CC) -std=c++11 -g $(INTERFACE).cpp Hand.o Deck.o Card.o -o $(EXE_FILE)

Hand.o: Hand.cpp Hand.hpp
	$(CC) -std=c++11 -g -c Hand.cpp

Deck.o: Deck.cpp Deck.hpp
	$(CC) -std=c++11 -g -c Deck.cpp

Card.o: Card.cpp Card.hpp
	$(CC) -std=c++11 -g -c Card.cpp

clean:
	rm -f *.o $(EXE_FILE)
