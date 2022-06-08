#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>  

#include "main.h"

void keyboard_input(SDL_Event event, bool KEYS[322], t_vertexs * shared);

#endif