#include <unistd.h>
#include <pthread.h>

#include <stdio.h>

// 1. main 함수가 반환하면, 프로세스는 종료한다.
// 2. 프로세스 내의 모든 스레드가 종료해야, 프로세스가 종료된다.

void *thread_routine(void *arg) 
{
	int i;
	for (i = 0 ; i < 3 ; ++i) {
		sleep(1);
		printf("foo thread...\n");
	}

	getchar();

	return (void*)0x100;
}

int main()
{
	int i;
	pthread_t thread;
	pthread_create(&thread, NULL, thread_routine, NULL);
	pthread_exit(0);
}














