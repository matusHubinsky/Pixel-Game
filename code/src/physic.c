
#include "textures.h"
#include "light.h"
#include "map.h"
#include "battle.h"


// update character map, calculate new possition of every character
void updateMap(lvl * Cmap)
{
	int row, collumn;
	
	for (int i = 0; i < MAP_WIDTH; i++)
	{
		for (int j = 0; j < MAP_HEIGTH; j++)
		{
			*Cmap[j][i] = 0;
		}
	}

	for (int i = 0; i < ENEMY_NUMBER; i++)
	{
		row = enemies[i].rec.y / BLOCK;
		collumn = enemies[i].rec.x / BLOCK;

		*Cmap[row][collumn] = 1;
	}

	row = player.rec.y / BLOCK;
	collumn = player.rec.x / BLOCK;

	*Cmap[row][collumn] = 1;
}

// colison detection
bool AABB(float x, float y, int number, t_vertexs * shared)
{	
	// TODO: clear
	int row, collumn;
	bool can = false;
	row = y / BLOCK;
	collumn = x / BLOCK;

	// if character is stading at doors, call door teleportation func
	if (map[row][collumn] == 2) 
		DoorMap(shared);
	
	if (map[row][collumn] != 3)
	{
		for (int i = 0; i < ENEMY_NUMBER; i++)
		{
			// cheking enemies
			if (number != i)	
			{
				if ((x >= enemies[i].rec.x) && (x <= enemies[i].rec.x + BLOCK) && (y >= enemies[i].rec.y) && (y <= enemies[i].rec.y + BLOCK)) return can;
			}
	
			// checking player
			if (number != ENEMY_NUMBER)	  
			{
				if ((x >= player.rec.x) && (x <= player.rec.x + BLOCK) && (y >= player.rec.y) && (y <= player.rec.y + BLOCK)) return can;			
			}
		}
		can = true;
		return can;
	}
	return can;
}


// MAIN FUNC
void updatePhysic(t_vertexs * shared)
{
	float new_x = player.rec.x + (player.velocity_x * player.speed);
	float new_y = player.rec.y + (player.velocity_y * player.speed);

	// calculate new plyer possition
	if (player.velocity_x > 0) new_x += BLOCK;
	if (player.velocity_y > 0) new_y += BLOCK;

	// check players new possition
	if (AABB(new_x, new_y, ENEMY_NUMBER, shared))
	{
		// if there are no collison, player is moved to new possition
		player.rec.x += (float) player.velocity_x * player.speed;
		player.rec.y += (float) player.velocity_y * player.speed;
	}

	if (PlayerDeath())
	{
		DeathScreen();
	}
}


bool enemySee(struct Creature * creature, t_vertexs * shared)
{
	bool valid = false;

	creature -> rec.x += BLOCK / 2;
	creature -> rec.y += BLOCK / 2;

	player.rec.x += BLOCK / 2;
	player.rec.y += BLOCK / 2;

	float rdx = player.rec.x - creature -> rec.x;
	float rdy = player.rec.y - creature -> rec.y;

	float min_t1 = INFINITY;
	float min_x = 0, min_y = 0;

	float sdx = player.rec.x;
	float sdy = player.rec.y;

    if (fabs(sdx - rdx) > 0.0f && fabs(sdy - rdy) > 0.0f)
    {
        float t2 = (rdx * (player.rec.y - creature -> rec.y) + (rdy * (creature -> rec.x - player.rec.x))) / (sdx * rdy - sdy * rdx);
        float t1 = (player.rec.x + sdx * t2 - creature -> rec.x) / rdx;

        if (t1 > 0 && t2 >= 0 && t2 <= 1.0f)
        {
            if (t1 < min_t1)
            {
                min_t1 = t1;
                min_x = creature -> rec.x + rdx * t1;
                min_y = creature -> rec.y + rdy * t1;
                valid = true;

                creature -> vidim = true;
            }
        }
    }

	rdx = player.rec.x - creature -> rec.x;
	rdy = player.rec.y - creature -> rec.y;

	for (int i = 0; i < shared -> edge_map_index; i++)
	{
	    Edge e1 = shared -> edgeMap[i];
	    float sdx = e1.end_x - e1.start_x;
	    float sdy = e1.end_y - e1.start_y;

	    if (fabs(sdx - rdx) > 0.0f && fabs(sdy - rdy) > 0.0f)
	    {
	        float t2 = (rdx * (e1.start_y - creature -> rec.y) + (rdy * (creature -> rec.x - e1.start_x))) / (sdx * rdy - sdy * rdx);
	        float t1 = (e1.start_x + sdx * t2 - creature -> rec.x) / rdx;

	        if (t1 > 0 && t2 >= 0 && t2 <= 1.0f)
	        {
	            if (t1 < min_t1)
	            {
	                min_t1 = t1;
	                min_x = creature -> rec.x + rdx * t1;
	                min_y = creature -> rec.y + rdy * t1;
	                valid = true;

	                creature -> vidim = false;
	            }
	        }
	    }
	}
    if (valid)
    {
    	creature -> sight.x = min_x;
    	creature -> sight.y = min_y;
    }
	creature -> rec.x -= BLOCK / 2;
	creature -> rec.y -= BLOCK / 2;

	player.rec.x -= BLOCK / 2;
	player.rec.y -= BLOCK / 2;

	return valid;
}


void AI(t_vertexs * shared)
{
    for (int i = 0; i < ENEMY_NUMBER; i++)
    {
        if (enemies[i].health != 0)
        {
            enemySee(&enemies[i], shared);

            if (enemies[i].vidim == true)
            {
                if (player.rec.x > enemies[i].rec.x)
                {
                	enemies[i].velocity_x = 1;	
                } 
                if (player.rec.x < enemies[i].rec.x)
                {
                	enemies[i].velocity_x = -1;	
                } 
                if (player.rec.y > enemies[i].rec.y)
                {
                	enemies[i].velocity_y = 1;	
                } 
                if (player.rec.y < enemies[i].rec.y) 
                {
                	enemies[i].velocity_y = -1;
                }

                if (player.rec.x == enemies[i].rec.x) enemies[i].velocity_x = 0;
                if (player.rec.y == enemies[i].rec.y) enemies[i].velocity_y = 0;

                float new_x = enemies[i].rec.x + (enemies[i].velocity_x * enemies[i].speed);
                float new_y = enemies[i].rec.y + (enemies[i].velocity_y * enemies[i].speed);

                if (enemies[i].velocity_x > 0) new_x += BLOCK;
                if (enemies[i].velocity_y > 0) new_y += BLOCK;

                if (AABB(new_x, new_y, i, shared))
                {
                    if (enemies[i].velocity_x != 0 && enemies[i].velocity_y != 0)
                    {
                        enemies[i].rec.x += (float) (enemies[i].velocity_x * enemies[i].speed) / 1.4142;
                        enemies[i].rec.y += (float) (enemies[i].velocity_y * enemies[i].speed) / 1.4142;
                    }
                    else
                    {
                        enemies[i].rec.x += (float) enemies[i].velocity_x * enemies[i].speed;
                        enemies[i].rec.y += (float) enemies[i].velocity_y * enemies[i].speed;
                    }   
                }
                if (EnemyAttack(&enemies[i]))
                {
                	DeathScreen();
                }
            }
        }
        else 
        {
            enemies[i].rec.x = 0;
            enemies[i].rec.y = 0;
        }
    }
}