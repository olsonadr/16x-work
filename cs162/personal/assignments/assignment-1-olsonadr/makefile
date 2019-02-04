CC=g++
EXE_FILE=explore_econdata
INTERFACE=explore_econdata
HEADER=econdata
IMPLEMENTATION=econdata
LIBRARY=help

all: $(EXE_FILE)

$(EXE_FILE): lib$(LIBRARY).so $(INTERFACE).cpp $(HEADER).hpp $(IMPLEMENTATION).o
	$(CC) -std=c++11 -Wl,-z,origin,-rpath=\$$ORIGIN -I. -L. -l$(LIBRARY) $(IMPLEMENTATION).o $(INTERFACE).cpp -o $(EXE_FILE)

$(IMPLEMENTATION).o: $(HEADER).hpp $(IMPLEMENTATION).cpp lib$(LIBRARY).so
	$(CC) -std=c++11 -c $(IMPLEMENTATION).cpp

lib$(LIBRARY).so: $(LIBRARY).cpp $(LIBRARY).hpp $(LIBRARY).o
	$(CC) -std=c++11 -fPIC -shared $(LIBRARY).o -o lib$(LIBRARY).so

$(LIBRARY).o: $(LIBRARY).cpp $(LIBRARY).hpp
	$(CC) -std=c++11 -fPIC -c $(LIBRARY).cpp

clean:
	rm -f *.o $(EXE_FILE) lib$(LIBRARY).so
