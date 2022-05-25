
CC = gcc
CFLAGS = -std=c11 -m64 -O4 -g -Wall -I 
OFLAGS = -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lm
GAME = /home/leviathan/Documents/VUT/git/PixelGame/game/pixelgame

all:
	$(BIN)	

pixelgame: src/*.c include/*.h
	$(CC) $(CFLAGS) $< -c -o $@ 

run:
	$(CC) -c src/*.c $(CFLAGS) include && gcc *.o -o $(GAME) $(OFLAGS) 
	$(CC) -c src/*.c $(CFLAGS) include && gcc *.o -o ./pixelgame $(OFLAGS) && ./pixelgame

clean:
	rm *.o pixelgame