#include <stdio.h>

#include <wiringPi.h>
#include <mcp3422.h>    // ADC

#define TMP36 401

int main()
{
	wiringPiSetup();
	
	// Pin base: 400
	// i2c address: i2cdetect -y 1
	//              0x6a

	// Base: 400
	// AD_CH1(CDS): 400
	// AD_CH2(TMP36): 401
	mcp3422Setup(400, 0x6a, 0, 0);  // ACD 초기화

	while (1) {
		// int reading = analogRead(401);
		int reading = analogRead(TMP36);
		double voltage = reading / 1000.;

		double temp = (voltage - 0.5) * 100;
		printf("%lf, %lf\n", voltage, temp);
		delay(1000);
	}
}






