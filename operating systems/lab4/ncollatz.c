#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	if(argc < 2)
	{	
		printf("Numar invalid de argumente\n");
		return EINVAL;
	}
	
	printf("Starting parent %d\n", getpid());
	
	pid_t pid;
	
	for(int i=1; i<argc; i++)
	{		
		pid = fork();

		if(pid < 0)
		{
			perror("Eroare la creare proces.\n");
			return errno;
		}
		
		
		else if(pid == 0)
		{
			int x = atoi(argv[i]);
			
			printf("%d: ", x);
			
			while(x != 1)
			{
				printf("%d ", x);
				if(x % 2 == 0) x/=2;
				else x = 3*x+1;
			}
			
			printf("1.\n");
			
			printf("Done Parent %d Me %d\n", getppid(), getpid());
			
			break;
		}
		else
		{
			wait(NULL);
		}
	}
	
	if(pid > 0) printf("Done Parent %d Me %d\n", getppid(), getpid());
	
	
	return 0;
}







