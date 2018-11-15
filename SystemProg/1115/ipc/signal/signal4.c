// sig_parent
// : 자식 프로세스(./sig_child)를 3개 생성하여,
//   10초 후에 인위적으로 SIGINT 메세지를 자식들에게 보낸다.
#include <unistd.h>
#include <signal.h>

#include <stdio.h>

#define NUMCHILD 3

int main(int argc, char* argv[])
{
	int pid, chpid[NUMCHILD];
	int i, status;

	for (i = 0; i < NUMCHILD; i++) {
		if ((pid = fork()) == 0)
			execlp("./sig_child", "./sig_child",
					(char*)0);
		chpid[i] = pid;
	}
	printf("sig_parent: %d child process run\n", NUMCHILD);
	sleep(10);
	for(i = 0; i < NUMCHILD; i++)
		kill(chpid[i], SIGINT);
}

