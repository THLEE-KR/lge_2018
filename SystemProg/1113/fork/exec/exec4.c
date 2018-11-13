#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#include <stdio.h>
#include <stdlib.h>

int main()
{
	pid_t pid;

	if ((pid = fork()) == 0) {
		char* argv[] = { "ls", "-l", NULL };
		int ret = execvp(argv[0], argv);

		if (ret == -1) {
			perror("execvp");
			exit(-1);
		}
	}
	
	wait(NULL);
	printf("Show me the money...\n");
}
