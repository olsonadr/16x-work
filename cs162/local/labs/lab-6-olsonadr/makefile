CC=g++

all: application

application: application.cpp Square.o Circle Rectangle Shape
	$(CC) -g application.cpp Square.o -o application

Square.o: Square.hpp Square.cpp
	$(CC) -g -c Square.cpp

Circle: Circle.hpp

Rectangle: Rectangle.hpp

Shape: Shape.hpp

clean:
	rm *.o application
