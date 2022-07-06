
#include "light.h"
#include "textures.h"

#define PI 3.14159265

bool up, down, left, right = false;

int number = 2;
SDL_Texture* triangle_texture;


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


// OLD FUNC
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

// calculate all the poinst and draw circle
// not sure wtich method I am using
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


// OLD FUNC
// fill triangle, not sure which method I am using
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


// just draw whole map
void DrawMap()
{
    int length = sizeof(mapTex)/sizeof(mapTex[0]);
    for (int i = 0; i < length; i++)
    {
        SDL_RenderCopy(renderer, mapTex[i], &mapSrc[i], &mapRec[i]);
    }
}


// draw all player, his attack animation and all the enemies
void DrawCreatures()
{
    // draw player
	SDL_RenderCopy(renderer, player.tex, &player.src, &player.rec);
    // his attack animation
    AttackAnimation(player.a_up, player.a_down, player.a_left, player.a_right);

    // draw all the enemies
    for (int i = 0; i < ENEMY_NUMBER; i++)
    {
        if (enemies[i].health != 0 && enemies[i].vidim) 
        {
            SDL_RenderCopy(renderer, enemies[i].tex, &enemies[i].src, &enemies[i].rec);     
        }
    }
}


// draw red edges of the objects
void DrawEdges(t_vertexs * shared)
{
    for (int i = 0; i < shared -> edge_map_index; i++)
    {
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
        SDL_RenderDrawLine(renderer, shared -> edgeMap[i].start_x, shared -> edgeMap[i].start_y , shared -> edgeMap[i].end_x, shared -> edgeMap[i].end_y);
        fill_circle(shared -> edgeMap[i].start_x, shared -> edgeMap[i].start_y, 6, 0x00, 0x00, 0xFF, 0xFF);
        fill_circle(shared -> edgeMap[i].end_x, shared -> edgeMap[i].end_y, 6, 0x00, 0x00, 0xFF, 0xFF);
    }
}


// draw blue blocks of the objects
void DrawBlocks(t_vertexs * shared)
{
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    for (int x = 0; x < 40; x++)
    {
        for (int y = 0; y < 30 ; y++)
        {
            if (shared -> poly_map[y*40 + x].exist) 
            {
                fill_rectangle(x * BLOCK, y * BLOCK, BLOCK, 0xFF, 0x00, 0x00, 0x55);
                // SDL_RenderFillRect(renderer, &box);
            }
        }
    }
}


// draw "dark" texture at whole map
void DrawDark()
{
    SDL_Rect rect;
    rect.x = 32;
    rect.y = 32;
    rect.w = 1280 - 64;
    rect.h = 960 - 64;

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x70);
    SDL_RenderFillRect(renderer, &rect);
}


// Draw all green visible edges
void VisibleEdges(t_vertexs * shared)
{
    SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
    // fprintf(file_ptr, "%i\n", shared -> visible_map_index);

    if (player.skin == 1)
    {
        for (int i = 0; i < shared -> visible_map_index; i++)
        {
            SDL_RenderDrawLine(renderer, player.rec.x + 16, player.rec.y + 16, shared -> visibleMap[i].x, shared -> visibleMap[i].y);
        }
    }
    else
    {
        for (int i = 0; i < shared -> visible_map_index; i++)
        {
            SDL_RenderDrawLine(renderer, player.rec.x + 64, player.rec.y + 64, shared -> visibleMap[i].x, shared -> visibleMap[i].y);
        }
    }

    for (int i = 0; i < shared -> visible_map_index; i++)
    {
        fill_circle(shared -> visibleMap[i].x, shared -> visibleMap[i].y, 5, 0x00, 0xFF, 0x00, 0xFF);
    }
}


