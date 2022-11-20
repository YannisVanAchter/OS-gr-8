/**
 * Travail 3 TP OS (INFOB231)
 * Dans le cadre de l'exercice de groupe nous avons du tester le programme sur un certain nombre de threads. 
 * Vous trouverez la capture d'écran de l'exécution ici
 * 
 * Voici nos conclussion:
 * Plus le nombre de threads est grand plus les processus attendent pour passer dans le processeur et etre exécuter. 
 * Celà a pour conséquence de ralentir significativement le traitement du merge sort.
 * Il n'est pas nessésaire de faire plusieur threads pour nos besoin quotidient.
 * 
 * Méthode de testing
 * Nous avons conserver la liste présente dans le code mais avons passé en inline arguments le nombre de threads souhaiter (voir image). 
 * Le programme se contente juste d'afficher le temps de traitement
 * 
 * Rappel de l'exécution pour 120.000 éléments:
 * 1 thread: 31.039.900ns
 * 2 threads: 17.319.200 ns
 * 3 threads: 14.691.800 ns 
 * 4 threads: 14.520.800 ns (Optimum)
 * 5 threads: 12.188.200 ns
 * 10 threads: 12.252.600 ns
 * 50 threads: 58.334.000 ns
 * 100 threads: 68.696.600 ns
 * 1000 threads: 567.263.700 ns
*/

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
    const int array_size = final - start;
    const index end_seg = floor((start + final) / N_THREAD); // end of one standart segmentation

    // set variable of thread management and function parameters
    struct thread_args* args = malloc(sizeof(struct thread_args) * N_THREAD);
    pthread_t* thread_array = malloc(sizeof(pthread_t) * N_THREAD); // list of pids of threads
    index begin = start; 
    index end = end_seg;
    // loop to create threads and updates parameters
    for (index n_thread = 0; n_thread < N_THREAD; n_thread++) 
    {
        args[n_thread].array = array;
        args[n_thread].start = begin;
        args[n_thread].final = end;
        if (n_thread == N_THREAD - 1 && array_size % 2 != 0) 
            args[n_thread].final = array_size - 1; // Check if we end at right place in the array
        

        pthread_create(&(thread_array[n_thread]), NULL, thread_merge_sort, &(args[n_thread]));
        end += end_seg; 
        begin += end_seg;
    }

    // Wait end of first and second process
    void* thread_return;
    pthread_join(thread_array[0], &thread_return);
    pthread_join(thread_array[1], &thread_return);
    
    // merge from all thread
    index separator = end_seg;
    end = 2 *end_seg;
    for (index n_thread = 1; n_thread < N_THREAD; n_thread++)
    {
        if (n_thread >= 2) 
            pthread_join(thread_array[n_thread], &thread_return); // wait end of next segmentation to merge
        
        if (n_thread == N_THREAD - 1 && array_size % 2 != 0) 
            end = array_size - 1; // Check if we end at right place in the array
        
        merge(array, 0, separator, end); 
        separator += end_seg; 
        end += end_seg;
    } 
}

void print_array(int array[], int start, int final)
{
    for (int i = start; i < final - start; i++)
    {
        printf("%d, ", array[i]);
    }
    printf("\n");
}

long int nanos_between(struct timespec *final , struct timespec *start) 
{
    time_t seconds = final ->tv_sec - start ->tv_sec;
    long int nanoseconds = final ->tv_nsec - start ->tv_nsec;
    return seconds * 1e9 + nanoseconds;
}

int main(int argc, char *argv[])
{
    int MAX_SIZE = 120000;
    srand(time(NULL));
    int array[MAX_SIZE];
    for (int i = 0; i < MAX_SIZE; i++) array[i] = rand() % MAX_SIZE;

    struct timespec start, final;
    int N_THREAD = -1;
    char *p;

    if (N_THREAD == -1 && argc >= 1)
    {
      N_THREAD = strtol(argv[1], &p, 10);
    }
    else
    {
      printf("How many threads do you want: ");
      scanf("%d", &N_THREAD);
    }

    clock_gettime(CLOCK_REALTIME , &start );
    start_merge_sort(array, 0, sizeof(array) / 4, N_THREAD);
    clock_gettime(CLOCK_REALTIME , &final );

    printf("Time elapsed : %ld ns\n", nanos_between(&final , &start));

    return EXIT_SUCCESS;
}
