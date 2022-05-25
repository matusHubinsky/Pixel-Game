
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


float secondsElapsed = 0.0f;

const int screen_width = 1280;
const int screen_heigth = 960;
const int map_width = 40;
const int map_height = 30;

// long long time, ltime, dtime = 0;
float velocity_x, velocity_y = 0.0f;
// int enemy_number = 2;

int step_walk = 32;     
int step_teleport = 64;
int n = 0;
int block = 32;
int poly_map_index, edge_map_index, visible_map_index = 0; 

int x_posun, y_posun; 
int x_kladne, x_zaporne;
int y_kladne, y_zaporne;
int i_zostatok;

float mouseX;
float mouseY;

_Bool quit = false;
_Bool KEYS[322]; 

lvl Cmap;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* texture = NULL;

SDL_Rect rec;
SDL_Rect src;

struct Creature player;
// struct Creature enemy;

struct Creature enemies [enemy_number];

// Edge poly_map[1200];
Edge edgeMap[1200]; 
Vedge visibleMap[1200];
Pedge poly_map[40*40 + 30];

int main(int argc, char* args[])
{   
	if(!InitWorld())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
        InitPlayer();

        SDL_Event e;

        int frameTime;            
        const int FPS = 60;
        const int frameDelay = 1000 / FPS;
        long long int frameStart;

        WorldMap();
        RewriteMap(map, world[lvlN]);
        CreateMap();

        int start = 0;
        int end = 0;

        while (quit != true)
        {
            start = SDL_GetPerformanceCounter();
            frameStart = SDL_GetTicks();
            
            AI();
            updatePhysic();
            Intersections1();
            DrawAll();            
            
            while (SDL_PollEvent(&e) != 0)
            {
         
                if (e.type == SDL_QUIT) quit = true;
                else if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP)
                {
                    keyboard(e);
                }
                else if (e.type == SDL_MOUSEMOTION)
                {
                    mouseX = e.motion.x;
                    mouseY = e.motion.y;
                }
               else
                {
                    frameTime = SDL_GetTicks() - frameStart;

                    while (frameDelay > frameTime)
                    {
                        AI();
                        updatePhysic();
                        Intersections1();
                        DrawAll();
                        frameTime = SDL_GetTicks() - frameStart;
                    }   
                }
            }   
            end = SDL_GetPerformanceCounter();
            secondsElapsed = (end - start) / (float)SDL_GetPerformanceFrequency();
            // printf("FPS %f\n", 1.0f / secondsElapsed);
            // print average FPS
        }
	}

	CloseInit();

	return 0;
}
