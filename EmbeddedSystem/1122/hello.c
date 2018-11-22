// LCD: Hello, world
// $ gcc hello.c ssd1306_i2c.c -lwiringPi
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <wiringPi.h>
#include "ssd1306_i2c.h"

int main() {
	char str[32] = " Hello, Pi";
	str[0] = 95 + 32;

	int fd = ssd1306I2CSetup(0x3C);  // i2c address를 인자로 전달하면 됩니다.
	displayOn(fd);

	// Text 출력 함수
	// draw_line(행, 열, 문자열)
	draw_line(1, 1, str);
	draw_line(2, 2, str);
	draw_line(3, 3, str);
	draw_line(4, 4, str);
	updateDisplay(fd);
	getchar();

	clearDisplay(fd);
	getchar();
}













