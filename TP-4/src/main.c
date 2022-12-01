#include<stdio.h> // printf
#include<stdlib.h> // EXIT_SUCCESS
#include<pthread.h> // pthread_t, pthread_create(), pthread_join()
#include<semaphore.h> // sem_t, sem_init(), sem_wait(), sem_post()
#include<unistd.h> // sleep

#define NB_PHILOSPHE 5

#define DROITE(i) (( i ) % NB_PHILOSPHE)
#define GAUCHE(i) ((i + 1) % NB_PHILOSPHE)
#define false 0
#define true 1

sem_t room;
sem_t chopstick[NB_PHILOSPHE];

void manger(int phil)
{
	printf("Philosopher %d is eating\n",phil);
	sleep(2);
	printf("Philosopher %d has finished eating\n",phil);
}

void tenter(int phil)
{
    printf("Try take chopsticks\tI'm the %d philo\n", phil);

    // Try take the chopsticks
    sem_wait(&chopstick[DROITE(phil)]);
    sem_wait(&chopstick[GAUCHE(phil)]);
    
    printf("Get the chopsticks\n");
}

void libere(int phil)
{
    // drop chopsticks for the next
	sem_post(&chopstick[GAUCHE(phil)]);
	sem_post(&chopstick[DROITE(phil)]);
}

void * philosophe(void * num)
{
	int phil=*(int *)num;

	sem_wait(&room);
	printf("Philosopher %d has entered room\n",phil);
    
    tenter(phil);
	manger(phil);
    libere(phil);

	sem_post(&room);
}

int main()
{
	int i,a[NB_PHILOSPHE];
	pthread_t tid[NB_PHILOSPHE];
	
	sem_init(&room,0,4);
	
	for(i=0;i<NB_PHILOSPHE;i++)
		sem_init(&chopstick[i],0,1);
		
	for(i=0;i<NB_PHILOSPHE;i++){
		a[i]=i;
		pthread_create(&tid[i], NULL, philosophe, (void *)&a[i]);
	}
	for(i=0;i<NB_PHILOSPHE;i++)
		pthread_join(tid[i], NULL);
}

/* INPIRED BY - ANUSHKA DESHPANDE */