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
	
	pid_t pid = fork();

	if(pid < 0)
	{
		perror("Eroare la creare proces.");
		return errno;
	}
	
	else if(pid == 0)
	{
		int x = atoi(argv[1]);
		
		printf("%d: ", x);
		
		while(x != 1)
		{
			printf("%d ", x);
			if(x % 2 == 0) x/=2;
			else x = 3*x+1;
		}
		
		printf("1.\n");
	}
	else
	{
		wait(NULL);
		printf("Child %d finished.", pid);
	}
	return 0;
}







