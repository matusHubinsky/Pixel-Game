#ifndef LIGHT_H_
#define LIGHT_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "main.h"

void Merge(t_vertexs * shared);
void CellsMap(int sx, int sy, int w, int h, int block_width, int pitch, t_vertexs * shared);
void Intersections1(t_vertexs * shared);


#endif