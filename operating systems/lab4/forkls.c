#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

int main()
{
	pid_t pid = fork();

	if(pid < 0)
	{
		perror("Eroare la creare proces.");
		return errno;
	}
	else if(pid == 0)
	{
		//printf("Copil: Hello!\n");
		char *argv[] = {"ls", NULL};
		execve("/usr/bin/ls", argv, NULL);
		printf("Execve a esuat\n");
	}
	else
	{
		wait(NULL);
		printf("Parinte: Am id %d! Copilul meu are id %d!\n",getpid(), pid);
	}
	return 0;
}
