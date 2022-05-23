#ifndef TEXTURES_H_
#define TEXTURES_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

#include "main.h"


// void setBlendMode( SDL_BlendMode blending );
// void setAlpha( Uint8 a );
int min(int a, int b, int c);
int max(int a, int b, int c);
float cross_produce(int v1[2], int v2[2]);
// int * Interpolate(int i0, int d0, int i1, int d1, int* values);
void draw_line(int sx, int sy, int ex, int ey, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
void draw_circle(int cx, int cy, int radius, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
void fill_rectangle(int x, int y, int radius, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
void fill_circle(int cx, int cy, int radius, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
void fill_triangle(int x1, int y1, int x2, int y2, int x3, int y3, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

void DrawMap();
void DrawLight();
void DrawCreatures();

void DrawEdges();
void DrawBlocks();

void DrawDark();

void VisibleEdges();
void VisibleTriangles();

void ChangePlayerPicture(int velocity_x, int velocity_y);

void enemySight();

void DeathScreen();

void AttackAnimation(bool up, bool down, bool left, bool right);

void DrawAll();

SDL_Texture* LoadTexture(const char* path);

#endif