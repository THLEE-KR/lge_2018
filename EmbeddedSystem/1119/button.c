#include <stdio.h>
#include <wiringPi.h>

#define SW    4
#define LED   27

int main()
{
	wiringPiSetup();

	pinMode(SW, INPUT);
	pinMode(LED, OUTPUT);

	while (1) {
		digitalWrite(LED, 0); // off
		delay(500);
		if (digitalRead(SW) == 0) {
			digitalWrite(LED, 1);
			delay(500);

			// printf("digitalRead(SW) == 0\n");
		} else {
			// printf("digitalRead(SW) == 1\n");
		}
	}

}
