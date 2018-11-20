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
	softServoWrite(SERVO, -250);
	getchar();
	softServoWrite(SERVO, 0);
	getchar();
	softServoWrite(SERVO, 250);
	getchar();
	softServoWrite(SERVO, 500);
	getchar();
	softServoWrite(SERVO, 750);
	getchar();
	softServoWrite(SERVO, 1000);
	getchar();
	softServoWrite(SERVO, 1250);
	getchar();

}
