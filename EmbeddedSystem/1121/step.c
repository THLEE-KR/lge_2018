#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <wiringPi.h>

int pin[4] = { 27, 24, 28, 29 };
//             16, 19, 20, 21     // BCM

// 1-2상 여자 동작입니다.
//  => 한 스텝의 동작은 자석이 45도 회전합니다.
//  => 모터의 회전은 약 1.8도 회전합니다. 
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

int main() {
	int i;
	wiringPiSetup();

	// OUTPUT 모드로 지정하면 됩니다.
	for (i = 0; i < 4; ++i) {
		pinMode(pin[i], OUTPUT);
	}

	while (1) {
		forwards(200);
	}
	getchar();
}































