all: compile link

compile:
	g++ -Isrc/include -c main.cpp node.cpp grid.cpp
link:
	g++ main.o node.o grid.o -o main -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system
