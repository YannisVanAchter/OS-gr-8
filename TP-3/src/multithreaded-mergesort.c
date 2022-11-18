#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <stdint.h>
#include "singlethreaded-mergesort.h" // merge_sort(), merge(), index, length

#define N_THREAD 4
#define SIZE_MAXX 5

struct thread_args {
    index start;
    index final;
    int* array;
};

void* thread_merge_sort(void* arguments) {
  struct thread_args* args = ((struct thread_args*) arguments);
  index start = args->start;
  index final = args->final;
  int* array = args->array;

  if(start < final) {
    index middle = floor((start + final) / 2);
    merge_sort(array, start, middle);
    merge_sort(array, middle+1, final);
    merge(array, start, middle, final);
  }
}

void start_merge_sort(int array[], index start, index final) {
    index end_seg = floor((start + final) / N_THREAD);

    struct thread_args* args = malloc(sizeof(struct thread_args));
    args->array = array;
    pthread_t thread_array[N_THREAD];
    index begin = start; 
    index end = end_seg;
    for (index n_thread = 0; end <= final;  n_thread++) 
    {
        args->start = begin;

        for(int i = 0; end > final; i++) end--; // decrement the end of segmentation if we go too far in memory
        args->final = end;
        pthread_create(thread_array + n_thread, NULL, thread_merge_sort, args);
        end += end_seg; begin += end_seg;
    }

    // merge from all thread 
    index begin = start; 
    index end = end_seg;
    for (index n_thread = 0; end <= final;  n_thread++) 
    {
        args->start = begin;

        for(int i = 0; end > final; i++) end--; // decrement the end of segmentation if we go too far in memory
        args->final = end;
        pthread_create(thread_array + n_thread, NULL, thread_merge_sort, args);
    }
}


int main(int argc, char **argv)
{
    // srand(time(NULL));

    int tab[SIZE_MAXX];

}
