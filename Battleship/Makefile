CC = g++
CFLAGS = -g -std=c++11

.PHONY: clean

all: battleship

battleship: interface.o game_logic.o main.cpp
	$(CC) $(CFLAGS) main.cpp interface.o game_logic.o -o battleship

interface.o: interface.cpp
	$(CC) $(CFLAGS) -c interface.cpp

game_logic.o: game_logic.cpp
	$(CC) $(CFLAGS) -c game_logic.cpp

clean:
	rm -f *.o battleship
