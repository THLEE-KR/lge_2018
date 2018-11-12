#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdio.h>

// 동일한 파일을 두번 열었을 때, 각 디스크립터는
// 오프셋을 공유하는가?

int main()
{
	int fd1, fd2;
	char buf[100];
	int ret;

	fd1 = open("input.txt", O_RDONLY);
	printf("fd1: %d\n", fd1);

	fd2 = open("input.txt", O_RDONLY);
	printf("fd2: %d\n", fd2);

	ret = read(fd1, buf, 2);
	write(1, buf, ret);
	
	ret = read(fd2, buf, 2);
	write(1, buf, ret);

	close(fd1);
	close(fd2);

	return 0;
}

















