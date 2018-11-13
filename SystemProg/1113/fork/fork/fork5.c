#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#include <stdio.h>
#include <stdlib.h>

// 문제점?
//  : fork() 목적은 동시성이다.
//    아래처럼 사용하면 동시성(병행성)을 사용할 수 없다.

// 리눅스는 자식 프로세스의 종료를 비동기적으로 처리할 수 있는 방법을
// 제공합니다.
//  => 시그널
//  =>  자식 프로세스는 자신이 종료되는 시점에 부모 프로세스에게 자신의
//     죽음을 시그널을 통해 알려줍니다.
//  => SIGCHLD
//  => SIGCHLD의 기본 동작은 무시입니다.

// 시그널은 비동기 입니다.
// => 언제 시그널이 발생할지 알 수 없습니다.

// 동기
// int ret = foo();


// 비동기
//  Blocking: 이벤트가 완료될 때까지 대기해야 한다.
//  Non-Blocking: 이벤트를 요청하고, 바로 반환한다.
//    -> Callback으로 처리한다.
//    -> Callback은 내가 호출하는 것이 아닌, 호출 되는 함수
void on_foo(int ret) {

}

void foo(void (*callback)(int)) {
	// Event 처리하고 나온 결과를 
	callback(42);
}

// foo(on_foo); 

void on_exit_child(int signo) {
	printf("signo: %d\n", signo);
	printf("자식 죽음...\n");

	wait(NULL);
}

int main()
{
	pid_t pid;
	int i;

	// signal 시스템 콜을 이용하면, 프로세스가 특정 시그널을 받았을 때의
	// 동작을 재정의할 수 있습니다.
	// signal(SIGCHLD, &on_exit_child);
	signal(SIGCHLD, on_exit_child);

	pid = fork();
	if (pid == 0) {
		for (i = 0 ; i < 5 ; ++i) {
			sleep(1);
			printf("\t\tchild\n");
		}
		exit(3);
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








