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
sem_t baguettes[NB_PHILOSPHE];

void manger(int phil)
{
	printf("Philosophe %d mange \n",phil);
	sleep(2);
	printf("Philosophe %d a fini de manger \n",phil);
}

void tenter(int phil)
{
    printf("Le philosophe n° %d essaye de prendre les baguettes\n", phil);

    // Try take the chopsticks
    sem_wait(&baguettes[DROITE(phil)]);
    sem_wait(&baguettes[GAUCHE(phil)]);
    
    printf("A récupérer les baguettess\n");
}

void libere(int phil)
{
    // drop chopsticks for the next
	sem_post(&baguettes[GAUCHE(phil)]);
	sem_post(&baguettes[DROITE(phil)]);
}

void * philosophe(void * num)
{
	int phil = *(int *)num;

	sem_wait(&room);
	printf("Je suis le philosophe %d\n",phil);
    
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
		sem_init(&baguettes[i],0,1);
		
	for(i=0;i<NB_PHILOSPHE;i++){
		a[i]=i;
		pthread_create(&tid[i], NULL, philosophe, (void *)&a[i]);
	}
	for(i=0;i<NB_PHILOSPHE;i++)
		pthread_join(tid[i], NULL);
}
