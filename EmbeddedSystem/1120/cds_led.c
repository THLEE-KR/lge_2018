#include <stdio.h>
#include <wiringPi.h>
#include <mcp3422.h>

#define LED 27
#define CDS 400

int main()
{
	int i;
	int led[4] = { 27, 24, 28, 29 };

	wiringPiSetup();
	mcp3422Setup(400, 0x6a, 0, 0);

	for (i = 0; i < 4; ++i) {
		pinMode(led[i], OUTPUT);
	}

	// 2048
	// 0 ~ 511: 1개
	// 512 ~ 1023: 2개
	// 1024 ~ 1535: 3개
	// 1536 ~ 2047: 4개
	
	while (1) {
		int cds = analogRead(CDS);
		int n = cds / 512;

		printf("cds: %d\n", cds);
		for (i = 0 ; i <= n; ++i) {
			digitalWrite(led[i], HIGH);
		}

		for (i = n + 1; i < 4; ++i) {
			digitalWrite(led[i], LOW);
		}
		
		delay(500);
	}
}




