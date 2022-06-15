#ifndef INIT_H_
#define INIT_H_

#include "main.h"

bool InitWorld(bool KEYS[322]);
void InitPlayer(lvl * Cmap);
void InitReborn(t_vertexs * shared, lvl * Cmap);
void ToggleFullscreen(SDL_Window* Window);
void CloseInit();

#endif