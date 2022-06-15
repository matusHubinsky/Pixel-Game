
#include "battle.h"
#include "init.h"
#include "map.h"
#include "physic.h"
#include "light.h"
#include "textures.h"


void keyboard_input(SDL_Event event, bool KEYS[322], t_vertexs * shared, lvl * Cmap)
{
    if (event.type == SDL_KEYDOWN)
    {
        switch (event.key.keysym.sym)
        {        
            //-------------------------------------------------------------
            // MOVEMENT
            //-------------------------------------------------------------
            case SDLK_a:
                player.velocity_x = -1;
                player.velocity_y = 0;
                break;
    
            case SDLK_d:
                player.velocity_x = 1;
                player.velocity_y = 0;
                break;

            case SDLK_w:
                player.velocity_x = 0;
                player.velocity_y = -1;
                break;

             case SDLK_s:
                player.velocity_x = 0;
                player.velocity_y = 1;
                break;
            //-------------------------------------------------------------

            // MAP
            case SDLK_m:
                DoorMap(shared);            
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
                    InitReborn(shared, Cmap);
                }
                break;

            // CLOSE GAME
            case SDLK_ESCAPE:
                player.health = 0;
                CloseInit();
                exit(0);

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
}