
#include "init.h"
#include "keyboard.h"
#include "textures.h"
#include "map.h"
#include "light.h"
#include "physic.h"


SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* texture = NULL;

// TODO:
// zdielanie character mao

struct Creature player;
struct Creature enemies [ENEMY_NUMBER];

int main(int argc, char* args[])
{
    t_vertexs shared;

    bool KEYS[322];
	if(!InitWorld(KEYS))
	{
        fprintf(stderr, "Failed to initialize!\n");
        exit(1);
	}
    else printf("InitWorld passed.\n");
    
    // charecter map
    lvl Cmap;
    SDL_Event e;
    long long int frameStart;    
    int start = 0, end = 0, i = 0, frameTime = 0;;
    float secondsElapsed = 60.0f, sum = 0.0f;

    InitPlayer(&Cmap);
    WorldMap();
    RewriteMap(map, world[lvlN], &shared);
    CreateMap();

    while (true)
    {
        start = SDL_GetPerformanceCounter();
        frameStart = SDL_GetTicks();
        
        AI(&shared);
        updatePhysic(&shared);
        Intersections1(&shared, KEYS);
        DrawAll(secondsElapsed, KEYS, &shared);            
        
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP)
            {
                keyboard_input(e, KEYS, &shared, &Cmap);
            }
            else
            {
                frameTime = SDL_GetTicks() - frameStart;

                while (FRAME_DELAY > frameTime)
                {
                    AI(&shared);
                    updatePhysic(&shared);
                    Intersections1(&shared, KEYS);
                    DrawAll(secondsElapsed, KEYS, &shared);
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