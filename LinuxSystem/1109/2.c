
#include <pthread.h>

void* foo(void* p)
{
	return 0;
}

int main()
{
	pthread_t thread;
	pthread_create(&thread, NULL, foo, NULL);
}
