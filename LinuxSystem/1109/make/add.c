#include "main.h" 

void foo()
{
	add(10, 20);
}

int add(int a, int b)
{
	foo();
	return a + b;
}

