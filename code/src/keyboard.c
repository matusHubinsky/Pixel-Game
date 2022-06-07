#include "keyboard.h"

#include "battle.h"
#include "main.h"
#include "init.h"
#include "map.h"
#include "physic.h"
#include "light.h"
#include "textures.h"

#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


struct timeval start, stop;
double secs = 0;

void keyboard(SDL_Event event, bool KEYS[322])
{
    //    gettimeofday(&stop, NULL);
    //    secs = (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);

    if (event.type == SDL_KEYDOWN)
    {
        switch (event.key.keysym.sym)
        {        
            //-------------------------------------------------------------
            // MOVEMENT
            //-------------------------------------------------------------
            case SDLK_a:
                player.velocity_x = -1;
                break;
    
            case SDLK_d:
                player.velocity_x = 1;
                break;

            case SDLK_w:
                player.velocity_y = -1;
                break;

             case SDLK_s:
                player.velocity_y = 1;
                break;
            //-------------------------------------------------------------

            // MAP
            case SDLK_m:
                DoorMap();            
                break;

            // FULLSCREEN
            case SDLK_f:
                ToggleFullscreen(window); 
                break;

            //-------------------------------------------------------------
            // ATTACK
            //-------------------------------------------------------------
            case SDLK_UP:
                PlayerAttack(&player, true, false, false, false);
                player.a_up = true;
                break;

            case SDLK_DOWN:
                PlayerAttack(&player, false, true, false, false);
                player.a_down = true;
                break;

            case SDLK_LEFT:
                PlayerAttack(&player, false, false, true, false);
                player.a_left = true;
                break;

            case SDLK_RIGHT:
                PlayerAttack(&player, false, false, false, true);
                player.a_right = true;
                break;
            //-------------------------------------------------------------

            // REBORN
            case SDLK_SPACE:
                if (player.health == 0)
                {
                    player.health = 10;
                    InitReborn();
                }
                break;

            // CLOSE GAME
            case SDLK_ESCAPE:
                player.health = 0;
                quit = true;
                break;

            default:
                if (KEYS[event.key.keysym.sym]) KEYS[event.key.keysym.sym] = false;
                else KEYS[event.key.keysym.sym] = true; 
                break;
        }
    }


    if (event.type == SDL_KEYUP)
    {
        switch (event.key.keysym.sym)
        { 
            case SDLK_a:
                player.velocity_x = 0;
                break;
            
            case SDLK_d:
                player.velocity_x = 0;
                break;

            case SDLK_w:
                player.velocity_y = 0;
                break;

             case SDLK_s:
                player.velocity_y = 0;
                break;

            case SDLK_UP:
                player.a_up = false;
                break;

            case SDLK_DOWN:
                player.a_down = false;
                break;

            case SDLK_RIGHT:
                player.a_right = false;
                break;

            case SDLK_LEFT:
                player.a_left = false;
                break;

            default:
                break;
        }
    }
    //  gettimeofday(&start, NULL);
}