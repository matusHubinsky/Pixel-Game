
#include "map.h"
#include "textures.h"
#include "keyboard.h"


void Merge(t_vertexs * shared)
{
    float mistake = 0.01f;
    int k = 0;
    Vedge points[shared -> visible_map_index];

    // This shouldn't work
    for (int i = 0; i < shared -> visible_map_index - 1; i++)
    {
        if ((fabs(shared -> visibleMap[i].x - shared -> visibleMap[i + 1].x)) > mistake) 
        {
            points[k] = shared -> visibleMap[i];
            k++;
        }
        if ((fabs(shared -> visibleMap[i].y - shared -> visibleMap[i + 1].y)) > mistake)
        {
            points[k] = shared -> visibleMap[i];
            k++;
        }
    }
    
    // reload new information;
    for (int i = 0; i < k; i++)
    {
        shared -> visibleMap[i] = points[i];
    }
    shared -> visible_map_index = k;
}


void CellsMap(int sx, int sy, int w, int h, int block_width, int pitch, t_vertexs * shared)
{
    sx += 1;
    sy += 1;
    bool value;

    for (int i = 0; i < (30*30 + 40); i++)
    {
        shared -> poly_map[i].exist = false;
    }

    // initialiaztion
    for (int x = 0; x < w; x++)
    {
        for (int y = 0; y < h; y++)
        {
            if (map[y][x] == 3 || map[y][x] == 2) value = true;
            else value = false;
            shared -> poly_map[y*pitch + x].exist = value;
            for (int i = 0; i < 4; i++)
            {
                shared -> poly_map[y * pitch +  x].edge_exist[i] = false;
                shared -> poly_map[y * pitch +  x].edge_id[i] = 0;
            }
        }
    }

    for (int i = 0; i < shared -> edge_map_index; i++)
    {
        shared -> edgeMap[i].start_x = -1;
        shared -> edgeMap[i].start_y = -1;
        shared -> edgeMap[i].end_x = -1;
        shared -> edgeMap[i].end_y = -1;
    }

    shared -> edge_map_index = 0;
    // searching for edges

    for (int x = 0; x < w; x++)
    {
        for (int y = 0; y < h; y++)
        {
            int i = (y + sy) * pitch + (x + sx);        // This
            int n = (y + sy - 1) * pitch + (x + sx);    // Northern Neighbour
            int s = (y + sy + 1) * pitch + (x + sx);    // Southern Neighbour
            int w = (y + sy) * pitch + (x + sx - 1);    // Western Neighbour
            int e = (y + sy) * pitch + (x + sx + 1);    // Eastern Neighbour

            if (shared -> poly_map[i].exist)
            {
                if (!shared -> poly_map[w].exist)
                {
                    if (shared -> poly_map[n].edge_exist[WEST])
                    {
                        shared -> edgeMap[shared -> poly_map[n].edge_id[WEST]].end_y += BLOCK;
                        shared -> poly_map[i].edge_id[WEST] = shared -> poly_map[n].edge_id[WEST];
                        shared -> poly_map[i].edge_exist[WEST] = true;
                    }
                    else
                    {
                        shared -> edgeMap[shared -> edge_map_index].start_x = (sx + x) * BLOCK; 
                        shared -> edgeMap[shared -> edge_map_index].start_y = (sy + y) * BLOCK;

                        shared -> edgeMap[shared -> edge_map_index].end_x = shared -> edgeMap[shared -> edge_map_index].start_x; 
                        shared -> edgeMap[shared -> edge_map_index].end_y = shared -> edgeMap[shared -> edge_map_index].start_y + BLOCK;

                        int edge_id = shared -> edge_map_index;
                        shared -> edge_map_index++;

                        shared -> poly_map[i].edge_id[WEST] = edge_id;
                        shared -> poly_map[i].edge_exist[WEST] = true;
                    }
                }

                if (!shared -> poly_map[e].exist)
                {
                    if (shared -> poly_map[n].edge_exist[EAST])
                    {
                        shared -> edgeMap[shared -> poly_map[n].edge_id[EAST]].end_y += BLOCK;
                        shared -> poly_map[i].edge_id[EAST] = shared -> poly_map[n].edge_id[EAST];
                        shared -> poly_map[i].edge_exist[EAST] = true;
                    }
                    else
                    {
                        shared -> edgeMap[shared -> edge_map_index].start_x = (sx + x + 1) * BLOCK; 
                        shared -> edgeMap[shared -> edge_map_index].start_y = (sy + y) * BLOCK;
                        shared -> edgeMap[shared -> edge_map_index].end_x = shared -> edgeMap[shared -> edge_map_index].start_x; 
                        shared -> edgeMap[shared -> edge_map_index].end_y = shared -> edgeMap[shared -> edge_map_index].start_y + BLOCK;

                        int edge_id = shared -> edge_map_index;
                        shared -> edge_map_index++;

                        shared -> poly_map[i].edge_id[EAST] = edge_id;
                        shared -> poly_map[i].edge_exist[EAST] = true;
                    }
                }
                if (!shared -> poly_map[n].exist)
                {
                    if (shared -> poly_map[w].edge_exist[NORTH])
                    {
                        shared -> edgeMap[shared -> poly_map[w].edge_id[NORTH]].end_x += BLOCK;
                        shared -> poly_map[i].edge_id[NORTH] = shared -> poly_map[w].edge_id[NORTH];
                        shared -> poly_map[i].edge_exist[NORTH] = true;
                    }
                    else
                    {
                        shared -> edgeMap[shared -> edge_map_index].start_x = (sx + x) * BLOCK; 
                        shared -> edgeMap[shared -> edge_map_index].start_y = (sy + y) * BLOCK;
                        shared -> edgeMap[shared -> edge_map_index].end_x = shared -> edgeMap[shared -> edge_map_index].start_x + BLOCK; 
                        shared -> edgeMap[shared -> edge_map_index].end_y = shared -> edgeMap[shared -> edge_map_index].start_y;
                        
                        int edge_id = shared -> edge_map_index;
                        shared -> edge_map_index++;

                        shared -> poly_map[i].edge_id[NORTH] = edge_id;
                        shared -> poly_map[i].edge_exist[NORTH] = true;
                    }
                }
                if (!shared -> poly_map[s].exist)
                {

                    if (shared -> poly_map[w].edge_exist[SOUTH])
                    {
                        shared -> edgeMap[shared -> poly_map[w].edge_id[SOUTH]].end_x += BLOCK;
                        shared -> poly_map[i].edge_id[SOUTH] = shared -> poly_map[w].edge_id[SOUTH];
                        shared -> poly_map[i].edge_exist[SOUTH] = true;
                    }
                    else
                    {
                        shared -> edgeMap[shared -> edge_map_index].start_x = (sx + x) * BLOCK; 
                        shared -> edgeMap[shared -> edge_map_index].start_y = (sy + y + 1) * BLOCK;
                        shared -> edgeMap[shared -> edge_map_index].end_x = shared -> edgeMap[shared -> edge_map_index].start_x + BLOCK; 
                        shared -> edgeMap[shared -> edge_map_index].end_y = shared -> edgeMap[shared -> edge_map_index].start_y;

                        int edge_id = shared -> edge_map_index;
                        shared -> edge_map_index++;
                        
                        shared -> poly_map[i].edge_id[SOUTH] = edge_id;
                        shared -> poly_map[i].edge_exist[SOUTH] = true;
                    }
                }
            }
        }
    }
}


