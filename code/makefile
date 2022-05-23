
CC = gcc
CFLAGS = -std=c11 -m64 -g -Wall -I -lSDL2main -lSDL2 -lSDL2_image -lm
BIN = pixelgame
#DEST = bin/debug/main 

all:
	$(BIN)	

pixelgame: src/*.c include/*.h
	$(CC) $(CFLAGS) $< -c -o $@ 

run:
	gcc -c src/*.c -std=c11 -m64 -g -Wall -I include && gcc *.o -o ./pixelgame -lSDL2main -lSDL2 -lSDL2_image -lm && ./pixelgame