#include<stdio.h> // printf()
#include<stdlib.h> // EXIT_SUCCESS
#include<pthread.h> // pthread_t, pthread_create(), pthread_mutex_trylock(), pthread_mutex_unlock(), pthread_mutex_init, pthread_mutex_t
#include<unistd.h> // sleep()

#ifndef NB_PHILOSOPHE
#define NB_PHILOSOPHE 5

#define DROITE(i) (( i ) % NB_PHILOSOPHE)
#define GAUCHE(i) ((i + 1) % NB_PHILOSOPHE)
#define false 0
#define true 1

pthread_mutex_t baguettes[NB_PHILOSOPHE];

void manger(int phil)
{
	printf("Philosophe %d mange \n",phil);
	sleep(2);
	printf("Philosophe %d a fini de manger \n",phil);
}

int tenter(int phil)
{
    printf("Le philosophe n %d essaye de prendre les baguettes\n", phil);

    // Try take the chopsticks
	int right = pthread_mutex_trylock(&baguettes[DROITE(phil)]);
	int left = pthread_mutex_trylock(&baguettes[GAUCHE(phil)]);
    
	if (left == 0 && right == 0) 
	{ // if philosopher has chopsticks
    	printf("%d a récupéré les baguettess\n", phil);
		return 1;
	}
	if (left != 0)
	{ // if philosopher didn't get the left one
		pthread_mutex_unlock(&baguettes[GAUCHE(phil)]);
	}
	if (right != 0)
	{ // if philosopher didn't get the right one
		pthread_mutex_unlock(&baguettes[DROITE(phil)]);
	}
    
	printf("%d n'a pas récupéré les baguettess\n", phil);

	return 0;
}

void libere(int phil)
{
    // drop chopsticks for the next
	pthread_mutex_unlock(&baguettes[GAUCHE(phil)]);
	pthread_mutex_unlock(&baguettes[DROITE(phil)]);
}

void penser(int phil)
{
	printf("Philosophe %d pense\n",phil);
	sleep(2);
	printf("Philosophe %d a fini de penser\n",phil);
}

void * philosophe(void * num)
{
	int phil = *(int *)num;
	printf("Je suis le philosophe %d\n",phil);
	int have_chopsticks = 0;

	while(true) 
	{		
		have_chopsticks = tenter(phil);
		if (have_chopsticks)
		{ // if philosopher has chopsticks he can eat
			manger(phil);
			libere(phil);
		}
		penser(phil);
	}
}

int main(int *argc, int *argv[])
{
	int i,a[NB_PHILOSOPHE];
	pthread_t pid[NB_PHILOSOPHE];

	// set each chopstrics as a mutex
	for (i=0; i<NB_PHILOSOPHE; i++)
		pthread_mutex_init(&baguettes[i], NULL);
		
	// generate thread for each philosopher
	for(i=0;i<NB_PHILOSOPHE;i++)
	{
		a[i]=i;
		pthread_create(&pid[i], NULL, philosophe, (void *)&a[i]);
	}

	for (i = 0; i<NB_PHILOSOPHE; i++)
		pthread_join(pid[i], NULL);
	
	return EXIT_SUCCESS;
}

#endif