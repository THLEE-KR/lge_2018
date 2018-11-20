
#include <stdio.h>

#include <wiringPi.h>

// PWM 제어를 통해서 LED 밝기를 조절하고자 한다. 

#define LED2   23 // BCM: 13(PWM1)  - Red
#define LED1   26 // BCM: 12(PWM0)  - Green

int main()
{
	int bright;
	wiringPiSetup();

	pinMode(LED1, PWM_OUTPUT);
	pinMode(LED2, PWM_OUTPUT);

	pwmWrite(LED1, 0);
	pwmWrite(LED2, 0);

	while (1) {
		for (bright = 0; bright < 1024 ; ++bright) {
			pwmWrite(LED1, bright);
			pwmWrite(LED2, bright);

			delay(1);
		}

		for (bright = 1024; bright >= 0 ; --bright) {
			pwmWrite(LED1, bright);
			pwmWrite(LED2, bright);

			delay(1);
		}
	}
}













