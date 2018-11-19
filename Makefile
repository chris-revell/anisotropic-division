# Compile with Intel c++ compiler

CC=icpc
CFlags=-c -Wall -std=c++11 -g -O0
CLibs=-larmadillo
LDFLAGS=-ggdb -std=c++11 -O0 -Wall

all: anisotropicdivision clean

anisotropicdivision: main.o cell.o
	$(CC) main.o cell.o -o anisotropicdivision $(LDFLAGS)

main: main.cpp
	$(CC) $(CFlags) main.cpp $(CLibs)

cell: cell.cpp
	$(CC) $(CFlags) cell.cpp $(CLibs)

clean:
	rm *.o
	rm *.gch
