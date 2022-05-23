#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>

#include "vector.h"
#include "main.h"

void initArray(Array *a, size_t initialSize) 
{
    a -> array = malloc(initialSize * sizeof(Edge));
    a -> used = 0;
    a -> size = initialSize;
}


void insertArray(Array *a, Edge element)
{
    if (a -> used == a -> size) 
    {
        a -> size *= 2;
        a -> array = realloc(a -> array, a -> size * sizeof(Edge));
    }
    a -> array[a -> used++] = element;
}


void freeArray(Array *a) 
{
    free(a -> array);
    a -> array = NULL;
    a -> used = a -> size = 0;
}
