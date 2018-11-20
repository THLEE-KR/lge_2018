#include <stdio.h>

#include <wiringPi.h>
#include <softServo.h>

// gcc servo.c ~/wiringPi/wiringPi/softServo.c -lwiringPi

#define SERVO 25
int main()
{
	wiringPiSetup();
	// 사용하지 않는 핀은 -1로 지정합니다.
	softServoSetup(SERVO, -1, -1, -1, -1, -1, -1, -1);

	while (1) {
		softServoWrite(SERVO, -250);
		delay(300);
		softServoWrite(SERVO, 0);
		delay(300);
		softServoWrite(SERVO, 250);
		delay(300);
		softServoWrite(SERVO, 500);
		delay(300);
		softServoWrite(SERVO, 750);
		delay(300);
		softServoWrite(SERVO, 1000);
		delay(300);
		softServoWrite(SERVO, 1250);
		delay(300);
	}
}





