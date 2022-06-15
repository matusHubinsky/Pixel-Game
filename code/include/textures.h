#ifndef TEXTURES_H_
#define TEXTURES_H_

#include "main.h"

int min(int a, int b, int c);
int max(int a, int b, int c);
float cross_produce(int v1[2], int v2[2]);
void draw_line(int sx, int sy, int ex, int ey, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
void draw_circle(int cx, int cy, int radius, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
void fill_rectangle(int x, int y, int radius, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
void fill_circle(int cx, int cy, int radius, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
void fill_triangle(int x1, int y1, int x2, int y2, int x3, int y3, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

void DrawMap();
void DrawCreatures();

void DrawEdges(t_vertexs * shared);
void DrawBlocks(t_vertexs * shared);

void DrawDark();
void VisibleEdges(t_vertexs * shared);
void VisibleTriangles(t_vertexs * shared);

void ChangePlayerPicture(Creature player);
void enemySight();
void DeathScreen();
void AttackAnimation(bool up, bool down, bool left, bool right);
void PrepareTriangles(t_vertexs * shared);
void DrawFPS(float secondsElapsed);

SDL_Texture* LoadTexture(const char* path);

void DrawAll(float secondsElapsed, bool KEYS[322], t_vertexs * shared);
void getRenderInfo();

#endif