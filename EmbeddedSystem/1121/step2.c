#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <wiringPi.h>

#include <pthread.h>

int pin[4] = { 27, 24, 28, 29 };
int seq[8][4] = {
	{ 1,0,0,1 },
	{ 1,0,0,0 },
	{ 1,1,0,0 },
	{ 0,1,0,0 },
	{ 0,1,1,0 },
	{ 0,0,1,0 },
	{ 0,0,1,1 },
	{ 0,0,0,1 }
};

void forwards(int count) {
	int i, j, k;

	for (i = 0 ; i < count ; ++i) {
		for (j = 0; j < 8; ++j) {
			for (k = 0; k < 4; ++k) {
				digitalWrite(pin[k], seq[j][k]);
			}
			delayMicroseconds(800);
		}
	}
}

void backwards(int count) {
	int i, j, k;

	for (i = 0 ; i < count ; ++i) {
		for (j = 0; j < 8; ++j) {
			for (k = 0; k < 4; ++k) {
				digitalWrite(pin[k], seq[7 - j][k]);
			}
			delayMicroseconds(800);
		}
	}
}

int flag = 1;
void *thread_routine(void *a) {
	int i, j, k;

	while (1) {
		for (j = 0; j < 8; ++j) {
			for (k = 0; k < 4; ++k) {
				int index = flag ? j : 7 - j;
				digitalWrite(pin[k], seq[index][k]);
			}
			delayMicroseconds(800);
		}
	}
}

int main() {
	int i;
	pthread_t thread;
	wiringPiSetup();

	// OUTPUT 모드로 지정하면 됩니다.
	for (i = 0; i < 4; ++i) {
		pinMode(pin[i], OUTPUT);
	}

	pthread_create(&thread, NULL, thread_routine, NULL);
	while (1) {
		getchar();
		flag = !flag;
	}
}









