#ifndef LIGHT_H_
#define LIGHT_H_

#include "main.h"

void Merge(t_vertexs * shared);
void CellsMap(int sx, int sy, int w, int h, int pitch, t_vertexs * shared);
void Intersections1(t_vertexs * shared, bool KEYS[322]);


#endif