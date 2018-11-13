#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#include <stdio.h>
#include <stdlib.h>

// 아래 코드의 문제점?
// 1. 시그널을 중첩되지 않는다.
// 2. 시그널은 저장되지 않는다.
// => 동시에 자식 프로세스 여러개가 종료될 경우, 오직 한번의 SIGCHLD 
//    만 발생한다.


void on_exit_child(int signo) {
	printf("signo: %d\n", signo);
	printf("자식 죽음...\n");

	// WNOHANG: Non-Blocking 연산입니다.
	while (waitpid(-1, NULL, WNOHANG) > 0)
		;
}
// 시그널 핸들러 안에서는 블록킹 연산을 사용하면 안됩니다.
/*
void on_exit_child(int signo) {
	printf("signo: %d\n", signo);
	printf("자식 죽음...\n");

	while (wait(NULL) > 0)
		;
}
*/

int main()
{
	pid_t pid;
	int i;

	signal(SIGCHLD, &on_exit_child);

	for (i = 0 ; i < 20 ; ++i) {
		pid = fork();
		if (i == 4) {
			sleep(5);
		}

		if (pid == 0) {
			int i;
			for (i = 0 ; i < 5 ; ++i) {
				// sleep(1);
				printf("\t\tchild\n");
			}
			exit(3);
		}
	}

	// getchar();
	// 자식 프로세스가 종료되면, 좀비 프로세스가 되지 않도록
	// wait 시스템 콜을 통해 종료 상태값을 확인해야 합니다.
	// wait(NULL);

	while (1) {
		sleep(1);
		printf("parent\n");
	}

}








