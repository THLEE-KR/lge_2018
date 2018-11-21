#include <stdio.h>
#include <wiringPi.h>
#include <string.h>
#include <stdlib.h>

#include <pthread.h>

int led[8] = { 11, 10, 13, 12, 14, 15, 16, 0 };
int num[10] = {
	0xFC,
	0x60,
	0xDA,
	0xF2,
	0x66,
	0xB6,
	0xBE,
	0xE0,
	0xFE,
	0xF6,
};

void show_digit(int select, int value) {
	int i, j;
	// int *arr = num[value];
	int n = num[value];

	// digitalWrite(select, HIGH); 
	for (i = 1; i <= 3; ++i) {
		digitalWrite(i, i == select);
	}
	
	for (i = 0; i < 8; ++i) {
		digitalWrite(led[i], n & (1 << (7-i)));  // !!
	}
}

int value;
void *fnd_thread(void *arg) {
	int arr[3];
	int i;
	int n;

	while (1) {
		i = 0;
		memset(arr, 0, sizeof arr);
		n = value;
		while (n > 0) {
			arr[i++] = n % 10;
			n /= 10;
		}

		show_digit(1, arr[2]);
		delay(1);
		show_digit(2, arr[1]);
		delay(1);
		show_digit(3, arr[0]);
		delay(1);
	}

	return 0;
}

void init_fnd() {
	int i;
	for (i = 1; i <= 3; ++i) {
		pinMode(i, OUTPUT);
	}

	for (i = 0; i < 8; ++i) {
		pinMode(led[i], OUTPUT);
	}
}

int main() {
	pthread_t thread;
	srand(time(0));

	wiringPiSetup();
	init_fnd();

	pthread_create(&thread, NULL, fnd_thread, NULL);
	while (getchar() != EOF) {
		value = rand() % 1000;
		printf("value: %d\n", value);
	}

	pthread_join(thread, NULL);
	return 0;
}
