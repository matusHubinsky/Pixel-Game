#ifndef PHYSIC_H_
#define PHYSIC_H_

#include <stdio.h>

void updateMap();

bool AABB(float x, float y, int number);

void updatePhysic();

bool enemySee(struct Creature * creature);

void AI();

#endif