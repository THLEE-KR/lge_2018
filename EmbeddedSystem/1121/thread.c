#include <pthread.h>
#include <stdio.h>

// 컴파일러의 최적화 옵션을 걸었을 때, 변수의 값의 변경을 제대로
// 관찰하지 못하는 문제가 발생합니다.
//  => 메모리 가시성 문제
//  => 반드시 변수의 값을 메모리를 통해 읽거나 쓰도록 하는 키워드
//    : volatile

volatile int n = 1;
void *foo(void *p) {
	while (n) {
		;
	}

	return 0;
}

int main() {
	pthread_t thread;

	pthread_create(&thread, NULL, foo, NULL);
	getchar();
	n = 0;

	pthread_join(thread, NULL);
}
