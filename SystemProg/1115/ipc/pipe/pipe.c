#include <unistd.h>
#include <unistd.h>
#include <signal.h>

#include <stdio.h>

// pipefd[0]: read 전용
// pipefd[1]: write 전용
int pipefd[2];
void sig_int(int signum) {
	printf("sig_int...\n");
	write(pipefd[1], "hello", 5);
}

int main()
{
	char buf[100];
	int ret;

	if (pipe(pipefd) < 0) {
		perror("pipe");
		return -1;
	}
	signal(SIGINT, sig_int);

	while ((ret = read(pipefd[0], buf, sizeof buf)) > 0) {
		printf("from pipe: ");
		write(1, buf, ret);
	}
	
	return 0;
}






