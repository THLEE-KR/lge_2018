// 공통 애노드(+): 공통 선이 +에 연결되어 있다. 각 LED에 LOW를 주면
//                 불이 켜진다.
// 공통 캐소드(-): 공통 선이 -에 연결되어 있다. 각 LED에 HIGH를 주면
//                 불이 켜진다.
//   => 현재 우리 보드의 fnd는 공통 캐소드 형 입니다.

// int select[3] = { 1, 2, 3 };

#include <stdio.h>
#include <wiringPi.h>

int led[8] = { 11, 10, 13, 12, 14, 15, 16, 0 };
// int led[8] = { 7, 8, 9, 10, 11, 14, 15, 17 };

// a  b  c  d  e  f  g  dot
#if 0
int num[10][8] = {
	{ 0, 0, 0, 0, 0, 0, 1, 1 },
	{ 1, 0, 0, 1, 1, 1, 1, 1 },
	{ 0, 0, 1, 0, 0, 1, 0, 1 },
	{ 0, 0, 0, 0, 1, 1, 0, 1 },
	{ 1, 0, 0, 1, 1, 0, 0, 1 },
	{ 0, 1, 0, 0, 1, 0, 0, 1 },
	{ 0, 1, 0, 0, 0, 0, 0, 1 },
	{ 0, 0, 0, 1, 1, 1, 1, 1 },
	{ 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 0, 0, 0, 0, 1, 0, 0, 1 }
};
#endif
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

int main() {
	int i;
	wiringPiSetup();
	
	for (i = 1; i <= 3; ++i) {
		pinMode(i, OUTPUT);
	}

	for (i = 0; i < 8; ++i) {
		pinMode(led[i], OUTPUT);
	}
	
	while (1) {
		show_digit(1, 4);
		delay(1);
		show_digit(2, 2);
		delay(1);
		show_digit(3, 3);
		delay(1);
	}
}