void Intersections1(t_vertexs * shared, bool KEYS[322])
{   
    player.rec.x += 16;
    player.rec.y += 16;

    shared -> visible_map_index = 0;

    for (int a = 0; a < shared -> edge_map_index; a++)
    {
        Edge e1 = shared -> edgeMap[a];
        for (int i = 0; i < 2; i++)
        {
            float rdx, rdy;
            rdx = (i == 0 ? e1.start_x : e1.end_x) - player.rec.x;
            rdy = (i == 0 ? e1.start_y : e1.end_y) - player.rec.y;

            float base_ang = atan2f(rdy, rdx);
            float ang = 0;
            float radius = 1;

            for (int j = 0; j < 3; j++)
            {
                if (j == 0) ang = base_ang - 0.00001f;
                if (j == 1) ang = base_ang;
                if (j == 2) ang = base_ang + 0.00001f;

                rdx = radius * cosf(ang);
                rdy = radius * sinf(ang);

                float min_t1 = INFINITY;
                float min_px = 0, min_py = 0, min_ang = 0;
                bool valid = false;

                for (int b = 0; b < shared -> edge_map_index; b++)
                {
                    Edge e2 = shared -> edgeMap[b];
                    float sdx = e2.end_x - e2.start_x;
                    float sdy = e2.end_y - e2.start_y;

                    if (fabs(sdx - rdx) > 0.0f && fabs(sdy - rdy) > 0.0f)
                    {
                        float t2 = (rdx * (e2.start_y - player.rec.y) + (rdy * (player.rec.x - e2.start_x))) / (sdx * rdy - sdy * rdx);
                        float t1 = (e2.start_x + sdx * t2 - player.rec.x) / rdx;

                        if (t1 > 0 && t2 >= 0 && t2 <= 1.0f)
                        {
                            if (t1 < min_t1)
                            {
                                min_t1 = t1;
                                min_px = player.rec.x + rdx * t1;
                                min_py = player.rec.y + rdy * t1;
                                min_ang = atan2f(min_py - player.rec.y, min_px - player.rec.x);
                                valid = true;
                            }
                        }
                    }
                }
                if (valid == true)
                {   
                    shared -> visibleMap[shared -> visible_map_index].x = min_px;
                    shared -> visibleMap[shared -> visible_map_index].y = min_py;
                    shared -> visibleMap[shared -> visible_map_index].a = min_ang;
                    shared -> visible_map_index++;
                } 
            }
        }
    }
    player.rec.x -= 16;
    player.rec.y -= 16;
    // this fix is awesome
    Vedge swap;

    for (int i = 0; i < shared -> visible_map_index; i++)
    {
        for (int j = 0; j < shared -> visible_map_index; j++)
        {
            if (shared -> visibleMap[j].a > shared -> visibleMap[j + 1].a)
            {
                swap = shared -> visibleMap[j];
                shared -> visibleMap[j] = shared -> visibleMap[j + 1];
                shared -> visibleMap[j + 1] = swap; 
            }
        }
    }
    if (KEYS[SDLK_0]) Merge(shared);
}
