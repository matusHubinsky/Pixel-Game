#ifndef MAIN_H_
#define MAIN_H_

#include <stdio.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_thread.h>
#include <SDL2/SDL_ttf.h>

#define NORTH 0
#define SOUTH 1
#define EAST 2
#define WEST 3

#define enemy_number 4

extern float secondsElapsed;

// constans
extern const int block;
extern const int step_walk;
extern const int step_teleport;
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

extern int lvlN;

typedef int lvl[30][40];			
extern lvl world[4];	
extern lvl map; 
extern lvl Cmap;
 
extern lvl lvl1;
extern lvl lvl2;
extern lvl lvl3;
extern lvl lvl4;

extern bool quit;
extern bool KEYS[322];

extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern SDL_Texture* texture;

extern SDL_Texture* LoadTexture(const char* path);

extern SDL_Rect mapRec[1200];
extern SDL_Rect mapSrc[1200];
extern SDL_Texture* mapTex[1200];

typedef struct Creature
{
    SDL_Texture* tex;

    SDL_Rect rec;
    SDL_Rect src;
	SDL_Rect sight;

	bool vidim;
    float speed;
    int skin;

    bool a_up;   bool a_down;
    bool a_left; bool a_right;

    int health;
	int velocity_y; int velocity_x;    
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

extern struct Creature player;
extern struct Creature enemies [enemy_number];

extern Edge edgeMap[1200]; 
extern Vedge visibleMap[1200];
extern Pedge poly_map[40*40 + 30]; 

extern SDL_Vertex vertex[1200];
extern int vertex_index;

#endif
