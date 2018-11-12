#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdio.h>

int main()
{
	int fd;
	// O_RDONLY: Read mode
	// O_WRONLY: Write mode
	// O_RDWR: Read / Write mode
	// O_CREAT:  파일이 없을 경우 생성한다.
	// O_TRUNC:  파일이 존재할 경우, 파일의 사이즈를 0으로 바꾼다.

	// O_CREAT를 지정할 경우, 퍼미션을 지정할 수 있다.
	// fopen("out", "w");
	fd = open("out", O_WRONLY | O_CREAT | O_TRUNC, 0644);

	close(1);
	dup(fd);
	// 인자로 전달받은 디스크립터를 가장 낮은 곳에 복사한다.



	printf("hello, world\n");
	// write(1, "hello, world", strlen("hello, world"));
	printf("hello, world\n");
	printf("hello, world\n");
}
