#include <wiringPi.h>
#include <softTone.h>

#include <stdio.h>

#define PIN 21

int scale [8] = { 262, 294, 330, 349, 392, 440, 494, 525 } ;
int main ()
{
	int i ;
	wiringPiSetup() ;
	softToneCreate(PIN) ;

	while (1)
	{
		for (i = 0 ; i < 8 ; ++i)
		{
			printf ("%3d\n", i);
			softToneWrite (PIN, scale [i]);
			delay (500);
		}
	}
}

