#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdio.h>

int main()
{
	int fd = open("dup2.c", O_RDONLY);

	close(0);
	dup(fd);

	int ch;
	// read(0, buf, 1);
	while ((ch = getchar()) != EOF)
		putchar(ch);

	close(fd);
}
