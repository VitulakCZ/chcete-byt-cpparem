game: main.o
	g++ -o game main.o -lsfml-audio
main.o: main.cpp
	g++ -c main.cpp
