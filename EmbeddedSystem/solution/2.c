
#include <stdio.h>
#include <wiringPi.h>

enum { SW1 = 4, SW2 };
enum { LED1 = 27, LED2 = 24 };

int main() {
	wiringPiSetup();

	pinMode(SW1, INPUT);
	pinMode(SW2, INPUT);

	pinMode(LED1, OUTPUT);
	pinMode(LED2, OUTPUT);

	digitalWrite(LED1, 0); 
	digitalWrite(LED2, 0); 

	while (1) {
		if (digitalRead(SW1) == 0) {
			printf("SW1 pressed\n");

			for (int i = 0; i < 3; i++) {
				digitalWrite(LED1, 1); delay(500);
				digitalWrite(LED1, 0); delay(500);
			}

			unsigned int value = 200;
			while (value >= 10) {
				digitalWrite(LED1, 1);
				digitalWrite(LED2, 1);
				delay(value);

				digitalWrite(LED1, 0);
				digitalWrite(LED2, 0);
				delay(value);

				value -= 10;
			}
		}
		else if (digitalRead(SW2) == 0) {
			printf("SW2 pressed\n");

			for (int i = 0; i < 3; i++) {
				digitalWrite(LED2, 1); delay(500);
				digitalWrite(LED2, 0); delay(500);
			}
		}
	}

	return 0;
}








