EXEC = ./pixelgame
CC = gcc
CFLAGS = -std=c11 -m64 -O3 -g -Wall -I
LDLIBS = -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lm
GAME = /home/leviathan/Documents/VUT/git/PixelGame/game/pixelgame

# doesnt't work yet
SRCS = $(wildcard *.c)
HEDS = $(wildcard *.h)
OBJS = $(patsubst %.c,%.o,$(SRCS))

# -pthread

all:
	$(CC) -c src/*.c $(CFLAGS) include && $(CC) *.o -o $(GAME) $(LDLIBS) 
	$(CC) -c src/*.c $(CFLAGS) include && $(CC) *.o -o ./pixelgame $(LDLIBS) && $(EXEC)

pixelgame: src/*.c include/*.h
	$(CC) $(CFLAGS) $< -c -o $@ 

clean:
	rm $(OBJS) $(EXEC) *.o