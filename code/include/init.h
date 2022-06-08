#ifndef INIT_H_
#define INIT_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>

#include "main.h"

bool InitWorld(bool KEYS[322]);
void InitPlayer();
void InitReborn(t_vertexs * shared);
void ToggleFullscreen(SDL_Window* Window);
void CloseInit();

#endif