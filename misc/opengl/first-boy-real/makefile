CC=g++
EXE_FILE=first_boy_interface
INTERFACE=first_boy_interface
HEADER=first_boy
IMPLEMENTATION=first_boy

all: $(EXE_FILE)

$(EXE_FILE): $(INTERFACE).cpp $(HEADER).hpp $(IMPLEMENTATION).o
	$(CC) -std=c++11 -lglfw -lglfw3 -lGL -lGLEW $(IMPLEMENTATION).o $(INTERFACE).cpp common/shader.cpp -o $(EXE_FILE)

$(IMPLEMENTATION).o: $(HEADER).hpp $(IMPLEMENTATION).cpp
	$(CC) -std=c++11 -c $(IMPLEMENTATION).cpp

clean:
	rm -f *.o $(EXE_FILE)
