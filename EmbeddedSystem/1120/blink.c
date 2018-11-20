#include <stdio.h>
#include <stdlib.h> // exit함수를 사용하기 위함
#include <wiringPi.h>

#define INTERRUPT_GPIO 4
#define LED 27

void blink(void)
{
	int i;
	printf("인터럽트 신호 발생\n");

	for (i = 0, digitalWrite(LED, 0); i < 5; i++)
	{
		digitalWrite(LED, 1);
		delay(1000);
		digitalWrite(LED, 0);
		delay(1000);
	}
}

// ctags
//  : 코드를 분석하기 위한 도구

// jump: g, ]
// back: Ctrl + T

int main(void)
{
	wiringPiSetup() ;
	pinMode(INTERRUPT_GPIO, INPUT);
	pinMode(LED, OUTPUT);
	digitalWrite(LED, 0);

	if (wiringPiISR(INTERRUPT_GPIO, INT_EDGE_FALLING, blink) < 0)
	{
		fputs("wiringPiISR error occured\n", stderr);
		exit(1);
	}

	while (1)
	{
		switch (waitForInterrupt(INTERRUPT_GPIO, 5000))
		{
			case 0:
				fputs("Time Out\n", stderr);
				break;
			case -1:
				fputs("waitForInterrupt error occured\n", stderr);
				exit(1);
		}
	}
	return 0;
}
