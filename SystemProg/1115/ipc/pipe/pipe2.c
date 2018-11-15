#include <unistd.h>
#include <signal.h>

#include <stdio.h>
// ./a.out ps sort 
// $ ps | sort
int main(int argc, char **argv)
{
	int fd[2];
	if (argc != 3) {
		return -1;
	}

	pid_t pid;

	if (pipe(fd) == -1) {
		perror("pipe");
		return 1;
	}

	if ((pid = fork()) > 0) {
		// 사용하지 않는 파이프를 닫는다.	
		close(fd[0]);
		dup2(fd[1], 1);
		// oldfd: dup(fd[1]);
		// newfd: close(1);

		// close(1);
		// dup(fd[1]);
		execlp(argv[1], argv[1], NULL);
	} else if (pid == 0) {
		close(fd[1]);
		dup2(fd[0], 0);
		execlp(argv[2], argv[2], NULL);
	} else {
		perror("fork");
	}
}






