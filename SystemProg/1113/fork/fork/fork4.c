#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <stdio.h>
#include <stdlib.h>

int main()
{
	pid_t pid;
	int i;

	pid = fork();
	if (pid == 0) {
		for (i = 0 ; i < 5 ; ++i) {
			sleep(1);
			printf("\t\tchild\n");
		}
		exit(3);
	}

	getchar();
	// 자식 프로세스가 종료되면, 좀비 프로세스가 되지 않도록
	// wait 시스템 콜을 통해 종료 상태값을 확인해야 합니다.
	wait(NULL);

	while (1) {
		sleep(1);
		printf("parent\n");
	}

}








