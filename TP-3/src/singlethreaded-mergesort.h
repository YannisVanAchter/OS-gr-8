#ifndef __singletheaded__
#define __singletheaded__

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef unsigned int index;
typedef unsigned int length;

void merge(int array[], index start, index middle, index final);
void merge_sort(int array[], index start, index final);

#endif