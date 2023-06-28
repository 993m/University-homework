// Cerinta 1

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[])
{

	if(argc < 2)
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

	//Scriere
	int fd_scriere = open(argv[1], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
	if(fd_scriere < 0)
	{
		perror("Eroare la deschidere fisier\n");
		return 1;
	}
	printf("Descriptorul pt %s este %d\n", argv[1],  fd_scriere);

	char *buffer = "Hello world!";
	int nr_write = write(fd_scriere, buffer, strlen(buffer));
	if(nr_write != strlen(buffer))
	{
		perror("Eroare la scriere\n");
		close(fd_scriere);
		return 1;
	}
	printf("Am scris in %s textul '%s'\n", argv[1], buffer);

	close(fd_scriere);

	//Citire

	int fd_citire =	open(argv[1], O_RDONLY);
	if(fd_citire < 0)
	{
		perror("Eroare deschidere fisier\n");
		return 1;
	}
	
	char buffer2[20];
	int nr_read = read(fd_citire, buffer2, 20);

	if(nr_read < 0)
	{
		perror("Eroare la citire\n");
		close(fd_citire);
		return 1;
	}
	
	printf("Am citit din %s textul '%s', lungime %d\n", argv[1], buffer2, nr_read);

	close(fd_citire);

	return 0;
	


}
