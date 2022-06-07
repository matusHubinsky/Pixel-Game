#ifndef MAP_H_
#define MAP_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

#include "main.h"

void RandomizeMap();    
void CreateMap();
void DoorMap();
void WorldMap();

void DrawCircle(int centreX, int centreY, int radius);
void RewriteMap(int first[30][40], int second[30][40]);


#endif