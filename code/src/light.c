#include "main.h"
#include "map.h"
#include "textures.h"
#include "light.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void CellsMap(int sx, int sy, int w, int h, int block_width, int pitch)
{
    sx += 1;
    sy += 1;
    bool value;

    for (int i = 0; i < (30*30 + 40); i++)
    {
        poly_map[i].exist = false;
    }

    // initialiaztion
    for (int x = 0; x < w; x++)
    {
        for (int y = 0; y < h; y++)
        {
            if (map[y][x] == 3 || map[y][x] == 2) value = true;
            else value = false;
            poly_map[y*pitch + x].exist = value;
            for (int i = 0; i < 4; i++)
            {
                poly_map[y * pitch +  x].edge_exist[i] = false;
                poly_map[y * pitch +  x].edge_id[i] = 0;
            }
        }
    }

    for (int i = 0; i < edge_map_index; i++)
    {
        edgeMap[i].start_x = -1;
        edgeMap[i].start_y = -1;
        edgeMap[i].end_x = -1;
        edgeMap[i].end_y = -1;
    }

    edge_map_index = 0;
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

            if (poly_map[i].exist)
            {
                if (!poly_map[w].exist)
                {
                    if (poly_map[n].edge_exist[WEST])
                    {
                        edgeMap[poly_map[n].edge_id[WEST]].end_y += block;
                        poly_map[i].edge_id[WEST] = poly_map[n].edge_id[WEST];
                        poly_map[i].edge_exist[WEST] = true;
                    }
                    else
                    {
                        edgeMap[edge_map_index].start_x = (sx + x) * block; 
                        edgeMap[edge_map_index].start_y = (sy + y) * block;

                        edgeMap[edge_map_index].end_x = edgeMap[edge_map_index].start_x; 
                        edgeMap[edge_map_index].end_y = edgeMap[edge_map_index].start_y + block;

                        int edge_id = edge_map_index;
                        edge_map_index++;

                        poly_map[i].edge_id[WEST] = edge_id;
                        poly_map[i].edge_exist[WEST] = true;
                    }
                }

                if (!poly_map[e].exist)
                {
                    if (poly_map[n].edge_exist[EAST])
                    {
                        edgeMap[poly_map[n].edge_id[EAST]].end_y += block;
                        poly_map[i].edge_id[EAST] = poly_map[n].edge_id[EAST];
                        poly_map[i].edge_exist[EAST] = true;
                    }
                    else
                    {
                        edgeMap[edge_map_index].start_x = (sx + x + 1) * block; 
                        edgeMap[edge_map_index].start_y = (sy + y) * block;
                        edgeMap[edge_map_index].end_x = edgeMap[edge_map_index].start_x; 
                        edgeMap[edge_map_index].end_y = edgeMap[edge_map_index].start_y + block;

                        int edge_id = edge_map_index;
                        edge_map_index++;

                        poly_map[i].edge_id[EAST] = edge_id;
                        poly_map[i].edge_exist[EAST] = true;
                    }
                }
                if (!poly_map[n].exist)
                {
                    if (poly_map[w].edge_exist[NORTH])
                    {
                        edgeMap[poly_map[w].edge_id[NORTH]].end_x += block;
                        poly_map[i].edge_id[NORTH] = poly_map[w].edge_id[NORTH];
                        poly_map[i].edge_exist[NORTH] = true;
                    }
                    else
                    {
                        edgeMap[edge_map_index].start_x = (sx + x) * block; 
                        edgeMap[edge_map_index].start_y = (sy + y) * block;
                        edgeMap[edge_map_index].end_x = edgeMap[edge_map_index].start_x + block; 
                        edgeMap[edge_map_index].end_y = edgeMap[edge_map_index].start_y;
                        
                        int edge_id = edge_map_index;
                        edge_map_index++;

                        poly_map[i].edge_id[NORTH] = edge_id;
                        poly_map[i].edge_exist[NORTH] = true;
                    }
                }
                if (!poly_map[s].exist)
                {

                    if (poly_map[w].edge_exist[SOUTH])
                    {
                        edgeMap[poly_map[w].edge_id[SOUTH]].end_x += block;
                        poly_map[i].edge_id[SOUTH] = poly_map[w].edge_id[SOUTH];
                        poly_map[i].edge_exist[SOUTH] = true;
                    }
                    else
                    {
                        edgeMap[edge_map_index].start_x = (sx + x) * block; 
                        edgeMap[edge_map_index].start_y = (sy + y + 1) * block;
                        edgeMap[edge_map_index].end_x = edgeMap[edge_map_index].start_x + block; 
                        edgeMap[edge_map_index].end_y = edgeMap[edge_map_index].start_y;

                        int edge_id = edge_map_index;
                        edge_map_index++;
                        
                        poly_map[i].edge_id[SOUTH] = edge_id;
                        poly_map[i].edge_exist[SOUTH] = true;
                    }
                }
            }
        }
    }
}


void Intersections1()
{   
    player.rec.x += 16;
    player.rec.y += 16;

    visible_map_index = 0;

    for (int a = 0; a < edge_map_index; a++)
    {
        Edge e1 = edgeMap[a];
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

                for (int b = 0; b < edge_map_index; b++)
                {
                    Edge e2 = edgeMap[b];
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
                    visibleMap[visible_map_index].x = min_px;
                    visibleMap[visible_map_index].y = min_py;
                    visibleMap[visible_map_index].a = min_ang;
                    visible_map_index++;
                } 
            }
        }
    }

    player.rec.x -= 16;
    player.rec.y -= 16;

    // this fix is awesome

    Vedge swap;

    for (int i = 0; i < visible_map_index; i++)
    {
        for (int j = 0; j < visible_map_index; j++)
        {
            if (visibleMap[j].a > visibleMap[j + 1].a)
            {
                swap = visibleMap[j];
                visibleMap[j] = visibleMap[j + 1];
                visibleMap[j + 1] = swap; 
            }
        }
    }

    Merge();
}


void Merge()
{
    Vedge points[visible_map_index];
    int k = 0;

    for (int i = 0; i < visible_map_index - 1; i++)
    {
        if ((fabs(visibleMap[i].x - visibleMap[i + 1].x) > 10.0f)) // && ((fabs(visibleMap[i].x - points[k].x) >= dis)))
        {
            points[k] = visibleMap[i];
            k++;
        }

        else if ((fabs(visibleMap[i].y - visibleMap[i + 1].y) > 10.0f)) // && ((fabs(visibleMap[i].y - points[k].y) >= dis)))
        {
            points[k] = visibleMap[i];
            k++;
        }
    }
    // printf("%i %i\n", visible_map_index, k);
    for (int i = 0; i < k; i++)
    {
        visibleMap[i] = points[i];
    }
    visible_map_index = k;
}
