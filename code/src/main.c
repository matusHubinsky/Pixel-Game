
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


// global const
const int block = 32;
const int step_walk = 32;     
const int step_teleport = 64;
const int screen_width = 1280;
const int screen_heigth = 960;
const int map_width = 40;
const int map_height = 30;

int poly_map_index, edge_map_index, visible_map_index = 0; 

bool quit = false;
bool KEYS[322]; 

lvl Cmap;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* texture = NULL;

struct Creature player;
struct Creature enemies [enemy_number];

Edge edgeMap[1200]; 
Vedge visibleMap[1200];
Pedge poly_map[40*40 + 30];

SDL_Vertex vertex[1200];
int vertex_index = 0;

int main(int argc, char* args[])
{   
	if(!InitWorld())
	{
        fprintf(stderr, "Failed to initialize!\n");
        exit(1);
	}
    InitPlayer();

    SDL_Event e;

    int frameTime;            
    float secondsElapsed = 60.0f;
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;
    long long int frameStart;

    WorldMap();
    RewriteMap(map, world[lvlN]);
    CreateMap();

    int start = 0;
    int end = 0;

    int i = 0;
    float sum = 0.0f;

    while (quit != true)
    {
        start = SDL_GetPerformanceCounter();
        frameStart = SDL_GetTicks();
        
        AI();
        updatePhysic();
        Intersections1();
        DrawAll(secondsElapsed, KEYS);            
        
        while (SDL_PollEvent(&e) != 0)
        {
     
            if (e.type == SDL_QUIT) quit = true;
            else if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP)
            {
                keyboard(e, KEYS);
            }
           else
            {
                frameTime = SDL_GetTicks() - frameStart;

                while (frameDelay > frameTime)
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
        if (i == 8)
        {
            secondsElapsed = sum / i;
            sum = 0.0f; i = 0;
        } 
        i++;
    }

	CloseInit();
	return 0;
}

