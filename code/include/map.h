#ifndef MAP_H_
#define MAP_H_

#include "main.h"

void RandomizeMap();    
void CreateMap();
void DoorMap(t_vertexs * shared);
void WorldMap();

void DrawCircle(int centreX, int centreY, int radius);
void RewriteMap(int first[30][40], int second[30][40], t_vertexs * shared);


#endif