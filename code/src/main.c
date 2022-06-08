
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "init.h"
#include "keyboard.h"
#include "textures.h"
#include "map.h"
#include "main.h"
#include "light.h"
#include "world.h"
#include "vector.h"
#include "physic.h"

    
lvl Cmap;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* texture = NULL;

struct Creature player;
struct Creature enemies [ENEMY_NUMBER];

Edge edgeMap[MAP_WIDTH * MAP_HEIGTH]; 
Vedge visibleMap[MAP_WIDTH * MAP_HEIGTH];
Pedge poly_map[MAP_WIDTH * MAP_WIDTH + MAP_HEIGTH]; 
SDL_Vertex vertex[MAP_WIDTH * MAP_HEIGTH];

int poly_map_index, edge_map_index, visible_map_index, vertex_index = 0; 


int main(int argc, char* args[])
{
    bool KEYS[322];
	if(!InitWorld(KEYS))
	{
        fprintf(stderr, "Failed to initialize!\n");
        exit(1);
	}
    InitPlayer();

    SDL_Event e;
    int frameTime;            
    float secondsElapsed = 60.0f;
    long long int frameStart;

    WorldMap();
    RewriteMap(map, world[lvlN]);
    CreateMap();

    int start = 0; int end = 0; int i = 0;
    float sum = 0.0f;

    while (true)
    {
        start = SDL_GetPerformanceCounter();
        frameStart = SDL_GetTicks();
        
        AI();
        updatePhysic();
        Intersections1();
        DrawAll(secondsElapsed, KEYS);            
        
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP)
            {
                keyboard(e, KEYS);
            }
            else
            {
                frameTime = SDL_GetTicks() - frameStart;

                while (FRAME_DELAY > frameTime)
                {
                    AI();
                    updatePhysic();
                    Intersections1();
                    DrawAll(secondsElapsed, KEYS);
                    frameTime = SDL_GetTicks() - frameStart;
                }   
            }
        }   
        end = SDL_GetPerformanceCounter();
        sum += (end - start) / (float)SDL_GetPerformanceFrequency();
        if (i == FRAME_DELAY)
        {
            secondsElapsed = sum / i;
            sum = 0.0f; i = 0;
        } 
        i++;
    }

	CloseInit();
	return 0;
}

