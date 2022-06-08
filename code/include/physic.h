#ifndef PHYSIC_H_
#define PHYSIC_H_

#include <stdio.h>

#include "main.h"

void updateMap();
bool AABB(float x, float y, int number, t_vertexs * shared);
void updatePhysic(t_vertexs * shared);
bool enemySee(struct Creature * creature, t_vertexs * shared);
void AI(t_vertexs * shared);

#endif