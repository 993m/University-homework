#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

char *sir;

void* strrev (void * cuv)
{
	char *s = (char *) cuv;
	sir = (char *)malloc((strlen(s))*sizeof(char));
	int index = 0;
	for(int i=strlen(s)-1; i>=0; i--)
		sir[index++] = s[i];
	return NULL;
}


int main (int argc, char* argv[])
{
	if( argc != 2)
	{
		printf("Numar invalid arg.\n");
		return EINVAL;
    	}		

	
	pthread_t tid;
	
	if(pthread_create (&tid , NULL , strrev, argv[1])) 
	{
		perror ( NULL );
		return errno ;
	}
	
	if(pthread_join(tid, NULL))
	{
		perror("Eroare join thread.\n");
        	return errno;
    	}
    	
    	printf("%s\n", sir);
    	return 0;

}

// compilare cu -pthread





