#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <poll.h>

#include <stdio.h>

// 아래 코드의 문제점
//  : read는 디스크립터의 수신 버퍼에 데이터가 존재하지 않으면
//    대기한다.

// multiplexing IO(poll, epoll, select)
//  => 해당 디스크립터의 수신 버퍼에 데이터가 존재함을 감지하는 시스템 콜

#if 0
struct pollfd {
	int fd;
	short events;
	short revents;
};
#endif

int main()
{
	struct pollfd fds[2];
	int ret;
	char buf[512];
	int len;
	int fd = open("myfifo", O_RDONLY);
	if (fd == -1) {
		perror("open");
		return 1;
	}

	fds[0].fd = 0;
	fds[0].events = POLLIN;
	fds[1].fd = fd;
	fds[1].events = POLLIN;

	while (1) {
		ret = poll(fds, 2,  -1);
		if (ret == 0) 
			continue;

		if (fds[0].revents & POLLIN) {
			len = read(0, buf, sizeof buf);
			buf[len] = '\0';
			printf("from keyboard: %s\n", buf);
		} else if (fds[1].revents & POLLIN) {
			len = read(fd, buf, sizeof buf);
			buf[len] = '\0';
			printf("from fifo: %s\n", buf);
		}
	}
}















