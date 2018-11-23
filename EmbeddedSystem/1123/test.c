#include <stdio.h>

#include <pthread.h>
#include <wiringPi.h>

void *foo(void *arg) {
	while (1) {
		printf("foo...\n");
		delay(100);
	}

	return 42;
}

int main() {
	pthread_t thread;
	pthread_create(&thread, NULL, foo, NULL);

	while (1) {
		printf("main...\n");
		delay(100);
	}
}
