
// 재진입 가능 함수
//   => 스레드 안전 하다.
//   => 재귀 함수로 돌릴 수 있다.
//   => 정적 메모리를 사용하지 않는다.

// 스레드 안전 함수: 두 개 이상의 스레드가 같은 함수를 동시에 호출하였을 때
//                   정상 동작하는 함수를 의미한다.

// 재진입이 불가능한 함수의 해결방법 2가지
// 1) Linux
//   : 재진입이 가능한 버전을 별도로 제공합니다. (다른 함수)
//   => 추가적인 인자를 전달한다.

// 2) Windows
//   : TLS(Thread Local Storage)
//     TSS(Thread Specific Storage)
//   => 각 스레드의 고유한 정적 메모리
//   만드는 방법 2가지
//   1) 정적 TLS: 컴파일러가 지원하는 확장 명령
//   2) 동적 TLS: pthread 라이브러리 함수


// 재진입이 불가능한 함수 - strtok, getpwnam
#include <string.h>
#include <stdio.h>

#include <pthread.h>

// char *strtok_r(char *str, const char *delim, char **saveptr);
// #define strtok(str, delim)  strtok_r(str, delim, &sp)

char* xstrtok(char* str, const char* delim) {
	static __thread char* sp;
	return strtok_r(str, delim, &sp);
}


void* foo1(void *arg)
{
	char s[] = "hello world show me the money";
	char* sp;
	char *p;

	p = xstrtok(s, " ");
	while (p != NULL) {
		printf("%s\n", p);
		p = xstrtok(NULL, " ");
	}

	return 0;
}

void* foo2(void *arg)
{
	char s[] = "123 456 789 999 100";
	char* sp;
	char *p;

	p = xstrtok(s, " ");
	while (p != NULL) {
		printf("%s\n", p);
		p = xstrtok(NULL, " ");
	}

	return 0;
}

int main()
{
	int i;
	pthread_t thread[2];
	pthread_create(&thread[0], NULL, &foo1, NULL);
	pthread_create(&thread[1], NULL, &foo2, NULL);

	for (i = 0; i < 2; ++i) {
		pthread_join(thread[i], NULL);
	}
}







