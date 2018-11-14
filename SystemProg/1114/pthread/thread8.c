#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

// 동적 TLS - Pthread API를 이용해서 생성하고 사용하는 방법
// 1. pthread_key_create
// 2. pthread_getspecific
// 3. pthread_setspecific

// key: 스레드마다 다릅니다.
//  => 현재 스레드 아이디에 따라서 다른 값을 얻을 수 있습니다.

pthread_key_t key;
void foo()
{
	int *tsd;
	tsd = pthread_getspecific(key);
	if (tsd == NULL) {
		tsd = calloc(1, sizeof(int));
		pthread_setspecific(key, tsd);
	}

	++*tsd;
	printf("count: %d\n", *tsd);
}
/*
void foo()
{
	static __thread int tsd = 0;
	++tsd;
	printf("count: %d\n", tsd);
}
*/

void *thread1(void *arg) {
	foo();
	foo();
	foo();
	return 0;
}

void *thread2(void* arg) {
	foo();
	foo();
	foo();
	return 0;
}

// 소멸자
void dtor(void* p) {
	printf("dtor()\n");
	free(p);
}

int main()
{
	// TLS 생성
	pthread_key_create(&key, dtor);

	pthread_t thread[2];
	pthread_create(&thread[0], NULL, thread1, NULL);
	pthread_create(&thread[1], NULL, thread2, NULL);

	for (int i = 0 ; i < 2; ++i) {
		pthread_join(thread[i], NULL);
	}

	pthread_key_delete(key);

}
