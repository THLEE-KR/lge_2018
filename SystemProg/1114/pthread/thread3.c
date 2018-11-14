// 스레드 동기화
#include <pthread.h>
#include <stdio.h>

// 1. 동기화 문제는 두개 이상의 스레드가 동일한 메모리에 대해서
//    읽거나 쓸 때 발생한다.

// 2. n++ 의 연산은 원자적이지 않다.
// n = 11                  

//    mov eax, [n]
//    add eax, 1         mov eax, [n]
//    mov [n], eax       add eax, 1
//                       mov [n], eax

// 3. 경쟁 조건(Race Condition)
//   : 여러 개의 스레드가 동시에 같은 메모리를 참조해서 연산하는 작업

// 4. 임계 영역(Critical Section)
//   : 여러 개의 스레드가 동시에 접근해서 문제가 발생하는 영역

// 5. 상호 배제(Mutual Exclusion)
//   : 임계 영역에 대해서 오직 한개의 스레드가 접근 가능하도록 하는 작업

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// open -> sys_open

int n = 0;
void *foo(void* arg) 
{
	int i;
	int local_n = 0;
	for (i = 0; i < 1000000; ++i) {
		local_n++;
	}

	pthread_mutex_lock(&mutex);
	n += local_n;
	pthread_mutex_unlock(&mutex);

	return 0;
}

int main()
{
	int i;
	pthread_t thread[3];
	for (i = 0; i < 3; ++i) {
		pthread_create(&thread[i], NULL, foo, NULL);
	}

	for (i = 0; i < 3; ++i) {
		pthread_join(thread[i], NULL);
	}

	printf("result: %d\n", n);
}









