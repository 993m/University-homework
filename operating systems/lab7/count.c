#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <stdlib.h>

#define MAX_RESOURCES 5
int available_resources = MAX_RESOURCES;
pthread_mutex_t mtx ;

int decrease_count (int count)
{
	pthread_mutex_lock(&mtx);
	
	if(available_resources < count)
		return -1;
	else
	{
		available_resources -= count;
		printf("Got %d resources %d remaining\n", count, available_resources);
	}
		
	pthread_mutex_unlock(&mtx);
	return 0;
}


int increase_count (int count)
{
	pthread_mutex_lock(&mtx);
	available_resources += count;
	printf("Released %d resources %d remaining\n", count, available_resources);
	pthread_mutex_unlock(&mtx);
	return 0;
}


void *fct (void *arg)
{
    int nr_resurse = *(int *)arg;
    while(decrease_count(nr_resurse) == -1);
    increase_count(nr_resurse);
    return NULL;
}

int main()
{
	printf("MAX_RESOURCES=%d\n", MAX_RESOURCES);
	
	// citire date
	printf("Introduceti numarul de threaduri si vectorul cu numarul de resurse pe care acestea le folosesc: \n");
	
	int nr_threads;
	scanf("%d", &nr_threads);
	
	int  nr_resurse[nr_threads];
	for(int i=0; i<nr_threads; i++) scanf("%d", nr_resurse + i);
	// -------------------------------------------------------------------------------
	
	
	//initializare mutex
	if (pthread_mutex_init (& mtx , NULL )) 
	{
		perror (NULL);
		return errno ;
	}
	// ------------------------------------------------


	// threaduri
 	pthread_t *tid = (pthread_t*) malloc (nr_threads*sizeof(pthread_t));
 		
 	for(int i=0; i<nr_threads; i++)
	{	
		if(pthread_create(tid + i, NULL, fct, &nr_resurse[i]))
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
	
	
    	//distrugere mutex
    	pthread_mutex_destroy(&mtx);
    	
    	return 0;
}
