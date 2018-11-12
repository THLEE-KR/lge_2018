
#include <stdio.h>

// fflush(stdin)
//  : Windows에서만 동작합니다.
//    표준이 아닙니다.

int main()
{
	int age;
	char gender;

	scanf("%d", &age);
	getchar();
	gender = getchar();

	printf("age: %d, gender: %c\n", age, gender);
	return 0;
}
