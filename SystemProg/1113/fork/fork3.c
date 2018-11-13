#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

// fork()를 사용하는 이유
//  : 동시에 수행해야 하는 작업을 위해서
//  => Multi Process Programming
//  => 병행성(동시성) 프로그래밍
//  => Concurrent Programming

// 좀비 프로세스
// 1. 자식 프로세스가 부모 프로세스보다 먼저 종료될 경우 발생한다.
// 2. 왜?
//    부모 프로세스가 자식 프로세스의 종료 상태값을 확인하기 전까지
//    자식 프로세스의 메모리 블록은 해지되지 않는 상태가 필요하다.

// 고아 프로세스
//  : 부모 프로세스가 자식 프로세스보다 먼저 종료될 경우 발생한다.
//  => init 프로세스가 대신 부모 프로세스가 된다.
//     init 프로세스가 종료된 고아 프로세스의 종료 상태값을 수거해서
//     메모리가 해지 될 수 있다.




int main()
{
	pid_t pid;
	int i;

	pid = fork();
	if (pid == 0) {
		for (i = 0 ; i < 10 ; ++i) {
			sleep(1);
			printf("\t\tchild\n");
		}
		exit(3);
	} else if (pid > 0) {
		while (1) {
			sleep(1);
			printf("parent\n");
		}

	} else {
		perror("fork");
		exit(1);
	}
}





