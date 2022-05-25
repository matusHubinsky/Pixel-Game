#include "textures.h"
#include "main.h"
#include "light.h"

#include <stdio.h>

#define PI 3.14159265

_Bool up, down, left, right = false;

int number = 2;


int min (int a, int b, int c)
{
    if ((a <= b) && (a <= c)) return a;   
    if ((b <= a) && (b <= c)) return b;
    if ((c <= b) && (c <= a)) return c;
    return 0;
}


int max(int a, int b, int c)
{
    if (a >= b && a >= c) return a;
    if (b >= a && b >= c) return b;
    if (c >= b && c >= a) return c;
    return 0;
}


float cross_produce(int v1[2], int v2[2])
{
    float result = (v1[0] * v2[1]) - (v1[1] * v2[0]);
    return result;   
}

void draw_circle(int cx, int cy, int radius, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    for (double dy = 1; dy <= radius; dy += 1.1)
    {
       double dx = floor(sqrt((2.0 * radius * dy) - (dy * dy)));
       SDL_RenderDrawPoint(renderer, cx + dx, cy - dy + radius);
       SDL_RenderDrawPoint(renderer, cx - dx, cy - dy + radius);
       SDL_RenderDrawPoint(renderer, cx + dx, cy + dy - radius);
       SDL_RenderDrawPoint(renderer, cx - dx, cy + dy - radius);
   }
}


void fill_rectangle(int x, int y, int radius, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
	for (int i = 0; i < radius; i++)
	{
		for (int j = 0; j < radius; j++)	
        {
	       SDL_RenderDrawPoint(renderer, x+i, y+j);
		}
	}
}


void fill_circle(int cx, int cy, int radius, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	for (double dy = 1; dy <= radius; dy += 1.1)
	{
	   double dx = floor(sqrt((2.0 * radius * dy) - (dy * dy)));
	   SDL_SetRenderDrawColor(renderer, r, g, b, a);
	   SDL_RenderDrawLine(renderer, cx - dx, cy + dy - radius, cx + dx, cy + dy - radius);
	   SDL_RenderDrawLine(renderer, cx - dx, cy - dy + radius, cx + dx, cy - dy + radius);
   }
}


void fill_triangle(int x0, int y0, int x1, int y1, int x2, int y2, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    int max_x = max(x0, x1, x2);
    int max_y = max(y0, y1, y2);
    int min_x = min(x0, x1, x2);
    int min_y = min(y0, y1, y2);

    int vs1[2] = {x1 - x0, y1 - y0};
    int vs2[2] = {x2 - x0, y2 - y0};

    SDL_SetRenderDrawColor(renderer, r, g, b, a);

    for (int x = min_x; x < max_x; x++)
    {
        for (int y = min_y; y < max_y; y++)
        {
            int q[2] = {x - x0, y - y0};

            float s = (float) cross_produce(q, vs2) / cross_produce(vs1, vs2);
            float t = (float) cross_produce(vs1, q) / cross_produce(vs1, vs2);
     
            if ((s >= 0) && (t >= 0) && (s+t <= 1))
            {
                SDL_RenderDrawPoint(renderer, x, y);
            }
            // prepisat na drawline
        }
    }
}


void DrawMap()
{
    int length = sizeof(mapTex)/sizeof(mapTex[0]);
    for (int i = 0; i < length; i++)
    {
        SDL_RenderCopy(renderer, mapTex[i], &mapSrc[i], &mapRec[i]);
    }
}


void DrawLight()
{
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    int n = 4;
    int part = 360/n;
    double dY, dX;
    double val = PI / 180;
    for (int i = 0; i < n; i++)
    {
        dX = cos(part*i * val);
        dY = sin(part*i * val);
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0x50);
        SDL_RenderDrawLine(renderer, mouseX, mouseY, mouseX+(250*dX), mouseY+(250*dY));
    }
    // printf("\n");
}


void DrawCreatures()
{
	SDL_RenderCopy(renderer, player.tex, &player.src, &player.rec);
    AttackAnimation(player.a_up, player.a_down, player.a_left, player.a_right);

    for (int i = 0; i < enemy_number; i++)
    {
        SDL_RenderCopy(renderer, enemies[i].tex, &enemies[i].src, &enemies[i].rec); 
    }
}


