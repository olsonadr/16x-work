CC=g++
EXE_FILE=escape_cs
INTERFACE=$(CPP_DIR)/escape_cs
LIB_NAME=panels
BUILD_DIR=build
OUT_DIR=bin
CPP_DIR=src
HPP_DIR=include
HPP_DIRS_-I=$(HPP_DIR) -I$(LIB_HPP_DIR)
LIB_DIR=lib
LIB_DIR_REL=../lib
LIB_HPP_DIR=lib/include
INIT_CHECK=$(LIB_DIR)/cpp_panels/makefile


# Defining thing for line-breaks in info outputs
define n


endef


all: $(INIT_CHECK) $(EXE_FILE)
.PHONY: clean lib


# Initializes the submodule and updates it if the person hasn't done so yet
$(INIT_CHECK):
	@echo $(n)
	@echo "=== NO === Initializing library submodule..."
	@echo "=== NO === This might require you to type in a password because you\'re cloning another of my git repos for the UI..."
	git submodule init
	git submodule update
	@echo "=== NO === Submodule added! Library source code in /lib/cpp_panels directory."
	@echo $(n)


lib:
	@echo $(n)
	@echo "=== NO === Making the library shared object file..."
	cd lib/cpp_panels/ && git pull && cd ../.. && make -C lib && make
	@echo "=== NO === Library file made, stored in the /lib directory!"
	@echo $(n)

clean:
	@echo $(n)
	@echo "=== NO === Cleaning project and library temp files..."
	rm -r -f $(BUILD_DIR) $(OUT_DIR)
	make -C $(LIB_DIR) clean
	@echo "=== NO === Cleaned!"
	@echo $(n)


$(EXE_FILE): $(OUT_DIR) $(INTERFACE).cpp $(HPP_DIR)/MazePerson.hpp $(BUILD_DIR)/IntrepidStudent.o $(BUILD_DIR)/TA.o $(BUILD_DIR)/Instructor.o $(HPP_DIR)/MazeLocation.hpp $(HPP_DIR)/Wall.hpp $(BUILD_DIR)/OpenSpace.o $(BUILD_DIR)/MazeLevel.o $(BUILD_DIR)/Maze.o $(BUILD_DIR)/Game.o
	@echo $(n)
	@echo "=== NO === Compiling and linking executable file..."
	$(CC) -std=c++11 -g -I$(HPP_DIRS_-I) $(BUILD_DIR)/IntrepidStudent.o $(BUILD_DIR)/TA.o $(BUILD_DIR)/Instructor.o $(BUILD_DIR)/OpenSpace.o $(BUILD_DIR)/MazeLevel.o $(BUILD_DIR)/Maze.o $(BUILD_DIR)/Game.o $(INTERFACE).cpp -o $(OUT_DIR)/$(EXE_FILE) -L$(LIB_DIR) -Wl,-z,origin,-rpath=\$$ORIGIN/$(LIB_DIR_REL) -l$(LIB_NAME)
	@echo "=== NO === Done! Should be in the /bin directory. Run it relative from root or from /bin."
	@echo $(n)


$(BUILD_DIR)/Game.o: $(BUILD_DIR) $(CPP_DIR)/Game.cpp $(HPP_DIR)/Game.hpp
	$(CC) -std=c++11 -g -I$(HPP_DIRS_-I) -c $(CPP_DIR)/Game.cpp -o $(BUILD_DIR)/Game.o

$(BUILD_DIR)/Maze.o: $(BUILD_DIR) $(CPP_DIR)/Maze.cpp $(HPP_DIR)/Maze.hpp
	$(CC) -std=c++11 -g -I$(HPP_DIRS_-I) -c $(CPP_DIR)/Maze.cpp -o $(BUILD_DIR)/Maze.o

$(BUILD_DIR)/MazeLevel.o: $(BUILD_DIR) $(CPP_DIR)/MazeLevel.cpp $(HPP_DIR)/MazeLevel.hpp
	$(CC) -std=c++11 -g -I$(HPP_DIRS_-I) -c $(CPP_DIR)/MazeLevel.cpp -o $(BUILD_DIR)/MazeLevel.o

$(BUILD_DIR)/OpenSpace.o: $(BUILD_DIR) $(CPP_DIR)/OpenSpace.cpp $(HPP_DIR)/OpenSpace.hpp $(HPP_DIR)/MazeLocation.hpp
	$(CC) -std=c++11 -g -I$(HPP_DIRS_-I) -c $(CPP_DIR)/OpenSpace.cpp -o $(BUILD_DIR)/OpenSpace.o

$(BUILD_DIR)/Instructor.o: $(BUILD_DIR) $(CPP_DIR)/Instructor.cpp $(HPP_DIR)/Instructor.hpp $(HPP_DIR)/MazePerson.hpp
	$(CC) -std=c++11 -g -I$(HPP_DIRS_-I) -c $(CPP_DIR)/Instructor.cpp -o $(BUILD_DIR)/Instructor.o

$(BUILD_DIR)/TA.o: $(BUILD_DIR) $(CPP_DIR)/TA.cpp $(HPP_DIR)/TA.hpp $(HPP_DIR)/MazePerson.hpp
	$(CC) -std=c++11 -g -I$(HPP_DIRS_-I) -c $(CPP_DIR)/TA.cpp -o $(BUILD_DIR)/TA.o

$(BUILD_DIR)/IntrepidStudent.o: $(BUILD_DIR) $(CPP_DIR)/IntrepidStudent.cpp $(HPP_DIR)/IntrepidStudent.hpp $(HPP_DIR)/MazePerson.hpp $(LIB_DIR)/lib$(LIB_NAME).so
	$(CC) -std=c++11 -g -I$(HPP_DIRS_-I) -c $(CPP_DIR)/IntrepidStudent.cpp -o $(BUILD_DIR)/IntrepidStudent.o


$(LIB_DIR)/lib$(LIB_NAME).so:
	@echo $(n)
	@echo "=== NO === Making the library shared object file..."
	make -C $(LIB_DIR)
	@echo "=== NO === Library file made, stored in the /lib directory!"
	@echo $(n)


$(BUILD_DIR):
	mkdir $(BUILD_DIR)

$(OUT_DIR):
	mkdir $(OUT_DIR)
