#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>

#define NTHRS 5
sem_t sem;
pthread_mutex_t mtx;
int n;


int barrier_point()
{
	pthread_mutex_lock(&mtx);
	n += 1;
	
	if(n == NTHRS)
	{
		for(int i=0; i<n; i++)
			if (sem_post(&sem))
			{
				perror (NULL);
				return errno ;
			}
		n = 0;
	}
	
	pthread_mutex_unlock(&mtx);
		
	if (sem_wait(& sem))
	{
		perror (NULL);
		return errno ;
	}
				
	return 0;
}

void *tfun (void *arg)
{
	int *t = (int *)arg;
	printf("%d reached the barrier\n", *t);
	barrier_point ();
	printf("%d passed the barrier\n", *t);
	return NULL;
}

int main()
{
	printf("NTHRS=%d\n", NTHRS);
	
	// citire date
	printf("Introduceti numarul de threaduri: ");
	
	int nr_threads;
	scanf("%d", &nr_threads);
	// -------------------------------------------------------------------------------
	
	
	//initializare semafor
	if (sem_init(&sem, 0, 0))
	{
		perror (NULL);
		return errno ;
	}
	// ------------------------------------------------

	//initializare mutex
	if (pthread_mutex_init (& mtx , NULL)) 
	{
		perror (NULL);
		return errno ;
	}
	// ------------------------------------------------


	// threaduri
 	pthread_t *tid = (pthread_t*) malloc (nr_threads*sizeof(pthread_t));
 		
 	
 	for(int i=0; i<nr_threads; i++)
	{	
		
		if(pthread_create(tid + i, NULL, tfun, tid+i))
		{
		    perror(NULL);
		    return errno;
		}
	}


	for(int i=0; i<nr_threads; i++)
    	{
        	if(pthread_join(tid[i], NULL))
        	{
            		perror(NULL);
            		return errno;
        	}
    	}
	// ------------------------------------------------
	
	
    	//distrugere semafor
    	sem_destroy(&sem);
    	
    	//distrugere mutex
    	pthread_mutex_destroy(&mtx);
    	
    	return 0;
}