// OLD FUNC 
// draw till visible triangles
void VisibleTriangles(t_vertexs * shared)
{
    // fprintf(file_ptr, "%i\n", shared -> visible_map_index);
    if (player.skin == 1)
    {
        for (int i = 0; i < shared -> visible_map_index -1 ; i++)
        {
            fill_triangle(player.rec.x + 16, player.rec.y + 16, shared -> visibleMap[i + 0].x, shared -> visibleMap[i + 0].y, shared -> visibleMap[i + 1].x, shared -> visibleMap[i + 1].y, 0xFF, 0xFF, 0xFF, 0xA0);     
        }
        fill_triangle(player.rec.x + 16, player.rec.y + 16, shared -> visibleMap[shared -> visible_map_index - 1].x, shared -> visibleMap[shared -> visible_map_index - 1].y, shared -> visibleMap[0].x, shared -> visibleMap[0].y, 0xFF, 0xFF, 0xFF, 0xA0);

        SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
        SDL_RenderDrawLine(renderer, player.rec.x + 16, player.rec.y + 16, shared -> visibleMap[0].x, shared -> visibleMap[0].y);
        SDL_RenderDrawLine(renderer, player.rec.x + 16, player.rec.y + 16, shared -> visibleMap[shared -> visible_map_index - 1].x, shared -> visibleMap[shared -> visible_map_index - 1].y);
    }
    else
    {       
        for (int i = 0; i < shared -> visible_map_index -1 ; i++)
        {
            fill_triangle(player.rec.x + 64, player.rec.y + 64, shared -> visibleMap[i + 0].x, shared -> visibleMap[i + 0].y, shared -> visibleMap[i + 1].x, shared -> visibleMap[i + 1].y, 0xFF, 0xFF, 0xFF, 0xA0);     
        }
        fill_triangle(player.rec.x + 64, player.rec.y + 64, shared -> visibleMap[shared -> visible_map_index - 1].x, shared -> visibleMap[shared -> visible_map_index - 1].y, shared -> visibleMap[0].x, shared -> visibleMap[0].y, 0xFF, 0xFF, 0xFF, 0xA0);

        SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
        SDL_RenderDrawLine(renderer, player.rec.x + 64, player.rec.y + 64, shared -> visibleMap[0].x, shared -> visibleMap[0].y);
        SDL_RenderDrawLine(renderer, player.rec.x + 64, player.rec.y + 64, shared -> visibleMap[shared -> visible_map_index - 1].x, shared -> visibleMap[shared -> visible_map_index - 1].y);
    }
}


// change player texture is player is moving in new direction
void ChangePlayerPicture(Creature player)
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


// draw lines of sight from enemies to player
void enemySight()
{
    for (int i = 0; i < ENEMY_NUMBER; i++)
    {
        if (enemies[i].health != 0)
        {
            if (enemies[i].vidim) 
            {
                fill_circle(enemies[i].sight.x, enemies[i].sight.y, 6, 0xFF, 0x00, 0x00, 0x88);
                fill_circle(enemies[i].sight.x, enemies[i].sight.y, 6, 0xFF, 0x00, 0x00, 0xFF);
                SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
            }    
            else 
            {
                fill_circle(enemies[i].sight.x, enemies[i].sight.y, 6, 0xFF, 0x00, 0xFF, 0x88);
                fill_circle(enemies[i].sight.x, enemies[i].sight.y, 4, 0xFF, 0x00, 0xFF, 0xFF);
                SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0xFF, 0xFF);
            }
            SDL_RenderDrawLine(renderer, player.rec.x + 16, player.rec.y + 16, enemies[i].rec.x + 16, enemies[i].rec.y + 16);
        }        
    }
}


// draw death screen, trigers only when player dies
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


// drawing half circle in font of the player
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


// drawing FPS in top right corner
void DrawFPS(float secondsElapsed)
{
    //this opens a font style and sets a size
    TTF_Font* Sans = TTF_OpenFont("/home/leviathan/Documents/VUT/git/PixelGame/code/tex/fonts/Arimo-Regular.ttf", 14);
    SDL_Color White = {255, 255, 255};

    int i  = 1.0f / secondsElapsed;
    char text[20]; 
    sprintf(text, "FPS: %3d", i);

    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, text, White); 
    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

    SDL_Rect Message_rect;      // create a rect
    Message_rect.x = 32*37;     // controls the rect's x coordinate 
    Message_rect.y = 32*0;      // controls the rect's y coordinte
    Message_rect.w = 75;        // controls the width of the rect
    Message_rect.h = 25;        // controls the height of the rect

    SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
    // Don't forget to free your surface and texture
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(Message);
}


// basic SDL texture function
SDL_Texture* LoadTexture(const char* path)
{
    SDL_Surface* loadedSurface = IMG_Load(path);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    SDL_FreeSurface(loadedSurface);

    return tex;
};


// I was trying to draw all triangles as cuts of texture....not sure if I can do it in SDL 
void TriagnleTexture(SDL_Texture* triangle_texture)
{
    /*
    SDL_Rect Rec;
    SDL_Rect Src;
    Rec.w = 512;
    Rec.h = 512;
    Src.w = 512;
    Src.h = 512;
    */
    triangle_texture = LoadTexture("tex/player/light.png");
}


