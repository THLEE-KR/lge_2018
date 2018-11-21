#include <stdio.h>
#include <wiringPi.h>
#include <string.h>

int led[8] = { 11, 10, 13, 12, 14, 15, 16, 0 };
int num[10][8] = {
	{ 1, 1, 1, 1, 1, 1, 0, 0 },
	{ 0, 1, 1, 0, 0, 0, 0, 0 },
	{ 1, 1, 0, 1, 1, 0, 1, 0 },
	{ 1, 1, 1, 1, 0, 0, 1, 0 },
	{ 0, 1, 1, 0, 0, 1, 1, 0 },
	{ 1, 0, 1, 1, 0, 1, 1, 0 },
	{ 1, 0, 1, 1, 1, 1, 1, 0 },
	{ 1, 1, 1, 0, 0, 0, 0, 0 },
	{ 1, 1, 1, 1, 1, 1, 1, 0 },
	{ 1, 1, 1, 1, 0, 1, 1, 0 }
};

void show_digit(int select, int value) {
	int i, j;
	int *arr = num[value];

	// digitalWrite(select, HIGH); 
	for (i = 1; i <= 3; ++i) {
		digitalWrite(i, i == select);
	}
	
	for (i = 0; i < 8; ++i) {
		digitalWrite(led[i], arr[i]);
	}
}

#if 0
void count() {
	int n;
	int value;
	int arr[3];
	int i;

	for (n = 0; n <= 999; ++n) {
		value = n;

		memset(arr, 0, sizeof arr);
		i = 0;
		while (value > 0) {
			arr[i++] = value % 10;
			value /= 10;
		}

		for (i = 0; i < 1000; ++i) {
			show_digit(1, arr[2]);
			delay(1);
			show_digit(2, arr[1]);
			delay(1);
			show_digit(3, arr[0]);
			delay(1);
		}
	}
}
#endif

void display(int value) {
	int arr[3];
	int i;

	memset(arr, 0, sizeof arr);
	i = 0;
	while (value > 0) {
		arr[i++] = value % 10;
		value /= 10;
	}

	for (i = 0; i < 100; ++i) {
		show_digit(1, arr[2]);
		delay(1);
		show_digit(2, arr[1]);
		delay(1);
		show_digit(3, arr[0]);
		delay(1);
	}
}

int main() {
	int i;
	wiringPiSetup();

	for (i = 1; i <= 3; ++i) {
		pinMode(i, OUTPUT);
	}

	for (i = 0; i < 8; ++i) {
		pinMode(led[i], OUTPUT);
	}

	display(100);
}











