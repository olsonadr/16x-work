CC=g++
EXE_FILE=window_test
INTERFACE=window_test
HPP_DIR=./headers
CPP_DIR=./source
OUT_DIR=./compiled

all: $(EXE_FILE) $(OUT_DIR)

$(EXE_FILE): $(CPP_DIR)/$(INTERFACE).cpp Card.o Hand.o Deck.o Game.o Player.o
	$(CC) -std=c++11 -g -Wl,-z,origin,-rpath=\$$ORIGIN -I$(HPP_DIR) -L$(OUT_DIR) Card.o Hand.o Deck.o Game.o Player.o $(INTERFACE).cpp -o $(EXE_FILE)

Element.o: $(HPP_DIR)/Element.hpp $(CPP_DIR)/Element.cpp
	$(CC) -std=c++11 -g -c $(CPP_DIR)/Element.cpp -o $(OUT_DIR)/Element.o
	
Container.o: $(HPP_DIR)/Container.hpp $(CPP_DIR)/Container.cpp
	$(CC) -std=c++11 -g -c $(CPP_DIR)/Container.cpp -o $(OUT_DIR)/Container.o

Window.o: $(HPP_DIR)/Window.hpp $(CPP_DIR)/Window.cpp
	$(CC) -std=c++11 -g -c $(CPP_DIR)/Window.cpp -o $(OUT_DIR)/Window.o

Panel.o: $(HPP_DIR)/Panel.hpp $(HPP_DIR)/Container.hpp $(CPP_DIR)/Panel.cpp
	$(CC) -std=c++11 -g -c $(CPP_DIR)/Panel.cpp -o $(OUT_DIR)/Panel.o

Label.o: $(HPP_DIR)/Label.hpp $(CPP_DIR)/Label.cpp
	$(CC) -std=c++11 -g -c $(CPP_DIR)/Label.cpp -o $(OUT_DIR)/Label.o

$(OUT_DIR):
	mkdir $(OUT_DIR)

clean:
	rm -f $(OUT_DIR)/* $(EXE_FILE)