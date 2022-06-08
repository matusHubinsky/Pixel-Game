#ifndef BATTLE_H_
#define BATTLE_H_

#include "main.h" 

void PlayerAttack(struct Creature * creature, bool up, bool down, bool left, bool right);
bool EnemyAttack(struct Creature * creature);
bool PlayerDeath();

#endif
