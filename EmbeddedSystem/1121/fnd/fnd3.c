#include <stdio.h>
#include <wiringPi.h>
#include <string.h>

// 1. fnd에 표시하는 동작은 계속해서 수행되어야 한다.
//  => 별도의 스레드를 만들어서 처리하자.
int led[8] = { 11, 10, 13, 12, 14, 15, 16, 0 };

// 2. fnd의 각 번호에 따른 상태를 비트열로 관리하면 좋다.
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

		for (i = 0; i < 100; ++i) {
			show_digit(1, arr[2]);
			delay(1);
			show_digit(2, arr[1]);
			delay(1);
			show_digit(3, arr[0]);
			delay(1);
		}
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

	count();
}











