#include "init.h"
#include "keyboard.h"
#include "textures.h"
#include "map.h"
#include "main.h"
#include "light.h"
#include "world.h"
#include "vector.h"
#include "physic.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "textures.h"


bool InitWorld()
{
	bool status = true;

	if (SDL_Init(SDL_INIT_VIDEO) > 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        status = false;
	}
    window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_width, screen_heigth, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        status = false;
    }
    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
    {
        printf("Image could not be initialize\n");
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
        printf("Rendere could not be initialize. SDL_Error: %s\n", SDL_GetError());
        status = false;
    }
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        printf("SDL_Image could not be initialize. SDL_Error: %s\n", IMG_GetError());
        status = false;
    }

    SDL_Surface* icon = IMG_Load("tex/player/logo_1.png");
    SDL_SetWindowIcon(window, icon);
    SDL_SetWindowTitle(window, "Pixel Game");

    for (int i = 0; i < 322; i++) KEYS[i] = false; 

    return status;
}


void InitPlayer()
{
    player.skin =1;

    if (player.skin == 0)
    {
        printf("Wrong characater skin\n");
    }
    else if (player.skin == 1)  
    {
        // kocka 
        player.rec.x = 32*14;
        player.rec.y = 32*18;
        player.rec.w = 32;
        player.rec.h = 32;

        player.src.x = 0;
        player.src.y = 0;
        player.src.w = 32;
        player.src.h = 32;

        player.a_up = false;
        player.a_down = false;
        player.a_left = false;
        player.a_right = false;

        player.speed = 3;
        player.health = 10;
        player.tex = LoadTexture("tex/map/wood_2.png");
    }
    else if (player.skin == 2)
    {
        // robot
        player.rec.x = 32*18;
        player.rec.y = 32*12;
        player.rec.w = 64 * 2;
        player.rec.h = 64 * 2;

        player.src.x = 0;
        player.src.y = 0;
        player.src.w = 64;
        player.src.h = 64;

        player.speed = 3;
        player.health = 10;
        player.tex = LoadTexture("tex/player/front_0.png");
    }

    for (int i = 0; i < enemy_number; i++)
    {   
        enemies[i].skin = 1; 

        enemies[i].rec.x = 32 * 10;
        enemies[i].rec.y = 32 * (10 + i);
        enemies[i].rec.w = 32;
        enemies[i].rec.h = 32;

        enemies[i].src.x = 0;
        enemies[i].src.y = 0;
        enemies[i].src.w = 32;
        enemies[i].src.h = 32;

        enemies[i].speed = 2;
        enemies[i].health = 10;
        enemies[i].tex = LoadTexture("tex/map/wood_2.png");
    }

    for (int i = 0; i < 30; i++) 
    {
        for (int j = 0; j < 40; j++)
        {
            Cmap[i][j] = 0;
        }
    }
}


void InitReborn()
{
    InitPlayer();

    WorldMap();
    RewriteMap(map, world[0]);
    CreateMap();
}

void ToggleFullscreen(SDL_Window* Window) {
    Uint32 FullscreenFlag = SDL_WINDOW_FULLSCREEN;
    bool IsFullscreen = SDL_GetWindowFlags(Window) & FullscreenFlag;
    SDL_SetWindowFullscreen(Window, IsFullscreen ? 0 : FullscreenFlag);
    SDL_ShowCursor(IsFullscreen);
}

void CloseInit()
{       
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    texture = NULL;
    renderer = NULL;
    window = NULL;

    SDL_Quit();
    IMG_Quit();
 }