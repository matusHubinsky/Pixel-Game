
#include "init.h"
#include "keyboard.h"
#include "textures.h"
#include "map.h"
#include "light.h"
#include "physic.h"


// Thigs that MUST be global
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* texture = NULL;


// This don't have to be global
struct Creature player;
struct Creature enemies [ENEMY_NUMBER];


// update all action
void update(float secondsElapsed, bool KEYS[322], t_vertexs * shared)
{
    // calculate next movement of AI
    AI(shared);
    // calculate next move of player ???
    updatePhysic(shared);
    // calculate field of views
    Intersections1(shared, KEYS);
    // draw everything
    DrawAll(secondsElapsed, KEYS, shared);      
}


// calculate FPS every 8th frame
// TODO: pointers
void calculate_fps(int * start, int * end, int * frame_counter, float * sum, float * secondsElapsed)
{
    end = SDL_GetPerformanceCounter();
    sum += (end - start) / (float)SDL_GetPerformanceFrequency();
    if (frame_counter == FRAME_DELAY)
    {
        secondsElapsed = sum / frame_counter;
        sum = 0.0f; 
        frame_counter = 0;
    } 
    frame_counter++;
}


int main(int argc, char* args[])
{
    t_vertexs shared;

    bool KEYS[322];
	if(!InitWorld(KEYS))
	{
        fprintf(stderr, "Failed to initialize World!\n");
        exit(1);
	}
    
    // charecter map
    lvl Cmap;
    SDL_Event e;
    long long int frameStart;    
    int start = 0, end = 0, frame_counter = 0, frameTime = 0;;
    float secondsElapsed = 60.0f, sum = 0.0f;

    // initialize player
    InitPlayer(&Cmap);
    // this can be moved into init world ??? 
    WorldMap();
    RewriteMap(map, world[lvlN], &shared);
    CreateMap();

    // main game cycle
    while (true)
    {
        // time counter 
        start = SDL_GetPerformanceCounter();
        frameStart = SDL_GetTicks();
        
        // do all actions
        update(secondsElapsed, KEYS, &shared);
    
        // handle all events
        while (SDL_PollEvent(&e) != 0)
        {
            // TODO: mouse input
            if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP)
            {
                // handle keyboard input
                keyboard_input(e, KEYS, &shared, &Cmap);
            }
            else
            {
                // calculate delay
                frameTime = SDL_GetTicks() - frameStart;
                // add delay
                while (FRAME_DELAY > frameTime)
                {
                    // do all actions
                    update(secondsElapsed, KEYS, &shared);
                    frameTime = SDL_GetTicks() - frameStart;
                }   
            }
        }   
        // count FPS
        end = SDL_GetPerformanceCounter();
        sum += (end - start) / (float)SDL_GetPerformanceFrequency();
        if (frame_counter == FRAME_DELAY)
        {
            secondsElapsed = sum / frame_counter;
            sum = 0.0f; 
            frame_counter = 0;
        } 
        frame_counter++;
    }
    // just close everything
	CloseInit();
	return 0;
}