#include <mcp3422.h>    // ADC
#include <pthread.h>

#include <wiringPi.h>
#include <stdio.h>
#include <string.h>

#define TMP36 401

int led[8] = {11, 10, 13, 12, 14, 15, 16, 0};
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

volatile int is_stopped = 0;
int value;
void *fnd_thread(void *arg) {
	int arr[3];
	int i;
	int n;

	while (!is_stopped) {
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

int main()
{
	pthread_t thread;

	wiringPiSetup();
	init_fnd();
	mcp3422Setup(400, 0x6a, 0, 0); 

	pthread_create(&thread, NULL, fnd_thread, NULL);

	while (1) {
		int reading = analogRead(TMP36);
		double voltage = reading / 1000.;
		double temp = (voltage - 0.5) * 100;
		value = temp;
		delay(1000);
	}
}






