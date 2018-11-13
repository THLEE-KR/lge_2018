#include <unistd.h>
#include <stdio.h>

// fork(): 새로운 프로세스를 생성합니다.
// - 기존 프로세스: 부모 프로세스
// - 새로운 프로세스: 자식 프로세스

int main()
{
	fork();
	printf("hello\n");
}
