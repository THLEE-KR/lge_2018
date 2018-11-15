#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>

#include <stdio.h>

int main(int argc, char **argv)
{
	char buf[100];
	int pfd[2];
	pipe(pfd);

	fcntl(pfd[0], F_SETFL, O_NONBLOCK); // O_NDELAY

	int ret;
	while ((ret = read(pfd[0], buf, sizeof buf))) {
		if (ret == 0) {
			break;
		}
		else if (ret == -1) {
			if (errno != EAGAIN) {
				perror("read");	
				return -1;
			}
		}
		write(1, buf, ret);
	}

	printf("ret: %d\n", ret);
}






