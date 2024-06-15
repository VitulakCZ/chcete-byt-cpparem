NO_SFML = 0
ifeq ($(NO_SFML), 0)
game: main.o
	g++ -o game main.o -lsfml-audio
	rm main.o
main.o: main.cpp
	g++ -c main.cpp
else
game: main.cpp
	g++ -o game main.cpp -DNO_SFML=1
endif
