
#include <pthread.h>

void* goo(void *arg) {
	printf("goo: %p\n", arg);
}

void* foo(void *arg) {
	static __thread int n;
	printf("addr:%p\n", &n);

	pthread_t thread;
	pthread_create(&thread, NULL, goo, &n);
}

int main()
{
	pthread_t thread[3];

	for (int i = 0; i < 1; ++i) {
		pthread_create(&thread[i], NULL, foo, NULL);
	}

	getchar();
}
