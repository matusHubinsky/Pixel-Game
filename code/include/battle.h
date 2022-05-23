#ifndef BATTLE_H_
#define BATTLE_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>

#include "main.h" 

void PlayerAttack(struct Creature * creature, bool up, bool down, bool left, bool right);
bool EnemyAttack(struct Creature * creature);
bool PlayerDeath();

#endif
