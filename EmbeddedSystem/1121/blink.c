#include <stdio.h>
#include <wiringPi.h>

int led_pin[4] = {27,24,28,29};
int main (void)
{
	int i, led ;

	printf ("Raspberry Pi - 4-LED Sequencer\n") ;
	printf ("==============================\n") ;
	printf ("\n") ;
	printf ("Connect LEDs to the first 4 GPIO pins and watch ...\n") ;

	wiringPiSetup () ;
	for (i = 0 ; i < 4 ; ++i)
		pinMode (led_pin[i], OUTPUT) ;

	for (;;)
	{
		for (led = 0 ; led < 4 ; ++led)
		{
			digitalWrite (led_pin[led], 1) ;
			delay (100) ;
		}

		for (led = 0 ; led < 4 ; ++led)
		{
			digitalWrite (led_pin[led], 0) ;
			delay (100) ;
		}
	}
}

