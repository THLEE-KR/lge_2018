
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <string.h>
#include <errno.h>

// System Call: 에러가 발생하면, -1 을 반환한다.
//  => 에러의 원인을 파악하기 위해서 errno에 에러코드를 설정한다.

int main()
{
	int fd = open("a.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		// printf("open: %s\n", strerror(errno));
		// printf("errno: %d\n", errno);
		// printf("open file error\n");
		return -1;
	}

}
