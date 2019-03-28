CC=g++
EXE_FILE=hunt_the_wumpus
INTERFACE=$(CPP_DIR)/hunt_the_wumpus
LIB_NAME=panels
BUILD_DIR=build
OUT_DIR=bin
CPP_DIR=src
HPP_DIR=include
LIB_DIR=lib
LIB_DIR_REL=../lib
LIB_HPP_DIR=lib/include

all: $(EXE_FILE)
.PHONY: clean lib

lib:
	cd lib/cpp_panels/ && git pull && cd ../.. && make -C lib && make

$(EXE_FILE): $(OUT_DIR) $(INTERFACE).cpp $(LIB_DIR)/lib$(LIB_NAME).so $(BUILD_DIR)/Bats.o $(BUILD_DIR)/Gold.o $(BUILD_DIR)/Pit.o $(BUILD_DIR)/Wumpus.o $(BUILD_DIR)/Player.o $(BUILD_DIR)/Room.o $(CPP_DIR)/Game.cpp $(LIB_DIR)/lib$(LIB_NAME).so $(INTERFACE).cpp
	$(CC) -std=c++11 -g -I$(HPP_DIR) -I$(LIB_HPP_DIR) $(BUILD_DIR)/Bats.o $(BUILD_DIR)/Gold.o $(BUILD_DIR)/Pit.o $(BUILD_DIR)/Wumpus.o $(BUILD_DIR)/Player.o $(BUILD_DIR)/Room.o $(CPP_DIR)/Game.cpp $(INTERFACE).cpp -o $(OUT_DIR)/$(EXE_FILE) -L$(LIB_DIR) -Wl,-z,origin,-rpath=\$$ORIGIN/$(LIB_DIR_REL) -l$(LIB_NAME)

$(BUILD_DIR)/Bats.o: $(BUILD_DIR) $(CPP_DIR)/Bats.cpp
	$(CC) -std=c++11 -g -I$(HPP_DIR) -c $(CPP_DIR)/Bats.cpp -o $(BUILD_DIR)/Bats.o

$(BUILD_DIR)/Gold.o: $(BUILD_DIR) $(CPP_DIR)/Gold.cpp
	$(CC) -std=c++11 -g -I$(HPP_DIR) -c $(CPP_DIR)/Gold.cpp -o $(BUILD_DIR)/Gold.o

$(BUILD_DIR)/Pit.o: $(BUILD_DIR) $(CPP_DIR)/Pit.cpp
	$(CC) -std=c++11 -g -I$(HPP_DIR) -c $(CPP_DIR)/Pit.cpp -o $(BUILD_DIR)/Pit.o

$(BUILD_DIR)/Wumpus.o: $(BUILD_DIR) $(CPP_DIR)/Wumpus.cpp
	$(CC) -std=c++11 -g -I$(HPP_DIR) -c $(CPP_DIR)/Wumpus.cpp -o $(BUILD_DIR)/Wumpus.o

$(BUILD_DIR)/Player.o: $(BUILD_DIR) $(CPP_DIR)/Player.cpp
	$(CC) -std=c++11 -g -I$(HPP_DIR) -c $(CPP_DIR)/Player.cpp -o $(BUILD_DIR)/Player.o

$(BUILD_DIR)/Room.o: $(BUILD_DIR) $(CPP_DIR)/Room.cpp
	$(CC) -std=c++11 -g -I$(HPP_DIR) -c $(CPP_DIR)/Room.cpp -o $(BUILD_DIR)/Room.o

$(LIB_DIR)/lib$(LIB_NAME).so:
	make -C $(LIB_DIR)

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

$(OUT_DIR):
	mkdir $(OUT_DIR)

clean:
	rm -r -f $(BUILD_DIR) $(OUT_DIR)
	make -C $(LIB_DIR) clean
