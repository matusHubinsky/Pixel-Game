#ifndef MAIN_H_
#define MAIN_H_

#include <stdio.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define NORTH 0
#define SOUTH 1
#define EAST 2
#define WEST 3

#define enemy_number 4

// constans
extern const int screen_width;
extern const int screen_heigth;
extern const int map_width;
extern const int map_heigth;

// player speed
extern float velocity_x;
extern float velocity_y;

// time 

/*
extern long long time;
extern long long ltime;
extern long long dtime;
*/

// indexs
extern int poly_map_index;
extern int edge_map_index;
extern int visible_map_index; 

// extern int enemy_number;

extern int step_walk;
extern int step_teleport;
extern int n;
extern int lvlN;
extern int block;

extern int x_posun;
extern int y_posun; 
extern int x_zaporne;
extern int x_kladne;
extern int y_zaporne;
extern int y_kladne;
extern int i_zostatok;

extern float mouseX;
extern float mouseY;

typedef int lvl[30][40];			
extern lvl world[4];	
extern lvl map; 
extern lvl Cmap;
 
extern lvl lvl1;
extern lvl lvl2;
extern lvl lvl3;
extern lvl lvl4;

extern _Bool quit;

extern SDL_Window* window;

extern SDL_Renderer* renderer;

extern SDL_Texture* texture;
extern SDL_Texture* LoadTexture(const char* path);

extern SDL_Rect rec;
extern SDL_Rect src;

extern SDL_Rect mapRec[1200];
extern SDL_Rect mapSrc[1200];
extern SDL_Texture* mapTex[1200];

extern _Bool KEYS[322]; 

typedef struct Creature
{
    SDL_Texture* tex;

    SDL_Rect rec;
    SDL_Rect src;
	SDL_Rect sight;

	_Bool vidim;
    float speed;
    int skin;

    _Bool a_up;
    _Bool a_down;
    _Bool a_left;
    _Bool a_right;

    int health;
	
	int velocity_y;
	int velocity_x;    

} Creature;

typedef struct room
{
	SDL_Rect roomRec[1200];
	SDL_Rect roomSrc[1200];
	SDL_Texture* roomTex[1200];
} Room;

typedef struct vedge
{
	float x, y, a;
} Vedge;

typedef struct edge 
{
	int start_x, start_y;
    int end_x, end_y;
} Edge;

typedef struct poly_edge
{
	int edge_id[4];			// N, S, W, E
	bool edge_exist[4];		// zapisem si kolko ma hran	
	bool exist;	
} Pedge;

// extern Edge poly_map[1200];  robim ju v light.c
extern Edge edgeMap[1200]; 
extern Vedge visibleMap[1200];
extern Pedge poly_map[40*40 + 30]; 

extern Creature enemies [enemy_number];

extern struct Creature player;
// extern struct Creature enemy;

#endif
