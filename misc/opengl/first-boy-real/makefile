CC=g++
EXE_FILE=first_boy_interface
INTERFACE=first_boy_interface
HEADER=first_boy
IMPLEMENTATION=first_boy
SHADER_HANDLER=common/shader

all: $(EXE_FILE)

$(EXE_FILE): $(INTERFACE).cpp $(HEADER).hpp $(IMPLEMENTATION).o
	$(CC) -std=c++11 -lglfw -lglfw3 -lGL -lGLEW $(IMPLEMENTATION).o $(INTERFACE).cpp $(SHADER_HANDLER).cpp -o $(EXE_FILE) -g

$(IMPLEMENTATION).o: $(HEADER).hpp $(IMPLEMENTATION).cpp
	$(CC) -std=c++11 -c $(IMPLEMENTATION).cpp -g

clean:
	rm -f *.o $(EXE_FILE)
