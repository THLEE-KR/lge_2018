#include <wiringPi.h>
#include <softPwm.h>
#include <stdio.h>

#define uchar unsigned char

#define LedPinRed    26
#define LedPinGreen  23
#define LedPinBlue   22

void ledInit(void)
{
	pinMode (LedPinRed, PWM_OUTPUT) ;
	pinMode (LedPinGreen, PWM_OUTPUT) ;
	softPwmCreate(LedPinBlue, 0, 100);
}

void ledColorSet(uchar r_val, uchar g_val, uchar b_val)
{
	pwmWrite(LedPinRed,   r_val);
	pwmWrite(LedPinGreen, g_val);
	softPwmWrite(LedPinBlue,  b_val);
}

int main(void)
{
	wiringPiSetup();
	ledInit();

	while(1){
		ledColorSet(0xff,0x00,0x00);   //red
		delay(500);
		ledColorSet(0x00,0xff,0x00);   //green
		delay(500);
		ledColorSet(0x00,0x00,0xff);   //blue
		delay(500);
		ledColorSet(0xff,0xff,0x00);   //yellow
		delay(500);
		ledColorSet(0xff,0x00,0xff);   //pick
		delay(500);
		ledColorSet(0xc0,0xff,0x3e);
		delay(500);
		ledColorSet(0x94,0x00,0xd3);
		delay(500);
		ledColorSet(0x76,0xee,0x00);
		delay(500);
		ledColorSet(0x00,0xc5,0xcd);
		delay(500);
	}
	return 0;
}




