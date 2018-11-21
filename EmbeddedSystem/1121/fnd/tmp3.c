#include <mcp3422.h>    // ADC
#include <pthread.h>

#include <wiringPi.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CDS   400
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

void show_digit(int select, int value, int dot) {
	int i, j;
	int n = num[value - '0'];

	for (i = 1; i <= 3; ++i) {
		digitalWrite(i, i == select);
	}
	
	for (i = 0; i < 7; ++i) {
		digitalWrite(led[i], n & (1 << (7-i)));  // !!
	}

	digitalWrite(0, dot);
}

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
volatile int is_stopped = 0;
char* value;
int mode = 0;
void *fnd_thread(void *arg) {
	int i;
	int n;

	// 38.9
	// 38.9
	while (!is_stopped) {
		pthread_mutex_lock(&mutex);
		char* p = NULL;
		if (value != NULL) {
			p = strdup(value);
		}
		pthread_mutex_unlock(&mutex);

		if (p == NULL)
			continue;

		show_digit(3, p[3], 0);
		delay(1);
		show_digit(2, p[1], 1);
		delay(1);
		show_digit(1, p[0], 0);
		delay(1);

		free(p);
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

double get_temp() {
	int reading = analogRead(TMP36);
	double voltage = reading / 1000.;
	double temp = (voltage - 0.5) * 100;

	return temp;
}

int get_cds() {
	return analogRead(CDS);
}

int main()
{
	pthread_t thread;

	wiringPiSetup();
	init_fnd();
	mcp3422Setup(400, 0x6a, 0, 0); 

	pthread_create(&thread, NULL, fnd_thread, NULL);
	char buf[128];

	while (1) {
		getchar();
		mode = !mode;

		if (mode == 0) {
			double temp = get_temp();
			sprintf(buf, "%04.1lf", temp);
			printf("temp: %s\n", buf);
		} else {
			sprintf(buf, "%04.1lf", (get_cds() / 2048.) * 100);
			printf("cds: %s\n", buf);
		}

		value = buf;
	}
}