void DrawEdges()
{
    for (int i = 0; i < edge_map_index; i++)
    {
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
        SDL_RenderDrawLine(renderer, edgeMap[i].start_x, edgeMap[i].start_y , edgeMap[i].end_x, edgeMap[i].end_y);
        fill_circle(edgeMap[i].start_x, edgeMap[i].start_y, 6, 0x00, 0x00, 0xFF, 0xFF);
        fill_circle(edgeMap[i].end_x, edgeMap[i].end_y, 6, 0x00, 0x00, 0xFF, 0xFF);
    }
}


void DrawBlocks()
{
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    for (int x = 0; x < 40; x++)
    {
        for (int y = 0; y < 30 ; y++)
        {
            if (poly_map[y*40 + x].exist) 
            {
                fill_rectangle(x * block, y * block, block, 0xFF, 0x00, 0x00, 0x55);
            }
        }
    }
}

void DrawDark()
{
    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = 1280;
    rect.h = 960;

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xA0);
    SDL_RenderFillRect(renderer, &rect);
}


void VisibleEdges()
{
    SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
    // printf("%i\n", visible_map_index);

    if (player.skin == 1)
    {
        for (int i = 0; i < visible_map_index; i++)
        {
            SDL_RenderDrawLine(renderer, player.rec.x + 16, player.rec.y + 16, visibleMap[i].x, visibleMap[i].y);
        }
    }
    else
    {
        for (int i = 0; i < visible_map_index; i++)
        {
            SDL_RenderDrawLine(renderer, player.rec.x + 64, player.rec.y + 64, visibleMap[i].x, visibleMap[i].y);
        }
    }

    for (int i = 0; i < visible_map_index; i++)
    {
        fill_circle(visibleMap[i].x, visibleMap[i].y, 5, 0x00, 0xFF, 0x00, 0xFF);
    }
}


void VisibleTriangles()
{
    // printf("%i\n", visible_map_index);
    if (player.skin == 1)
    {
        for (int i = 0; i < visible_map_index -1 ; i++)
        {
            fill_triangle(player.rec.x + 16, player.rec.y + 16, visibleMap[i + 0].x, visibleMap[i + 0].y, visibleMap[i + 1].x, visibleMap[i + 1].y, 0xFF, 0xFF, 0xFF, 0xA0);     
        }
        fill_triangle(player.rec.x + 16, player.rec.y + 16, visibleMap[visible_map_index - 1].x, visibleMap[visible_map_index - 1].y, visibleMap[0].x, visibleMap[0].y, 0xFF, 0xFF, 0xFF, 0xA0);

        SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
        SDL_RenderDrawLine(renderer, player.rec.x + 16, player.rec.y + 16, visibleMap[0].x, visibleMap[0].y);
        SDL_RenderDrawLine(renderer, player.rec.x + 16, player.rec.y + 16, visibleMap[visible_map_index - 1].x, visibleMap[visible_map_index - 1].y);
    }
    else
    {       
        for (int i = 0; i < visible_map_index -1 ; i++)
        {
            fill_triangle(player.rec.x + 64, player.rec.y + 64, visibleMap[i + 0].x, visibleMap[i + 0].y, visibleMap[i + 1].x, visibleMap[i + 1].y, 0xFF, 0xFF, 0xFF, 0xA0);     
        }
        fill_triangle(player.rec.x + 64, player.rec.y + 64, visibleMap[visible_map_index - 1].x, visibleMap[visible_map_index - 1].y, visibleMap[0].x, visibleMap[0].y, 0xFF, 0xFF, 0xFF, 0xA0);

        SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
        SDL_RenderDrawLine(renderer, player.rec.x + 64, player.rec.y + 64, visibleMap[0].x, visibleMap[0].y);
        SDL_RenderDrawLine(renderer, player.rec.x + 64, player.rec.y + 64, visibleMap[visible_map_index - 1].x, visibleMap[visible_map_index - 1].y);
    }
}


void ChangePlayerPicture(int velocity_x, int velocity_y)
{
    if (player.velocity_x < 0 && left == false)
    {
        player.tex = LoadTexture("tex/player/left_0.png");
        up = false;
        down = false;
        right = false;
        left = true;
    }

    if (player.velocity_x > 0 && right == false)
    {
        player.tex = LoadTexture("tex/player/right_0.png");
        up = false;
        down = false;
        right = true;
        left = false;
    }

    if (player.velocity_y < 0 && up == false)
    {
        player.tex = LoadTexture("tex/player/back_0.png");
        up = true;
        down = false;
        right = false;
        left = false;
    }

    if (player.velocity_y > 0 && down == false)
    {
        player.tex = LoadTexture("tex/player/front_0.png");
        up = false;
        down = true;
        right = false;
        left = false;
    }
}


