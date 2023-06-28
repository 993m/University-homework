#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	if(argc < 2)
	{	
		printf("Numar invalid de argumente\n");
		return EINVAL;
	}
	
	
	
	// memoria partajata:
	char shm_name[] = "myshm";
	int shm_fd = shm_open(shm_name, O_CREAT|O_RDWR, S_IRUSR|S_IWUSR);

	if (shm_fd < 0)
	{
		perror("Eroare la shm_open");
		return errno;
	}

	int shm_size = 4096 * (argc - 1);
	if (ftruncate(shm_fd, shm_size) == -1)
	{
		perror(NULL);
		shm_unlink(shm_name);
		return errno;
	}
	// --------------------------------------
	
	

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
			//scriere in shm
			
			void *shr_ptr = mmap(0, 4096, PROT_WRITE, MAP_SHARED, shm_fd, 4096 * (i-1));
			
			if(shr_ptr == MAP_FAILED)
			{
				perror(NULL);
				shm_unlink(shm_name);
				return errno;
			}
	
			int *shm_int = (int*)shr_ptr;

			int x = atoi(argv[i]);
			
			while(x != 1)
			{
				*(shm_int++) = x;
				if(x % 2 == 0) x/=2;
				else x = 3*x+1;
			}
			
			*(shm_int++) = x;
			
			munmap(shr_ptr, 4096);
			
			printf("Done Parent %d Me %d\n", getppid(), getpid());
			
			break;
		}
		else
		{
			wait(NULL);
		}
	}
	
	if(pid > 0)
	{
		//citire din shm
		for(int i=1; i<argc; i++)
		{
			void *shr_ptr = mmap(0, 4096, PROT_READ, MAP_SHARED, shm_fd, 4096 * (i-1));
			if(shr_ptr == MAP_FAILED)
			{
				perror(NULL);
				shm_unlink(shm_name);
				return errno;
			}
			
			int *shm_int = (int*)shr_ptr;
			
			printf("%d:", *(shm_int++));
			
			while(*shm_int >= 1)
			{
				printf(" %d", *(shm_int++));
			}
        		
        		printf(".\n");
        		
        		munmap(shr_ptr, 4096);
		}
		
	
		printf("Done Parent %d Me %d\n", getppid(), getpid());
	} 
	
	shm_unlink(shm_name);
	return 0;
}

// compile command: gcc shmcollatz.c -o shmcollatz -lrt







