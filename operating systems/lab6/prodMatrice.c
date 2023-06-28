#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

int A[100][100], B[100][100], C[100][100], n1, n2, m1, m2;

void* produs (void * arg)
{
	int *index = (int *) arg;
	int i = index[0];
	int j = index[1];
	
	for(int k=0; k<m1; k++)
		C[i][j] += A[i][k] * B[k][j];
		
	return NULL;
}



int main ()
{
	// citire marticea A
	scanf("%d", &n1);	
	scanf("%d", &m1);
	for(int i=0; i<n1; i++)
		for(int j=0; j<m1; j++)
			scanf("%d", &A[i][j]);
			
	// citire matricea B
	scanf("%d", &n2);	
	scanf("%d", &m2);
	for(int i=0; i<n2; i++)
		for(int j=0; j<m2; j++)
			scanf("%d", &B[i][j]);
			

	// n1 * m2 threaduri
	int nr_threads = n1 * m2;
	pthread_t *tid = (pthread_t*) malloc (nr_threads*sizeof(pthread_t));
	

	for(int i=0; i<n1; i++)
		for(int j=0; j<m2; j++)
		{
			int *arg = malloc(sizeof(int)*2);
			arg[0] = i;
			arg[1] = j;
			
			if(pthread_create(tid + (i * m2 + j), NULL, produs, arg))
			{
				perror (NULL);
				return errno ;
			}
			
		}
		
		
	for(int i=0; i<n1; i++)
		for(int j=0; j<m2; j++)
			if(pthread_join(tid[i * m2 + j], NULL))
			{
				perror("Eroare join thread.\n");
				return errno;
			}
			
		
    	// afisare matrice
    	for(int i=0; i<n1; i++)
    	{
		for(int j=0;  j<m2; j++)
		{
			printf("%d ", C[i][j]);
	    	}

	    printf("\n");

	}
	
    	return 0;

}

// compilare cu -pthread
// exemplu: 2 2 6 7 8 9 2 2 1 2 3 4