// set all riangles 
void PrepareTriangles(t_vertexs * shared)
{
    int j = 0;

    for (int i = 0; i < shared -> visible_map_index; i++)
    {
        shared -> vertex[j].position.x = (int) player.rec.x + 16;
        shared -> vertex[j].position.y = (int) player.rec.y + 16;
        shared -> vertex[j].color.r = 225;
        shared -> vertex[j].color.g = 160;
        shared -> vertex[j].color.b = 255;
        shared -> vertex[j].color.a = 25;
        j++;

        shared -> vertex[j].position.x = (int) shared -> visibleMap[i + 0].x;
        shared -> vertex[j].position.y = (int) shared -> visibleMap[i + 0].y;
        shared -> vertex[j].color.r = 225;
        shared -> vertex[j].color.g = 160;
        shared -> vertex[j].color.b = 255;
        shared -> vertex[j].color.a = 25;
        j++;

        shared -> vertex[j].position.x = (int) shared -> visibleMap[(i + 1) % shared -> visible_map_index].x;
        shared -> vertex[j].position.y = (int) shared -> visibleMap[(i + 1) % shared -> visible_map_index].y;   
        shared -> vertex[j].color.r = 225;
        shared -> vertex[j].color.g = 160;
        shared -> vertex[j].color.b = 255;
        shared -> vertex[j].color.a = 25;
        j++;         
    }
    shared -> vertex_index = j;
}


void DrawAll(float secondsElapsed, bool KEYS[322], t_vertexs * shared)
{
    if (player.health != 0)
    {
        // SDL set up
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

        // my texture rendering
        DrawMap();                          // map 
        
        if (KEYS[SDLK_1]) DrawBlocks(shared);     // draw all blocks          (blue)
        if (KEYS[SDLK_2]) DrawEdges(shared);      // draw all edges           (red)
        if (KEYS[SDLK_3]) VisibleEdges(shared);   // draw all visible lines   (green)
         
        if (player.skin == 2) ChangePlayerPicture(player);

        // SIGHT
        if (KEYS[SDLK_4]) enemySight();     // draw enemy lines of sight
        if (KEYS[SDLK_5]) DrawFPS(secondsElapsed);
        
        // render info
        if (KEYS[SDLK_7]) 
        {
            getRenderInfo();
            KEYS[SDLK_7] = false;
        }

        // Draw dark texture
        DrawDark();
        DrawCreatures();                    

        if (KEYS[SDLK_6])
        {
            TriagnleTexture(triangle_texture);
            PrepareTriangles(shared);
            SDL_RenderGeometry(renderer, triangle_texture, shared -> vertex, shared -> vertex_index, NULL, 0);
        }

        // SDL render
        SDL_RenderPresent(renderer);
    }
}

// Save all information about curent renderer into file .../txt/info.txt
void getRenderInfo()
{
    FILE * file_ptr;
    file_ptr = fopen("/home/leviathan/Documents/VUT/git/PixelGame/txt/info.txt", "w");
    
    if (file_ptr == NULL)
    {
        fprintf(stderr, "File can't be created\n");
        exit(1);
    }

    SDL_RendererInfo info = {0};
    if (SDL_GetRenderDriverInfo(0, &info) == 0)
    {
        fprintf(file_ptr, "-------------------------------------------------------\n");
        fprintf(file_ptr, "Render Driver info: \n");
        fprintf(file_ptr, "name: %s\n", info.name);
        fprintf(file_ptr, "flags: %d\n", info.flags);
        fprintf(file_ptr, "num_texture_formats: %d\n", info.num_texture_formats);

        for (int i = 0; i < info.num_texture_formats; i++)
        {
            fprintf(file_ptr, "texture_formats[%i]: %d\n", i, info.texture_formats[i]);    
        }

        fprintf(file_ptr, "max_texture_width: %d\n", info.max_texture_width);
        fprintf(file_ptr, "max_texture_height: %d\n", info.max_texture_height);            
    }
    else
    {
        fprintf(file_ptr, "SDL_Init failed: %s\n", SDL_GetError());
    }
    fprintf(file_ptr, "Render Driver number: %d\n", SDL_GetNumRenderDrivers());
    fprintf(file_ptr, "-------------------------------------------------------\n");

    // message to user
    fprintf(stdout, "Driver info sent!\n");
}