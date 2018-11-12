#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdio.h>

// fseek: 표준 라이브러리(FILE)의 파일 오프셋을 변경합니다.
// lseek: 시스템 콜을 통해 파일의 오프셋을 변경합니다.

// # 라이브러리를 사용하지 않고, 시스템 콜을 통해 파일을
//   다룰 때에도 오프셋을 지원합니다.

int main()
{
	int fd = open("input.txt", O_RDONLY);
	int ret;
	char buf[128];

	if (fd == -1) {
		fprintf(stderr, "file open error...\n");
		return -1;
	}
	printf("fd: %d\n", fd);

	ret = read(fd, buf, 2);
	write(1, buf, ret);

	lseek(fd, 0, SEEK_SET);
	// SEEK_SET: 처음
	// SEEK_END: 마지막
	// SEEK_CUR: 현재

	ret = read(fd, buf, 2);
	write(1, buf, ret);

	close(fd);
}













