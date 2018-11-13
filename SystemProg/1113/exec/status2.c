#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0) {
		getchar();
		exit(100);
	}

	wait(&status);
	if (WIFEXITED(status)) {
		printf("exit - status: %d\n", WEXITSTATUS(status));
	} else if (WIFSIGNALED(status)) {
		if (WCOREDUMP(status)) {
			printf("Code dumped...");
		}

		printf("signal - status: %d\n", WTERMSIG(status));
	}

	/*
	if (status & 0xff) {
		printf("signal - status: %d\n", status & 0xff);
	} else {
		printf("exit - status: %d\n", (status >> 8) & 0xff);
	}
	*/
}
