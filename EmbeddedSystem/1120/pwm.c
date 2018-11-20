#include <stdio.h>
#include <stdlib.h>

#include <wiringPi.h>
#include <softPwm.h>    // !!!

// PWM 제어를 통해서 LED 밝기를 조절하고자 한다. 
// PWM 종류
//  HW PWM: Red, Green
//  SW PWM: Blue

#define RED_LED     23     // BCM: 13(PWM1)  - Red
#define GREEN_LED   26     // BCM: 12(PWM0)  - Green
#define BLUE_LED    22     // BCM: 6

int main()
{
	int bright;
	wiringPiSetup();

	pinMode(GREEN_LED, PWM_OUTPUT);
	pinMode(RED_LED, PWM_OUTPUT);

	// Soft PWM
	pinMode(BLUE_LED, OUTPUT);        
	softPwmCreate(BLUE_LED, 0, 1024);
	//----------

	pwmWrite(GREEN_LED, 0);
	pwmWrite(RED_LED, 0);
	softPwmWrite(BLUE_LED, 0);

	while (1) {
		for (bright = 0; bright < 1024 ; ++bright) {
			pwmWrite(GREEN_LED, bright);
			pwmWrite(RED_LED, bright);
			softPwmWrite(BLUE_LED, bright);

			delay(1);
		}

		for (bright = 1024; bright >= 0 ; --bright) {
			pwmWrite(GREEN_LED, bright);
			pwmWrite(RED_LED, bright);
			softPwmWrite(BLUE_LED, bright);

			delay(1);
		}
	}
}













