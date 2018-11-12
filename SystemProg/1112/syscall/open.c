#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// task_struct
int main()
{
	int fd = open("open.c", O_RDONLY);
	printf("fd: %d\n", fd);

	close(fd);
}