void enemySight()
{
    for (int i = 0; i < enemy_number; i++)
    {
        if (enemies[i].health != 0)
        {
            if (enemies[i].vidim) SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
            else SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);

            SDL_RenderDrawLine(renderer, player.rec.x + 16, player.rec.y + 16, enemies[i].rec.x + 16, enemies[i].rec.y + 16);

            fill_circle(enemies[i].sight.x, enemies[i].sight.y, 6, 0xFF, 0x00, 0x00, 0xFF);
        }        
    }
}


void DeathScreen()
{
    if (player.health == 0)
    {
        SDL_Rect Rec;
        SDL_Rect Src;
        SDL_Texture* texture;

        Rec.x = 0;
        Rec.y = 0;
        Rec.w = 1280;
        Rec.h = 960;

        Src.x = 0;
        Src.y = 0;
        Src.w = 1280;
        Src.h = 960;

        texture = LoadTexture("tex/Death.jpg");
        
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, &Src, &Rec);
        SDL_RenderPresent(renderer);
    }
}


void AttackAnimation(bool up, bool down, bool left, bool right)
{
    SDL_Rect Rec;
    SDL_Rect Src;
    SDL_Texture* texture;

    Rec.w = 32;
    Rec.h = 32;

    Src.x = 0;
    Src.y = 0;
    Src.w = 32;
    Src.h = 32;

    texture = LoadTexture("tex/player/death.png");

    if (up)
    {
        Rec.x = player.rec.x;
        Rec.y = player.rec.y - 32;

        texture = LoadTexture("tex/player/a_up.png");
    }
    if (down)
    {
        Rec.x = player.rec.x;
        Rec.y = player.rec.y + 32;

        texture = LoadTexture("tex/player/a_down.png");
    }
    if (left)
    {
        Rec.x = player.rec.x - 32;
        Rec.y = player.rec.y;

        texture = LoadTexture("tex/player/a_left.png");
    }
    if (right)
    {
        Rec.x = player.rec.x + 32;
        Rec.y = player.rec.y;

        texture = LoadTexture("tex/player/a_right.png");
    }
    SDL_RenderCopy(renderer, texture, &Src, &Rec);
}


void DrawFPS()
{
        //this opens a font style and sets a size
    TTF_Font* Sans = TTF_OpenFont("/home/leviathan/Documents/VUT/git/PixelGame/code/tex/fonts/Arimo-Regular.ttf", 14);
    SDL_Color White = {255, 255, 255};

    int i  = 1.0f / secondsElapsed;
    char text[20]; 
    sprintf(text, "FPS: %d", i);

    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, text, White); 
    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

    SDL_Rect Message_rect; //create a rect
    Message_rect.x = 32*38;  //controls the rect's x coordinate 
    Message_rect.y = 32*0; // controls the rect's y coordinte
    Message_rect.w = 50; // controls the width of the rect
    Message_rect.h = 20; // controls the height of the rect

    SDL_RenderCopy(renderer, Message, NULL, &Message_rect);

    // Don't forget to free your surface and texture
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(Message);
}



SDL_Texture* LoadTexture(const char* path)
{
    SDL_Surface* loadedSurface = IMG_Load(path);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    SDL_FreeSurface(loadedSurface);

    return tex;
};


void DrawAll()
{
    if (player.health != 0)
    {
        // SDL set up
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

        // my texture rendering
        DrawMap();                          // map 
        DrawCreatures();                    // creatures

        if (KEYS[SDLK_1]) DrawBlocks();     // draw all blocks          (blue)
        if (KEYS[SDLK_2]) DrawEdges();      // draw all edges           (red)
        if (KEYS[SDLK_3]) VisibleEdges();   // draw all visible lines   (green)
         
        if (player.skin == 2) ChangePlayerPicture(velocity_x, velocity_y);

        if (KEYS[SDLK_4]) enemySight();     // draw enemy lines of sight
        if (KEYS[SDLK_5]) DrawFPS();

        // SDL render
        SDL_RenderPresent(renderer);
    }
}
