#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[])
{

	if(argc < 3)
	{
		printf("Nr invalid de argumente\n");
		return EINVAL;
	}

	struct stat informatii;
	int r = stat(argv[1], &informatii);
	if(r<0)
	{
		perror("Eroare la citirea datelor\n");
		return 1;
	}
	printf("Fisierul %s are dimensiunea %ld\n", argv[1], informatii.st_size);
	
	// descriptor fisier scriere
	int fd_scriere = open(argv[2], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
	if(fd_scriere < 0)
	{
		perror("Eroare la deschidere fisier2\n");
		return 1;
	}

	// descriptor fisier citire
	int fd_citire = open(argv[1], O_RDONLY);
	if(fd_citire < 0)
	{
		perror("Eroare la deschidere fisier1\n");
		return 1;
	}
	
	// copiere
	int n = 5;
	char buffer[n];
	int nr_read, nr_write, i=0;
	while(1)
	{
		nr_read = read(fd_citire, buffer, n);
		if(nr_read < 0)
		{
			perror("Eroare la citire\n");
			close(fd_citire);
			close(fd_scriere);
			return 1;
		}
		
		if(nr_read < n)
		{
			buffer[nr_read] = '\0';
			
			nr_write = write(fd_scriere, buffer, strlen(buffer));
			
			if(nr_write != strlen(buffer))
			{
				perror("Eroare la scriere\n");
				close(fd_scriere);
				close(fd_citire);
				return 1;
			}
		
			close(fd_scriere);
			close(fd_citire);
			return 0;
		}
		
		nr_write = write(fd_scriere, buffer, n);
		
		if(nr_write != n)
		{
			perror("Eroare la scriere\n");
			close(fd_scriere);
			close(fd_citire);
			return 1;
		}
		
	}
	
	
}
