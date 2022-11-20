#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <stdint.h>

typedef unsigned int index;
typedef unsigned int length;

void merge(int array[], index start, index middle, index final);
void merge_sort(int array[], index start, index final);
void print_array(int array[], int start, int final);

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

// Group function and code 
struct thread_args {
    index start;
    index final;
    int* array;
};

void* thread_merge_sort(void* arguments) {
  // get standart parameters from void pointer
  struct thread_args* args = ((struct thread_args*) arguments);
  index start = args->start;
  index final = args->final;
  int* array = args->array;

  // standart merge sort
  if(start < final) {
    index middle = floor((start + final) / 2);
    merge_sort(array, start, middle);
    merge_sort(array, middle+1, final);
    merge(array, start, middle, final);
  }

  pthread_exit(EXIT_SUCCESS);
}

void start_merge_sort(int array[], index start, index final, const int N_THREAD) 
{
    const index end_seg = floor((start + final) / N_THREAD);

    // set variable of thread management and function parameters
    struct thread_args* args = malloc(sizeof(struct thread_args));
    args->array = array;
    pthread_t* thread_array = malloc(sizeof(pthread_t) * N_THREAD); // pid of threads
    index begin = start; 
    index end = end_seg;
    // loop to create threads and updates parameters
    for (index n_thread = 0; n_thread < N_THREAD; n_thread++) 
    {
        args->start = begin;
        while (end > final) end--; // decrement the end of segmentation if we go too far in memory
        args->final = end;
        pthread_create(thread_array + n_thread, NULL, thread_merge_sort, args);
        end += end_seg; 
        begin += end_seg;
    }

    // Wait end of threads process
    void* thread_return;
    for (int i = 0; i < N_THREAD; i++) pthread_join(*(thread_array + i), &thread_return);
    
    // merge from all thread
    index separator = end_seg;
    end = 2 *end_seg;
    for (index n_thread = 0; n_thread < N_THREAD; n_thread++) 
    {
        while (end > final) end--; // decrement the end of segmentation if we go too far in memory
        merge(array, 0, separator, end); 
        separator += end_seg; 
        end += end_seg; 
    } 
}

void print_array(int array[], int start, int final)
{
    for (int i = 0; i < final - start; i++)
    {
        printf("%d, ", *(array + start + i));
    }
    printf("\n");
}

int main(int argc, char **argv)
{
    int array[12] = {12, 0, 2, 9, 34, 100, 300, 291, 377, 2110, 81, 1};

    printf("Current array: ");
    print_array(array, 0, sizeof(array) / 4);

    printf("\n\n");

    start_merge_sort(array, 0, sizeof(array) / 4, 4);

    printf("Current array: ");
    print_array(array, 0, sizeof(array) / 4);

    return EXIT_SUCCESS;
}
