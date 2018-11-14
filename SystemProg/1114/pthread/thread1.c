#include <unistd.h>
#include <pthread.h>

#include <stdio.h>

// 컴파일 하는 방법
// $ gcc source.c -lpthread
// $ gcc source.c -pthread

// pthread_create
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

	for (i = 0 ; i < 10; ++i) {
		sleep(1);
		printf("main thread...\n");
	}

	// 스레드에 대해서 종료를 대기해야 합니다.
	void* ret;
	pthread_join(thread, &ret);
	printf("ret: %p\n", ret);
}














