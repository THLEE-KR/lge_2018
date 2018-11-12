#include <unistd.h>
// =G
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdio.h>

// FILE*
//     stdin  stdout  stderr
// FD    0       1       2

int main()
{
	// FILE* fp;
	int fd;

	char buff[100];
	int ret;

	// fp = fopen("stdio.c", "r");
	fd = open("stdio.c", O_RDONLY);

	// while ((ret = read(fd, buff, sizeof buff)) != 0) {
	// read의 반환값
	//  EOF: 0을 반환한다.
	//     : 읽은 바이트 수를 반환합니다.
	// 에러: -1을 반환합니다.
	while ((ret = read(fd, buff, sizeof buff)) > 0) {
		write(1, buff, ret);
	}

	/*
	while (ret = fread(buff, 1, sizeof buff, fp)) {
		fwrite(buff, 1, ret, stdout);
	}
	*/

	// fclose(fp);
	close(fd);
	return 0;
}







