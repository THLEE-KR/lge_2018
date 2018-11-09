#include <stdio.h>

void foo()
{
	char* s = "hello";
	s[0] = 'x';
}

int main(int argc, char** argv)
{
	int i;
	for (i = 0 ; i < argc ; ++i)
		printf("argv[%d]: %s\n", i, argv[i]);

	foo();
}



