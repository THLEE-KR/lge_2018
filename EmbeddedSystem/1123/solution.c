#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h> 
#include <time.h>
#include <pthread.h>
#include <sys/types.h> 

#include <wiringPi.h>
#include <mcp3422.h>  
#include <softTone.h>
#include "ssd1306_i2c.h"

#define ARR_SIZE(x)		(sizeof((x))/sizeof(*(x)))

enum {
	CDS = 400, TMP36 = 401, SPKR = 21
};

enum {
	TEMP_NOTES = 0, CDS_NOTES
};
int temp_notes[] = { 
	391, 391, 440, 440, 391, 391, 329.63, 329.63,
	391, 391, 329.63, 329.63, 293.66, 293.66, 293.66, 0,
	391, 391, 440, 440, 391, 391, 329.63, 329.63,
	391, 329.63, 293.66, 329.63, 261.63, 261.63, 261.63, 0
};

int cds_notes[] = {
		659, 622, 659, 622, 659, 493, 587, 523, 440,
		261, 329, 440, 493, 329, 415, 493, 523,
		329, 659, 622, 659, 622, 659, 493, 587, 523, 440,
		261, 329, 440, 493, 329, 523, 493, 440,
		493, 523, 587, 659, 391, 698, 659, 587,
		349, 659, 587, 523, 329, 587, 523, 493,
		659, 329, 659, 659, 3329, 622, 659, 587, 659, 587, 659,
		587, 659, 622, 659, 622, 659, 493, 587, 523, 440,
		261, 329, 440, 493, 329, 415, 493, 261
};

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

int is_playing = 0;
void *play_thread(void *arg) {
	pthread_mutex_lock(&mtx);
	if (is_playing) {
		pthread_mutex_unlock(&mtx);
		return NULL;
	}
	is_playing = 1;

	printf("play_thread\n");
	int notes = (int)arg;

	int len = 0;
	int *arr = NULL;
	switch(notes) {
		case TEMP_NOTES:
			len = ARR_SIZE(temp_notes);
			arr = temp_notes;
			break;
		case CDS_NOTES:
			len = ARR_SIZE(cds_notes);
			arr = cds_notes;
			break;
		default:
			return NULL;
	}

	for (int i = 0; i < len; i++) {
		softToneWrite(SPKR, arr[i]);
		delay(280);                 
	}

	is_playing = 0;
	pthread_mutex_unlock(&mtx);
	return NULL;
}

int get_temp() {
	int reading = analogRead(TMP36);
	double voltage = reading / 1000.;
	double sTemp = (voltage - 0.5) * 100;

	return (int)sTemp;
}

int get_cds() {
	return analogRead(CDS);
}

int is_running = 1;
void sig_handler(int signo) {
	if (signo == SIGINT)
		is_running = 0;
}

int main() {
	signal(SIGINT, sig_handler);

	wiringPiSetup();
	mcp3422Setup(400, 0x6a, 0, 0); 
	softToneCreate(SPKR) ;   

	int fd = ssd1306I2CSetup(0x3C);
	displayOn(fd); 

	char sDate[16];
	char sTime[16];
	char sTemp[16];
	char sCds[16];
	while (is_running) {
		pthread_t tid;
		int notes = 0;

		int value = get_temp();
		if (value > 30 && !is_playing) {
			printf("value = %d, is_playing = %d\n", value, is_playing);
			notes = TEMP_NOTES;
			pthread_create(&tid, NULL, play_thread, (void*)notes);
			pthread_detach(tid);
		}
		sprintf(sTemp, "temp: %d", value);

		value = get_cds();
		if (value < 1024 && !is_playing) {
			notes = CDS_NOTES;
			pthread_create(&tid, NULL, play_thread, (void*)notes);
			pthread_detach(tid);
		}
		sprintf(sCds, "cds: %d", value);

		time_t cur_time = time(NULL);
		struct tm *tm = localtime(&cur_time);

		sprintf(sDate, "%d.%d.%d", tm->tm_year+1900, tm->tm_mon+1, tm->tm_mday);
		sprintf(sTime, "%d:%d", tm->tm_hour, tm->tm_min);

		draw_line(1, 1, sDate);
		draw_line(2, 1, sTime);
		draw_line(3, 1, sTemp);
		draw_line(4, 1, sCds);

		updateDisplay(fd);
		sleep(1);
	}

	clearDisplay(fd);
	displayOff(fd);

	return 0;
}

