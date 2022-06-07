#include "map.h"
#include "textures.h"
#include "light.h"
#include "world.h"
#include "const.h"

#include <stdlib.h>
#include <string.h>


int lvlN = 0;

lvl map;

long int random(void);

SDL_Rect mapRec[1200];
SDL_Rect mapSrc[1200];
SDL_Texture* mapTex[1200];

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


void CreateMap() // nacitanie textur
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


void DoorMap() // teleportacia pri vstupe do dveri
{
    // printf("Mapa: %i   %i %i\n", lvlN, player.rec.x, player.rec.y);
    if (player.rec.x >= 32 && player.rec.x <= 64)
    {
        if ((player.rec.y >= 416 && player.rec.y <= 448) || (player.rec.y >= 480 && player.rec.y <= 512))
        {
            player.rec.x = 1248 - 64;
            RewriteMap(map, world[lvlN-1]);
            lvlN--;
        } 
    }
    else if (player.rec.x >= 1184 && player.rec.x <= 1216)
    {
        if ((player.rec.y >= 416 && player.rec.y <= 448) || (player.rec.y >= 480 && player.rec.y <= 512))
        {
            player.rec.x = 64;
            RewriteMap(map, world[lvlN+1]);
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

    // horna a dolna mapa 
}


void WorldMap() // nastavenie dveri
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


void RewriteMap(int first[30][40], int second[30][40]) // zmena mapy
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
    CellsMap(0, 0, 40, 30, 32, 40);
}

