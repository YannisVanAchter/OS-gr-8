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

pthread_mutex_t baguettes[NB_PHILOSPHE];

void manger(int phil)
{
	printf("Philosophe %d mange \n",phil);
	sleep(2);
	printf("Philosophe %d a fini de manger \n",phil);
}

int tenter(int phil)
{
    printf("Le philosophe n° %d essaye de prendre les baguettes\n", phil);

    // Try take the chopsticks
	int right = pthread_mutex_trylock(&baguettes[DROITE(phil)]);
	int left = pthread_mutex_trylock(&baguettes[GAUCHE(phil)]);
    
	if (left == 0 && right == 0)
	{
    	printf("A récupérer les baguettess\n");
		return 1;
	}
	if (left != 0)
	{
		pthread_mutex_unlock(&baguettes[GAUCHE(phil)]);
	}
	if (right != 0)
	{
		pthread_mutex_unlock(&baguettes[DROITE(phil)]);
	}
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
	int s = 0;

	while(true) 
	{
		printf("Je suis le philosophe %d\n",phil);
		
		s = tenter(phil);
		if (s)
		{
			manger(phil);
			libere(phil);
		}
		penser(phil);
	}
}

int main()
{
	int i,a[NB_PHILOSPHE];
	pthread_t tid[NB_PHILOSPHE];

	for (i=0; i<NB_PHILOSPHE; i++)
	{

		pthread_mutex_init(&baguettes[i], NULL);
	}
		
	for(i=0;i<NB_PHILOSPHE;i++)
	{
		a[i]=i;
		pthread_create(&tid[i], NULL, philosophe, (void *)&a[i]);
	}
	for(i=0;i<NB_PHILOSPHE;i++)
		pthread_join(tid[i], NULL);
}
