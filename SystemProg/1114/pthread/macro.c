#include <stdio.h>

#define LOG() do {  			\
	printf("Hello...\n");       \
	printf("Hello...\n");		\
} while(0)			

int main()
{
#ifdef DEBUG
	printf("이 코드는 디버그 모드에서만 실행되어야 합니다.\n");
#else
	printf("지금은 릴리즈 모드 입니다...\n");
#endif


	int n = 42;
	if (n % 2 == 1)
		LOG();
}
