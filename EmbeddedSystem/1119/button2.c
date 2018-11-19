#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

// Interrupt 기반

#define SW    4
#define LED   27

// ISR(Interrupt Service Routine)
//  : 등록한 인터럽트가 발생하면 호출되는 함수
void blink(void)
{
	int i;
	printf("인터럽트 신호 발생...\n");

	i = 0;
	digitalWrite(LED, 0);
	while (i < 5) {
		digitalWrite(LED, 1);
		delay(1000);
		digitalWrite(LED, 0);
		delay(1000);
	}
}

// INT_EDGE_FALLING: 5V -> 0V  : 버튼을 누르는 시점
// INT_EDGE_RISING: 0V -> 5V   : 버튼을 띄는 시점

int main()
{
	wiringPiSetup();
	pinMode(LED, OUTPUT);

	// 1. 인터럽트를 사용하기 위해서는 INPUT 모드로 사용해야 합니다.
	pinMode(SW, INPUT);

	// 2. wiringPiISR을 통해 인터럽트 핸들러를 등록한다.
	wiringPiISR(SW, INT_EDGE_BOTH, blink);
		
	while (1) {
		switch (waitForInterrupt(SW, 5000)) {
			case 0: 
				printf("Timeout...\n");
				break;
			case -1:
				printf("error...\n");
				exit(1);
		}
	}

}












