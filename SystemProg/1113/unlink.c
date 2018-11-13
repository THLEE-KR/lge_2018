#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdio.h>

int main()
{
	int fd, ret;
	char buf[100];
	fd = open("zzz", O_RDWR | O_CREAT | O_TRUNC, 0666);
	getchar();

	unlink("zzz");
	write(fd, "hello\n", 6);

	lseek(fd, 0, SEEK_SET);

	ret = read(fd, buf, sizeof buf);
	write(1, buf, ret);

	while (1)
		;
	
	return 0;
}
