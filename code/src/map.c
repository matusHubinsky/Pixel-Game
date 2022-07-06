/**
 * @file map.c
 * 
 * @brief operations working with map textures, rewriting map
 * @author Matus Hubinsky
 */

#include "map.h"
#include "textures.h"
#include "light.h"
#include "const.h"


int lvlN = 0;
lvl map;
long int random(void);

SDL_Rect mapRec[1200];
SDL_Rect mapSrc[1200];
SDL_Texture* mapTex[1200];


/**
 * @brief put empty space and edge walls at egdes of the map
 * @param
 * @return 
 */
void RandomizeMap() 
{
	for (int i = 0; i < 30; i++) 
	{
		for (int j = 0; j < 40; j++)
		{
            if (map[i][j] == 1)
            {
                if ((i == 0) && (i == 29)) map[i][j] = 0;
                if ((j == 0) && (j == 29)) map[i][j] = 0;
                if ((i == 1) && (i == 28)) map[i][j] = 3;
                if ((j == 1) && (j == 38)) map[i][j] = 3;
            }
		}
	}
}


/**
 * @brief load and set all map textures
 * @param
 * @return 
 */
void CreateMap()
{
    int k = 0;

    SDL_Rect Rec;
    SDL_Rect Src;
    SDL_Texture* texture;

    texture = LoadTexture("tex/map/black.png");

    for (int i = 0; i < 30; i++)
    {
        for (int j = 0; j < 40; j++)
        {
            if (map[i][j] == 0) texture = LoadTexture("tex/map/black.png");
            else if (map[i][j] == 1) texture = LoadTexture("tex/map/dirt.png");
            else if (map[i][j] == 2) texture = LoadTexture("tex/map/wood_1.png");
            else if (map[i][j] == 3) texture = LoadTexture("tex/map/brick.png");
            else if (map[i][j] == 4) texture = LoadTexture("tex/map/dirt.png");  
            
            Rec.x = j*BLOCK;
            Rec.y = i*BLOCK;
            Rec.w = BLOCK;
            Rec.h = BLOCK;

            Src.x = 0;
            Src.y = 0;
            Src.w = BLOCK;
            Src.h = BLOCK;

            mapRec[k] = Rec;
            mapSrc[k] = Src;
            mapTex[k] = texture;
            k++;
        }
    }
}


/**
 * @brief teleportation of player from door to door on the next map
 * @todo top and down teleportation
 * @param shared, Shared variables
 * @return 
 */
void DoorMap(t_vertexs * shared)
{
    // printf("Mapa: %i   %i %i\n", lvlN, player.rec.x, player.rec.y);
    if (player.rec.x >= 32 && player.rec.x <= 64)
    {
        if ((player.rec.y >= 416 && player.rec.y <= 448) || (player.rec.y >= 480 && player.rec.y <= 512))
        {
            player.rec.x = 1248 - 64;
            RewriteMap(map, world[lvlN-1], shared);
            lvlN--;
        } 
    }
    else if (player.rec.x >= 1184 && player.rec.x <= 1216)
    {
        if ((player.rec.y >= 416 && player.rec.y <= 448) || (player.rec.y >= 480 && player.rec.y <= 512))
        {
            player.rec.x = 64;
            RewriteMap(map, world[lvlN+1], shared);
            lvlN++;
        }
    }

    /*
    else if (player.rec.y == 768)
    {
        if (player.rec.x == 640 or player.rec.x == 672) player.rec.y = 160;
    }
    else if (player.rec.y == 160)
    {
        if (player.rec.x == 640 or player.rec.x == 672) player.rec.y = 768;
    }
    */
}

/**
 * @brief set doors
 * @param
 * @return 
 */
void WorldMap()
{
    for (int i = 0; i < 4; i++)
    {  
        if (i != 3)
        {
            world[i][13][38] = 2;
            world[i][14][38] = 2;
            world[i][15][38] = 2;
            world[i][16][38] = 2;
        }
        if (i != 0)
        {
            world[i][13][1] = 2;
            world[i][14][1] = 2;
            world[i][15][1] = 2;
            world[i][16][1] = 2;
        }
    }
}


/**
 * @brief rewrite first map with second map
 * 
 * This FUNC is used after entering door and before teleporation into next room
 * 
 * @param first, first map
 * @param second, second map
 * @param shared, shared variable
 * @return 
 */
void RewriteMap(int first[30][40], int second[30][40], t_vertexs * shared) // zmena mapy
{
	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 40; j++)
		{
            first[i][j] = second[i][j];
        }
	}
    CreateMap();
    RandomizeMap();
    CellsMap(0, 0, 40, 30, 40, shared);
}

/*** End of file map.c ***/