#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

// # 부모와 자식 프로세스의 로직을 분기해야 한다.
// => 부모 프로세스와 자식 프로세스의 fork()의 반환값이 다르다.
// 부모 프로세스: 자식 프로세스의 PID를 받는다.
// 자식 프로세스: 0을 받습니다.

int main()
{
	pid_t pid;

	pid = fork();
	if (pid > 0) {
		// 부모 프로세스의 로직
		printf("parent...\n");
		exit(0);

	} else if (pid == 0) {
		// 자식 프로세스의 로직
		printf("child...\n");
		exit(0);

	} else {
		perror("fork");
		// printf("error...\n");
	}

	printf("hi...\n");
}





