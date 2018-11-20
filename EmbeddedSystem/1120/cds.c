#include <stdio.h>
#include <wiringPi.h>
#include <mcp3422.h>

#define CDS  400

int main()
{
	wiringPiSetup();
	mcp3422Setup(400, 0x6a, 0, 0);

	while (1) {
		printf("%d\n", analogRead(CDS));
		delay(100);
	}
}
