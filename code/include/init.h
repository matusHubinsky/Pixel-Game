#ifndef INIT_H_
#define INIT_H_

#include "main.h"

bool InitWorld(bool KEYS[322]);
void InitPlayer();
void InitReborn(t_vertexs * shared);
void ToggleFullscreen(SDL_Window* Window);
void CloseInit();

#endif