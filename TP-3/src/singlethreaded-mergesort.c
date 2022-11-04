#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef unsigned int index;
typedef unsigned int length;

void merge(int array[], index start, index middle, index final);
void merge_sort(int array[], index start, index final);

void merge_sort(int array[], index start, index final) {
  if(start < final) {
    index middle = floor((start + final) / 2);
    merge_sort(array, start, middle);
    merge_sort(array, middle+1, final);
    merge(array, start, middle, final);
  }
}

void merge(int array[], index start, index middle, index final) {
  length countL = middle - start + 1;
  int *arrayL = malloc(countL * sizeof(int));
  index currentL, currentR;
  for(currentL = 0; currentL < countL; currentL++)
    arrayL[currentL] = array[start + currentL];

  length countR = final - middle;
  int* arrayR = malloc(countR * sizeof(int));
  for(currentR = 0; currentR < countR; currentR++)
    arrayR[currentR] = array[middle + 1 + currentR];

  currentL = 0;
  currentR = 0;
  index current;
  for(current = start; current <= final && currentL < countL && currentR < countR; current++) {
    if(arrayL[currentL] <= arrayR[currentR]) {
      array[current] = arrayL[currentL];
      currentL++;
    } else { // arrayL[currentL] > arrayR[currentR]
      array[current] = arrayR[currentR];
      currentR++;
    }
  }

  // If <arrayL> was completely consumed, copy the remainder of <arrayR> over the remainder of <array>
  if(currentL >= countL)
    while(currentR < countR) {
      array[current] = arrayR[currentR];
      current++;
      currentR++;
    }

  // If <arrayR> was completely consumed, copy the remainder of <arrayL> over the remainder of <array>
  if(currentR >= countR)
    while(currentL < countL) {
      array[current] = arrayL[currentL];
      current++;
      currentL++;
    }

  free(arrayL);
  free(arrayR);
}

int tableau[] = { 2 , 27 , 3 , 49 , 98 , 12 , 4 , 1 };
int longueur = sizeof(tableau) / sizeof(int);

void show(int array[], length count) {
  for(index i = 0; i < count; i++)
    printf("%d ", array[i]);
  printf("\n");
}

int main(int argc, char* argv[]) {
  show(tableau, longueur);

  merge_sort(tableau, 0, longueur-1);

  show(tableau, longueur);

  return EXIT_SUCCESS;
}
