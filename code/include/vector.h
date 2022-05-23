#ifndef VECTOR_H_
#define VECTOR_H_

#include <stdio.h>

#include "main.h"

typedef struct
{
    Edge *array;
    size_t used;
    size_t size;
}  Array;


void initArray(Array *a, size_t initialSize);
void insertArray(Array *a, Edge element);
void freeArray(Array *a);


#endif