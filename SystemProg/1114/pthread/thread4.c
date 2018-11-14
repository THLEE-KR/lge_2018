#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/syscall.h> 

int mutex = 1;

void * foo(void *data)
{
	printf("start foo\n");
	syscall(202, &mutex, 0, 1, 0);  // __futex_wait();
	printf("after\n");
	return 0;
}

int main()
{
	pthread_t thread;
	pthread_create( &thread, 0, foo, 0 );
	getchar();
	syscall(202, &mutex, 1, 1);  // __futex_wake();
	pthread_join( thread, 0 );
	return 0;
}

