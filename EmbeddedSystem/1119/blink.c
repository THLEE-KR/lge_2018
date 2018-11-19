
// gcc blink.c -lwiringPi
#include <stdio.h>
#include <wiringPi.h> // !!

#define LED 27

int main()
{
	printf("Raspberry Pi Blink....\n");
	
	wiringPiSetup();       // 라이브러리 초기화

	pinMode(LED, OUTPUT);  // echo out > direction

	while (1) {
		digitalWrite(LED, HIGH);
		delay(500);  // 500 ms
		digitalWrite(LED, LOW);
		delay(500);  // 500 ms
	}
}




