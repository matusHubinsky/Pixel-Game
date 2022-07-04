
#include "battle.h"

// Deal damage to all the enemies that are near player
void PlayerAttack(struct Creature * creature, bool up, bool down, bool left, bool right)
{
	int hit = false;
	int distance = 64; 
	int k;

	for (int i = 0; i < ENEMY_NUMBER; i++)
	{
		if (up == true && (((enemies[i].rec.y - creature -> rec.y) < 0) && \
		 (enemies[i].rec.y - creature -> rec.y) > -distance))
		{
			hit = true;
			k = i;
			break;
		}
		if (down == true && (((enemies[i].rec.y - creature -> rec.y) < distance) && \
			(enemies[i].rec.y - creature -> rec.y) > 0)) 
		{
			hit = true;
			k = i;
			break;
		}
		if (left == true && (((enemies[i].rec.x - creature -> rec.x) < 0) && \
			(enemies[i].rec.x - creature -> rec.x) > -distance))
		{
			hit = true;
			k = i;
			break;
		}
		if (right == true && (((enemies[i].rec.y - creature -> rec.y) < distance) && \
			(enemies[i].rec.y - creature -> rec.y) > 0))
		{
			hit = true;
			k = i;
			break;
		}
	}

	if (hit)
	{
		enemies[k].health = 0;
		enemies[k].tex = LoadTexture("tex/player/death.png");
	}
}


// Calculate distance of all enemies and deal damage to player
bool EnemyAttack(struct Creature * creature)
{
	if ((abs(creature -> rec.x - player.rec.x) < 32) && (abs(creature -> rec.y - player.rec.y) < 32))
	{
		player.health = 0;
		return true;	
	}
	else return false;
}


// Kill player if outside of the boder
bool PlayerDeath()
{
	if (player.rec.x < 0 || player.rec.y < 0)
	{
		player.health = 0;
		return true;
	}
	if (player.rec.x > 1280 || player.rec.y > 960)
	{
		player.health = 0;
		return true;
	}

	return false;
}
