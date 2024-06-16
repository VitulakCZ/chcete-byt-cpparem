NO_SFML = 0
ifeq ($(NO_SFML), 0)
game: main.cpp
	g++ -o game main.cpp -lsfml-audio
else
game: main.cpp
	g++ -o game main.cpp -DNO_SFML=1
endif
