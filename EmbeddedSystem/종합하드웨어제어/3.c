
#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>

enum { LED1 = 27, LED2 = 24 };

int main() {
	wiringPiSetup();

	pinMode(LED1, OUTPUT);
	pinMode(LED2, OUTPUT);

	softPwmCreate(LED1, 0, 1024);
	softPwmCreate(LED2, 0, 1024);

	while (1) {
		for (int i = 0; i < 1024; i++) {
			softPwmWrite(LED1, i);
			softPwmWrite(LED2, i);
			delay(5);
		}
		delay(50);

		for (int i = 1023; i >= 0; i--) {
			softPwmWrite(LED1, i);
			softPwmWrite(LED2, i);
			delay(5);
		}
		delay(500);
	}

	return 0;
}








