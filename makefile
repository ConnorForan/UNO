CC=g++
CFLAGS = -c -Wall

all: unogame clean

unogame: Uno.o CompPlayer.o HumanPlayer.o Player.o Card.o Game.o
	$(CC) Uno.o CompPlayer.o HumanPlayer.o Player.o Card.o Game.o -o unogame

Uno.o: Uno.cpp
	$(CC) $(CFLAGS) Uno.cpp

CompPlayer.o: CompPlayer.cpp
	$(CC) $(CFLAGS) CompPlayer.cpp

HumanPlayer.o: HumanPlayer.cpp
	$(CC) $(CFLAGS) HumanPlayer.cpp

Player.o: Player.cpp
	$(CC) $(CFLAGS) Player.cpp
	
Card.o: Card.cpp
	$(CC) $(CFLAGS) Card.cpp

Game.o: Game.cpp
	$(CC) $(CFLAGS) Game.cpp

clean:
	rm *o