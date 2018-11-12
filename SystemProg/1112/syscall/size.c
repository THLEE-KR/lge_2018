#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdio.h>

// struct file

int main()
{
	int fd = open("a.out", O_RDONLY);
	long size = lseek(fd, 0, SEEK_END);

	printf("size: %ld\n", size);
	close(fd);
}
